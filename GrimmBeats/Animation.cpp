#include "Animation.h"
#include"./dxlib/DxLib.h"
#include"Time.h"

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

void Animation::ExtendAnimeDraw(Rect rect)
{
	//オブジェクトが空でないなら
	if (object != nullptr) {
		//dxlibの描画命令
		DrawExtendGraph(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h,
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

void Animation::BlinkDraw(int period, int a_percent, Vector2 pos)
{
	if (this == nullptr) return;

	int sin_a = a_percent + (int)(sin((PI * 2 / period * Time::freamtime)) * a_percent);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, sin_a);

	this->DrawAnime(pos);

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);
}

void Animation::BlinkExtendDraw(int period, int a_percent, Rect drawrect)
{
	if (this == nullptr) return;

	int sin_a = a_percent + (int)(sin((PI * 2 / period * Time::freamtime)) * a_percent);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, sin_a);

	this->ExtendAnimeDraw(drawrect);

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);
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
