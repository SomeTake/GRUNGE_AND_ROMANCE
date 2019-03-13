/*******************************************************************************
* タイトル:	ゲージヘッダー
* プログラム名:	Gauge.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/07/26
*******************************************************************************/
#ifndef _GAUGE_H_
#define _GAUGE_H_

// マクロ定義
#define	NUM_GAUGE			(2)									// ポリゴン数
#define TEXTURE_GAUGE		("data/TEXTURE/PLAYERHP.png")		// サンプル用画像
#define GAUGE_SIZE_X		(200)								// テクスチャサイズ
#define GAUGE_SIZE_Y		(30)								// 同上
#define GAUGE_MAX			(1)									// gaugeの数

#define	NUM_GAUGE2			(2)									// ポリゴン数
#define TEXTURE_GAUGE2		("data/TEXTURE/Hit_Point_000.png")	// サンプル用画像
#define GAUGE2_SIZE_X		(80)								// テクスチャサイズ
#define GAUGE2_SIZE_Y		(400)								// 同上
#define GAUGE2_MAX			(1)									// gauge2の数

#define	NUM_GAUGE3			(2)									// ポリゴン数
#define TEXTURE_GAUGE3		("data/TEXTURE/PLAYERHP.png")		// サンプル用画像
#define GAUGE3_SIZE_X		(200)								// テクスチャサイズ
#define GAUGE3_SIZE_Y		(30)								// 同上
#define GAUGE3_MAX			(1)									// gauge3の数

#define	NUM_GAUGE4			(2)									// ポリゴン数
#define TEXTURE_GAUGE4		("data/TEXTURE/Hit_Point_002.png")	// サンプル用画像
#define GAUGE4_SIZE_X		(80)								// テクスチャサイズ
#define GAUGE4_SIZE_Y		(400)								// 同上
#define GAUGE4_MAX			(1)									// gauge4の数

#define	NUM_GAUGE5			(2)									// ポリゴン数
#define TEXTURE_GAUGE5		("data/TEXTURE/Hit_Point_001.png")	// サンプル用画像
#define GAUGE5_SIZE_X		(80)								// テクスチャサイズ
#define GAUGE5_SIZE_Y		(400)								// 同上
#define GAUGE5_MAX			(1)									// gauge5の数

#define	NUM_GAUGE6			(2)									// ポリゴン数
#define TEXTURE_GAUGE6		("data/TEXTURE/Hit_Point_003.png")	// サンプル用画像
#define GAUGE6_SIZE_X		(80)								// テクスチャサイズ
#define GAUGE6_SIZE_Y		(400)								// 同上
#define GAUGE6_MAX			(1)									// gauge6の数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct	// gauge構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture;			// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];			// 頂点情報格納ワーク
	float			Radius;						// gaugeの半径
	float			BaseAngle;					// gaugeの角度
} GAUGE;

typedef struct	// gauge2構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture2;			// テクスチャ情報
	VERTEX_2D		vertexWk2[NUM_VERTEX];		// 頂点情報格納ワーク
	float			Radius;						// gauge2の半径
	float			BaseAngle;					// gauge2の角度
} GAUGE2;

typedef struct	// gauge3構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture3;			// テクスチャ情報
	VERTEX_2D		vertexWk3[NUM_VERTEX];			// 頂点情報格納ワーク
	float			Radius;						// gaugeの半径
	float			BaseAngle;					// gaugeの角度
} GAUGE3;

typedef struct	// gauge4構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture4;			// テクスチャ情報
	VERTEX_2D		vertexWk4[NUM_VERTEX];		// 頂点情報格納ワーク
	float			Radius;						// gauge2の半径
	float			BaseAngle;					// gauge2の角度
} GAUGE4;

typedef struct	// gauge5構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture5;			// テクスチャ情報
	VERTEX_2D		vertexWk5[NUM_VERTEX];		// 頂点情報格納ワーク
	float			Radius;						// gauge5の半径
	float			BaseAngle;					// gauge5の角度
} GAUGE5;

typedef struct	// gauge6構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント
	LPDIRECT3DTEXTURE9	g_pD3DTexture6;			// テクスチャ情報
	VERTEX_2D		vertexWk6[NUM_VERTEX];		// 頂点情報格納ワーク
	float			Radius;						// gauge6の半径
	float			BaseAngle;					// gag6の角度
} GAUGE6;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGauge(int type);
HRESULT MakeVertexGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
void SetVertexGauge(void);
void SetTextuerGauge(void);
GAUGE *GetGauge(int no);
GAUGE2 *GetGauge2(int no);
GAUGE3 *GetGauge3(int no);
GAUGE4 *GetGauge4(int no);
GAUGE5 *GetGauge5(int no);
GAUGE6 *GetGauge6(int no);

#endif
