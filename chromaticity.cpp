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
    
    static double cie_colour_match[81][3] = {
        {0.0014,0.0000,0.0065}, {0.0022,0.0001,0.0105}, {0.0042,0.0001,0.0201},
        {0.0076,0.0002,0.0362}, {0.0143,0.0004,0.0679}, {0.0232,0.0006,0.1102},
        {0.0435,0.0012,0.2074}, {0.0776,0.0022,0.3713}, {0.1344,0.0040,0.6456},
        {0.2148,0.0073,1.0391}, {0.2839,0.0116,1.3856}, {0.3285,0.0168,1.6230},
        {0.3483,0.0230,1.7471}, {0.3481,0.0298,1.7826}, {0.3362,0.0380,1.7721},
        {0.3187,0.0480,1.7441}, {0.2908,0.0600,1.6692}, {0.2511,0.0739,1.5281},
        {0.1954,0.0910,1.2876}, {0.1421,0.1126,1.0419}, {0.0956,0.1390,0.8130},
        {0.0580,0.1693,0.6162}, {0.0320,0.2080,0.4652}, {0.0147,0.2586,0.3533},
        {0.0049,0.3230,0.2720}, {0.0024,0.4073,0.2123}, {0.0093,0.5030,0.1582},
        {0.0291,0.6082,0.1117}, {0.0633,0.7100,0.0782}, {0.1096,0.7932,0.0573},
        {0.1655,0.8620,0.0422}, {0.2257,0.9149,0.0298}, {0.2904,0.9540,0.0203},
        {0.3597,0.9803,0.0134}, {0.4334,0.9950,0.0087}, {0.5121,1.0000,0.0057},
        {0.5945,0.9950,0.0039}, {0.6784,0.9786,0.0027}, {0.7621,0.9520,0.0021},
        {0.8425,0.9154,0.0018}, {0.9163,0.8700,0.0017}, {0.9786,0.8163,0.0014},
        {1.0263,0.7570,0.0011}, {1.0567,0.6949,0.0010}, {1.0622,0.6310,0.0008},
        {1.0456,0.5668,0.0006}, {1.0026,0.5030,0.0003}, {0.9384,0.4412,0.0002},
        {0.8544,0.3810,0.0002}, {0.7514,0.3210,0.0001}, {0.6424,0.2650,0.0000},
        {0.5419,0.2170,0.0000}, {0.4479,0.1750,0.0000}, {0.3608,0.1382,0.0000},
        {0.2835,0.1070,0.0000}, {0.2187,0.0816,0.0000}, {0.1649,0.0610,0.0000},
        {0.1212,0.0446,0.0000}, {0.0874,0.0320,0.0000}, {0.0636,0.0232,0.0000},
        {0.0468,0.0170,0.0000}, {0.0329,0.0119,0.0000}, {0.0227,0.0082,0.0000},
        {0.0158,0.0057,0.0000}, {0.0114,0.0041,0.0000}, {0.0081,0.0029,0.0000},
        {0.0058,0.0021,0.0000}, {0.0041,0.0015,0.0000}, {0.0029,0.0010,0.0000},
        {0.0020,0.0007,0.0000}, {0.0014,0.0005,0.0000}, {0.0010,0.0004,0.0000},
        {0.0007,0.0002,0.0000}, {0.0005,0.0002,0.0000}, {0.0003,0.0001,0.0000},
        {0.0002,0.0001,0.0000}, {0.0002,0.0001,0.0000}, {0.0001,0.0000,0.0000},
        {0.0001,0.0000,0.0000}, {0.0001,0.0000,0.0000}, {0.0000,0.0000,0.0000}
    };
    
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
    
    double t, x, y, z, r, g, b;
    struct colourSystem *cs = &SMPTEsystem;
//
//    Mat testcolor = imread("parrot.png", IMREAD_COLOR);
    //FOR WINDOWS --> CV_LOAD_IMAGE_COLOR);
//
//    int rows = testcolor.rows;
//    int cols = testcolor.cols;

	//CVD Simulation
//    Mat protanimg(rows, cols, CV_8UC3);
//    Mat deutanimg(rows, cols, CV_8UC3);
//
//    deuteranopia1(testcolor, protanimg, rows, cols);
//    imwrite("protan.jpg", protanimg);

        
        printf("Wavelength        x      y      z       R     G     B\n");
        printf("-----------    ------ ------ ------   ----- ----- -----\n");
    
        for (int wave = 380; wave <= 780; wave += 5)
        {
            double wavelength = wave;
            spectrum_to_xyz(wave, &x, &y, &z);
            xyz_to_rgb(cs, x, y, z, &r, &g, &b);
            printf("  %5.0f nm      %.4f %.4f %.4f   ", wave, x, y, z);
            if (constrain_rgb(&r, &g, &b)) {
                norm_rgb(&r, &g, &b);
                printf("%.3f %.3f %.3f (Approximation)\n", r, g, b);
            } else {
                norm_rgb(&r, &g, &b);
                printf("%.3f %.3f %.3f\n", r, g, b);
            }
        }
    
	return(0);
}
