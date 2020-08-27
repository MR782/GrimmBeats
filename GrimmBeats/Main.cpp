//���������[�N�𒲂ׂ�
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#include<Windows.h>
#include"SceneManager.h"
#include"KeyBoard.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"MovieResource.h"
#include"MusicDataManager.h"
#include"Time.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"./dxlib/DxLib.h"

SceneManager* sceneManager;

#include <crtdbg.h>

// WinMain�֐�
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	#pragma region ConfigSet
	#pragma region ScreenSizeSet
	//��ʃT�C�Y�ݒ�
	{
		int id = MessageBox(NULL, TEXT("�t���X�N���[�����[�h�ŋN�����܂����H"),
			TEXT("�G���[�������̓_�E�����[�h�y�[�W�̃A�h���X�ւ��A����������"), MB_YESNO | MB_ICONQUESTION);
		switch (id)
		{
		case IDYES:
			GetDefaultState(&ScreenData::width, &ScreenData::height, NULL);//�t���X�N�ݒ�
			break;
		case IDNO:
			ScreenData::width = 1048;
			ScreenData::height = 600;
			break;
		}
		SetGraphMode(ScreenData::width, ScreenData::height, 32);//�E�B���h�E�̃T�C�Y�����߂�
		SetWindowSize(ScreenData::width, ScreenData::height);
		ChangeWindowMode(TRUE);// �E�B���h�E���[�h�ύX
	}
	#pragma endregion
	//���������[�N�m�F
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//log.txt���쐬���Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
	//�o�b�N�O���E���h�ł����s��Ԃɂ���
	SetAlwaysRunFlag(TRUE);
	//�E�B���h�E�^�C�g��
	SetMainWindowText("Grimm Beats");
	#pragma endregion

	sceneManager = new SceneManager();
	// �c�w���C�u��������������
	if (DxLib_Init() == -1) { return -1; };
	//-------------------------------------------------
	SetDrawScreen(DX_SCREEN_BACK);//����ʐݒ�

	//�G���[���������Ă���Ȃ瑦���ɏI��
	try {
		#pragma region ���\�[�X�̏�����
		GraphicResource::Initialize();
		Audio::Initialize();
		MovieResource::Initialize();
		MusicDataManager::Initialize();

		GraphicResource::Load("all");
		#pragma endregion

		sceneManager->Initialize();

		Time::Initialize();
		KeyBoard::Initialize();
		#pragma region �Q�[�����[�v
		//��ʍX�V�����b�Z�[�W����&��ʎE�Q
		while ((ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)) {
			#pragma region ���͊֌W�̍X�V
			KeyBoard::Update();
			if (KeyBoard::KeyDown(KEY_INPUT_ESCAPE))break;
			#pragma endregion

			#pragma region �Q�[�������ԏ���
			Time::Update();
			#pragma endregion

			#pragma region �V�[���̍X�V�F�`�揈��
			sceneManager->Update();
			sceneManager->Draw();
			#pragma endregion
		}
		#pragma endregion
		sceneManager->Finalize();
	}
	#pragma region �G���[���̏���
	catch (const char* msg) {
		//�Ȃ���O��������ꂽ���m�点��
		MessageBox(NULL, msg, "ERROR", MB_OK);//WindowsAPI�@�\
	}
	#pragma endregion

	#pragma region �I������
	KeyBoard::Finalize();
	Audio::Finalize();
	GraphicResource::Finalize();
	MovieResource::Finalize();
	MusicDataManager::Finalize();
	#pragma endregion
	delete sceneManager;

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �Q�[���I��
}
