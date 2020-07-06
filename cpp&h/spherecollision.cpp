// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// SphereCollision処理の説明[spherecollision.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "SphereCollision.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// グローバル変数
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// コンストラクタ
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSphereCollision::CSphereCollision() : CCollision::CCollision()
{
	// 初期化
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Uninit(void)
{
	// 矩形情報の開放
	m_pSphereShape.reset();
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(矩形と円柱)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Debug(void)
{
	/*
	CDebugproc::Print("----------球の当たり判定情報----------\n");
	CDebugproc::Print("半径(%.1f)\n", m_pSphereShape->GetRadius());
	*/
	CCollision::Debug();
}
#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(矩形と矩形)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CSphereCollision::Judg(CRectShape * const RectShape)
{
	return RectAndSphere(RectShape, this->m_pSphereShape.get());
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(矩形と球)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CSphereCollision::Judg(CRectShape * const RectShape, D3DXVECTOR3 * pPos)
{
	return RectAndSphere(RectShape, this->m_pSphereShape.get());
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(矩形と球)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CSphereCollision::Judg(CSphereShape * const SphereShape)
{
	return SphereAndSphere(this->m_pSphereShape.get(), SphereShape);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(球と円柱)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CSphereCollision::Judg(CColumnShape * const ColumnShape)
{
	return SphereAndColumn(this->m_pSphereShape.get(), ColumnShape);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(シーン管理)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSphereCollision *CSphereCollision::Create(
	float const &fRadius,
	D3DXVECTOR3 const offset,
	OBJTYPE const &obj,
	CScene * pOwner,
	CScene * pParent,
	bool const &bPush,
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosold
)
{
	// 変数宣言
	CSphereCollision *pSphereCollision;
	// メモリ確保
	pSphereCollision = new CSphereCollision();
	// 球の設定
	pSphereCollision->m_pSphereShape = std::move(CSphereShape::Create(offset, fRadius,bPush, pPos,pPosold));	// 球の形を生成
	pSphereCollision->SetObjectID(obj);												// オブジェクト番号設定
	pSphereCollision->SetOwnScene(pOwner);
	pSphereCollision->SetParent(pParent);
	// シーン管理設定
	pSphereCollision->ManageSetting(CScene::LAYER_COLLISION);
	return pSphereCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(個人管理)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unique_ptr<CSphereCollision> CSphereCollision::Create_Self(
	float const &fRadius,
	D3DXVECTOR3 const offset,
	OBJTYPE const &obj,
	CScene * pOwner,
	CScene * pParent,
	bool const &bPush,
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosold
)
{
	// 変数宣言
	unique_ptr<CSphereCollision> pSphereCollision(new CSphereCollision);
	pSphereCollision->m_pSphereShape = std::move(CSphereShape::Create(offset, fRadius,bPush, pPos,pPosold));	// 球の形を生成
	pSphereCollision->SetObjectID(obj);												// オブジェクト番号設定
	pSphereCollision->SetOwnScene(pOwner);
	pSphereCollision->SetParent(pParent);

	return pSphereCollision;
}