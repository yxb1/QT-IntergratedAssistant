#include <QThread>
#include "udp_sock.h"

UdpSock::UdpSock(SocketInfo info): socket_info(info){
    sock_fd = new QUdpSocket();
    if(!strcmp("server", socket_info.identify.toStdString().c_str())) {
        _addr._dst = socket_info.cli_ip;
        _addr._port = socket_info.cli_port;
        if(!sock_fd->bind(QHostAddress(socket_info.ser_ip), socket_info.ser_port)) {
            std::cout << "Bind fail - " << strerror(errno) << std::endl;
            exit(-1);
        }
    }
    else{
        _addr._dst = socket_info.ser_ip;
        _addr._port = socket_info.ser_port;
        if(!sock_fd->bind(QHostAddress(socket_info.cli_ip), socket_info.cli_port)) {
            std::cout << "Bind fail - " << strerror(errno) << std::endl;
            exit(-1);
        }
    }

    _thread = new QThread();
    connect(sock_fd, SIGNAL(readyRead()), this, SLOT(SocketRxHandle()), Qt::DirectConnection);
    //this->moveToThread(_thread);
    sock_fd->moveToThread(_thread);
    _thread->start();
    qDebug() << "UdpSock: Enter constructor" << endl;
}

UdpSock::~UdpSock() {
    if(sock_fd != NULL) {
        delete sock_fd;
        sock_fd = NULL;
    }
    qDebug() << "UdpSock: leave destructor" << endl;
}

void UdpSock::SocketSend(char *ptr, int ss_len) {
    static char s_buff[MAX_BUFF_LEN] = {0};
    if(ss_len > MAX_BUFF_LEN) {
        qDebug() << "Oversize when send, ss_len is " << ss_len << endl;
        exit(-1);
    }
    if(ptr == NULL) {
        qDebug() << "ptr is nullptr when send." << endl;
        exit(-1);
    }
    else
    {
        memcpy(s_buff, ptr, ss_len);
    }
    int real_send = sock_fd->writeDatagram(s_buff, ss_len, QHostAddress(_addr._dst), _addr._port);
    if(real_send < 0) {
        qDebug() << "real_send is " << real_send << ". " << strerror(errno) <<endl;
    }
    else
    {
        qDebug() << "real_send is " << real_send << endl;
    }
}

void UdpSock::SocketRxHandle() {
    //static char r_buff[MAX_BUFF_LEN] = {0};
    QHostAddress client_address;
    quint16 client_port;
    while(sock_fd->hasPendingDatagrams()) {
        qDebug() << "Pending size = " << sock_fd->pendingDatagramSize() << endl;
        QByteArray m_data;
        m_data.resize(sock_fd->pendingDatagramSize());
        sock_fd->readDatagram(m_data.data(), m_data.size(), &client_address, &client_port);
        QString string = m_data.toHex();
        qDebug() << string << endl;
        deliverInfo(m_data, client_port);
    }
}
