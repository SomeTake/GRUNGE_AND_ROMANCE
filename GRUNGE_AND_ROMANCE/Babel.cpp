//=============================================================================
//
// バーベル処理 [Babel.cpp]
// Author : HAL東京 GP11B341-01 80163 飯塚春輝
//
//=============================================================================
#include "Struct.h"
#include "Babel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ITEM babelWk[BABEL_NUM];	// アイテム構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBabel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int in = 0; in < BABEL_NUM; in++)
	{
		// 位置・回転・スケールの初期設定
		babelWk[in].pos = D3DXVECTOR3(CreateRandomFloat(-100.0f, 100.0f), 0.0f, CreateRandomFloat(-10.0f, 10.0f));
		babelWk[in].rot = D3DXVECTOR3(0.0f, BABEL_DIRECTION, 0.0f);
		babelWk[in].scl = D3DXVECTOR3(BABEL_SCALE, BABEL_SCALE, BABEL_SCALE);

		babelWk[in].D3DTexture = NULL;
		babelWk[in].D3DXMesh = NULL;
		babelWk[in].D3DXBuffMat = NULL;
		babelWk[in].NumMat = 0;
		babelWk[in].use = true;
		babelWk[in].pickup = false;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(BABEL_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&babelWk[in].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&babelWk[in].NumMat,						// D3DXMATERIAL構造体の数
				&babelWk[in].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&babelWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBabel(void)
{
	for (int in = 0; in < BABEL_NUM; in++)
	{
		if (babelWk[in].D3DTexture != NULL)
		{	// テクスチャの開放
			babelWk[in].D3DTexture->Release();
			babelWk[in].D3DTexture = NULL;
		}

		if (babelWk[in].D3DXMesh != NULL)
		{	// メッシュの開放
			babelWk[in].D3DXMesh->Release();
			babelWk[in].D3DXMesh = NULL;
		}

		if (babelWk[in].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			babelWk[in].D3DXBuffMat->Release();
			babelWk[in].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBabel(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBabel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int in = 0; in < BABEL_NUM; in++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, babelWk[in].scl.x, babelWk[in].scl.y, babelWk[in].scl.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, babelWk[in].rot.y, babelWk[in].rot.x, babelWk[in].rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, babelWk[in].pos.x, babelWk[in].pos.y, babelWk[in].pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)babelWk[in].D3DXBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)babelWk[in].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, babelWk[in].D3DTexture);

			// 描画
			babelWk[in].D3DXMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================
// アイテムの情報を取得する
// 引数：in バーベル番号
//=============================================================================
ITEM *GetBabel(int in)
{
	return &babelWk[in];
}

//=============================================================================
// アイテムを拾ったときに使用
//=============================================================================
int SetBabel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int IdxBabel = -1;

	for (int nCntBabel = 0; nCntBabel < BABEL_NUM; nCntBabel++)
	{
		if (!babelWk[nCntBabel].pickup)
		{
			babelWk[nCntBabel].pos = pos;
			babelWk[nCntBabel].rot = rot;
			babelWk[nCntBabel].pickup = true;

			IdxBabel = nCntBabel;
			break;
		}
	}

	return IdxBabel;

}

//=============================================================================
// 位置の更新
//=============================================================================
void SetPositionBabel(int IdxBabel, D3DXVECTOR3 pos)
{
	babelWk[IdxBabel].pos = pos;
}

//=============================================================================
// 回転の更新
//=============================================================================
void SetRotationBabel(int IdxBabel, D3DXVECTOR3 rot)
{
	babelWk[IdxBabel].rot = rot;
}

