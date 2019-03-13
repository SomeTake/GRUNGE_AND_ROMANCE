//=============================================================================
//
// ブラックホールくん処理 [Blackhole.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Struct.h"
#include "Blackhole.h"
#include "Player.h"
#include "Game.h"
#include "Collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY blackholeWk[BLACKHOLE_NUM];	// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBlackhole(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		// 位置・回転・スケールの初期設定
		blackholeWk[en].HP = BLACKHOLE_HP_MAX;
		blackholeWk[en].HPzan = blackholeWk[en].HP;
		blackholeWk[en].pos = D3DXVECTOR3(130.0f, 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		blackholeWk[en].Epos = D3DXVECTOR3(0.0f, 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		blackholeWk[en].rot = D3DXVECTOR3(0.0f, BLACKHOLE_DIRECTION, 0.0f);
		blackholeWk[en].scl = D3DXVECTOR3(BLACKHOLE_SCALE, BLACKHOLE_SCALE, BLACKHOLE_SCALE);

		blackholeWk[en].D3DTexture = NULL;
		blackholeWk[en].D3DXMesh = NULL;
		blackholeWk[en].D3DXBuffMat = NULL;
		blackholeWk[en].NumMat = 0;
		blackholeWk[en].use = true;
		blackholeWk[en].IdleFlag = true;
		blackholeWk[en].IdleFlag = false;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(BLACKHOLE_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&blackholeWk[en].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&blackholeWk[en].NumMat,						// D3DXMATERIAL構造体の数
				&blackholeWk[en].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&blackholeWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlackhole(void)
{
	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		if (blackholeWk[en].D3DTexture != NULL)
		{	// テクスチャの開放
			blackholeWk[en].D3DTexture->Release();
			blackholeWk[en].D3DTexture = NULL;
		}

		if (blackholeWk[en].D3DXMesh != NULL)
		{	// メッシュの開放
			blackholeWk[en].D3DXMesh->Release();
			blackholeWk[en].D3DXMesh = NULL;
		}

		if (blackholeWk[en].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			blackholeWk[en].D3DXBuffMat->Release();
			blackholeWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlackhole(void)
{
	CHARA *charaWk = GetPlayer(0);

	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		for (int pn = 0; pn < PLAYER_NUM; pn++, charaWk++)
		{

			// 使用している場合のみ更新
			if (blackholeWk[en].use)
			{
				// エネミーの攻撃
				EnemyAttack(charaWk->pos, &blackholeWk[en], BLACKHOLE_XSCALE);

				SetVertexBlackhole();

				// HP0になったら消滅
				if (blackholeWk[en].HPzan == 0)
				{
					blackholeWk[en].use = false;
				}

				// 攻撃中の当たり判定
				if (blackholeWk[en].AttackFlag)
				{
					if (charaWk->Animation->CurrentAnimID == Idle || charaWk->Animation->CurrentAnimID == Walk
						|| charaWk->Animation->CurrentAnimID == Rightwalk || charaWk->Animation->CurrentAnimID == Leftwalk
						|| charaWk->Animation->CurrentAnimID == Idleitem)
					{
						if (HitCheckEToP(&blackholeWk[en], charaWk))
						{
							blackholeWk[en].AttackFlag = false;
							charaWk->Animation->ChangeAnimation(charaWk->Animation, Reaction, Data[Reaction].Spd);
							charaWk->HPzan -= ENEMY_DAMAGE;
						}
					}
				}
			}

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBlackhole(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < BLACKHOLE_NUM; en++)
	{
		if (blackholeWk[en].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, blackholeWk[en].scl.x, blackholeWk[en].scl.y, blackholeWk[en].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, blackholeWk[en].rot.y, blackholeWk[en].rot.x, blackholeWk[en].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, blackholeWk[en].pos.x, blackholeWk[en].pos.y, blackholeWk[en].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)blackholeWk[en].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)blackholeWk[en].NumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, blackholeWk[en].D3DTexture);

				// 描画
				blackholeWk[en].D3DXMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBlackhole(void)
{
	if (blackholeWk->Direction == false)
	{
		blackholeWk->rot.y = BLACKHOLE_DIRECTION;
	}
	else if (blackholeWk->Direction == true)
	{
		blackholeWk->rot.y = BLACKHOLE_DIRECTION2;
	}

}

//=============================================================================
// エネミーの情報を取得する
// 引数：en エネミー番号
//=============================================================================
ENEMY *GetBlackhole(int en)
{
	return &blackholeWk[en];
}