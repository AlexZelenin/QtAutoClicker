#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <QKeyEvent>

namespace KNCL {

enum MOUSE {
    MOUSEMOVE = 0x0200,
    LBUTTONDOWN = 0x0201,
    LBUTTONUP = 0x0202,
    LBUTTONDBLCLK = 0x0203,
    RBUTTONDOWN = 0x0204,
    RBUTTONUP = 0x0205,
    RBUTTONDBLCLK = 0x0206,
    MBUTTONDOWN = 0x0207,
    MBUTTONUP = 0x0208,
    MBUTTONDBLCLK = 0x0209,
};

enum KEYBOARD {
    KEY_ESC = 27,
    KEY_F1 = 112,
    KEY_F2 = 113,
    KEY_F3 = 114,
    KEY_F4 = 115,
    KEY_F5 = 116,
    KEY_F6 = 117,
    KEY_F7 = 118,
    KEY_F8 = 119,
    KEY_F9 = 120,
    KEY_F10 = 121,
    KEY_F11 = 122,
    KEY_F12 = 123,
    KEY_MEDIA_MUTE = 173,
    KEY_MEDIA_VOLUM_DOWN = 174,
    KEY_MEDIA_VOLUM_UP = 175,
    KEY_BACKSPACE = 8,
    KEY_ENTER = 13,
    KEY_SPACE = 32,
    KEY_TAB = 9,
    KEY_CAPS_LOCK = 20,
    KEY_LEFT_SHIFT = 160,
    KEY_RIGHT_SHIFT = 161,
    KEY_LEFT_CONTROL = 162,
    KEY_RIGHT_CONTROL = 163,
    KEY_LEFT_ALT = 164,
    KEY_RIGHT_ALT = 165,
    KEY_LWIN = 91,
    KEY_LEFT = 37,
    KEY_RIGHT = 39,
    KEY_UP = 38,
    KEY_DOWN = 40,
    KEY_INSERT = 45,
    KEY_HOME = 36,
    KEY_PGUP = 33,
    KEY_DELETE = 46,
    KEY_END = 35,
    KEY_PGDN = 34,
};
}
#endif // CONFIG_H
