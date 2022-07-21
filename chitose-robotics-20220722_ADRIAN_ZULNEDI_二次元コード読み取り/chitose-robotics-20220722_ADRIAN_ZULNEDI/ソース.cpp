#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <vector>
#include <thread>

using namespace cv;
using namespace std;

// global variables
VideoCapture inputVideo;
bool isTerminated = false;

// main process thread
void arucoThread() {
    // Prepare 6x6 aruco dictionary
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);

    cout << "---------------------------------------" << endl;
    cout << "marker detection ready." << endl;
    cout << "input 'exit' to terminate this program." << endl;
    cout << "---------------------------------------" << endl;

    // main loop
    while (inputVideo.grab() && !isTerminated) {
        Mat originalImage;
        inputVideo.retrieve(originalImage);

        // marker detection
        vector<int> ids;
        vector<vector<Point2f>> corners;
        aruco::detectMarkers(originalImage, dictionary, corners, ids);

        // if markers were detected
        if (ids.size() > 0) {
            // show ids in ascending order
            sort(ids.begin(), ids.end());
            cout << "detected ids: ";
            for (auto&& id : ids) {
                cout << id << " ";
            }
            cout << endl;
        }
    }
    return;
}

// key waiting thread
void keyThread() {
    string input;
    while (!isTerminated) {
        cin >> input;
        if (input == "exit") {
            isTerminated = true;
        }
    }
    return;
}

int main() {
    // Open camera device
    inputVideo.open(0);
    if (!inputVideo.isOpened()) {
        cout << "Error: Failed to open input device" << endl;
        return -1;
    }

    // create threads (for terminating program by input "exit")
    thread t1(arucoThread);
    thread t2(keyThread);
    t1.join();
    t2.join();

    return 0;
}