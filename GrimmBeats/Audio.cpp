﻿#include "Audio.h"
#include"JsonHelper.h"
#include<memory>
#include"./dxlib/DxLib.h"

std::vector<std::shared_ptr<AudioObject>> Audio::audioobj;

void AudioObject::SetDefault()
{
	if (loop == NULL) {
		loop = false;//ループ記述がない場合falseにする（ループしない）
	}
}

AudioObject::AudioObject()
{
	//オブジェクトの初期化
	this->exist = false;
	this->handle = 0;
	this->loop = false;
	this->name = "";
	this->path = "";
	this->scopes.clear();
}

void Audio::RegisterAudio(AudioObject& obj)
{
	//まだ読み込んでいないなら
	if (obj.exist == false) {
		//ハンドルにサウンドデータを読み込む
		obj.handle = LoadSoundMem(obj.path.c_str());
		obj.exist = true;//読み込み済み
	}
}

void Audio::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/audiosource.json");
	//-------------------------------------------------------------
	for (auto& item : json["audio"].array_items()) {//ファイル内のデータ分繰り返す
		std::shared_ptr<AudioObject> audio = std::make_shared<AudioObject>();
		audio->exist = false;//まだ読み込んでいない
		audio->name = item["name"].string_value();//識別子
		audio->loop = item["loop"].bool_value();//ループの判断
		audio->path = item["path"].string_value();//ファイルのパス
		for (auto& scope : item["scope"].array_items()) {//読み込む際の識別子
			audio->scopes.push_back(scope.string_value());
		}
		audio->SetDefault();//値が入っていない場合デフォルト値をセット
		audioobj.push_back(std::move(audio));//所有権の移行
	}
}

void Audio::Play(std::string name, bool is_multiple)
{
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		if ((*itr)->name == name) {//名前を見つけたら
			int playtype;
			//ループをするかしないか判断
			if ((*itr)->loop == true) playtype = DX_PLAYTYPE_LOOP;//ループ再生
			else playtype = DX_PLAYTYPE_BACK;//バックグラウンド再生

			if (is_multiple == true) {//多重再生OKのものなら
				PlaySoundMem((*itr)->handle, playtype);//再生
			}
			else {//多重再生禁止なら
				if (CheckSoundMem((*itr)->handle) == false) {//再生中か確認してから
					PlaySoundMem((*itr)->handle, playtype);//再生
				}
			}
			break;
		}
	}
}

int Audio::Load(std::string scope_)
{
	int num = 0;
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		if ((*itr)->exist == false) {//読み込まれていないなら
			if ((*itr)->ExistScope(scope_)) {
				RegisterAudio(*(*itr));//登録
				num++;
			}
		}
	}
	return num;//番号を返す
}

void Audio::StopAll()
{
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		//再生中なら
		if (CheckPlay((*itr)->name)) {
			StopSoundMem((*itr)->handle);//停止
		}
	}
}

void Audio::Stop(std::string name)
{
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		if ((*itr)->name == name) {//名前を見つけたら
			//再生中なら
			if (CheckPlay((*itr)->name)) {
				StopSoundMem((*itr)->handle);//停止
				break;
			}
		}
	}
}

void Audio::SetVolumeAudioName(std::string name, int percent)
{
	//指定した名前のボリュームを設定する
	for (auto itr = audioobj.begin(); itr != audioobj.end(); itr++) {
		ChangeVolumeSoundMem(255 * percent / 100, (*itr)->handle);
	}
}

void Audio::SetVolumeAudioScope(std::string scope, int percent)
{
	//指定したスコープのボリュームを設定する
	for (auto itr = audioobj.begin(); itr != audioobj.end(); itr++) {
		for (auto scope_itr = (*itr)->scopes.begin(); scope_itr != (*itr)->scopes.end(); scope_itr++) {
			if (scope == *scope_itr) {
				ChangeVolumeSoundMem(255 * percent / 100, (*itr)->handle);
			}
		}
	}
}

void Audio::StopScope(std::string scope)
{
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		for (auto scope_itr = (*itr)->scopes.begin(); scope_itr != (*itr)->scopes.end(); scope_itr++) {
			if ((*scope_itr == scope)) {
				if (CheckPlay((*itr)->name)) {
					StopSoundMem((*itr)->handle);
				}
			}
		}
	}
}

bool Audio::CheckPlay(std::string name)
{
	bool check = false;
	//読み込んだオーディオデータの数だけループを回す
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		if ((*itr)->name == name) {//引数と同じ名前を見つけたら
			//再生中なら
			if (CheckSoundMem((*itr)->handle) == 1) {
				check = true;
				break;
			}
			else if (CheckSoundMem((*itr)->handle) == 0) {
				check = true;
			}
		}
	}
	return check;
}

bool Audio::CheckPlayScope(std::string scope)
{
	bool check = false;
	//読み込んだオーディオデータの数だけループを回す
	for (auto itr = audioobj.begin(); itr != audioobj.end(); ++itr) {
		for (auto scope_itr = (*itr)->scopes.begin(); scope_itr != (*itr)->scopes.end(); scope_itr++) {
			if ((*scope_itr == scope)) {
				//再生中なら
				if (CheckSoundMem((*itr)->handle) == 1) {
					check = true;
					break;
				}
			}
		}
	}
	return check;
}

void Audio::Finalize()
{
	//読み込んだオーディオデータをクリア
	InitSoundMem();//

	audioobj.clear();
}

void Audio::DeleteSoundDataName(std::string name)
{
	for (auto itr = audioobj.begin(); itr != audioobj.end(); itr++) {
		//名前が一致したら
		if ((*itr)->name == name) {
			//メモリからハンドルを削除
			(*itr)->exist = false;
			DeleteSoundMem((*itr)->handle);
		}
	}
}

void Audio::DeleteSoundDataScope(std::string scope)
{
	//特定のスコープを持つAudioObjectのハンドルをメモリから削除
	for (auto itr = audioobj.begin(); itr != audioobj.end(); itr++) {
		for (auto scope_itr = (*itr)->scopes.begin(); scope_itr != (*itr)->scopes.end(); scope_itr++) {
			if ((*scope_itr == scope)) {
				(*itr)->exist = false;
				DeleteSoundMem((*itr)->handle);
			}
		}
	}
}

void Audio::DeleteSoundDataAll()
{
	for (auto itr = audioobj.begin(); itr != audioobj.end(); itr++) {
		DeleteSoundMem((*itr)->handle);
	}
}

bool AudioObject::ExistScope(std::string scope_)
{
	bool check = false;
	//そのオブジェクトのスコープの数だけ繰り返す
	for (auto&& scope : scopes) {
		if (scope == scope_) {//引数とスコープが合致するものがあったら
			check = true;//trueにする
			break;
		}
	}
	return check;//調べた結果を返す
}
