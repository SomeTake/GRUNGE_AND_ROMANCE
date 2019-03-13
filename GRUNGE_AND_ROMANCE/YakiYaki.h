//=============================================================================
//
// やきやき処理 [YakiYaki.h]
// Author : HAL東京 GP11B341-01 80163 飯塚春輝
//
//=============================================================================
#ifndef _YAKIYAKI_H_
#define _YAKIYAKI_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	YAKIYAKI_XFILE		"data/MODEL/YakiYaki.x"	// 読み込むモデル名
#define YAKIYAKI_NUM		(1)						// バーベルの数
#define YAKIYAKI_DIRECTION	(200.0f)
#define YAKIYAKI_SCALE		(3.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitYakiYaki(int type);
void UninitYakiYaki(void);
void UpdateYakiYaki(void);
void DrawYakiYaki(void);
ITEM *GetYakiYaki(int in);
int SetYakiYaki(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionYakiYaki(int IdxBabel, D3DXVECTOR3 pos);
void SetRotationYakiYaki(int IdxBabel, D3DXVECTOR3 rot);
void SetThrowedYakiYaki(int Idx);

#endif
