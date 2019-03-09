/*******************************************************************************
* タイトル:		オープニングヘッダー
* プログラム名:	Opening.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _OPENING_H_
#define _OPENING_H_

#include "Main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_OPENING		("data/TEXTURE/enter2.png")				// 読み込むテクスチャファイル名
#define	OPENING_SIZE_X		(800)									// オープニングの幅
#define	OPENING_SIZE_Y		(600)									// オープニングの高さ
#define OPENING_MAX			(1)										// オープニングの最大数
#define	NUM_OPENING			(2)										// ポリゴン数
#define TEXTURE_PATTERN_DIVIDE_X_OPENING	(1)						// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_OPENING	(1)						// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_OPENING			(TEXTURE_PATTERN_DIVIDE_X_OPENING*TEXTURE_PATTERN_DIVIDE_Y_OPENING)	// アニメーションパターン数
#define TIME_ANIMATION_OPENING				(4)						// アニメーションの切り替わるカウント

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// オープニング構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		scl;						// ポリゴンの拡大量
	D3DXVECTOR3		col;						// ポリゴンの色彩量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	float			Alpha;
	float			Radius;						// オープニングの半径
	float			BaseAngle;					// オープニングの角度
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D			VertexWkOpening[NUM_VERTEX];			// 頂点情報格納ワーク

} OPENING;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitOpening(void);
HRESULT MakeVertexOpening(void);
void UninitOpening(void);
void UpdateOpening(void);
void DrawOpening(void);
OPENING *GetOpening(int no);

#endif
