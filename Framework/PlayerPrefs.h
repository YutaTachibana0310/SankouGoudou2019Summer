//=====================================
//
// PlayerPrefs.h
// 機能:データ保存機能
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERPREFS_H_
#define _PLAYERPREFS_H_

#include <string>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class PlayerPrefs
{
public:
	static bool GetBool(const std::string& key);
	static void SaveBool(const std::string& key, bool value);
private:
	PlayerPrefs();
	
	static const char* FileName;
};

#endif