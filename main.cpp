#include <iostream>
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include <fstream>
#include <sstream>
#include<math.h>
#include "face.hpp"
using namespace std;
using namespace cv;

RNG g_rng(12345);
Ptr<face::FaceRecognizer> model;

int Predict(Mat src_image)  //识别图片
{
    Mat face_test;
    int predict = 0;
    //截取的ROI人脸尺寸调整
    if (src_image.rows >= 120)
    {
        //改变图像大小，使用双线性差值
        resize(src_image, face_test, Size(92, 112));

    }
    //判断是否正确检测ROI
    if (!face_test.empty())
    {
        //测试图像应该是灰度图
        predict = model->predict(face_test);
    }
    cout << predict << endl;
    return predict;
}

int main()
{
    VideoCapture cap(1);    //打开默认摄像头
    if (!cap.isOpened())
    {
        return -1;
    }
    Mat frame;
    Mat gray;
    //这个分类器是人脸检测所用
    CascadeClassifier cascade;
    bool stop = false;
    //训练好的文件名称，放置在可执行文件同目录下
    cascade.load("G:\\Qprogram\\end\\haarcascade_frontalface_alt2.xml");
    model = face::LBPHFaceRecognizer::create();
    //1.加载训练好的模型
    model->read("G:\\Qprogram\\end\\MyFaceLBPHModel.xml");// opencv2用load
    while (1)
    {
        cap >> frame;

        vector<Rect> faces(0);//建立用于存放人脸的向量容器

        cvtColor(frame, gray, COLOR_RGB2GRAY);//测试图像必须为灰度图

        equalizeHist(gray, gray); //变换后的图像进行直方图均值化处理
        //检测人脸
        cascade.detectMultiScale(gray, faces,
            1.1, 4,0|
            //|CV_HAAR_FIND_BIGGEST_OBJECT
             CASCADE_DO_ROUGH_SEARCH,
            //| CV_HAAR_SCALE_IMAGE,
            Size(70, 70), Size(1000, 1000));
        Mat* pImage_roi = new Mat[faces.size()];    //定以数组
        Mat face;
        Point text_lb;//文本写在的位置
        //框出人脸
        string str;
        for (int i = 0; i < faces.size(); i++)
        {
            pImage_roi[i] = gray(faces[i]); //将所有的脸部保存起来
            text_lb = Point(faces[i].x, faces[i].y);
            if (pImage_roi[i].empty())
                continue;
            cout<<Predict(pImage_roi[i]);
            switch (Predict(pImage_roi[i])) //对每张脸都识别
            {
            case 35:str = "yxyx"; break;
            default: str = "Error"; break;
            }
            Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//所取的颜色任意值
            rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), color, 1, 8);//放入缓存
            putText(frame, str, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));//添加文字
        }

        delete[]pImage_roi;
        imshow("face", frame);
        if(waitKey(200) == 27)
        break;
    }

        return 0;

    cout << "Hello World!" << endl;
    return 0;
}
