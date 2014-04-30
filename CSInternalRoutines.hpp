/*
 * CSInternalRoutines.hpp
 *
 *  Created on: Apr 25, 2014
 *      Author: Gregory Kramida
 */

#ifndef CSINTERNALROUTINES_HPP_
#define CSINTERNALROUTINES_HPP_

#include "Descriptors/ColorStructure.h"
#include "Extraction/ColorStructureExtraction.h"
#ifndef MAX
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#endif

namespace subroutines{
XM::ColorStructureDescriptor extractDescriptorFromQuantBuffer(unsigned char* quantImageBuffer, int width, int height);
}
#endif /* CSINTERNALROUTINES_HPP_ */
