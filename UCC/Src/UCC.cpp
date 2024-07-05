/*=============================================================================
	UCC.cpp: Unreal command-line launcher.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

Revision history:
	* Created by Tim Sweeney.
=============================================================================*/

#include <Windows.h>
#include <CommCtrl.h>
#include <malloc.h>
#include <stdio.h>
#include "Core.h"
#include "EditorPrivate.h"

/*-----------------------------------------------------------------------------
	Global variables.
-----------------------------------------------------------------------------*/

// Log.
#include "FOutputDeviceFile.h"
FOutputDeviceFile Log;

// Error.
#include "FOutputDeviceAnsiError.h"
FOutputDeviceAnsiError Error;

// Feedback.
#include "FFeedbackContextAnsi.h"
FFeedbackContextAnsi Warn;

// File manager.
#include "dnFileMgrDLC.h"

// NOTE: DNF assumes that the dnFileMgr implementation
// being used is dnFileMgrDLC. It writes to HashLookup
// in Multiplayer::SteamInit::LoadSHAHashTable without
// any type checks to ensure a dnFileMgrDLC is used.
dnFileMgrDLC FileManager;

// Config.
#include "FConfigCacheIni.h"

/*-----------------------------------------------------------------------------
	BugHandler.
-----------------------------------------------------------------------------*/
CORE_API long __stdcall CrashHandler_ConsoleExceptionHandler( LPEXCEPTION_POINTERS );
CORE_API long __stdcall CrashHandler_WindowedExceptionHandler( LPEXCEPTION_POINTERS );
CORE_API void CrashHandler_AssertHandler( void*, const char* Expr, const char* File, INT Line, const TCHAR* );

extern "C"
{
	CORE_API BOOL __stdcall SetCrashHandlerFilter( LONG(__stdcall*)( LPEXCEPTION_POINTERS ) );
	CORE_API void dnInitAssertMgr( void(*)( const TCHAR* ), void(*AssertHandler)( void*, const char* Expr, const char* File, INT Line, const TCHAR* ) );
}

/*-----------------------------------------------------------------------------
	Main.
-----------------------------------------------------------------------------*/

// Unreal command-line applet executor.
FString RightPad( FString In, INT Count )
{
	while( In.Len()<Count )
		In += TEXT(" ");
	return In;
}
INT Compare( FString& A, FString& B )
{
	return appStricmp( *A, *B );
}
void ShowBanner( FOutputDevice& Warn )
{
	Warn.Logf( TEXT("=======================================") );
	Warn.Logf( TEXT("ucc.exe: UnrealOS execution environment") );
	Warn.Logf( TEXT("Copyright 1999 Epic Games Inc") );
	Warn.Logf( TEXT("=======================================") );
	Warn.Logf( TEXT("") );
}
void MakeHeader( const TCHAR* Parms )
{
	FString Pkg, Path;
	UBOOL Force = ParseParam( Parms, TEXT("FORCEEXPORT") );
	UBOOL AllClasses = ParseParam( Parms, TEXT("ALLCLASSES") );

	if( !ParseToken(Parms, Pkg, 0) )
		appErrorf(TEXT("Package file not specified"));

	if( !ParseToken(Parms, Path, 0) )
		appErrorf(TEXT("Header path not specified"));

	INT Len = Path.InStr(TEXT("\\"), 1);
	UObject* Package = UObject::LoadPackage( NULL, *Pkg, LOAD_NoFail );

	if( Len > 0 && !GFileManager->MakeDirectory( *Path.Left(Len), 1) )
		appErrorf(TEXT("Failed to make directory %s"), *Path);

	for( TObjectIterator<UClass> It; It; ++It )
	{
		if( !It->IsIn( Package ) )
			continue;

		if( AllClasses )
			It->SetFlags( RF_Native );

		if( !(It->GetFlags() & RF_Native) )
			continue;

		if( Force )
			It->ClassFlags &= ~CLASS_NoExport;
		else if( It->ClassFlags & CLASS_NoExport )
			continue;

		for( TFieldIterator<UConst> FIt(*It); FIt; ++FIt )
			FIt->ConstFlags |= CONST_Native;

		for( TFieldIterator<UEnum> FIt(*It); FIt; ++FIt )
			FIt->EnumFlags |= ENUM_Native;

		for( TFieldIterator<UStruct> FIt(*It); FIt; ++FIt )
		{
			if( FIt->IsA(UFunction::StaticClass()) || FIt->IsA(UState::StaticClass()) )
				continue;

			if( FIt->GetOuter() != *It )
				continue;

			FIt->StructFlags |= STRUCT_Native;
		}

		if ( *It == UObject::StaticClass() )
			continue;

		It->SetFlags( RF_TagExp );
	}

	FStringOutputDevice Buffer;
	UClassExporterH* Exporter = ConstructObject<UClassExporterH>( UClassExporterH::StaticClass() );
	Exporter->ExportText( UObject::StaticClass(), TEXT("h"), Buffer, &Warn );
	appSaveStringToFile( Buffer, *Path );
	GIsRequestingExit = 1;
}
int _tmain( int argc, TCHAR* argv[] )
{
#if 1 // use windowed exception handler
	InitCommonControls();
	LoadLibrary( TEXT("RICHED32.DLL") );
	LoadLibrary( TEXT("DBGHELP.DLL") );
	SetCrashHandlerFilter( CrashHandler_WindowedExceptionHandler );
#else
	SetCrashHandlerFilter( CrashHandler_ConsoleExceptionHandler );
#endif
	dnInitAssertMgr( &UObject::StaticEnterSafeMode, &CrashHandler_AssertHandler );

	INT ErrorLevel = 0;
	GIsStarted     = 1;
#ifndef _DEBUG
	try
#endif
	{
		GIsGuarded = 1;

		// Parse command line.
		TCHAR CmdLine[2048], *CmdLinePtr=CmdLine;
		*CmdLinePtr = 0;

		TCHAR* Ch = GetCommandLine();
		while( *Ch && *Ch!=' ' )
			Ch++;
		while( *Ch==' ' )
			Ch++;
		while( *Ch )
			*CmdLinePtr++ = *Ch++;
		*CmdLinePtr++ = 0;
		
		// Init.
		GIsClient = GIsServer = GIsEditor = GIsScriptable = GIsUCC = 1;
		appInit( TEXT("DukeForever"), CmdLine, NULL, &Log, &Error, &Warn, &FileManager, FConfigCacheIni::Factory );
		UObject::SetLanguage(TEXT("int"));
		FString Token = argc>1 ? argv[1] : TEXT("");
		TArray<FRegistryObjectInfo> List;
		UObject::GetRegistryObjects( List, UClass::StaticClass(), UCommandlet::StaticClass(), 0 );
		GLazyLoad = 0;
		UBOOL Help = 0;
		DWORD LoadFlags = LOAD_NoWarn | LOAD_Quiet;
		if( Token==TEXT("") )
		{
			ShowBanner( Warn );
			Warn.Logf( TEXT("Use \"ucc help\" for help") );
		}
		else if ( Token==TEXT("MAKEHEADER") )
		{
			MakeHeader( appCmdLine() );
		}
		else if( Token==TEXT("HELP") )
		{
			ShowBanner( Warn );
			verify(UObject::StaticLoadClass( UCommandlet::StaticClass(), NULL, TEXT("Engine.Commandlet"), NULL, LOAD_NoFail, NULL )==UCommandlet::StaticClass());
			const TCHAR* Tmp = appCmdLine();
			GIsEditor = 0; // To enable loading localized text.
			if( !ParseToken( Tmp, Token, 0 ) )
			{
				INT i;
				Warn.Logf( TEXT("Usage:") );
				Warn.Logf( TEXT("   ucc <command> <parameters>") );
				Warn.Logf( TEXT("") );
				Warn.Logf( TEXT("Commands for \"ucc\":") );
				TArray<FString> Items;
				for( i=0; i<List.Num(); i++ )
				{
					UClass* Class = UObject::StaticLoadClass( UCommandlet::StaticClass(), NULL, *List(i).Object, NULL, LoadFlags, NULL );
					if( Class )
					{
						UCommandlet* Default = (UCommandlet*)Class->GetDefaultObject();
						Default->LoadLocalized();

						if( Default->HelpCmd.Len()==0 )
							new(Items)FString( FString(TEXT("   ucc ")) + RightPad(Default->HelpCmd,21) + TEXT(" (") + List(i).Object + TEXT(")") );
						else
							new(Items)FString( FString(TEXT("   ucc ")) + RightPad(Default->HelpCmd,21) + TEXT(" ") + Default->HelpOneLiner );
					}
				}
				new(Items)FString( TEXT("   ucc makeheader            Generate package headers") );
				new(Items)FString( TEXT("   ucc help <command>        Get help on a command") );
				Sort( &Items(0), Items.Num() );
				for( i=0; i<Items.Num(); i++ )
					Warn.Log( Items(i) );
			}
			else
			{
				Help = 1;
				goto Process;
			}
		}
		else
		{
			// Look it up.
			if( Token==TEXT("Make") )
				LoadFlags |= LOAD_DisallowFiles;
		Process:
			UClass* Class = UObject::StaticLoadClass( UCommandlet::StaticClass(), NULL, *Token, NULL, LoadFlags, NULL );
			if( !Class )
				Class = UObject::StaticLoadClass( UCommandlet::StaticClass(), NULL, *(Token+TEXT("Commandlet")), NULL, LoadFlags, NULL );
			if( !Class )
			{
				INT i;
				for( i=0; i<List.Num(); i++ )
				{
					FString Str = List(i).Object;
					while( Str.InStr(TEXT("."))>=0 )
						Str = Str.Mid(Str.InStr(TEXT("."))+1);
					if( Token==Str || Token+TEXT("Commandlet")==Str )
						break;
				}
				if( i<List.Num() )
					Class = UObject::StaticLoadClass( UCommandlet::StaticClass(), NULL, *List(i).Object, NULL, LoadFlags, NULL );
			}
			if( Class )
			{
				UCommandlet* Default = (UCommandlet*)Class->GetDefaultObject();
				if( Help )
				{
					// Get help on it.
					if( Default->HelpUsage!=TEXT("") )
					{
						Warn.Logf( TEXT("Usage:") );
						Warn.Logf( TEXT("   ucc %s"), *Default->HelpUsage );
					}
					if( Default->HelpParm[0]!=TEXT("") )
					{
						Warn.Logf( TEXT("") );
						Warn.Logf( TEXT("Parameters:") );
						for( INT i=0; i<ARRAY_COUNT(Default->HelpParm) && Default->HelpParm[i]!=TEXT(""); i++ )
							Warn.Logf( TEXT("   %s %s"), *RightPad(Default->HelpParm[i],16), *Default->HelpDesc[i] );
					}
					if( Default->HelpWebLink!=TEXT("") )
					{
						Warn.Logf( TEXT("") );
						Warn.Logf( TEXT("For more info, see") );
						Warn.Logf( TEXT("   %s"), *Default->HelpWebLink );
					}
				}
				else
				{
					// Run it.
					if( Default->LogToStdout )
					{
						Warn.AuxOut = GLog;
						GLog        = &Warn;
					}
					if( Default->ShowBanner )
					{
						ShowBanner( Warn );
					}
					debugf( TEXT("Executing %s"), Class->GetFullName() );
					GIsClient = Default->IsClient;
					GIsServer = Default->IsServer;
					GIsEditor = Default->IsEditor;
					GLazyLoad = Default->LazyLoad;
					UCommandlet* Commandlet = ConstructObject<UCommandlet>( Class );
					Commandlet->InitExecution();
					Commandlet->ParseParms( appCmdLine() );
					Commandlet->Main( appCmdLine() );
					if( Commandlet->ShowErrorCount )
						GWarn->Logf( TEXT("Success - 0 error(s), %i warnings"), Warn.WarningCount );
					if( Default->LogToStdout )
					{
						Warn.AuxOut = NULL;
						GLog        = &Log;
					}
				}
			}
			else
			{
				ShowBanner( Warn );
				Warn.Logf( TEXT("Commandlet %s not found"), *Token );
			}
		}
		appPreExit();
		GIsGuarded = 0;
	}
#ifndef _DEBUG
	catch( ... )
	{
		// Crashed.
		ErrorLevel = 1;
		GIsGuarded = 0;
	}
#endif
	appExit();
	GIsStarted = 0;
	return ErrorLevel;
}

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
