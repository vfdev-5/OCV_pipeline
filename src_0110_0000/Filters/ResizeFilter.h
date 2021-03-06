#pragma once

#include "ImageAbstractFilter.h"

class ResizeFilter : public ImageAbstractFilter
{
	
	int factor; 
	int interpolation;

public:
	ResizeFilter(int fact, int interp = INTER_LINEAR) {factor=fact; interpolation = interp;};
	~ResizeFilter(){};
	inline Mat & ApplyFilter(Mat & image);
	inline void ApplyFilter(PipelineInput & input, PipelineBuffer * buffer);
};



inline Mat & ResizeFilter::ApplyFilter(Mat & inputImage)
{
	
	resize(inputImage,inputImage,Size(inputImage.cols*factor,inputImage.rows*factor), 0.0, 0.0, interpolation);
	
	return inputImage;
}


inline void ResizeFilter::ApplyFilter(PipelineInput & input, PipelineBuffer * buffer)
{
	buffer->setOutputImages(ApplyFilter(buffer->getOutputImage(input.getChannelNumber())), input.getChannelNumber());
}