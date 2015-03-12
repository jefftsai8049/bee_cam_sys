#include "cam_connect.h"

cam_connect::cam_connect(const int &cam_pos_1,const int cam_pos_2,const int &cam_pos_3,QObject *parent) :
    QThread(parent)
{
    this->cam_pos[0] = cam_pos_1;
    this->cam_pos[1] = cam_pos_2;
    this->cam_pos[2] = cam_pos_3;

    cam_1 = new cam_cap(this->cam_pos[0],"Cam 1");
}

void cam_connect::connect_cam()
{
    cam_1->start();
}

void cam_connect::disconnect_cam()
{
    cam_1->cap_stop();
}

void cam_connect::run()
{

}

