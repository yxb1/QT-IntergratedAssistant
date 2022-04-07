#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>

SocketInfo info_1 = {
    62001,
    57001,
    "192.168.1.12",
    "192.168.1.10",
    "client"
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    filehandle = nullptr;
    status_udp = new UdpSock(info_1);
    connect(status_udp, SIGNAL(deliverInfo(QByteArray, quint16)), this, SLOT(show_opponent_status(QByteArray, quint16)));
}

Widget::~Widget()
{
    delete ui;
    delete filehandle;
    delete status_udp;
}

void Widget::show_opponent_status(QByteArray info, quint16 port) {
    qDebug() << "here: " << port << endl;
    _OpponentStatus *status = (_OpponentStatus *)info.data();
    if(status->mcu_status) {
        ui->lineEdit->setText("ping success");
    }
    else {
        ui->lineEdit->setText("ping failed");
    }
    if(status->tbox_status) {
        ui->lineEdit_3->setText("ping success");
    }
    else {
        ui->lineEdit_3->setText("ping failed");
    }
    if(status->hut_status) {
        ui->lineEdit_2->setText("ping success");
    }
    else {
        ui->lineEdit_2->setText("ping failed");
    }
}

void Widget::on_lineEdit_4_returnPressed()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("选择待分析文件"), "./", tr("落盘文件(*pcap *bin)"));
    ui->lineEdit_4->setText(filename);
    qDebug() << "The file we choose is " << filename;
    filehandle = new FileHandle(filename);
    filehandle->ReadData();
    ui->widget->addGraph();
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->widget->graph(0)->setData(filehandle->curr_seq, filehandle->delay_time);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->graph(0)->rescaleAxes();
    ui->widget->replot();
}
