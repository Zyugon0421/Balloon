// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// エフェクトの処理[effect.cpp]
// Author : Nishiyama koki
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "effect.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// マクロ定義
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 静的メンバ変数の初期化
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CEffect::CEffect() :CScene()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CEffect::~CEffect()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEffect::Init(void)
{

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ライフ更新処理
//	pVtx	: 2D頂点情報
//	pEffect	: エフェクト情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CEffect::UpdateLife(
	EFFECT *pEffect		// エフェクト情報
)
{
	// ライフが0未満なら
	if (pEffect->nLife < 0)
	{
		// ライフが0になったとき
		pEffect->bUse = false;
		// falseを返す
		return false;
	}
	// それ以外なら
	else
	{
		// ライフを減らす
		pEffect->nLife--;
		// trueを返す
		return true;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ライフ更新処理
//	pVtx	: 2D頂点情報
//	pEffect	: エフェクト情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CEffect::UpdateVetex(
	EFFECT *pEffect		// エフェクト情報
)
{
	// 半径を変化させる
	pEffect->size += pEffect->sizeValue;
	// アルファ値を変化させる
	pEffect->col.a -= pEffect->fAlphaValue;

	// エフェクトタイプ
	switch (pEffect->EffectType)
	{
		// 爆発
	case CEffect::EFFECT_TYPE_EXPLOSION:
		// 角度を変化させる
		pEffect->fAngle += (rand() % 10) * 0.01f;
		CCalculation::Rot_One_Limit(pEffect->fAngle);
		break;
		// 花火
	case CEffect::EFFECT_TYPE_SPARK:
		// 角度を変化させる
		pEffect->fAngle += (rand() % 10) * 0.01f;
		CCalculation::Rot_One_Limit(pEffect->fAngle);
		break;
		// 煙
	case CEffect::EFFECT_TYPE_SMOKE:
		// 角度を変化させる
		pEffect->fAngle += (rand() % 10) * 0.005f;
		CCalculation::Rot_One_Limit(pEffect->fAngle);
		break;
		// 線
	case CEffect::EFFECT_TYPE_LINE:
		// 角度を変化させる
		pEffect->fAngle += (rand() % 10) * 0.01f;
		CCalculation::Rot_One_Limit(pEffect->fAngle);
		break;
		// 衝撃
	case CEffect::EFFECT_TYPE_SHOCK:
		break;
		// 風船
	case CEffect::EFFECT_TYPE_BALLOON:
		break;
		// 焚火
	case CEffect::EFFECT_TYPE_BONFIRE_SPARK:

		break;
	default:
		break;
	}
	// 成功を返す
	return true;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ライフ更新処理
//	pVtx	: 2D頂点情報
//	pEffect	: エフェクト情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEffect::UpdateMove(
	EFFECT *pEffect		// エフェクト情報
)
{
	// エフェクトタイプ
	switch (pEffect->EffectType)
	{
		// 爆発
	case CEffect::EFFECT_TYPE_EXPLOSION:
		// 慣性
		pEffect->move.x += (0 - pEffect->move.x)*0.2f;
		pEffect->move.y += (0 - pEffect->move.y)*0.2f;
		pEffect->move.z += (0 - pEffect->move.z)*0.2f;
		break;
		// 花火
	case CEffect::EFFECT_TYPE_SPARK:
		break;
		// 煙
	case CEffect::EFFECT_TYPE_SMOKE:

		break;
		// 線
	case CEffect::EFFECT_TYPE_LINE:

		break;
		// 衝撃
	case CEffect::EFFECT_TYPE_SHOCK:
		break;
		// 風船
	case CEffect::EFFECT_TYPE_BALLOON:

		break;
		// 焚火
	case CEffect::EFFECT_TYPE_BONFIRE_SPARK:

		break;
	default:
		break;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 値の初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEffect::InitValues(
	EFFECT *pEffect	// エフェクト情報
)
{
	// エフェクトループ
	for (int nCount = 0; nCount < EFFECT_MAX; nCount++, pEffect++)
	{
		pEffect->pos				= D3DVECTOR3_ZERO;					// 位置
		pEffect->rot				= D3DVECTOR3_ZERO;					// 回転量
		pEffect->move				= D3DVECTOR3_ZERO;					// 移動量
		pEffect->col				= D3DXCOLOR_INI;					// 色
		pEffect->size				= D3DVECTOR2_ZERO;					// サイズ
		pEffect->sizeValue			= D3DVECTOR2_ZERO;					// 半径の変化値
		pEffect->fAngle				= 0.0f;								// 角度
		pEffect->fAlphaValue		= 0.0f;								// アルファ値の変化値
		pEffect->nLife				= 0;								// 持ち時間
		pEffect->nTexType			= 0;								// テクスチャータイプ
		pEffect->nCntAnim			= 0;								// カウントアニメ
		pEffect->nMaxCntAnim		= 1;								// 最大カウントアニメ
		pEffect->nHorizonAnim		= 0;								// 水平のアニメーション
		pEffect->nVirticalAnim		= 0;								// 垂直のアニメーション
		pEffect->nMaxHorizonAnim	= 1;								// 最大水平アニメーション
		pEffect->nMaxVirticalAnim	= 1;								// 最大垂直アニメーション
		pEffect->bUse				= false;							// 使用しているかどうか
		pEffect->BlendType			= CRenderer::BLEND_ADD_TRANSLUCENT;	// ブレンドタイプ
		pEffect->EffectType			= CEffect::EFFECT_TYPE_NONE;		// エフェクトの種類
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 値の初期化処理
//	pEffect		: エフェクト情報
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEffect::Init_OneValues(
	EFFECT * pEffect
)
{
	pEffect->pos = D3DVECTOR3_ZERO;							// 位置
	pEffect->rot = D3DVECTOR3_ZERO;							// 回転量
	pEffect->move = D3DVECTOR3_ZERO;						// 移動量
	pEffect->col = D3DXCOLOR_INI;							// 色
	pEffect->size = D3DVECTOR2_ZERO;						// サイズ
	pEffect->sizeValue = D3DVECTOR2_ZERO;					// 半径の変化値
	pEffect->fAngle = 0.0f;									// 角度
	pEffect->fAlphaValue = 0.0f;							// アルファ値の変化値
	pEffect->nLife = 0;										// 持ち時間
	pEffect->nTexType = 0;									// テクスチャータイプ
	pEffect->nCntAnim = 0;									// カウントアニメ
	pEffect->nMaxCntAnim = 1;								// 最大カウントアニメ
	pEffect->nHorizonAnim = 0;								// 水平のアニメーション
	pEffect->nVirticalAnim = 0;								// 垂直のアニメーション
	pEffect->nMaxHorizonAnim = 1;							// 最大水平アニメーション
	pEffect->nMaxVirticalAnim = 1;							// 最大垂直アニメーション
	pEffect->bUse = false;									// 使用しているかどうか
	pEffect->BlendType = CRenderer::BLEND_ADD_TRANSLUCENT;	// ブレンドタイプ
	pEffect->EffectType = CEffect::EFFECT_TYPE_NONE;		// エフェクトの種類
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 全リソース情報の読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CEffect::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 全リソース情報の開放
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEffect::Unload(void)
{
}

#ifdef _DEBUG
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ表示
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CEffect::Debug(void)
{
}
#endif // _DEBUG
