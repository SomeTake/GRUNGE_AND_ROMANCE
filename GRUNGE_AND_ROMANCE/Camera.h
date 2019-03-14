//=============================================================================
//
// カメラ処理 [camera.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)											// カメラの初期位置(X座標)
#define	POS_Y_CAM		(100.0f)											// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(250.0f)										// カメラの初期位置(Z座標)

#define AT_X_CAM		(0.0f)											// カメラの注視点(X座標)
#define AT_Y_CAM		(50.0f)											// カメラの注視点(Y座標)
#define AT_Z_CAM		(0.0f)											// カメラの注視点(Z座標)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

typedef struct {
	D3DXVECTOR3			pos;		// カメラの座標
	D3DXVECTOR3			at;			// カメラの注視点
	D3DXVECTOR3			up;			// カメラの上方向ベクトル
	D3DXVECTOR3			rot;		// カメラの回転
	float				distance;	// カメラの注視点と視点との距離
	D3DXMATRIX			mtxView;			// ビューマトリックス
	D3DXMATRIX			mtxProjection;		// プロジェクションマトリックス
}CAMERA;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UpdateCamera(void);
CAMERA *GetCamera(int cno);
void SetCamera(int no);

#endif
