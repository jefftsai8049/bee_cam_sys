#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgProcess = new img_process;
    camStartStatus = 0;
    camRecord = 0;
    //initialize capture
//    cam_1 = new cam_cap("Cam 1");
//    cam_2 = new cam_cap("Cam 2");
//    cam_3 = new cam_cap("Cam 3");
    img.resize(3);
    cam = 0;
//    qRegisterMetaType< std::vector<cv::Mat> >("std::vector<cv::Mat>");
//    connect(cam_1,SIGNAL(capSend(cv::Mat)),this,SLOT(cam_1_cap_receive(cv::Mat)));
//    connect(cam_2,SIGNAL(capSend(cv::Mat)),this,SLOT(cam_2_cap_receive(cv::Mat)));
//    connect(cam_3,SIGNAL(capSend(cv::Mat)),this,SLOT(cam_3_cap_receive(cv::Mat)));

    cc = new camera_calibration;
    pano = new panorama;

}

MainWindow::~MainWindow()
{

    cv::destroyAllWindows();
//    cam_1->deleteLater();

//    cam_2->deleteLater();

//    cam_3->deleteLater();
    delete imgProcess;
    delete cc;
    delete pano;

//    delete cam_1;
//    delete cam_2;
//    delete cam_3;
    delete ui;

}

void MainWindow::on_cam_connect_pushButton_clicked()
{
    if(cam == 0)
    {
        std::vector<int> camPos[3];
        camPos[0] = ui->cam;
//        cam = new cam_cap();
    }
//    if(!camStartStatus)
//    {
//        camStart();
//        camStartStatus = 1;
//    }
//    if(ui->cam_1_checkBox->isChecked())
//        cam_1->start();
//    if(ui->cam_2_checkBox->isChecked())
//        cam_2->start();
//    if(ui->cam_3_checkBox->isChecked())
//        cam_3->start();



    ui->statusBar->showMessage("Camera Opened");
}

void MainWindow::on_cam_disconnect_pushButton_clicked()
{
//    cam_1->capStop();
//    cam_2->capStop();
//    cam_3->capStop();
}


void MainWindow::cam_1_cap_receive(const cv::Mat &src)
{
//    cv::imshow("0",src);
    img[0] = src.clone();
    QImage temp(img[0].data,img[0].cols,img[0].rows,QImage::Format_RGB888);
    temp = temp.scaled(480,640,Qt::KeepAspectRatio,Qt::FastTransformation);
    ui->video_1_label->setGeometry(QRect(video_1_x,video_1_y,video_width,video_height));
    ui->video_1_label->setPixmap(QPixmap::fromImage(temp));
}

void MainWindow::cam_2_cap_receive(const cv::Mat &src)
{
//    cv::imshow("1",src);
//    img[1] = src.clone();
//    QImage temp(img[1].data,img[1].cols,img[1].rows,QImage::Format_RGB888);
//    temp = temp.scaled(480,640,Qt::KeepAspectRatio,Qt::FastTransformation);
//    ui->video_2_label->setGeometry(QRect(video_2_x,video_2_y,video_width,video_height));
//    ui->video_2_label->setPixmap(QPixmap::fromImage(temp));
}

void MainWindow::cam_3_cap_receive(const cv::Mat &src)
{
//    cv::imshow("2",src);
//    img[2] = src.clone();
//    QImage temp(img[2].data,img[2].cols,img[2].rows,QImage::Format_RGB888);
//    temp = temp.scaled(480,640,Qt::KeepAspectRatio,Qt::FastTransformation);
//    ui->video_3_label->setGeometry(QRect(video_3_x,video_3_y,video_width,video_height));
//    ui->video_3_label->setPixmap(QPixmap::fromImage(temp));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    cam_1->capStop();
//    cam_2->capStop();
//    cam_3->capStop();

//    cam_1->deleteLater();

//    cam_2->deleteLater();

//    cam_3->deleteLater();

}

void MainWindow::camStart()
{

//    cam_1->setCapPosition(ui->cam_1_comboBox->currentText().toInt());
//    cam_2->setCapPosition(ui->cam_2_comboBox->currentText().toInt());
//    cam_3->setCapPosition(ui->cam_3_comboBox->currentText().toInt());

}


void MainWindow::on_record_pushButton_clicked()
{
//    camRecord = 1;
//    cv::VideoWriter video("test.avi",cv::VideoWriter::fourcc('D', 'I', 'V', 'X'),12,cv::Size(1200,1600),true);
//    while(camRecord)
//    {
//        video << img[0];
//        //cv::imshow("frame",frame);
//        //cv::waitKey(50);
//        if(cv::waitKey(50) == 27)
//        {
//            break;
//        }
//    }
//    qDebug() << "release";
//    video.release();
}

void MainWindow::on_stopRecord_pushButton_clicked()
{
//    camRecord = 0;
}

void MainWindow::on_calibration_pushButton_clicked()
{
    calibrationFileName = ".jpg";
    ui->calibrationShot_pushButton->setEnabled(true);
    clibrationCamera = ui->calibration_comboBox->currentText().toInt();
    snapshots = 0;
    QDir snapshotsFolder("snapshots");
    if (!snapshotsFolder.exists()) {
        snapshotsFolder.mkpath(".");
    }
}

void MainWindow::on_calibrationShot_pushButton_clicked()
{
    if(snapshots >= ui->calibrationFiles_spinBox->value())
        return;
    QString filename = "snapshots/camera_"+ui->calibration_comboBox->currentText()+"_"+QString::number(snapshots)+calibrationFileName;
    ui->statusBar->showMessage("Image saved "+filename);
    cv::imwrite(filename.toStdString(),img[clibrationCamera]);
    snapshots++;
}

void MainWindow::on_calculation_pushButton_clicked()
{
    //load image files
    QFileDialog fd;
    QStringList QfileNames = fd.getOpenFileNames(this, tr("Open File"),"",tr("Images (*.jpg)"));
    if(QfileNames.isEmpty())
    {
        return;
    }
    std::vector<std::string> fileNames;
    for(int i=0;i<QfileNames.size();i++)
    {
        fileNames.push_back(QfileNames[i].toStdString());
    }

    //calibration
    QString folder = "";
    cv::Size SizePattern = cv::Size(ui->calibrationCols_spinBox->value(), ui->calibrationRows_spinBox->value());
    cv::Size2f SizeGrid = cv::Size2f(ui->gridSize_lineEdit->text().toFloat(), ui->gridSize_lineEdit->text().toFloat());
    cc->CameraCalibration(true, SizePattern, SizeGrid, fileNames);
    cc->SaveIntrinsic(folder.toStdString(), std::string("cam_init.yml"));
    cc->DisplayUndistortedImg(false);

}

void MainWindow::on_houghCircle_pushButton_clicked()
{
    QFileDialog fd;
    QStringList QfileNames = fd.getOpenFileNames(this, tr("Open File"),"",tr("Images (*.jpg)"));

    if(QfileNames.isEmpty())
    {
        return;
    }
    std::vector<cv::Mat> imgs;
    for(int i=0;i<QfileNames.size();i++)
    {
        imgs.push_back(cv::imread(QfileNames[i].toStdString(),cv::IMREAD_COLOR));
    }

    for(int j=0;j<imgs.size();j++)
    {
//        imgs[j]
        //std::vector<cv::Vec3f> circlePosition;
        //cv::HoughCircles(img[j],circlePosition,)

    }
}

void MainWindow::on_surf_pushButton_clicked()
{
//    //open img file
//    QFileDialog fd;
//    QStringList QfileNames = fd.getOpenFileNames(this, tr("Open File"),"",tr("Images (*.jpg)"));

//    if(QfileNames.isEmpty())
//    {
//        return;
//    }
//    std::vector<cv::Mat> imgs;
//    for(int i=0;i<QfileNames.size();i++)
//    {
//        imgs.push_back(cv::imread(QfileNames[i].toStdString(),cv::IMREAD_COLOR));
//    }

    //panorama
    cv::Mat dst;
    pano->panoramaThreeImgs(img,700,dst);
    pano->saveTwoHomography("homography.yml");
    cv::imshow("dst",dst);

}

void MainWindow::on_warp_pushButton_clicked()
{
//    pano->loadTwoHomography("homography.yml");

//    //open img file
//    QFileDialog fd;
//    QStringList QfileNames = fd.getOpenFileNames(this, tr("Open File"),"",tr("Images (*.jpg)"));

//    if(QfileNames.isEmpty())
//    {
//        return;
//    }
//    std::vector<cv::Mat> imgs;
//    for(int i=0;i<QfileNames.size();i++)
//    {
//        imgs.push_back(cv::imread(QfileNames[i].toStdString(),cv::IMREAD_COLOR));
//    }
pano->loadTwoHomography("homography.yml");
    cv::Mat dst;
    pano->warpingThreeImgs(img,dst);
    cv::imshow("yaya",dst);
}
