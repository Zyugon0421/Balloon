// ==========================================================
//
// プレイヤー(復活)処理 [revival.h]
// Author : RYOUMA INOUE
//
// ==========================================================
#ifndef _REVIVAL_H_
#define _REVIVAL_H_

#define _CRT_SECURE_NO_WARNINGS

// ==========================================================
// インクルードファイル
// ==========================================================
#include "player.h"

// ==========================================================
// 前方宣言
// ==========================================================


// ==========================================================
// クラス
// ==========================================================
class CRevival : public CPlayer
{
public:
	// ---------モーションタイプ---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CPlayer::MOTIONTYPE_MAX
	} MOTIONTYPE;
	/* 関数 */
	CRevival();
	~CRevival();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// プレイヤーが死んだときの関数
	void Die(void);
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	// 当たった後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_MyCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	);
	// 相手に当てられた後の処理
	//	nObjType	: オブジェクトタイプ
	//	pScene		: 相手のシーン情報
	virtual void Scene_OpponentCollision(
		int const &nObjType = 0,	// オブジェクトタイプ
		CScene * pScene = NULL		// 相手のシーン情報
	);
	// 生成処理(シーン管理)
	static CRevival * Create(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);			// 作成
				// 生成処理(個人管理)
	static CRevival * Create_Self(
		int const &nPlayerID,
		D3DXVECTOR3 const & pos = D3DVECTOR3_ZERO,
		D3DXVECTOR3 const & rot = D3DVECTOR3_ZERO
	);
	static HRESULT Load(void);			// 読み込み
	static void UnLoad(void);			// UnLoadする

	void CreateBalloon(void);			// 風船の作成
protected:
private:
	/* 構造体 */
	/* 関数 */

	/* 変数 */
	bool m_bRevival;					// 復活するかどうか
};
#endif
