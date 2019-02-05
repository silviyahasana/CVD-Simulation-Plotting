#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

const float toLMS[3][3] = {
	{17.8824, 43.5161, 4.1194}, 
	{ 3.4557, 27.1554, 3.8671},
	{ 0.0300,  0.1843, 1.4671}
};

const float toProtan[3][3] = {
	{0, 2.0234, -2.5258}, 
	{0,      1,       0},
	{0,      0,       1}
};

const float toDeutan[3][3] = {
	{      1,       0,      0}, 
	{ 0.4942,       0, 1.2483},
	{      0,       0,      1}
};

const float toRGB[3][3] = {
	{  0.0809, -0.1305,  0.1167}, 
	{ -0.0102,  0.0540, -0.1136},
	{ -0.0004, -0.0041,  0.6935}
};

//======================================================================================
// Simulation 1 : Jinmi Lee, Wellington Pinheiro dos Santos
// An Adaptive Fuzzy-Based System to Simulate, Quantify, and Compensate Color Blindness
// Based on Dalton.
// RGB --> LMS --> RGB
//======================================================================================

void dalton_protanopia(const Mat &testcolor, Mat &protan, int rows, int cols)
{
	for (int i = 0; i < testcolor.rows; i++) {
		for (int j = 0; j < testcolor.cols; j++) {

			float R = pow(testcolor.at<Vec3b>(i, j)[2], 2.2);
			float G = pow(testcolor.at<Vec3b>(i, j)[1], 2.2);
			float B = pow(testcolor.at<Vec3b>(i, j)[0], 2.2);

			float L =	(17.8824 * R) + (43.5161 * G) + ( 4.1194 * B) ;
			float M =	( 3.4557 * R) + (27.1554 * G) + ( 3.8671 * B) ;
			float S =	( 0.0300 * R) + ( 0.1843 * G) + ( 1.4671 * B) ;

            
			//protan transformation
			float l = 0 * L + 2.0234 * M + -2.5258 * S;
			float m = 0 * L +      1 * M +       0 * S;
			float s = 0 * L +      0 * M +       1 * S;

			float R1 = (  0.0809 * l) + ( -0.1305 * m) + (  0.1167 * s);
			float G1 = ( -0.0102 * l) + (  0.0540 * m) + ( -0.1136 * s);		
			float B1 = ( -0.0004 * l) + ( -0.0041 * m) + (  0.6935 * s);	

			protan.at<Vec3b>(i, j)[2] = pow(R1, (1.0 / 2.2));
			protan.at<Vec3b>(i, j)[1] = pow(G1, (1.0 / 2.2));
			protan.at<Vec3b>(i, j)[0] = pow(B1, (1.0 / 2.2));

		}
	}
}


void dalton_deuteranopia(const Mat &testcolor, Mat &deutan, int rows, int cols)
{
	for (int i = 0; i < testcolor.rows; i++) {
		for (int j = 0; j < testcolor.cols; j++) {

			float R = pow(testcolor.at<Vec3b>(i, j)[2], 2.2);
			float G = pow(testcolor.at<Vec3b>(i, j)[1], 2.2);
			float B = pow(testcolor.at<Vec3b>(i, j)[0], 2.2);

			float L =	(17.8824 * R) + (43.5161 * G) + ( 4.1194 * B) ;
			float M =	( 3.4557 * R) + (27.1554 * G) + ( 3.8671 * B) ;
			float S =	( 0.0300 * R) + ( 0.1843 * G) + ( 1.4671 * B) ;

			//deutan transformation
			float l =      1 * L + 0 * M +      0 * S;
			float m = 0.4942 * L + 0 * M + 1.2483 * S;
			float s =      0 * L + 0 * M +      1 * S;


			float R1 = (  0.0809 * l) + ( -0.1305 * m) + (  0.1167 * s);
			float G1 = ( -0.0102 * l) + (  0.0540 * m) + ( -0.1136 * s);		
			float B1 = ( -0.0004 * l) + ( -0.0041 * m) + (  0.6935 * s);	

			deutan.at<Vec3b>(i, j)[2] = pow(R1, (1.0 / 2.2));
			deutan.at<Vec3b>(i, j)[1] = pow(G1, (1.0 / 2.2));
			deutan.at<Vec3b>(i, j)[0] = pow(B1, (1.0 / 2.2));
		}
	}
}

//======================================================================================
// Simulation 2 : Brettel, Viénot, Mollon
// Digital Video Colourmaps for Checking the Legibility of Displays by Dichromats
// RGB --> LMS --> XYZ --> RGB
//======================================================================================

void bvm_protanopia(const Mat &testcolor, Mat &protan, int rows, int cols)
{
	for (int i = 0; i < testcolor.rows; i++) {
		for (int j = 0; j < testcolor.cols; j++) {

			float R = pow(testcolor.at<Vec3b>(i, j)[2], 2.2);
			float G = pow(testcolor.at<Vec3b>(i, j)[1], 2.2);
			float B = pow(testcolor.at<Vec3b>(i, j)[0], 2.2);

			float X =	(40.9568  * R) + (35.5041  * G) + (17.9167  * B);
			float Y =	(21.3389  * R) + (70.6743  * G) + ( 7.98680 * B);
			float Z =	( 1.86297 * R) + (11.4620  * G) + (91.2367  * B);

			float L = ( 0.15514 * X) + (0.54312 * Y) + (-0.03286 * Z);
			float M = (-0.15514 * X) + (0.45684 * Y) + ( 0.03286 * Z);
			float S = (       0 * X) + (      0 * Y) + ( 0.01608 * Z);

			//protan transformation
			float l = 0 * L + 2.02344 * M + -2.52581 * S;
			float m = 0 * L +       1 * M +        0 * S;
			float s = 0 * L +       0 * M +        1 * S;


			float R1 = (  0.080944    * l) + ( -0.130504   * m) + (  0.116721 * s);
			float G1 = ( -0.0102485   * l) + (  0.0540194  * m) + ( -0.113615 * s);		
			float B1 = ( -0.000365294 * l) + ( -0.00412163 * m) + (  0.693513 * s);		


			protan.at<Vec3b>(i, j)[2] = pow(R1, (1.0 / 2.2));
			protan.at<Vec3b>(i, j)[1] = pow(G1, (1.0 / 2.2));
			protan.at<Vec3b>(i, j)[0] = pow(B1, (1.0 / 2.2));

		}
	}
}

void bvm_deuteranopia(const Mat &testcolor, Mat &deutan, int rows, int cols)
{
	for (int i = 0; i < testcolor.rows; i++) {
		for (int j = 0; j < testcolor.cols; j++) {

			float R = pow(testcolor.at<Vec3b>(i, j)[2], 2.2);
			float G = pow(testcolor.at<Vec3b>(i, j)[1], 2.2);
			float B = pow(testcolor.at<Vec3b>(i, j)[0], 2.2);

			float X =	(40.9568  * R) + (35.5041  * G) + (17.9167  * B);
			float Y =	(21.3389  * R) + (70.6743  * G) + ( 7.98680 * B);
			float Z =	( 1.86297 * R) + (11.4620  * G) + (91.2367  * B);

			float L = ( 0.15514 * X) + (0.54312 * Y) + (-0.03286 * Z);
			float M = (-0.15514 * X) + (0.45684 * Y) + ( 0.03286 * Z);
			float S = (       0 * X) + (      0 * Y) + ( 0.01608 * Z);

			//deutan transformation
			float l =      1 * L + 0 * M +      0 * S;
			float m = 0.4942 * L + 0 * M + 1.2483 * S;
			float s =      0 * L + 0 * M +      1 * S;


			float R1 = (  0.080944    * l) + ( -0.130504   * m) + (  0.116721 * s);
			float G1 = ( -0.0102485   * l) + (  0.0540194  * m) + ( -0.113615 * s);		
			float B1 = ( -0.000365294 * l) + ( -0.00412163 * m) + (  0.693513 * s);		


			deutan.at<Vec3b>(i, j)[2] = pow(R1, (1.0 / 2.2));
			deutan.at<Vec3b>(i, j)[1] = pow(G1, (1.0 / 2.2));
			deutan.at<Vec3b>(i, j)[0] = pow(B1, (1.0 / 2.2));

		}
	}
}

int main(int argv, char** argc){
	Mat testcolor = imread("parrot.png", IMREAD_COLOR);
    //FOR WINDOWS --> CV_LOAD_IMAGE_COLOR);
    
	int rows = testcolor.rows;
	int cols = testcolor.cols;

	//CVD Simulation
	Mat protanimg(rows, cols, CV_8UC3);
	Mat deutanimg(rows, cols, CV_8UC3);

	dalton_protanopia(testcolor, protanimg, rows, cols);
    dalton_deuteranopia(testcolor, deutanimg, rows, cols);
	
	imwrite("dalton_protan.jpg", protanimg);
    imwrite("dalton_deutan.jpg", deutanimg);


	//cvtColor(testcolor, testcolor, COLOR_BGR2HSV);
	/**vector<Mat> channels;
	split(testcolor, channels);
	namedWindow("H Channel", WINDOW_AUTOSIZE);
	imshow("H Channel", channels[0]);
	namedWindow("S Channel", WINDOW_AUTOSIZE);
	imshow("S Channel", channels[1]);
	namedWindow("V Channel", WINDOW_AUTOSIZE);
	imshow("V Channel", channels[2]);

	namedWindow("HSV Image (all channels)", WINDOW_AUTOSIZE);
	imshow("HSV Image (all channels)", testcolor); **/ 

	return(0);
}
