//
//  MeanFilteringClass.cpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#include "MeanFilteringClass.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


bool arithMeanFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int mean = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    mean += img_temp.at<uchar>(i + x, j + y);
                }
            }
            
            mean = mean / (kernel * kernel);
            final = round(mean);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
        }
    }
    
    
    return true;
}

bool arithMeanFilter2(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int mean = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    mean += img_temp.at<uchar>(i + x, j + y);
                }
            }
            
            mean = mean / (kernel * kernel);
            final = round(mean);
            if(src.at<uchar>(i-padding,j-padding)<final){
                dst.at<uchar>(i - padding, j - padding)=0;
            }
            else{
                dst.at<uchar>(i - padding, j - padding)=src.at<uchar>(i-padding,j-padding);
            }

        }
    }
    
    
    return true;
}




bool geoMeanFilter(Mat& src, Mat& dst,int kernel){
    
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    float mean = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 1);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            int count=0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    mean += log10(img_temp.at<uchar>(i + x, j + y));
                    count++;
                }
            }
            
            float res=mean/count;
            float antilog=pow(10,res);
            final = round(antilog);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
        }
    }
    
    return true;
}


bool weightedMeanFilter(Mat& src, Mat& dst,int kernel,int weight)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    int mean = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    if(i+x==i&&j+y==j){
                        mean += weight*(img_temp.at<uchar>(i + x, j + y));
                    }
                    else{
                        mean += img_temp.at<uchar>(i + x, j + y);
                    }
                }
            }
            
            mean = mean / (kernel * kernel);
            final = round(mean);
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
            int val=dst.at<uchar>(i - padding, j - padding);
            //cout<<val<<endl;
        }
    }
    
    return true;
}

bool harmonicMeanFilter(Mat& src, Mat& dst,int kernel)
{
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    float mean = 0.0;
    int final = 0;
    int imgRows, imgCols;
    cv::Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 1);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            int count=0;
            // loop over neighborhood
            bool zeroFound=false;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    if(img_temp.at<uchar>(i + x, j + y)==0){
                        zeroFound=true;
                    }
                    
                    mean += (float)1/img_temp.at<uchar>(i + x, j + y);
                    count++;
                }
            }
            //cout<<"mean: "<<mean<<endl;
            
            //cout<<"count: "<<count<<endl;;
            float harmonicMean;
            if(zeroFound){
                harmonicMean=0;
            }
            else{
                harmonicMean=(float)count/mean;
            }
            //cout<<"harm mean: "<<harmonicMean<<endl;
            
            final = harmonicMean;
            //cout<<"final "<<final<<endl;
            // cast result to uchar and set pixel in output image
            dst.at<uchar>(i - padding, j - padding) = (uchar)final;
        }
    }
    
    return true;
}

bool localNoiseFilterMean(Mat& src, Mat&dst, int kernel){
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //padding size
    int padding = (kernel - 1) / 2;
    //declare and initialize variables
    int mean = 0.0;
    int meanSquared=0.0;
    int final = 0;
    int count=0;
    int imgRows, imgCols;
    int noiseVariance=0;
    Mat img_temp;
    Mat localMean;
    Mat nVarOverLocalVar;
    imgRows = src.size().height;
    imgCols = src.size().width;
    int localVariance[imgRows][imgCols];
    
    //make a border around image with 0s
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 0);
    
    //initialize Mat and array objects
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    localMean=Mat::zeros(imgRows, imgCols, CV_8UC1);
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            localVariance[i][j]=0;
        }
    }
    
    
    // finding local mean
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            meanSquared=0.0;
            count=0;
            
            // loop over neighborhood to find mean
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    
                    mean +=img_temp.at<uchar>(i + x, j + y);
                    count++;
                    
                }
            }
            //local mean,put it in localmean mat at specific point:
            mean=mean/count;
            meanSquared=pow(mean,2);
            final = round(mean);
            //cout<<"Final mean value: "<<final<<endl;
            localMean.at<uchar>(i - padding, j - padding) = (uchar)final;
            
            //int localMeanVal=localMean.at<uchar>(i - padding, j - padding);
            //cout<<"Final local mean value: "<<localMeanVal<<endl;
            
            
            //average the local viariances
            mean=0.0;
            count=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    //square the val in each window
                    mean+=pow(img_temp.at<uchar>(i + x, j + y),2);
                    count++;
                }
            }
            int meanWinSq=mean/count;
            int lvariance=meanWinSq-meanSquared;
            final=round(lvariance);
            //cout<<"final variance val: "<<final<<endl;
            
            localVariance[i - padding][j - padding]=final;
            //cout<<"final local variance val: "<<localVarVal<<endl;
            
            
        }
    }
    
    //find avergae local variance
    count=0;
    mean=0;
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            mean+=localVariance[i][j];
            count++;
        }
    }
    noiseVariance=mean/count;
    //cout<<"Noise Variance: "<<noiseVariance<<endl;
    
    //check if average local variance is greater than local variance at specific point. If so, replace point with the average local variance
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            if(noiseVariance>localVariance[i][j]){
                localVariance[i][j]=noiseVariance;
            }
        }
    }
    
    //final image
    for(int i=0;i<imgRows;i++){
        for(int j=0;j<imgCols;j++){
            int origVal=src.at<uchar>(i,j);
            float noiseOverLocal=noiseVariance/(localVariance[i][j]);
            int localMeanVal=localMean.at<uchar>(i,j);
            int imgMinusLocalMean=origVal-localMeanVal;
            int final=origVal-(noiseOverLocal)*(imgMinusLocalMean);
            dst.at<uchar>(i,j)=(uchar)final;
        }
    }
    
    return true;
    
}
