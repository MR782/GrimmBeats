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
	ClearGaugeFream* _fream;

	static std::vector<Book*> _books;
	static int _gaugeCnt;//�Q�[�W�̂��܂�(�Q�[�W)
	static int _gaugeBookCnt;//�Q�[�W�̂��܂�(�{)
public:
	ClearGauge();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	static void IncreaseGaugeCnt(int addval);
	static void DecreaseGaugeCnt(int decreaseval);
};