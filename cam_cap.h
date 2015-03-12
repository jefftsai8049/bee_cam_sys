#ifndef CAM_CAP_H
#define CAM_CAP_H

#include <QThread>
#include <QDebug>

#include "opencv.hpp"
#include "img_process.h"
#include "camera_calibration.h"

class cam_cap : public QThread
{
    Q_OBJECT
public:
    explicit cam_cap(const std::string &name,QObject *parent = 0);
    ~cam_cap();
    void capStop();
    void setCapPosition(const int &pos);
    bool isCamEnd();
    bool camStatus();
signals:
    void capSend(const cv::Mat &src);
public slots:

private:
    cv::VideoCapture *cap;
    img_process *imgProcess;
    camera_calibration *cc;

    std::string cap_name;
    int cap_pos;
    cv::Mat cap_frame;
    bool cap_status;
    bool cap_end;

    bool calibrationLoaded;

    void run();


};

#endif // CAM_CAP_H
