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
	//�{�̍X�V(�J�E���g�ɂ���ĐF�t���ɂ��邩���߂�)
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
	//�Q�[�W�̋�`���
	Rect draw = Rect(this->_fream->GetDrawRect().x, this->_fream->GetDrawRect().y + this->_fream->GetDrawRect().h - 1,
		this->_fream->GetDrawRect().w / 2, (this->_fream->GetDrawRect().h * -this->_gaugeCnt / 100));
	//�`��
	this->_anim->ExtendAnimeDraw(draw);
	this->_fream->Draw();
	//�{�̕`��
	for (auto itr = this->_books.begin(); itr != this->_books.end(); itr++) {
		Rect rect = Rect((this->_fream->GetDrawRect().x + this->_fream->GetDrawRect().w / 2) + (*itr)->graphSize / 3,
			this->_fream->GetDrawRect().y + ((*itr)->graphSize + ((*itr)->graphSize / 2)) * (*itr)->turnNo - 1,
			(*itr)->graphSize, (*itr)->graphSize);
		(*itr)->anime->ExtendAnimeDraw(rect);
	}
}

void ClearGauge::IncreaseGaugeCnt(int addval)
{
	//�{���ő�܂ł����Ă��Ȃ�
	if (this->_gaugeBookCnt < this->_books.size()) {
		//�Q�[�W��Max�ɂȂ�����
		if (this->_gaugeCnt + addval >= 100) {
			//�{��1���₵�ăJ�E���^��������
			this->_gaugeBookCnt = min(this->_gaugeBookCnt++, (int)this->_books.size());
			this->_gaugeCnt = 0;
		}
		//Max�łȂ��Ȃ瑝��
		else this->_gaugeCnt = (this->_gaugeCnt + addval) % 100;
	}
	//�{���ő�܂ōs������
	else {
		//Max�łȂ��Ȃ瑝��
		this->_gaugeCnt = min(this->_gaugeCnt + addval, 100);
	}
}

void ClearGauge::DecreaseGaugeCnt(int decreaseval)
{
	//�{��0�܂ł����Ă��Ȃ�
	if (this->_gaugeBookCnt > 0) {
		//�Q�[�W��0�ɂȂ�����
		if (this->_gaugeCnt - decreaseval <= 0) {
			//�{��1���炵�ăJ�E���^��Max�ɂ���
			this->_gaugeBookCnt = max(this->_gaugeBookCnt--, 0);
			this->_gaugeCnt = 100;
		}
		//0�łȂ��Ȃ猸��
		else this->_gaugeCnt = (this->_gaugeCnt - decreaseval) % 100;
	}
	//�{���ő�܂ōs������
	else {
		//Max�łȂ��Ȃ瑝��
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