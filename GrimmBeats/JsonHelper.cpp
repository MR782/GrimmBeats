#include "JsonHelper.h"
#include<fstream>

json11::Json JsonHelper::JsonInitialize(std::string filepath)
{
	std::ifstream jsonfile(filepath);//�g�p�t�@�C���ݒ�
	if (jsonfile.fail()) throw("jsonFile is not found.");//��O����
	//Json���g�p���鏀��------------------------------------------
	std::istreambuf_iterator<char> it(jsonfile);
	std::istreambuf_iterator<char> last;
	std::string json_str(it, last);	//string�`����json
	std::string err;
	//�t�@�C�������
	jsonfile.close();
	return json11::Json::parse(json_str, err);//Json�Ŏg����悤�ɂ���
}
