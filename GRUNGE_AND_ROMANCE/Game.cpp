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
#include "Input.h"
#include "Sound.h"
#include "Boss.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Game_Index = GAME_TYPE_STAGE_ONNA;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{

	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
		InitPlayer(1);
		InitOnna(1);
		InitGauge(1);
		InitBabel(1);
		InitKumatyang(1);
		InitYakiYaki(1);
		break;
	case GAME_TYPE_STAGE_BLACK_HOLE:
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
		InitBlackhole(0);
		break;
	case GAME_TYPE_STAGE_NEXT:
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
		break;
	default:
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		UninitMeshField();
		UninitOnna();
		break;
	case GAME_TYPE_STAGE_BLACK_HOLE:
		UninitMeshField();
		UninitBlackhole();
		break;
	case GAME_TYPE_STAGE_NEXT:
		UninitMeshField();
		UninitPlayer();
		UninitGauge();
		UninitBabel();
		UninitKumatyang();
		UninitYakiYaki();
		UninitEffect();
		UninitBoss();
		break;
	default:
		break;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		UpdateMeshField();
		UpdateMeshWall();
		UpdatePlayer();
		UpdateOnna();
		UpdateGauge();
		UpdateBabel();
		UpdateKumatyang();
		UpdateYakiYaki();
		UpdateEffect();
		break;
	case GAME_TYPE_STAGE_BLACK_HOLE:
		UpdateMeshField();
		UpdateMeshWall();
		UpdatePlayer();
		UpdateBlackhole();
		UpdateGauge();
		UpdateBabel();
		UpdateKumatyang();
		UpdateYakiYaki();
		UpdateEffect();
		break;
	case GAME_TYPE_STAGE_NEXT:
		UpdateMeshField();
		UpdateMeshWall();
		UpdatePlayer();
		UpdateGauge();
		UpdateBabel();
		UpdateKumatyang();
		UpdateYakiYaki();
		UpdateEffect();
		UpdateBoss();

		//if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_C) || IsButtonTriggered(1, BUTTON_C))
		//{// Enter押したら、ステージを切り替える
		//	Stop_Sound(SOUND_TYPE_BGM);
		//	Play_Sound(SOUND_TYPE_ENDING, SOUND_PLAY_TYPE_LOOP);
		//	SetStage(STAGE_ENDING);
		//	ReInit();
		//}

		break;
	default:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		DrawMeshField();
		DrawMeshWall();
		DrawPlayer();
		DrawOnna();
		DrawGauge();
		DrawBabel();
		DrawKumatyang();
		DrawYakiYaki();
		DrawEffect();
		break;
	case GAME_TYPE_STAGE_BLACK_HOLE:
		DrawMeshField();
		DrawMeshWall();
		DrawPlayer();
		DrawGauge();
		DrawBlackhole();
		DrawBabel();
		DrawKumatyang();
		DrawYakiYaki();
		DrawEffect();
		break;
	case GAME_TYPE_STAGE_NEXT:
		DrawMeshField();
		DrawMeshWall();
		DrawPlayer();
		DrawGauge();
		DrawBabel();
		DrawKumatyang();
		DrawYakiYaki();
		DrawEffect();
		DrawBoss();
		break;
	default:
		break;
	}

}

void Set_Game_Index(int Set_Index)
{
	if ((Set_Index < GAME_TYPE_STAGE_ONNA) || (Set_Index > (GAME_TYPE_MAX - 1)))
	{
		return;
	}

	Game_Index = Set_Index;

	return;
}

int Get_Game_Index(void)
{
	return Game_Index;
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