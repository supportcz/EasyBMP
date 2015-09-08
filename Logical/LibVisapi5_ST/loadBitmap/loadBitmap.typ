(********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Program: loadBitmap
 * File: loadBitmap.typ
 * Author: Bernecker + Rainer
 * Created: June 17, 2008
 ********************************************************************
 * Local data types of program loadBitmap
 ********************************************************************)

TYPE
	LibVisapi5_ST_state_type : 	STRUCT  (*State variables of VISAPI commands*)
		va_srelease : UINT; (*State variable of command VA_Srelease*)
		va_saccess : UINT; (*State variable of command VA_Saccess*)
		va_loadbitmap : UINT; (*State variable of command VA_LoadBitmap*)
		va_blitbitmap : UINT; (*State variable of command VA_BlitBitmap*)
		va_freebitmap : UINT; (*State variable of command VA_FreeBitmap*)
		va_attach : UINT; (*State variable of command VA_Attach*)
		va_detach : UINT; (*State variable of command VA_Detach*)
		va_redraw : UINT; (*State variable of command VA_Redraw*)
	END_STRUCT;
END_TYPE
