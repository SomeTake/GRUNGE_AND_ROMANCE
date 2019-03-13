//=============================================================================
//
// くまちゃん処理 [Kumatyang.cpp]
// Author : HAL東京 GP11B341-01 80163 飯塚春輝
//
//=============================================================================
#include "Struct.h"
#include "Kumatyang.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ITEM kumatyangWk[KUMATYANG_NUM];	// アイテム構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitKumatyang(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int in = 0; in < KUMATYANG_NUM; in++)
	{
		// 位置・回転・スケールの初期設定
		kumatyangWk[in].pos = D3DXVECTOR3(CreateRandomFloat(-100.0f, 100.0f), 0.0f, CreateRandomFloat(-10.0f, 10.0f));
		kumatyangWk[in].rot = D3DXVECTOR3(0.0f, KUMATYANG_DIRECTION, 0.0f);
		kumatyangWk[in].scl = D3DXVECTOR3(KUMATYANG_SCALE, KUMATYANG_SCALE, KUMATYANG_SCALE);

		kumatyangWk[in].D3DTexture = NULL;
		kumatyangWk[in].D3DXMesh = NULL;
		kumatyangWk[in].D3DXBuffMat = NULL;
		kumatyangWk[in].NumMat = 0;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(KUMATYANG_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&kumatyangWk[in].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&kumatyangWk[in].NumMat,						// D3DXMATERIAL構造体の数
				&kumatyangWk[in].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&kumatyangWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitKumatyang(void)
{
	for (int in = 0; in < KUMATYANG_NUM; in++)
	{
		if (kumatyangWk[in].D3DTexture != NULL)
		{	// テクスチャの開放
			kumatyangWk[in].D3DTexture->Release();
			kumatyangWk[in].D3DTexture = NULL;
		}

		if (kumatyangWk[in].D3DXMesh != NULL)
		{	// メッシュの開放
			kumatyangWk[in].D3DXMesh->Release();
			kumatyangWk[in].D3DXMesh = NULL;
		}

		if (kumatyangWk[in].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			kumatyangWk[in].D3DXBuffMat->Release();
			kumatyangWk[in].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateKumatyang(void)
{


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawKumatyang(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int in = 0; in < KUMATYANG_NUM; in++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, kumatyangWk[in].scl.x, kumatyangWk[in].scl.y, kumatyangWk[in].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, kumatyangWk[in].rot.y, kumatyangWk[in].rot.x, kumatyangWk[in].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, kumatyangWk[in].pos.x, kumatyangWk[in].pos.y, kumatyangWk[in].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)kumatyangWk[in].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)kumatyangWk[in].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, kumatyangWk[in].D3DTexture);

			// 描画
			kumatyangWk[in].D3DXMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// アイテムの情報を取得する
// 引数：in くまちゃん番号
//=============================================================================
ITEM *GetKumatyang(int in)
{
	return &kumatyangWk[in];
}

//=============================================================================
// アイテムを拾ったときに使用
//=============================================================================
int SetKumatyang(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int IdxKumatyang = -1;

	for (int nCntKumatyang = 0; nCntKumatyang < KUMATYANG_NUM; nCntKumatyang++)
	{
		if (!kumatyangWk[nCntKumatyang].pickup)
		{
			kumatyangWk[nCntKumatyang].pos = pos;
			kumatyangWk[nCntKumatyang].rot = rot;
			kumatyangWk[nCntKumatyang].pickup = true;

			IdxKumatyang = nCntKumatyang;
			break;
		}
	}

	return IdxKumatyang;

}

//=============================================================================
// 位置の更新
//=============================================================================
void SetPositionKumatyang(int IdxKumatyang, D3DXVECTOR3 pos)
{
	kumatyangWk[IdxKumatyang].pos = pos;
}

//=============================================================================
// 回転の更新
//=============================================================================
void SetRotationKumatyang(int IdxIdxKumatyang, D3DXVECTOR3 rot)
{
	kumatyangWk[IdxIdxKumatyang].rot = rot;
}
