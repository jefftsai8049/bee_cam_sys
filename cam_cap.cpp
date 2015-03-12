#include "cam_cap.h"


cam_cap::cam_cap(const std::string &name, QObject *parent) :
    QThread(parent)
{
    imgProcess = new img_process;
    //setting capture parameter
    this->cap_pos = 0;
    this->cap_name = name;
    this->cap_status = false;
    this->cap_end = false;
    //load calibration model file
    cc = new camera_calibration;
    calibrationLoaded = 1;
    /*calibrationLoaded = */cc->loadYMLFile("cam_init.yml");

}

cam_cap::~cam_cap()
{

    delete imgProcess;
    delete cc;

}

void cam_cap::run()
{
    //read capture img
    cap = new cv::VideoCapture(this->cap_pos);
    this->cap_status = true;
    while(cap->isOpened() && this->cap_status)
    {
        cap->read(this->cap_frame);
        cap_frame = imgProcess->rotate(cap_frame);
        if(calibrationLoaded)
        {
            cv::Mat undistorted;
            cc->undistorted(cap_frame,undistorted);
            emit capSend(undistorted);
        }
        else
        {
            emit capSend(cap_frame);
        }
    }
    this->cap_end = true;
    cap->release();
}
//stop camera capture
void cam_cap::capStop()
{
    this->cap_status = false;
}
//set camera position
void cam_cap::setCapPosition(const int &pos)
{
    this->cap_pos = pos;
}
//check camera is end or not
bool cam_cap::isCamEnd()
{
    return this->cap_end;
}
//check camera status(connectting or not)
bool cam_cap::camStatus()
{
    return this->cap_status;
}

