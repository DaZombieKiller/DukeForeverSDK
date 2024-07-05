/*=============================================================================
	EditorPrivate.h: Unreal editor public header file.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

/*----------------------------------------------------------------------------
	API.
----------------------------------------------------------------------------*/

#ifndef EDITOR_API
	#define EDITOR_API DLL_IMPORT
#endif

/*-----------------------------------------------------------------------------
	Exporters.
-----------------------------------------------------------------------------*/

class EDITOR_API UClassExporterH : public UExporter
{
	DECLARE_CLASS(UClassExporterH,UExporter,0)
	void StaticConstructor();
	UBOOL ExportText( UObject* Object, const TCHAR* Type, FOutputDevice& Out, FFeedbackContext* Warn );
};
