#include "Movie.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

Movie::Movie()
{
	this->object = std::make_shared<MovieObject>();
}

void Movie::Draw()
{
	//���[�r�[���Đ�����Ă��Ȃ��Ȃ�
	if (MovieResource::CheckPlay(object->name) == false) {
		SeekMovieToGraph(object->handle, 0);
		if (object->loop == true) {
			PlayMovieToGraph(object->handle);//�Đ�
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//���Z������ݒ�
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, object->handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���Z�������Ȃ���
}

void Movie::Set(std::string name)
{
	if (this == nullptr) throw("Movie�̃��������m�ۂ���Ă��܂���");
	//���O���Ⴄ�Ȃ�X�V
	if (object->name != name) {
		this->object = MovieResource::Get(name);
	}
}

void Movie::Delete()
{
	MovieResource::DeleteMovieMem(this->object->name);
}
