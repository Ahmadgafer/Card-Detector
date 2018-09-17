#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<vector>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;


#pragma once
class Classifier
{
	
public:
	string rank_name[13];
	string type_name[4];
	Mat rank[13];
	Mat type[4];
	string findRank(Mat &);
	string findType(Mat &);
	Classifier();
	~Classifier();
};

