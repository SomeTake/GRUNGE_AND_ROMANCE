/*******************************************************************************
* タイトル:		タイトルヘッダー
* プログラム名:	Title.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _TITLE_H_
#define _TITLE_H_

#include "Main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		("data/TEXTURE/enter2.png")				// 読み込むテクスチャファイル名
#define	TITLE_SIZE_X		(800)									// タイトルの幅
#define	TITLE_SIZE_Y		(600)									// タイトルの高さ
#define TITLE_MAX			(1)										// タイトルの最大数
#define	NUM_TITLE			(2)										// ポリゴン数
#define TEXTURE_PATTERN_DIVIDE_X_TITLE	(1)							// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_TITLE	(1)							// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_TITLE			(TEXTURE_PATTERN_DIVIDE_X_TITLE*TEXTURE_PATTERN_DIVIDE_Y_TITLE)	// アニメーションパターン数
#define TIME_ANIMATION_TITLE			(4)							// アニメーションの切り替わるカウント

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// タイトル構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		scl;						// ポリゴンの拡大量
	D3DXVECTOR3		col;						// ポリゴンの色彩量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			Alpha;
	float			Radius;						// titleの半径
	float			BaseAngle;					// titleの角度
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D			VertexWkTitle[NUM_VERTEX];			// 頂点情報格納ワーク

} TITLE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
HRESULT MakeVertexTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
TITLE *GetTitle(int no);
#endif
