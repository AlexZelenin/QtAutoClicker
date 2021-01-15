#include <mainwindow.h>

LRESULT CALLBACK MainWindow::KeyProc(int nCode, WPARAM wParam, LPARAM lParam) {
    auto vcode = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
    auto scode = ((LPKBDLLHOOKSTRUCT)lParam)->scanCode;
    auto ev = Bridge::inst().getStruct();

    switch(wParam)
    {
    case WM_KEYDOWN:
        qDebug() << "Key down;" << ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        ev.eventname = tr("KEYDOWN");
        ev.key_vnum = vcode;
        ev.key_snum = scode;
        ev.time = Bridge::inst().getTimer();
        Bridge::inst().setEvent(ev);
        break;
    case WM_KEYUP:
        qDebug() << "Key up" << ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        ev.eventname = tr("KEYUP");
        ev.key_vnum = vcode;
        ev.key_snum = scode;
        ev.time = Bridge::inst().getTimer();
        Bridge::inst().setEvent(ev);
        break;
    default:
        break;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

QString MainWindow::convertNumToChar(unsigned long vcode, unsigned long scode) {
    BYTE keyState[256] = {0};
    if (GetKeyboardState(keyState)) {
        wchar_t buffer[64];
        int result = ToUnicodeEx(vcode, scode, keyState, buffer, _countof(buffer), 0, NULL);

        if (result)
            return QString::fromWCharArray(buffer);
    }
    return tr("");
}

QString MainWindow::parseNumToNameKey(int vcode, int scode) {
    Q_UNUSED(scode);
    QString vkey;
    switch (vcode) {
    case KNCL::KEY_ESC:
        vkey = tr("Esc");
        break;
    case KNCL::KEY_F1:
        vkey = tr("F1");
        break;
    case KNCL::KEY_F2:
        vkey = tr("F2");
        break;
    case KNCL::KEY_F3:
        vkey = tr("F3");
        break;
    case KNCL::KEY_F4:
        vkey = tr("F4");
        break;
    case KNCL::KEY_F5:
        vkey = tr("F5");
        break;
    case KNCL::KEY_F6:
        vkey = tr("F6");
        break;
    case KNCL::KEY_F7:
        vkey = tr("F7");
        break;
    case KNCL::KEY_F8:
        vkey = tr("F8");
        break;
    case KNCL::KEY_F9:
        vkey = tr("F9");
        break;
    case KNCL::KEY_F10:
        vkey = tr("F10");
        break;
    case KNCL::KEY_F11:
        vkey = tr("F11");
        break;
    case KNCL::KEY_F12:
        vkey = tr("F12");
        break;
    case KNCL::KEY_MEDIA_MUTE:
        vkey = tr("(Media) Mute");
        break;
    case KNCL::KEY_MEDIA_VOLUM_DOWN:
        vkey = tr("(Media) Volume down");
        break;
    case KNCL::KEY_MEDIA_VOLUM_UP:
        vkey = tr("(Media) Volume up");
        break;
    case KNCL::KEY_BACKSPACE:
        vkey = tr("Backspace");
        break;
    case KNCL::KEY_ENTER:
        vkey = tr("Enter");
        break;
    case KNCL::KEY_SPACE:
        vkey = tr("Space");
        break;
    case KNCL::KEY_TAB:
        vkey = tr("Tab");
        break;
    case KNCL::KEY_CAPS_LOCK:
        vkey = tr("Caps Lock");
        break;
    case KNCL::KEY_LEFT_SHIFT:
        vkey = tr("Left Shift");
        break;
    case KNCL::KEY_RIGHT_SHIFT:
        vkey = tr("Right Shift");
        break;
    case KNCL::KEY_LEFT_CONTROL:
        vkey = tr("Left Control");
        break;
    case KNCL::KEY_RIGHT_CONTROL:
        vkey = tr("Right Control");
        break;
    case KNCL::KEY_LEFT_ALT:
        vkey = tr("Left Alt");
        break;
    case KNCL::KEY_RIGHT_ALT:
        vkey = tr("Right Alt");
        break;
    case KNCL::KEY_LWIN:
        vkey = tr("Win");
        break;
    case KNCL::KEY_LEFT:
        vkey = tr("Left");
        break;
    case KNCL::KEY_RIGHT:
        vkey = tr("Right");
        break;
    case KNCL::KEY_UP:
        vkey = tr("Up");
        break;
    case KNCL::KEY_DOWN:
        vkey = tr("Down");
        break;
    case KNCL::KEY_INSERT:
        vkey = tr("Insert");
        break;
    case KNCL::KEY_HOME:
        vkey = tr("Home");
        break;
    case KNCL::KEY_PGUP:
        vkey = tr("PgUp");
        break;
    case KNCL::KEY_DELETE:
        vkey = tr("Delete");
        break;
    case KNCL::KEY_END:
        vkey = tr("End");
        break;
    case KNCL::KEY_PGDN:
        vkey = tr("PgDn");
        break;
    default:
        vkey = convertNumToChar(vcode, scode);
        break;
    }

    if (vkey.isEmpty())
        vkey = tr("Unknown");
    return vkey;
}
