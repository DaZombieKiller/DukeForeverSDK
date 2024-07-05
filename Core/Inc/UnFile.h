/*=============================================================================
	UnFile.h: General-purpose file utilities.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

/*-----------------------------------------------------------------------------
	Global variables.
-----------------------------------------------------------------------------*/

// Global variables.
#if DNF
extern "C"
#endif
CORE_API extern DWORD GCRCTable[];

/*----------------------------------------------------------------------------
	Byte order conversion.
----------------------------------------------------------------------------*/

// Bitfields.
#ifndef NEXT_BITFIELD
	#if __INTEL_BYTE_ORDER__
		#define NEXT_BITFIELD(b) ((b)<<1)
		#define FIRST_BITFIELD   (1)
		#define INTEL_ORDER(x)   (x)
	#else
		#define NEXT_BITFIELD(b) ((b)>>1)
		#define FIRST_BITFIELD   (0x80000000)
		#define INTEL_ORDER(x)   (((x)>>24) + (((x)>>8)&0xff00) + (((x)<<8)&0xff0000) + ((x)<<24))
	#endif
#endif

/*-----------------------------------------------------------------------------
	Stats.
-----------------------------------------------------------------------------*/

#if STATS
	#define STAT(x) x
#else
	#define STAT(x)
#endif

/*-----------------------------------------------------------------------------
	Global init and exit.
-----------------------------------------------------------------------------*/

#if DNF
CORE_API void appInit( const TCHAR* InPackage, const TCHAR* InCmdLine, FMalloc* InMalloc, FOutputDevice* InLog, FOutputDeviceError* InError, FFeedbackContext* InWarn, FFileManager* InFileManager, FConfigCache*(*ConfigFactory)() );
#else
CORE_API void appInit( const TCHAR* InPackage, const TCHAR* InCmdLine, FMalloc* InMalloc, FOutputDevice* InLog, FOutputDeviceError* InError, FFeedbackContext* InWarn, FFileManager* InFileManager, FConfigCache*(*ConfigFactory)(), UBOOL RequireConfig );
#endif
CORE_API void appPreExit();
CORE_API void appExit();

/*-----------------------------------------------------------------------------
	Logging and critical errors.
-----------------------------------------------------------------------------*/

CORE_API void appRequestExit( UBOOL Force );

CORE_API void VARARGS appFailAssert( const ANSICHAR* Expr, const ANSICHAR* File, INT Line );
CORE_API void VARARGS appUnwindf( const TCHAR* Fmt, ... );
CORE_API const TCHAR* appGetSystemErrorMessage( INT Error=0 );
CORE_API const void appDebugMessagef( const TCHAR* Fmt, ... );
CORE_API const void appMsgf( const TCHAR* Fmt, ... );
CORE_API const void appGetLastError( void );

#define debugf				GLog->Logf
#define appErrorf			GError->Logf

#if DO_GUARD_SLOW
	#define debugfSlow		GLog->Logf
	#define appErrorfSlow	GError->Logf
#else
	#define debugfSlow		GNull->Logf
	#define appErrorfSlow	GNull->Logf
#endif

/*-----------------------------------------------------------------------------
	Misc.
-----------------------------------------------------------------------------*/

CORE_API void* appGetDllHandle( const TCHAR* DllName );
CORE_API void appFreeDllHandle( void* DllHandle );
CORE_API void* appGetDllExport( void* DllHandle, const TCHAR* ExportName );
CORE_API void appLaunchURL( const TCHAR* URL, const TCHAR* Parms=NULL, FString* Error=NULL );
CORE_API void appCreateProc( const TCHAR* URL, const TCHAR* Parms );
CORE_API void appEnableFastMath( UBOOL Enable );
CORE_API class FGuid appCreateGuid();
CORE_API void appCreateTempFilename( const TCHAR* Path, TCHAR* Result256 );
CORE_API void appCleanFileCache();
CORE_API UBOOL appFindPackageFile( const TCHAR* In, const FGuid* Guid, TCHAR* Out );

/*-----------------------------------------------------------------------------
	Clipboard.
-----------------------------------------------------------------------------*/

CORE_API void appClipboardCopy( const TCHAR* Str );
CORE_API FString appClipboardPaste();

/*-----------------------------------------------------------------------------
	Guard macros for call stack display.
-----------------------------------------------------------------------------*/

//
// guard/unguardf/unguard macros.
// For showing calling stack when errors occur in major functions.
// Meant to be enabled in release builds.
//
//#undef DO_GUARD
//#define DO_GUARD 0	// NJS: Turn it off.

#if defined(_DEBUG) || !DO_GUARD
	#define guard(func)			{static const TCHAR __FUNC_NAME__[]=TEXT(#func);
	#define unguard				}
	#define unguardf(msg)		}
#else
	#if _MSC_VER
		#define guard(func)			{static const TCHAR __FUNC_NAME__[]=TEXT(#func); try{
		#define unguard				}catch(TCHAR*Err){throw Err;}catch(...){appUnwindf(TEXT("%s"),__FUNC_NAME__); throw;}}
		#define unguardf(msg)		}catch(TCHAR*Err){throw Err;}catch(...){appUnwindf(TEXT("%s"),__FUNC_NAME__); appUnwindf msg; throw;}}
	#else
		#define guard(func)			{static const TCHAR __FUNC_NAME__[]=TEXT(#func); \
									__Context __LOCAL_CONTEXT__; try{ \
									if(setjmp(__Context::Env)) { throw 1; } else {
		#define unguard				}}catch(char*Err){throw Err;}catch(...) \
									{appUnwindf(TEXT("%s"),__FUNC_NAME__); throw;}}
		#define unguardf(msg)		}}catch(char*Err){throw Err;}catch(...) \
									{appUnwindf(TEXT("%s"),__FUNC_NAME__); \
									appUnwindf msg; throw;}}
	#endif
#endif

//
// guardSlow/unguardfSlow/unguardSlow macros.
// For showing calling stack when errors occur in performance-critical functions.
// Meant to be disabled in release builds.
//
#if defined(_DEBUG) || !DO_GUARD || !DO_GUARD_SLOW
	#define guardSlow(func)		{
	#define unguardfSlow(msg)	}
	#define unguardSlow			}
	#define unguardfSlow(msg)	}
#else
	#define guardSlow(func)		guard(func)
	#define unguardSlow			unguard
	#define unguardfSlow(msg)	unguardf(msg)
#endif

//
// For throwing string-exceptions which safely propagate through guard/unguard.
//
CORE_API void VARARGS appThrowf( const TCHAR* Fmt, ... );

/*-----------------------------------------------------------------------------
	Check macros for assertions.
-----------------------------------------------------------------------------*/

//
// "check" expressions are only evaluated if enabled.
// "verify" expressions are always evaluated, but only cause an error if enabled.
//
#if DO_CHECK
	#define check(expr)  {if(!(expr)) appFailAssert( #expr, __FILE__, __LINE__ );}
	#define verify(expr) {if(!(expr)) appFailAssert( #expr, __FILE__, __LINE__ );}
#else
	#define check(expr)
	#define verify(expr) expr
#endif

//
// Check for development only.
//
#if DO_GUARD_SLOW
	#define checkSlow(expr)  {if(!(expr)) appFailAssert( #expr, __FILE__, __LINE__ );}
	#define verifySlow(expr) {if(!(expr)) appFailAssert( #expr, __FILE__, __LINE__ );}
#else
	#define checkSlow(expr)
	#define verifySlow(expr) if(expr){}
#endif

/*-----------------------------------------------------------------------------
	Timing macros.
-----------------------------------------------------------------------------*/

//
// Normal timing.
//
#define clock(Timer)   {Timer -= appCycles();}
#define unclock(Timer) {Timer += appCycles()-34;}

//
// Performance critical timing.
//
#if DO_CLOCK_SLOW
	#define clockSlow(Timer)   {Timer-=appCycles();}
	#define unclockSlow(Timer) {Timer+=appCycles();}
#else
	#define clockSlow(Timer)
	#define unclockSlow(Timer)
#endif

/*-----------------------------------------------------------------------------
	Text format.
-----------------------------------------------------------------------------*/

CORE_API FString appFormat( FString Src, const TMultiMap<FString,FString>& Map );

/*-----------------------------------------------------------------------------
	Localization.
-----------------------------------------------------------------------------*/

#if DNF
CORE_API const dnString Localize( const TCHAR* Section, const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL, UBOOL Optional=0, UBOOL LogError=0, UBOOL* Result=NULL );
CORE_API const dnString LocalizeError( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
CORE_API const dnString LocalizeProgress( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
CORE_API const dnString LocalizeQuery( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
CORE_API const dnString LocalizeGeneral( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
#else
CORE_API const TCHAR* Localize( const TCHAR* Section, const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL, UBOOL Optional=0 );
CORE_API const TCHAR* LocalizeError( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
CORE_API const TCHAR* LocalizeProgress( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
CORE_API const TCHAR* LocalizeQuery( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
CORE_API const TCHAR* LocalizeGeneral( const TCHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
#endif

#if DNF
	CORE_API const dnString Localize( const ANSICHAR* Section, const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL, UBOOL Optional=0, UBOOL LogError=0, UBOOL* Result=NULL );
	CORE_API const dnString LocalizeError( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
	CORE_API const dnString LocalizeProgress( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
	CORE_API const dnString LocalizeQuery( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
	CORE_API const dnString LocalizeGeneral( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
#elif UNICODE
	CORE_API const TCHAR* Localize( const ANSICHAR* Section, const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL, UBOOL Optional=0 );
	CORE_API const TCHAR* LocalizeError( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
	CORE_API const TCHAR* LocalizeProgress( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
	CORE_API const TCHAR* LocalizeQuery( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
	CORE_API const TCHAR* LocalizeGeneral( const ANSICHAR* Key, const TCHAR* Package=GPackage, const TCHAR* LangExt=NULL );
#endif

/*-----------------------------------------------------------------------------
	File functions.
-----------------------------------------------------------------------------*/

// File utilities.
CORE_API const TCHAR* appFExt( const TCHAR* Filename );
CORE_API UBOOL appUpdateFileModTime( TCHAR* Filename );

#if !DNF
CORE_API FString appGetGMTRef();
#endif

/*-----------------------------------------------------------------------------
	OS functions.
-----------------------------------------------------------------------------*/

#if DNF
#define appCmdLine() GCmdLine
CORE_API const dnString appBaseDir();
CORE_API const dnString dnDataDir();
CORE_API const dnString dnBaseContentDir();
CORE_API const dnString appPackage();
CORE_API const dnString appComputerName();
CORE_API const dnString appUserName();
CORE_API extern HINSTANCE GLaunchMutex; // NJS: Used to track the 'single instance'
CORE_API extern HINSTANCE GDedicatedServerMutex;
#else
CORE_API const TCHAR* appCmdLine();
CORE_API const TCHAR* appBaseDir();
CORE_API const TCHAR* appPackage();
CORE_API const TCHAR* appComputerName();
CORE_API const TCHAR* appUserName();
#endif

/*-----------------------------------------------------------------------------
	Timing functions.
-----------------------------------------------------------------------------*/

#if !DEFINED_appCycles
CORE_API DWORD appCycles();
#endif

#if !DEFINED_appSeconds
CORE_API DOUBLE appSeconds();
#endif

CORE_API void appSystemTime( INT& Year, INT& Month, INT& DayOfWeek, INT& Day, INT& Hour, INT& Min, INT& Sec, INT& MSec );
CORE_API const TCHAR* appTimestamp();
CORE_API DOUBLE appSecondsSlow();
CORE_API void __fastcall appSleep( FLOAT Seconds );

/*-----------------------------------------------------------------------------
	Character type functions.
-----------------------------------------------------------------------------*/

inline TCHAR appToUpper( TCHAR c )
{
	return (c<'a' || c>'z') ? (c) : (c+'A'-'a');
}
inline TCHAR appToLower( TCHAR c )
{
	return (c<'A' || c>'Z') ? (c) : (c+'a'-'A');
}
inline UBOOL appIsAlpha( TCHAR c )
{
	return (c>='a' && c<='z') || (c>='A' && c<='Z');
}
inline UBOOL appIsDigit( TCHAR c )
{
	return c>='0' && c<='9';
}
inline UBOOL appIsAlnum( TCHAR c )
{
	return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9');
}

/*-----------------------------------------------------------------------------
	String functions.
-----------------------------------------------------------------------------*/

#if DNF
#define appFromAnsi( Str ) ( *( FString( Str ) ) )
#define appFromUnicode( Str ) ( *( FString( Str ) ) )
#define appToUnicode( Str ) ( *( FString( Str ) ) )
#else
CORE_API const ANSICHAR* appToAnsi( const TCHAR* Str );
CORE_API const UNICHAR* appToUnicode( const TCHAR* Str );
CORE_API const TCHAR* appFromAnsi( const ANSICHAR* Str );
CORE_API const TCHAR* appFromUnicode( const UNICHAR* Str );
CORE_API UBOOL appIsPureAnsi( const TCHAR* Str );
#endif

#if DNF
#define appStrcpy wcscpy
#define appStrlen wcslen
#define appStrstr wcsstr
#define appStrchr wcschr
#define appStrcat wcscat
#define appStrcmp wcscmp
#define appStricmp wcsicmp
#define appStrncmp wcsncmp
#define appStrncpy wcsncpy
#define appStrncat wcsncat
#define appStrupr wcsupr
#define appAtoi _wtoi
#define appAtof _wtof
#define appStrtoi wcstol
#define appStrnicmp wcsnicmp
#define appSprintf( Buffer, Fmt, ... ) _sntprintf( Buffer, 1024, Fmt, __VA_ARGS__ )
const TCHAR* appSpc( int Num );
const TCHAR* appStrfind( const TCHAR* Str, const TCHAR* Find );
#else
CORE_API TCHAR* appStrcpy( TCHAR* Dest, const TCHAR* Src );
CORE_API INT appStrcpy( const TCHAR* String );
CORE_API INT appStrlen( const TCHAR* String );
CORE_API TCHAR* appStrstr( const TCHAR* String, const TCHAR* Find );
CORE_API TCHAR* appStrchr( const TCHAR* String, INT c );
CORE_API TCHAR* appStrcat( TCHAR* Dest, const TCHAR* Src );
CORE_API INT appStrcmp( const TCHAR* String1, const TCHAR* String2 );
CORE_API INT appStricmp( const TCHAR* String1, const TCHAR* String2 );
CORE_API INT appStrncmp( const TCHAR* String1, const TCHAR* String2, INT Count );
CORE_API TCHAR* appStaticString1024();
CORE_API ANSICHAR* appAnsiStaticString1024();

CORE_API const TCHAR* appSpc( int Num );
CORE_API TCHAR* appStrncpy( TCHAR* Dest, const TCHAR* Src, int Max);
CORE_API TCHAR* appStrncat( TCHAR* Dest, const TCHAR* Src, int Max);
CORE_API TCHAR* appStrupr( TCHAR* String );
CORE_API const TCHAR* appStrfind(const TCHAR* Str, const TCHAR* Find);
CORE_API INT appAtoi( const TCHAR* Str );
CORE_API FLOAT appAtof( const TCHAR* Str );
CORE_API INT appStrtoi( const TCHAR* Start, TCHAR** End, INT Base );
CORE_API INT appStrnicmp( const TCHAR* A, const TCHAR* B, INT Count );
CORE_API INT appSprintf( TCHAR* Dest, const TCHAR* Fmt, ... );
#endif

CORE_API DWORD appStrCrc(const TCHAR* Data);
CORE_API DWORD appStrCrcCaps(const TCHAR* Data);
 
#if UNICODE
	#define appSSCANF	swscanf
#else
	#define appSSCANF	scanf
#endif

#if _MSC_VER
	CORE_API INT appGetVarArgs( TCHAR* Dest, INT Count, const TCHAR*& Fmt );
#else
	#include <stdio.h>
	#include <stdarg.h>
#endif

typedef int QSORT_RETURN;
typedef QSORT_RETURN(CDECL* QSORT_COMPARE)( const void* A, const void* B );

#if DNF
#define appStrlwr wcslwr
#define appQsort qsort
#else
CORE_API TCHAR *appStrlwr(TCHAR *s);
CORE_API void appQsort( void* Base, INT Num, INT Width, QSORT_COMPARE Compare );
#endif

//
// Case insensitive string hash function.
//
inline DWORD appStrihash( const TCHAR* Data )
{
	DWORD Hash=0;
	while( *Data )
	{
		TCHAR Ch = appToUpper(*Data++);
		BYTE  B  = Ch;
		Hash     = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
#if UNICODE
		B        = Ch>>8;
		Hash     = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
#endif
	}
	return Hash;
}

/*-----------------------------------------------------------------------------
	Parsing functions.
-----------------------------------------------------------------------------*/

#if DNF
#define PARSE_API
#else
#define PARSE_API CORE_API
#endif

PARSE_API UBOOL ParseCommand( const TCHAR** Stream, const TCHAR* Match );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, class FName& Name );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, DWORD& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, class FGuid& Guid );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, TCHAR* Value, INT MaxLen );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, BYTE& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, SBYTE& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, _WORD& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, SWORD& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, FLOAT& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, INT& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, FString& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, QWORD& Value );
PARSE_API UBOOL Parse( const TCHAR* Stream, const TCHAR* Match, SQWORD& Value );
PARSE_API UBOOL ParseUBOOL( const TCHAR* Stream, const TCHAR* Match, UBOOL& OnOff );
PARSE_API UBOOL ParseObject( const TCHAR* Stream, const TCHAR* Match, class UClass* Type, class UObject*& DestRes, class UObject* InParent );
PARSE_API UBOOL ParseLine( const TCHAR** Stream, TCHAR* Result, INT MaxLen, UBOOL Exact=0 );
PARSE_API UBOOL ParseLine( const TCHAR** Stream, FString& Resultd, UBOOL Exact=0 );
PARSE_API UBOOL ParseToken( const TCHAR*& Str, TCHAR* Result, INT MaxLen, UBOOL UseEscape );
PARSE_API UBOOL ParseToken( const TCHAR*& Str, FString& Arg, UBOOL UseEscape );
PARSE_API FString ParseToken( const TCHAR*& Str, UBOOL UseEscape );
PARSE_API void ParseNext( const TCHAR** Stream );
PARSE_API UBOOL ParseParam( const TCHAR* Stream, const TCHAR* Param );

/*-----------------------------------------------------------------------------
	Math functions.
-----------------------------------------------------------------------------*/
#include <math.h>
#include <float.h>
#include <stdlib.h>

inline DOUBLE appExp( DOUBLE Value )
{
	return exp(Value);
}
inline DOUBLE appLoge( DOUBLE Value )
{
	return log(Value);
}
inline DOUBLE appFmod( DOUBLE Y, DOUBLE X )
{
	return fmod(Y,X);
}
inline DOUBLE appSin( DOUBLE Value )
{
	return sin(Value);
}
inline DOUBLE appCos( DOUBLE Value )
{
	return cos(Value);
}
inline DOUBLE appTan( DOUBLE Value )
{
	return tan(Value);
}
inline DOUBLE appAsin( DOUBLE Value )
{
	return asin(Value);
}
inline DOUBLE appAcos( DOUBLE Value )
{
	return acos(Value);
}
inline DOUBLE appAtan( DOUBLE Value )
{
	return atan(Value);
}
inline DOUBLE appAtan2( DOUBLE Y, DOUBLE X )
{
	return atan2(Y,X);
}
inline DOUBLE appPow( DOUBLE A, DOUBLE B )
{
	return pow(A,B);
}

inline UBOOL appIsNan( DOUBLE A )
{
#if _MSC_VER
	return _isnan(A)==1;
#else
	return isnan(A)==1;
#endif
}
inline void appSrand( DWORD seed )
{
	srand( seed );
}
inline INT appRand()
{
	return rand();
}
inline FLOAT appFrand()
{
	return rand() / (FLOAT)RAND_MAX;
}
__forceinline DOUBLE appSqrt( DOUBLE Value )
{
	return sqrt(Value);
}

#if !DEFINED_appRound
CORE_API INT appRound( FLOAT Value );
#endif

#define DEFINED_appFloor 1

inline INT appFloor( FLOAT F )
{
	static FLOAT Half=0.5f;
	INT I;
	__asm fld [F]
	__asm fsub [Half]
	__asm fistp [I]
	return I;
}

#if !DEFINED_appFloor
CORE_API INT appFloor( FLOAT Value );
#endif

#if !DEFINED_appCeil
CORE_API INT appCeil( FLOAT Value );
#endif

/*-----------------------------------------------------------------------------
	Array functions.
-----------------------------------------------------------------------------*/

// Core functions depending on TArray and FString.
CORE_API UBOOL appLoadFileToArray( TArray<BYTE>& Result, const TCHAR* Filename, FFileManager* FileManager=GFileManager );
CORE_API UBOOL appLoadFileToString( FString& Result, const TCHAR* Filename, FFileManager* FileManager=GFileManager );
CORE_API UBOOL appSaveArrayToFile( const TArray<BYTE>& Array, const TCHAR* Filename, FFileManager* FileManager=GFileManager );
CORE_API UBOOL appSaveStringToFile( const FString& String, const TCHAR* Filename, FFileManager* FileManager=GFileManager );

/*-----------------------------------------------------------------------------
	CDH: File mapping
-----------------------------------------------------------------------------*/

#if !DNF
struct FFileMapping
{
	void* FileHandle;
	void* MapHandle;
	void* Data;
};

CORE_API UBOOL appMapFileRead(FFileMapping& OutMapping, const TCHAR* Filename);
CORE_API UBOOL appUnmapFile(FFileMapping& InMapping);
#endif

/*-----------------------------------------------------------------------------
	Memory functions.
-----------------------------------------------------------------------------*/
#include <memory.h>	// NJS: Include memory related functions
#include <string.h>

CORE_API INT appMemcmp( const void* Buf1, const void* Buf2, INT Count );
CORE_API UBOOL appMemIsZero( const void* V, int Count );
CORE_API DWORD appMemCrc( const void* Data, INT Length, DWORD CRC=0 );
CORE_API void appMemswap( void* Ptr1, void* Ptr2, DWORD Size );

//inline void *appMemcpy(void *dest,const void *src,size_t count)  { return memcpy(dest,src,count); } 
inline void appMemcpy( void* Dest, const void* Src, INT Count )
{	
	__asm
	{
		mov		ecx, Count
		mov		esi, Src
		mov		edi, Dest
		mov     ebx, ecx
		shr     ecx, 2
		and     ebx, 3
		rep     movsd
		mov     ecx, ebx
		rep     movsb
	}
}

#define appMemmove								memmove
#define appMemset								memset
inline void appMemzero(void *dest,size_t count) { memset(dest,0,count); } 

//
// C style memory allocation stubs.
//
#define appMalloc     GMalloc->Malloc
#define appFree       GMalloc->Free
#define appRealloc    GMalloc->Realloc

//
// C++ style memory allocation.
//
inline void* operator new( unsigned int Size, const TCHAR* Tag )
{
#if DNF
	return appMalloc( Size, 8 );
#else
	return appMalloc( Size, Tag );
#endif
}
inline void* operator new( unsigned int Size )
{
#if DNF
	return appMalloc( Size, 8 );
#else
	return appMalloc( Size, TEXT("new") );
#endif
}
inline void operator delete( void* Ptr )
{
	appFree( Ptr );
}

// CDH... placement new
inline void* operator new(unsigned int Size, void* Ptr)
{
	return(Ptr);
}
#if _MSC_VER >= 1200
inline void operator delete(void*, void*)
{
}
#endif
// ...CDH

#if PLATFORM_NEEDS_ARRAY_NEW
inline void* operator new[]( unsigned int Size, const TCHAR* Tag )
{
#if DNF
	return appMalloc( Size, 8 );
#else
	return appMalloc( Size, Tag );
#endif
}
inline void* operator new[]( unsigned int Size )
{
#if DNF
	return appMalloc( Size, 8 );
#else
	return appMalloc( Size, TEXT("new") );
#endif
}
inline void operator delete[]( void* Ptr )
{
	appFree( Ptr );
}
#endif

/*-----------------------------------------------------------------------------
	Math.
-----------------------------------------------------------------------------*/

CORE_API BYTE appCeilLogTwo( DWORD Arg );

/*-----------------------------------------------------------------------------
	MD5 functions.
-----------------------------------------------------------------------------*/

//
// MD5 Context.
//
struct FMD5Context
{
	DWORD state[4];
	DWORD count[2];
	BYTE buffer[64];
};

//
// MD5 functions.
//!!it would be cool if these were implemented as subclasses of
// FArchive.
//
CORE_API void appMD5Init( FMD5Context* context );
CORE_API void appMD5Update( FMD5Context* context, BYTE* input, INT inputLen );
CORE_API void appMD5Final( BYTE* digest, FMD5Context* context );
CORE_API void appMD5Transform( DWORD* state, BYTE* block );
CORE_API void appMD5Encode( BYTE* output, DWORD* input, INT len );
CORE_API void appMD5Decode( DWORD* output, BYTE* input, INT len );

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
