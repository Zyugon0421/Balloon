// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ColumnCollision処理の説明[columncollision.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ColumnCollision.h"
#include "meshdome.h"
#ifdef _DEBUG

#endif // _DEBUG

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
CColumnCollision::CColumnCollision() : CCollision::CCollision()
{
	// 初期化
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CColumnCollision::Uninit(void)
{
	// 円柱情報の開放
	m_pColumnShape.reset();
#ifdef _DEBUG
	// メッシュスフィアが生成されていたら
	if (m_pDebugdome != NULL)
	{
		// あたり判定可視化の開放
		m_pDebugdome->Release();
		m_pDebugdome = NULL;
	}
#endif // _DEBUG
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CColumnCollision::Update(void)
{
#ifdef _DEBUG
	// 当たり判定の使用状態がfalse ||
	// ->関数を抜ける
	if (!CCollision::GetUse())
	{
		return;
	}
#endif // _DEBUG
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(矩形と円柱)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CColumnCollision::Debug(void)
{
	// 最終的な位置
	m_pColumnShape->Set_DestPos();
	// メッシュスフィアが生成されていたら
	if (m_pDebugdome != NULL)
	{
		// メッシュスフィアの位置設定
		m_pDebugdome->SetPos(
			m_pColumnShape->m_DestPos - D3DXVECTOR3(0.0f, m_pColumnShape->GetVertical() * 0.5f, 0.0f)
		);
	}
	CCollision::Debug();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// あたり判定可視カの設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CColumnCollision::Collision_Visible_Set(void)
{
	// メッシュスフィア
	m_pDebugdome = CMeshdome::Create(
		m_pColumnShape->m_DestPos - D3DXVECTOR3(0.0f, m_pColumnShape->GetVertical() * 0.5f,0.0f),
		D3DXVECTOR3(m_pColumnShape->GetRadius(),m_pColumnShape->GetVertical(),m_pColumnShape->GetRadius()),
		10,
		10,
		CMeshdome::TYPE_NONE,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f),
		D3DVECTOR3_ZERO,
		true,
		CScene::LAYER_DEBUGCOLLISION
	);
	m_pDebugdome->SetUse(true);
}

#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(矩形と円柱)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CColumnCollision::Judg(CRectShape * const RectShape)
{
	return RectAndColumn(RectShape, this->m_pColumnShape.get());
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(球と矩形)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CColumnCollision::Judg(CRectShape * const RectShape, D3DXVECTOR3 * pPos)
{
	return RectAndColumn(RectShape, this->m_pColumnShape.get());
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(球と円柱)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CColumnCollision::Judg(CSphereShape * const SphereShape)
{
	return SphereAndColumn(SphereShape, this->m_pColumnShape.get());
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 当たり判定処理(円柱と円柱)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool CColumnCollision::Judg(CColumnShape * const ColumnShape)
{
	return ColumnAndColumn(this->m_pColumnShape.get(), ColumnShape);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(シーン管理)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CColumnCollision *CColumnCollision::Create(
	float const &fRadius,
	float const &fVertical,
	D3DXVECTOR3 const offset,
	OBJTYPE const &obj,
	CScene * pOwner,
	CScene * pParent,
	bool const &bPush,
	bool const &bOpponent,
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosold
)
{
	// 変数宣言
	CColumnCollision *pColumnCollision;
	// メモリ確保
	pColumnCollision = new CColumnCollision();
	// 円柱の当たり判定の円柱の生成
	pColumnCollision->m_pColumnShape = std::move(CColumnShape::Create(offset,fRadius,fVertical,bPush,bOpponent,pPos,pPosold));
	pColumnCollision->SetObjectID(obj);												// オブジェクト番号設定
	pColumnCollision->SetOwnScene(pOwner);
	pColumnCollision->SetParent(pParent);

	// 親の情報
	if (pOwner != NULL)
	{
		pColumnCollision->m_pColumnShape->m_pmove = pOwner->Scene_GetPMove();
	}
	// シーン管理設定
	pColumnCollision->ManageSetting(CScene::LAYER_COLLISION);
#ifdef _DEBUG
	// あたり判定可視化設定処理
	pColumnCollision->Collision_Visible_Set();
#endif // _DEBUG

	return pColumnCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(個人管理)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::unique_ptr<CColumnCollision> CColumnCollision::Create_Self(
	float const &fRadius,
	float const &fVertical,
	D3DXVECTOR3 const offset,
	OBJTYPE const &obj,
	CScene * pOwner,
	CScene * pParent,
	bool const &bPush,
	bool const &bOpponent,
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosold
)
{
	// 変数宣言
	std::unique_ptr<CColumnCollision> pColumnCollision(new CColumnCollision);
	// 円柱の設定
	pColumnCollision->m_pColumnShape = std::move(CColumnShape::Create(offset, fRadius, fVertical, bPush,bOpponent, pPos,pPosold));
	pColumnCollision->SetObjectID(obj);												// オブジェクト番号設定
	pColumnCollision->SetOwnScene(pOwner);
	pColumnCollision->SetParent(pParent);
	pColumnCollision->m_pColumnShape->m_pmove = pOwner->Scene_GetPMove();
	return pColumnCollision;
}
