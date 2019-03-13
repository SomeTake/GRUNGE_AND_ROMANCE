//====================================================================================================================================================================================
// �T�v
// �t�@�C�����FEnding.cpp
// �R�[�f�B���O�t�H���g�FRicty Diminished( 16�T�C�Y )
// �쐬�ҁFHAL���� GP-11B-341 07 �T���v��
// �쐬���F2018/12/10
//====================================================================================================================================================================================

//====================================================================================================================================================================================
// �C���N���[�h
//====================================================================================================================================================================================
#include "Main.h"
#include "Input.h"
#include "Sound.h"
#include "Ending.h"
//====================================================================================================================================================================================
// �O���[�o���ϐ�
//====================================================================================================================================================================================
ENDING Ending_State[ENDING_MAX];
//====================================================================================================================================================================================
// �G���f�B���O�̏�����
// �֐����FHRESULT Initialize_Ending
// �߂�l�FHRESULT
//====================================================================================================================================================================================
HRESULT Initialize_Ending(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR2 Temporary = { NULL,NULL };			//	�e���|�����[
	D3DXIMAGE_INFO Texture_Information[ENDING_MAX];	//	�e�N�X�`�����
	const char *Texture_File[ENDING_MAX] =			//	�e�N�X�`���t�@�C��
	{
		TEXTURE_FILE_ENDING,	//	ENDING_TYPE_000
	};

	// �[���N���A
	for (int i = 0; i < ENDING_MAX; i++)
	{
		for (int j = 0; j < NUM_VERTEX; j++)
		{
			ZeroMemory(&Ending_State[i].Vertex[j], sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < ENDING_MAX; i++)
	{
		// �G���f�B���O�̒��_���쐬
		Create_Vertex_Ending(i);

		// �e�N�X�`�����̎擾
		D3DXGetImageInfoFromFile(Texture_File[i], &Texture_Information[i]);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFileEx
		(
			pDevice,
			Texture_File[i],
			Texture_Information[i].Width,
			Texture_Information[i].Height,
			Texture_Information[i].MipLevels,
			0,
			Texture_Information[i].Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&Texture_Information[i],
			NULL,
			&Ending_State[i].Texture
		);

		// �G���f�B���O�̏�����
		switch (i)
		{
		case ENDING_TYPE_000:
			Temporary = D3DXVECTOR2(ENDING_TEXTURE_SIZE_X_000 / 2, ENDING_TEXTURE_SIZE_Y_000 / 2);
			Ending_State[i].Position = D3DXVECTOR3(SCREEN_WIDTH - (ENDING_TEXTURE_SIZE_X_000 / 2), SCREEN_HEIGHT / 2, 0.0f);
			Ending_State[i].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Ending_State[i].Radius = D3DXVec2Length(&Temporary);
			Ending_State[i].Angle = atan2f(ENDING_TEXTURE_SIZE_Y_000, ENDING_TEXTURE_SIZE_X_000);
			continue;
			break;
		default:
			continue;
			break;
		}
	}

	// ����I��
	return S_OK;
}

//====================================================================================================================================================================================
// �G���f�B���O�̉��
// �֐����Fvoid Release_Ending
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Release_Ending(void)
{
	for (int i = 0; i < ENDING_MAX; i++)
	{
		SAFE_RELEASE(Ending_State[i].Texture);
	}

	return;
}

//====================================================================================================================================================================================
// �G���f�B���O�̍X�V
// �֐����Fvoid Update_Ending
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Update_Ending(void)
{
	// �G���f�B���O�̒��_����ݒ�
	for (int i = 0; i < ENDING_MAX; i++)
	{
		Set_Vertex_Ending(i);
	}

	return;
}

//====================================================================================================================================================================================
// �G���f�B���O( �����҂� )�̕`��
// �֐����Fvoid Draw_Ending
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Draw_Ending(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENDING_MAX; i++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Ending_State[i].Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Ending_State[i].Vertex, sizeof(VERTEX_2D));
	}

	return;
}

//====================================================================================================================================================================================
// �G���f�B���O�̒��_���쐬
// �֐����FHRESULT Create_Vertex_Ending
// �߂�l�FHRESULT
// ���� 1�Fint
//====================================================================================================================================================================================
HRESULT Create_Vertex_Ending(int Ending_Index)
{
	// ���_���W�̐ݒ�
	Set_Vertex_Ending(Ending_Index);

	// RHW�̐ݒ�
	Ending_State[Ending_Index].Vertex[0].rhw = 1.0f;
	Ending_State[Ending_Index].Vertex[1].rhw = 1.0f;
	Ending_State[Ending_Index].Vertex[2].rhw = 1.0f;
	Ending_State[Ending_Index].Vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�( ���_�J���[ )
	Ending_State[Ending_Index].Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Ending_State[Ending_Index].Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Ending_State[Ending_Index].Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Ending_State[Ending_Index].Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	Set_Texture_Ending(Ending_Index);

	// ����I��
	return S_OK;
}

//====================================================================================================================================================================================
// �G���f�B���O�̒��_���W��ݒ�
// �֐����Fvoid Set_Vertex_Ending
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Set_Vertex_Ending(int Ending_Index)
{	
	// --------------------------------------------------	Vertex[0]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[0].vtx.x = (Ending_State[Ending_Index].Position.x - cosf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[0].vtx.y = (Ending_State[Ending_Index].Position.y - sinf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[1]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[1].vtx.x = (Ending_State[Ending_Index].Position.x + cosf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[1].vtx.y = (Ending_State[Ending_Index].Position.y - sinf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[2]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[2].vtx.x = (Ending_State[Ending_Index].Position.x - cosf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[2].vtx.y = (Ending_State[Ending_Index].Position.y + sinf(Ending_State[Ending_Index].Angle - Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[3]	--------------------------------------------------
	Ending_State[Ending_Index].Vertex[3].vtx.x = (Ending_State[Ending_Index].Position.x + cosf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;
	Ending_State[Ending_Index].Vertex[3].vtx.y = (Ending_State[Ending_Index].Position.y + sinf(Ending_State[Ending_Index].Angle + Ending_State[Ending_Index].Rotation.z) * Ending_State[Ending_Index].Radius) - 0.5f;

	return;
}

//====================================================================================================================================================================================
// �G���f�B���O�̃e�N�X�`�����W��ݒ�
// �֐����Fvoid Set_Texture_Ending
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Set_Texture_Ending(int Ending_Index)
{
	// �ϐ��錾�F������
	int Texture_Split_U = 0 % ENDING_TEXTURE_PATTERN_DIVIDE_X;	//	�e�N�X�`��������( U )
	int Texture_Split_V = 0 / ENDING_TEXTURE_PATTERN_DIVIDE_X;	//	�e�N�X�`��������( V )
	float Size_U = 1.0f / ENDING_TEXTURE_PATTERN_DIVIDE_X;		//	�e�N�X�`���̂P�����̉���( X )
	float Size_V = 1.0f / ENDING_TEXTURE_PATTERN_DIVIDE_Y;		//	�e�N�X�`���̂P�����̏c��( Y )

	// �e�N�X�`�����W�̐ݒ�
	Ending_State[Ending_Index].Vertex[0].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V);					//	�e�N�X�`�����W�̍����ݒ�
	Ending_State[Ending_Index].Vertex[1].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V);			//	�e�N�X�`�����W�̉E���ݒ�
	Ending_State[Ending_Index].Vertex[2].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V + Size_V);			//	�e�N�X�`�����W�̍�����ݒ�
	Ending_State[Ending_Index].Vertex[3].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V + Size_V);	//	�e�N�X�`�����W�̉E����ݒ�

	return;
}

//====================================================================================================================================================================================
// �G���f�B���O�̎擾
// �֐����FENDING *Get_Ending
// �߂�l�FENDING
// ���� 1�Fint
//====================================================================================================================================================================================
ENDING *Get_Ending(int Ending_Index)
{
	return &Ending_State[Ending_Index];
}