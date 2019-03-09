//=============================================================================
//
// モデル処理 [effekt.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
enum EffectType
{
	FIRE,
	WATER,
};


//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	EffekseerRendererDX9::Renderer		*Render;
	Effekseer::Manager					*Manager;
	Effekseer::Effect					**Effect;
	int									EffectNum;
}EFFECTCONTROLLER;

typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	D3DXVECTOR3				Ppos;
	int						ID;
	int						EffectType;
	bool					use;
}EFFECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(bool FirstInit);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 Pos, int EffectType);
HRESULT SafeLoadEffect(Effekseer::Manager *Manager, Effekseer::Effect **Effect, const EFK_CHAR* SrcPath, const char* ErrorSrc);
EFFECT *GetEffect(int no);
EFFECTCONTROLLER *GetEffectCtrl(void);

#endif
