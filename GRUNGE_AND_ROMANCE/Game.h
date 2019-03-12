/*******************************************************************************
* �^�C�g��:		�Q�[���w�b�_�[
* �v���O������:	Game.h
* �쐬��:		GP11B341 01 �ђˏt�P
* �쐬��:		2018/07/26
*******************************************************************************/
#ifndef _GAME_H_
#define _GAME_H_

#include "Main.h"
#include "Struct.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_WALK		(0.5f)								// �G�l�~�[�̕������x
#define	ENEMY_RUN		(2.0f)								// �G�l�~�[�̑��鑬�x

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void AddDamageEnemy(ENEMY *enemy, int damage);		// �G�l�~�[�Ƀ_���[�W��^����
void AddDamagePlayer(CHARA *player, int damage);	// �v���C���[�Ƀ_���[�W��^����

// �G�l�~�[�̍U��													
void EnemyAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl);		// �U����������̔��聕�U���̂Ƃ�܂Ƃ�
void EnemyLeftAttack(D3DXVECTOR3 PlayerPos, ENEMY *Enemy, float scl);	// �������̍U��
void EnemyRightAttack(D3DXVECTOR3 Playerpos, ENEMY *Enemy, float scl);	// �E�����̍U��


#endif
