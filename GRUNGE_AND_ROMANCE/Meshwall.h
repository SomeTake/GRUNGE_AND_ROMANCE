/*******************************************************************************
* タイトル:		壁ヘッダー
* プログラム名:	meshwall.h
* 作成者:		GP11B341 01 飯塚春輝
* 作成日:		2018/1/28
*******************************************************************************/
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "Main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_MESH_WALL		(10)							// 壁の総数
#define	TEXTURE_FILE_MESH_WALL_000	"data/TEXTURE/Mesh_Wall_000.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_FILE_MESH_WALL_001	"data/TEXTURE/Mesh_Wall_001.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_FILE_MESH_WALL_002	"data/TEXTURE/Mesh_Wall_002.jpg"		// 読み込むテクスチャファイル名
#define	VALUE_MOVE_WALL		(5.0f)							// 移動速度
#define	VALUE_ROTATE_WALL	(D3DX_PI * 0.001f)				// 回転速度
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
#endif
