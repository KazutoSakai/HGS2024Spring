//*********************************************
//
// ステンシルバッファ(stencil.h)
// Author : Junichi Uchiyama
//
//*********************************************

#ifndef _STENCIL_H_
#define _STENCIL_H_

/// <summary>
/// ステンシルバッファでの型抜き描画を管理
/// </summary>
class CStencil
{
public:
	
	//---------------------
	// enum

	// ステンシルバッファの型抜き方法を変える
	enum STENCIL_TYPE
	{
		NONE = -1,
		BASE,			// 型抜き元
		OVERLAP,		// 重ねるオブジェクト
		COLORPOLYGON,	// 色ポリゴン

		MAX
	};

	//---------------------
	// public Method
	static void Begine(STENCIL_TYPE type);
	static void End();
};

#endif