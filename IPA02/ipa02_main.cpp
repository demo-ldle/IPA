#include <iostream>
#include <opencv2/opencv.hpp>
#include "conv.h"

int main(int argc, char **argv) {
  
   conv img_conv;
   cv::Mat gaussK;
   if(argc>1){
     float sig=0;
     int m;
     sig=atof(argv[1]);
     m=atoi(argv[2]);
     cout<<"input sigma:"<<sig<<endl;
    // cin>>sig;
     cout<<"input m:"<<m<<endl;
    // cin>>m;
     gaussK=img_conv.gaussKernel(sig,m);
    }else{
     gaussK=img_conv.gaussKernel(1);
    }
   float sum=0;
   for (int i = 0; i < gaussK.rows; i++)
      {
	  for (int j = 0; j < gaussK.cols; j++)
	  {
	      sum += gaussK.ptr<float>(i)[j];
	  }
      }
   cout<<"gause:"<<endl<<gaussK<<endl<<"sum of gause kernal :"<<sum<<endl;
 //  cin.get();

   return 0;
}
