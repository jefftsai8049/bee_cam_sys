#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H

#include <QObject>

#include "opencv.hpp"

class img_process : public QObject
{
    Q_OBJECT
public:
    explicit img_process(QObject *parent = 0);

    cv::Mat rotate(const cv::Mat &src);
    void stitching3Img(const cv::Mat &src1,const cv::Mat &src2,const cv::Mat &src3,cv::Mat &dst);

signals:

public slots:



};

#endif // IMG_PROCESS_H
