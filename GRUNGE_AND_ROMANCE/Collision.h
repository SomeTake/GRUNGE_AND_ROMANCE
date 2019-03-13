//=============================================================================
//
// 当たり判定処理 [Collision.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Main.h"
#include "Struct.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BALL_XFILE		"data/MODEL/Ball.x"					// 読み込むモデル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCollision(int type, COLLISION *Collision, D3DXMATRIX Matrix, float Radius);	// 初期化、BALL構造体、行列、半径
void UninitCollision(COLLISION *Collision);
void UpdateCollision(COLLISION *Collision, D3DXMATRIX Matrix);
void DrawCollision(COLLISION *Collision);

bool HitSphere(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange);
bool HitCheckPToE(CHARA *Player, ENEMY *Enemy);		// プレイヤーの攻撃とエネミーの当たり判定
bool HitSphereToCircle(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange);
bool HitCheckPToI(CHARA *Player, ITEM *Item);		// プレイヤーとアイテムの当たり判定


#endif
