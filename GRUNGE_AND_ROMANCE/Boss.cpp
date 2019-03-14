//=============================================================================
//
// ボス処理 [Boss.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Struct.h"
#include "Boss.h"
#include "Player.h"
#include "Debugproc.h"
#include "Game.h"
#include "Effect.h"
#include "Sound.h"
#include "Collision.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY bossWk[BOSS_NUM];	// エネミー構造体

						//=============================================================================
						// 初期化処理
						//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int en = 0; en < BOSS_NUM; en++)
	{
		// 位置・回転・スケールの初期設定
		bossWk[en].HP = BOSS_HP_MAX;
		bossWk[en].HPzan = bossWk[en].HP;
		bossWk[en].pos = D3DXVECTOR3(CreateRandomFloat(-200.0f, 200.0f), 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		bossWk[en].Epos = D3DXVECTOR3(0.0f, 0.0f, CreateRandomFloat(-200.0f, 10.0f));
		bossWk[en].rot = D3DXVECTOR3(0.0f, BOSS_DIRECTION, 0.0f);
		bossWk[en].scl = D3DXVECTOR3(BOSS_SCALE, BOSS_SCALE, BOSS_SCALE);

		bossWk[en].D3DTexture = NULL;
		bossWk[en].D3DXMesh = NULL;
		bossWk[en].D3DXBuffMat = NULL;
		bossWk[en].NumMat = 0;
		bossWk[en].use = true;
		bossWk[en].IdleFlag = true;
		bossWk[en].AttackFlag = false;

		if (type == 0)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(BOSS_XFILE,		// 読み込むモデルファイル名(Xファイル)
				D3DXMESH_SYSTEMMEM,							// メッシュの作成オプションを指定
				pDevice,									// IDirect3DDevice9インターフェイスへのポインタ
				NULL,										// 隣接性データを含むバッファへのポインタ
				&bossWk[en].D3DXBuffMat,					// マテリアルデータを含むバッファへのポインタ
				NULL,										// エフェクトインスタンスの配列を含むバッファへのポインタ
				&bossWk[en].NumMat,						// D3DXMATERIAL構造体の数
				&bossWk[en].D3DXMesh)))					// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}

			bossWk[en].IdxShadow = SetShadow(bossWk[en].pos, 30.0f, 30.0f);
#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&bossWk[en].D3DTexture);	// 読み込むメモリー
#endif
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoss(void)
{
	for (int en = 0; en < BOSS_NUM; en++)
	{
		if (bossWk[en].D3DTexture != NULL)
		{	// テクスチャの開放
			bossWk[en].D3DTexture->Release();
			bossWk[en].D3DTexture = NULL;
		}

		if (bossWk[en].D3DXMesh != NULL)
		{	// メッシュの開放
			bossWk[en].D3DXMesh->Release();
			bossWk[en].D3DXMesh = NULL;
		}

		if (bossWk[en].D3DXBuffMat != NULL)
		{	// マテリアルの開放
			bossWk[en].D3DXBuffMat->Release();
			bossWk[en].D3DXBuffMat = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoss(void)
{
	static int Check = 0;

	CHARA *charaWk = GetPlayer(0);

	for (int pn = 0; pn < PLAYER_NUM; pn++, charaWk++)
	{

		for (int en = 0; en < BOSS_NUM; en++)
		{

			// 使用している場合のみ更新
			if (bossWk[en].use)
			{
				// エネミーの攻撃
				EnemyAttack(charaWk->pos, &bossWk[en], BOSS_XSCALE);

				SetVertexBoss();

				// HP0になったら消滅
				if (bossWk[en].HPzan == 0)
				{
					DeleteShadow(bossWk[en].IdxShadow);
					SetEffect(bossWk[en].pos, BurstEffect);
					Play_Sound(SOUND_TYPE_KNOCK_DOWN, SOUND_PLAY_TYPE_PLAY);
					bossWk[en].use = false;
					Check++;
				}

				// 攻撃中の当たり判定
				if (bossWk[en].AttackFlag)
				{
					if (charaWk->Animation->CurrentAnimID == Idle || charaWk->Animation->CurrentAnimID == Walk
						|| charaWk->Animation->CurrentAnimID == Rightwalk || charaWk->Animation->CurrentAnimID == Leftwalk
						|| charaWk->Animation->CurrentAnimID == Idleitem)
					{
						if (HitCheckEToP(&bossWk[en], charaWk))
						{
							bossWk[en].AttackFlag = false;
							charaWk->Animation->ChangeAnimation(charaWk->Animation, Reaction, Data[Reaction].Spd);
							charaWk->HPzan -= ENEMY_DAMAGE;
						}
					}
				}

				SetPositionShadow(bossWk[en].IdxShadow, bossWk[en].pos);
				SetVertexShadow(bossWk[en].IdxShadow, 30.0f, 30.0f);
				SetColorShadow(bossWk[en].IdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			}

		}
	}

	if (Check >= BOSS_NUM)
	{
		SetStage(STAGE_ENDING);
		ReInit();
		SetEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), FireEffect);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, g_mtxWorld;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;


	for (int en = 0; en < BOSS_NUM; en++)
	{
		if (bossWk[en].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, bossWk[en].scl.x, bossWk[en].scl.y, bossWk[en].scl.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, bossWk[en].rot.y, bossWk[en].rot.x, bossWk[en].rot.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, bossWk[en].pos.x, bossWk[en].pos.y, bossWk[en].pos.z);
			D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)bossWk[en].D3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)bossWk[en].NumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, bossWk[en].D3DTexture);

				// 描画
				bossWk[en].D3DXMesh->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}

	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBoss(void)
{
	if (bossWk->Direction == false)
	{
		bossWk->rot.y = BOSS_DIRECTION2;
	}
	else if (bossWk->Direction == true)
	{
		bossWk->rot.y = BOSS_DIRECTION;
	}

}

//=============================================================================
// エネミーの情報を取得する
// 引数：en エネミー番号
//=============================================================================
ENEMY *GetBoss(int en)
{
	return &bossWk[en];
}