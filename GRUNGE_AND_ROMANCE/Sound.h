//====================================================================================================================================================================================
// 概要
// ファイル名：Sound.h
// コーディングフォント：Ricty Diminished( 16サイズ )
// 作成者：HAL東京 GP-11B-341 07 亀岡竣介
// 作成日：2018/12/10
//====================================================================================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//====================================================================================================================================================================================
// インクルード
//====================================================================================================================================================================================

//====================================================================================================================================================================================
// マクロ定義
//====================================================================================================================================================================================
#define SOUND_FILE_AGONY ("data/SOUND/SE/Item.wav")	//	サウンドファイル
#define SOUND_FADE_VALUE (25)					//	サウンドのフェード値
#define SOUND_MAX (SOUND_TYPE_MAX)				//	サウンドの最大数
#define SOUND_VOLUME_MIN (-10000)				//	サウンドの音量最小値
#define SOUND_VOLUME_MAX (0)					//	サウンドの音量最大値
//====================================================================================================================================================================================
// 列挙型定義
//====================================================================================================================================================================================
enum SOUND_TYPE
{
	SOUND_TYPE_AGONY,	//	断末魔
	SOUND_TYPE_MAX,		//	定数の最大値
};
enum SOUND_PLAY_TYPE
{
	SOUND_PLAY_TYPE_PLAY,	//	再生
	SOUND_PLAY_TYPE_LOOP,	//	ループ再生
	SOUND_PLAY_TYPE_MAX,	//	定数の最大値
};
enum SOUND_FADE_TYPE
{
	SOUND_FADE_TYPE_NONE,		//	フェード無効
	SOUND_FADE_TYPE_FADE_IN,	//	フェードイン
	SOUND_FADE_TYPE_FADE_OUT,	//	フェードアウト
	SOUND_FADE_TYPE_MAX,		//	定数の最大値
};
enum SOUND_VOLUME_TYPE
{
	SOUND_VOLUME_TYPE_LOWEST,	//	最小
	SOUND_VOLUME_TYPE_HIGHEST,	//	最大
	SOUND_VOLUME_TYPE_MAX,		//	定数の最大値
};
//====================================================================================================================================================================================
// 構造体定義
//====================================================================================================================================================================================
typedef struct
{
	int Max = DSBVOLUME_MAX;	//	最大音量
	int Min = DSBVOLUME_MIN;	//	最小音量
}SETTING_VOLUME;
typedef struct
{
	IDirectSound8 *Direct_Sound = NULL;				//	サウンドのオブジェクト
	LPDIRECTSOUNDBUFFER8 Sound_Buffer[SOUND_MAX];	//	サウンド
	SETTING_VOLUME Setting_Volume;					//	設定音量
	DWORD Play_Position[SOUND_MAX];					//	再生位置
	DWORD Play_Method[SOUND_MAX];					//	再生方法
	int Fade_Type[SOUND_MAX];						//	フェードタイプ
	bool Fade_Switch[SOUND_MAX];					//	フェードスイッチ
	bool Play_Flag[SOUND_MAX];						//	再生フラグ
	bool Pause_Flag[SOUND_MAX];						//	一時停止フラグ
	int Volume[SOUND_MAX] =							//	音量
	{
		DSBVOLUME_MAX,	//	SOUND_TYPE_AGONY
	};
}SOUND;
//====================================================================================================================================================================================
// プロトタイプ宣言
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