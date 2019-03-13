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
#include "Meshfield.h"
#include "Effect.h"
#include "Meshwall.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitPlayer(0);
	InitOnna(0);
	InitGauge(0);
	InitBlackhole(0);
	InitBabel(0);
	InitKumatyang(0);
	InitYakiYaki(0);
	InitEffect(true);

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
	UninitEffect();
	UninitMeshWall();

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
	UpdateMeshField();
	UpdateEffect();
	UpdateMeshWall();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	DrawMeshWall();
	DrawMeshField();
	DrawPlayer();
	DrawOnna();
	DrawGauge();
	DrawBlackhole();
	DrawBabel();
	DrawKumatyang();
	DrawYakiYaki();
	DrawEffect();

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

void EnemyAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl)		// 攻撃する方向の判定＆攻撃のとりまとめ
{
	// プレイヤーの位置とエネミーの位置を比較
	if(Enemy->AttackFlag == false)
	{
		// エネミーが右側にいる
		if (PlayerPos.x <= Enemy->pos.x)
		{
			Enemy->Direction = false;

		}
		else
		{
			Enemy->Direction = true;
		}
	}

	// エネミーのほうが右側にいる場合
	if (Enemy->Direction == false)
	{
		EnemyLeftAttack(PlayerPos, Enemy, scl);
	}
	// 左側にいる場合
	else
	{
		EnemyRightAttack(PlayerPos, Enemy,scl);
	}
}

void EnemyLeftAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl)
{

	// 攻撃フラグが立っていないとき
	if (Enemy->AttackFlag == false)
	{
		// 攻撃フラグが立つとき
		if ((PlayerPos.z <= (Enemy->pos.z + scl)) && (PlayerPos.z >= (Enemy->pos.z - scl)))
		{
			float LAttackRandom = 0;

			LAttackRandom=CreateRandomFloat(0.0f, 100.0f);

			if (LAttackRandom > 97.0f)
			{
				Enemy->AttackFlag = true;
			}
		}

		// 待機状態の動き（移動場所が決まっていないとき）
		if (Enemy->IdleFlag == true)
		{
			Enemy->Epos.z = CreateRandomFloat(-200.0f, 10.0f);
			Enemy->IdleFlag = false;
		}

		// 待機状態の動き（移動場所が決まっているとき）
		else if (Enemy->IdleFlag == false)
		{
			// 動く
			if (Enemy->Epos.z > Enemy->pos.z)
			{
				Enemy->pos.z += ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1)	// 小数点以下は無視
				{
					Enemy->IdleFlag = true;
				}
			}
			else if (Enemy->Epos.z < Enemy->pos.z)
			{
				Enemy->pos.z -= ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1) // 小数点以下は無視
				{
					Enemy->IdleFlag = true;
				}

			}
		}
	}
	// 攻撃フラグが立っているとき
	else if (Enemy->AttackFlag == true)
	{
		// 突進していく動き
		if (PlayerPos.x <= Enemy->pos.x)
		{
			Enemy->pos.x -= ENEMY_RUN;
		}

		// 突進終了でフラグを戻す
		if (PlayerPos.x > Enemy->pos.x)
		{
			Enemy->AttackFlag = false;
		}

	}

}


void EnemyRightAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy,float scl)	// 右向きの攻撃
{

	// 攻撃フラグが立っていないとき
	if (Enemy->AttackFlag == false)
	{
		// 攻撃フラグが立つとき
		if ((PlayerPos.z <= (Enemy->pos.z + scl)) && (PlayerPos.z >= (Enemy->pos.z - scl)))
		{
			float RAttackRandom = 0;

			RAttackRandom=CreateRandomFloat(0.0f, 100.0f);

			if (RAttackRandom > 97.0f)
			{
				Enemy->AttackFlag = true;
			}
		}

		// 待機状態の動き（移動場所が決まっていないとき）
		if (Enemy->IdleFlag == true)
		{
			Enemy->Epos.z = CreateRandomFloat(-200.0f, 10.0f);
			Enemy->IdleFlag = false;
		}

		// 待機状態の動き（移動場所が決まっているとき）
		else if (Enemy->IdleFlag == false)
		{
			// 動く
			if (Enemy->Epos.z > Enemy->pos.z)
			{
				Enemy->pos.z += ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1)	// 小数点以下は無視
				{
					Enemy->IdleFlag = true;
				}
			}
			else if (Enemy->Epos.z < Enemy->pos.z)
			{
				Enemy->pos.z -= ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1) // 小数点以下は無視
				{
					Enemy->IdleFlag = true;
				}

			}
		}
	}
	// 攻撃フラグが立っているとき
	else if (Enemy->AttackFlag == true)
	{
		// 突進していく動き
		if (PlayerPos.x > Enemy->pos.x)
		{
			Enemy->pos.x += ENEMY_RUN;
		}

		// 突進終了でフラグを戻す
		if (PlayerPos.x < Enemy->pos.x)
		{
			Enemy->AttackFlag = false;
		}

	}

}