
//opencv
#include "opencv2/opencv.hpp"

//std
#include <iostream>
#include <cstdlib>

//

//main
int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	  int cam_id; //camera id . Associated to device number in /dev/videoX
	  cv::Scalar_<unsigned char> px_value; //pixel value (4-element vector)
	  int user_key; //user pressed key to quit
    cv::Vec3b pixel_intensity; //pixel RGB intensity
    cv::Vec3b pixel_intensity1; //pixel RGB intensity
    cv::Vec3b pixel_intensity2; //pixel RGB intensity
    cv::Vec3b pixel_intensity3; //pixel RGB intensity

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		   {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
    //Value of the central pixel BGR
     pixel_intensity = image.at<cv::Vec3b>(image.rows/2, image.cols/2);
     std::cout << "RGB: " 	<< (unsigned int)pixel_intensity[2] << ","
			                      << (unsigned int)pixel_intensity[1] << ","
			                      << (unsigned int)pixel_intensity[0] <<std::endl;
    // Change the color to red
    pixel_intensity[0] = 0;
		pixel_intensity[1] = 0;
		pixel_intensity[2] = 255;
    image.at<cv::Vec3b>(image.rows/2, image.cols/2) = pixel_intensity;


   // Line from y=o to central pixel (image.rows/2,image.cols/2) in red
   for(int y = 0; y < image.rows/2; y++ ) {
      image.at<cv::Vec3b>(y,image.cols/2 ) = pixel_intensity;
    }
  // Line from x=o to central pixel (image.rows/2,image.cols/2) in black
   for(int x = 0; x < image.cols/2; x++ ) {
      pixel_intensity2[0] = 0;
      pixel_intensity2[1] = 0;
      pixel_intensity2[2] = 0;
      image.at<cv::Vec3b>(image.rows/2, x) = pixel_intensity2;
    }
  // Line from the central pixel (image.rows/2,image.cols/2) to y =image.rows in green
    for(int y = image.rows/2; y < image.rows ; y++ ) {
      pixel_intensity1[0] = 0;
  		pixel_intensity1[1] = 255;
  		pixel_intensity1[2] = 0;
       image.at<cv::Vec3b>(y,image.cols/2 ) = pixel_intensity1;
     }
  // Line from the central pixel (image.rows/2,image.cols/2) to x =image.cols in blue
    for(int x = image.cols/2; x < image.cols ; x++ ) {
       pixel_intensity3[0] = 255;
       pixel_intensity3[1] = 0;
       pixel_intensity3[2] = 0;
       image.at<cv::Vec3b>(image.rows/2, x) = pixel_intensity3;
     }
        //show image in a window
        cv::imshow("Output Window", image);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }
}
