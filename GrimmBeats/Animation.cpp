#include "Animation.h"
#include"./dxlib/DxLib.h"
//#include"CoreScene.h"

void Animation::SwitchAnime()
{
	//アニメーションの切り替え
	current_anime++;
	if (current_anime >= object->sheets) {//問題
		//ループしないなら最後の画像で止める
		if (object->loop == true) { current_anime = 0; }//ループ有り
		else {
			current_anime = object->sheets;
		}
	}
}

Animation::Animation()
{
	current_anime = 0;
	current_rate = 0;
}

Animation::~Animation()
{
	object.reset();
}

void Animation::DrawAnime(Point point)
{
	//オブジェクトが空でないなら
	if (object != nullptr) {
		//dxlibの描画命令
		DrawGraph((int)point.x,
			(int)point.y,
			*(object->handle + current_anime), TRUE);
		current_rate++;
		if (object->interval != 0) {//インターバルが設定されているなら
			if (object->interval / current_rate == 1) { //インターバルをレートで割って答えが　1　なら
				current_rate = 0;//レートを0に設定
				SwitchAnime();//アニメーションの処理(画像切り替え)
			}
		}
	}
}

void Animation::DrawAnime(Vector2 point)
{
	//オブジェクトが空でないなら
	if (object != nullptr) {
		//dxlibの描画命令
		DrawGraph((int)point.x,
			(int)point.y,
			*(object->handle + current_anime), TRUE);
		current_rate++;
		if (object->interval != 0) {//インターバルが設定されているなら
			if (object->interval / current_rate == 1) { //インターバルをレートで割って答えが　1　なら
				current_rate = 0;//レートを0に設定
				SwitchAnime();//アニメーションの処理(画像切り替え)
			}
		}
	}
}

void Animation::Set(std::string name)
{
	if (object != GraphicResource::Get(name)) {
		//今のアニメーションと設定するアニメーションが違うなら
		object = GraphicResource::Get(name);//更新
		current_rate = 0;
		current_anime = 0;
	}
}
