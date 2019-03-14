//=============================================================================
//
// 当たり判定処理 [Collision.cpp]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#include "Collision.h"
#include "Player.h"
#include "Onna.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCollision(int type, COLLISION *Collision, D3DXMATRIX Matrix, float Radius)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ポインタの初期化
	Collision->D3DTexture = NULL;
	Collision->Mesh = NULL;
	Collision->D3DXMatBuff = NULL;

	// 場所、大きさの設定
	Collision->pos.x = Matrix._41;
	Collision->pos.y = Matrix._42;
	Collision->pos.z = Matrix._43;
	Collision->rot = Collision->rot;
	Collision->scl = D3DXVECTOR3(Radius, Radius, Radius);

	if (type == 0)
	{
		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(BALL_XFILE,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Collision->D3DXMatBuff,
			NULL,
			&Collision->NumMat,
			&Collision->Mesh)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitCollision(COLLISION *Collision)
{
	// テクスチャの開放
	SAFE_RELEASE(Collision->D3DTexture);

	// メッシュの開放
	SAFE_RELEASE(Collision->Mesh);

	// マテリアルの開放
	SAFE_RELEASE(Collision->D3DXMatBuff);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCollision(COLLISION *Collision, D3DXMATRIX Matrix)
{
	Collision->pos.x = Matrix._41;
	Collision->pos.y = Matrix._42;
	Collision->pos.z = Matrix._43;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCollision(COLLISION *Collision)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Collision->mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, Collision->scl.x, Collision->scl.y, Collision->scl.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Collision->rot.y, Collision->rot.x, Collision->rot.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Collision->pos.x, Collision->pos.y, Collision->pos.z);
	D3DXMatrixMultiply(&Collision->mtxWorld, &Collision->mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Collision->mtxWorld);

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)Collision->D3DXMatBuff->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)Collision->NumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, Collision->D3DTexture);

		// 描画
		Collision->Mesh->DrawSubset(nCntMat);
	}

	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}

	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=====================================================================================================
// 当たり判定
// AttackPos = 攻撃側中心位置, DefendPos = 防御側中心位置, AttackRange = 攻撃側半径, DefendPos = 防御側半径
//=====================================================================================================
bool HitSphere(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange)
{
	// 当たり判定の中心の距離を測る
	D3DXVECTOR3 unit = AttackPos - DefendPos;
	float dist = D3DXVec3Length(&unit);

	// 当たり判定の範囲を足した距離を出す（球なのでXYZどれとっても同じ）
	float hitrange = AttackRange + DefendRange;

	// 当たり判定の中心の距離よりも範囲を足した距離の方が長ければ当たる
	if (dist <= hitrange)
	{
		return true;
	}
	// 外れ
	else
	{

	}
	return false;
}

//=====================================================================================================
// 当たり判定
// AttackPos = 攻撃側中心位置, DefendPos = 防御側中心位置, AttackRange = 攻撃側半径, DefendPos = 防御側半径
//=====================================================================================================
bool HitSphereToCircle(D3DXVECTOR3 AttackPos, D3DXVECTOR3 DefendPos, float AttackRange, float DefendRange)
{
	// 当たり判定の中心の距離を測る
	float DistX = AttackPos.x - DefendPos.x;
	float DistZ = AttackPos.z - DefendPos.z;
	float dist = sqrtf(DistX * DistX + DistZ * DistZ);

	// 当たり判定の範囲を足した距離を出す（球なのでXYZどれとっても同じ）
	float hitrange = AttackRange + DefendRange;

	// 当たり判定の中心の距離よりも範囲を足した距離の方が長ければ当たる
	if (dist <= hitrange)
	{
		return true;
	}
	// 外れ
	else
	{

	}

	return false;
}


//=====================================================================================================
// プレイヤーの攻撃とエネミーとの当たり判定
// 引数：Player構造体　Enemy構造体
//=====================================================================================================
bool HitCheckPToE(CHARA *Player, ENEMY *Enemy)
{
	switch (Player->Animation->CurrentAnimID)
	{
	case Jab:
		if (HitSphereToCircle(Player->Collision[LeftHand].pos, Enemy->pos,
			Player->Collision[LeftHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Straight:
		if (HitSphereToCircle(Player->Collision[RightHand].pos, Enemy->pos,
			Player->Collision[RightHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Upper:
		if (HitSphereToCircle(Player->Collision[LeftHand].pos, Enemy->pos,
			Player->Collision[LeftHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Kick:
		if (HitSphereToCircle(Player->Collision[RightFoot].pos, Enemy->pos,
			Player->Collision[RightFoot].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Attackitem:
		if (HitSphereToCircle(Player->Collision[RightHand].pos, Enemy->pos,
			Player->Collision[RightHand].scl.x, Enemy->scl.x) == true)
		{
			return true;
		}
		break;
	case Throwitem:
		break;
	default:
		break;
	}

	return false;
}

//=====================================================================================================
// プレイヤーとアイテムとの当たり判定
// 引数：Player構造体　Item構造体
//=====================================================================================================
bool HitCheckPToI(CHARA *Player, ITEM *Item)
{
	switch (Player->Animation->CurrentAnimID)
	{
	case Pickup:
		if (HitSphere(Player->Collision[RightHand].pos, Item->pos, Player->Collision[RightHand].scl.x, ITEM_GETVALUE))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

bool HitCheckIToE(ITEM *Item, ENEMY *Enemy)		// 投げられたアイテムと敵との当たり判定
{
	if (HitSphereToCircle(Item->pos, Enemy->pos, ITEM_GETVALUE, ONNA_XSCALE))
	{
		return true;
	}

	return false;
}

bool HitCheckEToP(ENEMY *Enemy, CHARA *Player)		// 敵の攻撃とプレイヤーとの当たり判定
{
	if (HitSphere(Enemy->pos, Player->pos, ONNA_XSCALE, HitRadius[Hips]))
	{
		return true;
	}
	return false;
}