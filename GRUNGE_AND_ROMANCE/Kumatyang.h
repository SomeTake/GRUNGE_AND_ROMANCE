//=============================================================================
//
// くまちゃん処理 [Kumatyang.h]
// Author : HAL東京 GP11B341-01 80163 飯塚春輝
//
//=============================================================================
#ifndef _KUMATYANG_H_
#define _KUMATYANG_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	KUMATYANG_XFILE		"data/MODEL/kumazyang.x"	// 読み込むモデル名
#define KUMATYANG_NUM		(1)						// バーベルの数
#define KUMATYANG_DIRECTION	(200.0f)
#define KUMATYANG_SCALE		(3.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKumatyang(int type);
void UninitKumatyang(void);
void UpdateKumatyang(void);
void DrawKumatyang(void);
ITEM *GetKumatyang(int in);
int SetKumatyang(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionKumatyang(int IdxIdxKumatyang, D3DXVECTOR3 pos);
void SetRotationKumatyang(int IdxIdxKumatyang, D3DXVECTOR3 rot);
void SetThrowedKumatyang(int Idx);

#endif
