#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

bool Controller::shot()
{
    if (got::MyXInput::getInstance().isButtonDown(0, XINPUT_GAMEPAD_A)) {
        return true;
    }
    else if (got::MyDirectInput::getInstance().keyDown(DIK_Z)) {
        return true;
    }

    return false;
}

bool Controller::speedDown()
{
    if (got::MyXInput::getInstance().isButtonDown(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
        return true;
    }
    else if (got::MyDirectInput::getInstance().keyDown(DIK_LSHIFT)) {
        return true;
    }

    return false;
}

got::Vector2<float> Controller::move()
{
    float x = 0.0f;
    float y = 0.0f;

    if (got::MyDirectInput::getInstance().keyDown(DIK_RIGHT)) {
        x = 1.0f;
    }
    else if (got::MyDirectInput::getInstance().keyDown(DIK_LEFT)) {
        x = -1.0f;
    }

    if (got::MyDirectInput::getInstance().keyDown(DIK_UP)) {
        y = -1.0f;
    }
    else if (got::MyDirectInput::getInstance().keyDown(DIK_DOWN)) {
        y = 1.0f;
    }

    return (got::MyXInput::getInstance().padVec(0) + got::Vector2<float>(x, y).normalize()).normalize();
}

bool Controller::pause()
{
    return got::MyXInput::getInstance().isButtonPressed(0, XINPUT_GAMEPAD_START) || got::MyDirectInput::getInstance().keyPressed(DIK_P);
}


