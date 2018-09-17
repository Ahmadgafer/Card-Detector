#include "Card.h"


Card::Card()
{
}
Card::Card(vector<Point> con, Mat image){
	img = image;
	contour = con;
	center = (contour[0] + contour[1] + contour[2] + contour[3]) / 4.0;
	area = contourArea(contour);
	width = image.cols;
	cropNumberType();

}

Card::~Card()
{
}
void Card::draw(Mat &m){
	vector<vector<Point> > con; con.push_back(contour);
	cv::drawContours(m, con, 0, cv::Scalar(0, 0, 255), 2);
	for (int i = 0; i < 4; i++){
		circle(m, contour[i], 7, Scalar(200, 0, 0), -1);
	}
	circle(m, center, 7, Scalar(0, 255, 0), -1);
}
void Card::getMaxContour(Mat &m){
	vector<vector<Point> > con;
	cv::findContours(m, con, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	int mxId = 0, mx = -1;
	if (con.size() == 0)return;
	for (int i = 0; i < con.size(); i++){
		double area = contourArea(con[i]);
		if (area > mx){
			mx = area;
			mxId = i;
		}
	}
	m = Mat(m, boundingRect(con[mxId]));
}
void Card::cropNumberType(){
	Mat image = Mat(img, Rect(0, 0, cornerWidth, cornerHigh));

	// convert image to binary 
	cv::cvtColor(image, image, CV_BGR2GRAY);
	GaussianBlur(image, image, Size(3, 3), 0);
	int tr = (int)image.at<uchar>(5, 5) - 30;
	cv::threshold(image, image, tr, 255, CV_THRESH_BINARY_INV);
	
	int erosion_type = 0, erosion_size = 1;
	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	// extract number 
	number = Mat(image, Rect(0, 0, cornerWidth, 45));
	//erode(number, number, element);
	getMaxContour(number);
	resize(number, number, Size(100, 200));

	// extract type 
	type = Mat(image, Rect(0, 45, cornerWidth, cornerHigh - 45));
	erode(type, type, element);
	getMaxContour(type);
	resize(type,type, Size(100, 100));
}
void Card::overlayText(Mat &m){
	Point c = center;
	c.x -= 50;
	cv::putText(m,
		_number + " : " + _type,
		c, // Coordinates
		cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
		0.9, // Scale. 2.0 = 2x bigger
		cv::Scalar(0, 255, 255), // BGR Color
		2);// Line Thickness
}