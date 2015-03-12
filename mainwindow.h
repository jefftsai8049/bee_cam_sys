#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>
#include <vector>

#include <QMainWindow>
#include <QDebug>
#include <QMetaType>
#include <QDir>
#include <QTime>
#include <QFileDialog>

#include "cam_cap.h"
#include "img_process.h"
#include "camera_calibration.h"
#include "panorama.h"

#include "opencv.hpp"
#include "stitching.hpp"
#include "features2d.hpp"
#include "xfeatures2d.hpp"


#define video_width 480
#define video_height 640
#define video_1_x 30
#define video_1_y 30
#define video_2_x video_1_x+video_width
#define video_2_y 30
#define video_3_x video_2_x+video_width
#define video_3_y 30

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cam_connect_pushButton_clicked();

    void on_cam_disconnect_pushButton_clicked();


    void cam_1_cap_receive(const cv::Mat &src);

    void cam_2_cap_receive(const cv::Mat &src);

    void cam_3_cap_receive(const cv::Mat &src);

    void closeEvent (QCloseEvent *event);


    void on_record_pushButton_clicked();

    void on_stopRecord_pushButton_clicked();

    void on_calibration_pushButton_clicked();

    void on_calibrationShot_pushButton_clicked();

    void on_calculation_pushButton_clicked();

    void on_houghCircle_pushButton_clicked();

    void on_surf_pushButton_clicked();

    void on_warp_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    cam_cap *cam_1;
    cam_cap *cam_2;
    cam_cap *cam_3;
    img_process *imgProcess;
    camera_calibration *cc;
    panorama *pano;
    //cv::VideoWriter writer;

    std::vector<cv::Mat> img;

    bool camStartStatus;

    bool camRecord;
    int clibrationCamera;
    int snapshots;
    QString calibrationFileName;

    void camStart();


};

#endif // MAINWINDOW_H
