(********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Program: loadBitmap
 * File: loadBitmap.st
 * Author: Bernecker + Rainer
 * Created: June 17, 2008
 ********************************************************************
 * Implementation of program loadBitmap

pokud je BMP hloubka 24bit tak to nacte
pokud ten samy obrazek je ale 8bit hloubka - øve , že nemá dostatek pamìti
 ********************************************************************)

PROGRAM _INIT
	deviceName := 'DISK_F';				(* CF Name of configured file device DISK*)
	drawBoxPath := 'Init_Page/Default/DrawBox_1';		(* Path of DrawBox in Visualization (Pagename/Layername/Drawboxname) *)
	useDrawBox := TRUE;				(* Option variable if you want to paint the picture only in a Drawbox or over the whole page *)
END_PROGRAM
 

PROGRAM _CYCLIC
    IF (handle = 0) THEN
        handle := VA_Setup(1 , 'Visu');		(* Get visualization handle *)
    ELSE
		state.va_saccess := VA_Saccess(1,handle);	(* Get access to visualization *)
	
		(******************* Attach Visapi to Drawbox ******************)
		IF (useDrawBox = TRUE) THEN												(* Check if the Visapi commands should be performed in a DrawBox *)
			state.va_attach := VA_Attach(1, handle, 0, ADR(drawBoxPath));		(* Attach Visapi functions to DrawBox *)
		END_IF
			
			
		CASE step OF
			0: //convert := 1;
				step := 1;									
				
			1: 
				//IF convert = 0 THEN
					step := 2;
				//END_IF
			
			(************************* Load Bitmap *************************)
			2: 	state.va_loadbitmap := VA_LoadBitmap(1, handle, deviceName, convertedPicture, ADR(pBitmap));		(* Load picture into memory *)
			
			IF(state.va_loadbitmap = 0) THEN		(* Check if command was successful *)
				brsmemcpy(ADR(bitmapInfo), pBitmap, SIZEOF(bitmapInfo));
				state.va_redraw := VA_Redraw(1, handle);	(* Clean page befor drawing a new picture *)
				step := 3;					(* Go to next step *)
				END_IF
		
		
			(************************* Blit Bitmap *************************)
			3:	state.va_blitbitmap := VA_BlitBitmap(1, handle, pBitmap, 0, 0, 0, 0, 0, 0, 0);	(* Show picture at specific coordinates *)

				IF(state.va_blitbitmap = 0) THEN		(* Check if command was successful *)
					step := 4;					(* Go to next step *)
				END_IF
   

			(************************* Free Bitmap *************************)
			4:	state.va_freebitmap := VA_FreeBitmap(1, handle, ADR(pBitmap));		(* Delete picture from memory *)
			
				IF (state.va_freebitmap = 0) THEN		(* Check if command was successful *)
					step := 0;					(* End draw steps *)
				END_IF
		END_CASE;
					
					
		(****************** Detach Visapi from Drawbox *****************)
		IF (useDrawBox = TRUE) THEN						(* Check if the Visapi commands should be performed in a DrawBox *)
			state.va_detach := VA_Detach(1, handle);	(* Detach Visapi functions from DrawBox *)
		END_IF
		
		state.va_srelease := VA_Srelease(1, handle);	(* Release access from visualization *)				
	END_IF
	

END_PROGRAM
