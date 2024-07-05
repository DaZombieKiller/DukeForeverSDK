/*=============================================================================
	UnNames.h: Header file registering global hardcoded Unreal names.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

	Revision history:
		* Created by Tim Sweeney
=============================================================================*/

/*-----------------------------------------------------------------------------
	Macros.
-----------------------------------------------------------------------------*/

// Define a message as an enumeration.
#ifndef REGISTER_NAME
	#define REGISTER_NAME(num,name) NAME_##name = num,
	#define REG_NAME_HIGH(num,name) NAME_##name = num,
	#define REGISTERING_ENUM
	enum EName {
#endif

/*-----------------------------------------------------------------------------
	Hardcoded names which are not messages.
-----------------------------------------------------------------------------*/

// Special zero value, meaning no name.
REG_NAME_HIGH(   0, None             )

// Class property types; these map straight onto hardcoded property types.
REGISTER_NAME(   1, ByteProperty     )
REGISTER_NAME(   2, IntProperty      )
REGISTER_NAME(   3, BoolProperty     )
REGISTER_NAME(   4, FloatProperty    )
REGISTER_NAME(   5, ObjectProperty   )
REGISTER_NAME(   6, NameProperty     )
REGISTER_NAME(   7, DelegateProperty )
REGISTER_NAME(   8, ClassProperty    )
REGISTER_NAME(   9, ArrayProperty    )
REGISTER_NAME(  10, StructProperty   )
REGISTER_NAME(  11, VectorProperty   )
REGISTER_NAME(  12, RotatorProperty  )
REGISTER_NAME(  13, StrProperty      )
REGISTER_NAME(  14, PointerProperty  )

// Packages.
REGISTER_NAME(  20, Core             )
REGISTER_NAME(  21, Engine           )
REGISTER_NAME(  22, Editor           )
REGISTER_NAME(  25, dnGame           )
REGISTER_NAME(  26, dnAI             )
REGISTER_NAME(  27, dnVehicles       )

// UnrealScript types.
REG_NAME_HIGH(  80, Byte             )
REG_NAME_HIGH(  81, Int              )
REG_NAME_HIGH(  82, Bool             )
REG_NAME_HIGH(  83, Float            )
REG_NAME_HIGH(  84, Name             )
REG_NAME_HIGH(  85, String           )
REG_NAME_HIGH(  86, Struct           )
REG_NAME_HIGH(  87, Vector           )
REG_NAME_HIGH(  88, Rotator          )
REG_NAME_HIGH(  90, Color            )
REG_NAME_HIGH(  91, Plane            )
REG_NAME_HIGH(  92, Pointer          )

// Keywords.
REGISTER_NAME( 100, Begin            )
REG_NAME_HIGH( 102, State            )
REG_NAME_HIGH( 103, Function         )
REG_NAME_HIGH( 104, Self             )
REG_NAME_HIGH( 105, True             )
REG_NAME_HIGH( 106, False            )
REG_NAME_HIGH( 107, Transient        )
REG_NAME_HIGH( 117, Enum             )
REG_NAME_HIGH( 119, Replication      )
REG_NAME_HIGH( 120, Reliable         )
REG_NAME_HIGH( 121, Unreliable       )
REG_NAME_HIGH( 122, Always           )
REG_NAME_HIGH( 123, Anim             )
REG_NAME_HIGH( 124, NonTrans         )
REG_NAME_HIGH( 125, AnimEvent        )
REG_NAME_HIGH( 126, DebugOnly        )

// Object class names.
REGISTER_NAME( 150, Field            )
REGISTER_NAME( 151, Object           )
REGISTER_NAME( 152, TextBuffer       )
REGISTER_NAME( 153, Linker           )
REGISTER_NAME( 154, LinkerLoad       )
REGISTER_NAME( 155, LinkerSave       )
REGISTER_NAME( 156, Subsystem        )
REGISTER_NAME( 157, Factory          )
REGISTER_NAME( 158, TextBufferFactory)
REGISTER_NAME( 159, Exporter         )
REGISTER_NAME( 160, StackNode        )
REGISTER_NAME( 161, Property         )
REGISTER_NAME( 162, Camera           )
REGISTER_NAME( 163, Model            )

// Constants.
REG_NAME_HIGH( 600, Vect             )
REG_NAME_HIGH( 601, Rot              )
REG_NAME_HIGH( 605, ArrayCount       )
REG_NAME_HIGH( 606, EnumCount        )

// Flow control.
REG_NAME_HIGH( 620, Else             )
REG_NAME_HIGH( 621, If               )
REG_NAME_HIGH( 622, Goto             )
REG_NAME_HIGH( 623, Stop             )
REG_NAME_HIGH( 625, Until            )
REG_NAME_HIGH( 626, While            )
REG_NAME_HIGH( 627, Do               )
REG_NAME_HIGH( 628, Break            )
REG_NAME_HIGH( 629, For              )
REG_NAME_HIGH( 630, ForEach          )
REG_NAME_HIGH( 631, Assert           )
REG_NAME_HIGH( 632, Switch           )
REG_NAME_HIGH( 633, Case             )
REG_NAME_HIGH( 634, Default          )
REG_NAME_HIGH( 635, Continue         )

// Variable overrides.
REG_NAME_HIGH( 590, EditInline       )
REG_NAME_HIGH( 591, EditInlineUse    )
REG_NAME_HIGH( 592, EditConstArray   )
REG_NAME_HIGH( 593, EditInlineNotify )
REG_NAME_HIGH( 595, EdFindable       )
REG_NAME_HIGH( 640, Private          )
REG_NAME_HIGH( 641, Const            )
REG_NAME_HIGH( 642, Out              )
REG_NAME_HIGH( 643, Export           )
REG_NAME_HIGH( 644, Protected        )
REG_NAME_HIGH( 645, Public           )
REG_NAME_HIGH( 646, Skip             )
REG_NAME_HIGH( 647, Coerce           )
REG_NAME_HIGH( 648, Optional         )
REG_NAME_HIGH( 649, Input            )
REG_NAME_HIGH( 650, Config           )
REG_NAME_HIGH( 651, NetUpdate        )
REG_NAME_HIGH( 652, Travel           )
REG_NAME_HIGH( 653, EditConst        )
REG_NAME_HIGH( 654, Localized        )
REG_NAME_HIGH( 655, GlobalConfig     )
REG_NAME_HIGH( 656, SafeReplace      )
REG_NAME_HIGH( 657, New              )
REG_NAME_HIGH( 658, Obsolete         )
REG_NAME_HIGH( 659, NoCompress       )

// Class overrides.
REG_NAME_HIGH( 660, Expands          )
REG_NAME_HIGH( 661, Tags             )
REG_NAME_HIGH( 662, Within           )
REG_NAME_HIGH( 663, Abstract         )
REG_NAME_HIGH( 664, Package          )
REG_NAME_HIGH( 665, Guid             )
REG_NAME_HIGH( 666, Parent           )
REG_NAME_HIGH( 667, Class            )
REG_NAME_HIGH( 668, Extends          )
REG_NAME_HIGH( 669, NoExport         )
REG_NAME_HIGH( 670, NativeDestructor )
REG_NAME_HIGH( 671, PerObjectConfig  )
REG_NAME_HIGH( 672, NativeReplication)
REG_NAME_HIGH( 673, Placeable        )
REG_NAME_HIGH( 683, NotPlaceable     )
REG_NAME_HIGH( 684, EditInlineNew    )
REG_NAME_HIGH( 685, NotEditInlineNew )
REG_NAME_HIGH( 686, HideCategories   )
REG_NAME_HIGH( 687, ShowCategories   )
REG_NAME_HIGH( 688, Listable         )
REG_NAME_HIGH( 689, NotListable      )

// State overrides.
REG_NAME_HIGH( 675, Auto             )
REG_NAME_HIGH( 676, Ignores          )

// Calling overrides.
REG_NAME_HIGH( 680, Global           )
REG_NAME_HIGH( 681, Super            )
REG_NAME_HIGH( 682, Outer            )

// Function overrides.
REG_NAME_HIGH( 690, Operator         )
REG_NAME_HIGH( 691, PreOperator      )
REG_NAME_HIGH( 692, PostOperator     )
REG_NAME_HIGH( 693, Final            )
REG_NAME_HIGH( 694, Iterator         )
REG_NAME_HIGH( 695, Latent           )
REG_NAME_HIGH( 696, Return           )
REG_NAME_HIGH( 697, Singular         )
REG_NAME_HIGH( 698, Simulated        )
REG_NAME_HIGH( 699, Exec             )
REG_NAME_HIGH( 700, Event            )
REG_NAME_HIGH( 701, Static           )
REG_NAME_HIGH( 702, Native           )
REG_NAME_HIGH( 703, Invariant        )
REG_NAME_HIGH( 704, Indexed          )
REG_NAME_HIGH( 705, Delegate         )
REG_NAME_HIGH( 706, Cached           )
REG_NAME_HIGH( 707, Encrypted        )
REG_NAME_HIGH( 708, DevExec          )

// Variable declaration.
REG_NAME_HIGH( 710, Var              )
REG_NAME_HIGH( 711, Local            )
REG_NAME_HIGH( 712, Import           )
REG_NAME_HIGH( 713, From             )

// Special commands.
REG_NAME_HIGH( 720, Spawn            )
REG_NAME_HIGH( 721, Array            )

// Misc.
REGISTER_NAME( 740, Root             )
REG_NAME_HIGH( 741, Untags           )
REGISTER_NAME( 742, Role             )
REGISTER_NAME( 743, RemoteRole       )
REGISTER_NAME( 744, System           )
REGISTER_NAME( 745, User             )
REGISTER_NAME( 746, dnMyDigs         )
REGISTER_NAME( 747, Fire             )
REGISTER_NAME( 748, Melee            )
REGISTER_NAME( 749, PainBack01       )
REGISTER_NAME( 750, PainBack02       )
REGISTER_NAME( 751, PainRight01      )
REGISTER_NAME( 752, PainRight02      )
REGISTER_NAME( 753, PainLeft01       )
REGISTER_NAME( 754, PainLeft02       )
REGISTER_NAME( 755, Pickup           )
REGISTER_NAME( 756, Undefined        )

// Log messages.
REGISTER_NAME( 760, Log              )
REGISTER_NAME( 761, Critical         )
REGISTER_NAME( 762, Init             )
REGISTER_NAME( 763, Exit             )
REGISTER_NAME( 764, EventLog         )
REGISTER_NAME( 767, Warning          )
REGISTER_NAME( 768, ExecWarning      )
REGISTER_NAME( 769, ScriptWarning    )
REGISTER_NAME( 770, ScriptLog        )
REGISTER_NAME( 772, DevKill          )
REGISTER_NAME( 773, DevLoad          )
REGISTER_NAME( 774, DevSave          )
REGISTER_NAME( 775, DevReplace       )
REGISTER_NAME( 776, DevGarbage       )
REGISTER_NAME( 777, DevCompile       )
REGISTER_NAME( 778, DevBind          )
REGISTER_NAME( 779, DevNet           )
REGISTER_NAME( 780, DevNetTraffic    )
REGISTER_NAME( 781, NetComeGo        )
REGISTER_NAME( 785, Localization     )
REGISTER_NAME( 786, AmbientLightScale)
REGISTER_NAME( 788, Title            )
REGISTER_NAME( 789, Error            )
REGISTER_NAME( 790, Heading          )
REGISTER_NAME( 791, SubHeading       )
REGISTER_NAME( 792, FriendlyError    )
REGISTER_NAME( 793, Progress         )
REGISTER_NAME( 794, UserPrompt       )

// Misc.
REGISTER_NAME( 795, Front            )
REGISTER_NAME( 796, Back             )
REGISTER_NAME( 797, BuildConvert     )
REGISTER_NAME( 798, ScriptError      )
REGISTER_NAME( 799, Meqon            )
REGISTER_NAME( 800, LevelPhysicsEntityGroup)
REGISTER_NAME( 801, DukeIntro        )
REGISTER_NAME( 802, HoloActor        )
REGISTER_NAME( 803, MP_HoloActor     )
REGISTER_NAME( 816, CloseDialogBox   )
REGISTER_NAME( 817, ShutdownAllDialogs)
REGISTER_NAME( 818, ShowMessageBox   )
REGISTER_NAME( 819, HideMessageBox   )
REGISTER_NAME( 820, KeyType          )
REGISTER_NAME( 821, KeyEvent         )
REGISTER_NAME( 822, Write            )
REGISTER_NAME( 823, Message          )
REGISTER_NAME( 824, InitialState     )
REGISTER_NAME( 825, Texture          )
REGISTER_NAME( 826, Sound            )
REGISTER_NAME( 827, FireTexture      )
REGISTER_NAME( 828, IceTexture       )
REGISTER_NAME( 829, WaterTexture     )
REGISTER_NAME( 830, WaveTexture      )
REGISTER_NAME( 831, WetTexture       )
REGISTER_NAME( 832, Main             )
REGISTER_NAME( 833, NotifyLevelChange)
REGISTER_NAME( 834, VideoChange      )
REGISTER_NAME( 835, SendText         )
REGISTER_NAME( 836, SendBinary       )
REGISTER_NAME( 837, ConnectFailure   )
REGISTER_NAME( 838, ToAll            )
REGISTER_NAME( 839, LoadScreenShot   )
REGISTER_NAME( 840, SetProgressMessage)
REGISTER_NAME( 841, KillLoadScreen   )
REGISTER_NAME( 842, Fallthrough      )
REGISTER_NAME( 843, NoDebug          )
REGISTER_NAME( 844, InitWindowSystem )
REGISTER_NAME( 845, DisplayMainMenu  )
REGISTER_NAME( 846, UpdateJoy        )
REGISTER_NAME( 847, CloseUWindow     )
REGISTER_NAME( 848, ShowDialogBox    )
REGISTER_NAME( 849, ProcessPlayerInput)
REGISTER_NAME( 850, Length           )
REGISTER_NAME( 851, Insert           )
REGISTER_NAME( 852, Remove           )
REGISTER_NAME( 853, Add              )
REGISTER_NAME( 854, Empty            )
REGISTER_NAME( 855, ForClass         )
REGISTER_NAME( 860, XSpecial_Clear   )
REGISTER_NAME( 861, XSpecial_AnimEnd )
REGISTER_NAME( 862, Actor            )
REGISTER_NAME( 863, BeginDataExchange)
REGISTER_NAME( 870, GetMaterial      )
REGISTER_NAME( 871, SysScrapeFriend  )
REGISTER_NAME( 872, dnPhysicsFX_Spawned)
REGISTER_NAME( 873, FilmGrainEffect  )
REGISTER_NAME( 875, SoundConfig      )
REGISTER_NAME( 876, AmbientMusicEarlyEnd)
REGISTER_NAME( 877, AmbientMusicEnded)
REGISTER_NAME( 878, LipsNeutral      )
REGISTER_NAME( 879, LipSync          )
REGISTER_NAME( 880, Generic0         )
REGISTER_NAME( 881, Generic1         )
REGISTER_NAME( 882, Generic2         )
REGISTER_NAME( 883, Generic3         )
REGISTER_NAME( 884, Generic4         )
REGISTER_NAME( 885, Generic5         )
REGISTER_NAME( 886, Generic6         )
REGISTER_NAME( 887, AmbientLightFront)
REGISTER_NAME( 888, AmbientLightBack )
REGISTER_NAME( 889, SystemColor      )
REGISTER_NAME( 890, WAV              )
REGISTER_NAME( 891, MP3              )
REGISTER_NAME( 892, XMA              )
REGISTER_NAME( 900, Sound_StompBegin )
REGISTER_NAME( 901, Sound_Ambient    )
REGISTER_NAME( 902, Bottom           )
REGISTER_NAME( 903, Anim_Script      )
REGISTER_NAME( 920, Interact         )
REGISTER_NAME( 921, Music            )
REGISTER_NAME( 930, UWindow          )
REGISTER_NAME( 950, XLevel           )

/*-----------------------------------------------------------------------------
	Special engine-generated probe messages.
-----------------------------------------------------------------------------*/

//
// warning: All probe entries must be filled in, otherwise non-probe names might be mapped
// to probe name indices.
//
#define NAME_PROBEMIN ((EName)300)
#define NAME_PROBEMAX ((EName)351)

// Creation and destruction.
REGISTER_NAME( 300, Spawned          ) // Sent to actor immediately after spawning.
REGISTER_NAME( 301, Destroyed        ) // Called immediately before actor is removed from actor list.

// Gaining/losing actors.
REGISTER_NAME( 302, GainedChild      ) // Sent to a parent actor when another actor attaches to it.
REGISTER_NAME( 303, LostChild        ) // Sent to a parent actor when another actor detaches from it.

// Triggers.
REGISTER_NAME( 304, Trigger          ) // Message sent by Trigger actors.
REGISTER_NAME( 305, UnTrigger        ) // Message sent by Trigger actors.

// Physics & world interaction.
REGISTER_NAME( 306, HitWall          ) // Ran into a wall.
REGISTER_NAME( 307, Falling          ) // Actor is falling.
REGISTER_NAME( 308, Landed           ) // Actor has landed.
REGISTER_NAME( 309, ZoneChange       ) // Actor has changed into a new zone.
REGISTER_NAME( 310, Touch            ) // Actor was just touched by another actor.
REGISTER_NAME( 311, UnTouch          ) // Actor touch just ended, always sent sometime after Touch.
REGISTER_NAME( 312, Bump             ) // Actor was just touched and blocked. No interpenetration. No UnBump.
REGISTER_NAME( 313, BeginState       ) // Just entered a new state.
REGISTER_NAME( 314, EndState         ) // About to leave the current state.
REGISTER_NAME( 315, BaseChange       ) // Sent to actor when its floor changes.
REGISTER_NAME( 316, Attach           ) // Sent to actor when it's stepped on by another actor.
REGISTER_NAME( 317, Detach           ) // Sent to actor when another actor steps off it.
REGISTER_NAME( 318, ActorEntered     ) // Sent to a ZoneInfo actor when an actor enters.
REGISTER_NAME( 319, ActorLeaving     ) // Sent to a ZoneInfo actor when an actor is leaving.
REGISTER_NAME( 320, InterpolateEnd   ) // Movement interpolation sequence finished.
REGISTER_NAME( 321, EncroachingOn    ) // Encroaching on another actor.
REGISTER_NAME( 322, LinearDamping    )
REGISTER_NAME( 323, AngularDamping   )

// Updates.
REGISTER_NAME( 325, Tick             ) // Clock tick update for nonplayer.
REGISTER_NAME( 326, PlayerTick       ) // Clock tick update for player.
REGISTER_NAME( 327, Expired          ) // Actor's LifeSpan expired.

// AI.
REGISTER_NAME( 328, SeePlayer        ) // Can see player.
REGISTER_NAME( 330, SeeMonster       ) // Can see non-player.

// Network
REGISTER_NAME( 331, PostNetReceive   )

//
REGISTER_NAME( 332, RootGroup        )
REGISTER_NAME( 333, AnimEndEx        )

// Special tag meaning 'All probes'.
REGISTER_NAME( 334, All              ) // Special meaning, not a message.

REGISTER_NAME( 335, P335             )
REGISTER_NAME( 336, P336             )
REGISTER_NAME( 337, P337             )
REGISTER_NAME( 338, P338             )
REGISTER_NAME( 339, P339             )
REGISTER_NAME( 340, P340             )
REGISTER_NAME( 341, P341             )
REGISTER_NAME( 342, P342             )
REGISTER_NAME( 343, P343             )
REGISTER_NAME( 344, P344             )
REGISTER_NAME( 345, P345             )
REGISTER_NAME( 346, P346             )
REGISTER_NAME( 347, P347             )
REGISTER_NAME( 348, DOFFocalDistance )
REGISTER_NAME( 349, DOFFocalRangeMin )
REGISTER_NAME( 350, DOFFocalRangeMax )

/*-----------------------------------------------------------------------------
	Closing.
-----------------------------------------------------------------------------*/

#ifdef REGISTERING_ENUM
	};
	#undef REGISTER_NAME
	#undef REG_NAME_HIGH
	#undef REGISTERING_ENUM
#endif

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
