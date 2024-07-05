/*=============================================================================
	UnClass.h: UClass definition.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

	Revision history:
		* Created by Tim Sweeney.
		* NJS: Merged with UnClass.h to create additional optimization opportunities.
=============================================================================*/

/*-----------------------------------------------------------------------------
	Constants.
-----------------------------------------------------------------------------*/

// Boundary to align class properties on.
enum {PROPERTY_ALIGNMENT=4 };

/*-----------------------------------------------------------------------------
	FRepRecord.
-----------------------------------------------------------------------------*/

//
// Information about a property to replicate.
//
struct FRepRecord
{
	UProperty* Property;
	INT Index;
	FRepRecord(UProperty* InProperty,INT InIndex)
	: Property(InProperty), Index(InIndex)
	{}
};

/*-----------------------------------------------------------------------------
	FClassDependency.
	CDH: Altered how these work, the Deep member was meaningless and there
	     were other idiosyncracies with them.
-----------------------------------------------------------------------------*/

//
// One dependency record, for incremental compilation.
//
class CORE_API FClassDependency
{
public:
	// Variables.
	UClass*		Class;
	DWORD		ScriptTextCRC;

	// Functions.
	FClassDependency();
	FClassDependency( UClass* InClass );
	UBOOL IsUpToDate();
	CORE_API friend FArchive& operator<<( FArchive& Ar, FClassDependency& Dep );
};

/*-----------------------------------------------------------------------------
	FRepLink.
-----------------------------------------------------------------------------*/

//
// A tagged linked list of replicatable variables.
//
class FRepLink
{
public:
	UProperty*	Property;		// Replicated property.
	FRepLink*	Next;			// Next replicated link per class.
	FRepLink( UProperty* InProperty, FRepLink* InNext )
	:	Property	(InProperty)
	,	Next		(InNext)
	{}
};

/*-----------------------------------------------------------------------------
	FLabelEntry.
-----------------------------------------------------------------------------*/

//
// Entry in a state's label table.
//
struct CORE_API FLabelEntry
{
	// Variables.
	FName	Name;
	INT		iCode;

	// Functions.
	FLabelEntry( FName InName, INT iInCode );
	CORE_API friend FArchive& operator<<( FArchive& Ar, FLabelEntry &Label );
};

/*-----------------------------------------------------------------------------
	UField.
-----------------------------------------------------------------------------*/

#if !DNF
/*
	CDH: Property domain type
	Properties with different domains store their data in different locations.
	Normal properties store within the C++ object space, Unbounds are in an
	extension buffer hung off the object, and Statics are stored with the class.

    *** OBSOLETE *** Only use CPD_Normal
*/
enum EPropertyDomain
{
	CPD_Normal=0,		// normal instance property
	CPD_Unbound,		// unbound instance property (no C++ access, stored in object extension properties buffer)
	CPD_Static,			// static non-instance property
	CPD_MAX,

	CPD_FirstInstance=CPD_Normal,
	CPD_LastInstance=CPD_Unbound,
};
#endif

//
// Base class of UnrealScript language objects.
//
class CORE_API UField : public UObject
{
	DECLARE_ABSTRACT_CLASS(UField,UObject,0)
	NO_DEFAULT_CONSTRUCTOR(UField)

	// Constants.
	enum {HASH_COUNT = 256};

	// Variables.
	UField*			SuperField;
	UField*			Next;
	UField*			HashNext;
#if DNF
	void*			Unknown;
#endif

	// Constructors.
	UField( ENativeConstructor, UClass* InClass, const TCHAR* InName, const TCHAR* InPackageName, DWORD InFlags, UField* InSuperField );
	UField( UField* InSuperField );

	// UObject interface.
	void Serialize( FArchive& Ar );
	void PostLoad();
	void Register();

	// UField interface.
	virtual void AddCppProperty( UProperty* Property );
	virtual UBOOL MergeBools();
	virtual void Bind();
	virtual UClass* GetOwnerClass();
	virtual INT GetPropertiesSize();
};

/*-----------------------------------------------------------------------------
	TFieldIterator.
-----------------------------------------------------------------------------*/

//
// For iterating through a linked list of fields.
//
template <class T> class TFieldIterator
{
public:
	TFieldIterator( UStruct* InStruct )
	: Struct( InStruct )
	, Field( InStruct ? InStruct->Children : NULL )
	{
		IterateToNext();
	}
	operator UBOOL()
	{
		return Field != NULL;
	}
	void operator++()
	{
		checkSlow(Field);
		Field = Field->Next;
		IterateToNext();
	}
	T* operator*()
	{
		checkSlow(Field);
		return (T*)Field;
	}
	T* operator->()
	{
		checkSlow(Field);
		return (T*)Field;
	}
	UStruct* GetStruct()
	{
		return Struct;
	}
	void DumpAllFields(UStruct *Structo)
	{
		UField* Fieldo;
		

		while( Structo )
		{
			Fieldo=Structo->Children;

			while( Fieldo )
			{
				debugf(TEXT("Struct: %s, Field: %s"),*Structo->GetFName(),*Fieldo->GetFName());
				Fieldo = Fieldo->Next;
			}
			Structo = Structo->GetInheritanceSuper();
		}
	}
protected:
	__forceinline void IterateToNext()
	{
		while( Struct )
		{
			while( Field )
			{
				if( Field->IsA(T::StaticClass()) )
					return;
				Field = Field->Next;
			}
			Struct = Struct->GetInheritanceSuper();
			if( Struct )
				Field = Struct->Children;
		}
	}
	UStruct* Struct;
	UField* Field;
};

/*-----------------------------------------------------------------------------
	UStruct.
-----------------------------------------------------------------------------*/

//
// CDH: Struct flags
//
enum EStructFlags
{
	STRUCT_Native		= 0x00000001,	// struct is a native export
	STRUCT_IsUnion		= 0x00000002,	// struct is actually a union
	STRUCT_Exported		= 0x00000004,	// struct has been exported
};

//
// An UnrealScript structure definition.
//
class CORE_API UStruct : public UField
{
	DECLARE_CLASS(UStruct,UField,0)
	NO_DEFAULT_CONSTRUCTOR(UStruct)

	// Variables.
#if DNF
	BYTE				StructFlags;
#else
	DWORD				StructFlags; // CDH
#endif
	FName				StructCategory; // CDH: used for named categories for states/functions etc.
	UTextBuffer*		ScriptText;
#if DNF
	UObject*			Unknown1;
	UTextBuffer*		Unknwon2;
	TArray<UTextBuffer*>Unknown3;
#endif
	UField*				Children;
#if DNF
	INT					PropertiesSize;
#else
    INT					PropertiesSizes[CPD_MAX];
#endif
	FName				FriendlyName;
	TArray<BYTE>		Script;

	// Compiler info.
	INT					TextPos;
	INT					Line;

	// In memory only.
	UObjectProperty*	RefLink;
#if !DNF
	UStructProperty*	StructLink;
#endif
	UProperty*			PropertyLink;
	UProperty*			ConfigLink;
	UProperty*			ConstructorLink;

	// Constructors.
	UStruct( ENativeConstructor, INT InSize, const TCHAR* InName, const TCHAR* InPackageName, DWORD InFlags, UStruct* InSuperStruct );
	UStruct( UStruct* InSuperStruct );

	// UObject interface.
	void Serialize( FArchive& Ar );
	void PostLoad();
	void Destroy();
	void Register();

	// UField interface.
	void AddCppProperty( UProperty* Property );

	// UStruct interface.
	virtual UStruct* GetInheritanceSuper() {return GetSuperStruct();}
	virtual void Link( FArchive& Ar, UBOOL Props );
	virtual void SerializeBin( FArchive& Ar, BYTE* Data );
#if DNF
	virtual void SerializeTaggedProperties( FArchive& Ar, BYTE* Data, UClass* DefaultsClass, const TCHAR* const );
#else
	virtual void SerializeTaggedProperties( FArchive& Ar, BYTE* Data, UClass* DefaultsClass );
#endif
	virtual void CleanupDestroyed( BYTE* Data );
	virtual EExprToken SerializeExpr( INT& iCode, FArchive& Ar );
	__forceinline INT GetPropertiesSize()
	{
#if DNF
		return PropertiesSize;
#else
		return PropertiesSizes[CPD_Normal];
#endif
	}
	__forceinline DWORD GetScriptTextCRC()
	{
		return ScriptText ? appStrCrc(*ScriptText->Text) : 0;
	}
	__forceinline void SetPropertiesSize( INT NewSize )
	{
#if DNF
		PropertiesSize = NewSize;
#else
		PropertiesSizes[CPD_Normal] = NewSize;
#endif
	}
	__forceinline UBOOL IsChildOf( const UStruct* SomeBase ) const
	{
		for( const UStruct* Struct=this; Struct; Struct=Struct->GetSuperStruct() )
			if( Struct==SomeBase ) 
				return 1;
		return 0;
	}
	virtual TCHAR* GetNameCPP()
#if DNF
		;
#else
	{
		TCHAR* Result = appStaticString1024();
		appSprintf( Result, TEXT("F%s"), GetName() );
		return Result;
	}
#endif
	UStruct* GetSuperStruct() const
	{
		checkSlow(!SuperField||SuperField->IsA(UStruct::StaticClass()));
		return (UStruct*)SuperField;
	}
	UBOOL StructCompare( const void* A, const void* B );
};

/*-----------------------------------------------------------------------------
	UFunction.
-----------------------------------------------------------------------------*/

//
// Function flags.
//
enum EFunctionFlags
{
	// Function flags.
	FUNC_Final			= 0x00000001,	// Function is final (prebindable, non-overridable function).
	FUNC_Defined		= 0x00000002,	// Function has been defined (not just declared).
	FUNC_Iterator		= 0x00000004,	// Function is an iterator.
	FUNC_Latent		    = 0x00000008,	// Function is a latent state function.
	FUNC_PreOperator	= 0x00000010,	// Unary operator is a prefix operator.
	FUNC_Singular       = 0x00000020,   // Function cannot be reentered.
	FUNC_Net            = 0x00000040,   // Function is network-replicated.
	FUNC_NetReliable    = 0x00000080,   // Function should be sent reliably on the network.
	FUNC_Simulated		= 0x00000100,	// Function executed on the client side.
	FUNC_Exec		    = 0x00000200,	// Executable from command line.
	FUNC_Native			= 0x00000400,	// Native function.
	FUNC_Event          = 0x00000800,   // Event function.
	FUNC_Operator       = 0x00001000,   // Operator function.
	FUNC_Static         = 0x00002000,   // Static function.
	FUNC_NoExport       = 0x00004000,   // Don't export intrinsic function to C++.
	FUNC_Const          = 0x00008000,   // Function doesn't modify this object.
	FUNC_Invariant      = 0x00010000,   // Return value is purely dependent on parameters; no state dependencies or internal state changes.
	FUNC_Public			= 0x00020000,	// Function is accessible in all classes (if overridden, parameters much remain unchanged).
	FUNC_Private		= 0x00040000,	// Function is accessible only in the class it is defined in (cannot be overriden, but function name may be reused in subclasses.  IOW: if overridden, parameters don't need to match, and Super.Func() cannot be accessed since it's private.)
	FUNC_Protected		= 0x00080000,	// Function is accessible only in the class it is defined in and subclasses (if overridden, parameters much remain unchanged).
	FUNC_Multicast      = 0x00100000,   // Function is replicated to all clients for which the context actor is relevant
#if DNF
	FUNC_Indexed		= 0x00200000,
	FUNC_Delegate		= 0x00400000,	// Function is actually a delegate.
	FUNC_Cached			= 0x01000000,
	FUNC_Encrypted		= 0x02000000,
	FUNC_AnimEvent		= 0x04000000,	// Animation event function.
	FUNC_DevExec		= 0x20000000,	// Function is only executable from command line in development builds.
#endif

	// Combinations of flags.
	FUNC_FuncInherit        = FUNC_Exec | FUNC_Event,
	FUNC_FuncOverrideMatch	= FUNC_Exec | FUNC_Final | FUNC_Latent | FUNC_PreOperator | FUNC_Iterator | FUNC_Static | FUNC_Public | FUNC_Protected,
	FUNC_NetFuncFlags       = FUNC_Net | FUNC_NetReliable,
};

//
// An UnrealScript function.
//
#pragma warning(disable:4121) 
class CORE_API UFunction : public UStruct
{
	DECLARE_CLASS(UFunction,UStruct,0)
	DECLARE_WITHIN(UState)
	NO_DEFAULT_CONSTRUCTOR(UFunction)

	// Persistent variables.
	DWORD FunctionFlags;
	_WORD iNative;
	_WORD RepOffset;
	BYTE  OperPrecedence;

	// Variables in memory only.
	BYTE  NumParms;
	_WORD ParmsSize;
	_WORD ReturnValueOffset;
	void (__fastcall UObject::*Func)( FFrame& TheStack, RESULT_DECL );

#if DNF
	// NJS: Profiling stuff:
	DWORD ProfileCalls;
	__int64 ProfileCycles;
	__int64 ProfileChildrenCycles;
#endif

	// Constructors.
	UFunction( UFunction* InSuperFunction );

	// UObject interface.
	void Serialize( FArchive& Ar );
	void PostLoad();

	// UField interface.
	void Bind();

	// UStruct interface.
	UBOOL MergeBools() {return 0;}
	UStruct* GetInheritanceSuper() {return NULL;}
	void Link( FArchive& Ar, UBOOL Props );

	// UFunction interface.
	UFunction* GetSuperFunction() const
	{
		checkSlow(!SuperField||SuperField->IsA(UFunction::StaticClass()));
		return (UFunction*)SuperField;
	}
	UProperty* GetReturnProperty();
};
#pragma warning(default:4121)

/*-----------------------------------------------------------------------------
	UState.
-----------------------------------------------------------------------------*/

//
// State flags.
//
enum EStateFlags
{
	// State flags.
	STATE_Editable		= 0x00000001,	// State should be user-selectable in UnrealEd.
	STATE_Auto			= 0x00000002,	// State is automatic (the default state).
	STATE_Simulated     = 0x00000004,   // State executes on client side.
};

//
// An UnrealScript state.
//
class CORE_API UState : public UStruct
{
	DECLARE_CLASS(UState,UStruct,0)
	NO_DEFAULT_CONSTRUCTOR(UState)

	// Variables.
	QWORD ProbeMask;
	QWORD IgnoreMask;
	DWORD StateFlags;
	_WORD LabelTableOffset;
	UField* VfHash[HASH_COUNT];

	// Constructors.
	UState( ENativeConstructor, INT InSize, const TCHAR* InName, const TCHAR* InPackageName, DWORD InFlags, UState* InSuperState );
	UState( UState* InSuperState );

	// UObject interface.
	void Serialize( FArchive& Ar );
	void Destroy();

	// UStruct interface.
	UBOOL MergeBools() {return 1;}
	UStruct* GetInheritanceSuper() {return GetSuperState();}
	void Link( FArchive& Ar, UBOOL Props );

	// UState interface.
	UState* GetSuperState() const
	{
		checkSlow(!SuperField||SuperField->IsA(UState::StaticClass()));
		return (UState*)SuperField;
	}
};

/*-----------------------------------------------------------------------------
	UEnum.
-----------------------------------------------------------------------------*/

#if DNF
enum EEnumFlags
{
	ENUM_Native 		= 0x00000001,	// enum is a native export
};
#endif

//
// An enumeration, a list of names usable by UnrealScript.
//
class CORE_API UEnum : public UField
{
	DECLARE_CLASS(UEnum,UField,0)
	DECLARE_WITHIN(UStruct)
	NO_DEFAULT_CONSTRUCTOR(UEnum)

	// Variables.
	TArray<FName> Names;
#if DNF
	BYTE EnumFlags;
#endif

	// Constructors.
	UEnum( UEnum* InSuperEnum );

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UEnum interface.
	UEnum* GetSuperEnum() const
	{
		checkSlow(!SuperField||SuperField->IsA(UEnum::StaticClass()));
		return (UEnum*)SuperField;
	}
};

/*-----------------------------------------------------------------------------
	UClass.
-----------------------------------------------------------------------------*/

//
// An object class.
//
class CORE_API UClass : public UState
{
	DECLARE_CLASS(UClass,UState,0)
	DECLARE_WITHIN(UPackage)

	// Variables.
	DWORD				ClassFlags;
	INT					ClassUnique;
	FGuid				ClassGuid;
	UClass*				ClassWithin;
	FName				ClassConfigName;
	TArray<FRepRecord>	ClassReps;
	TArray<UField*>		NetFields;
	TArray<FClassDependency> Dependencies;
	TArray<FName>		PackageImports;
#if DNF
	TArray<FName>		Unknown1;
	TArray<FString>		Unknown2;
	TArray<BYTE>		Defaults;
#else
	TArray<BYTE>		Defaults[CPD_MAX];
#endif
	void(*ClassConstructor)(void*);
	void(UObject::*ClassStaticConstructor)();

	// In memory only.
	FString				DefaultPropText;
#if DNF
	DWORD				Unknown3;
	FBitArray			Unknown4;
#endif

	// Constructors.
	UClass();
	UClass( UClass* InSuperClass );
	UClass( ENativeConstructor, DWORD InSize, DWORD InClassFlags, UClass* InBaseClass, UClass* InWithinClass, FGuid InGuid, const TCHAR* InNameStr, const TCHAR* InPackageName, const TCHAR* InClassConfigName, DWORD InFlags, void(*InClassConstructor)(void*), void(UObject::*InClassStaticConstructor)() );

	// UObject interface.
	void Serialize( FArchive& Ar );
	void PostLoad();
	void Destroy();
	void Register();

	// UField interface.
	void Bind();

	// UStruct interface.
	UBOOL MergeBools() {return 1;}
	UStruct* GetInheritanceSuper() {return GetSuperClass();}
	TCHAR* GetNameCPP()
#if DNF
		;
#else
	{
		TCHAR* Result = appStaticString1024();
		UClass* C;
		for( C=this; C; C=C->GetSuperClass() )
			if( appStricmp(C->GetName(),TEXT("Actor"))==0 )
				break;
		appSprintf( Result, TEXT("%s%s"), C ? TEXT("A") : TEXT("U"), GetName() );
		return Result;
	}
#endif
	void Link( FArchive& Ar, UBOOL Props );

	// UClass interface.
	void AddDependency( UClass* InClass )
	{
		INT i;
		for( i=0; i<Dependencies.Num(); i++ )
			if( Dependencies(i).Class==InClass )
				break;
		if( i==Dependencies.Num() )
			new(Dependencies)FClassDependency( InClass );
	}
	UClass* GetSuperClass() const
	{
		return (UClass *)SuperField;
	}
    UObject* GetDefaultObject()
	{		
#if DNF
		check(Defaults.Num()==GetPropertiesSize());
		return (UObject*)&Defaults(0);
#else
		check(Defaults[CPD_Normal].Num()==GetPropertiesSize());
		return (UObject*)&Defaults[CPD_Normal](0);	
#endif
	}
	class AActor* GetDefaultActor()
	{
#if DNF
		check(Defaults.Num());
		return (AActor*)&Defaults(0);
#else
		check(Defaults[CPD_Normal].Num());
		return (AActor*)&Defaults[CPD_Normal](0);
#endif
	}
	
private:
	// Hide IsA because calling IsA on a class almost always indicates
	// an error where the caller should use IsChildOf.
	UBOOL IsA( UClass* Parent ) const {return UObject::IsA(Parent);}
};

/*-----------------------------------------------------------------------------
	UConst.
-----------------------------------------------------------------------------*/

#if DNF
enum EConstFlags
{
	CONST_Native 		= 0x00000001,	// const is a native export
};
#endif

//
// An UnrealScript constant.
//
class CORE_API UConst : public UField
{
	DECLARE_CLASS(UConst,UField,0)
	DECLARE_WITHIN(UStruct)
	NO_DEFAULT_CONSTRUCTOR(UConst)

	// Variables.
	FString Value;
#if DNF
	BYTE ConstFlags;
#endif

	// Constructors.
	UConst( UConst* InSuperConst, const TCHAR* InValue );

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UConst interface.
	UConst* GetSuperConst() const
	{
		checkSlow(!SuperField||SuperField->IsA(UConst::StaticClass()));
		return (UConst*)SuperField;
	}
};

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
