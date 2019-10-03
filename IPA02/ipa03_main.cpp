#include <iostream>
#include <opencv2/opencv.hpp>
#include "conv.h"

//sobel边缘检测算子
cv::Mat sobel_y_kernal= (cv::Mat_<float>(3,3) << -1, -2 ,-1, 0,  0 , 0, 1,  2 , 1);
cv::Mat average_kernal = (cv::Mat_<float>(3,3) << 0.111, 0.111 ,0.111,
                                                0.111, 0.111, 0.111,
                                                0.111, 0.111, 0.111);
cv::Mat cet_kernal= (cv::Mat_<float>(3,3) << 0, -1 ,0, -1,  5 , -1, 0,  -1 , 0);
int main(int argc, char **argv) {
  if(argc<2){
    cout<<"please input the Picture's directory like /xx/xx/xx.tiff"<<endl;
    return 0;
  }
   conv img_conv;
   cv::Mat img_in=cv::imread(string(argv[1]));
   cv::Mat img_out=cv::Mat::zeros(img_in.rows,img_in.cols,img_in.type());
   cv::Mat img_out_opencv=cv::Mat::zeros(img_in.rows,img_in.cols,img_in.type());

   
   cv::Mat gaussK;
   cv::Mat img_out_gray[4]=cv::Mat::zeros(img_in.rows,img_in.cols,img_in.type());
   gaussK=img_conv.gaussKernel(1);
   img_out_gray[0]=img_conv.twodConv(img_in,gaussK);
   imwrite("sig1.tif",img_out_gray[0]);
   gaussK=img_conv.gaussKernel(2);
   img_out_gray[1]=img_conv.twodConv(img_in,gaussK);
   imwrite("sig2.tif",img_out_gray[1]);

   gaussK=img_conv.gaussKernel(3);
   img_out_gray[2]=img_conv.twodConv(img_in,gaussK);
   imwrite("sig3.tif",img_out_gray[2]);
   gaussK=img_conv.gaussKernel(5);
   img_out_gray[3]=img_conv.twodConv(img_in,gaussK);
   imwrite("sig5.tif",img_out_gray[3]);

   gaussK=img_conv.gaussKernel(1);
   img_out=img_conv.twodConv(img_in,gaussK);
   cv::filter2D(img_in,img_out_opencv,img_in.depth(),gaussK);
   
   cv::Mat sig1=img_out-img_out_opencv;
   cv::Mat img_sig1_replicate=cv::Mat::zeros(img_in.rows,img_in.cols,img_in.type());
   imshow("compare",sig1);
   //imwrite("sig1_zero.tif",img_out);
   
   img_sig1_replicate=img_conv.twodConv(img_in,gaussK,"replicate");
   img_sig1_replicate=img_out-img_sig1_replicate;
   imshow("sig1_padding.tif",img_sig1_replicate);
   cv::waitKey(0);


   return 0;
}
