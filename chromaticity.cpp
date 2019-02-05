#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;


void RGBtoXYZ(const Mat &testcolor, Mat &toXYZ, int rows, int cols)
{
	for (int i = 0; i < testcolor.rows; i++) {
		for (int j = 0; j < testcolor.cols; j++) {

			float R = pow(testcolor.at<Vec3b>(i, j)[2], 2.2);
			float G = pow(testcolor.at<Vec3b>(i, j)[1], 2.2);
			float B = pow(testcolor.at<Vec3b>(i, j)[0], 2.2);

			float X =	(0.412453 * R) + (0.357580 * G) + (0.180423 * B);
			float Y =	(0.212671 * R) + (0.715160 * G) + (0.072169 * B);
			float Z =	(0.019334 * R) + (0.119193 * G) + (0.950227 * B);

			//normalization
            //float x = X/(X+Y+Z);
            //float y = Y/(X+Y+Z);
            //float z = Z/(X+Y+Z);

			float R1 = (  3.240479 * X) + ( −1.53715  * Y) + ( −0.498535 * Z);
			float G1 = ( −0.969256 * X) + (  1.875991 * Y) + (  0.041556 * Z);
			float B1 = (  0.055648 * X) + ( −0.204043 * Y) + (  1.057311 * Z);

			toXYZ.at<Vec3b>(i, j)[2] = pow(R1, (1.0 / 2.2));
			toXYZ.at<Vec3b>(i, j)[1] = pow(G1, (1.0 / 2.2));
			toXYZ.at<Vec3b>(i, j)[0] = pow(B1, (1.0 / 2.2));
		}
	}
}

void WavelengthtoXYZ(double (*spec_intens)(double wavelength), double *x, double *y, double *z)
{
    double wave, X = 0, Y = 0, Z = 0, XYZ;
    
    color_match[(wave - 380) / 5][0] = xBar
    color_match[(wave - 380) / 5][1] = yBar
    color_match[(wave - 380) / 5][2] = zBar
    
    for (int i = 0, wave = 380; wave <= 780; i++, wave += 5) {
        double Me;
        
        Me = (*spec_intens)(wave);
        X += Me * color_match[i][0];
        Y += Me * color_match[i][1];
        Z += Me * color_match[i][2];
    }
    
    XYZ = (X+Y+Z);
    *x  = X / XYZ;
    *y  = Y / XYZ;
    *z  = Z / XYZ;
    
}

void deuteranopia1(const Mat &testcolor, Mat &deutan, int rows, int cols)
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
			float m =  0.4942 * L + 0 * M + 1.2483 * S;
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





int main(int argv, char** argc){
	Mat testcolor = imread("parrot.png", IMREAD_COLOR);
    //FOR WINDOWS --> CV_LOAD_IMAGE_COLOR);
    
	int rows = testcolor.rows;
	int cols = testcolor.cols;

	//CVD Simulation
	Mat protanimg(rows, cols, CV_8UC3);
	Mat deutanimg(rows, cols, CV_8UC3);

	deuteranopia1(testcolor, protanimg, rows, cols);

	imwrite("protan.jpg", protanimg);


	return(0);
}
