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

#include "EasyBMP.h"
#include "stdio_br.h"

//using namespace std;

void _INIT test1Init(void)
{
	strcpy(sourcePicture,"object_8bit.bmp");
	strcpy(convertedPicture,"converted.bmp");
}

void _CYCLIC test1Cyclic(void)
{
	if (convert) {
	
//		cout << endl
//			<< "Using EasyBMP Version " << _EasyBMP_Version_ << endl << endl
//			<< "Copyright (c) by the EasyBMP Project 2005-6" << endl
//			<< "WWW: http://easybmp.sourceforge.net" << endl << endl;
	  
		//BMP Text;
		//Text.ReadFromFile("object_8bit.bmp");
  
		//BMP Background;
		//Background.ReadFromFile(sourcePicture);
  
		BMP Output;
		Output.ReadFromFile(sourcePicture);
		//Output.SetSize( Background.TellWidth() , Background.TellHeight() );
		//Output.SetBitDepth( 24 );
 
//		RangedPixelToPixelCopy( Background, 0, Output.TellWidth()-1,
//			Output.TellHeight()-1 , 0, 
//			Output, 0,0 );	
						 
		//		RangedPixelToPixelCopyTransparent( Text, 0, 380, 
		//			43, 0,
		//			Output, 110,5, 
		//			*Text(0,0) );
		//
		//		RangedPixelToPixelCopyTransparent( Text, 0, Text.TellWidth()-1, 
		//			Text.TellWidth()-1, 50,
		//			Output, 100,442, 
		//			*Text(0,49) );
					
//		Output.SetBitDepth( 32 );
//		cout << "writing 32bpp ... " << endl;					
//		Output.WriteToFile( "EasyBMPoutput32bpp.bmp" );

		Output.SetBitDepth( 24 );
		//cout << "writing 24bpp ... " << endl;			
		Output.WriteToFile(convertedPicture);
 
//		Output.SetBitDepth( 8 );
//		cout << "writing 8bpp ... " << endl;					
//		Output.WriteToFile( "EasyBMPoutput8bpp.bmp" );
//
//		Output.SetBitDepth( 4 );
//		cout << "writing 4bpp ... " << endl;					
//		Output.WriteToFile( "EasyBMPoutput4bpp.bmp" );
// 
//		Output.SetBitDepth( 1 );
//		cout << "writing 1bpp ... " << endl;					
//		Output.WriteToFile( "EasyBMPoutput1bpp.bmp" );
// 
//		Output.SetBitDepth( 24 );
//		Rescale( Output, 'p' , 50 );
//		cout << "writing 24bpp scaled image ..." << endl;
//		Output.WriteToFile( "EasyBMPoutput24bpp_rescaled.bmp" );	
		
		convert = 0;
	}
}
