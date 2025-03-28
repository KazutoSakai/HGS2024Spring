//*********************************************
//
// 汎用処理(utility.h)
// Author : Junichi Uchiyama
//
//*********************************************

#include "main.h"

/// <summary>
/// 便利関数まとめ
/// </summary>
class CUtility
{
public:
	//---------------------
	// static Method
	static void GetScriptIntValue(char* str, int* outValue);
	static void GetScriptStringValue(char* str, char* outValue);
private:
	//---------------------
	// private Method
	CUtility() {};
	~CUtility() {};
};