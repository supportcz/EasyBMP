/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Program: test1
 * File: test1.cpp
 * Author: vancurar
 * Created: August 20, 2015
 ********************************************************************
 * Implementation of program test1
 ********************************************************************/
unsigned long bur_heap_size=0xFFFFFF;

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include "..\Libraries\EasyBMP\EasyBMP.h"


void _INIT test1Init(void)
{
	strcpy(sourcePicture,"object_8bit.bmp");
	strcpy(convertedPicture,"converted.bmp");
}

void _CYCLIC test1Cyclic(void)
{
	//by setting "convert" to "1", an 8bit bitmap from F:\ will be converted to 24bit
	if (convert) {

		BMP Output;
		Output.ReadFromFile(sourcePicture);
		Output.SetBitDepth( 24 );
		Output.WriteToFile(convertedPicture);		
		convert = 0;
	}
}
