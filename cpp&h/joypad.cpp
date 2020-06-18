// ------------------------------------------
//
// �R���g���[���[���� [joypad.cpp]
// Author : KOKI NISHIYAMA
//
// ------------------------------------------
#include "joypad.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------
#define GAMEPAD_MAX_RANGE (1024)
#define MAX_TRUN (32768.0f)
#define COUNT_WAIT_REPEAT (20)
#define INTERVAL_REPEAT (1)

// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------
LPDIRECTINPUTDEVICE8 CJoypad::m_pJoyDevice[MAX_GAMEPAD] = {};	// ���̓f�o�C�X�ւ̃|�C���^
int CJoypad::m_nCntpad = 0;								// �J�E���g

// ------------------------------------------
//
// �O���[�o���ϐ�
//
// ------------------------------------------

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CJoypad::CJoypad()
{
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CJoypad::~CJoypad()
{
}

// ------------------------------------------
// ������
// ------------------------------------------
HRESULT CJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���̓f�o�C�X�̏�����
	if (!CInput::Init(hInstance, hWnd) == S_OK)
	{
		return E_FAIL;
	}

	// ����
	m_nCntWaitRepeat = COUNT_WAIT_REPEAT;
	m_nIntervalRepeat = INTERVAL_REPEAT;

	for (int nCntPad = 0; nCntPad < MAX_GAMEPAD; nCntPad++)
	{
		// ���̓f�o�C�X�i�Q�[���p�b�h�j�̍쐬
		if (FAILED(m_pInput->EnumDevices(
			DI8DEVCLASS_GAMECTRL,
			EnumCallback,
			NULL,
			DIEDFL_ATTACHEDONLY)) ||
			m_pJoyDevice[m_nCntpad] == NULL)
		{
			return E_FAIL;
		}
		// �f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(m_pJoyDevice[m_nCntpad]->SetDataFormat(&c_dfDIJoystick2)))
		{
			return E_FAIL;
		}
		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		if (FAILED(m_pJoyDevice[m_nCntpad]->SetCooperativeLevel(
			hWnd,
			(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		/* -------------------�p�b�h�̐ݒ�------------------- */
		// �ϐ��錾
		DIPROPRANGE diprg;			// �f�o�C�X�̐ݒ�
									// �\���̂̒��g��NULL�ɂ���
		ZeroMemory(&diprg, sizeof(diprg));

		/* ----------diprg�̐ݒ�---------- */
		/* diph�̒��g */
		diprg.diph.dwSize = sizeof(diprg);				// diprg�\���̂̃��������i�[
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);	// diph�\���̂̃��������i�[
		diprg.diph.dwHow = DIPH_BYOFFSET;				// ���̏��Ȃ̂���

														/* �p�b�h�̍ŏ��l�E�ő�l*/
		diprg.lMin = -GAMEPAD_MAX_RANGE;
		diprg.lMax = GAMEPAD_MAX_RANGE;

		/* ���ꂼ��̃p�b�h����ݒ� */
		// X���̐ݒ�
		diprg.diph.dwObj = DIJOFS_X;	// �p�b�h��x�̏��
		m_pJoyDevice[m_nCntpad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���̐ݒ�
		diprg.diph.dwObj = DIJOFS_Y;	// �p�b�h��y�̏��
		m_pJoyDevice[m_nCntpad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z���̐ݒ�
		diprg.diph.dwObj = DIJOFS_Z;	// �p�b�h��z�̏��
		m_pJoyDevice[m_nCntpad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// RZ���̐ݒ�
		diprg.diph.dwObj = DIJOFS_RZ;	// �p�b�h��rz�̏��
		m_pJoyDevice[m_nCntpad]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ���͐���J�n
		m_pJoyDevice[m_nCntpad]->Acquire();

		// �N���A
		memset(&m_aState[m_nCntpad], 0, sizeof(m_aState[m_nCntpad]));
		memset(&m_abState[m_nCntpad], 0, sizeof(m_abState[m_nCntpad]));
		memset(&m_abStateTrigger[m_nCntpad], 0, sizeof(m_abStateTrigger[m_nCntpad]));
		memset(&m_abStateRelease[m_nCntpad], 0, sizeof(m_abStateRelease[m_nCntpad]));
		memset(&m_abStateRepeat[m_nCntpad], 0, sizeof(m_abStateRepeat[m_nCntpad]));
		//// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		if (m_pJoyDevice[nCntPad] != NULL)
		{
			m_aState[nCntPad].lX = 0;
			m_aState[nCntPad].lY = 0;
		}
	}
	// ����������
	return S_OK;
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CJoypad::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		if (m_pJoyDevice[nCnt]!= NULL)
		{
			m_pJoyDevice[nCnt]->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����J��
			m_pJoyDevice[nCnt]->Release();
			m_pJoyDevice[nCnt] = NULL;
		}
	}

	// �R���g���[���[�f�o�C�X�̏�����
	CInput::Uninit();
}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CJoypad::Update(void)
{
	bool aJoyState[KEY_MAX];	// �L�[�{�[�h�̓��͏��
	bool abLeftStick[4];		// ���X�e�B�b�N�̏��
	int nCntPad;
	int nCntJoy;

	for (nCntPad = 0; nCntPad < MAX_GAMEPAD; nCntPad++)
	{
		if (m_pJoyDevice[nCntPad] == NULL)
		{
			return;
		}

		// �X�e�B�b�N�̏��ۑ�
		for (int nCntDirection = 0; nCntDirection < DIRECTION_MAX; nCntDirection++)
		{
			abLeftStick[nCntDirection] = m_abStick[nCntPad][nCntDirection];
		}
		// �L�[���ۑ�
		for (nCntJoy = 0; nCntJoy < KEY_MAX; nCntJoy++)
		{
			// �L�[�v���X���ۑ�
			aJoyState[nCntJoy] = m_abState[nCntPad][nCntJoy];
		}
		// �f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pJoyDevice[nCntPad]->GetDeviceState(sizeof(m_aState[nCntPad]), &m_aState[nCntPad])))
		{
			// �L�[���ݒ�
			SetState(nCntPad);
			// �X�e�B�b�N���̐ݒ�
			// �X�e�B�b�N�̃g���K�[�E�����[�X�E���s�[�g���̌v�Z
			m_abStick[nCntPad][DIRECTION_LEFT] = m_aState[nCntPad].lX < 0;	// ���̏��
			m_abStick[nCntPad][DIRECTION_RIGHT] = m_aState[nCntPad].lX > 0;	// �E�̏��
			m_abStick[nCntPad][DIRECTION_UP] = -m_aState[nCntPad].lY > 0;	// ��̏��
			m_abStick[nCntPad][DIRECTION_DOWN] = -m_aState[nCntPad].lY < 0;	// ���̏��

			// �X�e�B�b�N���v�Z
			for (int nCntDirection = 0; nCntDirection < DIRECTION_MAX; nCntDirection++)
			{
				// �X�e�B�b�N�g���K�[���̌v�Z
				m_abStickTrigger[nCntPad][nCntDirection] =
					(abLeftStick[nCntDirection] ^ m_abStick[nCntPad][nCntDirection]) &
					m_abStick[nCntPad][nCntDirection];
			}
			for (nCntJoy = 0; nCntJoy < KEY_MAX; nCntJoy++)
			{
				if (!m_sbState)
				{
					CInput::m_sbState = m_abState[nCntPad][nCntJoy];
				}
				/*
				pValueH = m_aState[nJoy].lX;
				pValueV = -m_aState[nJoy].lY;
				*/

				// �g���K�[�E�����[�X�E���s�[�g���̌v�Z
				m_abStateTrigger[nCntPad][nCntJoy] = (aJoyState[nCntJoy] ^ m_abState[nCntPad][nCntJoy]) & m_abState[nCntPad][nCntJoy];
				m_abStateRelease[nCntPad][nCntJoy] = (aJoyState[nCntJoy] ^ m_abState[nCntPad][nCntJoy]) & !m_abState[nCntPad][nCntJoy];
				m_abStateRepeat[nCntPad][nCntJoy] = m_abStateTrigger[nCntPad][nCntJoy];

				// ON�̏��
				if (m_abStateRepeat[nCntPad][nCntJoy])
				{
					m_aStateRepeatCnt[nCntPad][nCntJoy]++;
					if (m_aStateRepeatCnt[nCntPad][nCntJoy] < m_nCntWaitRepeat)
					{
						if (m_abStateRepeat[nCntPad][nCntJoy] == 1)
						{
							m_abStateRepeat[nCntPad][nCntJoy] = m_abState[nCntPad][nCntJoy];
						}

						else
						{
							m_abStateRepeat[nCntPad][nCntJoy] = 0;
						}
					}

					else
					{
						if ((m_abStateRepeat[nCntPad][nCntJoy] - m_nCntWaitRepeat) % m_nIntervalRepeat == 0)
						{
							m_abStateRepeat[nCntPad][nCntJoy] = m_abState[nCntPad][nCntJoy];
						}

						else
						{
							m_abStateRepeat[nCntPad][nCntJoy] = 0;
						}
					}
				}

				else
				{
					m_aStateRepeatCnt[nCntPad][nCntJoy] = 0;
					m_abStateRepeat[nCntPad][nCntJoy] = 0;
				}
			}
		}
		else
		{
			m_pJoyDevice[nCntPad]->Acquire();
		}
	}
}

// ------------------------------------------
// �W���C�p�b�h�\�͎擾
// ------------------------------------------
BOOL CALLBACK CJoypad::EnumCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	// �ϐ��錾
	static GUID pad_discrimination;
	DIDEVCAPS diDevCaps;

	if (FAILED(m_pInput->CreateDevice(pdidInstance->guidInstance, &m_pJoyDevice[m_nCntpad], NULL)))
	{
		return DIENUM_CONTINUE;
	}

	// �f�o�C�X�̔\�͎擾
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(m_pJoyDevice[m_nCntpad]->GetCapabilities(&diDevCaps)))
	{
		m_pJoyDevice[m_nCntpad]->Release();
		m_pJoyDevice[m_nCntpad] = NULL;
		return DIENUM_CONTINUE;
	}

	// �f�o�C�X�̎��ʎq��ۑ�
	pad_discrimination = pdidInstance->guidInstance;
	return DIENUM_STOP;
}

// ------------------------------------------
// �{�^���̐ݒ�
// ------------------------------------------
void CJoypad::SetState(int const &nJoy)
{
	// �ϐ��錾
	int nKey;

	if (m_aState[nJoy].rgdwPOV[0] >= 225 * 100 && m_aState[nJoy].rgdwPOV[0] <= 315 * 100)
	{
		// �\���L�[[��]��������Ă���
		m_abState[nJoy][KEY_LEFT] = true;
	}

	else
	{
		// �\���L�[[��]��������Ă���
		m_abState[nJoy][KEY_LEFT] = false;
	}

	if (m_aState[nJoy].rgdwPOV[0] >= 45 * 100 && m_aState[nJoy].rgdwPOV[0] <= 135 * 100)
	{
		// �\���L�[[�E]��������Ă���
		m_abState[nJoy][KEY_RIGHT] = true;
	}

	else
	{
		// �\���L�[[�E]��������Ă���
		m_abState[nJoy][KEY_RIGHT] = false;
	}

	if ((m_aState[nJoy].rgdwPOV[0] >= 315 * 100 && m_aState[nJoy].rgdwPOV[0] <= 360 * 100) ||
		(m_aState[nJoy].rgdwPOV[0] >= 0 * 100 && m_aState[nJoy].rgdwPOV[0] <= 45 * 100))
	{
		// �\���L�[[��]��������Ă���
		m_abState[nJoy][KEY_UP] = true;
	}

	else
	{
		// �\���L�[[��]��������Ă���
		m_abState[nJoy][KEY_UP] = false;
	}

	if (m_aState[nJoy].rgdwPOV[0] >= 135 * 100 && m_aState[nJoy].rgdwPOV[0] <= 225 * 100)
	{
		// �\���L�[[��]��������Ă���
		m_abState[nJoy][KEY_DOWN] = true;
	}

	else
	{
		// �\���L�[[��]��������Ă���
		m_abState[nJoy][KEY_DOWN] = false;
	}

	for (nKey = KEY_X; nKey <= KEY_START; nKey++)
	{
		if (m_aState[nJoy].rgbButtons[nKey])
		{
			// �{�^����������Ă���
			m_abState[nJoy][nKey] = true;
		}

		else
		{
			m_abState[nJoy][nKey] = false;
		}
	}
}

// ------------------------------------------
// ����������
// ------------------------------------------
bool CJoypad::GetPress(
	int const &nJoy,	// �W���C�p�b�h�̔ԍ�
	KEY const &key		// �L�[���
)
{
	return m_abState[nJoy][key];
}

// ------------------------------------------
// �����ꂽ�Ƃ��̏���
// ------------------------------------------
bool CJoypad::GetTrigger(
	int const &nJoy,	// �W���C�p�b�h�̔ԍ�
	KEY const &key		// �L�[���
)
{
	return m_abStateTrigger[nJoy][key];
}

// ------------------------------------------
// �����[�X����
// ------------------------------------------
bool CJoypad::GetRelease(
	int const &nJoy,	// �W���C�p�b�h�̔ԍ�
	KEY const &key		// �L�[���
)
{
	return m_abStateRelease[nJoy][key];
}

// ------------------------------------------
// ��������
// ------------------------------------------
bool CJoypad::GetRepeat(
	int const &nJoy,	// �W���C�p�b�h�̔ԍ�
	KEY const &key		// �L�[���
)
{
	return m_abStateRepeat[nJoy][key];
}

// ------------------------------------------
// L�{�^�������ꂽ����
// ------------------------------------------
int CJoypad::GetTriggerLeft(
	int const &nJoy,	// �W���C�p�b�h�̔ԍ�
	KEY const &key		// �L�[���
)
{
	return m_aState[nJoy].rgbButtons[KEY_LEFT_2];
}

// ------------------------------------------
// R�{�^�������ꂽ����
// ------------------------------------------
int CJoypad::GetTriggerRight(
	int const &nJoy,	// �W���C�p�b�h�̔ԍ�
	KEY const &key		// �L�[���
)
{
	return m_aState[nJoy].rgbButtons[KEY_RIGHT_2];
}

// ------------------------------------------
// ���X�e�B�b�N�����ꂽ����
// ------------------------------------------
void CJoypad::GetStickLeft(
	int const &nJoy,	// �W���C�p�b�h�ԍ�
	int & pValueH,		// ���������̗�
	int & pValueV		// ���������̗�
)
{
	pValueH = m_aState[nJoy].lX;
	pValueV = -m_aState[nJoy].lY;
}

// ------------------------------------------
// �E�X�e�B�b�N�����ꂽ����
// ------------------------------------------
void CJoypad::GetStickRight(
	int const &nJoy,	// �W���C�p�b�h�ԍ�
	int & pValueH,		// ���������̗�
	int & pValueV		// ���������̗�
)
{
	pValueH = m_aState[nJoy].lZ;
	pValueV = -m_aState[nJoy].lRz;
}