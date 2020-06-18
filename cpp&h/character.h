// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �L�����N�^�[���� [character.h]
// Author : KOKI NISHIYAMA
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "model.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O���錾
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CExtrusion;
class CMeshobit;
class CCollision;
class CStencilshadow;
class CBalloon;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �\����
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �N���X
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CCharacter : public CScene
{
public:
	/* �񋓌^ */
	// �X�e�[�^�X
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DIE,
		STATE_MAX
	} STATE;
	// ��{���[�V�����^�C�v
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@���[�V����
		MOTIONTYPE_MOVE,			// �ړ����[�V����
		MOTIONTYPE_DAMAGEACTION,	// �_���[�W���[�V����
		MOTIONTYPE_DOWNACTION,		// �_�E�����[�V����
		MOTIONTYPE_STANDUP,			// �N���オ�郂�[�V����
		MOTIONTYPE_MAX
	} MOTIONTYPE;
	// �L�����N�^�[
	typedef enum
	{
		// �v���C���[�p //
		CHARACTER_P_THUNDER = 0,				// ���g��
		CHARACTER_P_ZOMBIE,						// �]���r
		CHARACTER_PLAYERMAX,					// �v���C���[�p�̃L�����N�^�[�ő吔
		// �v���C���[�p //
		// �G�p //
		CHARACTER_NPC = CHARACTER_PLAYERMAX,	// NPC
		// �G�p //
		CHARACTER_MAX,							// �L�����N�^�[�S�̐�
	} CHARACTER;
	// �G�p�L�����N�^�[�ő吔
#define CHARACTER_ENEMYMAX (CHARACTER_MAX - CHARACTER_PLAYERMAX)	// �G�p�L�����N�^�[�ő吔

	/* �\���� */
	// �X�e�[�^�X���
	typedef struct STATUS
	{
		/* �֐� */
		// ������
		STATUS()
		{
			nMaxBalloon = 0;			// �ő啗�D��
			nMaxPopBalloon = 0;			// �ő�o�����D��
			fMaxInertia = 0;			// ������
			fMaxJump = 0;				// �W�����v��
			fMaxMove = 0;				// �ړ���
		}
		/* �ϐ� */
		int			nMaxBalloon;		// �ő啗�D��
		int			nMaxPopBalloon;		// �ő�o�����D��
		float		fMaxInertia;		// ������
		float		fMaxJump;			// �W�����v��
		float		fMaxMove;			// �ړ���
	} STATUS, *PSTATUS;
	/* �֐� */
	CCharacter(CHARACTER const &character);
	virtual ~CCharacter();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	// �L�����N�^�[�����񂾂Ƃ�
	virtual void Die(void);
	// ���D����
	void BalloonCreate(void);
	// �K�v�ɉ��������� //
	// �ݒ� //
	// �ʒu
	void SetPos(D3DXVECTOR3 const &pos)				{ m_pos = pos; };			
	// �ړ���
	void SetMove(D3DXVECTOR3 const &move)			{ m_move = move; };
	// ��]
	void SetRot(D3DXVECTOR3 const &rot)				{ m_rot = rot; };
	// �擾 //
	// �ʒu
	D3DXVECTOR3 &GetPos(void)						{ return m_pos; };
	// �ړ���
	D3DXVECTOR3 &GetMove(void)						{ return m_move; };
	// ��]
	D3DXVECTOR3 &GetRot(void)						{ return m_rot; };
	// �e�Ǝq�̉�]��
	D3DXVECTOR3 *GetPartsRot(int const nModelID);
	// �e�Ǝq�̈ʒu
	D3DXVECTOR3 * GetPartsPos(int const nModelID);
	// �e�Ǝq�̍s��
	D3DXMATRIX *GetMatrix(int const nModelID);	
	// ���
	STATE GetState(void) const						{ return m_State; };
	// �L�����N�^�[
	CHARACTER	GetCharacter(void) const			{ return m_character; };
	// �X�e�[�^�X(�L�����N�^�[�̃N���X�����N���X�Ɏ����Ă���N���X)
	STATUS &GetStatus(void) { return m_sStatus[m_character]; };
	// �X�e�[�^�X(�L�����N�^�[��)
	// ����:�L�����N�^�[�ԍ�
	static STATUS &GetStatus(CHARACTER const &character) { return m_sStatus[character]; };
	// ���̍���
	bool GetFloorHeight(void);
	// ���[�V�����̃t���[�����擾����
	int GetMaxFrame(
		CHARACTER character,					// �L�����N�^�[
		int nMotionID,							// ���[�V����ID
		int nNowKeyCnt = -1						// ���݂̃L�[�J�E���g
	);
	// �o���[���̏��擾
	CBalloon * GetBalloon(void) { return m_pBalloon; };
	// �J�����ǔ����Ă���ID
	static int GetCameraCharacter(void);
	/*
	// ���[�h�E�A�����[�h
	static void Load(
		CHARACTER const character,		// �L�����N�^�[
		int const nMaxMotion,			// �ő僂�[�V����
		const char * file_name			// �t�@�C����
		);
		*/
	// �L�����N�^�[�S�\�[�X�̓ǂݍ���
	static HRESULT Load(void);
	// �L�����N�^�[�̏��ǂݍ���
	static HRESULT Load_Character(void);
	// �X�e�[�^�X���ǂݍ���
	static HRESULT LoadStatus(void);
	// �L�����N�^�[�S�\�[�X�̊J��
	static void UnLoad(void);
	// �L�����N�^�[�̐ÓI�ϐ��̏�����
	static void InitStatic(void);

#ifdef _DEBUG
	void Debug(void);
	static void AllDebug(void);
#endif // _DEBUG
	CCollision * GetCollision(void) { return m_pCharacterCollision.get(); };
protected:
	/* �֐� */
	// �ݒ� //
	// �L�����N�^�[
	void SetCharacter(CHARACTER const character)	{ m_character = character; };
	// ���[�V�����ݒ�
	void SetMotion(int const nMotiontype);
	// �������[�V�����ݒ�
	void ComplusionSetMotion(int const nMotiontype);
	// �d��
	void FagGravity(void);						// �d��
	// �ڕW��]�ʐݒ�
	void SetRotDest(D3DXVECTOR3 const &rotDest)		{ m_rotLast = rotDest; };	
	// �ݒ� //
	// ���݂̃��[�V����
	int GetMotion(void) const						{ return m_nMotiontype; };
	// �ߋ��̃��[�V����
	int GetOldMotion(void) const					{ return m_nMotiontypeOld; };
	// �L�[�J�E���g
	int GetKeyInfoCnt(void) const					{ return m_keyinfoCnt; };
	// �ڕW��]�ʎ擾
	D3DXVECTOR3 GetRotDest(void) const				{ return m_rotLast; };	

	// ���[�V�����J�����̍X�V
	void MotionCamera(void);							
	/* �ϐ� */
	static int						m_nCameraCharacter;	// �L�����N�^�[�ɒǔ�����ID
	// ��
	STATE							m_State;			// ����̃X�e�[�^�X
	int								m_nCntState;		// �J�E���g�X�e�[�^�X

private:
	/* �֐� */
	void Collision(void);								// ���ꂼ��̓����蔻��
	void BalloonCollision(CBalloon * pBalloon);			// ���D�Ƃ̓����蔻��
	void Update_Normal(void);							// �ʏ펞�̍X�V
	void NextKeyMotion(void);							// ���̃��[�V����
	void Move(void);									// �ړ�
	void Motion(void);									// ���[�V����
	void ModelUpdate(void);								// ���f���̍X�V
	void TrackCamera(void);								// �J�����ǔ�
	void Limit(void);									// �������
	void Motion_Effect(void);							// ���[�V�����G�t�F�N�g		
	void Motion_Obit(void);								// ���[�V�����O��
	void BalloonNone(void);								// ���D���Ȃ��ꍇ
	/* �ϐ� */
	/* �\���̂̃X�^�e�B�b�N�ɂ��� */
	static MODEL_ALL				*m_modelAll[CHARACTER_MAX];		// ���f���S�̂̏��
	static vector<int>				m_modelId[CHARACTER_MAX];		// ���f���ԍ�
	static CModel_info				*m_model_info[CHARACTER_MAX];	// ���f�����
	static D3DXVECTOR3				m_CharacterSize[CHARACTER_MAX];	// �L�����N�^�[�̃T�C�Y
	static int						m_NumModel[CHARACTER_MAX];		// �ő僂�f����
	static int						m_NumParts[CHARACTER_MAX];		// ���������f����
	static STATUS					m_sStatus[CHARACTER_MAX];		// �L�����N�^�[���ׂẴX�^�[�^�X���
	static int						m_nAllCharacter;				// �o�����Ă���L�����N�^�[�l��
	CMeshobit						*m_pMeshobit;					// �O��
	CModel 							*m_pModel;						// ���f��
	CHARACTER						m_character;					// �L�����N�^�[
	D3DXMATRIX						m_mtxWorld;						// �s��
	D3DXVECTOR3						m_pos;							// �ʒu
	D3DXVECTOR3						m_posold;						// �O�̈ʒu
	D3DXVECTOR3						m_move;							// �ړ���
	D3DXVECTOR3						m_rot;							// ���݉�]��
	D3DXVECTOR3						m_rotLast;						// ������������
	D3DXVECTOR3						m_rotbetween;					// ��]�̍���
	D3DXVECTOR3						m_size;							// �L�����N�^�[�̃T�C�Y
	int								m_nMotiontype;					// ���[�V�����^�C�v
	int								m_nMotiontypeOld;				// �O��̃��[�V�����^�C�v
	int								m_nMaxMotion;					// �ő僂�[�V������
	int								m_keyinfoCnt;					// �L�[���̃J�E���g
	int								m_nFrame;						// �t���[���J�E���g
	int								m_nMotionFrame;					// ��̃��[�V�����̃J�E���g
	int								m_nIdAttackKey;					// �U���p�̃L�[ID
	int								m_nIDWho;						// �G��������
	float							m_fLength;						// �U���̓�����͈�
	float							m_fAlpha;						// �A���t�@�l
	bool							m_bMotionCamera;				// ���[�V�����J�����̐؂�ւ�ON�EOFF
	unique_ptr<CCollision>			m_pCharacterCollision;			// �L�����N�^�[�̓����蔻��
	vector<unique_ptr<CCollision>>	m_vec_AttackCollision;			// �U�������蔻��
	vector<unique_ptr<CMeshobit>>	m_vec_pMeshObit;				// ���
	CStencilshadow					* m_pStencilshadow;				// �X�e���V���V���h�E
	CBalloon						* m_pBalloon;					// ���D���
};

#endif