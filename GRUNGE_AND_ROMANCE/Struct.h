//=============================================================================
//
// 構造体定義処理 [Struct.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "Main.h"
#include "D3DXAnimation.h"


#define	HIT_CHECK_NUM	(13)								// 当たり判定の数
<<<<<<< HEAD
#define ITEM_GETVALUE	(10.0f)								// アイテムを拾える範囲

// アイテムの種類
enum ItemCategory {
	ItemBabel,
	ItemKumatyang,
	ItemYakiYaki,
};

=======
>>>>>>> Develop
//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 当たり判定用
typedef struct
{
	D3DXVECTOR3 pos;		// 現在の位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scl;		// 大きさ
	LPDIRECT3DTEXTURE9	D3DTexture;		// テクスチャ読み込み場所
	LPD3DXMESH			Mesh;			// ID3DXMeshインターフェイスへのポインタ
	LPD3DXBUFFER		D3DXMatBuff;	// メッシュのマテリアル情報を格納
	DWORD				NumMat;			// 属性情報の総数
	D3DXMATRIX			mtxWorld;		// ワールドマトリックス
} COLLISION;

// プレイヤーキャラクター用
typedef struct {
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			move;				// モデルの移動量
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	int					HP;					// 体力
	int					HPzan;				// 残り体力
	D3DXANIMATION		*Animation;			// アニメーション
	bool				reverse;			// 向き反転フラグ
	bool				HitFrag;			// 攻撃が当たったかどうか判定するフラグ
	bool				UseItem;			// アイテムを所持しているかどうか判定するフラグ
	COLLISION			Collision[HIT_CHECK_NUM];			// 当たり判定用構造体
	int					ItemIdx;			// 使用しているアイテム番号
	int					ItemCategory;		// 使用しているアイテムの種類
}CHARA;

// エネミーキャラクター用
typedef struct {
	LPDIRECT3DTEXTURE9	D3DTexture;			// テクスチャへのポインタ
	LPD3DXMESH			D3DXMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER		D3DXBuffMat;		// マテリアル情報へのポインタ
	DWORD				NumMat;				// マテリアル情報の数
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			Epos;				// モデルの次位置
	D3DXVECTOR3			move;				// モデルの移動量
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	int					HP;					// 体力
	int					HPzan;				// 残り体力
	bool				use;				// 使用中フラグ
	bool				IdleFlag;			// 敵移動フラグ
	bool				AttackFlag;			// 敵X値フラグ
	bool				Direction;			// 向き判定
}ENEMY;

// アイテム用
typedef struct {
	LPDIRECT3DTEXTURE9	D3DTexture;			// テクスチャへのポインタ
	LPD3DXMESH			D3DXMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER		D3DXBuffMat;		// マテリアル情報へのポインタ
	DWORD				NumMat;				// マテリアル情報の数
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			move;				// モデルの移動量
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	bool				pickup;				// 誰かが持っているかどうかのフラグ
	bool				use;				// 使用しているかどうかのフラグ
}ITEM;

#endif
