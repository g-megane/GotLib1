//////////////////////////////////////////////////
// �쐬��:2017/4/22
// �X�V��:2017/4/22
// �����:got
//////////////////////////////////////////////////
#include <winerror.h>
#include "MyXInput.h"

namespace got
{
    MyXInput::MyXInput()
    {
        padInputPrev = false;
        ZeroMemory(controllers, sizeof(CONTROLLER_STATE) * MAX_CONTROLLERS);
    }
    
    MyXInput::~MyXInput()
    {
    }
    // XInput�̍X�V����
    HRESULT MyXInput::updateControllerState()
    {
        DWORD result;
        for (DWORD i = 0; i < MAX_CONTROLLERS; ++i) {
            controllers[i].statePrev = controllers[i].state;
            result = XInputGetState(i, &controllers[i].state);

            if (result == ERROR_SUCCESS) {
                controllers[i].connected = true;
            }
            else {
                controllers[i].connected = false;
            }

        }

        return S_OK;
    }
    // �{�^����������Ă��邩�H
    bool MyXInput::isButtonDown(const DWORD playerIndex_, const WORD key_)
    {
        return controllers[playerIndex_].state.Gamepad.wButtons & key_;
    }
    // �{�^���������ꂽ�u�Ԃ��H
    bool MyXInput::isButtonPressed(const DWORD playerIndex_, const WORD key_)
    {
        return (controllers[playerIndex_].statePrev.Gamepad.wButtons == 0) && (controllers[playerIndex_].state.Gamepad.wButtons & key_);
    }
    // �{�^���������ꂽ�u�Ԃ��H
    bool MyXInput::isButtonReleased(const DWORD playerIndex_, const WORD key_)
    {
        return (controllers[playerIndex_].state.Gamepad.wButtons == 0) && (controllers[playerIndex_].statePrev.Gamepad.wButtons & key_);
    }

    bool MyXInput::isPadUp(const DWORD playerIndex_)
    {
        if (isNeutral(playerIndex_)) {
            padInputPrev = false;
            return false;
        }
        if (!padInputPrev && controllers[playerIndex_].statePrev.Gamepad.sThumbLY < controllers[playerIndex_].state.Gamepad.sThumbLY) {
            padInputPrev = true;
            return true;
        }

        return false;
    }

    bool MyXInput::isPadDown(const DWORD playerIndex_)
    {
        if (isNeutral(playerIndex_)) {
            padInputPrev = false;
            return false;
        }
        if (!padInputPrev && controllers[playerIndex_].statePrev.Gamepad.sThumbLY > controllers[playerIndex_].state.Gamepad.sThumbLY) {
            padInputPrev = true;
            return true;
        }

        return false;
    }

    bool MyXInput::isPadRight(const DWORD playerIndex_)
    {
        if(isNeutral(playerIndex_)) {
            padInputPrev = false;
            return false;
        }
        if (!padInputPrev && controllers[playerIndex_].statePrev.Gamepad.sThumbLX < controllers[playerIndex_].state.Gamepad.sThumbLX) {
            padInputPrev = true;
            return true;
        }

        return false;
    }

    bool MyXInput::isPadLeft(const DWORD playerIndex_)
    {
        if (isNeutral(playerIndex_)) {
            padInputPrev = false;
            return false;
        }
        if (!padInputPrev && controllers[playerIndex_].statePrev.Gamepad.sThumbLX > controllers[playerIndex_].state.Gamepad.sThumbLX) {
            padInputPrev = true;
            return true;
        }

        return false;
    }

    // �p�b�h�̃x�N�g����Ԃ�
    Vector2<float> MyXInput::padVec(const DWORD playerIndex_, const bool useDeadZone)
    {
        if (useDeadZone) {
            if (isNeutral(playerIndex_)) {
                return Vector2<float>::ZERO;
            }
        }

        return Vector2<float>(static_cast<float>(controllers[playerIndex_].state.Gamepad.sThumbLX),
                              static_cast<float>(-controllers[playerIndex_].state.Gamepad.sThumbLY)
                             ).normalize();
    }
    // ���̃o�C�u���[�V�����̐ݒ�(�U����)
    void MyXInput::setLeftVibration(const DWORD playerIndex_, const WORD motorSpeed)
    {
        controllers[playerIndex_].vibration.wLeftMotorSpeed = motorSpeed;
        XInputSetState(playerIndex_, &controllers[playerIndex_].vibration);
    }
    // �E�̃o�C�u���[�V�����̐ݒ�(�U����)
    void MyXInput::setRightVibration(const DWORD playerIndex_, const WORD motorSpeed)
    {
        controllers[playerIndex_].vibration.wRightMotorSpeed = motorSpeed;
        XInputSetState(playerIndex_, &controllers[playerIndex_].vibration);
    }
    // �p�b�h���j���[�g�����Ȉʒu�ɂ��邩�H
    bool MyXInput::isNeutral(const DWORD playerIndex_)
    {
        return
            (controllers[playerIndex_].state.Gamepad.sThumbLX <  INPUT_DEADZONE  &&
             controllers[playerIndex_].state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
            (controllers[playerIndex_].state.Gamepad.sThumbLY <  INPUT_DEADZONE  &&
             controllers[playerIndex_].state.Gamepad.sThumbLY > -INPUT_DEADZONE);
    }
}
