//*********************************************
//
// ”Ä—pˆ—(utility.h)
// Author : Junichi Uchiyama
//
//*********************************************

#include "main.h"

/// <summary>
/// •Ö—˜ŠÖ”‚Ü‚Æ‚ß
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