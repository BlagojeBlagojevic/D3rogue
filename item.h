#ifndef ITEM_H
#define ITEM_H
#include<string.h>
#include<stdio.h>

#include<stdlib.h>
#include "raylib.h"
#include "da_arr.h"

#include "common.h"

typedef enum{
	
	EQUIPTED_ARMOR,
	EQUIPTED_WEPON,
	EQUIPTED_RANGE,
	EQUIPTED_MUTITION,
	
	EQUIPTED_SHIELD,
	EQUIPTED_LEGS,
	EQUIPTED_HAND,
	EQUIPTED_TOURCH,
	
	
	EQUIPTED_HEAD, //Do not add below
	
	EQUIPTED_USE_SCROL,
	EQUIPTED_USE_POTION,
	EQUIPTED_NUM,
	
}Item_Equipted;


typedef enum{
	
	Sword = 0,
	BrokenDagger,
	RustySword,
	Dagger,
	Shovel,
	MainGauche,
	Whip,
	Spear,
	Rapier,
	SmallSword,
	Saber,
	Pick,
	Cutlass,
	SmallTrident,
	Trident,
	Mace,
	Tulwar,
	Quartestaff,
	BallandChain,
	WarHammer,
	Lance,
	Scimitar,
	BroadSword,
	BroadAxe,
	BattleAxe,
	AwlPike,
	Flail,
	Pike,
	Glaive,
	LucerneHammer,
	Katana,
	Halberd,
	GreatAxe,
	MaceScalp,
	TwoHandFlail,
	LochaberAxe,
	Scythe,
	TwoHandSword,
	ESword,
	SScythe,
	CBlade,
	DMace,
	//
	LeatherArmor,
	FRobe,
	Robe,
	SoftLeatherArmour,
	SoftStuddedLeather,
	HardLeatherArmour,
	HardStuddedLeather,
	LeatherScaleMail,
	MetalScaleMail,
	RustyChainMail,
	ChainMail,
	DoubleChainMail,
	AugmentedChainMail,
	BarChainMail,
	MetalBrigandineArmour,
	PartialPlateArmour,
	MetalLamellarArmour,
	FullPlateArmour,
	RibbedPlateArmour,
	MithrilChainMail,
	MithrilPlateMail,
	AdamantitePlateMail,
	BronzeDragonScaleMail,
	BlackDragonScaleMail,
	BlueDragonScaleMail,
	WhiteDragonScaleMail,
	GoldDragonScaleMail,
	ShiningDragonScaleMail,
	ChaosDragonScaleMail,
	GreenDragonScaleMail,
	LawDragonScaleMail,
	RedDragonScaleMail,
	BalanceDragonScaleMail,
	MultiHuedDragonScaleMail,
	PowerDragonScaleMail,
	

	//
	SmallBuckler,
	WoodenRoundShield,
	ReinforcedWoodenShield,
	IronRoundShield,
	SpikedShield,
	HeaterShield,
	SteelKiteShield,
	TowerShield,
	MithrilShield,
	DragonscaleShield,
	AdamantiteShield,
	AegisOfReflection,

	//
	LeatherCap,
	PaddedHood,
	IronCap,
	NasalHelm,
	Spangenhelm,
	Bascinet,
	GreatHelm,
	MithrilHelm,
	AdamantiteHelm,
	DragonboneHelm,
	CrownOfWisdom,

	LetherBoots,
	MetalBoots,

	LetherGloves,
	MetalGloves,

	//
	Bow,
	Arrows, 
	Tourch,
	Item_Num
}Item_Type;

static const char* ITEM_NAMES[] = {
    /* Oružja */
    "Sword",
    "BrokenDagger",
    "RustySword",
    "Dagger",
    "Shovel",
    "MainGauche",
    "Whip",
    "Spear",
    "Rapier",
    "SmallSword",
    "Saber",
    "Pick",
    "Cutlass",
    "SmallTrident",
    "Trident",
    "Mace",
    "Tulwar",
    "Quartestaff",
    "BallandChain",
    "WarHammer",
    "Lance",
    "Scimitar",
    "BroadSword",
    "BroadAxe",
    "BattleAxe",
    "AwlPike",
    "Flail",
    "Pike",
    "Glaive",
    "LucerneHammer",
    "Katana",
    "Halberd",
    "GreatAxe",
    "MaceScalp",
    "TwoHandFlail",
    "LochaberAxe",
    "Scythe",
    "TwoHandSword",
    "ESword",
    "SScythe",
    "CBlade",
    "DMace",

    /* Oklopi */
    "LeatherArmor",
    "FRobe",
    "Robe",
    "SoftLeatherArmour",
    "SoftStuddedLeather",
    "HardLeatherArmour",
    "HardStuddedLeather",
    "LeatherScaleMail",
    "MetalScaleMail",
    "RustyChainMail",
    "ChainMail",
    "DoubleChainMail",
    "AugmentedChainMail",
    "BarChainMail",
    "MetalBrigandineArmour",
    "PartialPlateArmour",
    "MetalLamellarArmour",
    "FullPlateArmour",
    "RibbedPlateArmour",
    "MithrilChainMail",
    "MithrilPlateMail",
    "AdamantitePlateMail",
    "BronzeDragonScaleMail",
    "BlackDragonScaleMail",
    "BlueDragonScaleMail",
    "WhiteDragonScaleMail",
    "GoldDragonScaleMail",
    "ShiningDragonScaleMail",
    "ChaosDragonScaleMail",
    "GreenDragonScaleMail",
    "LawDragonScaleMail",
    "RedDragonScaleMail",
    "BalanceDragonScaleMail",
    "MultiHuedDragonScaleMail",
    "PowerDragonScaleMail",
    
    /* Štitovi */
    "SmallBuckler",
    "WoodenRoundShield",
    "ReinforcedWoodenShield",
    "IronRoundShield",
    "SpikedShield",
    "HeaterShield",
    "SteelKiteShield",
    "TowerShield",
    "MithrilShield",
    "DragonscaleShield",
    "AdamantiteShield",
    "AegisOfReflection",

    /* Kacige */
    "LeatherCap",
    "PaddedHood",
    "IronCap",
    "NasalHelm",
    "Spangenhelm",
    "Bascinet",
    "GreatHelm",
    "MithrilHelm",
    "AdamantiteHelm",
    "DragonboneHelm",
    "CrownOfWisdom",

    /* Čizme i Rukavice */
    "LetherBoots",
    "MetalBoots",
    "LetherGloves",
    "MetalGloves",

    /* Ostalo */
    "Bow",
    "Arrows", 
    "Tourch"
};


 

typedef struct{
	Stats          stats;
	int            value;
	int            nDice;
	Position       pos;
	char*          name;
	Item_Type      type;
	Item_Type      fire;
	Item_Equipted  to;
	int            isEqu;
}Item;

typedef struct{
	int  count;
	int  capacity;
	Item *items;
}Item_DA;













//Items
void add_item_to_inventory(Item_Type type, Item_DA* inventory, int isEqu);
void equipt_item(Item_DA* inventory, int whatItem);
int  is_item_of_type_equ(Item_DA* inventory, Item_Equipted equ);
void add_items_from_list(ChanceItem_DA* list, Item_DA* inventory);


#endif