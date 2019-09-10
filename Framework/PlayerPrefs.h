//=====================================
//
// PlayerPrefs.h
// �@�\:�f�[�^�ۑ��@�\
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERPREFS_H_
#define _PLAYERPREFS_H_

#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
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