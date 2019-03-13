//=============================================================================
//
// モデル処理 [Effekt.cpp]
// Author : 
//
//=============================================================================
#include "Main.h"
#include "Effect.h"
#include "Player.h"
#include "Camera.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_MAX (1)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EFFECTCONTROLLER		EffectCtrl;
EFFECT					Effect[EFFECT_MAX];

static const EFK_CHAR* EffectFileName[] =
{
	(const EFK_CHAR*)L"data/EFFECT/blow.efk",
	(const EFK_CHAR*)L"data/EFFECT/FireCircle.efk",

};

D3DXVECTOR3 at, up, pos,ppos;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(bool FirstInit)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	int Effect_No = 0;

	for (Effect_No = 0; Effect_No < EFFECT_MAX; Effect_No++)
	{
		Effect[Effect_No].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		Effect[Effect_No].ID = -1;
		Effect[Effect_No].EffectType = -1;
		Effect[Effect_No].use = true;
	}

	// 初めて初期化
	if (FirstInit == true)
	{
		EffectCtrl.Manager = NULL;
		EffectCtrl.Render = NULL;
		EffectCtrl.Effect = NULL;
		EffectCtrl.EffectNum = sizeof(EffectFileName) / sizeof(const EFK_CHAR*);

		// 描画用インスタンスの生成
		EffectCtrl.Render = ::EffekseerRendererDX9::Renderer::Create(Device, 30000);

		// エフェクト管理用インスタンスの生成
		EffectCtrl.Manager = ::Effekseer::Manager::Create(30000);

		// 描画用インスタンスから描画機能を設定
		EffectCtrl.Manager->SetSpriteRenderer(EffectCtrl.Render->CreateSpriteRenderer());
		EffectCtrl.Manager->SetRibbonRenderer(EffectCtrl.Render->CreateRibbonRenderer());
		EffectCtrl.Manager->SetRingRenderer(EffectCtrl.Render->CreateRingRenderer());
		EffectCtrl.Manager->SetTrackRenderer(EffectCtrl.Render->CreateTrackRenderer());
		EffectCtrl.Manager->SetModelRenderer(EffectCtrl.Render->CreateModelRenderer());

		// 描画用インスタンスからテクスチャの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		EffectCtrl.Manager->SetTextureLoader(EffectCtrl.Render->CreateTextureLoader());
		EffectCtrl.Manager->SetModelLoader(EffectCtrl.Render->CreateModelLoader());

		// メモリを確保
		EffectCtrl.Effect = (Effekseer::Effect**)calloc(EffectCtrl.EffectNum, sizeof(Effekseer::Effect*));
		if (EffectCtrl.Effect == NULL)
		{
			MessageBox(0, "Alloc Effect Memory Failed！", "Error", 0);
			return E_FAIL;
		}

		// エフェクトの読込
		for (int i = 0; i < EffectCtrl.EffectNum; i++)
		{
			if (FAILED(SafeLoadEffect(EffectCtrl.Manager, &EffectCtrl.Effect[i], EffectFileName[i], "effect")))
			{
				return E_FAIL;
			}
		}
	}

	// 全エフェクト停止
	EffectCtrl.Manager->StopAllEffects();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// エフェクトの停止
	EffectCtrl.Manager->StopAllEffects();

	//// エフェクトの破棄
	//SafeFree(EffektCtrl.Effekt);
	// エフェクトの破棄
	ES_SAFE_RELEASE(*EffectCtrl.Effect);

	// 先にエフェクト管理用インスタンスを破棄
	EffectCtrl.Manager->Destroy();

	// 次に描画用インスタンスを破棄
	EffectCtrl.Render->Destroy();

	return;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	static int Count = 0;
	int Effect_No = 0;
	int EffectID = 0;

	for (Effect_No = 0; Effect_No < EFFECT_MAX; Effect_No++)
	{
		// 使用しているもののみ更新
		if (Effect[Effect_No].use == true)
		{
			EffectID = Effect[Effect_No].ID;
			// 1ループしたら終了
			if (EffectCtrl.Manager->GetShown(EffectID) == false)
			{
				EffectCtrl.Manager->StopEffect(Effect[Effect_No].ID);
				Effect[Effect_No].use = false;
				continue;
			}

		}
	}


	// エフェクトの更新処理を行う
	EffectCtrl.Manager->Update();

	return;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	CAMERA *cameraWk = GetCamera(0);

	pos=cameraWk->pos;
	at = cameraWk->at;
	up = cameraWk->up;

	// 投影行列を設定
	EffectCtrl.Render->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z));

	// カメラ行列を設定
	EffectCtrl.Render->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(pos.x, pos.y, pos.z), ::Effekseer::Vector3D(at.x, at.y, at.z + 50.0f), ::Effekseer::Vector3D(up.x, up.y, up.z)));

	// エフェクトの描画開始処理を行う。
	EffectCtrl.Render->BeginRendering();

	// エフェクトの描画を行う。
	EffectCtrl.Manager->Draw();

	// エフェクトの描画終了処理を行う。
	EffectCtrl.Render->EndRendering();

	return;
}

//=============================================================================
// エフェクトを設置する
//=============================================================================
void SetEffect(D3DXVECTOR3 Pos, int EffectType)
{
	int Effect_No = 0;

	for (Effect_No = 0; Effect_No < EFFECT_MAX; Effect_No++)
	{
		if (Effect[Effect_No].use == false)
		{
			Effect[Effect_No].ID = EffectCtrl.Manager->Play(EffectCtrl.Effect[EffectType], Pos.x, Pos.y, Pos.z);
			Effect[Effect_No].pos = Pos;
			Effect[Effect_No].EffectType = EffectType;
			Effect[Effect_No].use = true;
			break;
		}
	}

	return;
}

//=============================================================================
// エフェクトコントローラーを取得する
//=============================================================================
EFFECTCONTROLLER *GetEffectCtrl(void)
{
	return &EffectCtrl;
}

//=============================================================================
// エフェクトを読み込む
//=============================================================================
HRESULT SafeLoadEffect(Effekseer::Manager *Manager, Effekseer::Effect **Effect, const EFK_CHAR* SrcPath, const char* ErrorSrc)
{
	char Message[256];
	// エフェクトファイルの中のテクスチャの数
	int TextureNum = 0;

	// エフェクトファイルを読み込む
	(*Effect) = Effekseer::Effect::Create(Manager, SrcPath);
	// 失敗したら
	if ((*Effect) == NULL)
	{
		sprintf_s(Message, "Load %s Effect Failed！", ErrorSrc);
		MessageBox(0, Message, "Error", 0);
		return E_FAIL;
	}

	// エフェクトファイルの中のテクスチャの数を取得する
	TextureNum = (*Effect)->GetColorImageCount();
	for (int i = 0; i < TextureNum; i++)
	{
		// テクスチャのポインタを取得する
		Effekseer::TextureData *Texture = (*Effect)->GetColorImage(i);
		// テクスチャを読み込むが失敗したら
		if (Texture == NULL)
		{
			sprintf_s(Message, "Load %s Effect Texture Failed！", ErrorSrc);
			MessageBox(0, Message, "Error", 0);
			return E_FAIL;
		}
	}

	return S_OK;
}

EFFECT*GetEffect(int no)
{
	return(&Effect[no]);
}


