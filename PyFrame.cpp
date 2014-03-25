/*
 * PyFrame.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: Gregory Kramida
 */

#include <PyFrame.h>
using namespace boost::python;

PyFrame::PyFrame(int width, int height, bool imgFlag, bool grayFlag ,
		bool maskFlag):
		Frame(width, height, imgFlag, grayFlag, maskFlag) {}

PyFrame::PyFrame(Mat src, bool imgFlag, bool grayFlag, bool maskFlag):
		Frame(src, imgFlag, grayFlag, maskFlag){}

void PyFrame::checkSize(const Mat& mat){
	if (mat.empty()) {
		PyErr_SetString(PyExc_TypeError,
				"Empty image or incompatible image argument type.");
		throw_error_already_set();
	}
	if (this->width != mat.cols || this->height != mat.rows) {
		std::ostringstream err_msg;
		err_msg << "Argument image shape does not match frame shape."
				<< std::endl << "Expected (row-major): (" << this->height
				<< ", " << this->width << "). " << std::endl
				<< "Received: (" << mat.rows << ", " << mat.cols << ")."
				<< std::endl;
		PyErr_SetString(PyExc_TypeError, err_msg.str().c_str());
		throw_error_already_set();
	}
}

void PyFrame::setImage(Mat mat) {
		this->checkSize(mat);
		Frame::setImage(mat);
	}

void PyFrame::setGray(Mat mat){
	this->checkSize(mat);
	Frame::setGray(mat);
}

void PyFrame::setMask(Mat mat, int rid, int fg, int bg){
	this->checkSize(mat);
	Frame::setMask(mat, rid, fg, bg);
}

void PyFrame::setMaskAll(Mat mat, int rid, int fg, int bg){
	this->checkSize(mat);
	Frame::setMaskAll(mat, rid, fg, bg);
}

void PyFrame::setMaskImage(Mat mat, int rid, int fg, int bg){
	this->checkSize(mat);
	Frame::setMaskImage(mat, rid, fg, bg);
}

void PyFrame::setMaskGray(Mat mat, int rid, int fg, int bg){
	this->checkSize(mat);
	Frame::setMaskGray(mat, rid, fg, bg);
}



PyFrame::~PyFrame() {
	// TODO Auto-generated destructor stub
}

