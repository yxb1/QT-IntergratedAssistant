#ifndef _UDP_SOCK_HEAD_
#define _UDP_SOCK_HEAD_

#include <sys/types.h>
#include <QUdpSocket>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <memory.h>
#include <unistd.h>
#include <stdio.h>
#include "param.h"

#define MAX_BUFF_LEN (100*1024)

struct dst_addr {
    QString _dst;
    uint32_t _port;
};

class UdpSock : public QObject{
    Q_OBJECT
public:
    UdpSock(SocketInfo info);
    ~UdpSock();
    void SocketSend(char *ptr, int ss_len);
signals:
    void deliverInfo(QByteArray info, quint16 port);
public slots:
    void SocketRxHandle();

private:
    QUdpSocket *sock_fd;
    SocketInfo socket_info;
    dst_addr _addr;
    QThread *_thread;
};

#endif
