#include "GraphicResource.h"
#include"./dxlib/DxLib.h" 
#include"JsonHelper.h"
#include <iterator>
#include "json11.hpp"

std::vector<std::shared_ptr<GraphicObject>> GraphicResource::graph;

//-----------------------------------------------
//Jsonからの読み込みなど
//------------------------------------------------
void GraphicResource::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/resource.json");
	//データ登録
	for (auto& item : json["graph"].array_items()) {
		std::shared_ptr<GraphicObject> obj = std::make_shared<GraphicObject>();
		obj->exist = false;
		obj->name = item["name"].string_value();//識別するための名前
		obj->path = item["path"].string_value();//画像のファイルパス
		obj->vertical = item["vertical"].int_value();//分割時縦方向に何枚あるか
		obj->horizontal = item["horizontal"].int_value();//分割時横方向に何枚あるか
		obj->width = item["width"].int_value();//画像の横の大きさ
		obj->height = item["height"].int_value();//画像の縦の大きさ
		obj->loop = item["loop"].bool_value();//ループするか
		obj->interval = item["interval"].int_value();//画像を切り替える時間
		obj->sheets = item["sheets"].int_value();//全部で何枚あるか
		for (auto& scope : item["scope"].array_items()) {//ロードの際の名前
			obj->scopes.push_back(scope.string_value());
		}
		obj->SetDefaultToEmpty();
		graph.push_back(std::move(obj));
	}
}

std::shared_ptr<GraphicObject> GraphicResource::Get(std::string name)
{
	std::shared_ptr<GraphicObject> ret = nullptr;//空っぽの状態
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		if ((*itr)->name == name) {//その名前があるなら
			ret = (*itr);//そのオブジェクトを返す
			break;
		}
	}
	return ret;
}

void GraphicResource::Finalize()
{
	DeleteAll();
}

bool GraphicResource::ExistName(std::string name)
{
	//nameが存在しているか調べるメソッド
	bool ret = false;
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		if ((*itr)->name == name) {
			ret = true;
			break;
		}
	}
	return ret;
}

void GraphicResource::RegisterGraph(GraphicObject& obj)
{
	if (obj.exist == false) {
		obj.handle = new int[obj.sheets];	//アニメーション画像のフレーム枚数分のハンドル領域を確保する
		obj.exist = true;
		//メモリに画像を保存する
		LoadDivGraph(
			obj.path.c_str(),//ファイルパス
			obj.sheets,//画像を分割した際の全数
			obj.horizontal,//X方向の分割数
			obj.vertical,//Y方向の分割数
			obj.width,//画像の横の大きさ
			obj.height,//画像の縦の大きさ
			obj.handle//画像ハンドル
		);		//JSONに書かれた情報をLoadDivGraphから読み込むn
	}
}

void GraphicResource::DeleteGraphScope(std::string scope)
{
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		if ((*itr)->ExitsScope(scope)) {//scopeが存在している
			(*itr)->exist = false;
			for (int i = 0; i < (*itr)->sheets; i++) {
				DeleteGraph((*itr)->handle[i]);
			}
			delete (*itr)->handle;
		}
	}
}


int GraphicResource::Load(std::string _scope)
{
	//scopeの文字列の画像をjsonから検索し、読み込む
	//読み込んだ枚数を返す
	int ret = 0;
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		if ((*itr)->exist == false) {	//オブジェクトが未登録
			if ((*itr)->ExitsScope(_scope)) {		//scopeが存在している
				RegisterGraph(*(*itr));//登録
				ret++;//総合数増加
			}
		}
	}
	return ret;
}

void GraphicResource::DeleteAll()
{
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		if ((*itr)->exist == true) {	//オブジェクトが登録済み
			//シートの分だけ絵を削除する
			for (int i = 0; i < (*itr)->sheets; i++) {
				DeleteGraph(*((*itr)->handle + i));
			}
			delete (*itr)->handle;
		}
	}
}

int* GraphicResource::GetHandle(std::string name_)
{
	int* handle = nullptr;
	for (auto itr = graph.begin(); itr != graph.end(); itr++) {
		if ((*itr)->name == name_) {
			handle = (*itr)->handle;
		}
	}
	return handle;
}

//-------------------------------------------------------
//グラフィックオブジェクト
//-------------------------------------------------------
void GraphicObject::SetDefaultToEmpty()
{
	//デフォルト値の設定
	if (vertical == 0) vertical = 1;
	if (horizontal == 0) horizontal = 1;
	if (width == 0) width = 32;
	if (height == 0) height = 32;
	if (sheets == 0) sheets = vertical * horizontal;
}

bool GraphicObject::ExitsScope(std::string _scope)
{
	bool check = false;
	for (auto&& scope : scopes) {//スコープの数繰り返す
		if (scope == _scope) {//スコープ発見
			check = true;//存在していることを証明
			break;
		}
	}
	return check;
}

GraphicObject::GraphicObject()
{
	//データの初期化
	this->exist = false;
	this->handle = 0;
	this->height = 0;
	this->horizontal = 0;
	this->interval = 0;
	this->loop = false;
	this->name = "";
	this->path = "";
	this->scopes.clear();
	this->sheets = 0;
	this->vertical = 0;
	this->width = 0;
}
