#include <iostream>
#include <opencv2/opencv.hpp>
#include "plot.h"

using namespace cv;
using namespace std;

int PlotGraph(Mat & data) {
    
    //converting the Mat to CV_64F
    data.convertTo(data, CV_64F);
    Mat plot_result;
    
    Ptr<plot::Plot2d> plot = plot::Plot2d::create(data);
    plot->setPlotBackgroundColor(Scalar(50, 50, 50));
    plot->setPlotLineColor(Scalar(50, 50, 255));
    plot->render(plot_result);
    
    imshow("Graph", plot_result);
    waitKey();
    
    return 0;
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
