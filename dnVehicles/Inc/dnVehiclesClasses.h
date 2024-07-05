/*===========================================================================
    C++ class definitions exported from UnrealScript.
    This is automatically generated by the tools.
    DO NOT modify this manually! Edit the corresponding .uc files instead!
    If you even *think* about it, the engine will *know* and will come looking
    to devour your soul. You don't want to make it angry. Trust me.
===========================================================================*/
#if _MSC_VER
#pragma warning(disable:4121)
#elif defined PS3
#pragma ms_struct on
#endif
#pragma pack (push,4)

#ifndef DNVEHICLES_API
#define DNVEHICLES_API DLL_IMPORT
#endif

#ifndef NAMES_ONLY
#define AUTOGENERATE_NAME(name) extern DNVEHICLES_API FName DNVEHICLES_##name;
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#endif

AUTOGENERATE_NAME(DoSplatter)
AUTOGENERATE_NAME(CanAccelerateForwards)
AUTOGENERATE_NAME(CanAccelerateReverse)
AUTOGENERATE_NAME(PlayEngineSound)
AUTOGENERATE_NAME(DoLandingEffects)
AUTOGENERATE_NAME(GetGroundMaterialInfo)
AUTOGENERATE_NAME(ContactedGround)
AUTOGENERATE_NAME(UncontactedGround)

#ifndef NAMES_ONLY


//***************************************************************************//
/*	\class AVehicle_MeqonWheeled
*/
//***************************************************************************//


struct AVehicle_MeqonWheeled_eventCanAccelerateReverse_Parms
{
    BITFIELD ReturnValue;
};

struct AVehicle_MeqonWheeled_eventCanAccelerateForwards_Parms
{
    BITFIELD ReturnValue;
};
class DNVEHICLES_API AVehicle_MeqonWheeled : public AVehicleBase
{
public:
    FLOAT NeutralSteeringAdjust;
    FRotator SteerMaxAngles;
    FLOAT BrakeTorque;
    FLOAT NeutralBrakeTorque;
    FLOAT NoDriverBrakeTorque;
    FLOAT HandbrakeTorque;
    FLOAT VehicleMinNeutralTransitionTime;
    FLOAT MinDirectionalChangeSteerAlpha;
    dnArray<class UVehicleComponent*> VehicleComponents;
    dnArray<class UVWheel*> VWheels;
    FLOAT KLinearToleranceScale;
    FLOAT KAngularToleranceScale;
    INT KMaximumIterations;
    FName EnableDriveTrainTag;
    FName DisableDriveTrainTag;
    FLOAT LowFriction;
    FLOAT HighFriction;
    FLOAT LowSpeed;
    FLOAT LowSpeedBrakeTorque;
    FLOAT LowSpeedPct;
    FLOAT HighSpeed;
    FLOAT HighSpeedSteerPct;
    FLOAT HandbrakeActive;
    FLOAT SavedDisableThreshold;
    FLOAT AverageSteerAngle;
    FLOAT SteerAlpha;
    class UClass* WheelMaterialType;
    BYTE WheelMassType;
    FLOAT WheelSkidMinTime;
    INT WheelSkidDBIndex;
    FSPhysicsSoundOverride* WheelSkidOverrideEntry;
    FLOAT WheelSkidStartTime;
    BITFIELD bAdjustWheelFrictionForSlope:1 GCC_PACK(4);
    FLOAT FullTractionAngle GCC_PACK(4);
    FLOAT NoTractionAngle;
    DECLARE_FUNCTION(execAccelerator_NeutralNative);
    DECLARE_FUNCTION(execUpdateAverageSteeringAngle);
    DECLARE_FUNCTION(execHeading_NeutralNative);
    inline BITFIELD __fastcall eventCanAccelerateReverse()
    {
        AVehicle_MeqonWheeled_eventCanAccelerateReverse_Parms Parms;
        Parms.ReturnValue=0;
        ProcessEvent(FindFunctionChecked(DNVEHICLES_CanAccelerateReverse), &Parms);
        return Parms.ReturnValue;
    }
    inline BITFIELD __fastcall eventCanAccelerateForwards()
    {
        AVehicle_MeqonWheeled_eventCanAccelerateForwards_Parms Parms;
        Parms.ReturnValue=0;
        ProcessEvent(FindFunctionChecked(DNVEHICLES_CanAccelerateForwards), &Parms);
        return Parms.ReturnValue;
    }
    DECLARE_CLASS(AVehicle_MeqonWheeled,AVehicleBase,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR_START(AVehicle_MeqonWheeled)
    NO_DEFAULT_CONSTRUCTOR_INIT(VehicleComponents)
    NO_DEFAULT_CONSTRUCTOR_INITLAST(VWheels)
};
// Class Vehicle_MeqonWheeled exported:
//   Properties size: 164 bytes (3540 total)


//***************************************************************************//
/*	\class AVehicle_MeqonWheeled_CarLike
*/
//***************************************************************************//

class DNVEHICLES_API AVehicle_MeqonWheeled_CarLike : public AVehicle_MeqonWheeled
{
public:
    dnArray<FSCarWheelAxle> Axles;
    DECLARE_CLASS(AVehicle_MeqonWheeled_CarLike,AVehicle_MeqonWheeled,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR_START(AVehicle_MeqonWheeled_CarLike)
    NO_DEFAULT_CONSTRUCTOR_INITLAST(Axles)
};
// Class Vehicle_MeqonWheeled_CarLike exported:
//   Properties size: 12 bytes (3552 total)


//***************************************************************************//
/*	\class AVeh_CarTemplate
*/
//***************************************************************************//


struct AVeh_CarTemplate_eventPlayEngineSound_Parms
{
    FName EngineSoundName;
    BITFIELD bStopLast;
    BYTE StopSoundRule;
    FLOAT FadeOutTime;
};
class DNVEHICLES_API AVeh_CarTemplate : public AVehicle_MeqonWheeled_CarLike
{
public:
    FSCarWheelAxle FrontAxle;
    FSCarWheelAxle RearAxle;
    FLOAT FrontRearDifferential;
    FLOAT FrontRearDifferentialLock;
    FName EngineStartSoundName;
    FName EngineStopSoundName;
    dnArray<FSVehicleGearSounds> GearSounds;
    FLOAT EngineSoundVolume;
    FLOAT MinRPMPitchAdjust;
    FLOAT MaxRPMPitchAdjust;
    FLOAT BoostPitchAdjust;
    FLOAT InAirPitchAdjust;
    FVector EngineSoundOffset;
    FLOAT PitchAdjust;
    FLOAT PitchAdjustRate;
    FSVehiclePhysicsAxleProperties AxleProps;
    FSVehiclePhysicsGearboxProperties GearboxProps;
    FSVehiclePhysicsAxleProperties MotorAxleProps;
    FSVehiclePhysicsMotorProperties MotorProps;
    FSHUDEffect BoostHUDEffect;
    BITFIELD bHasBoost:1 GCC_PACK(4);
    BITFIELD bBoosting:1;
    FSVehiclePhysicsMotorProperties BoostMotorProps GCC_PACK(4);
    FSViewShakeInfo BoostVibration;
    FLOAT BoostTime;
    FLOAT BoostRechargeTime;
    FLOAT BoostOverheatDelay;
    FLOAT BoostFOVScale;
    FLOAT BoostFOVRampTime;
    FLOAT BoostMeter;
    FLOAT BoostOverheatTimer;
    class UClass* DifferentialClass;
    class UClass* MotorClass;
    class UClass* GearboxClass;
    class UClass* AxleClass;
    class UVMotor* motor;
    class UVGearbox* Gearbox;
    INT LastGearIndex;
    BYTE LastEngineSlot;
    BITFIELD bWasAccel:1 GCC_PACK(4);
    FLOAT EngineSoundStartTime GCC_PACK(4);
    FVector InAirVelocity;
    BITFIELD bHadGroundContactLastFrame:1 GCC_PACK(4);
    FSViewShakeInfo LandingShake GCC_PACK(4);
    FSRumbleInfo LandingRumble;
    FSRumbleInfo BounceRumble;
    FSRumbleInfo BoostRumble;
    FSRumbleInfo AccelRumble;
    FSRumbleInfo CollisionRumble;
    class AdnFriendFX_Spawners* DustCloud;
    FLOAT CrashVelocity;
    FLOAT BounceVelocity;
    FLOAT VelDotGravity;
    FLOAT ImpactRumbleThreshold;
    BITFIELD bPerformImpactEffects:1 GCC_PACK(4);
    BITFIELD bPerformLandingEffects:1;
    BITFIELD bLandingEffectsThrottled:1;
    inline void __fastcall eventDoLandingEffects()
    {
        ProcessEvent(FindFunctionChecked(DNVEHICLES_DoLandingEffects), NULL);
    }
    inline void __fastcall eventPlayEngineSound(FName EngineSoundName, BITFIELD bStopLast, BYTE StopSoundRule, FLOAT FadeOutTime)
    {
        AVeh_CarTemplate_eventPlayEngineSound_Parms Parms;
        Parms.EngineSoundName=EngineSoundName;
        Parms.bStopLast=bStopLast;
        Parms.StopSoundRule=StopSoundRule;
        Parms.FadeOutTime=FadeOutTime;
        ProcessEvent(FindFunctionChecked(DNVEHICLES_PlayEngineSound), &Parms);
    }
    DECLARE_CLASS(AVeh_CarTemplate,AVehicle_MeqonWheeled_CarLike,0,dnVehicles)

    // properties that must be constructed special for AVeh_CarTemplate:
    //       * GearSounds
    //       * GearboxProps
    //       * BoostHUDEffect

};
// Class Veh_CarTemplate exported:
//   Properties size: 1052 bytes (4604 total)


//***************************************************************************//
/*	\class AVeh_RCCar_NativeBase
*/
//***************************************************************************//

class DNVEHICLES_API AVeh_RCCar_NativeBase : public AVeh_CarTemplate
{
public:
    class AVehicleSpecialPartBase* Suspension;
    BITFIELD bInitialized:1 GCC_PACK(4);
    dnBone* pBone_Front_L_Wheel GCC_PACK(4);
    dnBone* pBone_Front_L_Spring;
    dnBone* pBone_Front_R_Wheel;
    dnBone* pBone_Front_R_Spring;
    dnBone* pBone_Rear_L_Wheel;
    dnBone* pBone_Rear_L_Spring;
    dnBone* pBone_Rear_R_Wheel;
    dnBone* pBone_Rear_R_Spring;
    DECLARE_FUNCTION(execUpdateSuspension);
    DECLARE_CLASS(AVeh_RCCar_NativeBase,AVeh_CarTemplate,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(AVeh_RCCar_NativeBase)
};
// Class Veh_RCCar_NativeBase exported:
//   Properties size: 40 bytes (4644 total)


//***************************************************************************//
/*	\class AVeh_MonsterTruck_NativeBase
*/
//***************************************************************************//


struct AVeh_MonsterTruck_NativeBase_eventGetGroundMaterialInfo_Parms
{
    class UClass* GroundMaterial;
    INT bPuddlesMaterial;
    INT bDirtMaterial;
};

struct AVeh_MonsterTruck_NativeBase_eventDoSplatter_Parms
{
    class UClass* SplatterClass;
};
class DNVEHICLES_API AVeh_MonsterTruck_NativeBase : public AVeh_CarTemplate
{
public:
    class AVehicleSpecialPartBase* Suspension;
    class UClass* MudSplatterClass;
    class UClass* WaterSplatterClass;
    BITFIELD bHasWheelEffects:1 GCC_PACK(4);
    FLOAT WheelEffectOffset GCC_PACK(4);
    FSWheelEffect WheelEffects[4];
    class ASoftParticleSystem* Exhaust[2];
    class ASoftParticleSystem* BoostExhaust[2];
    BITFIELD bInitialized:1 GCC_PACK(4);
    FName WheelWaterSoundName GCC_PACK(4);
    dnBone* pBone_Front_Main;
    dnBone* pBone_Front_1;
    dnBone* pBone_Front_L_1;
    dnBone* pBone_Front_L_Spring;
    dnBone* pBone_Front_R_1;
    dnBone* pBone_Front_R_Spring;
    dnBone* pBone_Rear_Main;
    dnBone* pBone_Rear_1;
    dnBone* pBone_Rear_L_1;
    dnBone* pBone_Rear_L_Spring;
    dnBone* pBone_Rear_R_1;
    dnBone* pBone_Rear_R_Spring;
    inline void __fastcall eventGetGroundMaterialInfo(class UClass* GroundMaterial, INT& bPuddlesMaterial, INT& bDirtMaterial)
    {
        AVeh_MonsterTruck_NativeBase_eventGetGroundMaterialInfo_Parms Parms;
        Parms.GroundMaterial=GroundMaterial;
        Parms.bPuddlesMaterial=bPuddlesMaterial;
        Parms.bDirtMaterial=bDirtMaterial;
        ProcessEvent(FindFunctionChecked(DNVEHICLES_GetGroundMaterialInfo), &Parms);
        bPuddlesMaterial=Parms.bPuddlesMaterial;
        bDirtMaterial=Parms.bDirtMaterial;
    }
    inline void __fastcall eventDoSplatter(class UClass* SplatterClass)
    {
        AVeh_MonsterTruck_NativeBase_eventDoSplatter_Parms Parms;
        Parms.SplatterClass=SplatterClass;
        ProcessEvent(FindFunctionChecked(DNVEHICLES_DoSplatter), &Parms);
    }
    DECLARE_CLASS(AVeh_MonsterTruck_NativeBase,AVeh_CarTemplate,0,dnVehicles)
};
// Class Veh_MonsterTruck_NativeBase exported:
//   Properties size: 156 bytes (4760 total)


//***************************************************************************//
/*	\class AVehicleSpecialPart_SteeringWheel
*/
//***************************************************************************//

class DNVEHICLES_API AVehicleSpecialPart_SteeringWheel : public AVehicleSpecialPartBase
{
public:
    DECLARE_CLASS(AVehicleSpecialPart_SteeringWheel,AVehicleSpecialPartBase,0,dnVehicles)
};
// Class VehicleSpecialPart_SteeringWheel exported:
//   Properties size: 0 bytes (2968 total)


//***************************************************************************//
/*	\class AVehicleSpecialPart_TireEx
*/
//***************************************************************************//

class DNVEHICLES_API AVehicleSpecialPart_TireEx : public AVehicleSpecialPartBase
{
public:
    FLOAT AngularVelocity;
    class UVWheel* Dummy;
    DECLARE_FUNCTION(execUpdateFromVWheel);
    DECLARE_CLASS(AVehicleSpecialPart_TireEx,AVehicleSpecialPartBase,0,dnVehicles)
};
// Class VehicleSpecialPart_TireEx exported:
//   Properties size: 8 bytes (2976 total)


//***************************************************************************//
/*	\class AMonsterTruckSpecialPartEx_Tire
*/
//***************************************************************************//

class DNVEHICLES_API AMonsterTruckSpecialPartEx_Tire : public AVehicleSpecialPart_TireEx
{
public:
    BITFIELD bFlipped:1 GCC_PACK(4);
    DECLARE_CLASS(AMonsterTruckSpecialPartEx_Tire,AVehicleSpecialPart_TireEx,0,dnVehicles)
};
// Class MonsterTruckSpecialPartEx_Tire exported:
//   Properties size: 4 bytes (2980 total)


//***************************************************************************//
/*	\class UPhysicsAction_Forklift
*/
//***************************************************************************//

class DNVEHICLES_API UPhysicsAction_Forklift : public UPhysicsAction
{
public:
    BITFIELD bMoving:1 GCC_PACK(4);
    BITFIELD bFlipping:1;
    class AKarmaActor* Fork GCC_PACK(4);
    class AKarmaActor* RearWeight;
    class AKFixed* ForkFixedConstraint;
    class AKLinear* ForkLinearConstraint;
    class AKLinearJointLimit* ForkLimit;
    class AKLinearMotorAffector* ForkMotor;
    DECLARE_CLASS(UPhysicsAction_Forklift,UPhysicsAction,0,dnVehicles)
};
// Class PhysicsAction_Forklift exported:
//   Properties size: 28 bytes (68 total)


//***************************************************************************//
/*	\class UPhysicsAction_RightVehicle
*/
//***************************************************************************//

class DNVEHICLES_API UPhysicsAction_RightVehicle : public UPhysicsAction
{
public:
    FVector FlipRotationAxis;
    FLOAT FlipTorque;
    FLOAT FlipLift;
    FLOAT FlipTimeLeft;
    DECLARE_CLASS(UPhysicsAction_RightVehicle,UPhysicsAction,0,dnVehicles)
};
// Class PhysicsAction_RightVehicle exported:
//   Properties size: 24 bytes (64 total)


//***************************************************************************//
/*	\class UVehicleComponent
*/
//***************************************************************************//

class DNVEHICLES_API UVehicleComponent : public UObject
{
public:
    INT VehiclePhysicsUserData;
    BITFIELD bComponentInitialized:1 GCC_PACK(4);
    BITFIELD bCaresAboutAcceleration:1;
    DECLARE_FUNCTION(execAcceleratorAdjust);
    DECLARE_FUNCTION(execAcceleratorNeutral);
    DECLARE_FUNCTION(execUpdate);
    DECLARE_FUNCTION(execAttachToMeqonVehicle);
    DECLARE_CLASS(UVehicleComponent,UObject,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVehicleComponent)
};
// Class VehicleComponent exported:
//   Properties size: 8 bytes (48 total)


//***************************************************************************//
/*	\class UVGearbox
*/
//***************************************************************************//

class DNVEHICLES_API UVGearbox : public UVehicleComponent
{
public:
    FSVehiclePhysicsGearboxProperties GearboxProps;
    class UVAxle* PrimaryAxle;
    class UVAxle* SecondaryAxle;
    FLOAT Clutch;
    FLOAT MaximumClutchTorque;
    INT CurrentGear;
    FLOAT GearboxMagnitude;
    DECLARE_FUNCTION(execSetGear);
    DECLARE_CLASS(UVGearbox,UVehicleComponent,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR_START(UVGearbox)
    NO_DEFAULT_CONSTRUCTOR_INITLAST(GearboxProps)
};
// Class VGearbox exported:
//   Properties size: 44 bytes (92 total)


//***************************************************************************//
/*	\class UVAutomaticGearbox
*/
//***************************************************************************//

class DNVEHICLES_API UVAutomaticGearbox : public UVGearbox
{
public:
    FLOAT ShiftDelay;
    DECLARE_CLASS(UVAutomaticGearbox,UVGearbox,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVAutomaticGearbox)
};
// Class VAutomaticGearbox exported:
//   Properties size: 4 bytes (96 total)


//***************************************************************************//
/*	\class UVConnection
*/
//***************************************************************************//

class DNVEHICLES_API UVConnection : public UVehicleComponent
{
public:
    class UVAxle* Axles[2];
    DECLARE_CLASS(UVConnection,UVehicleComponent,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVConnection)
};
// Class VConnection exported:
//   Properties size: 8 bytes (56 total)


//***************************************************************************//
/*	\class UVDifferential
*/
//***************************************************************************//

class DNVEHICLES_API UVDifferential : public UVehicleComponent
{
public:
    class UVAxle* InputAxle;
    class UVAxle* PrimaryOutputAxle;
    class UVAxle* SecondaryOutputAxle;
    FLOAT Ratio;
    FLOAT Lock;
    FLOAT DifferentialMagnitude;
    FLOAT LockMagnitude;
    DECLARE_CLASS(UVDifferential,UVehicleComponent,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVDifferential)
};
// Class VDifferential exported:
//   Properties size: 28 bytes (76 total)


//***************************************************************************//
/*	\class UVAxle
*/
//***************************************************************************//

class DNVEHICLES_API UVAxle : public UVehicleComponent
{
public:
    FSVehiclePhysicsAxleProperties AxleProps;
    FLOAT Angle;
    FLOAT AngularVelocity;
    FLOAT AngularAcceleration;
    DECLARE_FUNCTION(execApplyTorque);
    DECLARE_CLASS(UVAxle,UVehicleComponent,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVAxle)
};
// Class VAxle exported:
//   Properties size: 16 bytes (64 total)


//***************************************************************************//
/*	\class UVPropeller
*/
//***************************************************************************//

class DNVEHICLES_API UVPropeller : public UVAxle
{
public:
    FLOAT ForceBase;
    FLOAT AirInteractionForceScale;
    FLOAT WaterInteractionForceScale;
    FVector ForceOffset;
    FRotator ForceDirection;
    DECLARE_CLASS(UVPropeller,UVAxle,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVPropeller)
};
// Class VPropeller exported:
//   Properties size: 36 bytes (100 total)


//***************************************************************************//
/*	\class UVWheel
*/
//***************************************************************************//

class DNVEHICLES_API UVWheel : public UVAxle
{
public:
    INT InternalWheelMaterial;
    FVector LocationOffset;
    FRotator RotationOffset;
    BITFIELD bFlipWheel:1 GCC_PACK(4);
    BITFIELD bHasTireActor:1;
    FSVehiclePhysicsWheelProperties WheelProps GCC_PACK(4);
    FLOAT CurrentSteeringAngle;
    FLOAT BrakeTorque;
    FLOAT AutoBrakeTorque;
    FLOAT CurrentSpringLength;
    BITFIELD bOnGround:1 GCC_PACK(4);
    BITFIELD bWasOnGround:1;
    class UClass* GroundMaterialType GCC_PACK(4);
    DECLARE_FUNCTION(execGetHandbrakeBrakeTorque);
    DECLARE_FUNCTION(execSetWheelOffsets);
    inline void __fastcall eventUncontactedGround()
    {
        ProcessEvent(FindFunctionChecked(DNVEHICLES_UncontactedGround), NULL);
    }
    inline void __fastcall eventContactedGround()
    {
        ProcessEvent(FindFunctionChecked(DNVEHICLES_ContactedGround), NULL);
    }
    DECLARE_CLASS(UVWheel,UVAxle,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVWheel)
};
// Class VWheel exported:
//   Properties size: 116 bytes (180 total)


//***************************************************************************//
/*	\class UVMotor
*/
//***************************************************************************//

class DNVEHICLES_API UVMotor : public UVAxle
{
public:
    FSVehiclePhysicsMotorProperties MotorProps;
    FLOAT Input;
    FLOAT DriveMagnitude;
    FLOAT BrakeMagnitude;
    FLOAT RPMs;
    FLOAT BestRPMs;
    FLOAT MaxRPMs;
    DECLARE_CLASS(UVMotor,UVAxle,0,dnVehicles)
    NO_DEFAULT_CONSTRUCTOR(UVMotor)
};
// Class VMotor exported:
//   Properties size: 48 bytes (112 total)

#endif

AUTOGENERATE_FUNCTION(AVeh_RCCar_NativeBase,-1,execUpdateSuspension);
AUTOGENERATE_FUNCTION(AVehicle_MeqonWheeled,-1,execAccelerator_NeutralNative);
AUTOGENERATE_FUNCTION(AVehicle_MeqonWheeled,-1,execUpdateAverageSteeringAngle);
AUTOGENERATE_FUNCTION(AVehicle_MeqonWheeled,-1,execHeading_NeutralNative);
AUTOGENERATE_FUNCTION(AVehicleSpecialPart_TireEx,-1,execUpdateFromVWheel);
AUTOGENERATE_FUNCTION(UVGearbox,-1,execSetGear);
AUTOGENERATE_FUNCTION(UVehicleComponent,-1,execAcceleratorAdjust);
AUTOGENERATE_FUNCTION(UVehicleComponent,-1,execAcceleratorNeutral);
AUTOGENERATE_FUNCTION(UVehicleComponent,-1,execUpdate);
AUTOGENERATE_FUNCTION(UVehicleComponent,-1,execAttachToMeqonVehicle);
AUTOGENERATE_FUNCTION(UVAxle,-1,execApplyTorque);
AUTOGENERATE_FUNCTION(UVWheel,-1,execGetHandbrakeBrakeTorque);
AUTOGENERATE_FUNCTION(UVWheel,-1,execSetWheelOffsets);

#ifndef NAMES_ONLY
#undef AUTOGENERATE_NAME
#undef AUTOGENERATE_FUNCTION
#endif // NAMES_ONLY

#if _MSC_VER
#pragma pack (pop)
#elif defined PS3
#pragma pack (pop)
#endif


#ifdef NATIVE_DEFS_ONLY
#if _MSC_VER
#pragma message("*** Including native definitions from dnVehicles.")
#endif
DECLARE_NATIVE_TYPE(dnVehicles,AVeh_RCCar_NativeBase);
DECLARE_NATIVE_TYPE(dnVehicles,AVeh_CarTemplate);
DECLARE_NATIVE_TYPE(dnVehicles,AVehicle_MeqonWheeled_CarLike);
DECLARE_NATIVE_TYPE(dnVehicles,AVehicle_MeqonWheeled);
DECLARE_NATIVE_TYPE(dnVehicles,AVehicleSpecialPart_SteeringWheel);
DECLARE_NATIVE_TYPE(dnVehicles,UPhysicsAction_Forklift);
DECLARE_NATIVE_TYPE(dnVehicles,UPhysicsAction_RightVehicle);
DECLARE_NATIVE_TYPE(dnVehicles,AVeh_MonsterTruck_NativeBase);
DECLARE_NATIVE_TYPE(dnVehicles,AMonsterTruckSpecialPartEx_Tire);
DECLARE_NATIVE_TYPE(dnVehicles,AVehicleSpecialPart_TireEx);
DECLARE_NATIVE_TYPE(dnVehicles,UVAutomaticGearbox);
DECLARE_NATIVE_TYPE(dnVehicles,UVGearbox);
DECLARE_NATIVE_TYPE(dnVehicles,UVehicleComponent);
DECLARE_NATIVE_TYPE(dnVehicles,UVConnection);
DECLARE_NATIVE_TYPE(dnVehicles,UVDifferential);
DECLARE_NATIVE_TYPE(dnVehicles,UVPropeller);
DECLARE_NATIVE_TYPE(dnVehicles,UVAxle);
DECLARE_NATIVE_TYPE(dnVehicles,UVWheel);
DECLARE_NATIVE_TYPE(dnVehicles,UVMotor);

#define AUTO_INITIALIZE_REGISTRANTS_DNVEHICLES \
	AVeh_RCCar_NativeBase::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesAVeh_RCCar_NativeBaseNative; \
	AVeh_CarTemplate::StaticClassNoInline(); \
	AVehicle_MeqonWheeled_CarLike::StaticClassNoInline(); \
	AVehicle_MeqonWheeled::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesAVehicle_MeqonWheeledNative; \
	AVehicleSpecialPart_SteeringWheel::StaticClassNoInline(); \
	UPhysicsAction_Forklift::StaticClassNoInline(); \
	UPhysicsAction_RightVehicle::StaticClassNoInline(); \
	AVeh_MonsterTruck_NativeBase::StaticClassNoInline(); \
	AMonsterTruckSpecialPartEx_Tire::StaticClassNoInline(); \
	AVehicleSpecialPart_TireEx::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesAVehicleSpecialPart_TireExNative; \
	UVAutomaticGearbox::StaticClassNoInline(); \
	UVGearbox::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesUVGearboxNative; \
	UVehicleComponent::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesUVehicleComponentNative; \
	UVConnection::StaticClassNoInline(); \
	UVDifferential::StaticClassNoInline(); \
	UVPropeller::StaticClassNoInline(); \
	UVAxle::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesUVAxleNative; \
	UVWheel::StaticClassNoInline(); \
	GNativeLookupFuncs[Lookup++] = &FinddnVehiclesUVWheelNative; \
	UVMotor::StaticClassNoInline(); \

#endif // NATIVE_DEFS_ONLY

#ifdef NATIVES_ONLY
#if _MSC_VER
#pragma message("*** Including native classes from dnVehicles.")
#endif
NATIVE_INFO(AVeh_RCCar_NativeBase) GdnVehiclesAVeh_RCCar_NativeBaseNatives[] = 
{ 
	MAP_NATIVE(AVeh_RCCar_NativeBase,execUpdateSuspension)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,AVeh_RCCar_NativeBase);

NATIVE_INFO(AVehicle_MeqonWheeled) GdnVehiclesAVehicle_MeqonWheeledNatives[] = 
{ 
	MAP_NATIVE(AVehicle_MeqonWheeled,execAccelerator_NeutralNative)
	MAP_NATIVE(AVehicle_MeqonWheeled,execUpdateAverageSteeringAngle)
	MAP_NATIVE(AVehicle_MeqonWheeled,execHeading_NeutralNative)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,AVehicle_MeqonWheeled);

NATIVE_INFO(AVehicleSpecialPart_TireEx) GdnVehiclesAVehicleSpecialPart_TireExNatives[] = 
{ 
	MAP_NATIVE(AVehicleSpecialPart_TireEx,execUpdateFromVWheel)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,AVehicleSpecialPart_TireEx);

NATIVE_INFO(UVGearbox) GdnVehiclesUVGearboxNatives[] = 
{ 
	MAP_NATIVE(UVGearbox,execSetGear)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,UVGearbox);

NATIVE_INFO(UVehicleComponent) GdnVehiclesUVehicleComponentNatives[] = 
{ 
	MAP_NATIVE(UVehicleComponent,execAcceleratorAdjust)
	MAP_NATIVE(UVehicleComponent,execAcceleratorNeutral)
	MAP_NATIVE(UVehicleComponent,execUpdate)
	MAP_NATIVE(UVehicleComponent,execAttachToMeqonVehicle)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,UVehicleComponent);

NATIVE_INFO(UVAxle) GdnVehiclesUVAxleNatives[] = 
{ 
	MAP_NATIVE(UVAxle,execApplyTorque)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,UVAxle);

NATIVE_INFO(UVWheel) GdnVehiclesUVWheelNatives[] = 
{ 
	MAP_NATIVE(UVWheel,execGetHandbrakeBrakeTorque)
	MAP_NATIVE(UVWheel,execSetWheelOffsets)
	{NULL,NULL}
};
IMPLEMENT_NATIVE_HANDLER(dnVehicles,UVWheel);

#endif // NATIVES_ONLY
#if _MSC_VER
#pragma warning(default:4121)
#endif

#ifdef VERIFY_CLASS_SIZES
#pragma message("*** Verifying class sizes for dnVehicles.")
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,Suspension)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Front_L_Wheel)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Front_L_Spring)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Front_R_Wheel)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Front_R_Spring)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Rear_L_Wheel)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Rear_L_Spring)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Rear_R_Wheel)
VERIFY_CLASS_OFFSET_NODIE(AVeh_RCCar_NativeBase,Veh_RCCar_NativeBase,pBone_Rear_R_Spring)
VERIFY_CLASS_SIZE_NODIE(AVeh_RCCar_NativeBase)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,FrontAxle)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,RearAxle)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,FrontRearDifferential)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,FrontRearDifferentialLock)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,EngineStartSoundName)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,EngineStopSoundName)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,GearSounds)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,EngineSoundVolume)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,MinRPMPitchAdjust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,MaxRPMPitchAdjust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostPitchAdjust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,InAirPitchAdjust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,EngineSoundOffset)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,PitchAdjust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,PitchAdjustRate)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,AxleProps)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,GearboxProps)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,MotorAxleProps)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,MotorProps)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostHUDEffect)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostMotorProps)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostVibration)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostTime)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostRechargeTime)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostOverheatDelay)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostFOVScale)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostFOVRampTime)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostMeter)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostOverheatTimer)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,DifferentialClass)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,MotorClass)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,GearboxClass)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,AxleClass)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,motor)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,Gearbox)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,LastGearIndex)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,LastEngineSlot)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,EngineSoundStartTime)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,InAirVelocity)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,LandingShake)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,LandingRumble)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BounceRumble)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BoostRumble)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,AccelRumble)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,CollisionRumble)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,DustCloud)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,CrashVelocity)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,BounceVelocity)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,VelDotGravity)
VERIFY_CLASS_OFFSET_NODIE(AVeh_CarTemplate,Veh_CarTemplate,ImpactRumbleThreshold)
VERIFY_CLASS_SIZE_NODIE(AVeh_CarTemplate)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled_CarLike,Vehicle_MeqonWheeled_CarLike,Axles)
VERIFY_CLASS_SIZE_NODIE(AVehicle_MeqonWheeled_CarLike)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,NeutralSteeringAdjust)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,SteerMaxAngles)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,BrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,NeutralBrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,NoDriverBrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,HandbrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,VehicleMinNeutralTransitionTime)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,MinDirectionalChangeSteerAlpha)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,VehicleComponents)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,VWheels)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,KLinearToleranceScale)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,KAngularToleranceScale)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,KMaximumIterations)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,EnableDriveTrainTag)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,DisableDriveTrainTag)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,LowFriction)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,HighFriction)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,LowSpeed)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,LowSpeedBrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,LowSpeedPct)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,HighSpeed)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,HighSpeedSteerPct)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,HandbrakeActive)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,SavedDisableThreshold)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,AverageSteerAngle)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,SteerAlpha)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,WheelMaterialType)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,WheelMassType)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,WheelSkidMinTime)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,WheelSkidDBIndex)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,WheelSkidOverrideEntry)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,WheelSkidStartTime)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,FullTractionAngle)
VERIFY_CLASS_OFFSET_NODIE(AVehicle_MeqonWheeled,Vehicle_MeqonWheeled,NoTractionAngle)
VERIFY_CLASS_SIZE_NODIE(AVehicle_MeqonWheeled)
VERIFY_CLASS_SIZE_NODIE(AVehicleSpecialPart_SteeringWheel)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_Forklift,PhysicsAction_Forklift,Fork)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_Forklift,PhysicsAction_Forklift,RearWeight)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_Forklift,PhysicsAction_Forklift,ForkFixedConstraint)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_Forklift,PhysicsAction_Forklift,ForkLinearConstraint)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_Forklift,PhysicsAction_Forklift,ForkLimit)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_Forklift,PhysicsAction_Forklift,ForkMotor)
VERIFY_CLASS_SIZE_NODIE(UPhysicsAction_Forklift)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_RightVehicle,PhysicsAction_RightVehicle,FlipRotationAxis)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_RightVehicle,PhysicsAction_RightVehicle,FlipTorque)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_RightVehicle,PhysicsAction_RightVehicle,FlipLift)
VERIFY_CLASS_OFFSET_NODIE(UPhysicsAction_RightVehicle,PhysicsAction_RightVehicle,FlipTimeLeft)
VERIFY_CLASS_SIZE_NODIE(UPhysicsAction_RightVehicle)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,Suspension)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,MudSplatterClass)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,WaterSplatterClass)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,WheelEffectOffset)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,WheelEffects)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,Exhaust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,BoostExhaust)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,WheelWaterSoundName)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Front_Main)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Front_1)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Front_L_1)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Front_L_Spring)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Front_R_1)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Front_R_Spring)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Rear_Main)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Rear_1)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Rear_L_1)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Rear_L_Spring)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Rear_R_1)
VERIFY_CLASS_OFFSET_NODIE(AVeh_MonsterTruck_NativeBase,Veh_MonsterTruck_NativeBase,pBone_Rear_R_Spring)
VERIFY_CLASS_SIZE_NODIE(AVeh_MonsterTruck_NativeBase)
VERIFY_CLASS_SIZE_NODIE(AMonsterTruckSpecialPartEx_Tire)
VERIFY_CLASS_OFFSET_NODIE(AVehicleSpecialPart_TireEx,VehicleSpecialPart_TireEx,AngularVelocity)
VERIFY_CLASS_OFFSET_NODIE(AVehicleSpecialPart_TireEx,VehicleSpecialPart_TireEx,Dummy)
VERIFY_CLASS_SIZE_NODIE(AVehicleSpecialPart_TireEx)
VERIFY_CLASS_OFFSET_NODIE(UVAutomaticGearbox,VAutomaticGearbox,ShiftDelay)
VERIFY_CLASS_SIZE_NODIE(UVAutomaticGearbox)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,GearboxProps)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,PrimaryAxle)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,SecondaryAxle)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,Clutch)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,MaximumClutchTorque)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,CurrentGear)
VERIFY_CLASS_OFFSET_NODIE(UVGearbox,VGearbox,GearboxMagnitude)
VERIFY_CLASS_SIZE_NODIE(UVGearbox)
VERIFY_CLASS_OFFSET_NODIE(UVehicleComponent,VehicleComponent,VehiclePhysicsUserData)
VERIFY_CLASS_SIZE_NODIE(UVehicleComponent)
VERIFY_CLASS_OFFSET_NODIE(UVConnection,VConnection,Axles)
VERIFY_CLASS_SIZE_NODIE(UVConnection)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,InputAxle)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,PrimaryOutputAxle)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,SecondaryOutputAxle)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,Ratio)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,Lock)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,DifferentialMagnitude)
VERIFY_CLASS_OFFSET_NODIE(UVDifferential,VDifferential,LockMagnitude)
VERIFY_CLASS_SIZE_NODIE(UVDifferential)
VERIFY_CLASS_OFFSET_NODIE(UVPropeller,VPropeller,ForceBase)
VERIFY_CLASS_OFFSET_NODIE(UVPropeller,VPropeller,AirInteractionForceScale)
VERIFY_CLASS_OFFSET_NODIE(UVPropeller,VPropeller,WaterInteractionForceScale)
VERIFY_CLASS_OFFSET_NODIE(UVPropeller,VPropeller,ForceOffset)
VERIFY_CLASS_OFFSET_NODIE(UVPropeller,VPropeller,ForceDirection)
VERIFY_CLASS_SIZE_NODIE(UVPropeller)
VERIFY_CLASS_OFFSET_NODIE(UVAxle,VAxle,AxleProps)
VERIFY_CLASS_OFFSET_NODIE(UVAxle,VAxle,Angle)
VERIFY_CLASS_OFFSET_NODIE(UVAxle,VAxle,AngularVelocity)
VERIFY_CLASS_OFFSET_NODIE(UVAxle,VAxle,AngularAcceleration)
VERIFY_CLASS_SIZE_NODIE(UVAxle)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,InternalWheelMaterial)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,LocationOffset)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,RotationOffset)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,WheelProps)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,CurrentSteeringAngle)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,BrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,AutoBrakeTorque)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,CurrentSpringLength)
VERIFY_CLASS_OFFSET_NODIE(UVWheel,VWheel,GroundMaterialType)
VERIFY_CLASS_SIZE_NODIE(UVWheel)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,MotorProps)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,Input)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,DriveMagnitude)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,BrakeMagnitude)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,RPMs)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,BestRPMs)
VERIFY_CLASS_OFFSET_NODIE(UVMotor,VMotor,MaxRPMs)
VERIFY_CLASS_SIZE_NODIE(UVMotor)
#endif // VERIFY_CLASS_SIZES