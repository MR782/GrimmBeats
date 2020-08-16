//メモリリークを調べる
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#include<Windows.h>

#include"Time.h"
#include "./dxlib/DxLib.h"

// WinMain関数
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	#pragma region ConfigSet
	//メモリリーク確認
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//log.txtを作成しない
	SetOutApplicationLogValidFlag(FALSE);
	//バックグラウンドでも実行状態にする
	SetAlwaysRunFlag(TRUE);
	//ウィンドウタイトル
	SetMainWindowText("Grimm Beats");
	#pragma endregion

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) { return -1; };
	//-------------------------------------------------
	SetDrawScreen(DX_SCREEN_BACK);//裏画面設定

	//エラーが発生しているなら即座に終了
	try {
		Time::Initialize();
		#pragma region ゲームループ
		//画面更新＆メッセージ処理&画面殺害
		while ((ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)) {
			#pragma region 入力関係の更新

			#pragma endregion

			#pragma region ゲーム内時間処理
			Time::Update();
			#pragma endregion

			#pragma region シーンの更新：描画処理

			#pragma endregion
		}
		#pragma endregion
	}
	#pragma region エラー時の処理
	catch (const char* msg) {
		//なぜ例外が投げられたか知らせる
		MessageBox(NULL, msg, "ERROR", MB_OK);//WindowsAPI機能
	}
	#pragma endregion

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ゲーム終了
}
