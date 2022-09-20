//
//  MeanFilteringClass.hpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#ifndef MeanFilteringClass_hpp
#define MeanFilteringClass_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


bool arithMeanFilter(Mat& src, Mat& dst,int kernel);
bool geoMeanFilter(Mat& src, Mat& dst,int kernel);
bool harmonicMeanFilter(Mat& src, Mat& dst,int kernel);
bool weightedMeanFilter(Mat& src, Mat& dst,int kernel,int weight);
bool localNoiseFilterMean(Mat& src, Mat&dst, int kernel);
bool arithMeanFilter2(Mat& src, Mat& dst,int kernel);

#endif /* MeanFilteringClass_hpp */
