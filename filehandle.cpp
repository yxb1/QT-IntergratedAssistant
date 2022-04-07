#include "filehandle.h"

FileHandle::FileHandle(QString &filename) {
    file = nullptr;
    if(filename.isEmpty()) {
        qDebug() << "Filename is empty";
        exit(-1);
    }

    file = new QFile(filename);
    memset(&perfCal, 0 , sizeof(_CommPerfCal));
    qDebug() << "The perfCal size is " << sizeof(_CommPerfCal);
}

FileHandle::~FileHandle() {
    if(file != nullptr) free(file);
}

bool FileHandle::ReadData() {
    if(file->open(QIODevice::ReadOnly) == false) {
        qDebug() << "Open file failed! " << strerror(errno);
        exit(-1);
    }
    //int32_t maxSize = file->size();
    while(true) {
        //uint64_t ret = file->read((char *)&perfCal, sizeof(_CommPerfCal));
        //qDebug() << "The real read lenth is " << ret;
        if(file->read((char *)&perfCal, sizeof(_CommPerfCal)) != sizeof(_CommPerfCal)) {
            qDebug() << "Read file lenth is less than sizeof(_CommPerfCal), break while!";
            break;
        }
        else{
            qDebug() << "perfCal.curr_seq " << perfCal.curr_seq;
            qDebug() << "perfCal.time_delay " << perfCal.time_delay;
            curr_seq.push_back(perfCal.curr_seq);
            total_loss.push_back(perfCal.total_package_loss_num);
            total_disorder.push_back(perfCal.total_package_disorder_num);
            total_repeat.push_back(perfCal.total_package_repeated_num);
            curr_loss.push_back(perfCal.curr_package_loss_num);
            curr_disorder.push_back(perfCal.curr_package_disorder_num);
            curr_repeat.push_back(perfCal.curr_is_package_repeated);
            total_frame.push_back(perfCal.total_frames);
            if(perfCal.time_delay > 25000000) {
                delay_time.push_back(25000000/1000000);
            }
            else if(perfCal.time_delay < 0) {
                delay_time.push_back(-25000000/1000000);
            }
            else {
                delay_time.push_back(perfCal.time_delay/1000000);
            }
            //delay_time.push_back(perfCal.time_delay);
            time_jump.push_back(perfCal.time_jump);
            curr_time.push_back(perfCal.curr_time);
            mcu_time.push_back(perfCal.mcu_time);
        }
    }
    return true;
}
