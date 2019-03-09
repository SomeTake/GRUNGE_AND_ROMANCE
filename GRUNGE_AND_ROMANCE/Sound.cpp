//====================================================================================================================================================================================
// �T�v
// �t�@�C�����FSound.cpp
// �R�[�f�B���O�t�H���g�FRicty Diminished( 16�T�C�Y )
// �쐬�ҁFHAL���� GP-11B-341 07 �T���v��
// �쐬���F2018/12/10
//====================================================================================================================================================================================

//====================================================================================================================================================================================
// �C���N���[�h
//====================================================================================================================================================================================
#include "main.h"
#include "Sound.h"
//====================================================================================================================================================================================
// �O���[�o���ϐ�
//====================================================================================================================================================================================
SOUND Sound_State;
//====================================================================================================================================================================================
// �̈� - �擾
//====================================================================================================================================================================================
#pragma region Initialize
//====================================================================================================================================================================================
// �T�E���h�̏�����
// �֐����FHRESULT Initialize_Sound
// �߂�l�FHRESULT
// ���� 1�FHWND
//====================================================================================================================================================================================
HRESULT Initialize_Sound(HWND Window_Handle)
{
	// ������ / �[���N���A
	for (int i = 0; i < SOUND_MAX; i++)
	{
		Sound_State.Play_Flag[i] = NULL;
		ZeroMemory(&Sound_State.Sound_Buffer[i], sizeof(LPDIRECTSOUNDBUFFER8));
	}

	// IDirectSound8�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectSoundCreate8	//	DirectSoundCreate8�֐��F"IDirectSound8"�C���^�[�t�F�C�X���T�|�[�g����I�u�W�F�N�g���쐬���A����������
	(
		NULL,						//	�T�E���h�f�o�C�X������GUID�̃A�h���X�FNULL = �V�X�e���S�̂̊���̃I�[�f�B�I�Đ��f�o�C�X���w��
		&Sound_State.Direct_Sound,	//	"IDirectSound8"�C���^�[�t�F�C�X�|�C���^���󂯎��ϐ��̃A�h���X
		NULL						//	�R���|�[�l���g�I�u�W�F�N�g���f��( COM )�W���ɑ΂��鐧��I�u�W�F�N�g��IUnknown�C���^�[�t�F�C�X�̃A�h���X�ւ̃|�C���^�F�C���^�[�t�F�C�X���W������Ă��Ȃ��ꍇ�ɂ�"NULL"( �ʏ�A�Ăяo������"NULL"��n�� )
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CREATE_SOUND);
	}

	// �������[�h��ݒ�( �t�H�A�O���E���h&��r�����[�h )
	if (FAILED(Sound_State.Direct_Sound->SetCooperativeLevel	//	SetCooperativeLevel�֐��F�A�v���P�[�V�����̍ŏ�ʓ�������肷��
	(
		Window_Handle,	//	�E�B���h�E�n���h��
		DSSCL_PRIORITY	//	������w��( DSSCL_PRIORITY�F�D�惌�x���ɐݒ肷�� )
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_SETTING_COOPERATION_MODE);
	}

	// �T�E���h�̓ǂݍ���
	for (int i = 0; i < SOUND_MAX; i++)
	{
		Sound_State.Sound_Buffer[i] = Load_Sound(i);
	}

	// ����I��
	return S_OK;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - ���
//====================================================================================================================================================================================
#pragma region Release
//====================================================================================================================================================================================
// �T�E���h�̉��
// �֐����Fvoid Release_Sound
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Release_Sound(void)
{
	//Start_Critical_Section();
	SAFE_RELEASE(Sound_State.Direct_Sound);
	//End_Critical_Section();

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - �X�V
//====================================================================================================================================================================================
#pragma region Update
//====================================================================================================================================================================================
// �T�E���h�̍X�V
// �֐����Fvoid Update_Sound
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Update_Sound(void)
{
	// �t�F�[�h����
	for (int i = 0; i < SOUND_MAX; i++)
	{
		if ((Sound_State.Fade_Type[i] != SOUND_FADE_TYPE_NONE) && (Sound_State.Fade_Type[i] == SOUND_FADE_TYPE_FADE_IN))
		{
			// �t�F�[�h�C��
			Update_Sound_Fade_In(i);
		}
		else if ((Sound_State.Fade_Type[i] != SOUND_FADE_TYPE_NONE) && (Sound_State.Fade_Type[i] == SOUND_FADE_TYPE_FADE_OUT))
		{
			// �t�F�[�h�A�E�g
			Update_Sound_Fade_Out(i);
		}
	}

	return;
}

//====================================================================================================================================================================================
// �T�E���h�̍X�V( �t�F�[�h�C�� )
// �֐����Fvoid Update_Sound_Fade_In
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Update_Sound_Fade_In(int Sound_Index)
{
	// �������^�[��
	if (!Sound_State.Fade_Switch[Sound_Index])
	{
		return;
	}

	if (Sound_State.Setting_Volume.Max <= Sound_State.Volume[Sound_Index])
	{
		// ���ʂ̐ݒ�
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	Sound_State.Volume[Sound_Index] += SOUND_FADE_VALUE;

	if (Sound_State.Setting_Volume.Max > Sound_State.Volume[Sound_Index])
	{
		// ���ʂ̐ݒ�
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	Sound_State.Fade_Switch[Sound_Index] = false;
	Sound_State.Fade_Type[Sound_Index] = SOUND_FADE_TYPE_NONE;
	Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Max;

	//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);

	// ���ʂ̐ݒ�
	Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);

	return;
}

//====================================================================================================================================================================================
// �T�E���h�̍X�V( �t�F�[�h�A�E�g )
// �֐����Fvoid Update_Sound_Fade_Out
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Update_Sound_Fade_Out(int Sound_Index)
{
	// �������^�[��
	if (!Sound_State.Fade_Switch[Sound_Index])
	{
		return;
	}

	if (Sound_State.Setting_Volume.Min >= Sound_State.Volume[Sound_Index])
	{
		// ���ʂ̐ݒ�
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	Sound_State.Volume[Sound_Index] -= SOUND_FADE_VALUE;

	if (Sound_State.Setting_Volume.Min < Sound_State.Volume[Sound_Index])
	{
		// ���ʂ̐ݒ�
		Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);
		return;
	}

	//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);
	Sound_State.Fade_Switch[Sound_Index] = false;
	Sound_State.Fade_Type[Sound_Index] = SOUND_FADE_TYPE_NONE;
	Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Min;
	Stop_Sound(Sound_Index);

	// ���ʂ̐ݒ�
	Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - �ǂݍ���
//====================================================================================================================================================================================
#pragma region Load
//====================================================================================================================================================================================
// �T�E���h�̓ǂݍ���
// �֐����FLPDIRECTSOUNDBUFFER8 Load_Sound
// �߂�l�FLPDIRECTSOUNDBUFFER8
// ���� 1�Fint
//====================================================================================================================================================================================
LPDIRECTSOUNDBUFFER8 Load_Sound(int Sound_Index)
{
	// �ϐ��錾�F������ / �T�E���h�ǂݍ���
	const char *Sound_File[] =	//	�T�E���h�t�@�C��
	{
		SOUND_FILE_AGONY,	//	SOUND_TYPE_AGONY
	};

	// �ϐ��錾�F������
	// MMIO�F�}���`���f�B�A�C���v�b�g/�A�E�g�v�b�g( �}���`���f�B�AI/O( ���o�� ) )�̗���
	// .wav�t�@�C���́A���t( RIFF )�Ƃ����t�H�[�}�b�g�`���ɏ]���Ă���( RIFF�FResource InterChange File Format )
	// ����̓`�����N( Chunk�F�� )�ƌĂ΂��f�[�^�̈�܂Ƃ܂����ׂĉ��̏��𐮗����Ă���
	LPDIRECTSOUNDBUFFER Sound_Base_Buffer = NULL;	//	�����f�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 Sound_Buffer = NULL;		//	�����f�[�^�̃o�b�t�@
	DSBUFFERDESC Sound_Buffer_Config;				//	�o�b�t�@�̐ݒ�\����
	HMMIO MultiMedia_Input_Output_Handle = NULL;	//	�}���`���f�B�AI/O�n���h��
	MMIOINFO MultiMedia_Input_Output_Data;			//	�}���`���f�B�AI/O�̃f�[�^�\����
	MMRESULT MultiMedia_Input_Output_Result = NULL;	//	�}���`���f�B�A�������ʂ��i�[����ϐ�
	MMCKINFO Riff_Chunk;							//	�`�����N�f�[�^�̍\����
	MMCKINFO Format_Chunk;							//	�`�����N�f�[�^�̍\����
	MMCKINFO Data_Chunk;							//	�`�����N�f�[�^�̍\����
	DWORD Data_Size = NULL;							//	�f�[�^�̃T�C�Y���i�[����ϐ�
	WAVEFORMATEX Pulse_Code_Modulation;				//	�����f�[�^�̃t�H�[�}�b�g�\����
	LPVOID Secondary_Buffer = NULL;					//	�Z�J���_���o�b�t�@�̃f�[�^�̏������ݐ�A�h���X
	DWORD Secondary_Buffer_Size = NULL;				//	�Z�J���_���o�b�t�@�̃T�C�Y

	// �P�D�}���`���f�B�AI/O�n���h�������ɉ����t�@�C�����J��
	memset	//	memset�֐��F�w�肳�ꂽ�|�C���^���w���I�u�W�F�N�g�̐擪����A�w�肳�ꂽ�o�C�g�����ɁA�w�肵�������f�[�^���������ނ͂��炫������( �|�C���^���w���Ă��郁��������e"1"�o�C�g���Ƃɕ������Z�b�g���� )
	(
		&MultiMedia_Input_Output_Data,	//	�Z�b�g��̃������u���b�N�A�h���X ( �Z�b�g����̈�( �|�C���^ / ������ )
		0,								//	�Z�b�g���̃������u���b�N�A�h���X ( �Z�b�g����l )
		sizeof(MMIOINFO)				//	�Z�b�g������A�Z�b�g��ɃZ�b�g���郁�����̃u���b�N�T�C�Y���w��	( �Z�b�g����T�C�Y )
	);
	MultiMedia_Input_Output_Handle = mmioOpen	//	mmioOpen�֐��F���o�͂̃o�b�t�@�����O���������邩�A���o�͂��o�b�t�@�����O���ăt�@�C�����J���B�J�����Ƃ��ł���t�@�C���́A�W���t�@�C���E�������t�@�C���E�܂��̓J�X�^���̊i�[�V�X�e��
	(
		(LPSTR)Sound_File[Sound_Index],	//	�J���t�@�C���̃t�@�C������������������̃A�h���X���w��
		&MultiMedia_Input_Output_Data,	//	mmioOpen�֐��Ŏg����ǉ��̃p�����[�^���������AMMIOINFO�\���̂̃A�h���X���w��
		MMIO_READ						//	�I�[�v������̂��߂̃t���O���w��( MMIO_READ�F�t�@�C����ǂݎ���p�Ƃ��ĊJ�� )
	);
	if (!MultiMedia_Input_Output_Handle)
	{
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_SOUND_FILE_INPUT);
	}

	// �Q�D�t�@�C���̉��( 1 ) RIFF�`�����N�̌���
	// �������[�h���w��
	Riff_Chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');	//	mmioFOURCC�֐��F�S�̕������S�����̃R�[�h�ɕϊ����܂�( .wav�t�@�C����"FOURCC"�Ƃ����S�����̕�����Ń`�����N�̎�ނ���ʂ��Ă��� )
															//	mmioDescend�֐��͊�{�I�ɂ��̕�������Q�Ƃ��āA��������`�����N�𔻒f���邽�߁A�����ݒ肵�Ă����K�v������
	// �L�[���[�h��ΏۂɌ���
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend�֐��FmmioOpen�֐��ŊJ����RIFF�t�@�C���̃`�����N�ɐi������B�܂��A�w�肳�ꂽ�`�����N���������邱�Ƃ��ł���
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���RIFF�t�@�C���̃t�@�C���n���h�����w��
		&Riff_Chunk,					//	�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��
		NULL,							//	��������`�����N�̐e�����ʂ���F�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��B�e�`�����N���w�肳��Ă��Ȃ��ꍇ�A���̃p�����[�^��"NULL"�ɐݒ肷��
		MMIO_FINDRIFF					//	�����t���O���w��( MMIO_FINDRIFF�F�`�����N���ʎq��"RIFF"�ŁA�w�肳�ꂽ�t�H�[���^�C�v�̃`�����N���������� )
	);
	// �����Ɏ��s������ُ�I��
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CHUNKS);
	}

	// �R�D�t�@�C���̉��( 2 ) �t�H�[�}�b�g�`�����N�̌���
	// �������[�h���w��
	Format_Chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');	//	mmioFOURCC�֐��F�S�̕������S�����̃R�[�h�ɕϊ����܂�( .wav�t�@�C����"FOURCC"�Ƃ����S�����̕�����Ń`�����N�̎�ނ���ʂ��Ă��� )
														//	mmioDescend�֐��͊�{�I�ɂ��̕�������Q�Ƃ��āA��������`�����N�𔻒f���邽�߁A�����ݒ肵�Ă����K�v������
	// �L�[���[�h��ΏۂɌ���
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend�֐��FmmioOpen�֐��ŊJ�����t�H�[�}�b�g�t�@�C���̃`�����N�ɐi������B�܂��A�w�肳�ꂽ�`�����N���������邱�Ƃ��ł���
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���t�H�[�}�b�g�t�@�C���̃t�@�C���n���h�����w��
		&Format_Chunk,					//	�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��
		&Riff_Chunk,					//	��������`�����N�̐e�����ʂ���F�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��B�e�`�����N���w�肳��Ă��Ȃ��ꍇ�A���̃p�����[�^��"NULL"�ɐݒ肷��
		MMIO_FINDCHUNK					//	�����t���O���w��( MMIO_FINDCHUNK�F�w�肳�ꂽ�`�����N���ʎq�̃`�����N���������܂� )
	);
	// �����Ɏ��s������ُ�I��
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CHUNKS);
	}

	// �����������ɓǂݍ��ݏ���
	Data_Size = mmioRead	//	mmioRead�֐��FmmioOpen�֐��ŊJ�����t�@�C������A�w�肳�ꂽ�o�C�g����ǂݎ��
	(
		MultiMedia_Input_Output_Handle,	//	�ǂݎ��t�@�C���̃t�@�C���n���h�����w��
		(HPSTR)&Pulse_Code_Modulation,	//	�t�@�C������ǂݎ��ꂽ�f�[�^������o�b�t�@�̃A�h���X���w��
		Format_Chunk.cksize				//	�t�@�C������ǂݎ��o�C�g�����w��
	);
	// �ǂݍ��݂Ɏ��s������ُ�I��
	if (Data_Size != Format_Chunk.cksize)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_LOAD_SOUND_FILE_HANDLE);
	}

	mmioAscend	//	mmioAscend�֐��FmmioDescend�֐��Ői�������A�܂���mmioCreateChunk�֐��ō쐬����RIFF�t�@�C���̃`�����N����ޏo����
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���RIFF�t�@�C���̃t�@�C���n���h�����w��
		&Format_Chunk,					//	mmioDescend�֐��܂��́AmmioCreateChunk�֐��Œl���������܂�Ă���A�v���P�[�V������`��MMCKINFO�\���̂̃A�h���X���w��
		0								//	�\�񂳂�Ă���̂ŁA"0"���w��
	); 

	// �S�D�t�@�C���̉��( 3 ) �f�[�^�`�����N�̌���
	// �������[�h���w��
	Data_Chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');	//	mmioFOURCC�֐��F�S�̕������S�����̃R�[�h�ɕϊ����܂�( .wav�t�@�C����"FOURCC"�Ƃ����S�����̕�����Ń`�����N�̎�ނ���ʂ��Ă��� )
														//	mmioDescend�֐��͊�{�I�ɂ��̕�������Q�Ƃ��āA��������`�����N�𔻒f���邽�߁A�����ݒ肵�Ă����K�v������
	MultiMedia_Input_Output_Result = mmioDescend		//	mmioDescend�֐��FmmioOpen�֐��ŊJ�����t�H�[�}�b�g�t�@�C���̃`�����N�ɐi������B�܂��A�w�肳�ꂽ�`�����N���������邱�Ƃ��ł���
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���t�H�[�}�b�g�t�@�C���̃t�@�C���n���h�����w��
		&Data_Chunk,					//	�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��
		&Riff_Chunk,					//	��������`�����N�̐e�����ʂ���F�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��B�e�`�����N���w�肳��Ă��Ȃ��ꍇ�A���̃p�����[�^��"NULL"�ɐݒ肷��
		MMIO_FINDCHUNK					//	�����t���O���w��( MMIO_FINDCHUNK�F�w�肳�ꂽ�`�����N���ʎq�̃`�����N���������܂� )
	);
	// �����Ɏ��s������ُ�I��
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CHUNKS);
	}

	// �T�D�f�[�^�̓ǂݍ���
	// �|�C���^�ϐ��錾�F������
	char *Data = new char[Data_Chunk.cksize];	//	�K�v�ȑ傫���̗̈���m�ۂ���

	Data_Size = mmioRead	//	mmioRead�֐��FmmioOpen�֐��ŊJ�����t�@�C������A�w�肳�ꂽ�o�C�g����ǂݎ��
	(
		MultiMedia_Input_Output_Handle,	//	�ǂݎ��t�@�C���̃t�@�C���n���h�����w��
		(HPSTR)Data,					//	�t�@�C������ǂݎ��ꂽ�f�[�^������o�b�t�@�̃A�h���X���w��
		Data_Chunk.cksize				//	�t�@�C������ǂݎ��o�C�g�����w��
	);
	// �f�[�^�̓ǂݍ��݂Ɏ��s������ُ�I��
	if (Data_Size != Data_Chunk.cksize)
	{
		// �폜
		delete[] Data;

		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_LOAD_SOUND_FILE_HANDLE);
	}

	// �U�D�����f�[�^��ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&Sound_Buffer_Config, sizeof(DSBUFFERDESC));	//	ZeroMemory�}�N���F�w�肵���ϐ��̒��g��"0"�N���A����}�N��

	// �e��ݒ�
	// DSBUFFERDESC�F�V�����o�b�t�@�I�u�W�F�N�g�̓������L�q����
	Sound_Buffer_Config.dwSize = sizeof(DSBUFFERDESC);	//	�\���̂̃T�C�Y( �P�ʁFbyte )���w��F�\���̂��g���O�ɁA���̃����o�����������Ȃ���΂Ȃ�Ȃ�
	Sound_Buffer_Config.dwFlags =						//	�o�b�t�@�̔\�͂������t���O
		(
			DSBCAPS_GETCURRENTPOSITION2 |
			DSBCAPS_GLOBALFOCUS |
			DSBCAPS_LOCDEFER |
			DSBCAPS_CTRLFX |
			DSBCAPS_CTRLVOLUME
		);
	Sound_Buffer_Config.dwBufferBytes = Data_Size;				//	�V�����o�b�t�@�̃T�C�Y( �P�ʁFbyte )���w��
	Sound_Buffer_Config.lpwfxFormat = &Pulse_Code_Modulation;	//	�o�b�t�@�̃E�F�[�u�t�H�[���t�H�[�}�b�g���w��

	// �����o�b�t�@���쐬
	if (FAILED(Sound_State.Direct_Sound->CreateSoundBuffer	//	CreateSoundBuffer�֐��F�T���v�����O�I�[�f�B�I���Ǘ����邽�߂ɁA�T�E���h�o�b�t�@�I�u�W�F�N�g���쐬����
	(
		&Sound_Buffer_Config,	//	�쐬����T�E���h�o�b�t�@���L�q����Ă���"DSBUFFERDESC"�\���̂̃A�h���X
		&Sound_Base_Buffer,		//	�V�����o�b�t�@�I�u�W�F�N�g��"IDirectSoundBuffer"�C���^�[�t�F�C�X���󂯎��ϐ��̃A�h���X
		NULL					//	�R���|�[�l���g�I�u�W�F�N�g���f��( COM )�W���ɑ΂��鐧��I�u�W�F�N�g��IUnknown�C���^�[�t�F�C�X�̃A�h���X�ւ̃|�C���^�B�C���^�[�t�F�C�X���W������Ă��Ȃ��ꍇ�ɂ�"NULL" // �ʏ�A�Ăяo������"NULL"��n��
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_CREATE_SOUND_BUFFER);
	}

	// �T�E���h�o�b�t�@�̎��o��
	if (FAILED(Sound_Base_Buffer->QueryInterface	//	QueryInterface�֐��F�I�u�W�F�N�g������̃R���|�[�l���g�I�u�W�F�N�g���f��( COM )�C���^�[�t�F�C�X���T�|�[�g���Ă��邩�ǂ����𔻕ʂ���
													//						�C���^�[�t�F�C�X���T�|�[�g����Ă���ꍇ�A�V�X�e���̓I�u�W�F�N�g�̎Q�ƃJ�E���g�𑝂₵�A�A�v���P�[�V�����͂��̃C���^�[�t�F�C�X�������Ɏg����
	(
		IID_IDirectSoundBuffer8,	//	�v������C���^�[�t�F�C�X�̎Q�Ǝ��ʎq
		(LPVOID*)&Sound_Buffer		//	�ړI�̃C���^�[�t�F�C�X���T�|�[�g����Ă���ꍇ�ɁA�C���^�[�t�F�C�X�ւ̃|�C���^���i�[�����|�C���^�ϐ��̃A�h���X
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_GET_SOUND_INTERFACE);
	}

	// �T�E���h�o�b�t�@���o����A�����o�b�t�@���폜
	//Start_Critical_Section();
	SAFE_RELEASE(Sound_Base_Buffer);
	//End_Critical_Section();

	// �V�D�p�ӂ����Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �������݉\�ɂ��邽�߁A�o�b�t�@�����b�N
	if (FAILED(Sound_Buffer->Lock	//	Lock�֐��F�f�b�h���b�N�Ȃ��ł��ׂĂ̈��������b�N����
	(
		0,
		0,
		&Secondary_Buffer,
		&Secondary_Buffer_Size,
		NULL,
		NULL,
		DSBLOCK_ENTIREBUFFER
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		//Message_Window(MESSAGE_WINDOW_TYPE_ERROR_ARGUMENT_LOCK);
	}

	// �f�[�^�̓]��
	memcpy	//	memcpy�֐��F��2����( �R�s�[�� )����A��3����( �w��T�C�Y )���A��1����( �R�s�[�� )�փ��������R�s�[����
	(
		Secondary_Buffer,		//	�R�s�[��̃������u���b�N�A�h���X
		Data,					//	�R�s�[���̃������u���b�N�A�h���X
		Secondary_Buffer_Size	//	�R�s�[������A�R�s�[��ɃR�s�[���郁�����̃u���b�N�T�C�Y���w��
	);

	// ���̓ǂݍ��ݗ̈���폜
	delete[] Data;

	// �o�b�t�@�̃��b�N������
	Sound_Buffer->Unlock	//	Unlock�֐��F���R�[�h�̃��b�N����������
	(
		Secondary_Buffer,
		Secondary_Buffer_Size,
		0,
		0
	);

	// �Z�J���_���o�b�t�@��߂�l�Ƃ��ĕԂ�
	return Sound_Buffer;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - �Đ�
//====================================================================================================================================================================================
#pragma region Play
//====================================================================================================================================================================================
// �T�E���h�̍Đ�
// �֐����Fvoid Play_Sound
// �߂�l�Fvoid
// ���� 1�Fint
// ���� 2�Fint
//====================================================================================================================================================================================
void Play_Sound(int Sound_Index, int Play_Method)
{
	// Sound_Flag�F"1" = ( E_DS8_FLAG_LOOP )�Ȃ烋�[�v�Đ�
	if (!Sound_State.Pause_Flag[Sound_Index])
	{
		Sound_State.Sound_Buffer[Sound_Index]->SetCurrentPosition(0);
		Sound_State.Sound_Buffer[Sound_Index]->Play(0, 0, Play_Method);
	}
	else
	{
		Sound_State.Sound_Buffer[Sound_Index]->SetCurrentPosition(Sound_State.Play_Position[Sound_Index]);
		Sound_State.Sound_Buffer[Sound_Index]->Play(0, 0, Play_Method);
	}

	Sound_State.Play_Method[Sound_Index] = Play_Method;
	Sound_State.Play_Flag[Sound_Index] = true;
	Sound_State.Pause_Flag[Sound_Index] = false;

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - �ꎞ��~
//====================================================================================================================================================================================
#pragma region Pause
//====================================================================================================================================================================================
// �T�E���h�̈ꎞ��~
// �֐����Fvoid Pause_Sound
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Pause_Sound(int Sound_Index)
{
	if (Sound_State.Play_Flag[Sound_Index])
	{
		Sound_State.Pause_Flag[Sound_Index] = true;
		Get_Play_Position_Sound(Sound_Index);
	}
	else
	{
		Sound_State.Pause_Flag[Sound_Index] = false;
	}

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - ��~
//====================================================================================================================================================================================
#pragma region Stop
//====================================================================================================================================================================================
// �T�E���h�̒�~
// �֐����Fvoid Stop_Sound
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Stop_Sound(int Sound_Index)
{
	// �ϐ��錾�F������
	DWORD Status = NULL;	//	�X�e�[�^�X

	Sound_State.Sound_Buffer[Sound_Index]->GetStatus(&Status);	//	GetStatus�֐��F�w�肳�ꂽCFile�I�u�W�F�N�g�C���X�^���X�A�܂��͎w�肳�ꂽ�t�@�C���p�X�Ɋ֘A�����X�e�[�^�X�����擾���܂�
	
	// �T�E���h�Đ���
	if (Status & DSBSTATUS_PLAYING)
	{
		Sound_State.Sound_Buffer[Sound_Index]->Stop();	//	Stop�֐��F���݂̕\�����̎��s�𒆒f����( ���e�Ƃ��ẮA"Pause"�̂悤�Ȃ��� )
	}

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - ����
//====================================================================================================================================================================================
#pragma region Check
//====================================================================================================================================================================================
// �T�E���h�̍Đ���Ԃ𒲍�
// �֐����Fbool Check_Play_Flag_Sound
// �߂�l�Fbool
// ���� 1�Fint
//====================================================================================================================================================================================
bool Check_Play_Flag_Sound(int Sound_Index)
{
	// �ϐ��錾�F������
	DWORD Status = NULL;	//	�X�e�[�^�X

	Sound_State.Sound_Buffer[Sound_Index]->GetStatus(&Status);	//	GetStatus�֐��F�w�肳�ꂽCFile�I�u�W�F�N�g�C���X�^���X�A�܂��͎w�肳�ꂽ�t�@�C���p�X�Ɋ֘A�����X�e�[�^�X�����擾���܂�
	
	// �T�E���h�Đ���
	if (Status & DSBSTATUS_PLAYING)
	{
		return true;
	}

	return false;
}

//====================================================================================================================================================================================
// �T�E���h�̍Đ���Ԃ𒲍�( �S�� )
// �֐����Fvoid Check_Play_Flag_All_Sound
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Check_Play_Flag_All_Sound(void)
{
	// �ϐ��錾�F������
	DWORD Status = NULL;	//	�X�e�[�^�X

	for (int i = 0; i < SOUND_MAX; i++)
	{
		Sound_State.Sound_Buffer[i]->GetStatus(&Status);	//	GetStatus�֐��F�w�肳�ꂽCFile�I�u�W�F�N�g�C���X�^���X�A�܂��͎w�肳�ꂽ�t�@�C���p�X�Ɋ֘A�����X�e�[�^�X�����擾���܂�
		
		if (Status & DSBSTATUS_PLAYING)
		{
			Sound_State.Play_Flag[i] = true;
		}
		else
		{
			Sound_State.Play_Flag[i] = false;
		}

		Status = NULL;
	}

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - �ݒ�
//====================================================================================================================================================================================
#pragma region Set
//====================================================================================================================================================================================
// �T�E���h�̈ꎞ��~�ݒ�
// �֐����Fvoid Set_Pause_Sound
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Set_Pause_Sound(void)
{
	for (int i = 0; i < SOUND_MAX; i++)
	{
		//switch (i)
		//{
		////case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
		////case SOUND_TYPE_SOUND_EFFECT_003_GAME_THE_TOPOS:
		////case SOUND_TYPE_SOUND_EFFECT_004_GAME_VOEZ:
		////case SOUND_TYPE_SOUND_EFFECT_005_GAME_LUMINA:
		////case SOUND_TYPE_SOUND_EFFECT_006_GAME_DIVISION:
		////case SOUND_TYPE_SOUND_EFFECT_008_GAME_MENU:
		////case SOUND_TYPE_SOUND_EFFECT_009_GAME_MENU_ENTER:
		////case SOUND_TYPE_SOUND_EFFECT_010_GAME_MENU_BACK:
		//	Pause_Sound(i);
		//	Stop_Sound(i);
		//	continue;
		//	break;
		//default:
		//	continue;
		//	break;
		//}
	}

	return;
}

//====================================================================================================================================================================================
// �T�E���h�̍Đ��ĊJ�ݒ�
// �֐����Fvoid Set_Re_Play_Sound
// �߂�l�Fvoid
//====================================================================================================================================================================================
void Set_Re_Play_Sound(void)
{
	for (int i = 0; i < SOUND_MAX; i++)
	{
		// �����R���e�B�j���[
		if (!Sound_State.Pause_Flag[i])
		{
			continue;
		}

		//switch (i)
		//{
		//case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
		//case SOUND_TYPE_SOUND_EFFECT_003_GAME_THE_TOPOS:
		//case SOUND_TYPE_SOUND_EFFECT_004_GAME_VOEZ:
		//case SOUND_TYPE_SOUND_EFFECT_005_GAME_LUMINA:
		//case SOUND_TYPE_SOUND_EFFECT_006_GAME_DIVISION:
		//case SOUND_TYPE_SOUND_EFFECT_008_GAME_MENU:
		//case SOUND_TYPE_SOUND_EFFECT_009_GAME_MENU_ENTER:
		//case SOUND_TYPE_SOUND_EFFECT_010_GAME_MENU_BACK:
		//	Play_Sound(i, Sound_State.Play_Method[i]);
		//	continue;
		//	break;
		//default:
		//	continue;
		//	break;
		//}
	}

	return;
}

//====================================================================================================================================================================================
// �T�E���h�̃t�F�[�h�ݒ�
// �֐����Fvoid Set_Sound_Fade
// �߂�l�Fvoid
// ���� 1�Fint
// ���� 2�Fint
//====================================================================================================================================================================================
void Set_Sound_Fade(int Sound_Index, int Sound_Fade_Type)
{
	if (Sound_Fade_Type == SOUND_FADE_TYPE_NONE)
	{
		//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);
	}
	else
	{
		//Set_Switch(SWITCH_TYPE_SOUND_FADE, true);
	}

	Sound_State.Fade_Type[Sound_Index] = Sound_Fade_Type;
	Sound_State.Fade_Switch[Sound_Index] = true;

	return;
}

//====================================================================================================================================================================================
// �T�E���h�̉��ʐݒ�
// �֐����Fvoid Set_Sound_Volume
// �߂�l�Fvoid
// ���� 1�Fint
// ���� 2�Fint
//====================================================================================================================================================================================
void Set_Sound_Volume(int Sound_Index, int Sound_Volume_Type)
{
	Set_Sound_Fade(Sound_Index, SOUND_FADE_TYPE_NONE);

	switch (Sound_Volume_Type)
	{
	case SOUND_VOLUME_TYPE_LOWEST:
		Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Min;
		break;
	case SOUND_VOLUME_TYPE_HIGHEST:
		Sound_State.Volume[Sound_Index] = Sound_State.Setting_Volume.Max;
		break;
	default:
		break;
	}

	// ���ʂ̐ݒ�
	Sound_State.Sound_Buffer[Sound_Index]->SetVolume(Sound_State.Volume[Sound_Index]);

	return;
}
#pragma endregion
//====================================================================================================================================================================================
// �̈� - �擾
//====================================================================================================================================================================================
#pragma region Get
//====================================================================================================================================================================================
// �T�E���h�̍Đ��ʒu�̎擾
// �֐����Fvoid Get_Play_Position_Sound
// �߂�l�Fvoid
// ���� 1�Fint
//====================================================================================================================================================================================
void Get_Play_Position_Sound(int Sound_Index)
{
	Sound_State.Sound_Buffer[Sound_Index]->GetCurrentPosition(&Sound_State.Play_Position[Sound_Index], NULL);

	return;
}

//====================================================================================================================================================================================
// �T�E���h�̎擾
// �֐����FSOUND *Get_Sound
// �߂�l�FSOUND
//====================================================================================================================================================================================
SOUND *Get_Sound(void)
{
	return &Sound_State;
}
#pragma endregion
////====================================================================================================================================================================================
//// �̈� - �f�o�b�O
////====================================================================================================================================================================================
//#pragma region Debug
//#ifdef _DEBUG
////====================================================================================================================================================================================
//// �T�E���h�̃f�o�b�O�`��
//// �֐����Fvoid Draw_Debug_Sound
//// �߂�l�Fvoid
//// ���� 1�FDEBUG*
////====================================================================================================================================================================================
//void Draw_Debug_Sound(DEBUG *Debug)
//{
//	// �������^�[��
//	if ((!Debug->Switch) || (Debug->Type != DEBUG_TYPE_SOUND))
//	{
//		return;
//	}
//
//	// �f�o�b�O�^�C�v
//	Print_Debug("==========| �T�E���h |========== \n\n");
//	// �ݒ艹��
//	Print_Debug("Setting_Volume.Min�F%d \n", Sound_State.Setting_Volume.Min);
//	Print_Debug("Setting_Volume.Max�F%d \n\n", Sound_State.Setting_Volume.Max);
//	// �Đ��t���O�E�T�E���h����
//	switch (Get_Progress())
//	{
//	case PROGRESS_TYPE_OPENING:
//		Draw_Debug_Sound_Opening();
//		break;
//	case PROGRESS_TYPE_TITLE:
//		Draw_Debug_Sound_Title();
//		break;
//	case PROGRESS_TYPE_GAME:
//		Draw_Debug_Sound_Game();
//		break;
//	case PROGRESS_TYPE_ENDING:
//		Draw_Debug_Sound_Ending();
//		break;
//	default:
//		break;
//	}
//	// �I��
//	Print_Debug("==========| �I�� |==========");
//
//	return;
//}
//
////====================================================================================================================================================================================
//// �T�E���h( �I�[�v�j���O )�̃f�o�b�O�`��
//// �֐����Fvoid Draw_Debug_Sound_Opening
//// �߂�l�Fvoid
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Opening(void)
//{
//	// �ϐ��錾�F������
//	char Debug_Play_Flag[SOUND_MAX][6];		//	�t���O����
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	�t���O����
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	�t���O����
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// �����R���e�B�j���[
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// �Đ��t���O
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// �ꎞ��~�t���O
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// �t�F�[�h�X�C�b�`
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_SOUND_EFFECT_000_OPENING_NOISE:
//			Print_Debug("[ SE_000 - NOISE ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_OPENING_RECORD_NOISE:
//			Print_Debug("[ SE_001 - RECORD_NOISE ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//
////====================================================================================================================================================================================
//// �T�E���h( �^�C�g�� )�̃f�o�b�O�`��
//// �֐����Fvoid Draw_Debug_Sound_Title
//// �߂�l�Fvoid
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Title(void)
//{
//	// �ϐ��錾�F������
//	char Debug_Play_Flag[SOUND_MAX][6];		//	�t���O����
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	�t���O����
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	�t���O����
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// �����R���e�B�j���[
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// �Đ��t���O
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// �ꎞ��~�t���O
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// �t�F�[�h�X�C�b�`
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_BACKGROUND_MUSIC_000_TITLE_AMBIENT:
//			Print_Debug("[ BGM_000 - AMBIENT ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_000_TITLE_DECISION:
//			Print_Debug("[ SE_000 - DECISION ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_TITLE_SELECT:
//			Print_Debug("[ SE_001 - SELECT ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_002_TITLE_NEXT:
//			Print_Debug("[ SE_002 - NEXT ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//
////====================================================================================================================================================================================
//// �T�E���h( �Q�[�� )�̃f�o�b�O�`��
//// �֐����Fvoid Draw_Debug_Sound_Game
//// �߂�l�Fvoid
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Game(void)
//{
//	// �ϐ��錾�F������
//	char Debug_Play_Flag[SOUND_MAX][6];		//	�t���O����
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	�t���O����
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	�t���O����
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// �����R���e�B�j���[
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// �Đ��t���O
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// �ꎞ��~�t���O
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// �t�F�[�h�X�C�b�`
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_BACKGROUND_MUSIC_000_GAME_FOREST:
//			Print_Debug("[ BGM_000 - FOREST ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_BACKGROUND_MUSIC_001_GAME_AMBIENT:
//			Print_Debug("[ BGM_001 - AMBIENT ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
//			Print_Debug("[ BGM_002 - PARTICLE ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_000_GAME_BELL:
//			Print_Debug("[ SE_000 - BELL ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_GAME_WALK:
//			Print_Debug("[ SE_001 - WALK ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_002_GAME_RUN:
//			Print_Debug("[ SE_002 - RUN ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_003_GAME_THE_TOPOS:
//			Print_Debug("[ SE_003 - THE_TOPOS ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_004_GAME_VOEZ:
//			Print_Debug("[ SE_004 - VOEZ ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_005_GAME_LUMINA:
//			Print_Debug("[ SE_005 - LUMINA ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_006_GAME_DIVISION:
//			Print_Debug("[ SE_006 - DEVISION ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_007_GAME_PAUSE:
//			Print_Debug("[ SE_007 - PAUSE ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_008_GAME_MENU:
//			Print_Debug("[ SE_008 - MENU ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_009_GAME_MENU_ENTER:
//			Print_Debug("[ SE_009 - MENU_ENTER ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_010_GAME_MENU_BACK:
//			Print_Debug("[ SE_010 - MENU_BACK ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_011_GAME_TUTORIAL_SUCCESS:
//			Print_Debug("[ SE_011 - TUTORIAL_SUCCESS ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_012_GAME_TUTORIAL_CHECK:
//			Print_Debug("[ SE_012 - TUTORIAL_CHECK ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_013_GAME_TUTORIAL_PAPER:
//			Print_Debug("[ SE_013 - TUTORIAL_PAPER ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//
////====================================================================================================================================================================================
//// �T�E���h( �G���f�B���O )�̃f�o�b�O�`��
//// �֐����Fvoid Draw_Debug_Sound_Ending
//// �߂�l�Fvoid
////====================================================================================================================================================================================
//void Draw_Debug_Sound_Ending(void)
//{
//	// �ϐ��錾�F������
//	char Debug_Play_Flag[SOUND_MAX][6];		//	�t���O����
//	char Debug_Pause_Flag[SOUND_MAX][6];	//	�t���O����
//	char Debug_Fade_Switch[SOUND_MAX][6];	//	�t���O����
//
//	for (int i = 0; i < SOUND_MAX; i++)
//	{
//		// �����R���e�B�j���[
//		if (!Sound_State.Play_Flag[i])
//		{
//			continue;
//		}
//
//		// �Đ��t���O
//		if (Sound_State.Play_Flag[i])
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Play_Flag[i], "%s", "false");
//		}
//		// �ꎞ��~�t���O
//		if (Sound_State.Pause_Flag[i])
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Pause_Flag[i], "%s", "false");
//		}
//		// �t�F�[�h�X�C�b�`
//		if (Sound_State.Fade_Switch[i])
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "true");
//		}
//		else
//		{
//			sprintf(Debug_Fade_Switch[i], "%s", "false");
//		}
//
//		switch (i)
//		{
//		case SOUND_TYPE_SOUND_EFFECT_000_ENDING_SPLASH:
//			Print_Debug("[ SE_000 - SPLASH ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_001_ENDING_DEEP:
//			Print_Debug("[ SE_001 - DEEP ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		case SOUND_TYPE_SOUND_EFFECT_002_ENDING_SIGNAL:
//			Print_Debug("[ SE_002 - SIGNAL ] \n");
//			Print_Debug("Play_Method�F%d \n", Sound_State.Play_Method[i]);
//			Print_Debug("Play_Position�F%d \n", Sound_State.Play_Position[i]);
//			Print_Debug("Fade_Type�F%d \n", Sound_State.Fade_Type[i]);
//			Print_Debug("Volume�F%d \n", Sound_State.Volume[i]);
//			Print_Debug("Play_Flag�F%s \n", Debug_Play_Flag[i]);
//			Print_Debug("Pause_Flag�F%s \n", Debug_Pause_Flag[i]);
//			Print_Debug("Fade_Switch�F%s \n", Debug_Fade_Switch[i]);
//			Print_Debug("\n");
//			continue;
//			break;
//		default:
//			continue;
//			break;
//		}
//	}
//
//	return;
//}
//#endif
//#pragma endregion