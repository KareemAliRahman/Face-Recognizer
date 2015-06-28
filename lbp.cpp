#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <boost/python.hpp>
using namespace boost::python;

using namespace cv;
using namespace std;

/* load Image bu its title as greyScale and perform histogram
 * equalization
 * */
Mat loadAndPreprocessImage(string title){
    //cout << title << endl;
    Mat img = imread(title, CV_LOAD_IMAGE_GRAYSCALE );
    //debug
    //cout << "M = "<< endl << " "  << img << endl << endl;

    Mat equalized;
    equalizeHist( img, equalized);
    //namedWindow( "equalized_window",WINDOW_NORMAL); 
    //imshow("equalized_window", equalized);
    //waitKey(0);
    return equalized;
}

vector<unsigned int> lbp(string title)
{
    Mat I = loadAndPreprocessImage(title);
    vector<unsigned int> result(16,0);
    for(int i = 1; i<I.rows-1; ++i){
        for(int j = 1; j<I.cols-1; ++j){
            unsigned int pixelValue = I.at<uchar>(i,j);
            unsigned int newValue = (I.at<uchar>(i-1,j-1) > pixelValue)*pow(2,7);
            newValue += (I.at<uchar>(i-1,j) > pixelValue) * pow(2,6);
            newValue += (I.at<uchar>(i-1,j+1) > pixelValue) * pow(2,5);
            newValue += (I.at<uchar>(i, j+1) > pixelValue) * pow(2,4);
            newValue += (I.at<uchar>(i+1, j+1) > pixelValue) * pow(2,3);
            newValue += (I.at<uchar>(i+1, j) > pixelValue) * pow(2,2);
            newValue += (I.at<uchar>(i+1,j-1) > pixelValue) * 2;
            newValue += (I.at<uchar>(i, j-1) > pixelValue);
            result[newValue/16]++;
        } 
    }
    //for(int i=0; i<result.size(); ++i)
    //   std::cout << result[i] << ' ';
    return result;
}

list lbp_wrapper(string title){
    vector<unsigned int> result = lbp(title);
    boost::python::list resultList;
    vector<unsigned int>::iterator iter;
    for(iter= result.begin(); iter!=result.end(); ++iter){
        resultList.append(*iter);
    }
    return resultList;
}

// wrapper
BOOST_PYTHON_MODULE(lbp)
{
    def("loadAndPreprocessImage", loadAndPreprocessImage);
    def("lbp", &lbp_wrapper);
}
