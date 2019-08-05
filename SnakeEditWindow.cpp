//=====================================
//
//�X�l�[�N�G�f�B�b�g�E�B���h�E����[SnakeEditWindow.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnakeEditWindow.h"
#include "debugWindow.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�`�揈��
***************************************/
bool SnakeEditWindow::Draw()
{
	bool selected = false;

	string destLabel = string("destList");

	//destList�ƕ\��
	DebugText(destLabel.c_str());

	//�f�[�^�ǉ��{�^��
	if (DebugButton("Add")) destList.push_back(0);
	
	//�f�[�^�폜�{�^��
	DebugSameLine();
	if (DebugButton("Remove") && destList.size() > 0)
	{
		destList.pop_back();
	}

	//�e�f�[�^�����
	for (UINT i = 0; i < destList.size(); i++)
	{
		string label = string("##") + destLabel + to_string(i);
		selected |= DebugInputInt(label.c_str(), &destList[i]);

		destList[i] = Clamp(0, 4, destList[i]);
	}

	return selected;
}

/**************************************
�V���A���C�Y����
***************************************/
picojson::value SnakeEditWindow::Serialize()
{
	picojson::array dataList;

	for (auto& dest : destList)
	{
		picojson::object data;
		data.emplace(make_pair("dest", picojson::value((double)dest)));
		dataList.push_back(picojson::value(data));
	}

	picojson::object returnVal;
	returnVal.emplace(make_pair("destList", picojson::value(dataList)));
	return picojson::value(returnVal);
}

/**************************************
�f�V���A���C�Y����
***************************************/
void SnakeEditWindow::Deserialize(picojson::object data)
{
	picojson::array dataList = data["destList"].get<picojson::array>();

	destList.clear();
	destList.resize(dataList.size());

	for (UINT i = 0; i < destList.size(); i++)
	{
		destList[i] = static_cast<int>(dataList[i].get<picojson::object>()["dest"].get<double>());
	}
}
