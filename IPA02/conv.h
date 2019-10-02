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
#include <opencv2/opencv.hpp>

using namespace std;
#ifndef CONV_H
#define CONV_H

class conv
{
public:
  conv();
  ~conv();
  bool load_kernal(cv::Mat kernel);
  void padding(const cv::Mat & source_img,cv::Mat & img_pad,string mod);
  void convolute(const cv::Mat &image, cv::Mat &dst, string mod);
  cv::Mat twodConv(const cv::Mat & img,const cv::Mat kernal);
  cv::Mat gaussKernel(float sig,int m=0);

private:
  void compute_kernal(int i, int j,int chan,cv::Mat &complete_image, cv::Mat &dst);
  
  cv::Mat kernal;
  int pad_x;
  int pad_y;
};

#endif // CONV_H
