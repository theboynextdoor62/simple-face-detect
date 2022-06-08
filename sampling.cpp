#include <iostream>
#include <opencv.hpp>
#include <vector>
#include<stdio.h>
using namespace std;
using namespace cv;
int main()
{
    CascadeClassifier cascada;
    //将opencv官方训练好的人脸识别分类器拷贝到自己的工程目录中
    cascada.load("G:\\Qprogram\\untitled\\haarcascade_frontalface_alt2.xml");
    VideoCapture cap(1);  //0表示电脑自带的，如果用一个外接摄像头，将0变成1
    Mat frame, myFace;
    int pic_num = 1;
    while (1) {
        //摄像头读图像
        cap >> frame;
        vector<Rect> faces;//vector容器存检测到的faces
        Mat frame_gray;

        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);//转灰度化，减少运算

        cascada.detectMultiScale(frame_gray, faces, 1.1, 4, CASCADE_DO_ROUGH_SEARCH, Size(70, 70), Size(1000, 1000));
        printf("检测到人脸个数：%zd\n", faces.size());

        //识别到的脸用矩形圈出
        for (int i = 0; i < faces.size(); i++)
        {
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
        }
        //当只有一个人脸时，开始拍照
        if (faces.size() == 1)
        {
            Mat faceROI = frame_gray(faces[0]);//在灰度图中将圈出的脸所在区域裁剪出
            //cout << faces[0].x << endl;//测试下face[0].x
            resize(faceROI, myFace, Size(92, 112));//将兴趣域size为92*112
            putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);//在 faces[0].tl()的左上角上面写序号
            string filename = format("G:\\Qprogram\\untitled\\photo\\%d.jpg", pic_num); //图片的存放位置，frmat的用法跟QString差不对
            imwrite(filename, myFace);//存在当前目录下
            imshow(filename, myFace);//显示下size后的脸
            waitKey(500);//等待500us
            destroyWindow(filename);//:销毁指定的窗口
            pic_num++;//序号加1
            if (pic_num == 11)
            {
                return 0;//当序号为11时退出循环,一共拍10张照片
            }
        }
        int c = waitKey(10);
        if ((char)c == 27) { break; } //10us内输入esc则退出循环
        imshow("frame", frame);//显示视频流
        waitKey(100);//等待100us
    }
    return 0;
 }
