#include "MovieResource.h"
#include"JsonHelper.h"
#include"./dxlib/DxLib.h"

MovieObject::MovieObject()
{
	this->exist = false;
	this->handle = 0;
	this->loop = false;
	this->name = "";
	this->path = "";
}

bool MovieObject::ExistScope(std::string scope_)
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

//////////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<MovieObject>> MovieResource::movie_obj;

void MovieResource::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/movieData.json");
	//-------------------------------------------------------------
	for (auto& item : json["movie"].array_items()) {//ファイル内のデータ分繰り返す
		std::shared_ptr<MovieObject> movie = std::make_shared<MovieObject>();
		movie->exist = false;//まだ読み込んでいない
		movie->name = item["name"].string_value();//識別子
		movie->loop = item["loop"].bool_value();//ループの判断
		movie->path = item["path"].string_value();//ファイルのパス
		for (auto& scope : item["scope"].array_items()) {//読み込む際の識別子
			movie->scopes.push_back(scope.string_value());
		}
		movie_obj.push_back(std::move(movie));//所有権の移行
	}
}

void MovieResource::Finalize()
{
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		DeleteGraph((*itr)->handle);
	}
	movie_obj.clear();
}


void MovieResource::RegisterMovie(MovieObject& obj)
{
	//まだ読み込んでいないなら
	if (obj.exist == false) {
		//ハンドルにムービーデータを読み込む
		obj.handle = LoadGraph(obj.path.c_str());
		obj.exist = true;//読み込み済み
	}
}


int MovieResource::Load(std::string scope)
{
	int num = 0;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->exist == false) {//読み込まれていないなら
			if ((*itr)->ExistScope(scope)) {
				RegisterMovie(*(*itr));//登録
				num++;
			}
		}
	}
	return num;//番号を返す
}

bool MovieResource::CheckPlay(std::string name)
{
	bool check = false;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			check = GetMovieStateToGraph((*itr)->handle);
		}
	}
	return check;
}

void MovieResource::DeleteMovieMem(std::string name)
{
	//指定したオブジェクトをメモリから消す
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			DeleteGraph((*itr)->handle);//ハンドルデータを削除
			(*itr)->exist = false;
		}
	}
}

std::shared_ptr<MovieObject> MovieResource::Get(std::string name)
{
	std::shared_ptr<MovieObject> ret = nullptr;//空っぽの状態
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->name == name) {//その名前があるなら
			ret = (*itr);//そのオブジェクトを返す
		}
	}
	return ret;
}
