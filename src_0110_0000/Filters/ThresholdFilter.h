#ifndef THRESHOLDFILTER_H
#define THRESHOLDFILTER_H

#include "ImageAbstractFilter.h"

class ThresholdFilter : public ImageAbstractFilter
{

public :
	enum OperationType {THRESH_BINARY, THRESH_BINARY_INV, THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV, THRESH_INTERVAL};
	// THRESH_BINARY : maxVal if pixelVal > threshVal and 0 otherwise
	// THRESH_BINARY_INV : 0 if pixelVal > threshVal and maxVal otherwise
	// THRESH_TRUNC : threshVal if pixelVal > threshVal and pixelVal otherwise
	// THRESH_TOZERO : pixelVal if pixelVal > threshVal and 0 otherwise
	// THRESH_TOZERO_INV : 0 if pixelVal > threshVal and pixelVal otherwise
	// THRESH_INTERVAL : threshVal if pixelVal is in the interval and 0 otherwise
	

	ThresholdFilter(OperationType t=THRESH_BINARY, double threshval = 20., double maxval=255., double interv = 20){
		type = t;
		maxVal = maxval;
		threshVal = threshval;
		interval = interv;
	}


	~ThresholdFilter(){}
	inline void ApplyFilter(PipelineInput & input, PipelineBuffer * buffer);

protected:
	OperationType type;
	double threshVal;
	double maxVal;
	double interval;
};


inline void ThresholdFilter::ApplyFilter(PipelineInput & input, PipelineBuffer * buffer)
{
	Mat img = buffer->getOutputImage(input.getChannelNumber());
	if (img.channels() == 3){
		cvtColor(img,img,CV_BGR2GRAY);		   
	}

	if (type == THRESH_BINARY)
		threshold(img,img,threshVal,maxVal,CV_THRESH_BINARY);
	else if (type == THRESH_BINARY_INV)
		threshold(img,img,threshVal,maxVal,CV_THRESH_BINARY_INV);
	else if (type == THRESH_TRUNC)
		threshold(img,img,threshVal,maxVal,CV_THRESH_TRUNC);
	else if (type == THRESH_TOZERO)
		threshold(img,img,threshVal,maxVal,CV_THRESH_TOZERO);
	else if (type == THRESH_TOZERO_INV)
		threshold(img,img,threshVal,maxVal,CV_THRESH_TOZERO_INV);
	else if (type == THRESH_INTERVAL){
		Mat img2, img3; 
		threshold(img, img2, threshVal, 1.0, CV_THRESH_BINARY); // 1.0 : pixVal > threshVal
		threshold(img, img, threshVal + interval, 1.0, CV_THRESH_BINARY_INV); // 1.0 : pixVal < threshVal + interval
		multiply(img,img2,img,maxVal);
	}

	//return:
	buffer->setOutputImages(img, input.getChannelNumber());

}


#endif