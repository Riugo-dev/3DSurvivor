//********************************************************************************
//
// controller.cpp[コントローラークラス]
//
//															Author :Riugo Honda
//															Date   :2025/09/19
//********************************************************************************

#include "main.h"

#include "controller.h"

#include <Windows.h>
#include <cmath>

#pragma comment(lib, "xinput.lib")


//********************************************************************************
// 関数
//********************************************************************************

//コントローラーの初期化と接続台数の登録
Controller::Controller()
{
    Controller_Initialize();

    // コントローラーの状態を初期化
    ZeroMemory(&g_Controllers.state, sizeof(XINPUT_STATE));

    // 状態を取得
    DWORD result = XInputGetState(g_PlayerIndex, &g_Controllers.state);

    // 結果が成功ならコントローラーが接続されている
    if (result == ERROR_SUCCESS)
    {
        g_Controllers.isConnected = 1;

        g_Controller_Numbers = 1;
    }
    else
    {
        g_Controllers.isConnected = 0;
    }
}

Controller::~Controller()
{
    Controller_SetVibration(0, 0, 0);
}

void Controller::Controller_Initialize()
{
    g_PlayerIndex = 0;

    //初期化時の接続台数
    g_Controller_Numbers = 0;

    LeftStickX = 0;
    LeftStickY = 0;
    RightStickX = 0;
    RightStickY = 0;

    //回転用変数
    //LeftStick（左ステック）
    CurrentStickLocationLeft = 0.0f; //現在のスティック位置
    PreviousStickLocationLeft = 0.0f; //前回のステック位置

    //RightStick（右ステック）
    CurrentStickLocationRight = 0.0f; //現在のスティック位置
    PreviousStickLocationRight = 0.0f; //前回のステック位置

    m_ContinuousRightFrame = 0;
    m_ContinuousLeftFrame = 0;

    m_IsRightStickUp = false;
    m_IsRightStickDown = false;
    m_IsRightStickLeft = false;
    m_IsRightStickRight = false;
    m_IsLeftStickUp = false;
    m_IsLeftStickDown = false;
    m_IsLeftStickLeft = false;
    m_IsLeftStickRight = false;
}

//コントローラーの初期化と接続台数の登録
void Controller::Controller_Set()
{
    {
        g_Controller_Numbers = 0;

        // コントローラーの状態を初期化
        ZeroMemory(&g_Controllers.state, sizeof(XINPUT_STATE));

        // 状態を取得
        DWORD result = XInputGetState(g_Controller_Numbers, &g_Controllers.state);

        // 結果が成功ならコントローラーが接続されている
        if (result == ERROR_SUCCESS)
        {
            g_Controllers.isConnected = 1;

            
        }
        else
        {
            g_Controllers.isConnected = 0;

            g_PlayerIndex = - 1;

        }
    }
}

bool Controller::IsConnected()
{
    // 状態を取得
    DWORD result = XInputGetState(g_PlayerIndex, &g_Controllers.state);

    // 結果が成功ならコントローラーが接続されている
    if (result == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//状態の更新とすべてのプレイヤーの入力処理
void Controller::Controller_Update()
{
    //for (int i = 0; i < g_Controller_Numbers; i++)
    //{  // プレイヤー分の処理
    //    
    //}
    // コントローラーの全体状態を更新
    DWORD result = XInputGetState(g_PlayerIndex, &g_Controllers.state);

    // 結果が成功ならコントローラーが接続されている
    if (result == ERROR_SUCCESS) {
        g_Controllers.isConnected = 1;
    }
    else {
        g_Controllers.isConnected = 0;
        
        return;
    }

    //スティックの過去値更新
    PreviousStickLocationLeft = CurrentStickLocationLeft;
    PreviousStickLocationRight = CurrentStickLocationRight;

   
    // 各ボタンの状態を更新
    Controller_UpdateButtonState(&g_Controllers.aButton, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
    Controller_UpdateButtonState(&g_Controllers.bButton, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
    Controller_UpdateButtonState(&g_Controllers.xButton, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
    Controller_UpdateButtonState(&g_Controllers.yButton, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
    Controller_UpdateButtonState(&g_Controllers.rshoulder, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
    Controller_UpdateButtonState(&g_Controllers.lshoulder, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
    Controller_UpdateButtonState(&g_Controllers.leftTrigger, (g_Controllers.state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
    Controller_UpdateButtonState(&g_Controllers.rightTrigger, (g_Controllers.state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
    Controller_UpdateButtonState(&g_Controllers.startButton, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
    Controller_UpdateButtonState(&g_Controllers.backButton, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
    Controller_UpdateButtonState(&g_Controllers.DpadUp, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
    Controller_UpdateButtonState(&g_Controllers.DpadDown, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
    Controller_UpdateButtonState(&g_Controllers.DpadRight, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
    Controller_UpdateButtonState(&g_Controllers.DpadLeft, (g_Controllers.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);

    //ステック関連の更新
    LeftStickX = Controller_GetLeftStickX();
    LeftStickY = Controller_GetLeftStickY();
    RightStickX = Controller_GetRightStickX();
    RightStickY = Controller_GetRightStickY();

    //デッドゾーン処理
    if (LeftStickX > -DEADZONE && LeftStickX < DEADZONE) 
    {
        LeftStickX = 0;
        m_IsLeftStickLeft = false;
        m_IsLeftStickRight = false;
    }
    if (LeftStickY > -DEADZONE && LeftStickY < DEADZONE) 
    {
        LeftStickY = 0;
        m_IsLeftStickUp = false;
        m_IsLeftStickDown = false;
    }
    if (RightStickX > -DEADZONE && RightStickX < DEADZONE)
    {
        RightStickX = 0;
        m_IsRightStickLeft = false;
        m_IsRightStickRight = false;
    }
    if (RightStickY > -DEADZONE && RightStickY < DEADZONE)
    {
        RightStickY = 0;
        m_IsRightStickUp = false;
        m_IsRightStickDown = false;
    }

    //スティックの現在地更新
    CurrentStickLocationLeft = Controller_GetStickAngle(LeftStickX, LeftStickY);
    CurrentStickLocationRight = Controller_GetStickAngle(RightStickX, RightStickY);

}

//ボタン情報の更新  
void Controller::Controller_UpdateButtonState(ButtonState* buttonState, bool isCurrentlyPressed)
{
    // 前フレームの状態を保存
    buttonState->wasPressedLastFrame = buttonState->isPressed;

    // 現在の状態に更新
    if (isCurrentlyPressed) {
        if (!buttonState->isPressed) {
            buttonState->isPressed = true;
            buttonState->pressStartTime = GetTickCount();  // 押下開始時間を記録
        }
    }
    else {
        buttonState->isPressed = false;
        buttonState->pressStartTime = 0;
    }
}


//初期化時の接続台数の取得
int Controller::Controller_GetConnectedCount()
{
    return g_Controller_Numbers;
}

// 特定のボタンが押されているか確認する
int Controller::Controller_IsButtonDown(WORD button)
{
    return (g_Controllers.state.Gamepad.wButtons & button) != 0;
}

//ボタンが閾値を超えたかを調べる       thresholdはミリ秒
bool Controller::Controller_IsLongPress( ButtonState* buttonState, DWORD threshold)
{
    if (buttonState->isPressed) {
        DWORD currentTime = GetTickCount();
        return (currentTime - buttonState->pressStartTime >= threshold);
    }
    return false;
}

//押された瞬間の判定 
bool Controller::Controller_IsJustPressed( ButtonState* buttonState)
{
    return !buttonState->wasPressedLastFrame && buttonState->isPressed;
}

int Controller::Controller_IsButtonUp(WORD button)
{
    return (g_Controllers.state.Gamepad.wButtons & button) == 0;
}

//左トリガーの情報の取得
BYTE Controller::Controller_GetLeftTrigger()
{
    return g_Controllers.state.Gamepad.bLeftTrigger;
}

//右トリガーの情報の取得
BYTE Controller::Controller_GetRightTrigger()
{
    return g_Controllers.state.Gamepad.bRightTrigger;
}

// 左スティックのX軸の値を取得
SHORT Controller::Controller_GetLeftStickX()
{
    return g_Controllers.state.Gamepad.sThumbLX;
}

// 左スティックのY軸の値を取得
SHORT Controller::Controller_GetLeftStickY()
{
    return g_Controllers.state.Gamepad.sThumbLY;
}

// 右スティックのX軸の値を取得
SHORT Controller::Controller_GetRightStickX()
{
    return g_Controllers.state.Gamepad.sThumbRX;;
}

// 右スティックのY軸の値を取得
SHORT Controller::Controller_GetRightStickY()
{
    return g_Controllers.state.Gamepad.sThumbRY;
}

// スティックの角度を取得する関数
float Controller::Controller_GetStickAngle(SHORT x, SHORT y)
{
    return atan2((float)y, (float)x);  // y軸とx軸から角度を求める（ラジアン単位）
}

// 回転の方向と急な方向変化を検出
int Controller::Controller_GetRotationDirection(float previousAngle, float currentAngle)
{
    float deltaAngle = currentAngle - previousAngle;

    /*if (deltaAngle < 0)
    {
        deltaAngle = -deltaAngle;
    }*/

    // 急激な方向変化を無視
    if ((deltaAngle * M_PI / 180.0f) > MAX_JUMP_THRESHOLD)
    {
        return 0;  // 角度変化が大きすぎる場合、方向を判断しない
    }

    // 時計回りと反時計回りの判定を微調整
    if (deltaAngle > 0.01) return 1;   // 時計回り
    if (deltaAngle < -MIN_ROTATION_STEP) return -1; // 反時計回り

    return 0;  // ほぼ変化がない場合
}

// 一周回転の判定(左スティック）
bool Controller::Controller_IsFullRotation_LeftStick()
{
    int currentSection = Controller_GetRotationSection(CurrentStickLocationLeft);
    static int lastSection = -1;
    static int sectionCount = 0;
    static bool Rightrotation = false;
    static bool Leftrotation = false;
    static bool Isrotating = false;
    static int AccessCount = 0;

    if (LeftStickX < -15000 || LeftStickX > 15000)
    {
        if (LeftStickY < -15000 || LeftStickY > 15000)
        {
            if (currentSection != lastSection)
            {
                if (!Isrotating)
                {
                    if (lastSection == -1)
                    {

                        lastSection = currentSection;

                    }
                    else
                    {
                        Isrotating = true;

                        if ((currentSection > lastSection && !(lastSection == 1 && currentSection != 2)) || (currentSection == 1 && lastSection == 4))
                        {
                            Leftrotation = true;
                            sectionCount++;
                            lastSection = currentSection;
                        }
                        else if ((currentSection < lastSection && !(lastSection == 4 && currentSection != 3)) || (currentSection == 4 && lastSection == 1))
                        {
                            Rightrotation = true;
                            sectionCount++;
                            lastSection = currentSection;
                        }
                        else
                        {
                            Isrotating = false;
                            sectionCount = 0;
                            lastSection = -1;
                            AccessCount = 0;
                            return false;
                        }

                    }

                }
                else
                {
                    //右回転
                    if (Rightrotation)
                    {
                        //現在のステック位置チェック
                        if (currentSection == (lastSection - 1))
                        {
                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                        else
                        {
                            //もし7/4ラジアンから０に戻る以外の場合
                            if (currentSection != 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return false;
                            }

                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                    }

                    //左回転
                    if (Leftrotation)
                    {
                        //現在のステック位置チェック
                        if (currentSection == (lastSection + 1))
                        {
                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                        else
                        {
                            //もし7/4ラジアンから０に戻る以外の場合
                            if (currentSection != 1)
                            {
                                Leftrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return false;
                            }

                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                    }

                }

            }
            else
            {


                if (AccessCount >= 180)
                {
                    Leftrotation = false;
                    Rightrotation = false;
                    Isrotating = false;
                    sectionCount = 0;
                    lastSection = -1;
                    AccessCount = 0;
                }

                AccessCount++;
            }
        }
    }


    return false;
}

// 一周回転の判定（右スティック）
bool Controller::Controller_IsFullRotation_RightStick()
{
    int currentSection = Controller_GetRotationSection(CurrentStickLocationRight);
    /*int lastSection = Controller_GetRotationSection(PreviousStickLocationRight);*/
    static int lastSection = -1;
    static int sectionCount = 0;
    static bool Rightrotation = false;
    static bool Leftrotation = false;
    static bool Isrotating = false;
    static int AccessCount = 0;

    if (RightStickX < -15000 || RightStickX > 15000)
    {
        if (RightStickY < -15000 || RightStickY > 15000)
        {
            if (currentSection != lastSection)
            {
                if (!Isrotating)
                {
                    if (lastSection == -1)
                    {

                        lastSection = currentSection;

                    }
                    else
                    {
                        Isrotating = true;

                        if ((currentSection > lastSection && !(lastSection == 1 && currentSection != 2)) || (currentSection == 1 && lastSection == 4))
                        {
                            Leftrotation = true;
                            sectionCount++;
                            lastSection = currentSection;
                        }
                        else if ((currentSection < lastSection && !(lastSection == 4 && currentSection != 3)) || (currentSection == 4 && lastSection == 1))
                        {
                            Rightrotation = true;
                            sectionCount++;
                            lastSection = currentSection;
                        }
                        else
                        {
                            Isrotating = false;
                            sectionCount = 0;
                            lastSection = -1;
                            AccessCount = 0;
                            return false;
                        }

                    }

                }
                else
                {
                    //右回転
                    if (Rightrotation)
                    {
                        //現在のステック位置チェック
                        if (currentSection == (lastSection - 1))
                        {
                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                        else
                        {
                            //もし7/4ラジアンから０に戻る以外の場合
                            if (currentSection != 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return false;
                            }

                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                    }

                    //左回転
                    if (Leftrotation)
                    {
                        //現在のステック位置チェック
                        if (currentSection == (lastSection + 1))
                        {
                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                        else
                        {
                            //もし7/4ラジアンから０に戻る以外の場合
                            if (currentSection != 1)
                            {
                                Leftrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return false;
                            }

                            sectionCount++;

                            lastSection = currentSection;

                            if (sectionCount >= 4)
                            {
                                Rightrotation = false;
                                Isrotating = false;
                                sectionCount = 0;
                                lastSection = -1;
                                AccessCount = 0;
                                return true;
                            }
                        }
                    }

                }

            }
            else
            {


                if (AccessCount >= 180)
                {
                    Leftrotation = false;
                    Rightrotation = false;
                    Isrotating = false;
                    sectionCount = 0;
                    lastSection = -1;
                    AccessCount = 0;
                }

                AccessCount++;
            }
        }
    }
   

    return false;
}

//↓過去の書き方

//if (((CurrentStickLocationRight - PreviousStickLocationRight) * M_PI / 180) < MAX_JUMP_THRESHOLD)
    //{
    //    if (currentSection != lastSection)
    //    {
    //        lastSection = currentSection;
    //        sectionCount++;
    //    }
    //    

    //     //セクションが4つ分通過したら1周完了と判定
    //    if (sectionCount >= 4)
    //    {
    //        sectionCount = 0;
    //        return true;
    //    }

    //    return false;

    //}
    //// 急激な角度変化がない場合のみセクションをカウント
    //if (Controller_GetRotationDirection(PreviousStickLocationRight, CurrentStickLocationRight) == 0)
    //{
    //    sectionCount = 0;
    //}
    //else
    //{
    //    if (currentSection != lastSection)
    //    {
    //        lastSection = currentSection;
    //        sectionCount++;
    //    }

    //    // セクションが4つ分通過したら1周完了と判定
    //    if (sectionCount >= 4)
    //    {
    //        sectionCount = 0;
    //        return true;
    //    }
    //}


// セクションに基づき回転方向を判断
int Controller::Controller_GetRotationSection(float angle)
{
    if (angle >= (M_PI / 2)-0.0001 && angle < M_PI) return 2;

    else if (angle >= 0 && angle < M_PI / 2) return 1;

    else if (angle >= (-(M_PI / 2)-0.0001) && angle < 0)return 4;

    else if ((angle >= -M_PI && angle < -(M_PI /2) )|| (3.1415927f < angle && angle <= M_PI)) return 3;

    else return 0;
}

bool Controller::Controller_LeftStickIsUp()
{
   if (LeftStickY > DEADZONE)
   {
       return true;
   }
   return false;
}

bool Controller::Controller_LeftStickIsDown()
{
   if (LeftStickY < -DEADZONE)
   {
       return true;
   }
   return false;
}

bool Controller::Controller_LeftStickIsLeft()
{
   if (LeftStickX < -DEADZONE)
   {
       return true;
   }
   return false;
}

bool Controller::Controller_LeftStickIsRight()
{
   if (LeftStickX > DEADZONE)
   {
       return true;
   }
   return false;
}

bool Controller::Controller_RightStickIsUp()
{
    if (RightStickY > DEADZONE)
    {
        return true;
    }
    return false;
}

bool Controller::Controller_RightStickIsDown()
{
    if (RightStickY < -DEADZONE)
    {
        return true;
    }
    return false;
}

bool Controller::Controller_RightStickIsLeft()
{
    if (RightStickX < -DEADZONE)
    {
        return true;
    }
    return false;
}

bool Controller::Controller_RightStickIsRight()
{
    if (RightStickX > DEADZONE)
    {
        return true;
    }
    return false;
}

bool Controller::LeftStickIsUpContinuous()
{
    if (LeftStickY > DEADZONE)
    {
        if (!m_IsLeftStickUp)
        {
            m_IsLeftStickUp = true;
            m_ContinuousLeftFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousLeftFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousLeftFrame++;
                return true;
            }

            m_ContinuousLeftFrame++;
        }
    }
    return false;
}

bool Controller::LeftStickIsDownContinuous()
{
    if (LeftStickY < -DEADZONE)
    {
        if (!m_IsLeftStickDown)
        {
            m_IsLeftStickDown = true;
            m_ContinuousLeftFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousLeftFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousLeftFrame++;
                return true;
            }

            m_ContinuousLeftFrame++;
        }
    }
    return false;
}

bool Controller::LeftStickIsLeftContinuous()
{
    if (LeftStickX < -DEADZONE)
    {
        if (!m_IsLeftStickLeft)
        {
            m_IsLeftStickLeft = true;
            m_ContinuousLeftFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousLeftFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousLeftFrame++;
                return true;
            }

            m_ContinuousLeftFrame++;
        }
    }
    return false;
}

bool Controller::LeftStickIsRightContinuous()
{
    if (LeftStickX > DEADZONE)
    {
        if (!m_IsLeftStickRight)
        {
            m_IsLeftStickRight = true;
            m_ContinuousLeftFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousLeftFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousLeftFrame++;
                return true;
            }

            m_ContinuousLeftFrame++;
        }
    }
    return false;
}

bool Controller::RightStickIsUpContinuous()
{
    if (RightStickY > DEADZONE)
    {
        if (!m_IsRightStickUp)
        {
            m_IsRightStickUp = true;
            m_ContinuousRightFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousRightFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousRightFrame++;
                return true;
            }

            m_ContinuousRightFrame++;
        }
    }
    return false;
}

bool Controller::RightStickIsDownContinuous()
{
    if (RightStickY < -DEADZONE)
    {
        if (!m_IsRightStickDown)
        {
            m_IsRightStickDown = true;
            m_ContinuousRightFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousRightFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousRightFrame++;
                return true;
            }

            m_ContinuousRightFrame++;
        }
    }
    return false;
}

bool Controller::RightStickIsLeftContinuous()
{
    if (RightStickX < -DEADZONE)
    {
        if (!m_IsRightStickLeft)
        {
            m_IsRightStickLeft = true;
            m_ContinuousRightFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousRightFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousRightFrame++;
                return true;
            }

            m_ContinuousRightFrame++;
        }
    }
    return false;
}

bool Controller::RightStickIsRightContinuous()
{
    if (RightStickX > DEADZONE)
    {
        if (!m_IsRightStickRight)
        {
            m_IsRightStickRight = true;
            m_ContinuousRightFrame = 1;
            return true;
        }
        else
        {
            if (m_ContinuousRightFrame % CONTINUOUS_FRAMECOUNT == 0)
            {
                m_ContinuousRightFrame++;
                return true;
            }

            m_ContinuousRightFrame++;
        }
    }
    return false;
}

SHORT Controller::GetLeftStickX()
{
    return LeftStickX;
}

SHORT Controller::GetLeftStickY()
{
    return LeftStickY;
}

SHORT Controller::GetRightStickX()
{
    return RightStickX;
}

SHORT Controller::GetRightStickY()
{
    return RightStickY;
}



//バイブレーション開始
void Controller::Controller_StartVibration(WORD leftMotor, WORD rightMotor)
{
    XINPUT_VIBRATION vibration;

    // 左右モーターの強度を設定　0～65535
    vibration.wLeftMotorSpeed = leftMotor;  // 左モーター
    vibration.wRightMotorSpeed = rightMotor;  // 右モーター

    // 振動を設定
    DWORD result = XInputSetState(g_PlayerIndex, &vibration);
}

//バイブレーションのセット
void Controller::Controller_SetVibration(WORD leftMotor, WORD rightMotor, DWORD duration)
{
    // 振動の設定
    Controller_StartVibration(leftMotor, rightMotor);

    // 振動の情報を記録
    g_VibrationInfo.startTime = GetTickCount();
    g_VibrationInfo.duration = duration;
    g_VibrationInfo.isVibrating = 1;
}


//バイブレーションの更新管理
void Controller::Controller_UpdateVibration()
{
    DWORD currentTime = GetTickCount();

    for (int i = 0; i < g_Controller_Numbers; i++) {
        if (g_VibrationInfo.isVibrating) {
            //経過時間が設定した継続時間を超えたら振動を停止
            if (currentTime - g_VibrationInfo.startTime > g_VibrationInfo.duration) {
                Controller_StartVibration(0, 0);    //振動の停止
                g_VibrationInfo.isVibrating = 0;
            }

        }

    }
}

ButtonState* Controller::GetButtonForTrigger(WORD button)
{
    if (button == XINPUT_GAMEPAD_B )
    {
        return (&g_Controllers.bButton);
    }
    else if (button == XINPUT_GAMEPAD_A)
    {
        return (&g_Controllers.aButton);
    }
    else if (button == XINPUT_GAMEPAD_X)
    {
        return (&g_Controllers.xButton);
    }
    else if (button == XINPUT_GAMEPAD_Y)
    {
        return (&g_Controllers.yButton);
    }
    else if (button == XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        return (&g_Controllers.rshoulder);
    }
    else if (button == XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        return (&g_Controllers.lshoulder);
    }
    else if (button == XINPUT_GAMEPAD_RIGHT_THUMB)
    {
        return (&g_Controllers.rightTrigger);
    }
    else if (button == XINPUT_GAMEPAD_LEFT_THUMB)
    {
        return (&g_Controllers.leftTrigger);
    }
    else if (button == XINPUT_GAMEPAD_START)
    {
        return (&g_Controllers.startButton);
    }
    else if (button == XINPUT_GAMEPAD_BACK)
    {
        return (&g_Controllers.backButton);
    }
    else if (button == XINPUT_GAMEPAD_DPAD_UP)
    {
        return (&g_Controllers.DpadUp);
    }
    else if (button == XINPUT_GAMEPAD_DPAD_DOWN)
    {
        return (&g_Controllers.DpadDown);
    }
    else if (button == XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        return (&g_Controllers.DpadRight);
    }
    else if (button == XINPUT_GAMEPAD_DPAD_LEFT)
    {
        return (&g_Controllers.DpadLeft);
    }

    return nullptr;
}








