#include "CardDetector.h"


CardDetector::CardDetector()
{
}
CardDetector::CardDetector(Mat img, int m1, int m2, int t){
	image = img;
	minArea = m1;
	maxArea = m2;
	threshold = t;
}
void CardDetector::imagePrePocessing(){
	cv::cvtColor(image, binaryImage, CV_BGR2GRAY);
	//cv::medianBlur(image, image, 3);
	GaussianBlur(binaryImage, binaryImage, Size(3, 3), 0);
	cv::threshold(binaryImage, binaryImage, threshold, 255, CV_THRESH_BINARY);
}
void CardDetector::warpCard(Mat &card, vector<Point> &contour){
	Point2f src[4], dist[4];
	int w = 200, h = 300;
	dist[0].x = 0; dist[0].y = 0;
	dist[3].x = w - 1; dist[3].y = 0;
	dist[2].x = w - 1; dist[2].y = h - 1;
	dist[1].x = 0; dist[1].y = h - 1;
	Point2f cen = (contour[0] + contour[1] + contour[2] + contour[3]) / 4.0;
	//cout << cen.x << " " << cen.y << endl;
	vector<int>d;
	for (int i = 0; i < 4; i++){
		//cout << contour[i].x << " " << contour[i].y << " : " << i << endl;
		d.push_back((contour[i].x - contour[(i + 1) % 4].x)*(contour[i].x - contour[(i + 1) % 4].x) + (contour[i].y - contour[(i + 1) % 4].y)*(contour[i].y - contour[(i + 1) % 4].y));
	}
	int st = 0;
	if (d[0] < d[1]) st = 1;
	for (int i = 0; i < 4; i++){
		int j = (i + st) % 4;
		src[i].x = contour[j].x;
		src[i].y = contour[j].y;
		//cout << contour[j].x << " " << contour[j].y << " : " << j << endl;
	}
	Mat tr = getPerspectiveTransform(src, dist);
	warpPerspective(image, card, tr, Size(w, h));
	//imshow("card", card);
}
vector<Card> CardDetector::detectCards(){
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(binaryImage, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	cv::cvtColor(binaryImage, binaryImage, CV_GRAY2RGB);
	vector<Card> cards;
	for (int idx = 0; idx < contours.size(); idx++) {
		double area = cv::contourArea(contours[idx]);
		if (area < minArea || area > maxArea)
			continue;
		approxPolyDP(contours[idx], contours[idx], cv::arcLength(contours[idx], true) * 0.01, true);
		if (contours[idx].size() != 4)
			continue;
		

		Mat temp;
		warpCard(temp , contours[idx]);
		cards.push_back(Card(contours[idx], temp));
		cards.back().draw(binaryImage);
		//cout << fixed << setprecision(2) << area << endl;
		//cout << contours[idx].size() << endl;
	}
	return cards;
}
CardDetector::~CardDetector()
{
}
