#include "JsonHelper.h"
#include<fstream>

json11::Json JsonHelper::JsonInitialize(std::string filepath)
{
	std::ifstream jsonfile(filepath);//使用ファイル設定
	if (jsonfile.fail()) throw("jsonFile is not found.");//例外処理
	//Jsonを使用する準備------------------------------------------
	std::istreambuf_iterator<char> it(jsonfile);
	std::istreambuf_iterator<char> last;
	std::string json_str(it, last);	//string形式のjson
	std::string err;
	//ファイルを閉じる
	jsonfile.close();
	return json11::Json::parse(json_str, err);//Jsonで使えるようにする
}
