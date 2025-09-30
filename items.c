#include "item.h"
#define ITEM_SPECIAL 0.25f
#define ITEM_CURSE   (ITEM_SPECIAL + 0.35f)

void add_item_to_inventory(Item_Type type, Item_DA* inventory, int isEqu){
    Item i;
    int isSpecialItem = 1000;
    float chance = rand_f32(); 
    int value = rand()%5 + 1;
    if(chance < ITEM_SPECIAL){
        isSpecialItem = rand()%50;
        
    }
    else if(chance > ITEM_SPECIAL && chance < ITEM_CURSE){
        isSpecialItem = rand()%50;
        value *=-1;
    }
    else{
        //Not a thing
    } 
    //Str
    if(isSpecialItem < 10 && isSpecialItem != 0){
        i.stats = (Stats){value, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    //Dex
    else if(isSpecialItem > 10 && isSpecialItem < 20){
        i.stats = (Stats){ 0, value, 0, 0, 0, 0, 0, 0, 0};
    }
    //Int 
    else if(isSpecialItem > 20 && isSpecialItem < 30){
        i.stats = (Stats){ 0, 0, value, 0, 0, 0, 0, 0, 0};
    }
    //Cons
    else if(isSpecialItem > 30 && isSpecialItem < 40){
        i.stats = (Stats){0, 0, 0, value, 0, 0, 0, 0, 0};
    }
    else{
        i.stats = (Stats){0, 0, 0, 0,     0, 0, 0, 0, 0};
    }

    switch (type){
    case Sword:{
        i.name  = malloc(128);
        strcpy(i.name, "Sword");
        i.pos   = (Position){0, 0};
        i.type  = Sword;
        i.value = 3; 
        i.nDice  = rand()%2+1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BrokenDagger:{
        i.name  = malloc(128);
        strcpy(i.name, "BrokenDagger");
        i.pos   = (Position){0, 0};
        i.type  = BrokenDagger;
        i.value = 1; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case RustySword:{
        i.name  = malloc(128);
        strcpy(i.name, "RustySword");
        i.pos   = (Position){0, 0};
        i.type  = RustySword;
        i.value = 2; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Dagger:{
        i.name  = malloc(128);
        strcpy(i.name, "Dagger");
        i.pos   = (Position){0, 0};
        i.type  = Dagger;
        i.value = 4; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Shovel:{
        i.name  = malloc(128);
        strcpy(i.name, "Shovel");
        i.pos   = (Position){0, 0};
        i.type  = Shovel;
        i.value = 2; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MainGauche:{
        i.name  = malloc(128);
        strcpy(i.name, "MainGauche");
        i.pos   = (Position){0, 0};
        i.type  = MainGauche;
        i.value = 5; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Whip:{
        i.name  = malloc(128);
        strcpy(i.name, "Whip");
        i.pos   = (Position){0, 0};
        i.type  = Whip;
        i.value = 3; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Spear:{
        i.name  = malloc(128);
        strcpy(i.name, "Spear");
        i.pos   = (Position){0, 0};
        i.type  = Spear;
        i.value = 6; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Rapier:{
        i.name  = malloc(128);
        strcpy(i.name, "Rapier");
        i.pos   = (Position){0, 0};
        i.type  = Rapier;
        i.value = 6; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case SmallSword:{
        i.name  = malloc(128);
        strcpy(i.name, "SmallSword");
        i.pos   = (Position){0, 0};
        i.type  = SmallSword;
        if(rand()%2)
            i.value = 6;
        else
            i.value = 7; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Saber:{
        i.name  = malloc(128);
        strcpy(i.name, "Saber");
        i.pos   = (Position){0, 0};
        i.type  = Saber;
        i.value = 7; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Pick:{
        i.name  = malloc(128);
        strcpy(i.name, "Pick");
        i.pos   = (Position){0, 0};
        i.type  = Pick;
        i.value = 3; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Cutlass:{
        i.name  = malloc(128);
        strcpy(i.name, "Cutlass");
        i.pos   = (Position){0, 0};
        i.type  = Cutlass;
        i.value = 7; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case SmallTrident:{
        i.name  = malloc(128);
        strcpy(i.name, "SmallTrident");
        i.pos   = (Position){0, 0};
        i.type  = SmallTrident;
        i.value = 4; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Trident:{
        i.name  = malloc(128);
        strcpy(i.name, "Trident");
        i.pos   = (Position){0, 0};
        i.type  = Trident;
        i.value = 8; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Mace:{
        i.name  = malloc(128);
        strcpy(i.name, "Mace");
        i.pos   = (Position){0, 0};
        i.type  = Mace;
        i.value = 4; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Tulwar:{
        i.name  = malloc(128);
        strcpy(i.name, "Tulwar");
        i.pos   = (Position){0, 0};
        i.type  = Tulwar;
        i.value = 4; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    
    case Quartestaff:{
        i.name  = malloc(128);
        strcpy(i.name, "Quartestaff");
        i.pos   = (Position){0, 0};
        i.type  = Quartestaff;
        i.value = 9; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BallandChain:{
        i.name  = malloc(128);
        strcpy(i.name, "BallandChain");
        i.pos   = (Position){0, 0};
        i.type  = BallandChain;
        i.value = 4; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case WarHammer:{
        i.name  = malloc(128);
        strcpy(i.name, "WarHammer");
        i.pos   = (Position){0, 0};
        i.type  = WarHammer;
        i.value = 3; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Lance:{
        i.name  = malloc(128);
        strcpy(i.name, "Lance");
        i.pos   = (Position){0, 0};
        i.type  = Lance;
        i.value = 2; 
        i.nDice = 8;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Scimitar:{
        i.name  = malloc(128);
        strcpy(i.name, "Scimitar");
        i.pos   = (Position){0, 0};
        i.type  = Scimitar;
        i.value = 5; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }   
    case BroadSword:{
        i.name  = malloc(128);
        int what = rand()%3;
        if(what == 0)
            strcpy(i.name, "BroadSword");
        else if(what == 1)  
            strcpy(i.name, "LongSword");
        else
            strcpy(i.name, "BastardSword");
        i.pos   = (Position){0, 0};
        i.type  = BroadSword;
        if(what != 2){
            i.value = 5; 
            i.nDice = 2;
        }
        else{
            i.value = 4;
            i.nDice = 3;
        }
        
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BroadAxe:{
        i.name  = malloc(128);
        strcpy(i.name, "BroadAxe");
        i.pos   = (Position){0, 0};
        i.type  = BroadAxe;
        i.value = 6; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BattleAxe:{
        i.name  = malloc(128);
        strcpy(i.name, "BattleAxe");
        i.pos   = (Position){0, 0};
        i.type  = BattleAxe;
        i.value = 6; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case AwlPike:{
        i.name  = malloc(128);
        strcpy(i.name, "AwlPike");
        i.pos   = (Position){0, 0};
        i.type  = AwlPike;
        i.value = 8; 
        i.nDice = 1;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Flail:{
        i.name  = malloc(128);
        if(rand()%2)
            strcpy(i.name, "Flail");
        else
            strcpy(i.name, "MorningStar");
        i.pos   = (Position){0, 0};
        i.type  = Flail;
        i.value = 6; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Pike:{
        i.name  = malloc(128);
        strcpy(i.name, "Pike");
        i.pos   = (Position){0, 0};
        i.type  = Pike;
        i.value = 6; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Glaive:{
        i.name  = malloc(128);
        strcpy(i.name, "Glaive");
        i.pos   = (Position){0, 0};
        i.type  = Glaive;
        i.value = 6; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    
    case LucerneHammer:{
        i.name  = malloc(128);
        strcpy(i.name, "LucerneHammer");
        i.pos   = (Position){0, 0};
        i.type  = LucerneHammer;
        i.value = 5; 
        i.nDice = 2;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Katana:{
        i.name  = malloc(128);
        strcpy(i.name, "Katana");
        i.pos   = (Position){0, 0};
        i.type  = Katana;
        i.value = 4; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Halberd:{
        i.name  = malloc(128);
        strcpy(i.name, "Halberd");
        i.pos   = (Position){0, 0};
        i.type  = Halberd;
        i.value = 4; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case GreatAxe:{
        i.name  = malloc(128);
        strcpy(i.name, "GreatAxe");
        i.pos   = (Position){0, 0};
        i.type  = GreatAxe;
        i.value = 4; 
        i.nDice = 4;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MaceScalp:{
        i.name  = malloc(128);
        strcpy(i.name, "GreatMace");
        i.pos   = (Position){0, 0};
        i.type  = MaceScalp;
        i.value = 4; 
        i.nDice = 4;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case TwoHandFlail:{
        i.name  = malloc(128);
        strcpy(i.name, "TwoHandFlail");
        i.pos   = (Position){0, 0};
        i.type  = TwoHandFlail;
        i.value = 6; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case LochaberAxe:{
        i.name  = malloc(128);
        strcpy(i.name, "LochaberAxe");
        i.pos   = (Position){0, 0};
        i.type  = LochaberAxe;
        i.value = 8; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Scythe:{
        i.name  = malloc(128);
        strcpy(i.name, "Scythe");
        i.pos   = (Position){0, 0};
        i.type  = Scythe;
        i.value = 3; 
        i.nDice = 5;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }       

    case TwoHandSword:{
        i.name  = malloc(128);
        strcpy(i.name, "TwoHandSword");
        i.pos   = (Position){0, 0};
        i.type  = TwoHandSword;
        i.value = 6; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;  
    }
    case ESword:{
        i.name  = malloc(128);
        strcpy(i.name, "Executioner'sSword");
        i.pos   = (Position){0, 0};
        i.type  = ESword;
        i.value = 6; 
        i.nDice = 3;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;  
    }
    case SScythe:{
        i.name  = malloc(128);
        strcpy(i.name, "ScytheofSlicing");
        i.pos   = (Position){0, 0};
        i.type  = SScythe;
        i.value = 8; 
        i.nDice = 4;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    } 
    
    case CBlade:{
        i.name  = malloc(128);
        strcpy(i.name, "BladeOfChaos");
        i.pos   = (Position){0, 0};
        i.type  = CBlade;
        i.value = 5; 
        i.nDice = 6;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    } 
    case DMace:{
        i.name  = malloc(128);
        strcpy(i.name, "MaceOfDisruption");
        i.pos   = (Position){0, 0};
        i.type  = DMace;
        i.value = 8; 
        i.nDice = 4;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    } 
    
    // END OF ADDED ARMOR

    case LeatherArmor:{
        i.name = malloc(128);
        strcpy(i.name, "Leather Armor");
        i.pos   = (Position){0, 0};
        i.type  = LeatherArmor;
        i.value = 3;
        i.nDice  = rand()%2+1; 
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }

    case FRobe:{
        i.name = malloc(128);
        strcpy(i.name, "FilthyRag");
        i.pos   = (Position){0, 0};
        i.type  = FRobe;
        i.value = 1;
        i.nDice  = 1; 
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
	   case Robe:{
        i.name = malloc(128);
        strcpy(i.name, "Robe");
        i.pos   = (Position){0, 0};
        i.type  = Robe;
        i.value = 2; // PV: 2, Weight: 2.0, Cost: 4
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case SoftLeatherArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Soft Leather Armour");
        i.pos   = (Position){0, 0};
        i.type  = SoftLeatherArmour;
        i.value = 4; // PV: 4, Weight: 8.0, Cost: 18
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case SoftStuddedLeather:{
        i.name = malloc(128);
        strcpy(i.name, "Soft Studded Leather");
        i.pos   = (Position){0, 0};
        i.type  = SoftStuddedLeather;
        i.value = 5; // PV: 5, Weight: 9.0, Cost: 35
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case HardLeatherArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Hard Leather Armour");
        i.pos   = (Position){0, 0};
        i.type  = HardLeatherArmour;
        i.value = 3; // PV: 6, Weight: 10.0, Cost: 150
        i.nDice  = 2;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case HardStuddedLeather:{
        i.name = malloc(128);
        strcpy(i.name, "Hard Studded Leather");
        i.pos   = (Position){0, 0};
        i.type  = HardStuddedLeather;
        i.value = 7; // PV: 7, Weight: 11.0, Cost: 200
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case LeatherScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Leather Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = LeatherScaleMail;
        i.value = 11; // PV: 11, Weight: 14.0, Cost: 450
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MetalScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = MetalScaleMail;
        i.value = 13; // PV: 13, Weight: 25.0, Cost: 550
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case RustyChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Rusty Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = RustyChainMail;
        i.value = 7; // PV: 14, Weight: 20.0, Cost: 550
        i.nDice  = 2;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case ChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = ChainMail;
        i.value = 7; // PV: 14, Weight: 22.0, Cost: 750
        i.nDice  = 2;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case DoubleChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Double Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = DoubleChainMail;
        i.value = 8; // PV: 16, Weight: 25.0, Cost: 850
        i.nDice  = 2;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case AugmentedChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Augmented Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = AugmentedChainMail;
        i.value = 8; // PV: 16, Weight: 27.0, Cost: 900
        i.nDice = 2;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BarChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Bar Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = BarChainMail;
        i.value = 6; // PV: 18, Weight: 28.0, Cost: 950
        i.nDice = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MetalBrigandineArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Brigandine Armour");
        i.pos   = (Position){0, 0};
        i.type  = MetalBrigandineArmour;
        i.value = 19; // PV: 19, Weight: 29.0, Cost: 1100
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case PartialPlateArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Partial Plate Armour");
        i.pos   = (Position){0, 0};
        i.type  = PartialPlateArmour;
        i.value = 22; // PV: 22, Weight: 26.0, Cost: 1200
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MetalLamellarArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Lamellar Armour");
        i.pos   = (Position){0, 0};
        i.type  = MetalLamellarArmour;
        i.value = 23; // PV: 23, Weight: 34.0, Cost: 1250
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case FullPlateArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Full Plate Armour");
        i.pos   = (Position){0, 0};
        i.type  = FullPlateArmour;
        i.value = 25; // PV: 25, Weight: 38.0, Cost: 1350
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case RibbedPlateArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Ribbed Plate Armour");
        i.pos   = (Position){0, 0};
        i.type  = RibbedPlateArmour;
        i.value = 28; // PV: 28, Weight: 38.0, Cost: 1500
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MithrilChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = MithrilChainMail;
        i.value = 7; // PV: 28, Weight: 15.0, Cost: 7000
        i.nDice = 4;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MithrilPlateMail:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Plate Mail");
        i.pos   = (Position){0, 0};
        i.type  = MithrilPlateMail;
        i.value = 35; // PV: 35, Weight: 30.0, Cost: 15000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case AdamantitePlateMail:{
        i.name = malloc(128);
        strcpy(i.name, "Adamantite Plate Mail");
        i.pos   = (Position){0, 0};
        i.type  = AdamantitePlateMail;
        i.value = 40; // PV: 40, Weight: 42.0, Cost: 20000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BronzeDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Bronze Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BronzeDragonScaleMail;
        i.value = 30; // PV: 30, Weight: 20.0, Cost: 30000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BlackDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Black Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BlackDragonScaleMail;
        i.value = 30; // PV: 30, Weight: 20.0, Cost: 30000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BlueDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Blue Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BlueDragonScaleMail;
        i.value = 30; // PV: 30, Weight: 20.0, Cost: 25000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case WhiteDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "White Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = WhiteDragonScaleMail;
        i.value = 30; // PV: 30, Weight: 20.0, Cost: 40000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case GoldDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Gold Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = GoldDragonScaleMail;
        i.value = 30; // PV: 30, Weight: 20.0, Cost: 40000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case ShiningDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Shining Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = ShiningDragonScaleMail;
        i.value = 10; // PV: 30, Weight: 20.0, Cost: 60000
        i.nDice  = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case ChaosDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Chaos Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = ChaosDragonScaleMail;
        i.value = 10; // PV: 30, Weight: 20.0, Cost: 70000
        i.nDice  = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case GreenDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Green Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = GreenDragonScaleMail;
        i.value = 10; // PV: 30, Weight: 20.0, Cost: 80000
        i.nDice  = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case LawDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Law Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = LawDragonScaleMail;
        i.value = 10; // PV: 30, Weight: 20.0, Cost: 80000
        i.nDice  = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case RedDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Red Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = RedDragonScaleMail;
        i.value = 10; // PV: 30, Weight: 20.0, Cost: 100000
        i.nDice  = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case BalanceDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Balance Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BalanceDragonScaleMail;
        i.value = 10; // PV: 30, Weight: 20.0, Cost: 100000
        i.nDice  = 3;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MultiHuedDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Multi-Hued Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = MultiHuedDragonScaleMail;
        i.value = 30; // PV: 30, Weight: 20.0, Cost: 150000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case PowerDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Power Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = PowerDragonScaleMail;
        i.value = 40; // PV: 40, Weight: 20.0, Cost: 300000
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    //
    case SmallBuckler:{
        i.name = malloc(128);
        strcpy(i.name, "Small Buckler");
        i.pos   = (Position){0, 0};
        i.type  = SmallBuckler;
        i.value = 1; // DB: 2, Weight: 3.0, Cost: 15
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case WoodenRoundShield:{
        i.name = malloc(128);
        strcpy(i.name, "Wooden Round Shield");
        i.pos   = (Position){0, 0};
        i.type  = WoodenRoundShield;
        i.value = 3; // DB: 3, Weight: 5.0, Cost: 30
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case ReinforcedWoodenShield:{
        i.name = malloc(128);
        strcpy(i.name, "Reinforced Wooden Shield");
        i.pos   = (Position){0, 0};
        i.type  = ReinforcedWoodenShield;
        i.value = 2; // DB: 4, Weight: 7.0, Cost: 50
        i.nDice  = 2;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case IronRoundShield:{
        i.name = malloc(128);
        strcpy(i.name, "Iron Round Shield");
        i.pos   = (Position){0, 0};
        i.type  = IronRoundShield;
        i.value = 5; // DB: 5, Weight: 10.0, Cost: 90
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case SpikedShield:{
        i.name = malloc(128);
        strcpy(i.name, "Spiked Shield");
        i.pos   = (Position){0, 0};
        i.type  = SpikedShield;
        i.value = 5; // DB: 5, Weight: 11.0, Cost: 120
        i.nDice  = 1; // Can also be used as a weapon
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case HeaterShield:{
        i.name = malloc(128);
        strcpy(i.name, "Heater Shield");
        i.pos   = (Position){0, 0};
        i.type  = HeaterShield;
        i.value = 3; // DB: 6, Weight: 9.0, Cost: 150
        i.nDice  = 2;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case SteelKiteShield:{
        i.name = malloc(128);
        strcpy(i.name, "Steel Kite Shield");
        i.pos   = (Position){0, 0};
        i.type  = SteelKiteShield;
        i.value = 7; // DB: 7, Weight: 12.0, Cost: 250
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case TowerShield:{
        i.name = malloc(128);
        strcpy(i.name, "Tower Shield");
        i.pos   = (Position){0, 0};
        i.type  = TowerShield;
        i.value = 9; // DB: 9, Weight: 20.0, Cost: 400
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MithrilShield:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Shield");
        i.pos   = (Position){0, 0};
        i.type  = MithrilShield;
        i.value = 4; // DB: 8, Weight: 6.0, Cost: 5000
        i.nDice  = 2;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case DragonscaleShield:{
        i.name = malloc(128);
        strcpy(i.name, "Dragonscale Shield");
        i.pos   = (Position){0, 0};
        i.type  = DragonscaleShield;
        i.value = 7; // DB: 7, Weight: 8.0, Cost: 8000
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case AdamantiteShield:{
        i.name = malloc(128);
        strcpy(i.name, "Adamantite Shield");
        i.pos   = (Position){0, 0};
        i.type  = AdamantiteShield;
        i.value = 10; // DB: 10, Weight: 25.0, Cost: 12000
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case AegisOfReflection:{
        i.name = malloc(128);
        strcpy(i.name, "Aegis of Reflection");
        i.pos   = (Position){0, 0};
        i.type  = AegisOfReflection;
        i.value = 6; // DB: 12, Weight: 10.0, Cost: 50000
        i.nDice  = 2;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }

    case LeatherCap:{
        i.name = malloc(128);
        strcpy(i.name, "Leather Cap");
        i.pos   = (Position){0, 0};
        i.type  = LeatherCap;
        i.value = 1; // DB: 1, Weight: 1.0, Cost: 10
        i.nDice = 1;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case PaddedHood:{
        i.name = malloc(128);
        strcpy(i.name, "Padded Hood");
        i.pos   = (Position){0, 0};
        i.type  = PaddedHood;
        i.value = 2; // DB: 2, Weight: 1.5, Cost: 25
        i.nDice = 1;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case IronCap:{
        i.name = malloc(128);
        strcpy(i.name, "Iron Cap");
        i.pos   = (Position){0, 0};
        i.type  = IronCap;
        i.value = 3; // DB: 3, Weight: 4.0, Cost: 60
        i.nDice = 1;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case NasalHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Nasal Helm");
        i.pos   = (Position){0, 0};
        i.type  = NasalHelm;
        i.value = 2; // DB: 4, Weight: 5.0, Cost: 110
        i.nDice = 2;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Spangenhelm:{
        i.name = malloc(128);
        strcpy(i.name, "Spangenhelm");
        i.pos   = (Position){0, 0};
        i.type  = Spangenhelm;
        i.value = 5; // DB: 5, Weight: 6.0, Cost: 200
        i.nDice = 1;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Bascinet:{
        i.name = malloc(128);
        strcpy(i.name, "Bascinet");
        i.pos   = (Position){0, 0};
        i.type  = Bascinet;
        i.value = 2; // DB: 6, Weight: 7.0, Cost: 350
        i.nDice = 3;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case GreatHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Great Helm");
        i.pos   = (Position){0, 0};
        i.type  = GreatHelm;
        i.value = 4; // DB: 8, Weight: 10.0, Cost: 600
        i.nDice = 2;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case MithrilHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Helm");
        i.pos   = (Position){0, 0};
        i.type  = MithrilHelm;
        i.value = 7; // DB: 7, Weight: 3.0, Cost: 4500
        i.nDice = 1;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case AdamantiteHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Adamantite Helm");
        i.pos   = (Position){0, 0};
        i.type  = AdamantiteHelm;
        i.value = 2; // DB: 9, Weight: 12.0, Cost: 10000
        i.nDice = 3;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case DragonboneHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Dragonbone Helm");
        i.pos   = (Position){0, 0};
        i.type  = DragonboneHelm;
        i.value = 1; // DB: 8, Weight: 5.0, Cost: 15000
        i.nDice = 8;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case CrownOfWisdom:{
        i.name = malloc(128);
        strcpy(i.name, "Crown of Wisdom");
        i.pos   = (Position){0, 0};
        i.type  = CrownOfWisdom;
        i.value = 3; // DB: 3, Weight: 2.0, Cost: 25000
        i.nDice = 1;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    
    case LetherBoots:{
        i.name = malloc(128);
        strcpy(i.name, "Lether Boots");
        i.pos   = (Position){0, 0};
        i.type  = LetherBoots;
        i.value = 1; // DB: 3, Weight: 2.0, Cost: 25000
        i.nDice = 1;
        i.to    = EQUIPTED_LEGS;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }

    case MetalBoots:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Boots");
        i.pos   = (Position){0, 0};
        i.type  = MetalBoots;
        i.value = 3; // DB: 3, Weight: 2.0, Cost: 25000
        i.nDice = 1;
        i.to    = EQUIPTED_LEGS;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }

    case LetherGloves:{
        i.name = malloc(128);
        strcpy(i.name, "Lether Gloves");
        i.pos   = (Position){0, 0};
        i.type  = LetherGloves;
        i.value = 1; // DB: 3, Weight: 2.0, Cost: 25000
        i.nDice = 1;
        i.to    = EQUIPTED_HAND;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }

    case MetalGloves:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Gloves");
        i.pos   = (Position){0, 0};
        i.type  = MetalGloves;
        i.value = 2; // DB: 3, Weight: 2.0, Cost: 25000
        i.nDice = 1;
        i.to    = EQUIPTED_HAND;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }


    case Bow:{
        i.name = malloc(128);
        strcpy(i.name, "Bow");
        i.pos   = (Position){0, 0};
        i.type  = Bow;
        i.value = 3; 
        i.nDice  = rand()%2+1;
        i.to    = EQUIPTED_RANGE;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Arrows:{
        i.name = malloc(128);
        strcpy(i.name, "Arrow");
        i.pos   = (Position){0, 0};
        i.type  = Arrows;
        i.stats = (Stats){0, 0, 0, 0, 0, 0, 0, 0, 0};
        i.value = 3 + rand()%20; 
        i.nDice = 0;
        i.to    = EQUIPTED_MUTITION;
        i.fire  = Bow;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }
    case Tourch:{
        i.name = malloc(128);
        strcpy(i.name, "Tourch");
        i.pos   = (Position){0, 0};
        i.type  = Tourch;
        i.stats = (Stats){0, 0, 0, 0, 0, 0, 0, 0, 0};
        i.value = rand()%100 + 100; 
        i.value = 100;
        i.nDice = 0;
        i.to    = EQUIPTED_TOURCH;
        i.isEqu = isEqu;
        da_append(inventory, i);
        break;
    }

    default:
        ASSERT("Not defined item");
        break;
    }
}


void equipt_item(Item_DA* inventory, int whatItem){
    
    //Un
    
        for(int i = 0; i < inventory->count; i++){
        if(inventory->items[i].isEqu == true && inventory->items[i].to == inventory->items[whatItem].to){
            inventory->items[i].isEqu = false;
            break;
        }
    }
        inventory->items[whatItem].isEqu = true;
        
}

int  is_item_of_type_equ(Item_DA* inventory, Item_Equipted to){
    if(inventory->count == 0)
        return -1;
    for(int i = 0; i < inventory->count; i++){
        if(inventory->items[i].isEqu == true){
            if(inventory->items[i].to == to){               
                return i;
            }
        }
    }
    return -1;
}



void add_items_from_list(ChanceItem_DA* list, Item_DA* inventory) {
    
    for (int i = 0; i < list->count; i++) {
        float roll = rand_f32(); // [0,1]
        if (roll <= list->items[i].chance) {
            //printf("%s\n", ITEM_NAMES[(Item_Type)list->items[i].type]);
            add_item_to_inventory((Item_Type)list->items[i].type, inventory, 1);
        }
    }
}