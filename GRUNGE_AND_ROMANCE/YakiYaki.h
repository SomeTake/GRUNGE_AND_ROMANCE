//=============================================================================
//
// �₫�₫���� [YakiYaki.h]
// Author : HAL���� GP11B341-01 80163 �ђˏt�P
//
//=============================================================================
#ifndef _YAKIYAKI_H_
#define _YAKIYAKI_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	YAKIYAKI_XFILE		"data/MODEL/YakiYaki.x"	// �ǂݍ��ރ��f����
#define YAKIYAKI_NUM		(1)						// �o�[�x���̐�
#define YAKIYAKI_DIRECTION	(200.0f)
#define YAKIYAKI_SCALE		(3.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitYakiYaki(int type);
void UninitYakiYaki(void);
void UpdateYakiYaki(void);
void DrawYakiYaki(void);
ITEM *GetYakiYaki(int in);
int SetYakiYaki(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionYakiYaki(int IdxBabel, D3DXVECTOR3 pos);
void SetRotationYakiYaki(int IdxBabel, D3DXVECTOR3 rot);
void SetThrowedYakiYaki(int Idx);

#endif
