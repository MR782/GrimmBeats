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
	//���̃I�u�W�F�N�g�̃X�R�[�v�̐������J��Ԃ�
	for (auto&& scope : scopes) {
		if (scope == scope_) {//�����ƃX�R�[�v�����v������̂���������
			check = true;//true�ɂ���
			break;
		}
	}
	return check;//���ׂ����ʂ�Ԃ�
}

//////////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<MovieObject>> MovieResource::movie_obj;

void MovieResource::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/movieData.json");
	//-------------------------------------------------------------
	for (auto& item : json["movie"].array_items()) {//�t�@�C�����̃f�[�^���J��Ԃ�
		std::shared_ptr<MovieObject> movie = std::make_shared<MovieObject>();
		movie->exist = false;//�܂��ǂݍ���ł��Ȃ�
		movie->name = item["name"].string_value();//���ʎq
		movie->loop = item["loop"].bool_value();//���[�v�̔��f
		movie->path = item["path"].string_value();//�t�@�C���̃p�X
		for (auto& scope : item["scope"].array_items()) {//�ǂݍ��ލۂ̎��ʎq
			movie->scopes.push_back(scope.string_value());
		}
		movie_obj.push_back(std::move(movie));//���L���̈ڍs
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
	//�܂��ǂݍ���ł��Ȃ��Ȃ�
	if (obj.exist == false) {
		//�n���h���Ƀ��[�r�[�f�[�^��ǂݍ���
		obj.handle = LoadGraph(obj.path.c_str());
		obj.exist = true;//�ǂݍ��ݍς�
	}
}


int MovieResource::Load(std::string scope)
{
	int num = 0;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->exist == false) {//�ǂݍ��܂�Ă��Ȃ��Ȃ�
			if ((*itr)->ExistScope(scope)) {
				RegisterMovie(*(*itr));//�o�^
				num++;
			}
		}
	}
	return num;//�ԍ���Ԃ�
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
	//�w�肵���I�u�W�F�N�g���������������
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			DeleteGraph((*itr)->handle);//�n���h���f�[�^���폜
			(*itr)->exist = false;
		}
	}
}

std::shared_ptr<MovieObject> MovieResource::Get(std::string name)
{
	std::shared_ptr<MovieObject> ret = nullptr;//����ۂ̏��
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->name == name) {//���̖��O������Ȃ�
			ret = (*itr);//���̃I�u�W�F�N�g��Ԃ�
		}
	}
	return ret;
}
