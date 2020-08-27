// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ゲームヘッダー処理 [game.h]
// Author : KOKI NISHIYAMA
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// インクルードファイル
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "network.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// マクロ定義
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// 前方宣言
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CPause;			// ポーズ
class CScore;			// スコア
class CPlayer;			// プレイヤー

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// クラス
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CGame
{
public:
	/* 列挙型 */
	// 状態
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_PAUSE,
		STATE_MAX
	} STATE;
	/* 関数 */
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
#ifdef _DEBUG
	void Debug(void) {};
#endif // _DEBUG
	// 設定
	static void SetState(STATE const state) { m_state = state; };		// 状態
	// 取得
	static STATE GetState(void) { return m_state; };					// 状態
	// プレイヤーの取得
	static CPlayer *GetPlayer(int nIndex) { return m_pPlayer[nIndex]; }
	// スコアの情報取得
	CScore *GetScore(void) { return m_pScore; };
	// 観戦用
	void FocusPlayer(void);
protected:
private:
	/* 関数 */
	void DebugStatus(void);				// デバッグステータス
	void PauseState(void);				// ポーズの状態
	void PlayerCreate(void);			// プレイヤー生成
	/* 変数 */
	static STATE m_state;				// 状態

	CPause * m_pause;					// ポーズ
	CScore * m_pScore;					// スコア
	static CPlayer * m_pPlayer[MAX_PLAYER];
	int m_nWatchingId;					// 観戦するプレイヤーID

	std::thread th;
};
#endif
