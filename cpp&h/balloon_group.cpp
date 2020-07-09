// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// ���D�O���[�v�����̐���[balloon_group.cpp]
// Author : Koki Nishiyama
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "balloon_group.h"
#include "p_thunder.h"
#include "3Dparticle.h"
#include "selectcharacter.h"
#include "spherecollision.h"
#include "circleshadow.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �}�N����`
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BALLOON_GROUP_SPEED (10.0f)
#define BALLOON_GROUP_Y (50.0f)
#define BALLOON_GROUP_RADIUS (50.0f)

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �ÓI�ϐ��錾
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::CBalloon_group() : CScene::CScene()
{
	// ������
	m_nPopBalloon_group = 2;
	m_nBringBalloon_group = 0;
	m_mtx = NULL;
	m_fAngleBalloon_group = 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group::~CBalloon_group()
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ����������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Init(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �I������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Uninit(void)
{
	// �I������
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �X�V����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Update(void)
{
	// ���D�̍X�V����
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// �X�V
		m_apBalloon[nCntBalloon_group]->Update();
		// ���D�O���[�v������鏈��
		BreakBalloon_group(nCntBalloon_group);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �`�揈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Draw(void)
{
	// ���D�̍X�V����
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// �`��
		m_apBalloon[nCntBalloon_group]->Draw();
	}
}

#ifdef _DEBUG
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �f�o�b�O�\��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::Debug(void)
{
	/*
	CDebugproc::Print("�������Ă��镗�D�O���[�v�̐�[%d]\n", m_nBringBalloon_group);
	CDebugproc::Print("�o�����Ă��镗�D�O���[�v�̐�[%d]\n", m_nPopBalloon_group);
	*/
}
#endif // _DEBUG

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �s����ݒ菈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetMatrix(D3DXMATRIX * mtx)
{
	// �s����̃|�C���^�[���R�s�[����
	m_mtx = mtx;
	// ���D�̐e�s����ݒ菈��
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] == NULL) continue;
		// �e�s��̐ݒ�
		m_apBalloon[nCntBalloon_group]->SetParentMtx(m_mtx);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �O�ɏo���Ēu���镗�D�O���[�v�̍ő����ݒ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::SetPopMaxBalloom(
	int const & nPopMaxBaloon,
	CScene * pParent
)
{
	// �ő�o��������
	m_nMaxPopBalloon_group = nPopMaxBaloon;
	// �p�x
	m_fAngleBalloon_group = D3DX_PI / m_nMaxPopBalloon_group * 2;
	// �����ݒ�
	for (int nCntBalloon_group = 0; nCntBalloon_group < m_nMaxPopBalloon_group; nCntBalloon_group++)
	{
		//���D�O���[�v����
		m_apBalloon.push_back(CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
				D3DVECTOR3_ZERO,
				0
			));
		// �����蔻��ݒ�(��)
		m_apBalloon[nCntBalloon_group]->SetCollision(
			CShape::SHAPETYPE_SPHERE,
			CCollision::OBJTYPE_BALLOON,
			false,
			pParent
		);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D�O���[�v�𐶐�����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::CreateBalloon_group(
	CScene * pParent
)
{
	// ���D�O���[�v��������
	for (int nCntBalloon_group = 0; nCntBalloon_group < (signed)m_apBalloon.size(); nCntBalloon_group++)
	{
		// ���D��NULL�`�F�b�N
		// ->���[�v�X�L�b�v
		if (m_apBalloon[nCntBalloon_group] != NULL) continue;
		// �v���C���[(��)����
		m_apBalloon[nCntBalloon_group] = CBalloon::Create_Self(
			D3DXVECTOR3(
				sinf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS,
				BALLOON_GROUP_Y,
				cosf(m_fAngleBalloon_group * (nCntBalloon_group + 1)) * BALLOON_GROUP_RADIUS),
			D3DVECTOR3_ZERO,
			0
		);
		// �����蔻��ݒ�(��)
		m_apBalloon[nCntBalloon_group]->SetCollision(
			CShape::SHAPETYPE_SPHERE,
			CCollision::OBJTYPE_BALLOON,
			false,
			pParent
		);
		// �e�s��̐ݒ�
		m_apBalloon[nCntBalloon_group]->SetParentMtx(m_mtx);
		// �����Ă��镗�D�O���[�v�̌������炷
		m_nBringBalloon_group--;
		// �o�����Ă��镗�D�O���[�v�̌��𑝂₷
		m_nPopBalloon_group++;
		// �G�t�F�N�g��p�ӂ���Ȃ炱��




		// �����������I��������
		// ->�֐��𔲂���
		break;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D���擾����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon * CBalloon_group::GetBalloon(int const & nBalloon_group)
{
	// 0 < nBalloon_group <= BALLOON_GROUP_MAX�Ȃ�
	// ->�֐��𔲂���
	if (nBalloon_group < 0 || nBalloon_group >= (signed)m_apBalloon.size())
	{
#ifdef _DEBUG
		CCalculation::Messanger("CBalloon_group::GetSceneX->����z��");
#endif // _DEBUG
		return NULL;
	}
	// ���D�̏���Ԃ�
	return m_apBalloon[nBalloon_group];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �쐬����
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CBalloon_group * CBalloon_group::Create(
	D3DXMATRIX *mtx,			// �s��
	int const &nPopMaxBalloon_group,	// �ő啗�D�O���[�v��
	CScene * pParent			// �e���
)
{
	// �ϐ��錾
	CBalloon_group * pBalloon_group;		// �V�[��3D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pBalloon_group = new CBalloon_group();
	// �V�[���Ǘ��ݒ�
	pBalloon_group->ManageSetting(CScene::LAYER_3DOBJECT);
	// ����������
	pBalloon_group->Init();
	// �O�ɏo���Ēu���镗�D�O���[�v�̍ő����ݒ�
	pBalloon_group->SetPopMaxBalloom(
		nPopMaxBalloon_group,
		pParent
	);
	// �o�����Ă��镗�D�O���[�v�̌��ɑ������
	pBalloon_group->m_nPopBalloon_group = nPopMaxBalloon_group;
	// �s����ݒ�
	pBalloon_group->SetMatrix(mtx);
	// ���������I�u�W�F�N�g��Ԃ�
	return pBalloon_group;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���\�[�X���ǂݍ��ސݒ�
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CBalloon_group::Load(void)
{
	return S_OK;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ǂݍ��񂾃��\�[�X�����J������
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::UnLoad(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ���D�O���[�v������鏈��
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CBalloon_group::BreakBalloon_group(int const &nCntBalloon_group)
{
	// �����蔻���Ԃ�true�Ȃ�
	// ->�J��
	if (m_apBalloon[nCntBalloon_group]->GetBalloonCollision())
	{
		m_apBalloon[nCntBalloon_group]->Uninit();
		delete m_apBalloon[nCntBalloon_group];
		m_apBalloon[nCntBalloon_group] = NULL;
		// �o�����Ă��镗�D�O���[�v�̌��𑝂₷
		m_nPopBalloon_group--;
	}
}