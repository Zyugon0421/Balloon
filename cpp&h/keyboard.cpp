// ------------------------------------------
//
// ���͏��� [keyboard.cpp]
// Author : KOKI NISHIYAMA
//
// ------------------------------------------
#include "keyboard.h"
#include "debugproc.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------

// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CKeyboard::CKeyboard()
{
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CKeyboard::~CKeyboard()
{
}

// ------------------------------------------
// ������
// ------------------------------------------
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���̓f�o�C�X�̏�����
	if (!CInput::Init(hInstance, hWnd) == S_OK)
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CKeyboard::Uninit(void)
{
	// ���̓f�o�C�X�̏I��
	CInput::Uninit();

	// �L�[�{�[�h�̃f�o�C�X�̏I��
	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CKeyboard::Update(void)
{
	// �ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			if (aKeyState[nCntKey] != 0)
			{
				m_sbState = true;
			}
			m_aTrigger[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aState[nCntKey] = aKeyState[nCntKey];	// �L�[�v���X���ۑ�
		}
	}

	else
	{
		m_pDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
	}
}

// ------------------------------------------
// ������Ă����Ԃ��擾
// ------------------------------------------
bool CKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aState[nKey] & 0x80) ? true : false;
}

// ------------------------------------------
// ����������Ԃ��擾
// ------------------------------------------
bool CKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aTrigger[nKey] & 0x80) ? true : false;
}