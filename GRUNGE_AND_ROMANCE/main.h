//=============================================================================
//
// メイン処理 [main.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include <time.h>
#include <dshow.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <stdio.h>

// Effekseer
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include "dinput.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

#if _DEBUG
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX9.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "Release/Effekseer.lib" )
#pragma comment(lib, "Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "Release/EffekseerSoundXAudio2.lib" )
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define MY_VERTEX_FVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define SCREEN_WIDTH	(1920)											// ウインドウの幅
#define SCREEN_HEIGHT	(1080)											// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)								// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)								// ウインドウの中心Ｙ座標

#define TIME_PER_FRAME	(1/60.0f)										// 1/60秒

#define	NUM_VERTEX		(4)												// 頂点数
#define	NUM_POLYGON		(2)												// ポリゴン数

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(5000.0f)										// ビュー平面のFarZ値
#define MAX_SEPARATE	(2)												// 画面分割最大数

// デストラクタ
#define SAFE_DELETE(object)			{if(object){delete (object);		(object) = NULL;}}
#define SAFE_DELETE_ARRAY(object)	{if(object){delete[] (object);		(object) = NULL;}}
#define SAFE_RELEASE(object)		{if(object){(object)->Release();	(object)=NULL;}}

#define GetMonitorRect(rc) SystemParametersInfo(SPI_GETWORKAREA, 0, rc, 0)	// モニター矩形

#define DXtoEffekVec(Vec)	::Effekseer::Vector3D(Vec.x, Vec.y, Vec.z)
// malloc,calloc
#define SafeFree(Object)		{ if (Object) { free(Object);			(Object)=NULL; } }

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;

// 画面遷移定数
enum E_STAGE
{
	STAGE_OPENING,
	STAGE_TITLE,
	STAGE_GAME,
	STAGE_ENDING,
	STAGE_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);	// デバイスを取得する
void SetStage(int stage);			// ステージの変更
int GetStage(void);					// 現在のステージを取得
void ReInit(void);					// 再初期化
int CreateRandom(int Minimum, int Maximum);
float CreateRandomFloat(float Minimum, float Maximum);

#endif
