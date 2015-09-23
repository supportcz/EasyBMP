/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Program: test1
 * File: stdio_br.h
 * Author: vancurar
 * Created: August 28, 2015
 *******************************************************************/

#ifndef STDIO_BR
#define STDIO_BR

#include <bur/plctypes.h>
#include <stdio.h>
#include <string.h>
#include <FileIO.h> 

#define PATH "DISK_F"

class FileInfo1
{
	public:
	FileInfo1 ( );
	~FileInfo1 ( );
	UDINT ident;
	UDINT size;
	UDINT position;
	USINT *buffer;
	UDINT bufferSize;
	bool writeAccess;
};

#define feof(p) ((((FileInfo1*)p)->position < ((FileInfo1*)p)->size) ? false:true)

#endif
