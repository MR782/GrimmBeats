#pragma once
#include<string>
#include<memory>
#include<vector>

struct MovieObject {
	MovieObject();
	friend class MovieResource;
	std::string name;//識別名
	std::string path;//ファイルパス
	bool loop;//ループ再生するか
	int handle;//ハンドル
private:
	bool exist;//読み込み済みか判断
	std::vector<std::string> scopes;//読み込み時の名前
	bool ExistScope(std::string);
};

class MovieResource {
	static std::vector<std::shared_ptr<MovieObject>> movie_obj;//ムービーデータを格納する配列
	static void RegisterMovie(MovieObject&);//オブジェクトを登録
public:
	static void Initialize();
	static void Finalize();
	static int Load(std::string scope);//スコープ内を検索して一致するものをロードする
	static bool CheckPlay(std::string name);//すでに再生されているか確認
	static void DeleteMovieMem(std::string name);//メモリからムービーデータを削除する
	static std::shared_ptr<MovieObject> Get(std::string name);//名前が一致するもののポインタを返す
};