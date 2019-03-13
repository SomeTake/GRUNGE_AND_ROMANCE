//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : HAL東京 GP11B341-17 80277 染谷武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "D3DXAnimation.h"
#include "Collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHARA_XFILE			("data/MODEL/Togen.x")
#define PLAYER_NUM		(2)									// プレイヤーの数

#define FIRST_PLAYER_POS	D3DXVECTOR3(0.0f, 0.0f, 0.0f)	// 初期位置
#define PLAYER_HP_MAX	(200)

#define VALUE_FRONTWALK	(1.50f)								// 前歩き移動量
#define	VALUE_SIDESTEP	(1.00f)								// 横歩き移動量
#define VALUE_HALF		(0.5f)								// 何らかの値を半分にするために掛ける

//*****************************************************************************
// グローバル変数
//*****************************************************************************

// キャラクターのアニメーション番号
static const char* CharaStateAnim[] =
{
	"idle",				// 待機
	"walk",				// 前歩き
	"rightwalk",		// 横移動
	"leftwalk",			// 横移動
	"jab",				// パンチ1
	"straight",			// パンチ2
	"upper",			// パンチ3
	"kick",				// キック
	"pickup",			// アイテムを拾う
	"idleitem",			// 待機（アイテム所持時）
	"attackitem",		// 攻撃（アイテム所持時）
	"throwitem",		// アイテムを投げる
	"reaction"			// 被ダメージ
};

// キャラクターのアニメーション番号と連動（CharaStateAnim）
enum CharaStateNum
{
	Idle,
	Walk,
	Rightwalk,
	Leftwalk,
	Jab,
	Straight,
	Upper,
	Kick,
	Pickup,
	Idleitem,
	Attackitem,
	Throwitem,
	Reaction,
	AnimMax,			// アニメーションの最大数
};

// バトル用データ構造体
typedef struct
{
	int Damage;					// そのモーションによって与えるダメージ量
	float Spd;					// アニメーションを再生するスピード
	float ShiftTime;			// アニメーションの切り替え時間
	int CollisionStartTime;		// 攻撃当たり判定の発生する時間
	int CollisionFinishTime;	// 攻撃当たり判定の終了する時間
}BATTLEDATA;

// バトル用データ構造体配列
static BATTLEDATA Data[AnimMax] = {
	{ 0, 1.0f, 0.1f, 0, 0 },		// Idle
{ 0, 1.5f, 0.1f, 0, 0 },		// Walk
{ 0, 1.5f, 0.1f, 0, 0 },		// Rightwalk
{ 0, 1.5f, 0.1f, 0, 0 },		// Leftwalk
{ 10, 1.5f, 0.1f, 0, 0 },		// Jab
{ 10, 1.5f, 0.1f, 0, 0 },		// Straight
{ 10, 2.0f, 0.1f, 0, 0 },		// Upper
{ 10, 1.5f, 0.1f, 0, 0 },		// Kick
{ 0, 2.0f, 0.1f, 0, 0 },		// Pickup
{ 0, 1.0f, 0.1f, 0, 0 },		// Idleitem
{ 15, 1.5f, 0.1f, 0, 0 },		// Attackitem
{ 20, 1.5f, 0.1f, 0, 0 },		// Throwitem
{ 0, 1.5f, 0.1f, 0, 0 },		// Reaction
};

// 当たり判定を発生させる場所
static const char* CharaHitPos[] =
{
	"mixamorig_Hips",				// 尻
	"mixamorig_Neck",				// 首
	"mixamorig_Head",				// 頭
	"mixamorig_LeftShoulder",		// 左肩
	"mixamorig_RightShoulder",		// 右肩
	"mixamorig_LeftHand",			// 左手
	"mixamorig_RightHand",			// 右手
	"mixamorig_LeftFoot",			// 左足
	"mixamorig_RightFoot",			// 右足
	"mixamorig_LeftForeArm",		// 左肘
	"mixamorig_RightForeArm",		// 右肘
	"mixamorig_LeftLeg",			// 左膝
	"mixamorig_RightLeg"			// 右膝
};

// 当たり判定発生場所と連動（CharaHitPos）
enum CharaHitNum
{
	Hips,
	Neck,
	Head,
	LeftShoulder,
	RightShoulder,
	LeftHand,
	RightHand,
	LeftFoot,
	RightFoot,
	LeftForeArm,
	RightForeArm,
	LeftLeg,
	RightLeg,
};

// 当たり判定の半径（上の発生場所と連動）
static float HitRadius[] =
{
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
CHARA *GetPlayer(int pn);
void ControlPlayer(int pn);						// 操作
void MovePlayer(int pn);						// 座標移動
void HitAction(int pn, ENEMY *enemy);			// 攻撃ヒット時のアクション

#endif
