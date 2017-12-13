#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <highgui.h>
//#include "greyscaling.h"
//#include "binary.h"
//#include "histogram.h"

using namespace cv; 
using namespace std;

Mat outline(Mat img,int thresh)
{  
	Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));

	int r=0,c=0;
    for (r=0;r<img.rows;r++)
    {
    	for(c=0;c<img.cols;c++)
    	{
    		/*if (r==0||c==0||r==img.rows-1||c==img.cols-1)
    		{
    			img2.at<uchar>(r,c)=255;  not neccesary ,only perfection
    			continue;
    		}*/
    		int m=0,n=255;
    		for (int k=r-1;k<=r+1;k++)
    		{
    			for(int l=c-1;l<=c+1;l++)
    			{
    				if ((int)img.at<uchar>(k,l)>m)
    					m=(int)img.at<uchar>(k,l);
    				if ((int)img.at<uchar>(k,l)<n)
    					n=(int)img.at<uchar>(k,l);
    			}
    		}

    		if ((m-n)>thresh)
    			img2.at<uchar>(r,c)=255;
    	}
    }
    return img2;
}

int main(int argc,char**argv)
{
	Mat img;
	int t=0,u=0,l=0;
	img=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("my window",CV_WINDOW_NORMAL);
	namedWindow("canny",CV_WINDOW_NORMAL);
	createTrackbar("threshold","my window",&t,255);
	createTrackbar("upper","canny",&u,255);
	createTrackbar("lower","canny",&l,255);

	while(1)
	{
		Mat img2=outline(img,t);
		imshow("my window",img2);
		Mat img3(img.rows,img.cols,CV_8UC1);
		Canny(img,img3,l,u);
		imshow("canny",img3);
		char a=waitKey(33);
	}

	return 0;
}