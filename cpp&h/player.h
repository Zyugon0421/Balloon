// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���f������ [player.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "character.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �}�N����`
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O���錾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CPlayer : public CCharacter
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_MAX = CCharacter::MOTIONTYPE_MAX
	} MOTIONTYPE;
	// ---------�L�����N�^�[�^�C�v---------- //
	typedef enum
	{
		CHARATYPE_THUNDER = 0,
		CHARATYPE_ZOMBIE,
		CHARATYPE_MAX
	} CHARATYPE;
	/* �֐� */
	CPlayer(CCharacter::CHARACTER const &character);
	virtual ~CPlayer();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	// �v���C���[�����񂾂Ƃ��̊֐�
	virtual void Die(void);
	// �v���C���[�ԍ��̐ݒ�
	void SetPlayerID(int const &nPlayerID) { m_nPlayerID = nPlayerID; };
	// �v���C���[�ԍ��̎擾
	int const &GetPlayerID(void) { return m_nPlayerID; };
#ifdef _DEBUG
	void Debug(void);
#endif // _DEBUG
	static HRESULT Load(void);			// �ǂݍ���
	static void UnLoad(void);			// UnLoad����
protected:
private:
	/* �\���� */
	/* �֐� */
	void MyMove(void);					// ���L�����ړ�����
	void MyAction(void);				// ���L�����s������
	void Camera(void);					// �J��������
	void OtherMove(void);				// ���L�����ړ�����
	void OtherAction(void);				// ���L�����s������
	/* �ϐ� */
	static int	m_All;					// ����
	D3DXVECTOR3	m_posold;				// �O�̈ʒu
	int m_nPlayerID;							// �ԍ�
};
#endif