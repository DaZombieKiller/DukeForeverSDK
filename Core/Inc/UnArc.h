/*=============================================================================
	UnArc.h: Unreal archive class.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

	Revision history:
		* Created by Tim Sweeney
=============================================================================*/

/*-----------------------------------------------------------------------------
	Archive.
-----------------------------------------------------------------------------*/

//
// Archive class. Used for loading, saving, and garbage collecting
// in a byte order neutral way.
//
class CORE_API FArchive
{
public:
	// FArchive interface.
	virtual ~FArchive()
	{}
	virtual void Serialize( void* V, INT Length )
	{}
	virtual void SerializeBits( void* V, INT LengthBits )
	{
		Serialize( V, (LengthBits+7)/8 );
		if( IsLoading() )
			((BYTE*)V)[LengthBits/8] &= ((1<<(LengthBits&7))-1);
	}
	virtual void SerializeInt( DWORD& Value, DWORD Max )
	{
		*this << *(DWORD*)Value;
	}
	virtual void Preload( UObject* Object )
	{}
	virtual void CountBytes( SIZE_T InNum, SIZE_T InMax )
	{}
#if DNF
	virtual void SetMode( INT )
	{}
#endif
	virtual FArchive& operator<<( class FName& N )
	{
		return *this;
	}
	virtual FArchive& operator<<( class UObject*& Res )
	{
		return *this;
	}
#if DNF
	virtual INT SerializeMaterial( class UMaterialEx*&, FName* )
	{
		return 0;
	}
#endif
	virtual INT MapName( FName* Name )
	{
		return 0;
	}
	virtual INT MapObject( UObject* Object )
	{
		return 0;
	}
	virtual INT Tell()
	{
		return INDEX_NONE;
	}
#if DNF
	virtual SQWORD Tell64()
	{
		return Tell();
	}
#endif
	virtual INT TotalSize()
	{
		return INDEX_NONE;
	}
#if DNF
	virtual DWORD LinearTell()
	{
		return 0;
	}
	virtual DWORD LinearTotalSize()
	{
		return 0;
	}
#endif
	virtual UBOOL AtEnd()
	{
		INT Pos = Tell();
		return Pos!=INDEX_NONE && Pos>=TotalSize();
	}
	virtual void Seek( INT InPos )
	{}
#if DNF
	virtual void Seek64( SQWORD InPos )
	{
		Seek( InPos );
	}
#endif
	virtual void AttachLazyLoader( FLazyLoader* LazyLoader )
	{}
	virtual void DetachLazyLoader( FLazyLoader* LazyLoader )
	{}
#if DNF
	virtual void AttachLazyDataWorker( dnLazyDataWorker* )
	{}
	virtual void DetachLazyDataWorker( dnLazyDataWorker* )
	{}
#endif
	virtual void Precache( INT HintCount )
	{}
	virtual void Flush()
	{}
	virtual UBOOL Close()
	{
		return !ArIsError;
	}
	virtual UBOOL GetError()
	{
		return ArIsError;
	}
#if DNF
	virtual void InitTOC( dnArchive* )
	{}
	virtual UBOOL HasTOC() const
	{
		return 0;
	}
	virtual BYTE* GetCurrentPtr()
	{
		return NULL;
	}
	virtual UBOOL Compress( BYTE**, DWORD& )
	{
		return 0;
	}
	virtual void Lock()
	{}
	virtual void UnLock()
	{}
	virtual enum dnLazyDataMode GetLazyDataMode()
	{
		return (dnLazyDataMode)0;
	}
	virtual void SetLazyDataMode( dnLazyDataMode )
	{}
	virtual void AddDeferredLazyItem( dnLazyDataWorker*, INT )
	{}
	virtual void FlushDeferredLazyItems()
	{}
	virtual void VerifyLinear( const TCHAR* )
	{}
#endif

	// Hardcoded datatype routines that may not be overridden.
	FArchive& ByteOrderSerialize( void* V, INT Length )
	{
#if __INTEL_BYTE_ORDER__
		Serialize( V, Length );
#else
		if( ArIsPersistent )
		{
			// Transferring between memory and file, so flip the byte order.
			for( INT i=Length-1; i>=0; i-- )
				Serialize( (BYTE*)V + i, 1 );
		}
		else
		{
			// Transferring around within memory, so keep the byte order.
			Serialize( V, Length );
		}
#endif
		return *this;
	}

	// Constructor.
	FArchive()
	:	ArVer			(PACKAGE_FILE_VERSION)
#if DNF
	,	ArLVer			(PACKAGE_FILE_VERSION_LICENSEE)
#endif
	,	ArNetVer		(ENGINE_NEGOTIATION_VERSION)
#if DNF
	,	ArMergeVer		(0)
#endif
	,	ArIsLoading		(0)
	,	ArIsSaving		(0)
	,   ArIsTrans		(0)
	,	ArIsPersistent  (0)
	,   ArIsError       (0)
	,	ArForEdit		(1)
	,	ArForClient		(1)
	,	ArForServer		(1)
	{}

	// Status accessors.
	INT Ver()				{return ArVer;}
	INT NetVer()			{return ArNetVer&0x7fffffff;}
#if DNF
	INT LVer()				{return ArLVer;}
	void SetVer(INT Ver)	{ArVer = Ver;}
	UBOOL IsTaggingUsed()	{return ArIsTaggingUsed;}
	UBOOL IsCompressor()	{return ArIsCompressor;}
	UBOOL IsUncompressor()	{return ArIsUncompressor;}
	UBOOL IsCriticalError()	{return ArIsCriticalError;}
#endif
	UBOOL IsLoading()		{return ArIsLoading;}
	UBOOL IsSaving()		{return ArIsSaving;}
	UBOOL IsTrans()			{return ArIsTrans;}
	UBOOL IsNet()			{return (ArNetVer&0x80000000)!=0;}
	UBOOL IsPersistent()    {return ArIsPersistent;}
	UBOOL IsError()         {return ArIsError;}
	UBOOL ForEdit()			{return ArForEdit;}
	UBOOL ForClient()		{return ArForClient;}
	UBOOL ForServer()		{return ArForServer;}

	// Friend archivers.
	friend FArchive& operator<<( FArchive& Ar, ANSICHAR& C )
	{
		Ar.Serialize( &C, 1 );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, BYTE& B )
	{
		Ar.Serialize( &B, 1 );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, SBYTE& B )
	{
		Ar.Serialize( &B, 1 );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, _WORD& W )
	{
		Ar.ByteOrderSerialize( &W, sizeof(W) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, SWORD& S )
	{
		Ar.ByteOrderSerialize( &S, sizeof(S) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, DWORD& D )
	{
		Ar.ByteOrderSerialize( &D, sizeof(D) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, INT& I )
	{
		Ar.ByteOrderSerialize( &I, sizeof(I) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, FLOAT& F )
	{
		Ar.ByteOrderSerialize( &F, sizeof(F) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, DOUBLE& F )
	{
		Ar.ByteOrderSerialize( &F, sizeof(F) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive &Ar, QWORD& Q )
	{
		Ar.ByteOrderSerialize( &Q, sizeof(Q) );
		return Ar;
	}
	friend FArchive& operator<<( FArchive& Ar, SQWORD& S )
	{
		Ar.ByteOrderSerialize( &S, sizeof(S) );
		return Ar;
	}

protected:
	// Status variables.
	INT ArVer;
#if DNF
	INT ArLVer;
#endif
	INT ArNetVer;
#if DNF
	INT ArMergeVer;
	BITFIELD ArIsLoading : 1;
	BITFIELD ArIsSaving : 1;
	BITFIELD ArIsTaggingUsed : 1;
	BITFIELD ArIsTrans : 1;
	BITFIELD ArIsPersistent : 1;
	BITFIELD ArForEdit : 1;
	BITFIELD ArForClient : 1;
	BITFIELD ArForServer : 1;
	BITFIELD ArIsError : 1;
	BITFIELD ArIsCriticalError : 1;
	BITFIELD ArIsUncompressor : 1;
	BITFIELD ArIsCompressor : 1;
#else
	UBOOL ArIsLoading;
	UBOOL ArIsSaving;
	UBOOL ArIsTrans;
	UBOOL ArIsPersistent;
	UBOOL ArForEdit;
	UBOOL ArForClient;
	UBOOL ArForServer;
	UBOOL ArIsError;
#endif
};

/*-----------------------------------------------------------------------------
	FArchive macros.
-----------------------------------------------------------------------------*/

//
// Class for serializing objects in a compactly, mapping small values
// to fewer bytes.
//
class CORE_API FCompactIndex
{
public:
	INT Value;
	CORE_API friend FArchive& operator<<( FArchive& Ar, FCompactIndex& I );
};

//
// Archive constructor.
//
template <class T> T Arctor( FArchive& Ar )
{
	T Tmp;
	Ar << Tmp;
	return Tmp;
}

// Macro to serialize an integer as a compact index.
#define AR_INDEX(intref) \
	(*(FCompactIndex*)&(intref))

/*----------------------------------------------------------------------------
	The End.
----------------------------------------------------------------------------*/
