#include "ClearGauge.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"
#include <algorithm>
#include <functional>

int ClearGauge::_gaugeCnt;
int ClearGauge::_gaugeBookCnt;
std::vector<ClearGauge::Book*> ClearGauge::_books;

ClearGauge::ClearGauge()
{
	_gaugeBookCnt = 0;
	_gaugeCnt = 0;
	this->_fream = nullptr;
	_books.clear();
}

void ClearGauge::Initialize()
{
	this->name = "ClearGauge";
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("ClearGauge");

	this->_fream = new ClearGaugeFream();
	this->_fream->Initialize();

	_books.push_back(new Book("Book(Blue)", _fream->GetDrawRect().w / 3, 1));
	_books.push_back(new Book("Book(Blue)", _fream->GetDrawRect().w / 3, 2));
	_books.push_back(new Book("Book(Blue)", _fream->GetDrawRect().w / 3, 3));
	_books.push_back(new Book("Book(Blue)", _fream->GetDrawRect().w / 3, 4));
	_books.push_back(new Book("Book(Red)", (int)(_fream->GetDrawRect().w / 3), 5));
	_books.push_back(new Book("Book(Red)", (int)(_fream->GetDrawRect().w / 3), 6));

	std::sort(_books.begin(), _books.end());
}

void ClearGauge::Finalize()
{
	this->_anim.reset();
	this->_fream->Finalize();
	
	for (auto itr = _books.begin(); itr != _books.end(); itr++) {
		delete (*itr);
	}
	_books.clear();
	delete this->_fream;
}

void ClearGauge::Update()
{
	//�{�̍X�V(�J�E���g�ɂ���ĐF�t���ɂ��邩���߂�)
	for (auto itr = _books.begin(); itr != _books.end(); itr++) {
		std::string name = "Book(Null)";
		if ((*itr)->turnNo <= _gaugeBookCnt) {
			name = (*itr)->bookColorName;
		}
		(*itr)->anime->Set(name);
	}
}

void ClearGauge::Draw()
{
	//�Q�[�W�̋�`���
	Rect draw = Rect(this->_fream->GetDrawRect().x, this->_fream->GetDrawRect().y + this->_fream->GetDrawRect().h - 1,
		this->_fream->GetDrawRect().w / 2, (this->_fream->GetDrawRect().h * -_gaugeCnt / 100));
	//�`��
	this->_anim->ExtendAnimeDraw(draw);
	this->_fream->Draw();
	//�{�̕`��
	for (auto itr = _books.begin(); itr != _books.end(); itr++) {
		Rect rect = Rect((this->_fream->GetDrawRect().x + this->_fream->GetDrawRect().w / 2) + (*itr)->graphSize / 3,
			this->_fream->GetDrawRect().y + ((*itr)->graphSize + ((*itr)->graphSize / 2)) * (*itr)->turnNo - 1,
			(*itr)->graphSize, (*itr)->graphSize);
		(*itr)->anime->ExtendAnimeDraw(rect);
	}
}

void ClearGauge::IncreaseGaugeCnt(int addval)
{
	//�{���ő�܂ł����Ă��Ȃ�
	if (_gaugeBookCnt < _books.size()) {
		//�Q�[�W��Max�ɂȂ�����
		if (_gaugeCnt + addval >= 100) {
			//�{��1���₵�ăJ�E���^��������
			_gaugeBookCnt = min(_gaugeBookCnt++, (int)_books.size());
			_gaugeCnt = 0;
		}
		//Max�łȂ��Ȃ瑝��
		else _gaugeCnt = (_gaugeCnt + addval) % 100;
	}
	//�{���ő�܂ōs������
	else {
		//Max�łȂ��Ȃ瑝��
		_gaugeCnt = min(_gaugeCnt + addval, 100);
	}
}

void ClearGauge::DecreaseGaugeCnt(int decreaseval)
{
	//�{��0�܂ł����Ă��Ȃ�
	if (_gaugeBookCnt > 0) {
		//�Q�[�W��0�ɂȂ�����
		if (_gaugeCnt - decreaseval <= 0) {
			//�{��1���炵�ăJ�E���^��Max�ɂ���
			_gaugeBookCnt = max(_gaugeBookCnt--, 0);
			_gaugeCnt = 100;
		}
		//0�łȂ��Ȃ猸��
		else _gaugeCnt = (_gaugeCnt - decreaseval) % 100;
	}
	//�{���ő�܂ōs������
	else {
		//Max�łȂ��Ȃ瑝��
		_gaugeCnt = max(_gaugeCnt - decreaseval, 0);
	}
}

ClearGauge::Book::Book(std::string bookName, int size, int turn)
{
	this->bookColorName = bookName;
	this->graphSize = size;
	this->turnNo = turn;
	this->anime = std::make_unique<Animation>();
}