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

signals:
    void showStatus(QString);
public slots:
    void wJson(QString filename);
    QString rJson(QString filename);
    void keyPressEvent(QKeyEvent *event) override;

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
    Ui::MainWindow *ui;

    HHOOK hHook = NULL;
    QProgressBar *progress;
    QString open_file;
};
#endif // MAINWINDOW_H
