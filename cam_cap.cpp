#include "cam_cap.h"


cam_cap::cam_cap(const std::vector<int> pos, QObject *parent) :
    QThread(parent)
{
    imgProcess = new img_process;


    //setting capture parameter
    for(int i=0;i<pos.size();i++)
    {
        this->camPos[i] = pos[i];
    }


    this->capStatus = false;
    this->capEnd = false;
    //load calibration model file
    cc = new camera_calibration;
    calibrationLoaded = 0;
    cc->loadYMLFile("cam_init.yml");

}

cam_cap::~cam_cap()
{

    delete imgProcess;
    delete cc;

}

void cam_cap::run()
{

    capL = new cv::VideoCapture(this->camPos[0]);
    capM = new cv::VideoCapture(this->camPos[1]);
    capR = new cv::VideoCapture(this->camPos[2]);

    capFrame.resize(3);

    //read capture img
    this->capStatus = true;

    while(capL->isOpened() && capM->isOpened() && capR->isOpened() && this->capStatus)
    {
        capL->read(this->capFrame[0]);
        capM->read(this->capFrame[1]);
        capR->read(this->capFrame[2]);

        for(int i=0;i<this->capFrame.size();i++)
        {
            this->capFrame[i] = imgProcess->rotate(this->capFrame[i]);

            emit capSend(this->capFrame);
        }


//        if(calibrationLoaded)
//        {
//            cv::Mat undistorted;
//            cc->undistorted(cap_frame,undistorted);
//            emit capSend(undistorted);
//        }
//        else
//        {
//            emit capSend(cap_frame);
//        }
    }
    this->capEnd = true;
    capL->release();
    capM->release();
    capR->release();
}
//stop camera capture
void cam_cap::capStop()
{
    this->capStatus = false;
}
////set camera position
//void cam_cap::setCapPosition(const int &pos)
//{
//    this->cap_pos = pos;
//}
//check camera is end or not
bool cam_cap::isCamEnd()
{
    return this->capEnd;
}
//check camera status(connectting or not)
bool cam_cap::camStatus()
{
    return this->capStatus;
}

