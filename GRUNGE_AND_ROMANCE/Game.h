/*******************************************************************************
* タイトル:		ゲームヘッダー
* プログラム名:	Game.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include "Main.h"
#include "Struct.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ENEMY_WALK		(0.5f)								// エネミーの歩く速度
#define	ENEMY_RUN		(2.0f)								// エネミーの走る速度

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void AddDamageEnemy(ENEMY *enemy, int damage);		// エネミーにダメージを与える
void AddDamagePlayer(CHARA *player, int damage);	// プレイヤーにダメージを与える

// エネミーの攻撃													
void EnemyAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl);		// 攻撃する方向の判定＆攻撃のとりまとめ
void EnemyLeftAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl);	// 左向きの攻撃
void EnemyRightAttack(D3DXVECTOR3 Playerpos, ENEMY *Enemy, float scl);	// 右向きの攻撃


#endif
