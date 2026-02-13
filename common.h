#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "stdint.h"
#include "raylib.h"
#include "rlgl.h"
//#include "item.h"


#define MAX_ENTITIES 6000
#define MAX_COMPONENTS 32

// Component type bitmask
typedef uint32_t CompMask;

enum{NOT = 0, MOVE, ATTACK, ATTACK_RANGE};

 


// Component types (as bit flags)
typedef enum {
	COMP_POSITION = 1 << 0,
	COMP_RENDER   = 1 << 1,
	COMP_HEALTH   = 1 << 2,
	COMP_MONSTER  = 1 << 3,
	COMP_PLAYER   = 1 << 4,
	COMP_INPUT    = 1 << 5,
	COMP_STATS    = 1 << 6,
	COMP_STATE    = 1 << 7,
	COMP_OPEN     = 1 << 8,
	COMP_PROJEC   = 1 << 9,	
	COMP_GAS      = 1 << 10,
	COMP_SPELL    = 1 << 11, 
	COMP_FIRE     = 1 << 12,
	COMP_STATUS   = 1 << 13,
	COMP_SHOP     = 1 << 14,
	COMP_VITAL    = 1 << 15,
	
	} CompType;



typedef  Vector2 Position;
/*
typedef struct {
	int x, y;

	} Position;
*/

typedef struct {
	int 	count;
	int 	capacity;
	char** items;
	} Str;


typedef enum{
	//Undead monsters
	Artas,
	Abomination,//
	Ghoul,//b
	Banshee,//b
	Necromancer,//b
	Wagon,//b
	Zombie,//b
	Acolyte,//b
	AcolyteB,//b
	AcolyteS,//b
	AcolyteD,//b
	AcolyteDB, //b
	AcolyteDW,//b
	SPit,//b

	Spider,  //Balance
	SpiderMage,//b

	Wolf, //Balance
	

	Garg,    //Kinda
	Bat, //Balance Tbd summon vamp
	Vampire,//b

	Bloat,       //Balanced
	//PitBloat

	ObsidanStatue,//b
	Anubis,   //Balanced
	OrcWarrior, //Balance
	OrcRaider, //Balance
	OrcShaman,  //Balance  
	OrcWarloc,  //Balance
	RedOrc,     //Balance
	OrcBrute,   //Balance  
	OrcSamurai,   //Balanced
	OrcWarchief,  //Balanced
	OrcScout,     //Balanced

	GoblinWarrior, //Balanced
	GoblinArcher,  //Balanced
	GoblinWarlord, //Balanced
	GoblinBarrack, //Balanced 

	GiantRat,      //Balanced
	PinkJelly,    //ba
	GreenJelly,		//b
	BlueJelly,	//b
	Toad,		//B

	Imp,      //B
	MindFlayer, //B
	Phantom, //B
	Lich, //B
	Succubus,//B
	BeholderKin,//B
	SoulReaper,//B
	Manes,//B
	FlashDemon,//B
	FireDemon,//B
	Kraken,//B
	WaterDemon,//B

	Monster_Num

}Monster_Type;


static const char* Monster_Names[] = {
	"Artas",
	"Abomination",
	"Ghoul",
	"Banshee",
	"Necromancer",
	"Wagon",
	"Zombie",
	"Acolyte",
	"AcolyteB",
	"AcolyteS",
	"AcolyteD",
	"AcolyteDB", 
	"AcolyteDW",
	"SPit",

	"Spider", //1
	"SpiderMage",

	"Wolf",  //1
	

	"Garg",
	"Bat",  //1
	"Vampire",

	"Bloat",

	"ObsidanStatue",
	"Anubis",
	"OrcWarrior",
	"OrcRaider",
	"OrcShaman",
	"OrcWarloc",
	"RedOrc",
	"OrcBrute",
	"OrcSamurai",
	"OrcWarchief",
	"OrcScout",

	"GoblinWarrior", //1   
	"GoblinArcher",  //1
	"GoblinWarlord", 
	"GoblinBarrack",

	"GiantRat",//1
	"PinkJelly",
	"GreenJelly",
	"BlueJelly",
	"Toad",

	"Imp",
	"MindFlayer",
	"Phantom",
	"Lich",
	"Succubus",
	"BeholderKin",
	"SoulReaper",
	"Manes",
	"FlashDemon",
	"FireDemon",
	"Kraken",
	"WaterDemon",

}; 



//Order is important
typedef enum{
	//Undead monsters
	S_Artas,
	S_Abomination,
	S_Ghoul,
	S_Banshee,
	S_Necromancer,
	S_Wagon,
	S_Zombie,
	S_Acolyte,
	S_AcolyteB,
	S_AcolyteS,
	S_AcolyteD,
	S_AcolyteDB,
	S_AcolyteDW,
	S_SPit,
	S_Spider,
	S_SpiderMage,
	S_Wolf,
	S_Garg,
	S_Bat,
	S_Vampire,
	S_Bloat,
	S_ObsidanStatue,
	S_Anubis,
	S_OrcWarrior,
	S_OrcRaider,
	S_OrcShaman,
	S_OrcWarloc,
	S_RedOrc,
	S_OrcBrute,	
	S_OrcSamurai,
	S_OrcWarchief,
	S_OrcScout,
	S_GoblinWarrior,
	S_GoblinArcher,
	S_GoblinWarlord,
	S_GoblinBarrack,
	S_GiantRat,
	S_PinkJelly,
	S_GreenJelly,
	S_BlueJelly,
	S_Toad,
	S_Imp,
	S_MindFlayer,
	S_Phantom,
	S_Lich,
	S_Succubus,
	S_BeholderKin,
	S_SoulReaper,
	S_Manes,
	S_FlashDemon,
	S_FireDemon,
	S_Kraken,
	//Do not change
	S_WaterDemon,

	//
	S_OpenDoor,
	S_ClosedDoor,
	//Items
	S_Sword,
	S_BrokenDagger,
	S_RustySword,
	S_Dagger,
	S_Shovel,
	S_MainGauche,
	S_Whip,
	S_Spear,
	S_Rapier,
	S_SmallSword,
	S_Saber,
	S_Pick,
	S_CutlAss,
	S_SmallTrident,
	S_Trident,
	S_Mace,
	S_Tulwar,
	S_Quartestaff,
	S_BallandChain,
	S_WarHammer,
	S_Lance,
	S_Scimitar,
	S_BroadSword,
	S_BroadAxe,
	S_BattleAxe,
	S_AwlPike,
	S_Flail,
	S_Pike, 
	S_Glaive,
	S_LucerneHammer,
	S_Katana,
	S_Halberd,
	S_GreatAxe,
	S_MaceScalp,
	S_TwoHandFlail,
	S_LochaberAxe,
	S_Scythe,
	S_TwoHandSword,
	S_ESword,
	S_SScythe,
	S_CBlade,
	S_MaceD,

	S_LetherArmor,
	S_FRobe,
	S_Robe,
	S_SoftLeatherArmour,
	S_SoftStuddedLeather,
	S_HardLeatherArmour,
	S_HardStuddedLeather,
	S_LeatherScaleMail,
	S_MetalScaleMail,
	S_RustyChainMail,
	S_ChainMail,
	S_DoubleChainMail,
	S_AugmentedChainMail,
	S_BarChainMail,
	S_MetalBrigandineArmour,
	S_PartialPlateArmour,
	S_MetalLamellarArmour,
	S_FullPlateArmour,
	S_RibbedPlateArmour,
	S_MithrilChainMail,
	S_MithrilPlateMail,
	S_AdamantitePlateMail,
	S_BronzeDragonScaleMail,
	S_BlackDragonScaleMail,
	S_BlueDragonScaleMail,
	S_WhiteDragonScaleMail,
	S_GoldDragonScaleMail,
	S_ShiningDragonScaleMail,
	S_ChaosDragonScaleMail,
	S_GreenDragonScaleMail,
	S_LawDragonScaleMail,
	S_RedDragonScaleMail,
	S_BalanceDragonScaleMail,
	S_MultiHuedDragonScaleMail,
	S_PowerDragonScaleMail,

	//
	S_SmallBuckler,
	S_WoodenRoundShield,
	S_ReinforcedWoodenShield,
	S_IronRoundShield,
	S_SpikedShield,
	S_HeaterShield,
	S_SteelKiteShield,
	S_TowerShield,
	S_MithrilShield,
	S_DragonscaleShield,
	S_AdamantiteShield,
	S_AegisOfReflection,
	//
	S_LeatherCap,
	S_PaddedHood,
	S_IronCap,
	S_NasalHelm,
	S_Spangenhelm,
	S_Bascinet,
	S_GreatHelm,
	S_MithrilHelm,
	S_AdamantiteHelm,
	S_DragonboneHelm,
	S_CrownOfWisdom,

	S_LetherBoots,
	S_MetalBoots,

	S_LetherGloves,
	S_MetalGloves,

	S_Bow,
	S_Arrow,
	S_Tourch,
	S_Food,
	S_Gold,
	S_Mushroom,
	S_Scroll,
	S_Potion,
	
	//S_Pile,
	//S_asd,
	
	//ENv
	S_Plant,
	S_PlantBig,
	S_UpS,
	S_DownS, 
	S_Armory,
	S_WeponS,
	S_GeneralS,
	S_PotionS,
	S_ScrollS,
	S_Ground,
	S_Wall,
	S_Water,
	S_Lava,

	S_Sprite_Num

}Sprite_Type;




typedef enum{
	OpenDoor = Monster_Num,
	ClosedDoor,
	//PileItem,
	Door_num
}Door_Type;




//Tbd glyph to num of structure
typedef struct {
	Sprite_Type type;
	} Renderable;

typedef struct {
	int current;
	int max;
	} Health;


typedef struct {
	Position nextPosition;
	float    playerYaw;
	float    targetYaw;
	float    moveLerpAlpha;
	uint8_t  isMoving;
	uint8_t  isFinishedAttack;
	int      entProjectile;
	bool     isAquatic;
	//float moveLerpAlpha;
	} Input;

typedef struct {
	int str;   //Chance to wield a wepon, size inventory, base attack strenght 
	int dex;   //Chance to doge a attack
	int inte;  // 
	int cons;  //Heling speed some stuff for vision range stamina
	
	int morale;//Just monsters for now to run and stuff
	int perception;
	int stealth;
	

	int dmgMax;
	int dmgMin;
	int defence;

}Stats;

typedef struct{
	int str;    
	int dex;   
	int inte; 
	int cons;
	int turns;
	int dmgMax;
	int dmgMin;
	int defence;
	int health;
	int maxHealth;
}TempStats;

typedef struct 
{
	int count;
	int capacity;
	TempStats *items;
}TempStats_DA;



typedef struct {
	uint8_t isOpen;
	uint8_t isLock;
}Open;

typedef struct {
	int max;
	int stamina;
}Stamina;




typedef enum {
	STATE_WANDERING,
	STATE_RUNING,
	STATE_HUNTING,
	STATE_RESTING,   //Sleep 
	STATE_BERSERK,
	STATE_RANGE,
	STATE_ALERTED, 
	STATE_SEARCHING,
	STATE_STALKING,
	STATE_TERRITORIAL,
	STATE_STUN,
	STATE_SPELL,
	STATE_NUM
	} State_Monster;

	typedef enum{
		AL_BEAST,
		AL_COWARD,
		AL_HUNTER,
		AL_RANGE,
		AL_NUM,

		
	}AL_Type;

static const char* AL_Name[] = {
		"AL_BEAST",
		"AL_COWARD",
		"AL_HUNTER",
		"AL_RANGE",
	};

typedef struct {
	State_Monster current;
	//Tbd remove
	float    chancesR;
	float    chancesH;
	float    chancesW;
	float    chancesRe;
	float    chancesB;
	float    chanceRange;
	
	float 	 fear;
	int   	 lastSeenX;
	int   	 lastSeenY;
	int   	 memoryTimer;
	int   	 territoryRadius;
	Position home;
	int      stunTurn;
	AL_Type  type;	
}State;

/*
typedef struct {
    Vector2 velocity;   
    float lifetime;     
    int owner_id;       
} Projectile;

*/

static const char* itemActions[] = {
	
	"Equipt",
	
	"Wield",
	"Wield",
	"Munition",

	"Equipt",
	"Equipt",
	"Equipt",
	"Equipt",

	"Equipt",
	
	"Use",
	"Use"

};





#define MAP_WIDTH  80
#define MAP_HEIGHT 40



#define STR_SIZE 256

typedef struct{
	int count;
	int capacity;
	int *items;
}Num;


typedef struct {
	float chance;
	int   type;
}ChanceItem;

typedef struct{
	int 		count;
	int 	    capacity;
	ChanceItem *items;
}ChanceItem_DA;



typedef enum{
	gasNo,
	gasBasic = 1,
	gasHealing,
	gasSwamp, 
	gasPoison,
	gasAcid,
	gasStun,
	gasNum
}GasType;

static const Color gasColor[] = {
	(Color){0, 0, 0, 0},
	(Color){139, 4, 10, 50},
	(Color){30, 203, 225, 50},
	(Color){115, 63, 8, 50},
	(Color){16, 248, 7, 50},
	(Color){248, 7, 87, 50},
	(Color){10, 0, 4, 50},
	(Color){0, 0, 0, 0}
}; 


typedef struct{
	GasType type;
	int     isActive;
	int     timeToStay;
	Color   color;
	//Tbd otherStufss
}Gas;



//Spells
typedef enum{
    Spell_Summon,
    Spell_Stun,
    Spell_Blink,
    Spell_Explode,
    Spell_Dmg,
    //Spell_Buff,
    Spell_Teleport,
    Spell_Shout,
	Spell_Hook,
	Spell_Web,
	Spell_Obsidian, //Buffs
	Spell_Anubis,
	Spell_OrcScout,
	Spell_Sacrifice,
	Spell_Mirror,
	Spell_WarCray,
	Spell_GoblinBarrack,
	Spell_Confusion,
	Spell_ReduceStr,
	Spell_No,
	

	Spell_Num
}SpellType;

enum {DMG, HEAL}; //For obsidan

typedef struct {
    SpellType type;
    int value; // 
    int cooldown;
    int passTurn;
}Spell;


typedef enum{
	Tile_Dirt   = ' ',
	TIle_Grass  = '"',
	Tile_BGrass = '\'',
	Tile_CDoor  = '+',
	Tile_ODoor  = '-',
	Tile_Water  = '~',
	Tile_Dwater = '(',
	Tile_Fire   = '^',
	Tile_Lava   = '%',
	Tile_Caz    = ':',
	Tile_Wall   = '#',
	Tile_DownS  = '<',
	Tile_UpS    = '>', 
	Tile_Armory = 'A',//
	Tile_Wepon  = 'W',//
	Tile_Genera = 'G',
	Tile_Pot    = 'P',
	Tile_Scro   = 'S',

}Tiles;


typedef struct{
	int imuneToFire;
	int isOnFire;
}Fire;


typedef enum{
	TRAP_NO,
	TRAP_POISON, 
	TRAP_ACID, 
	TRAP_FIRE,
	TRAP_STUN,
	TRAP_TELEPORT,
	TRAP_BEAR,
	TRAP_SUMMON,
	TRAP_NUM

}Trap_Types;

typedef struct{
	Trap_Types trap;
	int value;
}Trap;

//Tbd refactor fire and stun in this
typedef struct{
	int poison;
	int poisonTurn;
	int poisonImune;

	int hallucination;
	int hallucinationTurn;
	int hallucinationImune;

	int confusion;
	int confusionTurn;
	int confusionImune;

	int levitation;
	int levitationTurn;
	int levitationImune;
	
	int telepaty;
	int telepatyTurn;
	int telepatyImune;
	
	int str;
	int isStr;
	int strTurn;
	int strImune;


	int inte;
	int isInte;
	int inteTurn;
	int inteImune;


	int dex;
	int isDex;
	int dexTurn;
	int dexImune;
	

}StatusEffects;

//Need to add its junk but
typedef enum{
	P_Arrow 	= S_Arrow,
	P_Potion 	= S_Potion, 
}ProjeciteType;

typedef struct{
	ProjeciteType type;
	int itemID;
}Projectile;


typedef struct  {
	int max;
	int current;
}Vital;



#endif