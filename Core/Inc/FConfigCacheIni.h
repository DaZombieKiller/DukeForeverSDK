/*=============================================================================
	FConfigCacheIni.h: Unreal config file reading/writing.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

	Revision history:
		* Created by Tim Sweeney
=============================================================================*/

/*-----------------------------------------------------------------------------
	Config cache.
-----------------------------------------------------------------------------*/

// One section in a config file.
class FConfigSection : public TMultiMap<FString,FString>
{};

// One config file.
class FConfigFile : public TMap<FString,FConfigSection>
{
public:
	UBOOL Dirty, NoSave;
	FConfigFile()
	: Dirty( 0 )
	, NoSave( 0 )
	{}
	UBOOL WriteToString( dnString& )
	{
		// TODO
		return 0;
	}
	UBOOL ReadFromString( dnString, UBOOL )
	{
		// TODO
		return 0;
	}
	void DecryptFromArray( dnArray<BYTE>, UBOOL )
	{
		// TODO
	}
	void CopyFromConfigFile( const FConfigFile* Other )
	{
		if( Other && Other != this )
		{
			Pairs = Other->Pairs;
			Rehash();
		}
	}
	void Read( const TCHAR* Filename, UBOOL NoEmpty=0, UBOOL Unknown=0 )
	{
		// TODO: Implement whatever Unknown does

		if( !NoEmpty )
			Empty();

		FString Text;
		if( appLoadFileToString( Text, Filename ) )
		{
			TCHAR* Ptr = const_cast<TCHAR*>( *Text );
			FConfigSection* CurrentSection = NULL;
			UBOOL Done = 0;
			while( !Done )
			{
				while( *Ptr=='\r' || *Ptr=='\n' )
					Ptr++;
				TCHAR* Start = Ptr;
				while( *Ptr && *Ptr!='\r' && *Ptr!='\n' )
					Ptr++;
				if( *Ptr==0 )
					Done = 1;
				*Ptr++ = 0;
				if( *Start=='[' && Start[appStrlen(Start)-1]==']' )
				{
					Start++;
					Start[appStrlen(Start)-1] = 0;
					CurrentSection = Find( Start );
					if( !CurrentSection )
						CurrentSection = &Set( Start, FConfigSection() );
				}
				else if( CurrentSection && *Start )
				{
					TCHAR* Value = appStrchr(Start,'=');
					if( Value )
					{
						*Value++ = 0;
						if( *Value=='\"' && Value[appStrlen(Value)-1]=='\"' )
						{
							Value++;
							Value[appStrlen(Value)-1]=0;
						}
						CurrentSection->Add( Start, Value );
					}
				}
			}
		}
	}
	UBOOL Write( const TCHAR* Filename, UBOOL Unknown=0 )
	{
		// TODO: Implement whatever Unknown does

		if( !Dirty || NoSave )
			return 1;
		Dirty = 0;
		FString Text;
		for( TIterator It(*this); It; ++It )
		{
			Text += FString::Printf( TEXT("[%s]\r\n"), *It.Key() );
			for( FConfigSection::TIterator It2(It.Value()); It2; ++It2 )
				Text += FString::Printf( TEXT("%s=%s\r\n"), *It2.Key(), *It2.Value() );
			Text += FString::Printf( TEXT("\r\n") );
		}
		return appSaveStringToFile( Text, Filename );
	}
};

// Set of all cached config files.
class FConfigCacheIni : public FConfigCache, public TMap<FString,FConfigFile>
{
public:
	// Basic functions.
	DWORD Unknown1, Unknown2; // related to coalesced files
	FString SystemIni, UserIni, ProgressIni;
	FConfigCacheIni()
	{}
	~FConfigCacheIni()
	{
		if( !GIsEditor || GIsUCC )
			Empty();
		else
			Flush( 1 );
	}
	FConfigFile* Find( const TCHAR* InFilename, UBOOL CreateIfNotFound, UBOOL Unknown1=0, UBOOL Unknown2=0 )
	{
		// TODO: Implement Unknown1, Unknown2

		// If filename not specified, use default.
		TCHAR Filename[256];
		appStrcpy( Filename, InFilename ? InFilename : *SystemIni );

		// Add .ini extension.
		INT Len = appStrlen(Filename);
		if( Len<5 || (Filename[Len-4]!='.' && Filename[Len-5]!='.') )
			appStrcat( Filename, TEXT(".ini") );

		// Automatically translate generic filenames.
		if( appStricmp(Filename,TEXT("User.ini"))==0 )
			appStrcpy( Filename, *UserIni );
		else if( appStricmp(Filename,TEXT("System.ini"))==0 )
			appStrcpy(Filename,*SystemIni);

		// Get file.
		FConfigFile* Result = TMap<FString,FConfigFile>::Find( Filename );
		if( !Result && (CreateIfNotFound || GFileManager->FileSize(Filename)>=0)  )
		{
			Result = &Set( Filename, FConfigFile() );
			Result->Read( Filename );
		}
		return Result;

	}
	void Flush( UBOOL Read, const TCHAR* Filename=NULL )
	{
		// TODO: DNF extensions

		for( TIterator It(*this); It; ++It )
			if( !Filename || It.Key()==Filename )
				It.Value().Write( *It.Key() );
		if( Read )
		{
			if( Filename )
				Remove(Filename);
			else
				Empty();
		}
	}
	void Detach( const TCHAR* Filename )
	{
		FConfigFile* File = Find( Filename, 1 );
		if( File )
			File->NoSave = 1;
	}
	UBOOL GetString( const TCHAR* Section, const TCHAR* Key, TCHAR* Value, INT Size, const TCHAR* Filename )
	{
		*Value = 0;
		FConfigFile* File = Find( Filename, 0 );
		if( !File )
			return 0;
		FConfigSection* Sec = File->Find( Section );
		if( !Sec )
			return 0;
		FString* PairString = Sec->Find( Key );
		if( !PairString )
			return 0;
		appStrncpy( Value, **PairString, Size );
		return 1;
	}
	UBOOL GetSection( const TCHAR* Section, TCHAR* Result, INT Size, const TCHAR* Filename )
	{
		*Result = 0;
		FConfigFile* File = Find( Filename, 0 );
		if( !File )
			return 0;
		FConfigSection* Sec = File->Find( Section );
		if( !Sec )
			return 0;
		TCHAR* End = Result;
		for( FConfigSection::TIterator It(*Sec); It && End-Result+appStrlen(*It.Key())+1<Size; ++It )
			End += appSprintf( End, TEXT("%s=%s"), *It.Key(), *It.Value() ) + 1;
		*End++ = 0;
		return 1;
	}
	TMultiMap<FString,FString>* GetSectionPrivate( const TCHAR* Section, UBOOL Force, UBOOL Const, const TCHAR* Filename )
	{
		FConfigFile* File = Find( Filename, Force );
		if( !File )
			return NULL;
		FConfigSection* Sec = File->Find( Section );
		if( !Sec && Force )
			Sec = &File->Set( Section, FConfigSection() );
		if( Sec && (Force || !Const) )
			File->Dirty = 1;
		return Sec;
	}
	void SetString( const TCHAR* Section, const TCHAR* Key, const TCHAR* Value, const TCHAR* Filename )
	{
		FConfigFile* File = Find( Filename, 1 );
		FConfigSection* Sec  = File->Find( Section );
		if( !Sec )
			Sec = &File->Set( Section, FConfigSection() );
		FString* Str = Sec->Find( Key );
		if( !Str )
		{
			Sec->Add( Key, Value );
			File->Dirty = 1;
		}
		else if( appStricmp(**Str,Value)!=0 )
		{
			File->Dirty = (appStrcmp(**Str,Value)!=0);
			*Str = Value;
		}
	}
	void EmptySection( const TCHAR* Section, const TCHAR* Filename )
	{
		FConfigFile* File = Find( Filename, 0 );
		if( File )
		{
			FConfigSection* Sec = File->Find( Section );
			if( Sec && FConfigSection::TIterator(*Sec) )
			{
				Sec->Empty();
				File->Dirty = 1;
			}
		}
	}
	void Init( const TCHAR* InSystem, const TCHAR* InUser, const TCHAR* InProgress, UBOOL RequireConfig )
	{
		SystemIni   = InSystem;
		UserIni     = InUser;
		ProgressIni = InProgress;
	}
	void Exit()
	{
		if( !GIsEditor || GIsUCC )
			Empty();
		else
			Flush( 1 );
	}
	void Dump( FOutputDevice& Ar )
	{
		Ar.Log( TEXT("Files map:") );
		TMap<FString,FConfigFile>::Dump( Ar );
	}
	void CoalesceFilesFromDisk( const TCHAR*, UBOOL )
	{
		// TODO
		GLog->Log(__FUNCTIONW__);
	}
	void LoadCoalescedLocalizationFile()
	{
		// TODO
		// Unknown1 and Unknown2 are set here
		GLog->Log(__FUNCTIONW__);
	}
	TArray<FString> FindFiles( const TCHAR* Filename, UBOOL Files, UBOOL Directories, UBOOL SubDirectories, UBOOL Absolute )
	{
		if( Unknown1 )
		{
			// TODO
		}

		return GFileManager->FindFiles( Filename, Files, Directories, SubDirectories, Absolute );
	}
	const TCHAR* GetNextToken( const TCHAR* Str, TCHAR* Result, INT StrLen )
	{
		if ( Str == NULL || *Str == '\0' )
			return NULL;

		while ( *Str == ' ' || *Str == '\t' || *Str == '\n' || *Str == '\r' )
			Str++;

		while ( StrLen - 1 > 0 && *Str != ' ' && *Str != '\t' && *Str != '\0' && *Str != '\n' && *Str != '\r' )
			*Result++ = *Str++;

		*Result = '\0';
		return Str;
	}
	void SaveConfig( FConfigFile*, const TCHAR*, UBOOL )
	{
		// TODO
	}
	void LoadFile( const TCHAR*, const TCHAR* )
	{
		// TODO
	}

	// Derived functions.
	UBOOL GetFColor
	(
		const TCHAR*	Section,
		const TCHAR*	Key,
		BYTE&			R,
		BYTE&			G,
		BYTE&			B,
		BYTE&			A,
		const TCHAR*	Filename
	)
	{
		TCHAR Token[82];
		const TCHAR* pText;
		TCHAR Text[80];
		if ( GetString( Section, Key, Text, ARRAY_COUNT(Text), Filename ) )
		{
			if ( (pText = GetNextToken( Text, Token, ARRAY_COUNT(Text) )) )
				R = appAtoi( Token );

			if ( (pText = GetNextToken( pText, Token, ARRAY_COUNT(Text) )) )
				G = appAtoi( Token );

			if ( (pText = GetNextToken( pText, Token, ARRAY_COUNT(Text) )) )
				B = appAtoi( Token );

			if ( (pText = GetNextToken( pText, Token, ARRAY_COUNT(Text) )) )
				A = appAtoi( Token );

			return 1;
		}

		return 0;
	}
	UBOOL GetString
	(
		const TCHAR* Section,
		const TCHAR* Key,
		FString&     Str,
		const TCHAR* Filename
	)
	{
		TCHAR Temp[4096]=TEXT("");
		UBOOL Result = GetString( Section, Key, Temp, ARRAY_COUNT(Temp), Filename );
		Str = Temp;
		return Result;
	}
	const dnString GetStr( const TCHAR* Section, const TCHAR* Key, const TCHAR* Filename )
	{
		dnString Result;
		GetString( Section, Key, Result, Filename );
		return Result;
	}
	UBOOL GetInt
	(
		const TCHAR*	Section,
		const TCHAR*	Key,
		INT&			Value,
		const TCHAR*	Filename
	)
	{
		TCHAR Text[80]; 
		if( GetString( Section, Key, Text, ARRAY_COUNT(Text), Filename ) )
		{
			Value = appAtoi(Text);
			return 1;
		}
		return 0;
	}
	UBOOL GetFloat
	(
		const TCHAR*	Section,
		const TCHAR*	Key,
		FLOAT&			Value,
		const TCHAR*	Filename
	)
	{
		TCHAR Text[80]; 
		if( GetString( Section, Key, Text, ARRAY_COUNT(Text), Filename ) )
		{
			Value = appAtof(Text);
			return 1;
		}
		return 0;
	}
	UBOOL GetBool
	(
		const TCHAR*	Section,
		const TCHAR*	Key,
		UBOOL&			Value,
		const TCHAR*	Filename
	)
	{
		TCHAR Text[80]; 
		if( GetString( Section, Key, Text, ARRAY_COUNT(Text), Filename ) )
		{
			if( appStricmp(Text,TEXT("True"))==0 )
			{
				Value = 1;
			}
			else
			{
				Value = appAtoi(Text)==1;
			}
			return 1;
		}
		return 0;
	}
	void SetFColor
	(
		const TCHAR* Section,
		const TCHAR* Key,
		BYTE		 R,
		BYTE		 G,
		BYTE		 B,
		BYTE		 A,
		const TCHAR* Filename
	)
	{
		TCHAR Buffer[82];
		appSprintf( Buffer, TEXT("%d %d %d %d"), R, G, B, A );
		SetString( Section, Key, Buffer, Filename );
	}
	void SetInt
	(
		const TCHAR* Section,
		const TCHAR* Key,
		INT			 Value,
		const TCHAR* Filename
	)
	{
		TCHAR Text[30];
		appSprintf( Text, TEXT("%i"), Value );
		SetString( Section, Key, Text, Filename );
	}
	void SetFloat
	(
		const TCHAR*	Section,
		const TCHAR*	Key,
		FLOAT			Value,
		const TCHAR*	Filename
	)
	{
		TCHAR Text[30];
		appSprintf( Text, TEXT("%f"), Value );
		SetString( Section, Key, Text, Filename );
	}
	void SetBool
	(
		const TCHAR* Section,
		const TCHAR* Key,
		UBOOL		 Value,
		const TCHAR* Filename
	)
	{
		SetString( Section, Key, Value ? TEXT("True") : TEXT("False"), Filename );
	}

	// Static allocator.
	static FConfigCache* Factory()
	{
		return new FConfigCacheIni();
	}
};

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
