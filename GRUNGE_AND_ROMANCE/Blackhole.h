//=============================================================================
//
// ブラックホールくん処理 [Blackhole.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _BLACKHOLE_H_
#define _BLACKHOLE_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BLACKHOLE_XFILE		"data/MODEL/black.x"		// 読み込むモデル名
#define BLACKHOLE_NUM			(10)						// エネミーの数
#define BLACKHOLE_HP_MAX		(50)
#define BLACKHOLE_DIRECTION		(0.0f)
#define BLACKHOLE_DIRECTION2	(160.0f)					// エネミーを反対向きに
#define BLACKHOLE_SCALE			(3.0f)
#define BLACKHOLE_XSCALE		(12.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBlackhole(int type);
void UninitBlackhole(void);
void UpdateBlackhole(void);
void DrawBlackhole(void);
ENEMY *GetBlackhole(int en);
void SetVertexBlackhole(void);

#endif
