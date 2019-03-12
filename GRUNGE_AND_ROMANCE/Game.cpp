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
#include "Meshfield.h"
#include "Effect.h"
#include "Meshwall.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
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
// �I������
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
// �X�V����
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
// �`�揈��
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

void EnemyAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl)		// �U����������̔��聕�U���̂Ƃ�܂Ƃ�
{
	// �v���C���[�̈ʒu�ƃG�l�~�[�̈ʒu���r
	if(Enemy->AttackFlag == false)
	{
		// �G�l�~�[���E���ɂ���
		if (PlayerPos.x <= Enemy->pos.x)
		{
			Enemy->Direction = false;

		}
		else
		{
			Enemy->Direction = true;
		}
	}

	// �G�l�~�[�̂ق����E���ɂ���ꍇ
	if (Enemy->Direction == false)
	{
		EnemyLeftAttack(PlayerPos, Enemy, scl);
	}
	// �����ɂ���ꍇ
	else
	{
		EnemyRightAttack(PlayerPos, Enemy,scl);
	}
}

void EnemyLeftAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl)
{

	// �U���t���O�������Ă��Ȃ��Ƃ�
	if (Enemy->AttackFlag == false)
	{
		// �U���t���O�����Ƃ�
		if ((PlayerPos.z <= (Enemy->pos.z + scl)) && (PlayerPos.z >= (Enemy->pos.z - scl)))
		{
			float LAttackRandom = 0;

			LAttackRandom=CreateRandomFloat(0.0f, 100.0f);

			if (LAttackRandom > 97.0f)
			{
				Enemy->AttackFlag = true;
			}
		}

		// �ҋ@��Ԃ̓����i�ړ��ꏊ�����܂��Ă��Ȃ��Ƃ��j
		if (Enemy->IdleFlag == true)
		{
			Enemy->Epos.z = CreateRandomFloat(-200.0f, 10.0f);
			Enemy->IdleFlag = false;
		}

		// �ҋ@��Ԃ̓����i�ړ��ꏊ�����܂��Ă���Ƃ��j
		else if (Enemy->IdleFlag == false)
		{
			// ����
			if (Enemy->Epos.z > Enemy->pos.z)
			{
				Enemy->pos.z += ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1)	// �����_�ȉ��͖���
				{
					Enemy->IdleFlag = true;
				}
			}
			else if (Enemy->Epos.z < Enemy->pos.z)
			{
				Enemy->pos.z -= ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1) // �����_�ȉ��͖���
				{
					Enemy->IdleFlag = true;
				}

			}
		}
	}
	// �U���t���O�������Ă���Ƃ�
	else if (Enemy->AttackFlag == true)
	{
		// �ːi���Ă�������
		if (PlayerPos.x <= Enemy->pos.x)
		{
			Enemy->pos.x -= ENEMY_RUN;
		}

		// �ːi�I���Ńt���O��߂�
		if (PlayerPos.x > Enemy->pos.x)
		{
			Enemy->AttackFlag = false;
		}

	}

}


void EnemyRightAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy,float scl)	// �E�����̍U��
{

	// �U���t���O�������Ă��Ȃ��Ƃ�
	if (Enemy->AttackFlag == false)
	{
		// �U���t���O�����Ƃ�
		if ((PlayerPos.z <= (Enemy->pos.z + scl)) && (PlayerPos.z >= (Enemy->pos.z - scl)))
		{
			float RAttackRandom = 0;

			RAttackRandom=CreateRandomFloat(0.0f, 100.0f);

			if (RAttackRandom > 97.0f)
			{
				Enemy->AttackFlag = true;
			}
		}

		// �ҋ@��Ԃ̓����i�ړ��ꏊ�����܂��Ă��Ȃ��Ƃ��j
		if (Enemy->IdleFlag == true)
		{
			Enemy->Epos.z = CreateRandomFloat(-200.0f, 10.0f);
			Enemy->IdleFlag = false;
		}

		// �ҋ@��Ԃ̓����i�ړ��ꏊ�����܂��Ă���Ƃ��j
		else if (Enemy->IdleFlag == false)
		{
			// ����
			if (Enemy->Epos.z > Enemy->pos.z)
			{
				Enemy->pos.z += ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1)	// �����_�ȉ��͖���
				{
					Enemy->IdleFlag = true;
				}
			}
			else if (Enemy->Epos.z < Enemy->pos.z)
			{
				Enemy->pos.z -= ENEMY_WALK;

				if (Enemy->Epos.z == Enemy->pos.z / 1) // �����_�ȉ��͖���
				{
					Enemy->IdleFlag = true;
				}

			}
		}
	}
	// �U���t���O�������Ă���Ƃ�
	else if (Enemy->AttackFlag == true)
	{
		// �ːi���Ă�������
		if (PlayerPos.x > Enemy->pos.x)
		{
			Enemy->pos.x += ENEMY_RUN;
		}

		// �ːi�I���Ńt���O��߂�
		if (PlayerPos.x < Enemy->pos.x)
		{
			Enemy->AttackFlag = false;
		}

	}

}