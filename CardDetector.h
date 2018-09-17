#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<bits/stdc++.h>
#include "Card.h"
using namespace std;
using namespace cv;

#pragma once
class CardDetector
{
public:
	Mat image, binaryImage;
	int minArea, maxArea;
	int threshold;
	void imagePrePocessing();
	vector<Card> detectCards();
	void warpCard(Mat &card, vector<Point> &contour);
	
	CardDetector();
	CardDetector(Mat , int ,int ,int);
	~CardDetector();
};

