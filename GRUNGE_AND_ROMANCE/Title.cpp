//====================================================================================================================================================================================
// �T�v
// �t�@�C�����FTitle.cpp
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
#include "Title.h"
//====================================================================================================================================================================================
// �O���[�o���ϐ�
//====================================================================================================================================================================================
TITLE Title_State[TITLE_MAX];
//====================================================================================================================================================================================
// �^�C�g���̏�����
// �֐����FHRESULT Initialize_Title
// �߂�l�FHRESULT
//====================================================================================================================================================================================
HRESULT Initialize_Title(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR2 Temporary = { NULL,NULL };			//	�e���|�����[
	D3DXIMAGE_INFO Texture_Information[TITLE_MAX];	//	�e�N�X�`�����
	const char *Texture_File[TITLE_MAX] =			//	�e�N�X�`���t�@�C��
	{
		TEXTURE_FILE_TITLE_BACK_GROUND,	//	TITLE_TYPE_BACK_GROUND
		TEXTURE_FILE_TITLE_LOGO,		//	TITLE_TYPE_LOGO
	};

	// �[���N���A
	for (int i = 0; i < TITLE_MAX; i++)
	{
		for (int j = 0; j < NUM_VERTEX; j++)
		{
			ZeroMemory(&Title_State[i].Vertex[j], sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < TITLE_MAX; i++)
	{
		// �^�C�g���̒��_���쐬
		Create_Vertex_Title(i);

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
			&Title_State[i].Texture
		);

		// �^�C�g���̏�����
		switch (i)
		{
		case TITLE_TYPE_BACK_GROUND:
			Temporary = D3DXVECTOR2(TITLE_TEXTURE_SIZE_X_000 / 2, TITLE_TEXTURE_SIZE_Y_000 / 2);
			Title_State[i].Position = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_TEXTURE_SIZE_X_000 / 2), SCREEN_HEIGHT / 2, 0.0f);
			Title_State[i].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Title_State[i].Radius = D3DXVec2Length(&Temporary);
			Title_State[i].Angle = atan2f(TITLE_TEXTURE_SIZE_Y_000, TITLE_TEXTURE_SIZE_X_000);
			continue;
			break;
		case TITLE_TYPE_LOGO:
			Temporary = D3DXVECTOR2(TITLE_TEXTURE_SIZE_X_000 / 2, TITLE_TEXTURE_SIZE_Y_000 / 2);
			Title_State[i].Position = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_TEXTURE_SIZE_X_000 / 2), SCREEN_HEIGHT / 2, 0.0f);
			Title_State[i].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Title_State[i].Radius = D3DXVec2Length(&Temporary);
			Title_State[i].Angle = atan2f(TITLE_TEXTURE_SIZE_Y_000, TITLE_TEXTURE_SIZE_X_000);
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
// �^�C�g���̉��
// �֐����Fvoid Release_Title
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Release_Title(void)
{
	for (int i = 0; i < TITLE_MAX; i++)
	{
		SAFE_RELEASE(Title_State[i].Texture);
	}

	return;
}

//====================================================================================================================================================================================
// �^�C�g���̍X�V
// �֐����Fvoid Update_Title
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Update_Title(void)
{
	// �^�C�g���̒��_����ݒ�
	for (int i = 0; i < TITLE_MAX; i++)
	{
		Set_Vertex_Title(i);
	}

	return;
}

//====================================================================================================================================================================================
// �^�C�g��( �����҂� )�̕`��
// �֐����Fvoid Draw_Title
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Draw_Title(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TITLE_MAX; i++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Title_State[i].Texture);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Title_State[i].Vertex, sizeof(VERTEX_2D));
	}

	return;
}

//====================================================================================================================================================================================
// �^�C�g���̒��_���쐬
// �֐����FHRESULT Create_Vertex_Title
// �߂�l�FHRESULT
// ���� 1�Fint
//====================================================================================================================================================================================
HRESULT Create_Vertex_Title(int Title_Index)
{
	// ���_���W�̐ݒ�
	Set_Vertex_Title(Title_Index);

	// RHW�̐ݒ�
	Title_State[Title_Index].Vertex[0].rhw = 1.0f;
	Title_State[Title_Index].Vertex[1].rhw = 1.0f;
	Title_State[Title_Index].Vertex[2].rhw = 1.0f;
	Title_State[Title_Index].Vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�( ���_�J���[ )
	Title_State[Title_Index].Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Title_State[Title_Index].Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Title_State[Title_Index].Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Title_State[Title_Index].Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	Set_Texture_Title(Title_Index);

	// ����I��
	return S_OK;
}

//====================================================================================================================================================================================
// �^�C�g���̒��_���W��ݒ�
// �֐����Fvoid Set_Vertex_Title
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Set_Vertex_Title(int Title_Index)
{	
	// --------------------------------------------------	Vertex[0]	--------------------------------------------------
	Title_State[Title_Index].Vertex[0].vtx.x = (Title_State[Title_Index].Position.x - cosf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[0].vtx.y = (Title_State[Title_Index].Position.y - sinf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[1]	--------------------------------------------------
	Title_State[Title_Index].Vertex[1].vtx.x = (Title_State[Title_Index].Position.x + cosf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[1].vtx.y = (Title_State[Title_Index].Position.y - sinf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[2]	--------------------------------------------------
	Title_State[Title_Index].Vertex[2].vtx.x = (Title_State[Title_Index].Position.x - cosf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[2].vtx.y = (Title_State[Title_Index].Position.y + sinf(Title_State[Title_Index].Angle - Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	// --------------------------------------------------	Vertex[3]	--------------------------------------------------
	Title_State[Title_Index].Vertex[3].vtx.x = (Title_State[Title_Index].Position.x + cosf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;
	Title_State[Title_Index].Vertex[3].vtx.y = (Title_State[Title_Index].Position.y + sinf(Title_State[Title_Index].Angle + Title_State[Title_Index].Rotation.z) * Title_State[Title_Index].Radius) - 0.5f;

	return;
}

//====================================================================================================================================================================================
// �^�C�g���̃e�N�X�`�����W��ݒ�
// �֐����Fvoid Set_Texture_Title
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Set_Texture_Title(int Title_Index)
{
	// �ϐ��錾�F������
	int Texture_Split_U = 0 % TITLE_TEXTURE_PATTERN_DIVIDE_X;	//	�e�N�X�`��������( U )
	int Texture_Split_V = 0 / TITLE_TEXTURE_PATTERN_DIVIDE_X;	//	�e�N�X�`��������( V )
	float Size_U = 1.0f / TITLE_TEXTURE_PATTERN_DIVIDE_X;		//	�e�N�X�`���̂P�����̉���( X )
	float Size_V = 1.0f / TITLE_TEXTURE_PATTERN_DIVIDE_Y;		//	�e�N�X�`���̂P�����̏c��( Y )

	// �e�N�X�`�����W�̐ݒ�
	Title_State[Title_Index].Vertex[0].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V);					//	�e�N�X�`�����W�̍����ݒ�
	Title_State[Title_Index].Vertex[1].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V);			//	�e�N�X�`�����W�̉E���ݒ�
	Title_State[Title_Index].Vertex[2].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U, (float)(Texture_Split_V)* Size_V + Size_V);			//	�e�N�X�`�����W�̍�����ݒ�
	Title_State[Title_Index].Vertex[3].tex = D3DXVECTOR2((float)(Texture_Split_U)* Size_U + Size_U, (float)(Texture_Split_V)* Size_V + Size_V);	//	�e�N�X�`�����W�̉E����ݒ�

	return;
}

//====================================================================================================================================================================================
// �^�C�g���̎擾
// �֐����FTITLE *Get_Title
// �߂�l�FTITLE
// ���� 1�Fint
//====================================================================================================================================================================================
TITLE *Get_Title(int Title_Index)
{
	return &Title_State[Title_Index];
}