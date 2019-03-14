//=============================================================================
//
// �{�X���� [Boss.cpp]
// Author : HAL���� GP11B341-17 80277 ���J���u
//
//=============================================================================
#include "Struct.h"
#include "Boss.h"
#include "Player.h"
#include "Debugproc.h"
#include "Game.h"
#include "Effect.h"
#include "Sound.h"
#include "Collision.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ENEMY bossWk[BOSS_NUM];	// �G�l�~�[�\����

						//=============================================================================
						// ����������
						//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < BOSS_NUM; en++)
	{
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		bossWk[en].HP = BOSS_HP_MAX;
		bossWk[en].HPzan = bossWk[en].HP;
		bossWk[en].pos = D3DXVECTOR3(CreateRandomFloat(-200.0f, 200.0f), 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		bossWk[en].Epos = D3DXVECTOR3(0.0f, 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		bossWk[en].rot = D3DXVECTOR3(0.0f, BOSS_DIRECTION, 0.0f);
		bossWk[en].scl = D3DXVECTOR3(BOSS_SCALE, BOSS_SCALE, BOSS_SCALE);

		bossWk[en].D3DTexture = NULL;
		bossWk[en].D3DXMesh = NULL;
		bossWk[en].D3DXBuffMat = NULL;
		bossWk[en].NumMat = 0;
		bossWk[en].use = true;
		bossWk[en].IdleFlag = true;
		bossWk[en].AttackFlag = false;

		if (type == 0)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(BOSS_XFILE,		// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,							// ���b�V���̍쐬�I�v�V�������w��
				pDevice,									// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,										// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&bossWk[en].D3DXBuffMat,					// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,										// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&bossWk[en].NumMat,						// D3DXMATERIAL�\���̂̐�
				&bossWk[en].D3DXMesh)))					// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
			{
				return E_FAIL;
			}

			bossWk[en].IdxShadow = SetShadow(bossWk[en].pos, 30.0f, 30.0f);
#if 0
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				TEXTURE_FILENAME,		// �t�@�C���̖��O
				&bossWk[en].D3DTexture);	// �ǂݍ��ރ������[
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{
	for (int en = 0; en < BOSS_NUM; en++)
	{
		if (bossWk[en].D3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			bossWk[en].D3DTexture->Release();
			bossWk[en].D3DTexture = NULL;
		}

		if (bossWk[en].D3DXMesh != NULL)
		{	// ���b�V���̊J��
			bossWk[en].D3DXMesh->Release();
			bossWk[en].D3DXMesh = NULL;
		}

		if (bossWk[en].D3DXBuffMat != NULL)
		{	// �}�e���A���̊J��
			bossWk[en].D3DXBuffMat->Release();
			bossWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	static int Check = 0;

	CHARA *charaWk = GetPlayer(0);

	for (int pn = 0; pn < PLAYER_NUM; pn++, charaWk++)
	{

		for (int en = 0; en < BOSS_NUM; en++)
		{

			// �g�p���Ă���ꍇ�̂ݍX�V
			if (bossWk[en].use)
			{
				// �G�l�~�[�̍U��
				EnemyAttack(charaWk->pos, &bossWk[en], BOSS_XSCALE);

				SetVertexBoss();

				// HP0�ɂȂ��������
				if (bossWk[en].HPzan == 0)
				{
					DeleteShadow(bossWk[en].IdxShadow);
					SetEffect(bossWk[en].pos, BurstEffect);
					Play_Sound(SOUND_TYPE_KNOCK_DOWN, SOUND_PLAY_TYPE_PLAY);
					bossWk[en].use = false;
					Check++;
				}

				// �U�����̓����蔻��
				if (bossWk[en].AttackFlag)
				{
					if (charaWk->Animation->CurrentAnimID == Idle || charaWk->Animation->CurrentAnimID == Walk
						|| charaWk->Animation->CurrentAnimID == Rightwalk || charaWk->Animation->CurrentAnimID == Leftwalk
						|| charaWk->Animation->CurrentAnimID == Idleitem)
					{
						if (HitCheckEToP(&bossWk[en], charaWk))
						{
							bossWk[en].AttackFlag = false;
							charaWk->Animation->ChangeAnimation(charaWk->Animation, Reaction, Data[Reaction].Spd);
							charaWk->HPzan -= ENEMY_DAMAGE;
						}
					}
				}

				SetPositionShadow(bossWk[en].IdxShadow, bossWk[en].pos);
				SetVertexShadow(bossWk[en].IdxShadow, 30.0f, 30.0f);
				SetColorShadow(bossWk[en].IdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			}

		}
	}

	if (Check >= BOSS_NUM)
	{
		SetStage(STAGE_ENDING);
		ReInit();
		SetEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), FireEffect);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < BOSS_NUM; en++)
	{
		if (bossWk[en].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, bossWk[en].scl.x, bossWk[en].scl.y, bossWk[en].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, bossWk[en].rot.y, bossWk[en].rot.x, bossWk[en].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, bossWk[en].pos.x, bossWk[en].pos.y, bossWk[en].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)bossWk[en].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)bossWk[en].NumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, bossWk[en].D3DTexture);

				// �`��
				bossWk[en].D3DXMesh->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}

	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss(void)
{
	if (bossWk->Direction == false)
	{
		bossWk->rot.y = BOSS_DIRECTION2;
	}
	else if (bossWk->Direction == true)
	{
		bossWk->rot.y = BOSS_DIRECTION;
	}

}

//=============================================================================
// �G�l�~�[�̏����擾����
// �����Fen �G�l�~�[�ԍ�
//=============================================================================
ENEMY *GetBoss(int en)
{
	return &bossWk[en];
}