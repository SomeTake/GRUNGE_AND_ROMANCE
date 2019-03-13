//=============================================================================
//
// �o�[�x������ [Babel.h]
// Author : HAL���� GP11B341-01 80163 �ђˏt�P
//
//=============================================================================
#ifndef _BABEL_H_
#define _BABEL_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BABEL_XFILE		"data/MODEL/babel.x"		// �ǂݍ��ރ��f����
#define BABEL_NUM		(1)						// �o�[�x���̐�
#define BABEL_DIRECTION	(200.0f)
#define BABEL_SCALE		(3.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBabel(int type);
void UninitBabel(void);
void UpdateBabel(void);
void DrawBabel(void);
ITEM *GetBabel(int in);
int SetBabel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionBabel(int IdxBabel, D3DXVECTOR3 pos);
void SetRotationBabel(int IdxBabel, D3DXVECTOR3 rot);
void SetThrowedBabel(int Idx);

#endif
