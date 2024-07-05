/*=============================================================================
	dnFileMgrDLC.h: DLC file manager.
=============================================================================*/

#include "FFileManagerWindows.h"

/*-----------------------------------------------------------------------------
	File Manager.
-----------------------------------------------------------------------------*/

// File manager.
class dnFileMgrDLC : public FFileManagerWindows
{
	void Init()
	{
		FString CurrentDir = GetCurrentDirectory();
		SetCurrentDirectory( *dnBaseContentDir() );
		BaseContentDir = GetCurrentDirectory();
		SetCurrentDirectory( *dnBaseDir() );
		BaseDir = GetCurrentDirectory();
		SetCurrentDirectory( *CurrentDir );
	}
	
	UBOOL FileExistsInDLC( const TCHAR* Filename, FString& DLCFilename )
	{
		TCHAR Buffer[1024];
		TArray<FString> Paths;

		if( GIsUCC && !g_UCCAllowDLCFiles )
			return 0;

		if( appStrstr( Filename, TEXT("..\\") )==Filename || appStrstr( Filename, TEXT("../") )==Filename )
			Filename += 3;

		for( INT i=DLCFiles.Num()-1; i>=0; i-- )
		{
			appSprintf( Buffer, TEXT("%s%s\\%s"), *BaseDLCContentDir, *DLCFiles(i), Filename );
			Paths = FFileManagerWindows::FindFiles( Buffer, 1, 0, 0, 1 );

			if( Paths.Num() )
			{
				DLCFilename = Buffer;

				if( HashLookup )
				{
					return HashLookup( DLCFilename );
				}
			}
		}

		return 0;
	}

	UBOOL RemovePrefix( const TCHAR* Prefix, const TCHAR* Str, FString& Dest )
	{
		INT PrefixLen;
		INT ResultLen;
		TCHAR Buffer[1024];
		PrefixLen = appStrlen( Prefix );

		if( appStrncmp( Str, Prefix, PrefixLen ) )
		{
			Dest = Str;
			return 0;
		}

		ResultLen = appStrlen( Str ) - PrefixLen + 1;
		appStrncpy( Buffer, Str + PrefixLen, ResultLen );
		Buffer[ResultLen - 1] = TEXT('\0');
		Dest = Buffer;
		return 1;
	}

public:
	virtual ~dnFileMgrDLC()
	{
	}

	void PreInit()
	{
		TCHAR Buffer[1024];
		Init();
		appSprintf( Buffer, TEXT("%sDLC\\"), *BaseContentDir );
		BaseDLCContentDir = Buffer;
	}

	TArray<FString> FindFiles( const TCHAR* Filename, UBOOL Files, UBOOL Directories, UBOOL SubDirectories, UBOOL Absolute )
	{
		FString Path;
		TArray<FString> Paths;
		TArray<FString> DLCPaths;
		TCHAR Buffer[1026];

		if( GIsUCC && !g_UCCAllowDLCFiles )
			return FFileManagerWindows::FindFiles( Filename, Files, Directories, SubDirectories, Absolute );

		Paths = FFileManagerWindows::FindFiles( Filename, Files, Directories, SubDirectories, Absolute );

		if( RemovePrefix( *BaseContentDir, Filename, Path ))
		{
			appSprintf( Buffer, TEXT("%s%s"), *BaseDLCContentDir, *Path );
			DLCPaths = FFileManagerWindows::FindFiles( Buffer, Files, Directories, SubDirectories, Absolute );
		}

		for( INT i=0; i<DLCPaths.Num(); i++ )
			Paths.AddItem( DLCPaths(i) );

		return Paths;
	}

	FArchive* CreateFileReader( const TCHAR* Filename, DWORD Flags, FOutputDevice* Error )
	{
		FString DLCFilename;

		if( FileExistsInDLC( Filename, DLCFilename ))
			return FFileManagerWindows::CreateFileReader( *DLCFilename, Flags, Error );

		return FFileManagerWindows::CreateFileReader( Filename, Flags, Error );
	}

	INT FileSize( const TCHAR* Filename )
	{
		FString DLCFilename;

		if( FileExistsInDLC( Filename, DLCFilename ))
			return FFileManagerWindows::FileSize( *DLCFilename );

		return FFileManagerWindows::FileSize( Filename );
	}
private:
	TArray<FString> DLCFiles;
	FString BaseContentDir;
	FString BaseDir;
	FString BaseDLCContentDir;

	// Might be public, mightd have an optimized out setter.
	// Assigned by Multiplayer::SteamInit::LoadSHAHashTable.
	UBOOL(*HashLookup)( FString );
};
