/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: EasyBMP
 * File: stdio_br.cpp
 * Author: vancurar
 * Created: September 09, 2015
 *******************************************************************/

#include <stdio_br.h>

FileInfo1::FileInfo1 ( )
{
	ident = 0;
	size = 0;
	position = 0;
	buffer = NULL;
	bufferSize = 0;
	writeAccess = 0;
}   

FileInfo1::~FileInfo1 ( )
{
	delete [] buffer;
	buffer = NULL;
} 

FILE *	fopen(const char *_name, const char *_type)
{
	if(!strcmp(_type, "rb")) {
		FileOpen_typ FileOpen_0 = {0};

		FileOpen_0.enable = 1;
		FileOpen_0.pDevice = (UDINT)PATH;
		FileOpen_0.pFile = (UDINT)_name;
		FileOpen_0.mode = fiREAD_ONLY;
	
		do {
			FileOpen(&FileOpen_0);	
		}while (FileOpen_0.status == 65535);
		
		if (FileOpen_0.status) return NULL;
	
		FileInfo_typ FileInfo_0 = {0};
		FileInfo_0.enable = 1;
		FileInfo_0.pDevice = (UDINT)PATH;
		FileInfo_0.pName = (UDINT)_name;
		fiFILE_INFO fiFILE_INFO_0 = {0};
		FileInfo_0.pInfo = (UDINT)&fiFILE_INFO_0;
		
		do {
			FileInfo(&FileInfo_0);
		}while (FileInfo_0.status == 65535);
	
		if (FileInfo_0.status) return NULL;
	
		FileInfo1 *fi = new FileInfo1(); 
		fi->size = fiFILE_INFO_0.size;		
		fi->ident = FileOpen_0.ident;
		return (FILE*)fi;		
	}	
	
	if(!strcmp(_type, "wb")) {
		//try to delete the file
		FileDelete_typ FileDelete_0 = {0};
		FileDelete_0.enable = 1;
		FileDelete_0.pDevice = (UDINT)PATH;
		FileDelete_0.pName = (UDINT)_name;
		do {
			FileDelete(&FileDelete_0);
		}while (FileDelete_0.status == 65535);
		
		//create the file
		FileCreate_typ FileCreate_0 = {0};
		FileCreate_0.enable = 1;
		FileCreate_0.pDevice = (UDINT)PATH;
		FileCreate_0.pFile = (UDINT)_name;
		do {
			FileCreate(&FileCreate_0);
		}while (FileCreate_0.status == 65535);
		
		if (FileCreate_0.status) return NULL;

		FileInfo1 *fi = new FileInfo1(); 
		fi->ident = FileCreate_0.ident;
		fi->writeAccess = 1;
		return (FILE*)fi;		
	}
	return 0;
}



size_t fread ( void * ptr, size_t size, size_t count, FILE * stream )
{
	FileInfo1 *fi = (FileInfo1 *)stream;

	if (fi->position == 0) {
		fi->buffer = new USINT[fi->size];
		
		FileRead_typ FileRead_0 = {0};
		FileRead_0.enable = 1;
		FileRead_0.ident = fi->ident;
		FileRead_0.offset = 0;
		FileRead_0.pDest = (UDINT)fi->buffer;
		FileRead_0.len = fi->size;
	
		do {
			FileRead(&FileRead_0);
		}while (FileRead_0.status == 65535);

		if (FileRead_0.status) return 0;
	}
	
	size_t length = size * count;
	memcpy(ptr, fi->buffer + fi->position, length);
	fi->position += length;
	return length;	
}

int fclose ( FILE * stream )
{
	FileInfo1 *fi = (FileInfo1 *)stream;

	if (fi->writeAccess) {
		//data written
		if (fi->position > 0) {
			FileWrite_typ FileWrite_0 = {0};
			FileWrite_0.enable = 1;
			FileWrite_0.ident = fi->ident;
			FileWrite_0.offset = 0;
			FileWrite_0.pSrc = (UDINT)fi->buffer;
			FileWrite_0.len = fi->position;
		
			do {
				FileWrite(&FileWrite_0);
			}while (FileWrite_0.status == 65535);
		
			if (FileWrite_0.status) return FileWrite_0.status;
		}
	}		
	
	FileClose_typ FileClose_0 = {0};
	FileClose_0.enable = 1;
	FileClose_0.ident = fi->ident;
	
	do {
		FileClose(&FileClose_0);
	}while (FileClose_0.status == 65535);
	
	return FileClose_0.status; 	
}


size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream )
{
	const int reserve = 1000;
	FileInfo1 *fi = (FileInfo1 *)stream;	
	
	//	if (fi->position == 0) {
	//		bufferSize = 0;
	//		write_buffer = NULL;
	//	}
	
	size_t length = size * count;
	size_t needed_length = fi->position + length;
		
	//reallocate array if it is too small
	if (needed_length >= fi->bufferSize) {
		fi->bufferSize = needed_length + reserve;
		USINT* resize_array = new USINT[fi->bufferSize];
			memcpy(resize_array, fi->buffer, fi->position);
		delete [] fi->buffer;
		fi->buffer = resize_array;
	}
		
	memcpy(fi->buffer + fi->position, ptr, length);	
	fi->position += length;
	return length;	
}


