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
#define SOUND_FILE_ATTACK_ITEM ("data/SOUND/SE/Attack_Item_Extinction.wav")	//	�T�E���h�t�@�C��
#define SOUND_FILE_ATTACK_KICK ("data/SOUND/SE/Attack_Kick_Jeize.wav")		//	�T�E���h�t�@�C��
#define SOUND_FILE_ATTACK_PUNCH ("data/SOUND/SE/Attack_Punch_Foise.wav")	//	�T�E���h�t�@�C��
#define SOUND_FILE_ITEM_PICK ("data/SOUND/SE/Item_Pick.wav")				//	�T�E���h�t�@�C��
#define SOUND_FILE_KNOCK_DOWN ("data/SOUND/SE/Knock_Down.wav")				//	�T�E���h�t�@�C��
#define SOUND_FILE_KNOCK_DOWN_BOSS ("data/SOUND/SE/Knock_Down_Boss.wav")	//	�T�E���h�t�@�C��
#define SOUND_FILE_BGM ("data/SOUND/BGM/ClubAvenue.wav")					//	�T�E���h�t�@�C��
#define SOUND_FILE_ENDING ("data/SOUND/BGM/Title_Back_Ground_Music_000_Ambient.wav")	//	�T�E���h�t�@�C��
#define SOUND_MAX (SOUND_TYPE_MAX)											//	�T�E���h�̍ő吔
//====================================================================================================================================================================================
// �񋓌^��`
//====================================================================================================================================================================================
enum SOUND_TYPE
{
	SOUND_TYPE_ATTACK_ITEM,		//	�^�_���F�A�C�e��
	SOUND_TYPE_ATTACK_KICK,		//	�^�_���F�L�b�N
	SOUND_TYPE_ATTACK_PUNCH,	//	�^�_���F�p���`
	SOUND_TYPE_ITEM_PICK,		//	�A�C�e���擾
	SOUND_TYPE_KNOCK_DOWN,		//	�m�b�N�_�E��
	SOUND_TYPE_KNOCK_DOWN_BOSS,	//	�m�b�N�_�E���F�{�X
	SOUND_TYPE_BGM,				//	BGM
	SOUND_TYPE_ENDING,			//	ENDING
	SOUND_TYPE_MAX,				//	�萔�̍ő�l
};
enum SOUND_PLAY_TYPE
{
	SOUND_PLAY_TYPE_PLAY,	//	�Đ�
	SOUND_PLAY_TYPE_LOOP,	//	���[�v�Đ�
	SOUND_PLAY_TYPE_MAX,	//	�萔�̍ő�l
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
}SOUND;
//====================================================================================================================================================================================
// �v���g�^�C�v�錾
//====================================================================================================================================================================================
// Initialize
HRESULT Initialize_Sound(HWND Window_Handle);

// Release
void Release_Sound(void);

// Load
LPDIRECTSOUNDBUFFER8 Load_Sound(int Sound_Index);

// Play
void Play_Sound(int Sound_Index, int Sound_Flag);

// Stop
void Stop_Sound(int Sound_Index);

// Get
SOUND *Get_Sound(void);
#endif