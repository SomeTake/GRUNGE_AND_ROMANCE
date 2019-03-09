//====================================================================================================================================================================================
// �T�v
// �t�@�C�����FSound.h
// �R�[�f�B���O�t�H���g�FRicty Diminished( 16�T�C�Y )
// �쐬�ҁFHAL���� GP-11B-341 07 �T���v��
// �쐬���F2018/12/10
//====================================================================================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//====================================================================================================================================================================================
// �C���N���[�h
//====================================================================================================================================================================================

//====================================================================================================================================================================================
// �}�N����`
//====================================================================================================================================================================================
#define SOUND_FILE_AGONY ("data/SOUND/SE/Item.wav")	//	�T�E���h�t�@�C��
#define SOUND_FADE_VALUE (25)					//	�T�E���h�̃t�F�[�h�l
#define SOUND_MAX (SOUND_TYPE_MAX)				//	�T�E���h�̍ő吔
#define SOUND_VOLUME_MIN (-10000)				//	�T�E���h�̉��ʍŏ��l
#define SOUND_VOLUME_MAX (0)					//	�T�E���h�̉��ʍő�l
//====================================================================================================================================================================================
// �񋓌^��`
//====================================================================================================================================================================================
enum SOUND_TYPE
{
	SOUND_TYPE_AGONY,	//	�f����
	SOUND_TYPE_MAX,		//	�萔�̍ő�l
};
enum SOUND_PLAY_TYPE
{
	SOUND_PLAY_TYPE_PLAY,	//	�Đ�
	SOUND_PLAY_TYPE_LOOP,	//	���[�v�Đ�
	SOUND_PLAY_TYPE_MAX,	//	�萔�̍ő�l
};
enum SOUND_FADE_TYPE
{
	SOUND_FADE_TYPE_NONE,		//	�t�F�[�h����
	SOUND_FADE_TYPE_FADE_IN,	//	�t�F�[�h�C��
	SOUND_FADE_TYPE_FADE_OUT,	//	�t�F�[�h�A�E�g
	SOUND_FADE_TYPE_MAX,		//	�萔�̍ő�l
};
enum SOUND_VOLUME_TYPE
{
	SOUND_VOLUME_TYPE_LOWEST,	//	�ŏ�
	SOUND_VOLUME_TYPE_HIGHEST,	//	�ő�
	SOUND_VOLUME_TYPE_MAX,		//	�萔�̍ő�l
};
//====================================================================================================================================================================================
// �\���̒�`
//====================================================================================================================================================================================
typedef struct
{
	int Max = DSBVOLUME_MAX;	//	�ő剹��
	int Min = DSBVOLUME_MIN;	//	�ŏ�����
}SETTING_VOLUME;
typedef struct
{
	IDirectSound8 *Direct_Sound = NULL;				//	�T�E���h�̃I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER8 Sound_Buffer[SOUND_MAX];	//	�T�E���h
	SETTING_VOLUME Setting_Volume;					//	�ݒ艹��
	DWORD Play_Position[SOUND_MAX];					//	�Đ��ʒu
	DWORD Play_Method[SOUND_MAX];					//	�Đ����@
	int Fade_Type[SOUND_MAX];						//	�t�F�[�h�^�C�v
	bool Fade_Switch[SOUND_MAX];					//	�t�F�[�h�X�C�b�`
	bool Play_Flag[SOUND_MAX];						//	�Đ��t���O
	bool Pause_Flag[SOUND_MAX];						//	�ꎞ��~�t���O
	int Volume[SOUND_MAX] =							//	����
	{
		DSBVOLUME_MAX,	//	SOUND_TYPE_AGONY
	};
}SOUND;
//====================================================================================================================================================================================
// �v���g�^�C�v�錾
//====================================================================================================================================================================================
// Initialize
HRESULT Initialize_Sound(HWND Window_Handle);

// Release
void Release_Sound(void);

// Update
void Update_Sound(void);
void Update_Sound_Fade_In(int Sound_Index);
void Update_Sound_Fade_Out(int Sound_Index);

// Load
LPDIRECTSOUNDBUFFER8 Load_Sound(int Sound_Index);

// Play
void Play_Sound(int Sound_Index, int Sound_Flag);

// Pause
void Pause_Sound(int Sound_Index);

// Stop
void Stop_Sound(int Sound_Index);

// Check
bool Check_Play_Flag_Sound(int Sound_Index);
void Check_Play_Flag_All_Sound(void);

// Set
void Set_Pause_Sound(void);
void Set_Re_Play_Sound(void);
void Set_Sound_Fade(int Sound_Index, int Sound_Fade_Type);
void Set_Sound_Volume(int Sound_Index, int Sound_Volume_Type);

// Get
void Get_Play_Position_Sound(int Sound_Index);
SOUND *Get_Sound(void);

//// Debug
//#ifdef _DEBUG
//void Draw_Debug_Sound(DEBUG *Debug);
//void Draw_Debug_Sound_Opening(void);
//void Draw_Debug_Sound_Title(void);
//void Draw_Debug_Sound_Game(void);
//void Draw_Debug_Sound_Ending(void);
//#endif
#endif