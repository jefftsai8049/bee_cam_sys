#include "img_process.h"

img_process::img_process(QObject *parent) :
    QObject(parent)
{
}
//rotate 90deg
cv::Mat img_process::rotate(const cv::Mat &src)
{
    cv::Mat dst;
    cv::transpose(src,dst);
    cv::flip(dst,dst,1);
    return dst;
}
//stitching 3 Imgs
void img_process::stitching3Img(const cv::Mat &src1, const cv::Mat &src2, const cv::Mat &src3, cv::Mat &dst)
{
    dst.create(src1.rows,src1.cols+src2.cols+src3.cols,src1.type());
    cv::Mat part = dst(cv::Rect(0,0,src1.cols,src1.rows));
    src1.copyTo(part);
    part = dst(cv::Rect(src1.cols,0,src2.cols,src2.rows));
    src2.copyTo(part);
    part = dst(cv::Rect(src1.cols+src2.cols,0,src3.cols,src3.rows));
    src3.copyTo(part);
}
