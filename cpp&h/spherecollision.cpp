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
#ifdef _DEBUG
#include "meshsphere.h"
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
CSphereCollision::CSphereCollision() : CCollision::CCollision()
{
	// 初期化
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Init(void)
{

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Uninit(void)
{
	// 矩形情報の開放
	m_pSphereShape.reset();
#ifdef _DEBUG
	// メッシュスフィアが生成されていたら
	if (m_uni_pMeshsphere)
	{
		// あたり判定可視化の変数
		m_uni_pMeshsphere->Uninit();
		// あたり判定可視化の変数
		m_uni_pMeshsphere.reset();
	}
#endif // _DEBUG
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Update(void)
{
#ifdef _DEBUG
	// 当たり判定の使用状態がfalse ||
	// ->関数を抜ける
	if (!CCollision::GetUse())
	{
		return;
	}
	// メッシュスフィアが生成されていたら
	if (m_uni_pMeshsphere)
	{
		// あたり判定可視化の変数
		m_uni_pMeshsphere->Update();
	}
#endif // _DEBUG
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Draw(void)
{
#ifdef _DEBUG
	// 当たり判定の使用状態がfalse ||
	// ->関数を抜ける
	if (!CCollision::GetUse())
	{
		return;
	}
	// メッシュスフィアが生成されていたら
	if (m_uni_pMeshsphere)
	{
		// あたり判定可視化の変数
		m_uni_pMeshsphere->Draw();
	}
#endif // _DEBUG
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デバッグ処理
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Debug(void)
{
	// メッシュスフィアが生成されていたら
	if (m_uni_pMeshsphere)
	{
		// メッシュスフィアの位置設定
		m_uni_pMeshsphere->SetPosition(
			m_pSphereShape->m_DestPos
		);
	}
	ImGui::Text("----------SphereCollision_Information----------");
	ImGui::Text("Radius(%.1f)", m_pSphereShape->GetRadius());
	//CDebugproc::Print("----------球の当たり判定情報----------\n");
	//CDebugproc::Print("半径(%.1f)\n", m_pSphereShape->GetRadius());
	CCollision::Debug();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// あたり判定可視カの設定
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSphereCollision::Collision_Visible_Set(void)
{
	// メッシュスフィア
	m_uni_pMeshsphere = std::move(CMeshsphere::Create_Unique(
		m_pSphereShape->m_DestPos,
		m_pSphereShape->GetRadius(),
		10,
		10,
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f),
		CMeshsphere::TEXTYPE_NONE
	));
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
	bool const &bOpponent,
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosold
)
{
	// 変数宣言
	CSphereCollision *pSphereCollision;
	// メモリ確保
	pSphereCollision = new CSphereCollision();
	// 球の生成
	pSphereCollision->m_pSphereShape = std::move(CSphereShape::Create(offset, fRadius,bPush,bOpponent, pPos,pPosold));
	// 球の設定
	pSphereCollision->SetObjectID(obj);												// オブジェクト番号設定
	pSphereCollision->SetOwnScene(pOwner);
	pSphereCollision->SetParent(pParent);
	pSphereCollision->m_pSphereShape->m_pmove = pOwner->Scene_GetPMove();
	// シーン管理設定
	pSphereCollision->ManageSetting(CScene::LAYER_COLLISION);
#ifdef _DEBUG
	// あたり判定可視化設定処理
	pSphereCollision->Collision_Visible_Set();
#endif // _DEBUG
	return pSphereCollision;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 作成処理(個人管理)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::unique_ptr<CSphereCollision> CSphereCollision::Create_Self(
	float const &fRadius,
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
	std::unique_ptr<CSphereCollision> pSphereCollision(new CSphereCollision);
	// 球の形を生成
	pSphereCollision->m_pSphereShape = std::move(CSphereShape::Create(offset, fRadius,bPush,bOpponent, pPos,pPosold));
	// 球の設定
	pSphereCollision->SetObjectID(obj);		// オブジェクト番号設定
	pSphereCollision->SetOwnScene(pOwner);
	pSphereCollision->SetParent(pParent);
	if (pOwner != NULL)
	{
		pSphereCollision->m_pSphereShape->m_pmove = pOwner->Scene_GetPMove();
	}
#ifdef _DEBUG
	// あたり判定可視化設定処理
	pSphereCollision->Collision_Visible_Set();
#endif // _DEBUG
	return pSphereCollision;
}