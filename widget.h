#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "filehandle.h"
#include "param.h"
#include "udp_sock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_lineEdit_4_returnPressed();
    void show_opponent_status(QByteArray info, quint16 port);

private:
    Ui::Widget *ui;
    FileHandle *filehandle;
    UdpSock *status_udp;
};
#endif // WIDGET_H
