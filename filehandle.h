#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>

;
#pragma pack(push,1)
typedef struct {
    uint32_t curr_seq;
    uint32_t total_package_loss_num;
    uint32_t total_package_disorder_num;
    uint32_t total_package_repeated_num;
    uint32_t curr_package_loss_num;
    uint32_t curr_package_disorder_num;
    uint32_t curr_is_package_repeated;
    uint32_t total_frames;
    int64_t time_delay;
    uint32_t time_jump;
    uint64_t curr_time;
    uint64_t mcu_time;
}_CommPerfCal;
#pragma pack(pop)

class FileHandle {
public:
    FileHandle(QString &filename);
    virtual ~FileHandle();
    bool ReadData();

public:
    QVector<double> curr_seq;
    QVector<uint32_t> total_loss;
    QVector<uint32_t> total_disorder;
    QVector<uint32_t> total_repeat;
    QVector<uint32_t> curr_loss;
    QVector<uint32_t> curr_disorder;
    QVector<uint32_t> curr_repeat;
    QVector<uint32_t> total_frame;
    QVector<double>  delay_time;
    QVector<uint32_t> time_jump;
    QVector<uint64_t> curr_time;
    QVector<uint64_t> mcu_time;
    QVector<uint32_t> local_time;
    QVector<uint32_t> over_second;
    QVector<uint32_t> want_tick;

private:
    QFile *file;
    _CommPerfCal perfCal;
};

#endif // FILEHANDLE_H
