/*=============================================================================
	Core.h: Unreal core public header file.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

	Revision history:
		* Created by Tim Sweeney
=============================================================================*/

#ifndef _INC_CORE
#define _INC_CORE

/*----------------------------------------------------------------------------
	Low level includes.
----------------------------------------------------------------------------*/

// API definition.
#ifndef CORE_API
#define CORE_API DLL_IMPORT
#endif

// Build options.
#include "UnBuild.h"

// Identifier remappings.
#if DNF
#include "dnRemap.h"
#endif

// Duke Nukem Forever.
#if DNF
#define IF_DNF(X) X
#define IFNDNF(X)
#define DNF_EXTERN_C_BEGIN extern "C" {
#define DNF_EXTERN_C_END }
#else
#define IF_DNF(X)
#define IFNDNF(X) X
#define DNF_EXTERN_C_BEGIN
#define DNF_EXTERN_C_END
#endif

// Compiler specific include.
#if _MSC_VER
	#if DNF
		#include "tchar.h"
	#endif
	#include "UnVcWin32.h"
#elif __GNUG__
	#include <string.h>
	#include "UnGnuG.h"
#else
	#error Unknown Compiler
#endif

// If no asm, redefine __asm to cause compile-time error.
#if !ASM && !__GNUG__
	#define __asm ERROR_ASM_NOT_ALLOWED
#endif

// OS specific include.
#if __UNIX__
	#include "UnUnix.h"
	#include <signal.h>
#endif

// Global constants.
enum {MAXBYTE		= 0xff       };
enum {MAXWORD		= 0xffffU    };
enum {MAXDWORD		= 0xffffffffU};
enum {MAXSBYTE		= 0x7f       };
enum {MAXSWORD		= 0x7fff     };
enum {MAXINT		= 0x7fffffff };
enum {INDEX_NONE	= -1         };
enum {UNICODE_BOM   = 0xfeff     };
enum ENoInit {E_NoInit = 0};

// Unicode or single byte character set mappings.
#ifdef _UNICODE
	#ifndef _TCHAR_DEFINED
		typedef UNICHAR  TCHAR;
		typedef UNICHARU TCHARU;
	#endif
	#undef TEXT
	#define TEXT(s) L##s
	#undef US
	#define US FString(L"")
	inline TCHAR    FromAnsi   ( ANSICHAR In ) { return (BYTE)In;                        }
	inline TCHAR    FromUnicode( UNICHAR In  ) { return In;                              }
	inline ANSICHAR ToAnsi     ( TCHAR In    ) { return (_WORD)In<0x100 ? In : MAXSBYTE; }
	inline UNICHAR  ToUnicode  ( TCHAR In    ) { return In;                              }
#else
	#ifndef _TCHAR_DEFINED
		typedef ANSICHAR  TCHAR;
		typedef ANSICHARU TCHARU;
	#endif
	#undef TEXT
	#define TEXT(s) s
	#undef US
	#define US FString("")
	inline TCHAR    FromAnsi   ( ANSICHAR In ) { return In;                              }
	inline TCHAR    FromUnicode( UNICHAR In  ) { return (_WORD)In<0x100 ? In : MAXSBYTE; }
	inline ANSICHAR ToAnsi     ( TCHAR In    ) { return (_WORD)In<0x100 ? In : MAXSBYTE; }
	inline UNICHAR  ToUnicode  ( TCHAR In    ) { return (BYTE)In;                        }
#endif

/*----------------------------------------------------------------------------
	Forward declarations.
----------------------------------------------------------------------------*/

// Objects.
class	UObject;
class		UExporter;
class		UFactory;
class		UField;
class			UConst;
class			UEnum;
class			UProperty;
class				UByteProperty;
class				UIntProperty;
class				UBoolProperty;
class				UFloatProperty;
class				UObjectProperty;
class					UClassProperty;
class				UNameProperty;
class				UStructProperty;
class               UStrProperty;
class               UArrayProperty;
class			UStruct;
class				UFunction;
class				UState;
class					UClass;
class		ULinker;
class			ULinkerLoad;
class			ULinkerSave;
class		UPackage;
class		USubsystem;
class			USystem;
class		UTextBuffer;
class       URenderDevice;
class		UPackageMap;

// Structs.
class FName;
class FArchive;
class FCompactIndex;
class FExec;
class FGuid;
class FMemCache;
class FMemStack;
class FPackageInfo;
class FTransactionBase;
class FUnknown;
class FRepLink;
class FArray;
class FLazyLoader;
class FString;
class FMalloc;

#if DNF
class FDnExec; // CDH
class FBitArray;
class dnLazyDataWorker;
#endif

// Templates.
template<class T> class TArray;
template<class T> class TTransArray;
template<class T> class TLazyArray;
template<class TK, class TI> class TMap;
template<class TK, class TI> class TMultiMap;

#if DNF
template<class TK, class TI> class dnMap;
template<class TK, class TI> class dnMultiMap;
#endif

// Globals.
CORE_API extern class FOutputDevice* GNull;

// EName definition.
#include "UnNames.h"

/*-----------------------------------------------------------------------------
	Abstract interfaces.
-----------------------------------------------------------------------------*/

// An output device.
class CORE_API FOutputDevice
{
public:
	// FOutputDevice interface.
	virtual void Serialize( const TCHAR* V, EName Event )=0;

	// Simple text printing.
	void Log( const TCHAR* S );
#if DNF
	void Log( const char * S );
#endif
	void Log( enum EName Type, const TCHAR* S );
	void Log( const FString& S );
	void Log( enum EName Type, const FString& S );
	void Logf( const TCHAR* Fmt, ... );
	void Logf( enum EName Type, const TCHAR* Fmt, ... );
#if DNF
	virtual void Flush() {}
	virtual void FlushRealtime() {}
	virtual void PrintfArgList( TCHAR* Buffer, size_t Size, const TCHAR* Fmt, va_list ArgList ) { _vstprintf(Buffer, Size, Fmt, ArgList); }
#endif
};

// Error device.
class CORE_API FOutputDeviceError : public FOutputDevice
{
public:
#if !DNF
	virtual void HandleError()=0;
#endif
};

// Memory allocator.
class CORE_API FMalloc
{
public:
#if DNF
	virtual void* Malloc( DWORD Count, DWORD ) { return Malloc( Count, NULL, NULL, -1 ); }
	virtual void* Realloc( void* Original, DWORD Count, DWORD ) { return Realloc( Original, Count, NULL, NULL, -1 ); }
#else
	virtual void* Malloc( DWORD Count, const TCHAR* Tag )=0;
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag )=0;
#endif
	virtual void Free( void* Original )=0;
#if DNF
	virtual void* Malloc( DWORD Count, const TCHAR* Tag, const TCHAR*, INT ) { return Malloc( Count, 8 ); }
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag, const TCHAR*, INT ) { return Realloc( Original, Count, 8 ); }
	virtual void ExternalMalloc( void*, INT, INT, bool ) {}
	virtual void ExternalFree( void*, INT, bool ) {}
	virtual INT MemSize() { return 0; }
	virtual void DumpAllocs() {}
	virtual void DumpHeap() {}
	virtual void DumpHeapSnapshot() {}
	virtual void DumpVirtualQueries() {}
	virtual void PushMemoryMode( enum dnMemoryMode ) {}
	virtual void PopMemoryMode() {}
	virtual dnMemoryMode GetMemoryMode() { return (dnMemoryMode)0; }
	virtual DWORD GetMemoryModeTotal( dnMemoryMode ) { return 0; }
	virtual INT* GetMemoryModeStats() { return NULL; }
	virtual void DisplayMemoryModeThreadStats() {}
	virtual bool VerifyMemory( void* ) { return true; }
	virtual void RecordMemory() {}
	virtual UBOOL GetRecordingMemory() { return 0; }
	virtual FLOAT GetFreeMB() { return 0; }
	virtual FLOAT GetFreeWithinMalloc() { return 0; }
	virtual INT GetAllocPaddingSize() { return 0; }
#else
	virtual void DumpAllocs()=0;
#endif
	virtual TCHAR* GetAllocsStats() { return TEXT("GetAllocsStats() not supported by this FMalloc implementation."); }
#if DNF
	virtual void DumpStats( dnOutputDevice* ) {}
	virtual FLOAT GetVirtualFragmentation() { return 0; }
	virtual FLOAT GetHeapFragmentation() { return 0; }
	virtual FLOAT GetFreeAvailableVirtualBlock() { return 0; }
	virtual FLOAT GetFreeAvailableHeapBlock() { return 0; }
	virtual void HeapCheck() {}
	virtual void UseDeltaStats( bool ) {}
	virtual void Init() {}
	virtual void Exit() {}
	virtual void OutOfMemory( DWORD ) {}
	virtual UBOOL Exec( const TCHAR*, dnOutputDevice& ) { return 0; }
	virtual void Tick( FLOAT ) {}
	virtual UBOOL IsInternallyThreadSafe() { return 0; }
	virtual void GetAllocationInfo( DWORD& Unknown1, DWORD& Unknown2 ) { Unknown1 = 0; Unknown2 = 0; }
	virtual void GetTotalAllocationInfo( INT&, FLOAT&, INT& ) {}
	virtual void CheckMemoryFragmentationLevel( dnOutputDevice& Ar ) { Ar.Log( TEXT("CheckMemoryFragmentationLevel not implemented") ); }
	virtual INT TrimMemory( DWORD, INT ) { return 0; }
#else
	virtual void HeapCheck()=0;
	virtual void Init()=0;
	virtual void Exit()=0;
#endif
};

// Configuration database cache.
class FConfigCache
{
public:
#if DNF
	virtual UBOOL GetFColor( const TCHAR* Section, const TCHAR* Key, BYTE& R, BYTE& G, BYTE& B, BYTE& A, const TCHAR* Filename=NULL )=0;
#endif
	virtual UBOOL GetBool( const TCHAR* Section, const TCHAR* Key, UBOOL& Value, const TCHAR* Filename=NULL )=0;
	virtual UBOOL GetInt( const TCHAR* Section, const TCHAR* Key, INT& Value, const TCHAR* Filename=NULL )=0;
	virtual UBOOL GetFloat( const TCHAR* Section, const TCHAR* Key, FLOAT& Value, const TCHAR* Filename=NULL )=0;
	virtual UBOOL GetString( const TCHAR* Section, const TCHAR* Key, TCHAR* Value, INT Size, const TCHAR* Filename=NULL )=0;
	virtual UBOOL GetString( const TCHAR* Section, const TCHAR* Key, class FString& Str, const TCHAR* Filename=NULL )=0;
#if DNF
	virtual const dnString GetStr( const TCHAR* Section, const TCHAR* Key, const TCHAR* Filename=NULL )=0;
#else
	virtual const TCHAR* GetStr( const TCHAR* Section, const TCHAR* Key, const TCHAR* Filename=NULL )=0;
#endif
	virtual UBOOL GetSection( const TCHAR* Section, TCHAR* Value, INT Size, const TCHAR* Filename=NULL )=0;
#if !DNF
	virtual TMultiMap<FString,FString>* GetSectionPrivate( const TCHAR* Section, UBOOL Force, UBOOL Const, const TCHAR* Filename=NULL )=0;
#endif
	virtual void EmptySection( const TCHAR* Section, const TCHAR* Filename=NULL )=0;
#if DNF
	virtual void SetFColor( const TCHAR* Section, const TCHAR* Key, BYTE R, BYTE G, BYTE B, BYTE A, const TCHAR* Filename=NULL )=0;
#endif
	virtual void SetBool( const TCHAR* Section, const TCHAR* Key, UBOOL Value, const TCHAR* Filename=NULL )=0;
	virtual void SetInt( const TCHAR* Section, const TCHAR* Key, INT Value, const TCHAR* Filename=NULL )=0;
	virtual void SetFloat( const TCHAR* Section, const TCHAR* Key, FLOAT Value, const TCHAR* Filename=NULL )=0;
	virtual void SetString( const TCHAR* Section, const TCHAR* Key, const TCHAR* Value, const TCHAR* Filename=NULL )=0;
#if DNF
	virtual TMultiMap<FString,FString>* GetSectionPrivate( const TCHAR* Section, UBOOL Force, UBOOL Const, const TCHAR* Filename=NULL )=0;
#endif
	virtual void Flush( UBOOL Read, const TCHAR* Filename=NULL )=0;
	virtual void Detach( const TCHAR* Filename )=0;
#if DNF
	virtual void Init( const TCHAR* InSystem, const TCHAR* InUser, const TCHAR* InProgress, UBOOL RequireConfig )=0;
#else
	virtual void Init( const TCHAR* InSystem, const TCHAR* InUser, UBOOL RequireConfig )=0;
#endif
	virtual void Exit()=0;
	virtual void Dump( FOutputDevice& Ar )=0;
#if DNF
	virtual void CoalesceFilesFromDisk( const TCHAR*, UBOOL )=0;
	virtual void LoadCoalescedLocalizationFile()=0;
	virtual TArray<FString> FindFiles( const TCHAR* Filename, UBOOL Files, UBOOL Directories, UBOOL SubDirectories, UBOOL Absolute )=0;
#endif
	virtual ~FConfigCache() {};
};

// Any object that is capable of taking commands.
class CORE_API FExec
{
public:
	virtual UBOOL Exec( const TCHAR* Cmd, FOutputDevice& Ar )=0;
};

// Notification hook.
class CORE_API FNotifyHook
{
public:
	virtual void NotifyDestroy( void* Src ) {}
	virtual void NotifyPreChange( void* Src ) {}
	virtual void NotifyPostChange( void* Src ) {}
	virtual void NotifyExec( void* Src, const TCHAR* Cmd ) {}
};

// Interface for returning a context string.
class FContextSupplier
{
public:
	virtual FString GetContext()=0;
};

// A context for displaying modal warning messages.
class CORE_API FFeedbackContext : public FOutputDevice
{
#if DNF
	DWORD Unknown1;
	DWORD Unknown2;
#endif
public:
	virtual UBOOL YesNof( const TCHAR* Fmt, ... )=0;
	virtual void BeginSlowTask( const TCHAR* Task, UBOOL StatusWindow, UBOOL Cancelable )=0;
	virtual void EndSlowTask()=0;
	virtual UBOOL VARARGS StatusUpdatef( INT Numerator, INT Denominator, const TCHAR* Fmt, ... )=0;
	virtual void SetContext( FContextSupplier* InSupplier )=0;
#if DNF
	virtual void MapCheck_Show() {};
	virtual void MapCheck_ShowConditionally() {};
	virtual void MapCheck_Clear() {};
	virtual void MapCheck_Add( enum DN_MAPCHECK_TYPE InError, void* InActor, const TCHAR* InMessage ) {};
	virtual void BrushCheck_Show() {};
	virtual void BrushCheck_Clear() {};
	virtual void BrushCheck_Add( DN_MAPCHECK_TYPE InError, void* InActor, const TCHAR* InMessage ) {};
#endif
};

// Class for handling undo/redo transactions among objects.
typedef void( *STRUCT_AR )( FArchive& Ar, void* TPtr );
typedef void( *STRUCT_DTOR )( void* TPtr );
class CORE_API FTransactionBase
{
public:
	virtual void SaveObject( UObject* Object )=0;
	virtual void SaveArray( UObject* Object, FArray* Array, INT Index, INT Count, INT Oper, INT ElementSize, STRUCT_AR Serializer, STRUCT_DTOR Destructor )=0;
	virtual void Apply()=0;
};

// File manager.
enum EFileTimes
{
	FILETIME_Create      = 0,
	FILETIME_LastAccess  = 1,
	FILETIME_LastWrite   = 2,
};
enum EFileWrite
{
	FILEWRITE_NoFail            = 0x01,
	FILEWRITE_NoReplaceExisting = 0x02,
	FILEWRITE_EvenIfReadOnly    = 0x04,
	FILEWRITE_Unbuffered        = 0x08,
	FILEWRITE_Append			= 0x10,
	FILEWRITE_AllowRead         = 0x20,
};
enum EFileRead
{
	FILEREAD_NoFail             = 0x01,
};
#if DNF
class dnDirectoryInfo
{
public:
	TCHAR Unknown1[1024];
	TCHAR Unknown2[1024];
};
#endif
class CORE_API FFileManager
{
public:
#if DNF
	virtual void PreInit() {}
	virtual void OpenLinearFile( const TCHAR*, INT, INT ) {}
	virtual void CloseLinearFile() {}
	virtual UBOOL IsLinearFileOpen() { return 0; }
	virtual dnArchive* CreateLinearReader( const TCHAR* Filename ) { return NULL; }
	virtual UBOOL FindPackageFile( const TCHAR* Filename, TCHAR* ) { return 0; }
#endif
	virtual FArchive* CreateFileReader( const TCHAR* Filename, DWORD ReadFlags=0, FOutputDevice* Error=GNull )=0;
	virtual FArchive* CreateFileWriter( const TCHAR* Filename, DWORD WriteFlags=0, FOutputDevice* Error=GNull )=0;
	virtual INT FileSize( const TCHAR* Filename )=0;
	virtual UBOOL Delete( const TCHAR* Filename, UBOOL RequireExists=0, UBOOL EvenReadOnly=0 )=0;
	virtual UBOOL Copy( const TCHAR* Dest, const TCHAR* Src, UBOOL Replace=1, UBOOL EvenIfReadOnly=0, UBOOL Attributes=0, void (*Progress)(FLOAT Fraction)=NULL )=0;
	virtual UBOOL Move( const TCHAR* Dest, const TCHAR* Src, UBOOL Replace=1, UBOOL EvenIfReadOnly=0, UBOOL Attributes=0 )=0;
	virtual SQWORD GetGlobalTime( const TCHAR* Filename )=0;
	virtual UBOOL SetGlobalTime( const TCHAR* Filename )=0;
	virtual UBOOL MakeDirectory( const TCHAR* Path, UBOOL Tree=0 )=0;
	virtual UBOOL DeleteDirectory( const TCHAR* Path, UBOOL RequireExists=0, UBOOL Tree=0 )=0;
#if DNF
	virtual TArray<FString> FindFiles( const TCHAR* Filename, UBOOL Files, UBOOL Directories, UBOOL SubDirectories=0, UBOOL Absolute=0 )=0;
#else
	virtual TArray<FString> FindFiles( const TCHAR* Filename, UBOOL Files, UBOOL Directories )=0;
#endif
	virtual UBOOL SetDefaultDirectory( const TCHAR* Filename )=0;
	virtual FString GetDefaultDirectory()=0;
#if DNF
	virtual void FindSubDirectories( TArray<dnDirectoryInfo>&, UBOOL Root=1 )=0;
#endif
};

/*----------------------------------------------------------------------------
	Global functions.
----------------------------------------------------------------------------*/

#if DNF
CORE_API FMalloc* GetMalloc();
CORE_API void SetMalloc( FMalloc* InMalloc );
#endif

/*----------------------------------------------------------------------------
	Global variables.
----------------------------------------------------------------------------*/

// Core globals.
CORE_API extern FMemStack				GMem;
CORE_API extern FOutputDevice*			GLog;
CORE_API extern FOutputDevice*			GNull;
CORE_API extern FOutputDevice*		    GThrow;
CORE_API extern FOutputDeviceError*		GError;
CORE_API extern FFeedbackContext*		GWarn;
CORE_API extern FConfigCache*			GConfig;
DNF_EXTERN_C_BEGIN
CORE_API extern FTransactionBase*		GUndo;
DNF_EXTERN_C_END
CORE_API extern FOutputDevice*			GLogHook;
CORE_API extern FExec*					GExec;
#if !DNF
CORE_API extern FMalloc*				GMalloc;
#endif
CORE_API extern FFileManager*			GFileManager;
CORE_API extern USystem*				GSys;
CORE_API extern UProperty*				GProperty;
CORE_API extern BYTE*					GPropAddr;
#if DNF
CORE_API extern UObject*				GPropObject;
CORE_API extern DWORD					GRuntimeUCFlags;
#endif
CORE_API extern USubsystem*				GWindowManager;
CORE_API extern TCHAR				    GErrorHist[4096];
DNF_EXTERN_C_BEGIN
#if DNF
CORE_API extern const TCHAR				GCmdLine[2048];
#endif
CORE_API extern TCHAR					GTrue[64], GFalse[64], GYes[64], GNo[64], GNone[64];
DNF_EXTERN_C_END
CORE_API extern TCHAR					GCdPath[];
DNF_EXTERN_C_BEGIN
CORE_API extern DOUBLE					GSecondsPerCycle;
DNF_EXTERN_C_END
CORE_API extern	DOUBLE					GTempDouble;
CORE_API extern void					(*GTempFunc)(void*);
CORE_API extern SQWORD					GTicks;
CORE_API extern INT                     GScriptCycles;
DNF_EXTERN_C_BEGIN
CORE_API extern DWORD					GPageSize;
CORE_API extern DWORD					GProcessorCount;
DNF_EXTERN_C_END
CORE_API extern DWORD					GPhysicalMemory;
CORE_API extern DWORD                   GUglyHackFlags;
CORE_API extern UBOOL					GIsScriptable;
DNF_EXTERN_C_BEGIN
CORE_API extern UBOOL					GIsEditor;
#if DNF
CORE_API extern UBOOL					GIsUCC;
CORE_API extern UBOOL					GIsGame;
#endif
CORE_API extern UBOOL					GIsClient;
CORE_API extern UBOOL					GIsServer;
CORE_API extern UBOOL					GIsCriticalError;
CORE_API extern UBOOL					GIsStarted;
CORE_API extern UBOOL					GIsRunning;
#if DNF
CORE_API extern UBOOL					GIsRunningInternal;
#endif
CORE_API extern UBOOL					GIsSlowTask;
DNF_EXTERN_C_END
CORE_API extern UBOOL					GIsGuarded;
DNF_EXTERN_C_BEGIN
CORE_API extern UBOOL					GIsRequestingExit;
DNF_EXTERN_C_END
CORE_API extern UBOOL					GIsStrict;
CORE_API extern UBOOL                   GScriptEntryTag;
DNF_EXTERN_C_BEGIN
CORE_API extern UBOOL					GLazyLoad;
CORE_API extern UBOOL					GUnicode;
CORE_API extern UBOOL					GUnicodeOS;
DNF_EXTERN_C_END
#if DNF
CORE_API extern FDnExec*				GDnExec; // CDH
CORE_API extern INT						GPreloadSize;
CORE_API extern INT						GTexturePreloadSize;
CORE_API extern DOUBLE					GPreloadSerializeTime;
DNF_EXTERN_C_BEGIN
CORE_API extern UBOOL					GIsWinXP;
CORE_API extern UBOOL					GIsHackConverting;
CORE_API extern UBOOL					g_UCCAllowDLCFiles;
DNF_EXTERN_C_END
#endif

CORE_API extern class FGlobalMath		GMath;
CORE_API extern	URenderDevice*			GRenderDevice;
CORE_API extern class FArchive*         GDummySave;
CORE_API extern DWORD					GCurrentViewport;

// Per module globals.
extern "C" DLL_EXPORT TCHAR GPackage[];

// Normal includes.
#include "UnFile.h"			// Low level utility code.
#include "UnObjVer.h"		// Object version info.
#include "UnArc.h"			// Archive class.
#include "UnTemplate.h"     // Dynamic arrays.
#include "UnName.h"			// Global name subsystem.
#include "UnStack.h"		// Script stack definition.
#include "UnObjBas.h"		// Object base class.
#include "UnCoreNet.h"		// Core networking.
#include "UnCorObj.h"		// Core object class definitions.
#include "UnClass.h"		// Class definition.
#include "UnType.h"			// Base property type.
#include "UnScript.h"		// Script class.
#include "UFactory.h"		// Factory definition.
#include "UExporter.h"		// Exporter definition.
#include "UnCache.h"		// Cache based memory management.
#include "UnMem.h"			// Stack based memory management.
#include "UnCId.h"          // Cache ID's.
#include "UnBits.h"         // Bitstream archiver.
#include "UnMath.h"         // Vector math functions.
#if DNF
#include "DnExec.h"			// CDH: DNF Exec extensions
#endif

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
#endif
