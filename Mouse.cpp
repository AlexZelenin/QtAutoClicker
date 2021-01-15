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
            ev.eventname = "LBUTTONDOWN";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_LBUTTONUP:
            qDebug() << "LBUTTONUP";
            ev.eventname = "LBUTTONUP";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_RBUTTONDOWN:
            qDebug() << "WM_RBUTTONDOWN";
            ev.eventname = "RBUTTONDOWN";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_RBUTTONUP:
            qDebug() << "WM_RBUTTONUP";
            ev.eventname = "RBUTTONUP";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_MBUTTONDOWN:
            qDebug() << "WM_MBUTTONDOWN";
            ev.eventname = "MBUTTONDOWN";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_MBUTTONUP:
            qDebug() << "WM_MBUTTONUP";
            ev.eventname = "MBUTTONUP";
            ev.time = Bridge::inst().getTimer();
            ev.x = QCursor::pos().x();
            ev.y = QCursor::pos().y();
            Bridge::inst().setEvent(ev);
            break;
        case WM_MOUSEWHEEL:
            qDebug() << "WM_MOUSEWHEEL";
            ev.eventname = "MOUSEWHEEL";
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
