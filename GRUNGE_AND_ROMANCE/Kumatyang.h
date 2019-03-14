//=============================================================================
//
// ���܂���񏈗� [Kumatyang.h]
// Author : HAL���� GP11B341-01 80163 �ђˏt�P
//
//=============================================================================
#ifndef _KUMATYANG_H_
#define _KUMATYANG_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	KUMATYANG_XFILE		"data/MODEL/kumazyang.x"	// �ǂݍ��ރ��f����
#define KUMATYANG_NUM		(1)						// �o�[�x���̐�
#define KUMATYANG_DIRECTION	(200.0f)
#define KUMATYANG_SCALE		(3.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKumatyang(int type);
void UninitKumatyang(void);
void UpdateKumatyang(void);
void DrawKumatyang(void);
ITEM *GetKumatyang(int in);
int SetKumatyang(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionKumatyang(int IdxIdxKumatyang, D3DXVECTOR3 pos);
void SetRotationKumatyang(int IdxIdxKumatyang, D3DXVECTOR3 rot);
void SetThrowedKumatyang(int Idx);

#endif
