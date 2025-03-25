//*********************************************
//
// �ėp����(utility.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

#include "utility.h"

/// <summary>
/// ������擪���猟�����Đ������擾
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
/// ������擪���猟������ = ���̕�������擾
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
			// �X�y�[�X���΂�
			i += 2;
			trimIndex = i;
			break;
		}
		i++;
	}

	// �p�X�̒������擾
	while (str[i] != '\0')
	{
		if (isspace(str[i]) != 0)
			break;

		pathIndex++;
		i++;
	}

	// �R�s�[
	strncpy(outValue, &str[trimIndex], pathIndex);
	outValue[pathIndex] = '\0';
}