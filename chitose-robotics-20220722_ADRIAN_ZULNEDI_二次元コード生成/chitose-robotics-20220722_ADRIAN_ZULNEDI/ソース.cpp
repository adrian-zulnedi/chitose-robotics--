// 二次元コード生成プログラム

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/aruco.hpp"
#include "opencv2/calib3d.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void creatArucoMarkers() {
	Mat outputMarker;

	Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_6X6_100);

	for (int i = 0; i < 10; i++) {

		aruco::drawMarker(markerDictionary, i, 500, outputMarker, 1);
		ostringstream convert;
		string imageName = "6x6Marker_";
		convert << imageName << i << ".jpg";
		imwrite(convert.str(), outputMarker);

	}
}

int main(int argv, char** argc) {
	creatArucoMarkers();
}