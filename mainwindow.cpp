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

void MainWindow::saveAs() {
    QString file = QFileDialog::getSaveFileName(nullptr, "Save file", ".", "All (*.*)");
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "Error", "Error open file for save");
        return;
    }

}

void MainWindow::open() {
    displayUserAction();
}

void MainWindow::quitApp() {
    QApplication::quit();
}

void MainWindow::record() {
    hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (hHook == NULL) {
        ui->statusbar->showMessage("Mouse hook failed");
    }
    khHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyProc, NULL, 0);
    if (khHook == NULL)
        ui->statusbar->showMessage("Keyboard hook filed");
}

void MainWindow::stopRecord() {
    if (!UnhookWindowsHookEx(hHook) || !UnhookWindowsHookEx(khHook)) return;

    auto q = Bridge::inst().getQueue();

    progress = new QProgressBar;
    progress->setMaximumHeight(16);
    progress->setMaximumWidth(150);
    progress->setTextVisible(false);
    progress->setMinimum(0);
    progress->setMaximum(q.size());
    ui->statusbar->addPermanentWidget(progress);
    ui->statusbar->showMessage("Save...");

    QFile jfile(QDateTime::currentDateTime().toString("ddMMyyhhmmss").append(".json"));
    Bridge::inst().setFileName(jfile.fileName());
    QJsonObject obj, obj1;
    int i = 0;

    while (!q.isEmpty()) {
        auto e = q.dequeue();
        qDebug() << e.time << e.eventname << e.x << e.y;
        qDebug() << q.size();
        if (e.eventname == "KEYDOWN" || e.eventname == "KEYUP") {
            obj1.insert("eventname", e.eventname);
            obj1.insert("time", e.time);
            obj1.insert("vkey", QVariant().fromValue(e.key_vnum).toInt());
            obj1.insert("skey", QVariant().fromValue(e.key_snum).toInt());
            obj.insert(QString().number(i), obj1);
        } else {
            obj1.remove("vkey");
            obj1.remove("skey");
            obj1.insert("eventname", e.eventname);
            obj1.insert("time", e.time);
            obj1.insert("x", e.x);
            obj1.insert("y", e.y);
            obj.insert(QString().number(i), obj1);
        }
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
    Bridge::inst().setFileName(QFileDialog::getOpenFileName(nullptr, "Open File", ".", "JSON (*.json)"));
    QFile jfile(Bridge::inst().getFileName());
    if (!jfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Error open file");
        return;
    }
    ui->textBrowser->clear();
    QByteArray data = jfile.readAll();
    jfile.close();

    QJsonDocument doc;
    doc = doc.fromJson(data);
    for (int i = 0; i < doc.object().count(); i++) {
        QString tmp;
        QJsonValue val = doc.object()[QString().number(i)];
        if (val["eventname"].toString() == tr("KEYDOWN") || val["eventname"].toString() == tr("KEYUP")) {
            QString vkey = parseNumToNameKey(val["vkey"].toInt(), val["skey"].toInt());
            tmp = tr("[ ")
                    .append(val["time"].toString())
                    .append(tr(" ] - ")).append(val["eventname"].toString())
                    .append(tr(" - Key: ")).append(vkey);
        } else {
            tmp = tr("[ ")
                    + val["time"].toString()
                    + tr(" ] - ") + val["eventname"].toString()
                    + tr(" - X: ") + QString().number(val["x"].toInt())
                    + tr(" Y: ") + QString().number(val["y"].toInt());
        }
        ui->textBrowser->append(tmp);
    }
}

void MainWindow::playUserActions() {
    QFile jfile(Bridge::inst().getFileName());
    if (!jfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Error open file");
        return;
    }

    QByteArray data = jfile.readAll();
    jfile.close();
    QJsonDocument doc;
    doc = doc.fromJson(data);

    bool status = false;
    int recurs;
    QString lncount = ui->lineEdit->text();

    if (lncount.isEmpty())
        recurs = 1;
    else
        recurs = lncount.toInt();

    while (recurs > 0) {

        int start = clock();
        QTime time;
        time.setHMS(0,0,0);

        QtConcurrent::run([doc, start, time, status]() mutable {
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
                    if (event == tr("LBUTTONDOWN")) {
                        int x = val["x"].toInt();
                        int y = val["y"].toInt();
                        SetCursorPos(x, y);
                        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
                    } else if (event == tr("LBUTTONUP")) {
                        int x = val["x"].toInt();
                        int y = val["y"].toInt();
                        SetCursorPos(x, y);
                        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
                    } else if (event == tr("RBUTTONDOWN")) {
                        int x = val["x"].toInt();
                        int y = val["y"].toInt();
                        SetCursorPos(x, y);
                        mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
                    } else if (event == tr("RBUTTONUP")) {
                        int x = val["x"].toInt();
                        int y = val["y"].toInt();
                        SetCursorPos(x, y);
                        mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
                    } else if (event == tr("MBUTTONDOWN")) {
                        int x = val["x"].toInt();
                        int y = val["y"].toInt();
                        SetCursorPos(x, y);
                        mouse_event(MOUSEEVENTF_MIDDLEDOWN, x, y, 0, 0);
                    } else if (event == tr("MBUTTONUP")) {
                        int x = val["x"].toInt();
                        int y = val["y"].toInt();
                        SetCursorPos(x, y);
                        mouse_event(MOUSEEVENTF_MIDDLEUP, x, y, 0, 0);
                    } else if (event == tr("KEYDOWN")) {
                        keybd_event( val["vkey"].toInt(),
                                val["skey"].toInt(),
                                KEYEVENTF_EXTENDEDKEY | 0,
                                0 );
                    } else if (event == tr("KEYUP")) {
                        keybd_event( val["vkey"].toInt(),
                                val["skey"].toInt(),
                                KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                                0);
                    }
                }));
            }
            status = true;
        });
        recurs--;
        while (true) {
            if (!status)
                Sleep(1);
            else
                break;
        }
    }
    if (status)
        emit showStatus("Play complete");
}
