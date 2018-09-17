#include<bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<bits/stdc++.h>
#include "opencv2/highgui/highgui.hpp"
#include "Card.h"
#include "CardDetector.h"
#include "Classifier.h"
using namespace std;
using namespace cv;

int main() {
	Classifier cls;
	cv::Mat image = cv::imread("Capture.jpg");
	if (!image.data) {
		std::cout << "Image file not found\n";
		return 1;
	}
	CardDetector detector(image, 1000, 50000, 150);
	detector.imagePrePocessing();
	vector<Card> cards = detector.detectCards();
	for (int i = 0; i < cards.size(); i++){
		cards[i]._number = cls.findRank(cards[i].number);
		cards[i]._type = cls.findType(cards[i].type);
		cards[i].overlayText(detector.image);
	}
	for (int i = 0; i < cards.size(); i++){
		
		if (i > 10) break;
		string s;
		s += char('0' + i);
		//imshow("card", cards[i].img);
		//imshow("number", cards[i].number);
		//moveWindow("number", 0, 0);
		//imshow("type", cards[i].type);
	}
	cv::imshow("contours", detector.binaryImage);
	cv::moveWindow("Input Image", 0, 0);
	cv::imshow("Image", image);
	cv::moveWindow("Image", 500, 0);
	cv::waitKey(0);
	return 0;
}