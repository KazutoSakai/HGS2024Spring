//*********************************************
//
// �ėp����(utility.h)
// Author : Junichi Uchiyama
//
//*********************************************

#include "main.h"

/// <summary>
/// �֗��֐��܂Ƃ�
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