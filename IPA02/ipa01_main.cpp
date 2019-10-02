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

//    for (int i = 0; i < gaussK.rows; i++)
//   {
//       for (int j = 0; j < gaussK.cols; j++)
//       {
// 	  
// 	  sum += gaussK.ptr<float>(i)[j];
//       }
//   }
//    cout<<"gause:"<<gaussK<<"sum:"<<sum<<endl;
   img_out=img_conv.twodConv(img_in,cet_kernal);
   cv::filter2D(img_in,img_out_opencv,img_in.depth(),cet_kernal);
   
   imshow("lena",img_in);
   imshow("lena_conv",img_out);
   imshow("lena_conv_opencv",img_out_opencv);
   cv::waitKey(0);

   return 0;
}
