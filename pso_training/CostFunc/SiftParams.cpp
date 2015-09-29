#include "SiftParams.h"

const int SiftParams::dimension_of_freedom = 8;

std::vector<std::pair<double, double> > SiftParams::paramRange = {
		{ 3.0, 100.0 }, // alpha
		{ 3.0, 100.0 }, // beta
		{ 0.0, 1.0 },   // tau
		{ 0.0, 20.0 }, // Nr
		{ 0.0, 1.0 },   // threshold
		{ 0.0, 0.15 },   // responseThresholdx
		{ 0.0, 0.15 },   // responseThresholdy
		{ 0.0, 1.0 }    // rectangleThreshold
};   

SiftParams::SiftParams(double alpha,double beta, double tau,double  Nr,
                       double threshold,double  responseThresholdx,double responseThresholdy,double  rectangleThreshold)
{
    params.push_back(alpha);
    params.push_back(beta);
    params.push_back(tau);
    params.push_back(Nr);
    params.push_back(threshold);
    params.push_back(responseThresholdx);
    params.push_back(responseThresholdy);
    params.push_back(rectangleThreshold);
}
