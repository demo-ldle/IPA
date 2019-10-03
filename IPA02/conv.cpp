/*
 * Copyright 2019 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "conv.h"

conv::conv()
{

}

conv::~conv()
{
  
}
//load conv kernal and detect the window size
bool conv::load_kernal(cv::Mat kernel_in)
{
  //cout<<kernel_in<<endl;
 // kernal=kernel_in/(kernel_in.cols*kernel_in.rows);
//   kernal=kernel_in;
  kernal=cv::Mat::zeros(kernel_in.rows,kernel_in.cols,kernel_in.type());
  for (int i=0;i<kernel_in.rows;i++){
    for(int j=0;j<kernel_in.cols;j++){
      kernal.at<float>(i,j)=kernel_in.at<float>(kernel_in.rows-i-1,kernel_in.cols-j-1);
    }
  }
  if(kernal.cols%2==1&&kernal.rows%2==1){
    pad_x=(kernal.cols-1)/2;
    pad_y=(kernal.rows-1)/2;
    //Normalization
//     float sum=0;
//     for(int norm_x=0;norm_x<kernal.rows;norm_x++){
//       for(int norm_y=0;norm_y<kernal.cols;norm_y++){
// 	sum+=kernal.at<float>(norm_x,norm_y);
// 	cout<<sum<<"	";
//       }
//     }
//     
//     for(int norm_x=0;norm_x<kernal.cols;norm_x++){
//       for(int norm_y=0;norm_y<kernal.rows;norm_y++){
// 	kernal.at<float>(norm_x,norm_y)=kernal.at<float>(norm_x,norm_y)/sum;
//       }
//     }
//        cout<<kernal<<endl;
    return true;
  }else{
    std::cout<<"invalid kernal for conv"<<std::endl;
    return false;
  }
  
}
//img padding in two mode: replicate OR zero
void conv::padding(const cv::Mat & source_img,cv::Mat & img_pad,string mod)
{
  //bool mod_select=mod.compare("replicate");
  //img_pad=cv::Mat::zeros(2*pad_x+source_img.rows,2*pad_y+source_img.cols,source_img.type());;
  //replicate mod
  if(mod.compare("replicate")==0){
    cout<<"mod replicate "<<endl;
    cv::Rect rect(pad_x,pad_y,source_img.cols,source_img.rows);
    source_img.copyTo(img_pad(rect));
//     cv::Rect rect_x_top=cv::Rect(0,0,source_img.cols,1);
//     cv::Rect rect_y_left=cv::Rect(0,0,1,source_img.rows);
//     cv::Rect rect_x_bot=cv::Rect(0,source_img.rows-1,source_img.cols,1);
//     cv::Rect rect_y_right=cv::Rect(source_img.cols-1,0,1,source_img.rows);
//     
//     cv:Mat pad_mat_x=cv::Mat::zeros(1,2*pad_y+source_img.cols,source_img.type());
//     cv:Mat pad_mat_y=cv::Mat::zeros(2*pad_x+source_img.rows,1,source_img.type());
//     source_img(rect_x_top).copyTo(pad_mat_x);
//     for(int i;i<pad_y;i++){
//       source_img(rect).copyTo(img_pad(re));
//     }
    
    //four corner while padding
//     for(int i=0;i<pad_y;i++){
//       for (int j=0;j<pad_x;j++){	
// 	img_pad.at<float>(i,j)=source_img.at<float>(0,0);
// 	img_pad.at<float>(i,j+pad_x+source_img.cols)=source_img.at<float>(0,source_img.cols-1);
// 	img_pad.at<float>(i+pad_y+source_img.rows,j)=source_img.at<float>(source_img.rows-1,0);
// 	img_pad.at<float>(i+pad_y+source_img.rows,j+pad_x+source_img.cols)=source_img.at<float>(source_img.rows-1,source_img.cols-1);
//       }
//       //top and bottom padding
//       for(int k=0;k<source_img.cols;k++){
// 	img_pad.at<float>(i,k+pad_x)=source_img.at<float>(0,k);
// 	img_pad.at<float>(i+pad_y+source_img.rows,k+pad_x)=source_img.at<float>(source_img.rows-1,k);
//       }
//     }
//     // left and right padding
//     for(int i=0;i<pad_x;i++){
//       for(int j=0;j<source_img.rows;j++){
// 	img_pad.at<float>(j+pad_y,i)=source_img.at<float>(j,0);
// 	img_pad.at<float>(j+pad_y,i+pad_x+source_img.cols)=source_img.at<float>(j,source_img.cols-1);
//       }
//     }
     for(int i=0;i<pad_y;i++){
      for (int j=0;j<pad_x;j++){	
	img_pad.at<uchar>(i,j)=source_img.at<uchar>(0,0);
	img_pad.at<uchar>(i,j+pad_x+source_img.cols)=source_img.at<uchar>(0,source_img.cols-1);
	img_pad.at<uchar>(i+pad_y+source_img.rows,j)=source_img.at<uchar>(source_img.rows-1,0);
	img_pad.at<uchar>(i+pad_y+source_img.rows,j+pad_x+source_img.cols)=source_img.at<uchar>(source_img.rows-1,source_img.cols-1);
      }
      //top and bottom padding
      for(int k=0;k<source_img.cols;k++){
	img_pad.at<uchar>(i,k+pad_x)=source_img.at<uchar>(0,k);
	img_pad.at<uchar>(i+pad_y+source_img.rows,k+pad_x)=source_img.at<uchar>(source_img.rows-1,k);
      }
    }
    // left and right padding
    for(int i=0;i<pad_x;i++){
      for(int j=0;j<source_img.rows;j++){
	img_pad.at<uchar>(j+pad_y,i)=source_img.at<uchar>(j,0);
	img_pad.at<uchar>(j+pad_y,i+pad_x+source_img.cols)=source_img.at<uchar>(j,source_img.cols-1);
      }
    }
   // cv::imshow("padding ",img_pad);
  }
  //zero(default mod)
  else{
    cout<<"mod zero "<<endl;
    cv::Rect rect(pad_x,pad_y,source_img.cols,source_img.rows);
    source_img.copyTo(img_pad(rect));
  }
}

void conv::convolute(const cv::Mat &image, cv::Mat &dst, string mod){

   /* if(load_kernal()){
        cout<<"kernal is empty!Please load the kernal first!"<<endl;return;
    }
*/
    cv::Mat complete_image=cv::Mat::zeros(2*pad_x+image.rows,2*pad_y+image.cols,image.type());
    padding(image,complete_image,mod);
    int channels=image.channels();
    if(channels==3){
        for(int chan=0;chan<channels;chan++){
            for(int i=0;i<dst.rows;i++){
                for(int j=0;j<dst.cols;j++){
                    compute_kernal(i,j,chan,complete_image,dst);
                }
            }
        }
   }
    if(channels==1){
        for(int i=0;i<dst.rows;i++){
            for(int j=0;j<dst.cols;j++){
                compute_kernal(i,j,0,complete_image,dst);
            }
        }
    }
}

void conv::compute_kernal(int i, int j,int chan,cv::Mat &complete_image, cv::Mat &dst){
    using namespace cv;
    if(complete_image.channels()==3){
      
        float sum=0;
        int bios_rows=i;
        int bios_cols=j;

        for(int curr_rows=0;curr_rows<kernal.rows;curr_rows++){
            for(int curr_cols=0;curr_cols<kernal.cols;curr_cols++){
                float a=kernal.at<float>(curr_rows,curr_cols)*complete_image.at<Vec3b>(curr_rows+bios_rows,curr_cols+bios_cols)[chan];
                sum+=a;
            }
        }
        dst.at<Vec3b>(i,j)[chan]=saturate_cast<uchar>(sum);
    }

    else{

        if(complete_image.channels()==1){
            float sum=0;
            int bios_rows=i;
            int bios_cols=j;

            for(int curr_rows=0;curr_rows<kernal.rows;curr_rows++){
                for(int curr_cols=0;curr_cols<kernal.cols;curr_cols++){
                    float a=kernal.at<float>(curr_rows,curr_cols)*complete_image.at<uchar>(curr_rows+bios_rows,curr_cols+bios_cols);
                    sum+=a;
                }
            }
            dst.at<uchar>(i,j)=saturate_cast<uchar>(sum);
        }
        else{
            cout<<"the type of image is not suitable!"<<endl;
	    return ;
        }
    }
}
cv::Mat conv::twodConv(const cv::Mat& img, const cv::Mat kernal,string mod)
{
  cv::Mat img_out=cv::Mat::zeros(img.rows,img.cols,img.type());
  load_kernal(kernal);
  convolute(img, img_out, mod);
  return img_out;
}

cv::Mat conv::gaussKernel(float sig, int m)
{
  float window_size=ceil(sig*3)*2+1;
  if(m<window_size&&m!=-1|m%2==0){
    cout<<"the value m is too small,bigger and odd is appreciated"<<endl;
    exit(0);
  }
  if(m==-1){
    m=window_size;
  }
  const double PI = 3.14159265358979323846;
  int center = m / 2;
  cv::Mat kernal(m, m, CV_32FC1);
  float s = 2 * sig*sig;
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < m; j++)
      {
	  int x = i - center, y=j - center;
	  kernal.ptr<float>(i)[j] = exp(-(x*x + y*y) / s) / (PI*s);
      }
  }
  float sum=0;
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < m; j++)
      {
	  
	  sum += kernal.ptr<float>(i)[j];
      }
  }
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < m; j++)
      {
	  
	  kernal.ptr<float>(i)[j] = kernal.ptr<float>(i)[j];
      }
  }
  return kernal;

}


