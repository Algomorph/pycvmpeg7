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
#include "Extraction/ColorStructureExtraction.h"
#include "CSInternalRoutines.hpp"

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
XM::ColorStructureDescriptor getColorStructureD3(Mat image,int descSize = 64) {
	PyFrame f(image);
	return *Feature::getColorStructureD(&f,descSize);
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

//=================================SECONDARY ROUTINES===============================================
PyObject* convert_RGB2HMMD(PyObject* o){
	if(!PyArray_Check(o)){
		PyErr_SetString(PyExc_ValueError,"convert_RGB2HMMD only accepts a 3D numpy ndarray of type np.uint8 as an argument");
		bp::throw_error_already_set();
	}
	PyArrayObject* arr = (PyArrayObject*) o;
	int ndims = PyArray_NDIM(arr);
	if(ndims != 3){
		PyErr_SetString(PyExc_ValueError,"convert_RGB2HMMD only accepts a 3D numpy ndarray of type np.uint8 as an argument");
		bp::throw_error_already_set();
	}
	int dtype = PyArray_TYPE(arr);
	if(dtype != NPY_UBYTE){
		PyErr_SetString(PyExc_ValueError,"convert_RGB2HMMD only accepts a 3D numpy ndarray of type np.uint8 as an argument");
		bp::throw_error_already_set();
	}
	const npy_intp* _sizes = PyArray_DIMS(arr);
	if(_sizes[2] != 3){
		PyErr_SetString(PyExc_ValueError,"Depth of the array must be 3");
		bp::throw_error_already_set();
	}
	NpyIter* iter = NpyIter_New(arr, NPY_ITER_READONLY, NPY_KEEPORDER, NPY_NO_CASTING, PyArray_DescrFromType(dtype));
	NpyIter_IterNextFunc* iternext = NpyIter_GetIterNext(iter, NULL);
	size_t byteSize = sizeof(short)*_sizes[0]*_sizes[1]*_sizes[2];
	short* result = (short*)malloc(byteSize);

	uchar** dataptr = (uchar**)NpyIter_GetDataPtrArray(iter);
	short* resptr = result;
	int H, S, D, R, G, B;

	do {
		R = (int)**dataptr;
		iternext(iter);
		G = (int)**dataptr;
		iternext(iter);
		B = (int)**dataptr;
		XM::ColorStructureExtractionTool::RGB2HMMD(R,G,B, H, S, D );
		*resptr = (short)H;
		resptr++;
		*resptr = (short)S;
		resptr++;
		*resptr = (short)D;
		resptr++;
	} while (iternext(iter));

	npy_intp dims[] = {_sizes[0],_sizes[1],_sizes[2]};
	PyObject* out = PyArray_SimpleNew(3, dims, NPY_SHORT);
	void *arr_data = PyArray_DATA((PyArrayObject*)out);
	memcpy(arr_data,result,byteSize);
	free(result);
	return out;
}

PyObject* quantizeHMMD(PyObject* o){
	if(!PyArray_Check(o)){
		PyErr_SetString(PyExc_ValueError,"convert_RGB2HMMD only accepts a 3D numpy ndarray of type np.int16 as an argument");
		bp::throw_error_already_set();
	}
	PyArrayObject* arr = (PyArrayObject*) o;
	int ndims = PyArray_NDIM(arr);
	if(ndims != 3){
		PyErr_SetString(PyExc_ValueError,"convert_RGB2HMMD only accepts a 3D numpy ndarray of type np.int16 as an argument");
		bp::throw_error_already_set();
	}
	int dtype = PyArray_TYPE(arr);
	if(dtype != NPY_SHORT){
		PyErr_SetString(PyExc_ValueError,"convert_RGB2HMMD only accepts a 3D numpy ndarray of type np.int16 as an argument");
		bp::throw_error_already_set();
	}
	const npy_intp* _sizes = PyArray_DIMS(arr);
	if(_sizes[2] != 3){
		PyErr_SetString(PyExc_ValueError,"Depth of the array must be 3");
		bp::throw_error_already_set();
	}
	NpyIter* iter = NpyIter_New(arr, NPY_ITER_READONLY, NPY_KEEPORDER, NPY_NO_CASTING, PyArray_DescrFromType(dtype));
	NpyIter_IterNextFunc* iternext = NpyIter_GetIterNext(iter, NULL);

	short** dataptr = (short**)NpyIter_GetDataPtrArray(iter);

	int H, S, D;
	uchar quant;

	npy_intp dims[] = {_sizes[0],_sizes[1]};
	PyObject* out = PyArray_SimpleNew(2, dims, NPY_UBYTE);
	uchar* arr_data = (uchar*)PyArray_DATA((PyArrayObject*)out);
	uchar* resptr = arr_data;

	do {
		H = (int)**dataptr;
		iternext(iter);
		S = (int)**dataptr;
		iternext(iter);
		D = (int)**dataptr;
		quant = (unsigned char)XM::ColorStructureExtractionTool::QuantHMMD(H,S,D,XM::ColorStructureExtractionTool::BASE_QUANT_SPACE_INDEX);
		*resptr = quant;
		resptr++;
	} while (iternext(iter));

	return out;
}

PyObject* quantizeAmplitude(PyObject* o){
	if(!PyArray_Check(o)){
		PyErr_SetString(PyExc_ValueError,"quantizeAmplitude only accepts a 1D numpy ndarray of type np.uint16 as an argument");
		bp::throw_error_already_set();
	}
	PyArrayObject* arr = (PyArrayObject*) o;
	int ndims = PyArray_NDIM(arr);
	if(ndims != 1){
		PyErr_SetString(PyExc_ValueError,"quantizeAmplitude only accepts a 1D numpy ndarray of type np.uint16 as an argument");
		bp::throw_error_already_set();
	}
	int dtype = PyArray_TYPE(arr);
	if(dtype != NPY_USHORT){
		PyErr_SetString(PyExc_ValueError,"quantizeAmplitude only accepts a 1D numpy ndarray of type np.uint16 as an argument");
		bp::throw_error_already_set();
	}
	NpyIter* iter = NpyIter_New(arr, NPY_ITER_READONLY, NPY_KEEPORDER, NPY_NO_CASTING, PyArray_DescrFromType(dtype));
	NpyIter_IterNextFunc* iternext = NpyIter_GetIterNext(iter, NULL);
	ushort** dataptr = (ushort**)NpyIter_GetDataPtrArray(iter);

	XM::ColorStructureExtractionTool* csdt = new  XM::ColorStructureExtractionTool();
	XM::ColorStructureDescriptor* csd = csdt->GetDescriptor();
	csd->SetSize(ColorStructureExtractionTool::BASE_QUANT_SPACE);
	for (int i =0; i < ColorStructureExtractionTool::BASE_QUANT_SPACE; i++){
		csd->SetElement(i,(int)**dataptr);
		iternext(iter);
	}
	csdt->QuantAmplNonLinear(249*249);
	npy_intp dims[] = {ColorStructureExtractionTool::BASE_QUANT_SPACE};
	PyObject* out = PyArray_SimpleNew(1, dims, NPY_UBYTE);
	uchar* arr_data = (uchar*)PyArray_DATA((PyArrayObject*)out);
	for (int i =0; i < ColorStructureExtractionTool::BASE_QUANT_SPACE; i++){
		arr_data[i] = (unsigned char)csd->GetElement(i);
	}
	return out;
}

XM::ColorStructureDescriptor slidingHistogram(PyObject* o){
	if(!PyArray_Check(o)){
		PyErr_SetString(PyExc_ValueError,"quantizeAmplitude only accepts a 2D numpy ndarray of type np.uint8 as an argument");
		bp::throw_error_already_set();
	}
	PyArrayObject* arr = (PyArrayObject*) o;
	int ndims = PyArray_NDIM(arr);
	if(ndims != 2){
		PyErr_SetString(PyExc_ValueError,"quantizeAmplitude only accepts a 2D numpy ndarray of type np.uint8 as an argument");
		bp::throw_error_already_set();
	}
	int dtype = PyArray_TYPE(arr);
	if(dtype != NPY_UBYTE){
		PyErr_SetString(PyExc_ValueError,"quantizeAmplitude only accepts a 2D numpy ndarray of type np.uint8 as an argument");
		bp::throw_error_already_set();
	}
	const npy_intp* shape = PyArray_DIMS(arr);
	uchar* arr_data = (uchar*)PyArray_DATA((PyArrayObject*)arr);
	return subroutines::extractDescriptorFromQuantBuffer(arr_data,shape[0],shape[1]);
}



//TODO: add Edge Histogram Descriptor extraction and Homogenous Texture Descriptor extraction

BOOST_PYTHON_MODULE(libMPEG7)
{
	using namespace XM;
	using namespace boost::python;
	init_ar();

	//Initialize converters
	to_python_converter<cv::Mat, bcvt::matToNDArrayBoostConverter>();
	bcvt::matFromNDArrayBoostConverter();
	to_python_converter<ColorStructureDescriptor,
			cvt::ColorStructureDescriptorToNDArray>();
	to_python_converter<ScalableColorDescriptor,
			cvt::ScalableColorDescriptorToPyObject>();
	to_python_converter<DominantColorDescriptor,
			cvt::DominantColorDescriptorToPyObject>();

	//Port subroutines
	def("convert_RGB2HMMD",convert_RGB2HMMD, arg("raster"));
	def("quantize_HMMD",quantizeHMMD,arg("raster"));
	def("quantize_amplitude",quantizeAmplitude,arg("descriptor"));
	def("sliding_histogram",slidingHistogram,arg("quant_array"));

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
	def("get_color_structure_descriptor", getColorStructureD3, (arg("raster"), arg("desc_size") = 64));
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
