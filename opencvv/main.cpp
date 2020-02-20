#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int max_value_H = 355;
int low_H=2;
int high_H=max_value_H;
string window_name = "opencv Camera Feed";

static void on_hue_trackbar(int, void *)
{
  //low_H = max(high_H, low_H+1);
  setTrackbarPos("Low H", window_name, low_H);
}

int main(int argc, char* argv[])
{
 //Open the default video camera
 VideoCapture cap(0);
 SimpleBlobDetector::Params pDefaultBLOB;
 // This is default parameters for SimpleBlobDetector
 pDefaultBLOB.thresholdStep = 10;
 pDefaultBLOB.minThreshold = 10;
 pDefaultBLOB.maxThreshold = 220;
 pDefaultBLOB.minRepeatability = 2;
 pDefaultBLOB.minDistBetweenBlobs = 10;
 pDefaultBLOB.filterByColor = true;
 pDefaultBLOB.blobColor = 0;
 pDefaultBLOB.filterByArea = false;
 pDefaultBLOB.minArea = 25;
 pDefaultBLOB.maxArea = 5000;
 pDefaultBLOB.filterByCircularity = false;
 pDefaultBLOB.minCircularity = 0.9f;
 pDefaultBLOB.maxCircularity = (float)1e37;
 pDefaultBLOB.filterByInertia = false;
 pDefaultBLOB.minInertiaRatio = 0.1f;
 pDefaultBLOB.maxInertiaRatio = (float)1e37;
 pDefaultBLOB.filterByConvexity = true;
 pDefaultBLOB.minConvexity = 0.95f;
 pDefaultBLOB.maxConvexity = (float)1e37;
 Ptr<Feature2D> b;
 b = SimpleBlobDetector::create(pDefaultBLOB);
 // Color palette
 vector< Vec3b >  palette;
 for (int i = 0; i<65536; i++)
  {
    uchar c1 = (uchar)rand();
    uchar c2 = (uchar)rand();
    uchar c3 = (uchar)rand();
    palette.push_back(Vec3b(c1, c2, c3));
  }

 // if not success, exit program
 if (cap.isOpened() == false)
 {
  cout << "Cannot open the video camera" << endl;
  cin.get(); //wait for any key press
  return -1;
 }

 double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
 double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

 cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

 namedWindow(window_name); //create a window called "My Camera Feed"
 float y = 200;
 float x =100;
 uchar color1 ;
 int hueHigh = 100;
 int hueLow = 200;
 createTrackbar("Low H", window_name, &low_H, max_value_H, on_hue_trackbar);
 Mat frame;
 // main loop
 while (true)
 {
  bool bSuccess = cap.read(frame); // read a new frame from video
  Mat colour_seg;
  cvtColor(frame, frame, COLOR_BGR2HSV);
  inRange(frame, cv::Scalar(0, 255, 255), cv::Scalar(low_H, 255, 255), colour_seg);
  //Breaking the while loop if the frames cannot be captured
  if (bSuccess == false)
  {
   cout << "Video camera is disconnected" << endl;
   cin.get(); //Wait for any key press
   break;
  }
  // We can detect keypoint with detect method
  vector<KeyPoint>  keyImg;
  vector<Rect>  zone;
  vector<vector <Point> >  region;
  Mat     desc, result(dWidth, dHeight, CV_8UC3);
  if (b.dynamicCast<SimpleBlobDetector>().get())
  {
      Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();
      sbd->detect(colour_seg, keyImg, Mat());
      drawKeypoints(frame, keyImg, result);
      int i = 0;
      for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); ++k, ++i)
        circle(result, k->pt, (int)k->size, palette[i % 65536]);
  }
  // show original image
  //imshow("Original", frame);
  // draw circle
  circle(result, Point(100,75), 10, Scalar(low_H+20, 255, 255), FILLED, LINE_AA);
  circle(result, Point(100,100), 10, Scalar(low_H, 255, 255), FILLED, LINE_AA);
  circle(result, Point(100,125), 10, Scalar(low_H-20, 255, 255), FILLED, LINE_AA);
  //x+=1;

  cvtColor(result, result, COLOR_HSV2BGR);
  // Draw detected blobs as red circles.
  //show the frame in the created window
  imshow(window_name, result);

  //wait for for 10 ms until any key is pressed.
  //If the 'Esc' key is pressed, break the while loop.
  //If the any other key is pressed, continue the loop
  //If any key is not pressed withing 10 ms, continue the loop
  if (waitKey(10) == 27)
  {
   cout << "Esc key is pressed by user. Stoppig the video" << endl;
   break;
  }
 }
 return 0;
}
