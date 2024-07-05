/*=============================================================================
	dnRemap.h: DNF identifier remappings.
=============================================================================*/

#ifndef _INC_DN_REMAP
#define _INC_DN_REMAP

/*----------------------------------------------------------------------------
	Classes.
----------------------------------------------------------------------------*/

#define FName					dnName
#define FNameEntry				dnNameEntry
#define FArchive				dnArchive
#define FArchiveFileReader		dnArchiveFileReader
#define FArchiveFileWriter		dnArchiveFileWriter
#define FCompactIndex			dnCompactIndex
#define FGuid					dnGUID
#define FMemStack				dnMemStack
#define FTransactionBase		dnTransactionBase
#define FArray					dnArrayBase
#define FLazyLoader				dnLazyLoader
#define FString					dnString
#define FStringNoInit			dnStringNoInit
#define TArray					dnArray
#define TTransArray				dnTransArray
#define TLazyArray				dnLazyArray
#define FOutputDevice			dnOutputDevice
#define FOutputDeviceError		dnOutputDeviceError
#define FStringOutputDevice		dnStringOutputDevice
#define FConfigCache			dnConfigCache
#define FContextSupplier		dnContextSupplier
#define FFeedbackContext		dnFeedbackContext
#define FFeedbackContextWindows	dnFeedbackContextWin32
#define FFileManager			dnFileMgr
#define FFileManagerGeneric		dnFileMgrGeneric
#define FFileManagerWindows		dnFileMgrWin32
#define TMapBase				dnMapBase

// TMap and TMultiMap are renamed to dnMap and dnMultiMap in DNF.
// New TMap and TMultiMap types are defined that inherit from the
// now-renamed originals. This is handled in UnTemplate.h instead
// of dnRemap.h to simplify the implementation.

/*----------------------------------------------------------------------------
	Functions.
----------------------------------------------------------------------------*/

#define winToANSI				dnWinToANSI
#define winGetSizeANSI			dnWinGetSizeANSI
#define winToUNICODE			dnWinToUNICODE
#define winGetSizeUNICODE		dnWinGetSizeUNICODE
#define appBaseDir				dnBaseDir
#define appPackage				dnPackage
#define appComputerName			dnComputerName
#define appUserName				dnUserName
#define appTimestamp			dnTimeStamp
#define appSecondsSlow			dnSecondsSlow
#define appLoadFileToArray		dnLoadFileToArray
#define appLoadFileToString		dnLoadFileToString
#define appSaveArrayToFile		dnSaveArrayToFile
#define appSaveStringToFile		dnSaveStringToFile

// FFileManager::*
#define GetDefaultDirectory		GetCurrentDirectory
#define SetDefaultDirectory		SetCurrentDirectory

/*----------------------------------------------------------------------------
	Globals.
----------------------------------------------------------------------------*/

// DNF replaces GMalloc with GetMalloc() and SetMalloc(FMalloc*).
// GMalloc is substituted with a GetMalloc() call here which should
// cover the majority of cases (setting GMalloc is much rarer).
#define GMalloc					(GetMalloc())

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
#endif
