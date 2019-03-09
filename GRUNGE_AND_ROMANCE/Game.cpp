/*******************************************************************************
* タイトル:		ゲームプログラム
* プログラム名:	Game.cpp
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#include "Game.h"
#include "Player.h"
#include "Onna.h"
#include "Gauge.h"
#include "meshfield.h"
#include "Blackhole.h"
#include "Babel.h"
#include "Kumatyang.h"
#include "YakiYaki.h"
<<<<<<< HEAD:GRANGE_AND_ROMANCE/Game.cpp
<<<<<<< HEAD
#include "Meshwall.h"
=======
#include "Meshfield.h"
>>>>>>> b96be5230b4eadb2b0e522d1e41ab817c456e042:GRUNGE_AND_ROMANCE/Game.cpp
#include "Effect.h"
=======
>>>>>>> parent of e81f7cc... Effect

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
	InitPlayer(0);
	InitOnna(0);
	InitGauge(0);
	InitBlackhole(0);
	InitBabel(0);
	InitKumatyang(0);
	InitYakiYaki(0);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitMeshField();
	UninitPlayer();
	UninitOnna();
	UninitGauge();
	UninitBlackhole();
	UninitBabel();
	UninitKumatyang();
	UninitYakiYaki();
	UninitMeshField();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	UpdateMeshField();
	UpdatePlayer();
	UpdateOnna();
	UpdateGauge();
	UpdateBlackhole();
	UpdateBabel();
	UpdateKumatyang();
	UpdateYakiYaki();
<<<<<<< HEAD:GRANGE_AND_ROMANCE/Game.cpp
<<<<<<< HEAD
	UpdateMeshWall();
=======
	UpdateMeshField();
>>>>>>> b96be5230b4eadb2b0e522d1e41ab817c456e042:GRUNGE_AND_ROMANCE/Game.cpp
	UpdateEffect();
=======
>>>>>>> parent of e81f7cc... Effect

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	DrawMeshField();
	DrawPlayer();
	DrawOnna();
	DrawGauge();
	DrawBlackhole();
	DrawBabel();
	DrawKumatyang();
	DrawYakiYaki();
<<<<<<< HEAD
	DrawEffect();
=======
>>>>>>> parent of e81f7cc... Effect

}

//=============================================================================
// エネミーにダメージを与える
//=============================================================================
void AddDamageEnemy(ENEMY *enemy, int damage)
{
	enemy->HPzan -= damage;

	if (enemy->HPzan < 0)
	{
		enemy->HPzan = 0;
	}
}

//=============================================================================
// プレイヤーにダメージを与える
//=============================================================================
void AddDamagePlayer(CHARA *player, int damage)
{
	player->HPzan -= damage;

	if (player->HPzan < 0)
	{
		player->HPzan = 0;
	}

}