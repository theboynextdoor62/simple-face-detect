## opencv学习笔记

#样本取样
sampling.cpp
首先下载样例数据https://www.kaggle.com/datasets/kasikrit/att-database-of-faces
打开摄像头拍摄10张照片，利用opencv自带的haarcascade_frontalface_alt2.xml对人脸进行识别，并对照片进行灰度处理，得到一个人的样本。
#模型训练
script.py
获取每个样本的路径，以及lable
train.cpp
用opencv自带的模型对样本训练，得到3种模型文件MyFaceFisherModel.xml、MyFaceLBPHModel.xml、MyFacePCAModel.xml
#人脸识别
main.cpp
随便选一种模型进行人脸识别，我选的MyFaceLBPHModel.xml（准确率最高）
