//=============================================================================
//
// �{�X���� [Boss.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOSS_XFILE		"data/MODEL/sora_ai.x"		// �ǂݍ��ރ��f����
#define BOSS_NUM		(1)						// �G�l�~�[�̐�
#define BOSS_HP_MAX		(200)
#define BOSS_DIRECTION	(200.0f)
#define BOSS_DIRECTION2	(360.0f)				// �G�l�~�[�𔽑Ό�����
#define BOSS_SCALE		(10.0f)
#define BOSS_XSCALE		(10.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoss(int type);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
ENEMY *GetBoss(int en);
void SetVertexBoss(void);

#endif