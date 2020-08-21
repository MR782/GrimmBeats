#pragma once
#include<iostream>
#include"json11.hpp"

//音楽ファイルの読み込みや再生を行う

class AudioObject {
	friend class Audio;
	bool exist;//読み込んで膝窩のフラグ
	std::vector<std::string> scopes;//読み込み時の名前

	bool ExistScope(std::string);
	void SetDefault();//値が入っていない場合デフォルトで入力
public:
	AudioObject();
	bool loop;//ループ再生するかのフラグ
	std::string  name;//再生又は停止時にどれか判断する識別子
	std::string  path;//音楽ファイルまでのパス
	int handle;//音楽ハンドル
};

class Audio {
private:
	static std::vector<std::shared_ptr<AudioObject>> audioobj;
	static void RegisterAudio(AudioObject&);
public:
	static void Initialize();
	static void Play(std::string name,bool is_multiple = true);
	static int Load(std::string name);
	static void StopAll();
	static void Stop(std::string name);
	static void StopScope(std::string scope);
	static void SetVolumeAudioName(std::string name,int percent);
	static void SetVolumeAudioScope(std::string scope, int percent);
	static bool CheckPlay(std::string);//特定のBGMが再生中か調べる
	static bool CheckPlayScope(std::string scope);//指定したスコープのBGMがなっているか確認
	static void Finalize();
	static void DeleteSoundDataName(std::string name);//特定の音楽データをメモリから削除(nameで指定)
	static void DeleteSoundDataScope(std::string scope);//特定の音楽データをメモリから削除(scopeで指定)
	static void DeleteSoundDataAll();//読み込み済みの音楽データをすべてメモリから削除
};