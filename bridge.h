#ifndef BRIDGE_H
#define BRIDGE_H

#include <map>
#include <vector>
#include <string>
#include <QTimer>
#include <QTime>
#include <ctime>
#include <QQueue>

class Bridge {
    Bridge(){}
    ~Bridge(){}

    Bridge(Bridge const&) = delete;
    Bridge operator = (Bridge const&) = delete;

    struct Event {
        QString time;
        QString eventname;
        unsigned int key_vnum;
        unsigned int key_snum;
        int x = 0;
        int y = 0;
    };

public:
    static Bridge &inst() {
        static Bridge b;
        return b;
    }

public:
    void startTimer() {
        start_t = clock();
        _timer.setHMS(0,0,0);
    }

    QString getTimer() {
        int end = clock();
        uint32_t ms = ((end - start_t) * 1000) / CLOCKS_PER_SEC;
        return _timer.addMSecs(ms).toString("hh:mm:ss.zzz");
    }

    void setEvent(Event ev) {
        _queue.enqueue(ev);
    }

    Event getStruct() {
        Event ev;
        return ev;
    }

    QQueue<Event> getQueue() {
        return _queue;
    }

    void setFileName(QString fname) {
        filename = fname;
    }

    QString getFileName() {
        return filename;
    }

    void setData(QByteArray d) {
        data = d;
    }

    QByteArray getData() {
        return data;
    }

private:
    QTime _timer;
    int start_t = 0;
    QQueue<Event> _queue;
    QString filename;
    QByteArray data;
};

#endif // BRIDGE_H
