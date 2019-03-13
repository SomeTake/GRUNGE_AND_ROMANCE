//=============================================================================
//
// 女.x処理 [Onna.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Struct.h"
#include "Onna.h"
#include "Player.h"
#include "Debugproc.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY onnaWk[ONNA_NUM];	// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitOnna(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < ONNA_NUM; en++)
	{
		// 位置・回転・スケールの初期設定
		onnaWk[en].HP = ONNA_HP_MAX;
		onnaWk[en].HPzan = onnaWk[en].HP;
		onnaWk[en].pos = D3DXVECTOR3(-100.0f, 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		onnaWk[en].Epos = D3DXVECTOR3(0.0f, 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		onnaWk[en].rot = D3DXVECTOR3(0.0f, ONNA_DIRECTION, 0.0f);
		onnaWk[en].scl = D3DXVECTOR3(ONNA_SCALE, ONNA_SCALE, ONNA_SCALE);

		onnaWk[en].D3DTexture = NULL;
		onnaWk[en].D3DXMesh = NULL;
		onnaWk[en].D3DXBuffMat = NULL;
		onnaWk[en].NumMat = 0;
		onnaWk[en].use = true;
		onnaWk[en].IdleFlag = true;
		onnaWk[en].AttackFlag = false;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(ONNA_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&onnaWk[en].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&onnaWk[en].NumMat,						// D3DXMATERIAL構造体の数
				&onnaWk[en].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&onnaWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOnna(void)
{
	for (int en = 0; en < ONNA_NUM; en++)
	{
		if (onnaWk[en].D3DTexture != NULL)
		{	// テクスチャの開放
			onnaWk[en].D3DTexture->Release();
			onnaWk[en].D3DTexture = NULL;
		}

		if (onnaWk[en].D3DXMesh != NULL)
		{	// メッシュの開放
			onnaWk[en].D3DXMesh->Release();
			onnaWk[en].D3DXMesh = NULL;
		}

		if (onnaWk[en].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			onnaWk[en].D3DXBuffMat->Release();
			onnaWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateOnna(void)
{
	CHARA *charaWk = GetPlayer(0);
	ENEMY *onnaWk = GetOnna(0);

#ifdef _DEBUG
	PrintDebugProc("攻撃フラグ %s", onnaWk[0].AttackFlag ? "true":"false");
	PrintDebugProc("位置決定フラグ %s", onnaWk[0].IdleFlag ? "true" : "false");
#endif
	for (int en = 0; en < ONNA_NUM; en++, charaWk++)
	{
		// 使用している場合のみ更新
		if (onnaWk[en].use)
		{
			// エネミーの攻撃
			EnemyAttack(charaWk->pos, &onnaWk[en], ONNA_XSCALE);

			SetVertexOnna();

			// HP0になったら消滅
			if (onnaWk[en].HPzan == 0)
			{
				onnaWk[en].use = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOnna(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < ONNA_NUM; en++)
	{
		if (onnaWk[en].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, onnaWk[en].scl.x, onnaWk[en].scl.y, onnaWk[en].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, onnaWk[en].rot.y, onnaWk[en].rot.x, onnaWk[en].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, onnaWk[en].pos.x, onnaWk[en].pos.y, onnaWk[en].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)onnaWk[en].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)onnaWk[en].NumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, onnaWk[en].D3DTexture);

				// 描画
				onnaWk[en].D3DXMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}

	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexOnna(void)
{
	if (onnaWk->Direction == false)
	{
		onnaWk->rot.y = ONNA_DIRECTION2;
	}
	else if (onnaWk->Direction == true)
	{
		onnaWk->rot.y = ONNA_DIRECTION;
	}

}

//=============================================================================
// エネミーの情報を取得する
// 引数：en エネミー番号
//=============================================================================
ENEMY *GetOnna(int en)
{
	return &onnaWk[en];
}