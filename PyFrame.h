/*
 * PyFrame.h
 *
 *  Created on: Mar 24, 2014
 *      Author: Gregory Kramida
 */

#ifndef PYFRAME_H_
#define PYFRAME_H_

#include "Frame.h"
#include <boost/python.hpp>


class PyFrame: public Frame {
public:
	PyFrame(int width, int height, bool imgFlag = true, bool grayFlag = true,
			bool maskFlag = true);
	PyFrame(Mat src, bool imgFlag = true, bool grayFlag = true, bool maskFlag = true);
	void setImage(Mat mat);
	void setGray(Mat mat);
	void setMask(Mat mat, int rid, int fg = 255, int bg = 0);
	void setMaskAll(Mat mat, int rid, int fg = 255, int bg = 0);
	void setMaskGray(Mat mat, int rid, int fg = 255, int bg = 0);
	void setMaskImage(Mat mat, int rid, int fg = 255, int bg = 0);
	virtual ~PyFrame();
private:
	void checkSize(const Mat& mat);
};

#endif /* PYFRAME_H_ */
