/*******************************************************************************
* �^�C�g��:		�Q�[���v���O����
* �v���O������:	Game.cpp
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
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
//#include "Meshwall.h"
#include "Meshfield.h"
#include "Effect.h"
#include "Input.h"
#include "Sound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Game_Index = GAME_TYPE_STAGE_ONNA;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);
		InitPlayer(0);
		InitOnna(0);
		InitGauge(0);
		InitBabel(0);
		InitKumatyang(0);
		InitYakiYaki(0);
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
// �I������
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
		break;
	default:
		break;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		UpdateMeshField();
		//UpdateMeshWall();
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
		//UpdateMeshWall();
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
		//UpdateMeshWall();
		UpdatePlayer();
		UpdateGauge();
		UpdateBabel();
		UpdateKumatyang();
		UpdateYakiYaki();
		UpdateEffect();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			Stop_Sound(SOUND_TYPE_BGM);
			Play_Sound(SOUND_TYPE_ENDING, SOUND_PLAY_TYPE_LOOP);
			SetStage(STAGE_ENDING);
		}

		break;
	default:
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	switch (Game_Index)
	{
	case GAME_TYPE_STAGE_ONNA:
		DrawMeshField();
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
		DrawPlayer();
		DrawGauge();
		DrawBabel();
		DrawKumatyang();
		DrawYakiYaki();
		DrawEffect();
		break;
	default:
		break;
	}

}

//=============================================================================
// �G�l�~�[�Ƀ_���[�W��^����
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
// �v���C���[�Ƀ_���[�W��^����
//=============================================================================
void AddDamagePlayer(CHARA *player, int damage)
{
	player->HPzan -= damage;

	if (player->HPzan < 0)
	{
		player->HPzan = 0;
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