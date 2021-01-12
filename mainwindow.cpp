#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#pragma comment(lib, "user32.lib")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    Bridge::inst().startTimer();

    connect(this, &MainWindow::showStatus, [this](QString msg){
        ui->statusbar->showMessage(msg);
    });

    connect(ui->actionQuit, SIGNAL(triggered()), SLOT(quitApp()));
    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(open()));

    connect(ui->record_pushButton, SIGNAL(released()), SLOT(record()));
    connect(ui->stop_pushButton, SIGNAL(released()), SLOT(stopRecord()));
    connect(ui->display_pushButton, SIGNAL(released()), SLOT(displayUserAction()));
    connect(ui->play_pushButton, SIGNAL(released()), SLOT(playUserActions()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << event->key();
}

void MainWindow::wJson(QString filename) {
    QFile file(filename);
    QJsonArray arr;

}

QString MainWindow::rJson(QString filename) {
    QFile file(filename);
    return tr("");
}

void MainWindow::saveAs() {
    QString file = QFileDialog::getSaveFileName(nullptr, "Save file", ".", "All (*.*)");
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "Error", "Error open file for save");
        return;
    }

}

void MainWindow::open() {
    open_file = QFileDialog::getOpenFileName(nullptr, "Open file", ".", "JSON (*.json)");
}

void MainWindow::quitApp() {
    QApplication::quit();
}

void MainWindow::record() {
    hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (hHook == NULL) {
        ui->statusbar->showMessage("Hook failed");
    }
}

void MainWindow::stopRecord() {
    if (!UnhookWindowsHookEx(hHook)) return;
    progress = new QProgressBar;
    progress->setMaximumHeight(16);
    progress->setMaximumWidth(150);
    progress->setTextVisible(false);
    auto q = Bridge::inst().getQueue();
    progress->setMinimum(0);
    progress->setMaximum(q.size());
    ui->statusbar->addPermanentWidget(progress);
    ui->statusbar->showMessage("Save...");
<<<<<<< HEAD
=======
    qDebug() << "QueSize: " << q.size();
>>>>>>> e3ae98e4137a1b39c4b6499c3f2ed46743841552
    QFile jfile(QDateTime::currentDateTime().toString("ddMMyyhhmmss") + ".json");
    QJsonObject obj, obj1;
    int i = 0;
    while (!q.isEmpty()) {
        auto e = q.dequeue();
        qDebug() << e.time << e.eventname << e.x << e.y;
        qDebug() << q.size();
        obj1.insert("eventname", e.eventname);
        obj1.insert("time", e.time);
        obj1.insert("x", e.x);
        obj1.insert("y", e.y);
        obj.insert(QString().number(i), obj1);
        i++;
        progress->setValue(i);
    }
    QJsonDocument doc(obj);
    QString data = doc.toJson();
    if (!jfile.open(QIODevice::WriteOnly))
        QMessageBox::critical(nullptr, "Error", "Error create file");
    QTextStream stream(&jfile);
    stream << data;
    jfile.close();
    ui->statusbar->clearMessage();
    ui->statusbar->removeWidget(progress);
    ui->statusbar->showMessage("Save complete");
}

void MainWindow::displayUserAction() {
    open_file = QFileDialog::getOpenFileName(nullptr, "Open File", ".", "JSON (*.json)");
    QFile jfile(open_file);
    if (!jfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Error open file");
        return;
    }
    ui->textBrowser->clear();
    QByteArray data = jfile.readAll();
    jfile.close();

    QJsonDocument doc;
    doc = doc.fromJson(data);
<<<<<<< HEAD
=======
    qDebug() << "Size element json: " << doc.object().count();
>>>>>>> e3ae98e4137a1b39c4b6499c3f2ed46743841552
    for (int i = 0; i < doc.object().count(); i++) {
        QJsonValue val = doc.object()[QString().number(i)];
        QString tmp = tr("[ ")
                + val["time"].toString()
                + tr(" ] - ") + val["eventname"].toString()
                + tr(" - X: ") + QString().number(val["x"].toInt())
                + tr(" Y: ") + QString().number(val["y"].toInt());
        ui->textBrowser->append(tmp);
    }
}

void MainWindow::playUserActions() {
    //open_file = QFileDialog::getOpenFileName(nullptr, "Open File", ".", "JSON (*.json)");
    QFile jfile(open_file);
    if (!jfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Error open file");
        return;
    }

    QByteArray data = jfile.readAll();
    jfile.close();
    QJsonDocument doc;
    doc = doc.fromJson(data);

    int start = clock();
    QTime time;
    time.setHMS(0,0,0);

<<<<<<< HEAD
=======
    qDebug() << "Size element json: " << doc.object().count();
>>>>>>> e3ae98e4137a1b39c4b6499c3f2ed46743841552
    QtConcurrent::run([this, doc, start, time]() mutable {
        const int threadCount = 1;
        QThreadPool::globalInstance()->setMaxThreadCount(threadCount);
        QFutureSynchronizer<void> sync;

        for (int i = 0; i < doc.object().count() - 2; i++) {
            QJsonValue val = doc.object()[QString().number(i)];
            sync.addFuture(QtConcurrent::run([ val, start, time]() mutable {
                while(true) {
                    int end = clock();
                    uint32_t ms = ((end - start) * 1000) / CLOCKS_PER_SEC;
                    QString curr_time = time.addMSecs(ms).toString("hh:mm:ss.zzz");
                    if (curr_time != val["time"].toString())
                        continue;
                    else
                        break;
                   // Sleep(5);
                }
                auto event = val["eventname"].toString();
                qDebug() << event;
                if (event == tr("WM_LBUTTONDOWN")) {
                    int x = val["x"].toInt();
                    int y = val["y"].toInt();
                    SetCursorPos(x, y);
                    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
                } else if (event == tr("WM_LBUTTONUP")) {
                    int x = val["x"].toInt();
                    int y = val["y"].toInt();
                    SetCursorPos(x, y);
                    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
                } else if (event == tr("WM_RBUTTONDOWN")) {
                    int x = val["x"].toInt();
                    int y = val["y"].toInt();
                    SetCursorPos(x, y);
                    mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
                } else if (event == tr("WM_RBUTTONUP")) {
                    int x = val["x"].toInt();
                    int y = val["y"].toInt();
                    SetCursorPos(x, y);
                    mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
                } else if (event == tr("WM_MBUTTONDOWN")) {
                    int x = val["x"].toInt();
                    int y = val["y"].toInt();
                    SetCursorPos(x, y);
                    mouse_event(MOUSEEVENTF_MIDDLEDOWN, x, y, 0, 0);
                } else if (event == tr("WM_MBUTTONUP")) {
                    int x = val["x"].toInt();
                    int y = val["y"].toInt();
                    SetCursorPos(x, y);
                    mouse_event(MOUSEEVENTF_MIDDLEUP, x, y, 0, 0);
                }
            }));
            sync.setCancelOnWait(false);
            emit showStatus("Play complete");
        }
    });
}
