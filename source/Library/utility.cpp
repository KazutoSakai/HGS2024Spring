//*********************************************
//
// 汎用処理(utility.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "utility.h"

/// <summary>
/// 文字列先頭から検索して整数を取得
/// </summary>
/// <param name="str"></param>
/// <param name="outValue"></param>
void CUtility::GetScriptIntValue(char* str, int* outValue)
{
	int num = -1;
	int i = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]) != 0)
		{
			num = atoi(&str[i]);

			if (str[i - 1] == '-')
			{
				num *= -1;
			}

			break;
		}
		i++;
	}

	*outValue = num;
}

/// <summary>
/// 文字列先頭から検索して = 後ろの文字列を取得
/// </summary>
/// <param name="str"></param>
/// <param name="outValue"></param>
void CUtility::GetScriptStringValue(char* str, char* outValue)
{
	int i = 0;
	int trimIndex = 0;
	int pathIndex = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '=') {
			// スペースを飛ばす
			i += 2;
			trimIndex = i;
			break;
		}
		i++;
	}

	// パスの長さを取得
	while (str[i] != '\0')
	{
		if (isspace(str[i]) != 0)
			break;

		pathIndex++;
		i++;
	}

	// コピー
	strncpy(outValue, &str[trimIndex], pathIndex);
	outValue[pathIndex] = '\0';
}