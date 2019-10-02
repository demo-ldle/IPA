#include <iostream>
#include <opencv2/opencv.hpp>
#include "conv.h"

int main(int argc, char **argv) {
  
   conv img_conv;
   cv::Mat gaussK;
   gaussK=img_conv.gaussKernel(1);
   float sum=0;
   for (int i = 0; i < gaussK.rows; i++)
      {
	  for (int j = 0; j < gaussK.cols; j++)
	  {
	      sum += gaussK.ptr<float>(i)[j];
	  }
      }
   cout<<"gause:"<<endl<<gaussK<<endl<<"sum of gause kernal :"<<sum<<endl;
   cin.get();

   return 0;
}
