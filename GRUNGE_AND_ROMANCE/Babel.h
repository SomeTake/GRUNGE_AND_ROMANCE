//=============================================================================
//
// バーベル処理 [Babel.h]
// Author : HAL東京 GP11B341-01 80163 飯塚春輝
//
//=============================================================================
#ifndef _BABEL_H_
#define _BABEL_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BABEL_XFILE		"data/MODEL/babel.x"		// 読み込むモデル名
#define BABEL_NUM		(1)						// バーベルの数
#define BABEL_DIRECTION	(200.0f)
#define BABEL_SCALE		(3.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBabel(int type);
void UninitBabel(void);
void UpdateBabel(void);
void DrawBabel(void);
ITEM *GetBabel(int in);
int SetBabel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionBabel(int IdxBabel, D3DXVECTOR3 pos);
void SetRotationBabel(int IdxBabel, D3DXVECTOR3 rot);
#endif
