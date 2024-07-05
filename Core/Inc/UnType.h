/*=============================================================================
	UnType.h: Unreal engine base type definitions.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

/*-----------------------------------------------------------------------------
	UProperty.
-----------------------------------------------------------------------------*/

// Property exporting flags.
enum EPropertyPortFlags
{
	PPF_Localized = 1,
	PPF_Delimited = 2,
};

//
// An UnrealScript variable.
//
class CORE_API UProperty : public UField
{
public:
    INT         Offset;

	DECLARE_ABSTRACT_CLASS(UProperty,UField,0)
	DECLARE_WITHIN(UField)

	// Persistent variables.
#if DNF
	_WORD		ArrayDim;
	_WORD		ElementSize;
#else
	INT			ArrayDim;
	INT			ElementSize;
#endif
	DWORD		PropertyFlags;
#if DNF
	DWORD		Unknown1;
#endif
	FName		Category;
	_WORD		RepOffset;
	FString		CommentString; // CDH: comment or description string if desired

	// In memory variables.
	_WORD		RepIndex;
#if DNF
	DWORD		Unknown2;
#endif
	UProperty*	PropertyLinkNext;
	UProperty*	ConfigLinkNext;
	UProperty*	ConstructorLinkNext;
#if DNF
	DWORD		Unknown3;
#endif
	UProperty*	RepOwner;

	// Constructors.
	UProperty();
	UProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags );

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
#if DNF
	virtual void CleanupDestroyed( BYTE* Data ) {}
#endif
	virtual void Link( FArchive& Ar, UProperty* Prev );
	virtual UBOOL Identical( const void* A, const void* B ) const=0;
	virtual void ExportCpp( FOutputDevice& Out, UBOOL IsLocal, UBOOL IsParm ) const;
	virtual void ExportCppItem( FOutputDevice& Out ) const=0;
	virtual void SerializeItem( FArchive& Ar, void* Value ) const=0;
	virtual UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	virtual void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const=0;
	virtual const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const=0;
	virtual UBOOL ExportText( INT ArrayElement, TCHAR* ValueStr, BYTE* Data, BYTE* Delta, INT PortFlags ) const;
	virtual void CopySingleValue( void* Dest, void* Src ) const;
	virtual void CopyCompleteValue( void* Dest, void* Src ) const;
	virtual void DestroyValue( void* Dest ) const;
	virtual UBOOL Port() const;
	virtual BYTE GetID() const;
#if DNF
	virtual UBOOL ShouldRefLink() const=0;
#endif

	// Inlines.
    INT GetOffset() const
    {
        return Offset;
    }
    INT GetElementOffset(INT Index) const
	{
		return(Offset + Index*ElementSize);
	}
	UBOOL Matches( const void* A, const void* B, INT ArrayIndex ) const
	{
		INT Ofs = Offset + ArrayIndex * ElementSize;
		return Identical( (BYTE*)A + Ofs, B ? (BYTE*)B + Ofs : NULL );
	}
	INT GetSize() const
	{
		return ArrayDim * ElementSize;
	}
	UBOOL ShouldSerializeValue( FArchive& Ar ) const
	{
		UBOOL Skip
		=	((PropertyFlags & CPF_Native   )                      )
		||	((PropertyFlags & CPF_Transient) && Ar.IsPersistent() );
		return !Skip;
	}
};

/*-----------------------------------------------------------------------------
	UByteProperty.
-----------------------------------------------------------------------------*/

//
// Describes an unsigned byte value or 255-value enumeration variable.
//
class CORE_API UByteProperty : public UProperty
{
	DECLARE_CLASS(UByteProperty,UProperty,0)

	// Variables.
	UEnum* Enum;

	// Constructors.
	UByteProperty()
	{}
	UByteProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags, UEnum* InEnum=NULL )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	,	Enum( InEnum )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UIntProperty.
-----------------------------------------------------------------------------*/

//
// Describes a 32-bit signed integer variable.
//
class CORE_API UIntProperty : public UProperty
{
	DECLARE_CLASS(UIntProperty,UProperty,0)

	// Constructors.
	UIntProperty()
	{}
	UIntProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

#if DNF
/*-----------------------------------------------------------------------------
	UPointerProperty.
-----------------------------------------------------------------------------*/

class CORE_API UPointerProperty : public UProperty
{
	DECLARE_CLASS(UPointerProperty,UProperty,0)

	// Variables.
	FName PointerType;

	// Constructors.
	UPointerProperty()
	{}
	UPointerProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UProperty Interface
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
	UBOOL ShouldRefLink() const;
};
#endif

/*-----------------------------------------------------------------------------
	UBoolProperty.
-----------------------------------------------------------------------------*/

//
// Describes a single bit flag variable residing in a 32-bit unsigned double word.
//
class CORE_API UBoolProperty : public UProperty
{
	DECLARE_CLASS(UBoolProperty,UProperty,0)

	// Variables.
	BITFIELD BitMask;

	// Constructors.
	UBoolProperty()
	{}
	UBoolProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	,	BitMask( 1 )
	{}
	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UFloatProperty.
-----------------------------------------------------------------------------*/

//
// Describes an IEEE 32-bit floating point variable.
//
class CORE_API UFloatProperty : public UProperty
{
	DECLARE_CLASS(UFloatProperty,UProperty,0)

	// Constructors.
	UFloatProperty()
	{}
	UFloatProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UObjectProperty.
-----------------------------------------------------------------------------*/

//
// Describes a reference variable to another object which may be nil.
//
class CORE_API UObjectProperty : public UProperty
{
	DECLARE_CLASS(UObjectProperty,UProperty,0)

	// Variables.
	class UClass* PropertyClass;
	UObjectProperty* NextReference;

	// Constructors.
	UObjectProperty()
	{}
	UObjectProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags, UClass* InClass )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	,	PropertyClass( InClass )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UObjectProperty.
-----------------------------------------------------------------------------*/

//
// Describes a reference variable to another object which may be nil.
//
class CORE_API UClassProperty : public UObjectProperty
{
	DECLARE_CLASS(UClassProperty,UObjectProperty,0)

	// Variables.
	class UClass* MetaClass;

	// Constructors.
	UClassProperty()
	{}
	UClassProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags, UClass* InMetaClass )
	:	UObjectProperty( EC_CppProperty, InOffset, InCategory, InFlags, UClass::StaticClass() )
	,	MetaClass( InMetaClass )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	BYTE GetID() const
	{
		return NAME_ObjectProperty;
	}
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UNameProperty.
-----------------------------------------------------------------------------*/

//
// Describes a name variable pointing into the global name table.
//
class CORE_API UNameProperty : public UProperty
{
	DECLARE_CLASS(UNameProperty,UProperty,0)

	// Variables
	FName NameOptionNameA, NameOptionNameB; // CDH: various uses based on property flags
	UObject* NameOptionObjectA, *NameOptionObjectB; // CDH: various uses based on property flags

	// Constructors.
	UNameProperty()
	{}
	UNameProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	,	NameOptionNameA(NAME_None), NameOptionNameB(NAME_None)
	,	NameOptionObjectA(NULL), NameOptionObjectB(NULL)
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UStrProperty.
-----------------------------------------------------------------------------*/

//
// Describes a dynamic string variable.
//
class CORE_API UStrProperty : public UProperty
{
	DECLARE_CLASS(UStrProperty,UProperty,0)

	// Constructors.
	UStrProperty()
	{}
	UStrProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void DestroyValue( void* Dest ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

/*-----------------------------------------------------------------------------
	UFixedArrayProperty.
-----------------------------------------------------------------------------*/

//
// Describes a fixed length array.
//
class CORE_API UFixedArrayProperty : public UProperty
{
	DECLARE_CLASS(UFixedArrayProperty,UProperty,0)

	// Variables.
	UProperty* Inner;
	INT Count;

	// Constructors.
	UFixedArrayProperty()
	{}
	UFixedArrayProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void DestroyValue( void* Dest ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif

	// UFixedArrayProperty interface.
	void AddCppProperty( UProperty* Property, INT Count );
};

/*-----------------------------------------------------------------------------
	UArrayProperty.
-----------------------------------------------------------------------------*/

//
// Describes a dynamic array.
//
class CORE_API UArrayProperty : public UProperty
{
	DECLARE_CLASS(UArrayProperty,UProperty,0)

	// Variables.
	UProperty* Inner;

	// Constructors.
	UArrayProperty()
	{}
	UArrayProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void DestroyValue( void* Dest ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif

	// UArrayProperty interface.
	void AddCppProperty( UProperty* Property );
};

#if !DNF
/*-----------------------------------------------------------------------------
	UMapProperty.
-----------------------------------------------------------------------------*/

//
// Describes a dynamic map.
//
class CORE_API UMapProperty : public UProperty
{
	DECLARE_CLASS(UMapProperty,UProperty,0)

	// Variables.
	UProperty* Key;
	UProperty* Value;

	// Constructors.
	UMapProperty()
	{}
	UMapProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void DestroyValue( void* Dest ) const;
};
#endif

/*-----------------------------------------------------------------------------
	UStructProperty.
-----------------------------------------------------------------------------*/

//
// Describes a structure variable embedded in (as opposed to referenced by) 
// an object.
//
class CORE_API UStructProperty : public UProperty
{
	DECLARE_CLASS(UStructProperty,UProperty,0)

	// Variables.
	class UStruct* Struct;
	UStructProperty* NextStruct;

	// Constructors.
	UStructProperty()
	{}
	UStructProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags, UStruct* InStruct )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	,	Struct( InStruct )
	{}

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UProperty interface.
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void DestroyValue( void* Dest ) const;
#if DNF
	UBOOL ShouldRefLink() const;
#endif
};

#if DNF
/*-----------------------------------------------------------------------------
	UDelegateProperty.
-----------------------------------------------------------------------------*/

class CORE_API UDelegateProperty : public UProperty
{
	DECLARE_CLASS(UDelegateProperty,UProperty,0)

	// Variables.
	UFunction* Function;

	// Constructors.
	UDelegateProperty()
	{}
	UDelegateProperty( ECppProperty, INT InOffset, const TCHAR* InCategory, DWORD InFlags )
	:	UProperty( EC_CppProperty, InOffset, InCategory, InFlags )
	{}

	// UProperty Interface
	void Link( FArchive& Ar, UProperty* Prev );
	UBOOL Identical( const void* A, const void* B ) const;
	void SerializeItem( FArchive& Ar, void* Value ) const;
	UBOOL NetSerializeItem( FArchive& Ar, UPackageMap* Map, void* Data ) const;
	void ExportCppItem( FOutputDevice& Out ) const;
	void ExportTextItem( TCHAR* ValueStr, BYTE* PropertyValue, BYTE* DefaultValue, INT PortFlags ) const;
	const TCHAR* ImportText( const TCHAR* Buffer, BYTE* Data, INT PortFlags ) const;
	void CopySingleValue( void* Dest, void* Src ) const;
	void CopyCompleteValue( void* Dest, void* Src ) const;
	UBOOL ShouldRefLink() const;
};
#endif

/*-----------------------------------------------------------------------------
	Field templates.
-----------------------------------------------------------------------------*/

//
// Find a typed field in a struct.
//
template <class T> T* FindField( UStruct* Owner, const TCHAR* FieldName )
{
	for( TFieldIterator<T>It( Owner ); It; ++It )
		if( appStricmp( It->GetName(), FieldName )==0 )
			return *It;
	return NULL;
}

/*-----------------------------------------------------------------------------
	UObject accessors that depend on UClass.
-----------------------------------------------------------------------------*/


//
// See if this object belongs to the specified class.
//

UBOOL __forceinline UObject::IsA( class UClass* SomeBase ) const
{
	for( UClass* TempClass=Class; TempClass; TempClass=(UClass*)TempClass->SuperField )
		if( TempClass==SomeBase )
			return 1;

	return SomeBase==NULL;
}

//
// See if this object is in a certain package.
//
inline UBOOL UObject::IsIn( class UObject* SomeOuter ) const
{
	for( UObject* It=GetOuter(); It; It=It->GetOuter() )
		if( It==SomeOuter )
			return 1;
	return SomeOuter==NULL;
}

//
// Return whether an object wants to receive a named probe message.
//
inline UBOOL UObject::IsProbing( FName ProbeName )
{
	return	(ProbeName.GetIndex() <  NAME_PROBEMIN)
	||		(ProbeName.GetIndex() >= NAME_PROBEMAX)
	||		(!StateFrame)
	||		(StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
}

/*-----------------------------------------------------------------------------
	UStruct inlines.
-----------------------------------------------------------------------------*/

//
// UStruct inline comparer.
//
__forceinline UBOOL UStruct::StructCompare( const void* A, const void* B )
{
	for( TFieldIterator<UProperty> It(this); It; ++It )
		for( INT i=0; i<It->ArrayDim; i++ )
			if( !It->Matches(A,B,i) )
				return 0;
	return 1;
}

/*-----------------------------------------------------------------------------
	C++ property macros.
-----------------------------------------------------------------------------*/

#define CPP_PROPERTY(name) \
	EC_CppProperty, (BYTE*)&((ThisClass*)NULL)->name - (BYTE*)NULL

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/


