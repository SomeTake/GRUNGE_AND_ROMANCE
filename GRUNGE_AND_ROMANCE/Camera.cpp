//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Main.h"
#include "Camera.h"
#include "Input.h"
#include "Player.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define VIEW_DIST			(4)		// 最低限のキャラクターとカメラの距離
#define VIEW_DIST_RATE		(0.3f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA cameraWk[MAX_SEPARATE];

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	cameraWk->at = D3DXVECTOR3(AT_X_CAM, AT_Y_CAM, AT_Z_CAM);
	cameraWk->pos = cameraWk->at + D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);

	cameraWk->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	cameraWk->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 注視点からカメラの位置までの距離計測
	float vx, vz;
	vx = cameraWk->pos.x - cameraWk->at.x;
	vz = cameraWk->pos.z - cameraWk->at.z;
	cameraWk->distance = sqrtf(vx * vx + vz * vz);

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(int no)
{
	CAMERA *cameraWk = GetCamera(no);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&cameraWk->mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&cameraWk->mtxView,
		&cameraWk->pos,		// カメラの視点
		&cameraWk->at,		// カメラの注視点
		&cameraWk->up);		// カメラの上方向ベクトル

							// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &cameraWk->mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&cameraWk->mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&cameraWk->mtxProjection,
		VIEW_ANGLE,			// ビュー平面の視野角
		VIEW_ASPECT,		// ビュー平面のアスペクト比
		VIEW_NEAR_Z,		// ビュー平面のNearZ値
		VIEW_FAR_Z);		// ビュー平面のFarZ値

							// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &cameraWk->mtxProjection);

}

//=============================================================================
//カメラの情報を取得する
//=============================================================================
CAMERA *GetCamera(int cno)
{
	return &cameraWk[cno];
}
