#include "mainwindow.h"

#include "bridge.h"

LRESULT CALLBACK MainWindow::MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;

    auto ev = Bridge::inst().getStruct();

    if(pMouseStruct != nullptr) {
        switch (wParam) {
        case WM_MOUSEMOVE:
            //qDebug() << "WM_MOUSEMOVE";
            break;
        case WM_LBUTTONDOWN:
            qDebug() << "[" << Bridge::inst().getTimer() << "] " << "WM_LBUTTONDOWN";
            ev.eventname = "WM_LBUTTONDOWN";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_LBUTTONUP:
            qDebug() << "WM_LBUTTONUP";
            ev.eventname = "WM_LBUTTONUP";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_RBUTTONDOWN:
            qDebug() << "WM_RBUTTONDOWN";
            ev.eventname = "WM_RBUTTONDOWN";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_RBUTTONUP:
            qDebug() << "WM_RBUTTONUP";
            ev.eventname = "WM_RBUTTONUP";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_MBUTTONDOWN:
            qDebug() << "WM_MBUTTONDOWN";
            ev.eventname = "WM_MBUTTONDOWN";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_MBUTTONUP:
            qDebug() << "WM_MBUTTONUP";
            ev.eventname = "WM_MBUTTONUP";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_MOUSEWHEEL:
            qDebug() << "WM_MOUSEWHEEL";
            ev.eventname = "WM_MOUSEWHEEL";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        default:
            break;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
