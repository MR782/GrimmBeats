#include "Movie.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

Movie::Movie()
{
	this->object = std::make_shared<MovieObject>();
}

void Movie::Draw()
{
	//ムービーが再生されていないなら
	if (MovieResource::CheckPlay(object->name) == false) {
		SeekMovieToGraph(object->handle, 0);
		if (object->loop == true) {
			PlayMovieToGraph(object->handle);//再生
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//加算合成を設定
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, object->handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//加算合成をなくす
}

void Movie::Set(std::string name)
{
	if (this == nullptr) throw("Movieのメモリが確保されていません");
	//名前が違うなら更新
	if (object->name != name) {
		this->object = MovieResource::Get(name);
	}
}

void Movie::Delete()
{
	MovieResource::DeleteMovieMem(this->object->name);
}
