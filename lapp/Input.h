#ifndef INC_LAPP_INPUT_H_
#define INC_LAPP_INPUT_H_
/**
@file Input.h
@author t-sakai
@date 2018/10/30 create
*/
#include "lapp.h"

#ifdef LAPP_USE_DINPUT
#    ifdef _WIN32
#        define DIRECTINPUT_VERSION 0x0800
#        include <dinput.h>
typedef IDirectInput8 DirectInput;
typedef IDirectInputDevice8 DirectInputDevice;
#    endif
#endif

namespace lapp
{
    enum Pad : u16
    {
        Pad_Up = 0x0001U,
        Pad_Down = 0x0002U,
        Pad_Left = 0x0004U,
        Pad_Right = 0x0008U,
        Pad_Start = 0x0010U,
        Pad_Back = 0x00020U,
        Pad_LThumb = 0x0040U,
        Pad_RThumb = 0x0080U,
        Pad_LShoulder = 0x0100U,
        Pad_RShoulder = 0x0200U,
        Pad_A = 0x1000U,
        Pad_B = 0x2000U,
        Pad_X = 0x4000U,
        Pad_Y = 0x8000U,
    };

    enum Key
    {
        Key_LBUTTON = VK_LBUTTON,
        Key_RBUTTON = VK_RBUTTON,
        Key_CANCEL = VK_CANCEL,
        Key_MBUTTON = VK_MBUTTON,

        Key_BACK = VK_BACK,
        Key_TAB = VK_TAB,

        Key_CLEAR = VK_CLEAR,
        Key_RETURN = VK_RETURN,

        Key_SHIFT = VK_SHIFT,
        Key_CONTROL = VK_CONTROL,
        Key_MENU = VK_MENU,
        Key_PAUSE = VK_PAUSE,
        Key_CAPITAL = VK_CAPITAL,
        Key_KANA = VK_KANA,

        Key_ESCAPE = VK_ESCAPE,

        Key_CONVERT = VK_CONVERT,
        Key_NONCONVERT = VK_NONCONVERT,
        Key_ACCEPT = VK_ACCEPT,
        Key_MODECHANGE = VK_MODECHANGE,

        Key_SPACE = VK_SPACE,
        Key_PRIOR = VK_PRIOR,
        Key_NEXT = VK_NEXT,
        Key_END = VK_END,
        Key_HOME = VK_HOME,
        Key_LEFT = VK_LEFT,
        Key_UP = VK_UP,
        Key_RIGHT = VK_RIGHT,
        Key_DOWN = VK_DOWN,
        Key_SELECT = VK_SELECT,
        Key_PRINT = VK_PRINT,
        Key_EXECUTE = VK_EXECUTE,
        Key_SNAPSHOT = VK_SNAPSHOT,
        Key_INSERT = VK_INSERT,
        Key_DELETE = VK_DELETE,
        Key_HELP = VK_HELP,

        Key_0 = '0',
        Key_1 = '1',
        Key_2 = '2',
        Key_3 = '3',
        Key_4 = '4',
        Key_5 = '5',
        Key_6 = '6',
        Key_7 = '7',
        Key_8 = '8',
        Key_9 = '9',

        Key_A = 'A',
        Key_B = 'B',
        Key_C = 'C',
        Key_D = 'D',
        Key_E = 'E',
        Key_F = 'F',
        Key_G = 'G',
        Key_H = 'H',
        Key_I = 'I',
        Key_J = 'J',
        Key_K = 'K',
        Key_L = 'L',
        Key_M = 'M',
        Key_N = 'N',
        Key_O = 'O',
        Key_P = 'P',
        Key_Q = 'Q',
        Key_R = 'R',
        Key_S = 'S',
        Key_T = 'T',
        Key_U = 'U',
        Key_V = 'V',
        Key_W = 'W',
        Key_X = 'X',
        Key_Y = 'Y',
        Key_Z = 'Z',

        Key_LWIN = VK_LWIN,
        Key_RWIN = VK_RWIN,
        Key_APPS = VK_APPS,

        Key_SLEEP = VK_SLEEP,

        Key_NUMPAD0 = VK_NUMPAD0,
        Key_NUMPAD1 = VK_NUMPAD1,
        Key_NUMPAD2 = VK_NUMPAD2,
        Key_NUMPAD3 = VK_NUMPAD3,
        Key_NUMPAD4 = VK_NUMPAD4,
        Key_NUMPAD5 = VK_NUMPAD5,
        Key_NUMPAD6 = VK_NUMPAD6,
        Key_NUMPAD7 = VK_NUMPAD7,
        Key_NUMPAD8 = VK_NUMPAD8,
        Key_NUMPAD9 = VK_NUMPAD9,
        Key_MULTIPLY = VK_MULTIPLY,
        Key_ADD = VK_ADD,
        Key_SEPARATOR = VK_SEPARATOR,
        Key_SUBTRACT = VK_SUBTRACT,
        Key_DECIMAL = VK_DECIMAL,
        Key_DIVIDE = VK_DIVIDE,

        Key_F1 = VK_F1,
        Key_F2 = VK_F2,
        Key_F3 = VK_F3,
        Key_F4 = VK_F4,
        Key_F5 = VK_F5,
        Key_F6 = VK_F6,
        Key_F7 = VK_F7,
        Key_F8 = VK_F8,
        Key_F9 = VK_F9,
        Key_F10 = VK_F10,
        Key_F11 = VK_F11,
        Key_F12 = VK_F12,
        Key_F13 = VK_F13,
        Key_F14 = VK_F14,
        Key_F15 = VK_F15,
        Key_F16 = VK_F16,
        Key_F17 = VK_F17,
        Key_F18 = VK_F18,
        Key_F19 = VK_F19,
        Key_F20 = VK_F20,
        Key_F21 = VK_F21,
        Key_F22 = VK_F22,
        Key_F23 = VK_F23,
        Key_F24 = VK_F24,

        Key_LSHIFT = VK_LSHIFT,
        Key_RSHIFT = VK_RSHIFT,
        Key_LCONTROL = VK_LCONTROL,
        Key_RCONTROL = VK_RCONTROL,
        Key_LMENU = VK_LMENU,
        Key_RMENU = VK_RMENU,
    };

    enum Mouse : u8
    {
        Mouse_L = 0x01U,
        Mouse_R = 0x02U,
        Mouse_M = 0x04U,
    };

    struct Int2
    {
        s32 x_;
        s32 y_;
    };

    class Input
    {
    public:
        static const u32 MaxRawInputs = 2;

        Input();
        ~Input();

        bool initialize(InputParam& param);
        void terminate();

        void update();
        void onResize();
        void showCursor(bool show);

        s32 getNumGamePads() const;
        bool isUp(s32 pad, Pad key) const;
        bool isDown(s32 pad, Pad key) const;
        bool isClick(s32 pad, Pad key) const;
        bool isOn(s32 pad, Pad key) const;

        bool isUp(Mouse key) const;
        bool isDown(Mouse key) const;
        bool isClick(Mouse key) const;
        bool isOn(Mouse key) const;
        const Int2 getMousePosition() const;
    protected:
        LAPP_NON_COPYABLE(Input);
        static u32 __stdcall procGamePad(void* args);

        static const s32 MaxGamePads = 4;
        static const u32 NumKeys = 256;

        struct GamePadRawState
        {
            u32 prevPacketNumber_;
            u32 packetNumber_; 
            u16 prevButtons_;
            u16 buttons_;
            //u8 leftTrigger_;
            //u8 rightTrigger_;
            //s16 thumbLX_;
            //s16 thumbLY_;
            //s16 thumbRX_;
            //s16 thumbRY_;
        };

        struct GamePadState
        {
            u16 up_;
            u16 down_;
            u16 click_;
            u16 on_;
        };

        struct BitVector
        {
            static const u32 MaxBits = 256;
            static const u32 Shift = 5;
            static const u32 Mask = (1U<<Shift)-1;
            static const u32 NumBuckets = MaxBits>>Shift;

            void clear();
            bool check(u32 index) const;
            void set(u32 index);
            void reset(u32 index);

            void calc(u32& bucket, u32& bit, u32 index);
            bool check(u32 bucket, u32 bit) const;
            void set(u32 bucket, u32 bit, bool flag);

            u32 bits_[NumBuckets];
        };

        struct MouseState
        {
            Int2 position_;
            u8 up_;
            u8 down_;
            u8 click_;
            u8 on_;
            s32 wheelDelta_;
        };

        void enter()
        {
            EnterCriticalSection(&cs_);
        }

        void leave()
        {
            LeaveCriticalSection(&cs_);
        }

        void initRawInput(bool keyboard, bool mouse);
        void updateMousePosition();

        void update(s32 pad);
        void updateGamePad();

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        HANDLE threadHandle_;
        u32 threadId_;
        CRITICAL_SECTION cs_;
        bool requestEnd_;
#ifdef LAPP_USE_DINPUT
        DirectInput* directInput_;
#endif
        s32 maxGamePads_;
        u16 numRawGamePads_;
        u16 numGamePads_;
        GamePadRawState gamePadRawStates_[MaxGamePads];
        GamePadState gamePadStates_[MaxGamePads];

        HWND hWnd_;
        WNDPROC nextWndProc_;
        Int2 windowSize_;
        BitVector keysOn_;
        BitVector keysDown_;
        BitVector keysUp_;

        MouseState mouse_;
    };
}

#endif //INC_LAPP_INPUT_H_
