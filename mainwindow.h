#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QCursor>
#include <QDebug>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>
#include <QProgressBar>

#include <Windows.h>
#include <bridge.h>

#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK KeyProc(int nCode, WPARAM wParam, LPARAM lParam);

    QString convertNumToChar(unsigned long vcode, unsigned long scode);
    QString parseNumToNameKey(int vcode, int scode);

signals:
    void showStatus(QString);
public slots:
    // Menus

    void saveAs();
    void open();
    void quitApp();

    // Events proc
    void record();
    void stopRecord();
    void displayUserAction();
    void playUserActions();

private:
//    static int getInputMethod() {
//        HWND hwnd = GetForegroundWindow();
//        if (hwnd) {
//            DWORD threadID = GetWindowThreadProcessId(hwnd, NULL);
//            HKL currentLayout = GetKeyboardLayout(threadID);
//            unsigned int x = (unsigned int)currentLayout & 0x0000FFFF;
//            return x;
//        }
//        return 0;
//    }

    Ui::MainWindow *ui;

    HHOOK hHook = NULL;
    HHOOK khHook = NULL;
    QProgressBar *progress;
//    QString open_file;
};
#endif // MAINWINDOW_H
