/*
 * CSInternalRoutines.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: Gregory Kramida
 */
#include "CSInternalRoutines.hpp"
#include <cmath>
#include <cstring>
namespace subroutines{
XM::ColorStructureDescriptor extractDescriptorFromQuantBuffer(unsigned char* quantImageBuffer, int width, int height){
	using namespace XM;
	double logArea =  log(width * height) / log(2);
	int scalePower = (int)floor(0.5 * logArea - 8 + 0.5);
	scalePower = MAX(0, scalePower);
	unsigned long subSample = 1 << scalePower;
	unsigned long slideWidth = 8 * subSample;
	unsigned long slideHeight = 8 * subSample;

	unsigned long modifiedImageWidth  = width  - (slideWidth  - 1);
	unsigned long modifiedImageHeight = height - (slideHeight - 1);

	// allocate local sliding window histogram
	unsigned long* slideHist = new unsigned long[ColorStructureExtractionTool::BASE_QUANT_SPACE];
	unsigned long row, col, index;
	unsigned char	*pAdd, *pDel, *pAddStop;
	ColorStructureDescriptor m_Descriptor = ColorStructureDescriptor();
	m_Descriptor.SetSize(ColorStructureExtractionTool::BASE_QUANT_SPACE);

	// loop through columns
	for( col = 0; col < modifiedImageWidth; col += subSample ){
		// reset and fill in the first (top of image) full sliding window histograms
		memset( (void *) slideHist, 0, ColorStructureExtractionTool::BASE_QUANT_SPACE * sizeof(unsigned long) );
		for( row = 0; row < slideHeight; row += subSample ){
			pAdd  =    &quantImageBuffer[row * width + col];
			pAddStop = pAdd + slideWidth;
			for( ; pAdd < pAddStop; pAdd += subSample){
					slideHist[*pAdd] ++;
			}
		}

		// update histogram from first sliding window histograms
		for ( index = 0; index < ColorStructureExtractionTool::BASE_QUANT_SPACE; index ++){
			if( slideHist[ index ] ){
				m_Descriptor.
				SetElement( index, m_Descriptor.
							GetElement(index) + 1 );
			}
		}

		// slide the window down the rest of the rows
		for( row = subSample; row < modifiedImageHeight; row += subSample ){
			pDel  =    &quantImageBuffer[(row - subSample) * width + col];
			pAdd  =    &quantImageBuffer[(row + slideHeight - subSample) * width + col];
			pAddStop = pAdd + slideWidth;
			for( ; pAdd < pAddStop; pDel += subSample, pAdd += subSample){
					slideHist[*pDel] --;
					slideHist[*pAdd] ++;
			}

			// update histogram from sliding window histogram
			for ( index = 0; index < ColorStructureExtractionTool::BASE_QUANT_SPACE; index ++)
			{
				if( slideHist[ index ] )
					m_Descriptor.
						SetElement( index, m_Descriptor.
											GetElement(index) + 1 );
			}
		}
	}

	// Free memory
	delete [] slideHist;
	delete [] quantImageBuffer;
	return m_Descriptor;
}
}//end namespace subroutines
