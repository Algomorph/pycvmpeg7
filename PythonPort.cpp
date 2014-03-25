/*
 * PythonPort.hpp
 *
 *  Created on: Mar 21, 2014
 *      Author: Gregory Kramida
 */

#include "CVBoostConverter.hpp"
#include "Feature.h"
#include "PyFrame.h"
#include "DescriptorConverters.hpp"

namespace bp = boost::python;

template<typename T>
inline std::vector<T> to_std_vector(const bp::object& iterable) {
	return std::vector<T>(bp::stl_input_iterator<T>(iterable),
			bp::stl_input_iterator<T>());
}

static void init_ar() {
	Py_Initialize();
	import_array();
}

//======================================COLOR STRUCTURE=============================================
XM::ColorStructureDescriptor getColorStructureD0(PyFrame f, int descSize = 64) {
	return *Feature::getColorStructureD(&f, descSize);
}
XM::ColorStructureDescriptor getColorStructureD1(Mat image, Mat mask,
		int maskVal = 0) {
	PyFrame f(image);
	f.setMaskAll(mask, maskVal);
	return *Feature::getColorStructureD(&f);
}
XM::ColorStructureDescriptor getColorStructureD2(Mat image) {
	PyFrame f(image);
	return *Feature::getColorStructureD(&f);
}
//=====================================SCALABLE COLOR===============================================
XM::ScalableColorDescriptor getScalableColorD0(PyFrame f, bool maskFlag = true,
		int numCoeff = 256, int bitPlanesDiscarded = 0) {
	return *Feature::getScalableColorD(&f, maskFlag, numCoeff,
			bitPlanesDiscarded);
}

XM::ScalableColorDescriptor getScalableColorD1(Mat image, Mat mask,
		int maskVal = 0, int numCoeff = 256, int bitPlanesDiscarded = 0) {
	PyFrame f(image);
	f.setMaskAll(mask, maskVal);
	return *Feature::getScalableColorD(&f, true, numCoeff, bitPlanesDiscarded);
}
XM::ScalableColorDescriptor getScalableColorD2(Mat image, int numCoeff = 256,
		int bitPlanesDiscarded = 0) {
	PyFrame f(image);
	return *Feature::getScalableColorD(&f, false, numCoeff, bitPlanesDiscarded);
}
//=====================================DOMINANT COLOR===============================================
XM::DominantColorDescriptor getDominantColorD0(Frame f, bool normalize = true,
		bool variance = true, bool spatial = true, int bin1 = 32, int bin2 = 32,
		int bin3 = 32) {
	return *Feature::getDominantColorD(&f, normalize, variance, spatial, bin1,
			bin2, bin3);
}
XM::DominantColorDescriptor getDominantColorD1(Mat image, bool normalize = true,
		bool variance = true, bool spatial = true, int bin1 = 32, int bin2 = 32,
		int bin3 = 32) {
	PyFrame f(image);
	return *Feature::getDominantColorD(&f, normalize, variance, spatial, bin1,
			bin2, bin3);
}
XM::DominantColorDescriptor getDominantColorD2(Mat image, Mat mask,
		int maskVal = 0, bool normalize = true, bool variance = true,
		bool spatial = true, int bin1 = 32, int bin2 = 32, int bin3 = 32) {
	PyFrame f(image);
	f.setMaskAll(mask, maskVal);
	return *Feature::getDominantColorD(&f, normalize, variance, spatial, bin1,
			bin2, bin3);
}

//TODO: add Edge Histogram Descriptor extraction and Homogenous Texture Descriptor extraction

BOOST_PYTHON_MODULE(libMPEG7)
{
	using namespace XM;
	using namespace boost::python;
	init_ar();
	to_python_converter<cv::Mat, bcvt::matToNDArrayBoostConverter>();
	bcvt::matFromNDArrayBoostConverter();
	to_python_converter<ColorStructureDescriptor,
			cvt::ColorStructureDescriptorToNDArray>();
	to_python_converter<ScalableColorDescriptor,
			cvt::ScalableColorDescriptorToPyObject>();
	to_python_converter<DominantColorDescriptor,
			cvt::DominantColorDescriptorToPyObject>();

	void (PyFrame::*setImageProper)(Mat) = &PyFrame::setImage;
	void (PyFrame::*setGrayProper)(Mat) = &PyFrame::setGray;
	void (PyFrame::*setMaskProper)(Mat, int, int, int) = &PyFrame::setMask;
	void (PyFrame::*setMaskAllProper)(Mat, int, int,
			int) = &PyFrame::setMaskAll;
	void (PyFrame::*setMaskImageProper)(Mat, int, int,
			int) = &PyFrame::setMaskImage;
	void (PyFrame::*setMaskGrayProper)(Mat, int, int,
			int) = &PyFrame::setMaskGray;

	//{RGB,YCRCB,HSV,HMMD,LinearMatrix,Monochrome}
	enum_<ColorSpaceType>("color_space_type").value("RGB", ColorSpaceType::RGB).value(
			"YCRCB", ColorSpaceType::YCRCB).value("HSV", ColorSpaceType::HSV).value(
			"HMMD", ColorSpaceType::HMMD).value("LinearMatrix",
			ColorSpaceType::LinearMatrix).value("Monochrome",
			ColorSpaceType::Monochrome);

	class_<PyFrame>("Frame", init<int, int, bool, bool, bool>()).def(
			init<int, int, bool, bool>()).def(init<int, int, bool>()).def(
			init<int, int>()).def(init<Mat, bool, bool, bool>()).def(
			init<Mat, bool, bool>()).def(init<Mat, bool>()).def(init<Mat>()).def(
			"reset_mask_all", &PyFrame::resetMaskAll).def("reset_mask_gray",
			&PyFrame::resetMaskGray).def("reset_mask_image",
			&PyFrame::resetMaskImage).def("resize", &PyFrame::resize).def(
			"set_image", setImageProper).def("set_gray", setGrayProper).def(
			"set_mask", setMaskProper).def("set_mask_all", setMaskAllProper).def(
			"set_mask_gray", setMaskGrayProper).def("set_mask_image",
			setMaskImageProper).def("set_mask_value", &Frame::setMaskValue).def_readonly(
			"width", &PyFrame::width).def_readonly("height", &Frame::height);

	def("get_color_structure_descriptor", getColorStructureD0,
			(arg("frame"), arg("desc_size") = 64));
	def("get_color_structure_descriptor", getColorStructureD1,
			(arg("raster"), arg("mask"), arg("mask_val")));
	def("get_color_structure_descriptor", getColorStructureD2, (arg("raster")));
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++
	def("get_scalable_color_descriptor", getScalableColorD0,
			(arg("frame"), arg("use_mask") = true, arg("num_coeffs") = 256, arg(
					"num_bit_planes_to_discard") = 0));
	def("get_scalable_color_descriptor", getScalableColorD1,
			(arg("raster"), arg("mask"), arg("mask_val") = 0, arg("num_coeffs") =
					256, arg("num_bit_planes_to_discard") = 0));
	def("get_scalable_color_descriptor", getScalableColorD2,
			(arg("raster"), arg("num_coeffs") = 256, arg(
					"num_bit_planes_to_discard") = 0));
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++

	def("get_dominant_color_descriptor", getDominantColorD0,
			(arg("frame"), arg("variance") = true, arg("spatial") = true, arg(
					"bin1") = 32, arg("bin2") = 32, arg("bin3") = 32));

	def("get_dominant_color_descriptor", getDominantColorD1,
			(arg("raster"), arg("variance") = true, arg("spatial") = true, arg(
					"bin1") = 32, arg("bin2") = 32, arg("bin3") = 32));
	def("get_dominant_color_descriptor", getDominantColorD2,
			(arg("raster"), arg("mask"), arg("mask_val") = 0, arg("variance") =
					true, arg("spatial") = true, arg("bin1") = 32, arg("bin2") =
					32, arg("bin3") = 32));
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++

}
