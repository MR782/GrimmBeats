#pragma once
#include<string>
#include<memory>
#include<vector>

struct MovieObject {
	MovieObject();
	friend class MovieResource;
	std::string name;//���ʖ�
	std::string path;//�t�@�C���p�X
	bool loop;//���[�v�Đ����邩
	int handle;//�n���h��
private:
	bool exist;//�ǂݍ��ݍς݂����f
	std::vector<std::string> scopes;//�ǂݍ��ݎ��̖��O
	bool ExistScope(std::string);
};

class MovieResource {
	static std::vector<std::shared_ptr<MovieObject>> movie_obj;//���[�r�[�f�[�^���i�[����z��
	static void RegisterMovie(MovieObject&);//�I�u�W�F�N�g��o�^
public:
	static void Initialize();
	static void Finalize();
	static int Load(std::string scope);//�X�R�[�v�����������Ĉ�v������̂����[�h����
	static bool CheckPlay(std::string name);//���łɍĐ�����Ă��邩�m�F
	static void DeleteMovieMem(std::string name);//���������烀�[�r�[�f�[�^���폜����
	static std::shared_ptr<MovieObject> Get(std::string name);//���O����v������̂̃|�C���^��Ԃ�
};