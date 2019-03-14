//=============================================================================
//
// �₫�₫���� [YakiYaki.cpp]
// Author : HAL���� GP11B341-01 80163 �ђˏt�P
//
//=============================================================================
#include "Struct.h"
#include "YakiYaki.h"
#include "Onna.h"
#include "Blackhole.h"
#include "Collision.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ITEM yakiyakiWk[YAKIYAKI_NUM];	// �A�C�e���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitYakiYaki(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		yakiyakiWk[in].pos = D3DXVECTOR3(CreateRandomFloat(-100.0f, 100.0f), 0.0f, CreateRandomFloat(-10.0f, 10.0f));
		yakiyakiWk[in].rot = D3DXVECTOR3(0.0f, YAKIYAKI_DIRECTION, 0.0f);
		yakiyakiWk[in].scl = D3DXVECTOR3(YAKIYAKI_SCALE, YAKIYAKI_SCALE, YAKIYAKI_SCALE);

		yakiyakiWk[in].D3DTexture = NULL;
		yakiyakiWk[in].D3DXMesh = NULL;
		yakiyakiWk[in].D3DXBuffMat = NULL;
		yakiyakiWk[in].NumMat = 0;
		yakiyakiWk[in].use = true;
		yakiyakiWk[in].pickup = false;
		yakiyakiWk[in].throwed = false;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(YAKIYAKI_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&yakiyakiWk[in].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&yakiyakiWk[in].NumMat,						// D3DXMATERIAL�\���̂̐�
				&yakiyakiWk[in].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&yakiyakiWk[en].D3DTexture);	// �ǂݍ��ރ������[
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitYakiYaki(void)
{
	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		if (yakiyakiWk[in].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			yakiyakiWk[in].D3DTexture->Release();
			yakiyakiWk[in].D3DTexture = NULL;
		}

		if (yakiyakiWk[in].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			yakiyakiWk[in].D3DXMesh->Release();
			yakiyakiWk[in].D3DXMesh = NULL;
		}

		if (yakiyakiWk[in].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			yakiyakiWk[in].D3DXBuffMat->Release();
			yakiyakiWk[in].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateYakiYaki(void)
{
	ENEMY *Onna = GetOnna(0);
	ENEMY *Black = GetBlackhole(0);

	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		if (yakiyakiWk[in].use)
		{
			if (yakiyakiWk[in].throwed)
			{
				// �ړ��v�Z
				yakiyakiWk[in].move.x -= sinf(yakiyakiWk[in].rot.y) * ITEM_THROWED_SPEED;
				yakiyakiWk[in].move.z -= cosf(yakiyakiWk[in].rot.y) * ITEM_THROWED_SPEED;

				yakiyakiWk[in].pos += yakiyakiWk[in].move;
				yakiyakiWk[in].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �����蔻��
				for (int en = 0; en < ONNA_NUM; en++, Onna++)
				{
					if (HitCheckIToE(&yakiyakiWk[in], Onna))
					{
						yakiyakiWk[in].use = false;
						Onna->HPzan -= Data[Throwitem].Damage;
					}
				}

				for (int en = 0; en < ONNA_NUM; en++, Black++)
				{
					if (HitCheckIToE(&yakiyakiWk[in], Black))
					{
						yakiyakiWk[in].use = false;
						Black->HPzan -= Data[Throwitem].Damage;
					}
				}

				// ��ʊO����
				if (yakiyakiWk[in].pos.x >= 1000.0f || yakiyakiWk[in].pos.x <= -1000.0f)
				{
					yakiyakiWk[in].use = false;
				}
			}
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawYakiYaki(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int in = 0; in < YAKIYAKI_NUM; in++)
	{
		if (yakiyakiWk[in].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, yakiyakiWk[in].scl.x, yakiyakiWk[in].scl.y, yakiyakiWk[in].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, yakiyakiWk[in].rot.y, yakiyakiWk[in].rot.x, yakiyakiWk[in].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, yakiyakiWk[in].pos.x, yakiyakiWk[in].pos.y, yakiyakiWk[in].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)yakiyakiWk[in].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)yakiyakiWk[in].NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, yakiyakiWk[in].D3DTexture);

				// �`��
				yakiyakiWk[in].D3DXMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// �A�C�e���̏����擾����
// �����Fin �₫�₫�ԍ�
//=============================================================================
ITEM *GetYakiYaki(int in)
{
	return &yakiyakiWk[in];
}

//=============================================================================
// �A�C�e�����E�����Ƃ��Ɏg�p
//=============================================================================
int SetYakiYaki(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int IdxYakiYaki = -1;

	for (int nCntYakiYaki = 0; nCntYakiYaki < YAKIYAKI_NUM; nCntYakiYaki++)
	{
		if (!yakiyakiWk[nCntYakiYaki].pickup)
		{
			yakiyakiWk[nCntYakiYaki].pos = pos;
			yakiyakiWk[nCntYakiYaki].rot = rot;
			yakiyakiWk[nCntYakiYaki].pickup = true;

			IdxYakiYaki = nCntYakiYaki;
			break;
		}
	}

	return IdxYakiYaki;

}

//=============================================================================
// �ʒu�̍X�V
//=============================================================================
void SetPositionYakiYaki(int IdxYakiYaki, D3DXVECTOR3 pos)
{
	yakiyakiWk[IdxYakiYaki].pos = pos;
}

//=============================================================================
// ��]�̍X�V
//=============================================================================
void SetRotationYakiYaki(int IdxYakiYaki, D3DXVECTOR3 rot)
{
	yakiyakiWk[IdxYakiYaki].rot = rot;
}

void SetThrowedYakiYaki(int Idx)
{
	yakiyakiWk[Idx].throwed = true;
	yakiyakiWk[Idx].pickup = false;
}
