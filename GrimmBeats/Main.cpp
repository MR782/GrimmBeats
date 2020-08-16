//���������[�N�𒲂ׂ�
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#include<Windows.h>

#include"Time.h"
#include "./dxlib/DxLib.h"

// WinMain�֐�
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	#pragma region ConfigSet
	//���������[�N�m�F
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//log.txt���쐬���Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
	//�o�b�N�O���E���h�ł����s��Ԃɂ���
	SetAlwaysRunFlag(TRUE);
	//�E�B���h�E�^�C�g��
	SetMainWindowText("Grimm Beats");
	#pragma endregion

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) { return -1; };
	//-------------------------------------------------
	SetDrawScreen(DX_SCREEN_BACK);//����ʐݒ�

	//�G���[���������Ă���Ȃ瑦���ɏI��
	try {
		Time::Initialize();
		#pragma region �Q�[�����[�v
		//��ʍX�V�����b�Z�[�W����&��ʎE�Q
		while ((ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)) {
			#pragma region ���͊֌W�̍X�V

			#pragma endregion

			#pragma region �Q�[�������ԏ���
			Time::Update();
			#pragma endregion

			#pragma region �V�[���̍X�V�F�`�揈��

			#pragma endregion
		}
		#pragma endregion
	}
	#pragma region �G���[���̏���
	catch (const char* msg) {
		//�Ȃ���O��������ꂽ���m�点��
		MessageBox(NULL, msg, "ERROR", MB_OK);//WindowsAPI�@�\
	}
	#pragma endregion

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �Q�[���I��
}
