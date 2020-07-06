// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 兵士処理 [solider.cpp]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "solider.h"
#include "3Dparticle.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CSolider::m_nAllNum = 0;		// 現在存在している数
int CSolider::m_nKoCount = 0;		// 倒した数

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// オーバーロードコンストラクタ(自身用)
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSolider::CSolider() : CEnemy::CEnemy(CHARACTER_NPC)
{
	m_nID = m_nAllNum;
	// 総数アっプ
	m_nAllNum++;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// デストラクタ処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSolider::~CSolider()
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::Init(void)
{
	// 敵の初期化
	CEnemy::Init();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 静的変数の初期化処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::StaticInit(void)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 終了処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::Uninit(void)
{
	// 敵の終了処理
	CEnemy::Uninit();
	// 総数ダウン
	m_nAllNum--;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 更新処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::Update(void)
{
	// 敵の更新処理
	CEnemy::Update();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::Draw(void)
{
	// 敵の描画処理
	CEnemy::Draw();

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 死亡処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::Die(void)
{
	// 敵の描画処理
	CEnemy::Die();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// シーン継承の当たり判定処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::Scene_Collision(int const & nObjType, CScene * pScene)
{
	CEnemy::Scene_Collision(nObjType, pScene);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 生成処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CSolider * CSolider::Create(
	D3DXVECTOR3 const & pos,	// 位置
	D3DXVECTOR3 const & rot		// 回転
)
{
	// 変数宣言
	CSolider * pSolider;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pSolider = new CSolider();
	// シーン管理設定
	pSolider->ManageSetting(CScene::LAYER_CHARACTER);
	// 位置設定
	pSolider->SetPos(pos);
	// 回転設定
	pSolider->SetRot(rot);
	// 初期化処理
	pSolider->Init();
	// 生成したオブジェクトを返す
	return pSolider;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CSolider::LoadCreate(void)
{
	// 変数宣言
	D3DXVECTOR3 pos;
	for (int nCntCreate = 0; nCntCreate < 10; nCntCreate++)
	{
		// 位置設定
		pos.x = (float)(rand() % 1000) - (float)(rand() % 1000);
		pos.y = 10.0f;
		pos.z = (float)(rand() % 1000) - (float)(rand() % 1000);
		// 作成
		CSolider::Create(pos);
	}
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込み処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CSolider::Load(void)
{
	return S_OK;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 読み込んだ情報を破棄処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::UnLoad(void)
{
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 総数処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CSolider::GetAllNum(void)
{
	return m_nAllNum;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 移動処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::move(void)
{
	// 変数宣言
	D3DXVECTOR3 pos;	// 位置
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 回転処理
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CSolider::rot(void)
{
	// 変数宣言
	D3DXVECTOR3 rot;	// 回転
}

#ifdef _DEBUG
//-------------------------------------------------------------------------------------------------------------
// デバッグ表示
//-------------------------------------------------------------------------------------------------------------
void CSolider::Debug(void)
{
	CEnemy::Debug();
}
#endif // _DEBUG
