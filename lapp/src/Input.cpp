/**
@file Input.cpp
@author t-sakai
@date 2018/10/30 create
*/
#include "Input.h"
#include <xinput.h>
#include <process.h>

namespace lapp
{
namespace
{
#ifdef LAPP_USE_DINPUT
    struct EnumContext
    {
        static const s32 MaxDevices = 4;

        EnumContext(DirectInput* dinput)
            :dinput_(dinput)
            ,numDevices_(0)
        {
        }

        DirectInput* dinput_;
        s32 numDevices_;
        DirectInputDevice* device_[MaxDevices];
        DIDEVCAPS caps_[MaxDevices];
    };

    BOOL CALLBACK EnumGamePad(const DIDEVICEINSTANCE* dev, LPVOID data)
    {
        EnumContext* context = reinterpret_cast<EnumContext*>(data);

        //Create a device
        DirectInputDevice* device = LAPP_NULL;
        HRESULT hr = context->dinput_->CreateDevice(dev->guidInstance, &device, NULL);
        if(FAILED(hr)){
            return DIENUM_CONTINUE;
        }

        //Get DIDEVCAPS
        DIDEVCAPS caps;
        caps.dwSize = sizeof(DIDEVCAPS);
        hr = device->GetCapabilities(&caps);
        if(FAILED(hr)){
            device->Release();
            return DIENUM_CONTINUE;
        }
        u32 type = caps.dwDevType & 0xFFU;
        if(DI8DEVTYPE_GAMEPAD != type
            || DI8DEVTYPE_JOYSTICK != type){
            device->Release();
            return DIENUM_CONTINUE;
        }
        context->caps_[context->numDevices_] = caps;
        context->device_[context->numDevices_] = device;
        ++context->numDevices_;
        return EnumContext::MaxDevices<=context->numDevices_? DIENUM_STOP : DIENUM_CONTINUE;
    }
#endif

    inline void set(u16& up, u16& down, u16& click, u16& on, u16 cur, u16 prev, u16 mask)
    {
        cur &= mask;
        prev &= mask;
        up |= ((0==cur) && (0!=prev))? mask : 0;
        down |= ((0!=cur) && (0==prev))? mask : 0;
        click = up;
        on |= (0!=cur)? mask : 0;
    }
}

    //------------------------------------------------
    //---
    //--- Input::BitVector
    //---
    //------------------------------------------------
    void Input::BitVector::clear()
    {
        for(u32 i=0; i<NumBuckets; ++i){
            bits_[i] = 0;
        }
    }

    bool Input::BitVector::check(u32 index) const
    {
        LAPP_ASSERT(0<=index && index<MaxBits);
        u32 bucket = index>>Shift;
        u32 bit = 1U<<(index - (bucket<<Shift));
        return (bits_[bucket]&bit);
    }

    void Input::BitVector::set(u32 index)
    {
        LAPP_ASSERT(0<=index && index<MaxBits);
        u32 bucket = index>>Shift;
        u32 bit = 1U<<(index - (bucket<<Shift));
        bits_[bucket] |= bit;
    }

    void Input::BitVector::reset(u32 index)
    {
        LAPP_ASSERT(0<=index && index<MaxBits);
        u32 bucket = index>>Shift;
        u32 bit = 1U<<(index - (bucket<<Shift));
        bits_[bucket] &= ~bit;
    }

    void Input::BitVector::calc(u32& bucket, u32& bit, u32 index)
    {
        bucket = index>>Shift;
        bit = 1U<<(index - (bucket<<Shift));
    }

    bool Input::BitVector::check(u32 bucket, u32 bit) const
    {
        return (bits_[bucket]&bit);
    }

    void Input::BitVector::set(u32 bucket, u32 bit, bool flag)
    {
        if(flag){
            bits_[bucket] |= bit;
        } else{
            bits_[bucket] &= ~bit;
        }
    }

    //------------------------------------------------
    //---
    //--- Input
    //---
    //------------------------------------------------
    Input::Input()
        :threadHandle_(LAPP_NULL)
        ,threadId_(0)
        ,requestEnd_(false)
#ifdef LAPP_USE_DINPUT
        ,directInput_(LAPP_NULL)
#endif
        ,maxGamePads_(0)
        ,numRawGamePads_(0)
        ,numGamePads_(0)
        ,hWnd_(LAPP_NULL)
        ,nextWndProc_(LAPP_NULL)
    {
        InitializeCriticalSection(&cs_);
    }

    Input::~Input()
    {
        if(LAPP_NULL != threadHandle_){
            CloseHandle(threadHandle_);
            threadHandle_ = LAPP_NULL;
            DeleteCriticalSection(&cs_);
        }
    }

    bool Input::initialize(InputParam& param)
    {
        LAPP_ASSERT(LAPP_NULL != param.hWnd_);
        if(LAPP_NULL != threadHandle_){
            return false;
        }
        maxGamePads_ = minimum(param.maxGamePads_, MaxGamePads);
        memset(gamePadRawStates_, 0, sizeof(GamePadRawState)*MaxGamePads);
        memset(gamePadStates_, 0, sizeof(GamePadState)*MaxGamePads);
        keysOn_.clear();
        keysDown_.clear();
        keysUp_.clear();
        memset(&mouse_, 0, sizeof(MouseState));

        XInputEnable(TRUE);

        hWnd_ = param.hWnd_;
        if(param.keyboard_ || param.mouse_){
            initRawInput(param.keyboard_, param.mouse_);
        }
        onResize();

        requestEnd_ = false;
        threadHandle_ = reinterpret_cast<HANDLE>(_beginthreadex(LAPP_NULL, 0, Input::procGamePad, this, 0, &threadId_));

#ifdef LAPP_USE_DINPUT
        HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(param.hWnd_, GWLP_HINSTANCE);
        if(NULL == hInstance){
            return false;
        }
        if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, NULL))){
            return true;
        }
#endif
        return true;
    }

    void Input::terminate()
    {
        if(LAPP_NULL != threadHandle_){
            enter();
            requestEnd_ = true;
            ResumeThread(threadHandle_);
            leave();

            for(s32 i=0; i<60; ++i){
                if(WAIT_OBJECT_0 == WaitForSingleObject(threadHandle_, 16)){
                    break;
                }
            }
            CloseHandle(threadHandle_);
            threadHandle_ = LAPP_NULL;
        }
        DeleteCriticalSection(&cs_);

#ifdef LAPP_USE_DINPUT
        if(LAPP_NULL != directInput_){
            directInput_->Release();
            directInput_ = LAPP_NULL;
        }
#endif

        if(LAPP_NULL != nextWndProc_){
            SetWindowLongPtr(hWnd_, GWLP_WNDPROC, (LONG_PTR)nextWndProc_);
            RegisterRawInputDevices(LAPP_NULL, 0, sizeof(RAWINPUTDEVICE));
            SetWindowLongPtr(hWnd_, GWLP_USERDATA, (LONG_PTR)0);
            nextWndProc_ = LAPP_NULL;
        }

        XInputEnable(FALSE);
    }

    void Input::update()
    {
        enter();
        numGamePads_ = numRawGamePads_;
        s32 count = 0;
        for(; count<numGamePads_; ++count){
            update(count);
        }
        leave();
    }

    void Input::onResize()
    {
        RECT rect = {0, 0, 1, 1};
        GetClientRect(hWnd_, &rect);
        windowSize_.x_ = rect.right - rect.left;
        windowSize_.y_ = rect.bottom - rect.top;

        updateMousePosition();
    }

    void Input::showCursor(bool show)
    {
        ShowCursor(show?TRUE:FALSE);
    }

    s32 Input::getNumGamePads() const
    {
        return numGamePads_;
    }

    bool Input::isUp(s32 pad, Pad key) const
    {
        LAPP_ASSERT(0<=pad && pad<MaxGamePads);
        return gamePadStates_[pad].up_ & key;
    }

    bool Input::isDown(s32 pad, Pad key) const
    {
        LAPP_ASSERT(0<=pad && pad<MaxGamePads);
        return gamePadStates_[pad].down_ & key;
    }

    bool Input::isClick(s32 pad, Pad key) const
    {
        LAPP_ASSERT(0<=pad && pad<MaxGamePads);
        return gamePadStates_[pad].click_ & key;
    }

    bool Input::isOn(s32 pad, Pad key) const
    {
        LAPP_ASSERT(0<=pad && pad<MaxGamePads);
        return gamePadStates_[pad].on_ & key;
    }

    bool Input::isUp(Mouse key) const
    {
        return mouse_.up_ & key;
    }

    bool Input::isDown(Mouse key) const
    {
        return mouse_.down_ & key;
    }

    bool Input::isClick(Mouse key) const
    {
        return mouse_.click_ & key;
    }

    bool Input::isOn(Mouse key) const
    {
        return mouse_.on_ & key;
    }

    const Int2 Input::getMousePosition() const
    {
        return mouse_.position_;
    }

    void Input::initRawInput(bool keyboard, bool mouse)
    {
        RAWINPUTDEVICE rawInputDevices[2];
        u32 count = 0;
        if(keyboard){
            rawInputDevices[count].usUsagePage = 0x01;
            rawInputDevices[count].usUsage = 0x06;
            rawInputDevices[count].dwFlags = 0;//RIDEV_NOLEGACY;
            rawInputDevices[count].hwndTarget = hWnd_;
            ++count;
        }
        if(mouse){
            rawInputDevices[count].usUsagePage = 0x01;
            rawInputDevices[count].usUsage = 0x02;
            rawInputDevices[count].dwFlags = 0;//RIDEV_NOLEGACY;
            rawInputDevices[count].hwndTarget = hWnd_;
            ++count;
        }
        RegisterRawInputDevices(rawInputDevices, count, sizeof(RAWINPUTDEVICE));
        nextWndProc_ = (WNDPROC)SetWindowLongPtr(hWnd_, GWLP_WNDPROC, (LONG_PTR)WndProc);
        SetWindowLongPtr(hWnd_, GWLP_USERDATA, (LONG_PTR)this);
    }

    void Input::updateMousePosition()
    {
        POINT p;
        if(GetCursorPos(&p)){
            ScreenToClient(hWnd_, &p);
            mouse_.position_.x_ = clamp(static_cast<s32>(p.x), 0, windowSize_.x_-1);
            mouse_.position_.y_ = clamp(static_cast<s32>(p.y), 0, windowSize_.y_-1);
        } else{
            mouse_.position_ ={0,0};
        }
    }
    void Input::update(s32 pad)
    {
        GamePadRawState& rawState = gamePadRawStates_[pad];
        GamePadState& state = gamePadStates_[pad];

        state.up_ = state.down_ = state.click_ = state.on_ = 0;

        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Up);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Down);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Left);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Right);

        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Start);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Back);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_LThumb);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_RThumb);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_LShoulder);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_RShoulder);

        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_A);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_B);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_X);
        set(state.up_, state.down_, state.click_, state.on_, rawState.buttons_, rawState.prevButtons_, Pad_Y);

        rawState.prevPacketNumber_ = rawState.packetNumber_;
        rawState.prevButtons_ = rawState.buttons_;

        rawState.buttons_ = 0;
    }

    u32 __stdcall Input::procGamePad(void* args)
    {
        s64 cycleCount;
        bool supportHighPeformanceCounter;
        {
            LARGE_INTEGER frequency;
            if(QueryPerformanceFrequency(&frequency)){
                supportHighPeformanceCounter = true;
                cycleCount = frequency.QuadPart / 120;
                if(cycleCount<=1000){
                    cycleCount = 20000LL;
                }
            } else{
                supportHighPeformanceCounter = false;
                cycleCount = 16;
            }
        }

        LARGE_INTEGER startTime, currentTime;
        Input* input = reinterpret_cast<Input*>(args);
        for(;;){
            input->enter();
            if(input->requestEnd_){
                input->leave();
                break;
            }
            input->updateGamePad();
            input->leave();

            if(supportHighPeformanceCounter){ //The system supports High Performance Counter.
                QueryPerformanceCounter(&startTime);
                for(;;){
                    _mm_pause();
                    QueryPerformanceCounter(&currentTime);
                    if(cycleCount<=(currentTime.QuadPart-startTime.QuadPart)){
                        break;
                    }
                }

            } else{ //Use legacy timer
                startTime.LowPart = timeGetTime();
                for(;;){
                    Sleep(0);
                    currentTime.LowPart = timeGetTime();

                    u32 duration = (startTime.LowPart<=currentTime.LowPart)? (currentTime.LowPart - startTime.LowPart) : (0xFFFFFFFFU-startTime.LowPart + currentTime.LowPart);
                    if(cycleCount<=duration){
                        break;
                    }
                }
            }//if(supportHighPeformanceCounter)
        }//for(;;)
        _endthreadex(0);
        return 0;
    }

    void Input::updateGamePad()
    {
        XINPUT_STATE state;
        for(numRawGamePads_=0; numRawGamePads_<maxGamePads_; ++numRawGamePads_){
            if(ERROR_SUCCESS == XInputGetState(numRawGamePads_, &state)){
                gamePadRawStates_[numRawGamePads_].packetNumber_ = state.dwPacketNumber;
                gamePadRawStates_[numRawGamePads_].buttons_ |= state.Gamepad.wButtons;
            }
        }
    }


    LRESULT Input::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Input* input = (Input*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        RAWINPUT rawInputs[Input::MaxRawInputs];
        switch(msg)
        {
        case WM_INPUT:{
            HRAWINPUT hRawInput = (HRAWINPUT)lParam;
            u32 size;
            GetRawInputData(hRawInput, RID_INPUT, LAPP_NULL, &size, sizeof(RAWINPUTHEADER));
            static const u32 MaxSize = sizeof(RAWINPUT) * Input::MaxRawInputs;
            if(size<=MaxSize && GetRawInputData(hRawInput, RID_INPUT, rawInputs, &size, sizeof(RAWINPUTHEADER))==size){
                if(RIM_TYPEKEYBOARD == rawInputs->header.dwType){
                    u32 bucket, bit;
                    input->keysOn_.calc(bucket, bit, rawInputs->data.keyboard.VKey);
                    bool cur = ((rawInputs->data.keyboard.Flags&0x01U) == RI_KEY_MAKE);
                    bool prev = input->keysOn_.check(bucket, bit);

                    input->keysOn_.set(bucket, bit, cur);
                    input->keysDown_.set(bucket, bit, cur && !prev);
                    input->keysUp_.set(bucket, bit, !cur && prev);

                } else if(RIM_TYPEMOUSE == rawInputs->header.dwType){
                    if(rawInputs->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE){
                        input->mouse_.position_.x_ = rawInputs->data.mouse.lLastX;
                        input->mouse_.position_.y_ = rawInputs->data.mouse.lLastY;
                    } else{
                        input->updateMousePosition();
                    }
                    //if(rawInputs->data.mouse.usFlags & MOUSE_VIRTUAL_DESKTOP){
                    //    DEBUG_PRINT("MOUSE_VIRTUAL_DESKTOP\n");
                    //}

                    input->mouse_.up_ = 0;
                    input->mouse_.down_ = 0;
                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN){
                        input->mouse_.down_ |= Mouse_L;
                        input->mouse_.on_ |= Mouse_L;
                    }
                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP){
                        input->mouse_.up_ |= Mouse_L;
                        input->mouse_.on_ &= ~Mouse_L;
                    }
                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN){
                        input->mouse_.down_ |= Mouse_M;
                        input->mouse_.on_ |= Mouse_M;
                    }
                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP){
                        input->mouse_.up_ |= Mouse_M;
                        input->mouse_.on_ &= ~Mouse_M;
                    }
                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN){
                        input->mouse_.down_ |= Mouse_R;
                        input->mouse_.on_ |= Mouse_R;
                    }
                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP){
                        input->mouse_.up_ |= Mouse_R;
                        input->mouse_.on_ &= ~Mouse_R;
                    }
                    input->mouse_.click_ = input->mouse_.up_;

                    if(rawInputs->data.mouse.usButtonFlags & RI_MOUSE_WHEEL){
                        input->mouse_.wheelDelta_ = *((s16*)&rawInputs->data.mouse.usButtonData);
                    }
                }

            }
        }
        default:
            return CallWindowProc(input->nextWndProc_, hWnd, msg, wParam, lParam);
        }
    }
}
