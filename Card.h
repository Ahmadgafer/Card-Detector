#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include<vector>
using namespace std;
using namespace cv;

#pragma once
class Card
{
public:
	static const int cornerHigh = 85, cornerWidth = 35;
	int width, hight;
	Mat img, number, type;
	vector<Point> contour;
	double area;
	Point center;
	string _number, _type;
	void draw(Mat &);
	void overlayText(Mat &);
	void cropNumberType();
	void getMaxContour(Mat &);
	Card();
	Card(vector<Point> con, Mat image);
	~Card();
};


