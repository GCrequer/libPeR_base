/*!
 \file RationalPolynomial2PlumbBoCameraModelConversion.cpp
 \brief Example program to convert a PeR camera model to another
 \author Guillaume CARON
 \version 0.1
 \date July 2023
 */

#include <iostream>

#include <per/prPerspective.h>
#include <per/prCameraModelConvert.h>

/*!
 * \fn main()
 * \brief Main function of the sample program to convert a PeR camera model set of distorsion parameters to another
 *
 * Output the perspective camera model with distortions computed from another with more distortion parameters
 * TODO: load/save xml files
 *
 */
int main()
{
    // Perspective camera definition with rational polynomial model of distortions
    // Example of a camera calibrated with opencv: k1 k2 p1 p2 k3 k4 k5 k6
    // 0.39919957518577576, -2.5894720554351807, -1.5258635812642751e-06, -0.000308827351545915, 1.5280966758728027, 0.27556535601615906, -2.4022183418273926, 1.4482877254486084
    // K : [604.71728515625, 0.0, 640.8141479492188, 0.0, 604.6306762695312, 365.88763427734375, 0.0, 0.0, 1.0]
    /*
    double au = 604.71728515625;
    double av = 604.6306762695312;
    double u0 = 640.8141479492188;
    double v0 = 365.88763427734375;
    
    double k1 = 0.39919957518577576;
    double k2 = -2.5894720554351807;
    double k3 = 1.5280966758728027;
    double k4 = -1.5258635812642751e-06;
    double k5 = -0.000308827351545915;
    double k6 = 0.27556535601615906;
    double k7 = -2.4022183418273926;
    double k8 = 1.4482877254486084;
    */
    
    // Example of an Azure Kinect camera 
    double au = 967.548;
    double av = 967.409;
    double u0 = 1025.603;
    double v0 = 777.720;
    
    double k1 = 0.399;
    double k2 = -2.589;
    double k3 = 1.528;
    double k4 = -1.526e-6; // tangential 1
    double k5 = -3.088e-4; //tangential 2
    double k6 = 0.276;
    double k7 = -2.402;
    double k8 = 1.448;
    
    double FoV = 90; // degrees; horizontal
    
    prPerspective inperspcam(au, av, u0, v0, k1, k2, k3, k4, k5, k6, k7, k8);
    prPerspective outperspcam(au, av, u0, v0, k1, k2, k3, k4, k5, k6, k7, k8);

    std::cout << "The input camera is a " << inperspcam.getName() << " camera of intrinsic parameters " << std::endl;
    inperspcam.operator<<(std::cout);
    
    // Conversion of the equidistant fisheye to an omni camera
    double residual = prCameraModelConvert::convert_distortions(&inperspcam, &outperspcam, FoV);
    
    std::cout << "The ouput camera is a " << outperspcam.getName() << " camera of intrinsic parameters " << std::endl;
    outperspcam.operator<<(std::cout);
    
    std::cout << "An average error of " << residual << " pixel(s) has been made during the conversion" << std::endl;

    
	return 0;
}
