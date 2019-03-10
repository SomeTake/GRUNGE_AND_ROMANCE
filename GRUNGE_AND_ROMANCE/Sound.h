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
#define SOUND_FILE_ATTACK_ITEM ("data/SOUND/SE/Attack_Item_Extinction.wav")	//	サウンドファイル
#define SOUND_FILE_ATTACK_KICK ("data/SOUND/SE/Attack_Kick_Jeize.wav")		//	サウンドファイル
#define SOUND_FILE_ATTACK_PUNCH ("data/SOUND/SE/Attack_Punch_Foise.wav")	//	サウンドファイル
#define SOUND_FILE_ITEM_PICK ("data/SOUND/SE/Item_Pick.wav")				//	サウンドファイル
#define SOUND_FILE_KNOCK_DOWN ("data/SOUND/SE/Knock_Down.wav")				//	サウンドファイル
#define SOUND_FILE_KNOCK_DOWN_BOSS ("data/SOUND/SE/Knock_Down_Boss.wav")	//	サウンドファイル
#define SOUND_FADE_VALUE (25)												//	サウンドのフェード値
#define SOUND_MAX (SOUND_TYPE_MAX)											//	サウンドの最大数
#define SOUND_VOLUME_MIN (-10000)											//	サウンドの音量最小値
#define SOUND_VOLUME_MAX (0)												//	サウンドの音量最大値
//====================================================================================================================================================================================
// 列挙型定義
//====================================================================================================================================================================================
enum SOUND_TYPE
{
	SOUND_TYPE_ATTACK_ITEM,		//	与ダメ：アイテム
	SOUND_TYPE_ATTACK_KICK,		//	与ダメ：キック
	SOUND_TYPE_ATTACK_PUNCH,	//	与ダメ：パンチ
	SOUND_TYPE_ITEM_PICK,		//	アイテム取得
	SOUND_TYPE_KNOCK_DOWN,		//	ノックダウン
	SOUND_TYPE_KNOCK_DOWN_BOSS,	//	ノックダウン：ボス
	SOUND_TYPE_MAX,				//	定数の最大値
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
		DSBVOLUME_MAX,	//	SOUND_TYPE_ATTACK_ITEM
		DSBVOLUME_MAX,	//	SOUND_TYPE_ATTACK_KICK
		DSBVOLUME_MAX,	//	SOUND_TYPE_ATTACK_PUNCH
		DSBVOLUME_MAX,	//	SOUND_TYPE_ITEM_PICK
		DSBVOLUME_MAX,	//	SOUND_TYPE_KNOCK_DOWN
		DSBVOLUME_MAX,	//	SOUND_TYPE_KNOCK_DOWN_BOSS
	};
}SOUND;
//====================================================================================================================================================================================
// プロトタイプ宣言
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