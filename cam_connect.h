#ifndef CAM_CONNECT_H
#define CAM_CONNECT_H

#include <QThread>
#include <QDebug>

#include "opencv.hpp"

#include "cam_cap.h"

class cam_connect : public QThread
{
    Q_OBJECT
public:
    explicit cam_connect(const int &cam_pos_1,const int cam_pos_2,const int &cam_pos_3,QObject *parent = 0);
    void connect_cam();
    void disconnect_cam();
signals:

public slots:

private:
    std::vector<int> cam_pos;

    cam_cap *cam_1;
    void run();


};
#endif // CAM_CONNECT_H
