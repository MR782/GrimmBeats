#include "ClearGauge.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"
#include <algorithm>
#include <functional>

void ClearGauge::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("ClearGauge");

	this->_fream = new ClearGaugeFream();
	this->_fream->Initialize();

	this->_books.push_back(new Book("Book(Blue)", this->_fream->GetDrawRect().w / 3, 1));
	this->_books.push_back(new Book("Book(Blue)", this->_fream->GetDrawRect().w / 3, 2));
	this->_books.push_back(new Book("Book(Blue)", this->_fream->GetDrawRect().w / 3, 3));
	this->_books.push_back(new Book("Book(Blue)", this->_fream->GetDrawRect().w / 3, 4));
	this->_books.push_back(new Book("Book(Red)", (int)(this->_fream->GetDrawRect().w / 3), 5));
	this->_books.push_back(new Book("Book(Red)", (int)(this->_fream->GetDrawRect().w / 3), 6));

	std::sort(this->_books.begin(), this->_books.end());
}

void ClearGauge::Finalize()
{
	this->_anim.reset();
	this->_fream->Finalize();
	
	for (auto itr = this->_books.begin(); itr != this->_books.end(); itr++) {
		delete (*itr);
	}
	this->_books.clear();
	delete this->_fream;
}

void ClearGauge::Update()
{
	//本の更新(カウントによって色付きにするか決める)
	for (auto itr = this->_books.begin(); itr != this->_books.end(); itr++) {
		std::string name = "Book(Null)";
		if ((*itr)->turnNo <= this->_gaugeBookCnt) {
			name = (*itr)->bookColorName;
		}
		(*itr)->anime->Set(name);
	}
}

void ClearGauge::Draw()
{
	//ゲージの矩形情報
	Rect draw = Rect(this->_fream->GetDrawRect().x, this->_fream->GetDrawRect().y + this->_fream->GetDrawRect().h - 1,
		this->_fream->GetDrawRect().w / 2, (this->_fream->GetDrawRect().h * -this->_gaugeCnt / 100));
	//描画
	this->_anim->ExtendAnimeDraw(draw);
	this->_fream->Draw();
	//本の描画
	for (auto itr = this->_books.begin(); itr != this->_books.end(); itr++) {
		Rect rect = Rect((this->_fream->GetDrawRect().x + this->_fream->GetDrawRect().w / 2) + (*itr)->graphSize / 3,
			this->_fream->GetDrawRect().y + ((*itr)->graphSize + ((*itr)->graphSize / 2)) * (*itr)->turnNo - 1,
			(*itr)->graphSize, (*itr)->graphSize);
		(*itr)->anime->ExtendAnimeDraw(rect);
	}
}

void ClearGauge::IncreaseGaugeCnt(int addval)
{
	//本が最大までいっていない
	if (this->_gaugeBookCnt < this->_books.size()) {
		//ゲージがMaxになったら
		if (this->_gaugeCnt + addval >= 100) {
			//本を1つ増やしてカウンタを初期化
			this->_gaugeBookCnt = min(this->_gaugeBookCnt++, (int)this->_books.size());
			this->_gaugeCnt = 0;
		}
		//Maxでないなら増加
		else this->_gaugeCnt = (this->_gaugeCnt + addval) % 100;
	}
	//本が最大まで行ったら
	else {
		//Maxでないなら増加
		this->_gaugeCnt = min(this->_gaugeCnt + addval, 100);
	}
}

void ClearGauge::DecreaseGaugeCnt(int decreaseval)
{
	//本が0までいっていない
	if (this->_gaugeBookCnt > 0) {
		//ゲージが0になったら
		if (this->_gaugeCnt - decreaseval <= 0) {
			//本を1つ減らしてカウンタをMaxにする
			this->_gaugeBookCnt = max(this->_gaugeBookCnt--, 0);
			this->_gaugeCnt = 100;
		}
		//0でないなら減少
		else this->_gaugeCnt = (this->_gaugeCnt - decreaseval) % 100;
	}
	//本が最大まで行ったら
	else {
		//Maxでないなら増加
		this->_gaugeCnt = max(this->_gaugeCnt - decreaseval, 0);
	}
}

ClearGauge::Book::Book(std::string bookName, int size, int turn)
{
	this->bookColorName = bookName;
	this->graphSize = size;
	this->turnNo = turn;
	this->anime = std::make_unique<Animation>();
}