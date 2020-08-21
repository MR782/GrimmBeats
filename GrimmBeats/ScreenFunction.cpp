#include "ScreenFunction.h"
#include"ScreenHelperGraph.h"
#include"./dxlib/DxLib.h"
#include"ScreenSystem.h"
#include"Necessary.h"

#define FadeSpeed 5

int ScreenFunction::blendcnt;
int ScreenFunction::screen_graph;

void ScreenFunction::Initialize()
{
	//フェードアウト、イン用の画像をロード
	ScreenHelperGraph::black_graph = LoadGraph("./data/graph/screen/black_screen.png");
	ScreenHelperGraph::white_graph = LoadGraph("./data/graph/screen/white_screen.png");
	if (ScreenHelperGraph::black_graph == -1 || ScreenHelperGraph::white_graph == -1) {
		throw"ScreenHelperGraph is not found";
	}
	screen_graph = ScreenHelperGraph::black_graph;
	blendcnt = 0;//初期は透明にしておく
}

void ScreenFunction::Finalize()
{
	DeleteGraph(ScreenHelperGraph::black_graph);
	DeleteGraph(ScreenHelperGraph::white_graph);
}

void ScreenFunction::FeedOut()
{
	//ブレンドカウントを加算していく
	if (CheckBlendMax() == false) {//255より小さい値なら
		blendcnt += FadeSpeed;
	}
}

void ScreenFunction::FeedIn()
{
	//ブレンドカウントを減算していく
	if (CheckBlendMin() == false) {//0より大きい値なら
		blendcnt -= FadeSpeed;
	}
}

void ScreenFunction::Update()
{
	if (Necessary::GetFadeIOFlag()) {//フェードアウトの合図が来たら
		FeedOut();//フェードアウトを呼び出す
	}
	else {//フェードアウトの合図が来てないなら
		FeedIn();//フェードインを呼び出す
	}
}

void ScreenFunction::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendcnt);		//ブレンドモードをαに設定
	//始点（0,0）から終点(画面サイズ（X）,画面サイズ(Y)まで引数で受け取った画像ハンドルを描画)
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, screen_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
}

bool ScreenFunction::CheckBlendMax()
{
	return blendcnt >= 255;//255より大きいならtrue
}

bool ScreenFunction::CheckBlendMin()
{
	return blendcnt <= 0;//0より小さいならtrue
}
