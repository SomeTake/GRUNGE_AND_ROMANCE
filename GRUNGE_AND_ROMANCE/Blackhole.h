//=============================================================================
//
// �u���b�N�z�[�����񏈗� [Blackhole.h]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#ifndef _BLACKHOLE_H_
#define _BLACKHOLE_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BLACKHOLE_XFILE		"data/MODEL/black.x"		// �ǂݍ��ރ��f����
#define BLACKHOLE_NUM			(10)						// �G�l�~�[�̐�
#define BLACKHOLE_HP_MAX		(50)
#define BLACKHOLE_DIRECTION		(0.0f)
#define BLACKHOLE_DIRECTION2	(160.0f)					// �G�l�~�[�𔽑Ό�����
#define BLACKHOLE_SCALE			(3.0f)
#define BLACKHOLE_XSCALE		(12.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBlackhole(int type);
void UninitBlackhole(void);
void UpdateBlackhole(void);
void DrawBlackhole(void);
ENEMY *GetBlackhole(int en);
void SetVertexBlackhole(void);

#endif
