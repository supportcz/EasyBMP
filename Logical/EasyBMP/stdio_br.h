/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Program: test1
 * File: stdio_br.h
 * Author: vancurar
 * Created: August 28, 2015
 *******************************************************************/

#include <bur/plctypes.h>
#include <stdio.h>

#define PATH "DISK_F"

FILE *	fopen(const char *_name, const char *_type)
{
	if(!strcmp(_type, "rb")) {
		FileOpen_0.enable = 1;
		FileOpen_0.pDevice = (UDINT)PATH;
		FileOpen_0.pFile = (UDINT)_name;
		FileOpen_0.mode = fiREAD_ONLY;
	
		do {
			FileOpen(&FileOpen_0);	
		}while (FileOpen_0.status == 65535);
		
		if (FileOpen_0.status) return NULL;
	
		FileInfo_0.enable = 1;
		FileInfo_0.pDevice = (UDINT)PATH;
		FileInfo_0.pName = (UDINT)_name;
		FileInfo_0.pInfo = (UDINT)&fiFILE_INFO_0;
		
		do {
			FileInfo(&FileInfo_0);
		}while (FileInfo_0.status == 65535);
	
		if (FileInfo_0.status) return NULL;
	
		read_position = 0;
		return (FILE*)FileOpen_0.ident;		
	}	
	
	if(!strcmp(_type, "wb")) {
		//try to delete the file
		FileDelete_0.enable = 1;
		FileDelete_0.pDevice = (UDINT)PATH;
		FileDelete_0.pName = (UDINT)_name;
		do {
			FileDelete(&FileDelete_0);
		}while (FileDelete_0.status == 65535);
		
		//create the file
		FileCreate_0.enable = 1;
		FileCreate_0.pDevice = (UDINT)PATH;
		FileCreate_0.pFile = (UDINT)_name;
		do {
			FileCreate(&FileCreate_0);
		}while (FileCreate_0.status == 65535);
		
		if (FileCreate_0.status) return NULL;
		write_position = 0;
		return (FILE*)FileCreate_0.ident;		
	}
	return 0;
}

int feof(FILE *_file)
{
	if (read_position < fiFILE_INFO_0.size)
		return 0;
	else
		return 1;
}

size_t fread ( void * ptr, size_t size, size_t count, FILE * stream )
{
	if (read_position == 0) {
		read_buffer = new USINT[fiFILE_INFO_0.size];
			
		FileRead_0.enable = 1;
		FileRead_0.ident = (UDINT)stream;
		FileRead_0.offset = 0;
		FileRead_0.pDest = (UDINT)read_buffer;
		FileRead_0.len = fiFILE_INFO_0.size;
	
		do {
			FileRead(&FileRead_0);
		}while (FileRead_0.status == 65535);

		if (FileRead_0.status) return 0;
	}
	
	size_t length = size * count;
	memcpy(ptr, read_buffer + read_position, length);
	read_position += length;
	return length;	
}

int fclose ( FILE * stream )
{
	//data read?
	if (read_position > 0) {
		delete [] read_buffer;
		read_position = 0;
	}
	
	//write data?
	if (write_position > 0) {
		FileWrite_0.enable = 1;
		FileWrite_0.ident = (UDINT)stream;
		FileWrite_0.offset = 0;
		FileWrite_0.pSrc = (UDINT)write_buffer;
		FileWrite_0.len = write_position;
	
		do {
			FileWrite(&FileWrite_0);
		}while (FileWrite_0.status == 65535);
	
		delete [] write_buffer;	
		write_position = 0;
		if (FileWrite_0.status) return FileWrite_0.status;
	}
		
	
	FileClose_0.enable = 1;
	FileClose_0.ident = (UDINT)stream;
	
	do {
		FileClose(&FileClose_0);
	}while (FileClose_0.status == 65535);
	
	return FileClose_0.status; 	
}


size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream )
{
	const int reserve = 1000;
	
	if (write_position == 0) {
		write_buffer_size = 0;
		write_buffer = NULL;
	}
	
	size_t length = size * count;
	size_t needed_length = write_position + length;
		
	//reallocate array if it is too small
	if (needed_length >= write_buffer_size) {
		write_buffer_size = needed_length + reserve;
		USINT* resize_array = new USINT[write_buffer_size];
		memcpy(resize_array, write_buffer, write_position);
		delete [] write_buffer;
		write_buffer = resize_array;
	}
		
	memcpy(write_buffer + write_position, ptr, length);	
	write_position += length;
	return length;	
}
