#pragma once
#include"GameObject.h"
#include"ClearGaugeFream.h"

class ClearGauge : public GameObject {
	struct Book {
		std::string bookColorName;
		std::unique_ptr<Animation> anime;
		int graphSize;
		int turnNo;
		Book(std::string, int, int);

		bool operator < (const Book& right)const {
			return this->turnNo < right.turnNo;
		}
		bool operator > (const Book& right)const {
			return this->turnNo > right.turnNo;
		}
	};

	std::vector<Book*> _books;
	ClearGaugeFream* _fream;

	int _gaugeCnt;//ゲージのたまり具合(ゲージ)
	int _gaugeBookCnt;//ゲージのたまり具合(本)
public:
	ClearGauge();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	void IncreaseGaugeCnt(int addval);
	void DecreaseGaugeCnt(int decreaseval);
};