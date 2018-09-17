#include "Classifier.h"


Classifier::Classifier()
{
	string r[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string t[4] = { "Diamonds", "Hearts", "Clubs", "Spades" };
	for (int i = 0; i < 13; i++){
		rank_name[i] = r[i];
		rank[i] = imread("cards/" + rank_name[i] + ".jpg");
		cv::cvtColor(rank[i], rank[i], CV_BGR2GRAY);
		cv::threshold(rank[i], rank[i], 128, 255, CV_THRESH_BINARY);
		resize(rank[i], rank[i], Size(100, 200));
	}
	for (int i = 0; i < 4; i++){
		type_name[i] = t[i];
		type[i] = imread("cards/" + type_name[i] + ".jpg");
		cv::cvtColor(type[i], type[i], CV_BGR2GRAY);
		resize(type[i], type[i], Size(100, 100));
	}

}
string Classifier::findRank(Mat &m){
	int maxMatch = -1;
	string result;
	for (int i = 0; i < 13; i++){
		Mat temp;
		vector<Point> pnts;
		bitwise_xor(rank[i], m, temp);
		findNonZero(temp, pnts);
		int match = pnts.size() * 100 / (temp.rows*temp.cols);
		match = 100 - match;
		if (maxMatch < match){
			result = rank_name[i];
			maxMatch = match;
		}
	}
	if (maxMatch < 25){
		result = "Unknown";
	}
	return result;
}

string Classifier::findType(Mat &m){
	int maxMatch = -1;
	string result;
	for (int i = 0; i < 4; i++){
		Mat temp;
		vector<Point> pnts;
		bitwise_xor(type[i], m, temp);
		findNonZero(temp, pnts);
		int match = pnts.size() * 100 / (temp.rows*temp.cols);
		match = 100 - match;
		if (maxMatch < match){
			result = type_name[i];
			maxMatch = match;
		}
	}
	if (maxMatch < 25){
		result = "Unknown";
	}
	return result;
}
Classifier::~Classifier()
{
}
