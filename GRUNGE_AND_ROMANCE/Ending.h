/*******************************************************************************
* タイトル:		エンディングヘッダー
* プログラム名:	Ending.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _ENDING_H_
#define _ENDING_H_

#include "Main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ENDING		("data/TEXTURE/enter2.png")				// 読み込むテクスチャファイル名
#define	ENDING_SIZE_X			(800)								// エンディングの幅
#define	ENDING_SIZE_Y			(600)								// エンディングの高さ
#define ENDING_MAX			(1)										// エンディングの最大数
#define	NUM_ENDING			(2)										// ポリゴン数
#define TEXTURE_PATTERN_DIVIDE_X_ENDING	(1)							// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENDING	(1)							// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENDING			(TEXTURE_PATTERN_DIVIDE_X_ENDING*TEXTURE_PATTERN_DIVIDE_Y_ENDING)	// アニメーションパターン数
#define TIME_ANIMATION_ENDING			(4)							// アニメーションの切り替わるカウント

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// エンディング構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		scl;						// ポリゴンの拡大量
	D3DXVECTOR3		col;						// ポリゴンの色彩量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			Alpha;
	float			Radius;						// エンディングの半径
	float			BaseAngle;					// エンディングの角度
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D			VertexWkEnding[NUM_VERTEX];			// 頂点情報格納ワーク

} ENDING;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnding(void);
HRESULT MakeVertexEnding(void);
void UninitEnding(void);
void UpdateEnding(void);
void DrawEnding(void);
ENDING *GetEnding(int no);

#endif
