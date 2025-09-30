#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "stdint.h"
#include "raylib.h"

#define MAX_ENTITIES 1024
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

	} CompType;



typedef  Vector2 Position;
/*
typedef struct {
	int x, y;

	} Position;
*/

typedef enum{
	//Undead monsters
	Artas,
	Abomination,
	Ghoul,
	Banshee,
	Necromancer,
	Wagon,
	Zombie,
	Acolyte,
	AcolyteB,
	AcolyteS,
	AcolyteD,
	AcolyteDB, 
	AcolyteDW,
	Monster_Num

}Monster_Type;


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
	//S_Pile,
	//S_asd,
	
	//ENv
	S_Plant,
	S_PlantBig,
	 

	//Generated sprites for gas
	S_BasicGas,
	//S_

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


}Stats;

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
//	STATE_MOVING_AWAY_RANGE,
	STATE_HUNTING,
	
	STATE_RESTING,   //Sleep 
	STATE_BESERK,
	STATE_RANGE,
	STATE_ALERTED, 
	STATE_SEARCHING,
//	STATE_RESURECT,
//	STATE_SUMMON,
//	STATE_SPELL,
	STATE_NUM
	} State_Monster;

typedef struct {
	State_Monster current;
	float chancesR;
	float chancesH;
	float chancesW;
	float chancesRe;
	float chancesB;
	float chanceRange;	
	float fear;
	int   lastSeenX;
	int   lastSeenY;
	int   memoryTimer;
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





#define MAP_WIDTH  100
#define MAP_HEIGHT 30



#define STR_SIZE 128

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
	gasNo = -1,
	gasBasic = 0,
	gasNum
}GasType;

typedef struct{
	GasType type;
	int     isActive;
	int     timeToStay;
	Color   color;
	//Tbd otherStufss
}Gas;




#endif