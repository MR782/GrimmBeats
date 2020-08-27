//メモリリークを調べる
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

// WinMain関数
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	#pragma region ConfigSet
	#pragma region ScreenSizeSet
	//画面サイズ設定
	{
		int id = MessageBox(NULL, TEXT("フルスクリーンモードで起動しますか？"),
			TEXT("エラー発生時はダウンロードページのアドレスへご連絡ください"), MB_YESNO | MB_ICONQUESTION);
		switch (id)
		{
		case IDYES:
			GetDefaultState(&ScreenData::width, &ScreenData::height, NULL);//フルスク設定
			break;
		case IDNO:
			ScreenData::width = 1048;
			ScreenData::height = 600;
			break;
		}
		SetGraphMode(ScreenData::width, ScreenData::height, 32);//ウィンドウのサイズを決める
		SetWindowSize(ScreenData::width, ScreenData::height);
		ChangeWindowMode(TRUE);// ウィンドウモード変更
	}
	#pragma endregion
	//メモリリーク確認
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//log.txtを作成しない
	SetOutApplicationLogValidFlag(FALSE);
	//バックグラウンドでも実行状態にする
	SetAlwaysRunFlag(TRUE);
	//ウィンドウタイトル
	SetMainWindowText("Grimm Beats");
	#pragma endregion

	sceneManager = new SceneManager();
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) { return -1; };
	//-------------------------------------------------
	SetDrawScreen(DX_SCREEN_BACK);//裏画面設定

	//エラーが発生しているなら即座に終了
	try {
		#pragma region リソースの初期化
		GraphicResource::Initialize();
		Audio::Initialize();
		MovieResource::Initialize();
		MusicDataManager::Initialize();

		GraphicResource::Load("all");
		#pragma endregion

		sceneManager->Initialize();

		Time::Initialize();
		KeyBoard::Initialize();
		#pragma region ゲームループ
		//画面更新＆メッセージ処理&画面殺害
		while ((ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)) {
			#pragma region 入力関係の更新
			KeyBoard::Update();
			if (KeyBoard::KeyDown(KEY_INPUT_ESCAPE))break;
			#pragma endregion

			#pragma region ゲーム内時間処理
			Time::Update();
			#pragma endregion

			#pragma region シーンの更新：描画処理
			sceneManager->Update();
			sceneManager->Draw();
			#pragma endregion
		}
		#pragma endregion
		sceneManager->Finalize();
	}
	#pragma region エラー時の処理
	catch (const char* msg) {
		//なぜ例外が投げられたか知らせる
		MessageBox(NULL, msg, "ERROR", MB_OK);//WindowsAPI機能
	}
	#pragma endregion

	#pragma region 終了処理
	KeyBoard::Finalize();
	Audio::Finalize();
	GraphicResource::Finalize();
	MovieResource::Finalize();
	MusicDataManager::Finalize();
	#pragma endregion
	delete sceneManager;

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ゲーム終了
}
