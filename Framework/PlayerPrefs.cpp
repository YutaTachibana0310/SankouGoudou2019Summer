//=====================================
//
//データ保存機能処理[PlayerPrefs.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerPrefs.h"
#include "../picojson/picojson.h"
#include <unordered_map>
#include <fstream>

/**************************************
グローバル変数
***************************************/
const char* PlayerPrefs::FileName = "data/data.bin";

/**************************************
bool取得処理
***************************************/
bool PlayerPrefs::GetBool(const std::string & key)
{
	std::ifstream ifs;
	ifs.open(FileName, std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	return val.get<picojson::object>()[key].get<bool>();
}

/**************************************
bool保存処理
***************************************/
void PlayerPrefs::SaveBool(const std::string & key, bool value)
{
	std::ifstream ifs;
	ifs.open(FileName, std::ios::binary);

	if (ifs.is_open())
	{
		picojson::value val;
		ifs >> val;
		ifs.close();

		picojson::object obj = val.get<picojson::object>();
		val.get<picojson::object>()[key] = picojson::value(value);

		std::string serializeData = val.serialize();
		std::ofstream ofs;
		ofs.open(FileName, std::ios::out);
		ofs << serializeData << std::endl;
		ofs.close();
	}
	else
	{
		picojson::object data;
		data.emplace(key, picojson::value(value));

		std::string serializeData = picojson::value(data).serialize();
		std::ofstream ofs;
		ofs.open(FileName, std::ios::out);
		ofs << serializeData << std::endl;
		ofs.close();
	}
}
