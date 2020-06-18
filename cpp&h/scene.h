// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �V�[�������̐���[scene.h]
// Author : Koki Nishiyama
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef _SCENE_H_
#define _SCENE_H_	 // �t�@�C������������߂�

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "manager.h"
#include "texture_manager.h"
#include "load.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �N���X
//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class CScene
{
public:
	/* �񋓌^ */
	// ���̔z�u����
	typedef enum
	{
		LAYER_WORLD = 0,
		LAYER_3DOBJECT,
		LAYER_3DSHADOW,
		LAYER_SELECTCHARACTER,
		LAYER_CHARACTER,
		LAYER_3DPARTICLE,
		LAYER_3DOBJECT2,
		LAYER_COLLISION,
		LAYER_UI,
		LAYER_PARTICLE,
		LAYER_FADE,
		LAYER_MAX
	} LAYER;
	/* �֐� */
	CScene();
	virtual ~CScene();
	virtual void Init(void) = 0;										// ������
	virtual void Uninit(void) = 0;										// �I��
	virtual void Update(void) = 0;										// �X�V
	virtual void Draw(void) = 0;										// �`��
#ifdef _DEBUG
	virtual void Debug(void);										// �f�o�b�O�p
#endif // _DEBUG

	static void ReleaseAll(void);										// �V�[���e�q�����[�X
	static void UpdateAll(void);										// �V�[���e�q�X�V
	static void DrawAll(void);											// �V�[���e�q�`��
	// �擾
	// �V�[�����擾(���C���[�E�N���X�w��)
	static CScene * GetScene(
		LAYER const &layer,												// ���C���[
		int const &nCntScene,											// �J�E���g�V�[��
		CScene &										// �N���X�^���
	);
	// �V�[�����擾(���C���[�w��)
	static CScene * GetScene(
		LAYER const &layer,												// ���C���[
		int const &nCntScene											// �J�E���g�V�[��
	);
	// ���C���[���̃V�[���ő吔�擾
	static int GetMaxLayer(LAYER const &layer) 
	{ return (signed)m_pScene[layer].size(); };	
	static bool GetUpdateStop(void) { return m_sta_bStop; };						// �Î~���
	// �ݒ�
	// �V�[���̐Î~
	static void UpdateStop(
		bool const &bStop,												// �Î~���邩���Ȃ���
		int const &nMaxStop = 0											// �ő�Î~����
	);	// �X�V���Ƃ߂�
	// �V�[���Ǘ��ݒ�
	void ManageSetting(LAYER const &layer);
	// �I�u�W�F�N�g�̍X�V�X�g�b�v��Ԑݒ�
	void SetStop(bool const &bStopState)
	{
		m_bStop = bStopState; 
	};
	// �I�u�W�F�N�g�̍X�V�X�g�b�v��Ԏ擾
	bool GetStop(void)
	{
		return m_bStop;
	};
	// �I�u�W�F�N�g�̕`���Ԑݒ�
	void SetDrawState(bool const &bDraw)
	{
		m_bDraw = bDraw;
	};
	// �I�u�W�F�N�g�̕`���Ԏ擾
	bool GetDrawState(void)
	{
		return m_bDraw;
	};

	void Release(void);													// �I�u�W�F�N�g�̔j��
protected:

private:
	/* �֐� */
	static void DeadFragAll(void);				// ���S�t���O�����������̂������[�X
	/* �ϐ� */
	static vector<CScene*> m_pScene[LAYER_MAX];	// �V�[���Ǘ��p�ϐ�
	static bool	m_sta_bStop;						// �X�V���~�߂�
	static int m_nMaxStop;						// �ő�Î~����
	static int m_nCntStop;						// �Î~����
	bool m_bDeadFrag;							// �t���O
	bool m_bStop;								// �X�V���~�߂邩�~�߂Ȃ���
	bool m_bDraw;								// �`����
};

#endif