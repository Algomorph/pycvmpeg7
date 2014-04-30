/*
 * ColorDescriptorConverters.hpp
 *
 *  Created on: Mar 24, 2014
 *      Author: Gregory Kramida
 */

#ifndef DESCRIPTORCONVERTERS_HPP_
#include "boost/python.hpp"
#include <boost/python/stl_iterator.hpp>
#include "Python.h"
#include <numpy/ndarrayobject.h>
#include "Descriptors.h"
#include <cstring>
#include <cstdio>

using namespace XM;
namespace bp = boost::python;
namespace cvt{

struct ColorStructureDescriptorToNDArray {
	static PyObject* convert(const ColorStructureDescriptor& desc) {
		npy_intp dims[] = {static_cast<unsigned int>(desc.m_Size)};
		PyObject* o = PyArray_SimpleNew(1, dims, NPY_ULONG);
		void *arr_data = PyArray_DATA((PyArrayObject*)o);
		memcpy(arr_data,desc.m_Data,PyArray_ITEMSIZE((PyArrayObject*) o) * desc.m_Size);
		return o;
	}
};

struct ScalableColorDescriptorToPyObject {
	static PyObject* convert(const ScalableColorDescriptor& desc) {
		npy_intp dims[] = {static_cast<unsigned int>(desc.m_NumberOfCoefficients)};

		PyObject* hist = PyArray_SimpleNew(1, dims, NPY_ULONG);
		PyObject* signs = PyArray_SimpleNew(1, dims, NPY_ULONG);
		void *arr_data_hist = PyArray_DATA((PyArrayObject*)hist);
		void *arr_data_signs = PyArray_DATA((PyArrayObject*)signs);
		memcpy(arr_data_hist,desc.m_ScalableHistogram,PyArray_ITEMSIZE((PyArrayObject*) hist) * desc.m_NumberOfCoefficients);
		memcpy(arr_data_signs,desc.m_Sign,PyArray_ITEMSIZE((PyArrayObject*) hist) * desc.m_NumberOfCoefficients);
		return Py_BuildValue("OOk",hist,signs,desc.m_NumberOfBitplanesDiscarded);
	}
};

struct ColorQuantizerDescriptorToPyObject{
	static PyObject* convert(const ColorQuantizerDescriptor& desc) {
		const int num_components = 3;
		int components[num_components] = {desc.GetComponent(0),desc.GetComponent(1),desc.GetComponent(2)};
		int bin_number[num_components] =
				{desc.GetBinNumberByComponent(components[0]),
				desc.GetBinNumberByComponent(components[1]),
				desc.GetBinNumberByComponent(components[2])};
		PyObject* color_comp_tuple = PyTuple_New(num_components);
		for(Py_ssize_t i_comp = 0; i_comp < num_components; i_comp ++){
			PyTuple_SET_ITEM(color_comp_tuple,i_comp,Py_BuildValue("ii", bin_number[i_comp], components[i_comp]));
		}
		return color_comp_tuple;
	}
};

struct ColorSpaceDescriptorToPyObject{
	static PyObject* convert(const ColorSpaceDescriptor& desc) {
		npy_intp dims[] = {3,3};
		PyObject* matrix_arr = PyArray_SimpleNew(2, dims, NPY_FLOAT);
		const float* matrix = desc.GetColorSpaceMatrix();
		void *arr_data = PyArray_DATA((PyArrayObject*)matrix_arr);
		memcpy(arr_data,matrix,PyArray_ITEMSIZE((PyArrayObject*) matrix_arr) * 9);
		return Py_BuildValue("Oii",matrix_arr,desc.GetColorReferenceFlag(),desc.GetDescriptionColorSpace());
	}
};

struct DominantColorDescriptorToPyObject{
	static PyObject* convert(const DominantColorDescriptor& desc) {
		Py_ssize_t dominantColorCount = desc.GetDominantColorsNumber();
		PyObject* dominantColorList = PyList_New(dominantColorCount);
		DOMCOL* dominantColors = desc.GetDominantColors();
		//construct a tuple for each dominant color and add it to the list.
		for(Py_ssize_t i_dom_col = 0; i_dom_col < dominantColorCount; i_dom_col ++){
			DOMCOL color = dominantColors[i_dom_col];
			int percentage = color.m_Percentage;
			PyObject* color_value = Py_BuildValue("iii",color.m_ColorValue[0],color.m_ColorValue[1],color.m_ColorValue[2]);
			PyObject* color_variance = Py_BuildValue("iii",color.m_ColorVariance[0],color.m_ColorVariance[1],color.m_ColorVariance[2]);
			PyObject* py_dom_color = Py_BuildValue("OOi",color_value,color_variance,percentage);
			PyList_SetItem(dominantColorList,i_dom_col,py_dom_color);
		}
		Py_ssize_t ret_size = 1 + (int)desc.GetColorSpacePresent() + (int)desc.GetColorQuantizationPresent();
		if(ret_size == 1)
			//just the dominant colors are there, return the list itself.
			return dominantColorList;
		//other descriptors are present, combine them into a tuple with the dominant color list.
		PyObject* ret_tuple = PyTuple_New(ret_size);
		PyTuple_SET_ITEM(ret_tuple,0,dominantColorList);
		Py_ssize_t index = 1;
		if(desc.GetColorSpacePresent()){
			PyObject* pyColorSpaceDesc = ColorSpaceDescriptorToPyObject::convert(*desc.GetColorSpaceDescriptor());
			PyTuple_SET_ITEM(ret_tuple,index,pyColorSpaceDesc);
			index++;
		}
		if(desc.GetColorQuantizationPresent()){
			PyObject* pyColorSpaceDesc = ColorQuantizerDescriptorToPyObject::convert(*desc.GetColorQuantizerDescriptor());
			PyTuple_SET_ITEM(ret_tuple,index,pyColorSpaceDesc);
		}

		return ret_tuple;

	}
};



}//end namespace cvt
#define DESCRIPTORCONVERTERS_HPP_





#endif /* COLORDESCRIPTORCONVERTERS_HPP_ */
