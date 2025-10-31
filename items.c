#include "item.h"
#define ITEM_SPECIAL 0.1f
#define ITEM_CURSE   (ITEM_SPECIAL + 0.35f)

static void add_potion_item_to_inventory(Item_DA* inventory, Potion_Type potion, int isIdent){
    Item i = (Item){0};
    if(rand_f32() < 0.2f){
        i.isCursed = true;
    }
    else{
        i.isCursed = false;
    }
    i.to = EQUIPTED_USE_POTION;
    i.type = Potion;
    i.potion = potion;
    i.isIdent = false;
    switch(potion){
        case Potion_No:
            ASSERT("Non existant potion");
            break;
        case Potion_Healing:
            i.name = malloc(128);
            strcpy(i.name, "Potion of healing");
            
        break;
        case Potion_Str:
            i.name = malloc(128);
            strcpy(i.name, "Potion of strenght");
            
        break;    
        case Potion_Int:
            i.name = malloc(128);
            strcpy(i.name, "Potion of inteligenec");
            
        break;
        case Potion_Size:
            i.name = malloc(128);
            strcpy(i.name, "Potion of size");
            
        break;
        case Potion_Att:
            i.name = malloc(128);
            strcpy(i.name, "Potion of att");
            
        break;
        case Potion_Def:
            i.name = malloc(128);
            strcpy(i.name, "Potion of def");
            
        break;
        case Potion_Poison:
            i.name = malloc(128);
            strcpy(i.name, "Potion of poison");
            
        break;

	    case Potion_Gas:
        i.name = malloc(128);
            strcpy(i.name, "Potion of gas");
            
        break;

	    case Potion_Acid:
        i.name = malloc(128);
            strcpy(i.name, "Potion of acid");
            
        break;
	    case Potion_HealingGas:
        i.name = malloc(128);
            strcpy(i.name, "Potion of healing gas");
            
        break;


        default:
            ASSERT("Potion NOT implemented");
            break;    
    }
    da_append(inventory, i);

    DROP(isIdent);
}


static void add_scroll_item_to_inventory(Item_DA* inventory, Scroll_Type scroll, int isIdent){
    Item i = (Item){0};
    if(rand_f32() < 0.2f){
        i.isCursed = true;
    }
    else{
        i.isCursed = false;
    }
    i.to = EQUIPTED_USE_SCROL;
    i.type = Scroll;
    i.potion = Potion_No;
    if(scroll != Scroll_No){
        switch (scroll)
        {
        case Scroll_Teleport:
            i.name = malloc(128);
            i.scroll = Scroll_Teleport;
            //if(isIdent)

            strcpy(i.name, "Scroll of teleport");
            
            //else
            //    strcpy(i.name, "Scroll of unonw origin");

            da_append(inventory, i);    
            break;
        
        case Scroll_Identif:
            i.name = malloc(128);
            i.scroll = Scroll_Identif;
            //if(isIdent)
            strcpy(i.name, "Scroll of identify");
            //else
            //    strcpy(i.name, "Scroll of unonw origin");

            da_append(inventory, i);    
            break;

        case Scroll_EnchantW:
            i.name = malloc(128);
            i.scroll = Scroll_EnchantW;
            //if(isIdent)
            strcpy(i.name, "Scroll of enchant wepon");
            //else
            //    strcpy(i.name, "Scroll of unonw origin");

            da_append(inventory, i);    
            break;    
        case Scroll_EnchantA:
            i.name = malloc(128);
            i.scroll = Scroll_EnchantA;
            //if(isIdent)
            strcpy(i.name, "Scroll of enchant armor");
            //else
            //    strcpy(i.name, "Scroll of unonw origin");

            da_append(inventory, i);    
            break;    
        
        case Scroll_SummonMonster:
            i.name = malloc(128);
            i.isCursed = false; //Not posible to be cursed
            i.scroll = Scroll_SummonMonster;
            //if(isIdent)
            strcpy(i.name, "Scroll of summon monster");
            
            da_append(inventory, i);    
            break;    
        case Scroll_Acq:
            i.name = malloc(128);
            i.scroll = Scroll_Acq;
            //if(isIdent)
            strcpy(i.name, "Scroll of acquairment");
            
            da_append(inventory, i);    
            break;    
        case Scroll_Stun:
            i.name = malloc(128);
            i.scroll = Scroll_Stun;
            //if(isIdent)
            strcpy(i.name, "Scroll of stun");
           
            da_append(inventory, i);    
            break;
        case Scroll_Scare: 
        i.name = malloc(128);
            i.scroll = Scroll_Scare;
            i.isCursed = false;
            //if(isIdent)
        
            strcpy(i.name, "Scroll of scare monster");
            da_append(inventory, i);    
            break;
	    case Scroll_Hunt: 
            i.name = malloc(128);
            i.scroll = Scroll_Hunt;
            i.isCursed = true;
            //if(isIdent)
            strcpy(i.name, "Scroll of hunt monster");
            da_append(inventory, i);    
            break;
	    case Scroll_Confuse:
             i.name = malloc(128);
            i.scroll = Scroll_Confuse;
            strcpy(i.name, "Scroll of confusion");
            
            da_append(inventory, i);    
            break; 
        
        case Scroll_Levitation:
            i.name = malloc(128);
            i.scroll = Scroll_Levitation;
            strcpy(i.name, "Scroll of levitation");
            
            da_append(inventory, i);    
            break; 
        
        case Scroll_Telepaty:
            i.name = malloc(128);
            i.scroll = Scroll_Telepaty;
            strcpy(i.name, "Scroll of telepaty");
            
            da_append(inventory, i);    
            break; 

         case Scroll_Water:
            i.name = malloc(128);
            i.scroll = Scroll_Water;
            strcpy(i.name, "Scroll of summon water");
            
            da_append(inventory, i);    
            break;     
        
         case Scroll_Negation:
            i.name = malloc(128);
            i.scroll = Scroll_Negation;
            strcpy(i.name, "Scroll of negation");
            
            da_append(inventory, i);    
            break;     
        
        case Scroll_Incinarat:
            i.name = malloc(128);
            i.scroll = Scroll_Incinarat;
            strcpy(i.name, "Scroll of incinerate");
            
            da_append(inventory, i);    
            break;    
        
        case Scroll_MagicMaping:
            i.name = malloc(128);
            i.scroll = Scroll_MagicMaping;
            strcpy(i.name, "Scroll of magic maping");
            
            da_append(inventory, i);    
            break;


        case Scroll_Recharging:
            i.name = malloc(128);
            i.scroll = Scroll_Recharging;
            strcpy(i.name, "Scroll of recharging");
            
            da_append(inventory, i);    
            break;    
       
        case Scroll_Sacrifice:
            i.name = malloc(128);
            i.scroll = Scroll_Sacrifice;
            strcpy(i.name, "Scroll of sacrifice");
            
            da_append(inventory, i);    
            break;    

        case Scroll_Fate:
            i.name = malloc(128);
            i.scroll = Scroll_Fate;
            
            

            strcpy(i.name, "Scroll of fate");
            
            da_append(inventory, i);    
            break;
        
         case Scroll_Amnesia:
            i.name = malloc(128);
            i.scroll = Scroll_Amnesia;
            i.isCursed = false;
            
            strcpy(i.name, "Scroll of amnesia");
            
            da_append(inventory, i);    
            break;    
         
        case Scroll_Gambler:
            i.name = malloc(128);
            i.scroll = Scroll_Gambler;
            i.isCursed = false;
            strcpy(i.name, "Scroll of gambling");
            
            da_append(inventory, i);    
            break;   
        
        
        //case Scroll_Chasm:
        //    i.name = malloc(128);
        //    i.scroll = Scroll_Chasm;
            
        //    strcpy(i.name, "Scroll of chasm");
            
        //    da_append(inventory, i);    
        //    break;        
        
        case Scroll_Calcific:
            i.name = malloc(128);
            i.scroll = Scroll_Calcific;
            
            strcpy(i.name, "Scroll of calfication");
            
            da_append(inventory, i);    
            break;
            
            
        case Scroll_Bprince:
            i.name = malloc(128);
            i.scroll = Scroll_Bprince;
            
            strcpy(i.name, "Scroll of bprince");
            
            da_append(inventory, i);    
            break;
            
        case Scroll_RemoveCurse:
            i.name = malloc(128);
            i.scroll = Scroll_RemoveCurse;
            
            strcpy(i.name, "Scroll of remove curse");
            
            da_append(inventory, i);    
            break;
        
        

        
        default:
            ASSERT("Not implemented item");    
        break;
        }
    }

//    if(i.isCursed){
 //       strcat(i.name, " cursed");
  //  }


    DROP(isIdent);
}

void add_item_to_inventory(Item_Type type, Item_DA* inventory, Scroll_Type scroll, Potion_Type potion, int isEqu, int isIdentScrool){
    Item i = (Item){0};
    if(type == Scroll){
        add_scroll_item_to_inventory(inventory, scroll, isIdentScrool);
    }
    else if(type == Potion){
        add_potion_item_to_inventory(inventory, potion, isIdentScrool);
        printf("Add potion");
    }
    else{
    int isSpecialItem = 1000;
    float chance = rand_f32(); 
    int value = rand()%5 + 1;
    if(chance < ITEM_SPECIAL){
        isSpecialItem = rand()%50;
        i.isCursed = false;
        
    }
    else if(chance > ITEM_SPECIAL && chance < ITEM_CURSE){
        isSpecialItem = rand()%50;
        value *=-1;
        i.isCursed = true;
    }
    else{
        i.isCursed = false;
    } 
    //Str
    if(isSpecialItem < 10 && isSpecialItem != 0){
        i.stats = (Stats){value, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    //Dex
    else if(isSpecialItem > 10 && isSpecialItem < 20){
        i.stats = (Stats){ 0, value, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    //Int 
    else if(isSpecialItem > 20 && isSpecialItem < 30){
        i.stats = (Stats){ 0, 0, value, 0, 0, 0, 0, 0, 0, 0};
    }
    //Cons
    else if(isSpecialItem > 30 && isSpecialItem < 40){
        i.stats = (Stats){0, 0, 0, value, 0, 0, 0, 0, 0, 0};
    }
    else{
        i.stats = (Stats){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }

    i.isIdent = false;
switch (type){
    case Sword:{
        i.name  = malloc(128);
        strcpy(i.name, "Sword");
        i.pos   = (Position){0, 0};
        i.type  = Sword;
        i.value = 3; 
        i.nDice  = rand()%2+1;
        i.to    = EQUIPTED_WEPON;
        i.strReq = 13;
        i.isEqu = isEqu;
        i.itemChance = 3.0f; // Medium common weapon
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
        i.strReq = 12;
        i.itemChance = 5.0f; // Very common, weak weapon
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
        i.strReq = 12;
        i.itemChance = 4.5f; // Common weak weapon
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
        i.strReq = 12;
        i.itemChance = 4.0f; // Common basic weapon
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
        i.strReq = 10;
        i.itemChance = 4.0f; // Common tool/weapon
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
        i.strReq = 12;
        i.itemChance = 3.5f; // Uncommon sidearm
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
        i.strReq = 12;
        i.itemChance = 3.0f; // Uncommon specialty weapon
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
        i.strReq = 13;
        i.itemChance = 3.0f; // Uncommon polearm
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
        i.strReq = 13;
        i.itemChance = 2.5f; // Rare finesse weapon
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
        i.strReq = 13;
        i.itemChance = 2.5f; // Rare light weapon
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
        i.strReq = 13;
        i.itemChance = 2.0f; // Rare cavalry weapon
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
        i.strReq = 10;
        i.itemChance = 3.5f; // Uncommon tool/weapon
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
        i.strReq = 13;
        i.itemChance = 2.0f; // Rare naval weapon
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
        i.strReq = 13;
        i.itemChance = 2.5f; // Rare polearm
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
        i.strReq = 13;
        i.itemChance = 1.5f; // Very rare polearm
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
        i.strReq = 13;
        i.itemChance = 2.5f; // Rare blunt weapon
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
        i.strReq = 13;
        i.itemChance = 2.0f; // Rare curved sword
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
        i.strReq = 14;
        i.itemChance = 2.0f; // Rare staff weapon
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
        i.strReq = 14;
        i.itemChance = 1.5f; // Very rare flail weapon
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
        i.strReq = 14;
        i.itemChance = 1.5f; // Very rare heavy weapon
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
        i.strReq = 14;
        i.itemChance = 1.0f; // Very rare cavalry weapon
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
        i.strReq = 15;
        i.itemChance = 1.5f; // Very rare curved sword
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
        i.strReq = 14;
        i.itemChance = 1.5f; // Very rare versatile sword
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
        i.strReq = 15;
        i.itemChance = 1.0f; // Very rare axe
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
        i.strReq = 15;
        i.itemChance = 1.0f; // Very rare military axe
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
        i.strReq = 13;
        i.itemChance = 1.5f; // Very rare polearm
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
        i.strReq = 14;
        i.itemChance = 1.0f; // Very rare flail weapon
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
        i.strReq = 14;
        i.itemChance = 1.0f; // Very rare long polearm
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
        i.strReq = 13;
        i.itemChance = 1.0f; // Very rare polearm
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
        i.strReq = 14;
        i.itemChance = 0.8f; // Extremely rare polearm
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
        i.strReq = 14;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        i.itemChance = 0.7f; // Extremely rare exotic weapon
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
        i.strReq = 14;
        i.itemChance = 0.7f; // Extremely rare poleaxe
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
        i.strReq = 16;
        i.itemChance = 0.5f; // Extremely rare heavy weapon
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
        i.strReq = 16;
        i.itemChance = 0.5f; // Extremely rare heavy mace
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
        i.strReq = 17;
        i.itemChance = 0.4f; // Extremely rare massive flail
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
        i.strReq = 17;
        i.itemChance = 0.3f; // Legendary Scottish weapon
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
        i.strReq = 16;
        i.to    = EQUIPTED_WEPON;
        i.isEqu = isEqu;
        i.itemChance = 0.8f; // Extremely rare converted tool
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
        i.strReq = 16;
        i.itemChance = 0.5f; // Extremely rare greatsword
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
        i.strReq = 17;
        i.itemChance = 0.3f; // Legendary execution weapon
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
        i.strReq = 16;
        i.itemChance = 0.2f; // Legendary magical weapon
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
        i.strReq = 18;
        i.itemChance = 0.1f; // Mythical chaos weapon
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
        i.strReq = 18;
        i.itemChance = 0.1f; // Mythical magical mace
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
        i.strReq = 12;
        i.itemChance = 4.5f; // Common basic armor
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
        i.strReq = 10;
        i.itemChance = 5.0f; // Very common trash armor
        da_append(inventory, i);
        break;
    }
    case Robe:{
        i.name = malloc(128);
        strcpy(i.name, "Robe");
        i.pos   = (Position){0, 0};
        i.type  = Robe;
        i.value = 2;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 10;
        i.itemChance = 4.5f; // Common cloth armor
        da_append(inventory, i);
        break;
    }
    case SoftLeatherArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Soft Leather Armour");
        i.pos   = (Position){0, 0};
        i.type  = SoftLeatherArmour;
        i.value = 4;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 10;
        i.itemChance = 4.0f; // Common light armor
        da_append(inventory, i);
        break;
    }
    case SoftStuddedLeather:{
        i.name = malloc(128);
        strcpy(i.name, "Soft Studded Leather");
        i.pos   = (Position){0, 0};
        i.type  = SoftStuddedLeather;
        i.value = 5;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 12;
        i.itemChance = 3.5f; // Uncommon reinforced armor
        da_append(inventory, i);
        
        break;
    }
    case HardLeatherArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Hard Leather Armour");
        i.pos   = (Position){0, 0};
        i.type  = HardLeatherArmour;
        i.value = 3;
        i.nDice  = 2;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 12;
        i.itemChance = 3.0f; // Uncommon medium armor
        da_append(inventory, i);
        break;
    }
    case HardStuddedLeather:{
        i.name = malloc(128);
        strcpy(i.name, "Hard Studded Leather");
        i.pos   = (Position){0, 0};
        i.type  = HardStuddedLeather;
        i.value = 7;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 14;
        i.itemChance = 2.5f; // Rare heavy leather
        da_append(inventory, i);
        break;
    }
    case LeatherScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Leather Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = LeatherScaleMail;
        i.value = 11;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 16;
        i.itemChance = 2.0f; // Rare composite armor
        da_append(inventory, i);
        break;
    }
    case MetalScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = MetalScaleMail;
        i.value = 13;
        i.nDice  = 1;
        i.strReq = 14;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 1.5f; // Very rare metal armor
        da_append(inventory, i);
        break;
    }
    case RustyChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Rusty Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = RustyChainMail;
        i.value = 7;
        i.nDice  = 2;
        i.strReq = 14;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 2.0f; // Rare damaged mail
        da_append(inventory, i);
        break;
    }
    case ChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = ChainMail;
        i.value = 7;
        i.nDice  = 2;
        i.strReq = 14;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 1.5f; // Very rare quality mail
        da_append(inventory, i);
        break;
    }
    case DoubleChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Double Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = DoubleChainMail;
        i.value = 8;
        i.nDice  = 2;
        i.strReq = 16;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 1.0f; // Very rare reinforced mail
        da_append(inventory, i);
        break;
    }
    case AugmentedChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Augmented Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = AugmentedChainMail;
        i.value = 8;
        i.nDice = 2;
        i.strReq = 16;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.8f; // Extremely rare enhanced mail
        da_append(inventory, i);
        break;
    }
    case BarChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Bar Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = BarChainMail;
        i.value = 6;
        i.nDice = 3;
        i.strReq = 16;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.7f; // Extremely rare specialty mail
        da_append(inventory, i);
        break;
    }
    case MetalBrigandineArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Brigandine Armour");
        i.pos   = (Position){0, 0};
        i.type  = MetalBrigandineArmour;
        i.value = 19;
        i.nDice  = 1;
        i.strReq = 18;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.6f; // Extremely rare plate armor
        da_append(inventory, i);
        break;
    }
    case PartialPlateArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Partial Plate Armour");
        i.pos   = (Position){0, 0};
        i.type  = PartialPlateArmour;
        i.value = 22;
        i.nDice  = 1;
        i.strReq = 18;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.5f; // Extremely rare partial plate
        da_append(inventory, i);
        break;
    }
    case MetalLamellarArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Lamellar Armour");
        i.pos   = (Position){0, 0};
        i.type  = MetalLamellarArmour;
        i.value = 23;
        i.nDice  = 1;
        i.strReq = 18;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.4f; // Legendary lamellar armor
        da_append(inventory, i);
        break;
    }
    case FullPlateArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Full Plate Armour");
        i.pos   = (Position){0, 0};
        i.type  = FullPlateArmour;
        i.value = 25;
        i.nDice  = 1;
        i.strReq = 18;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.3f; // Legendary full plate
        da_append(inventory, i);
        break;
    }
    case RibbedPlateArmour:{
        i.name = malloc(128);
        strcpy(i.name, "Ribbed Plate Armour");
        i.pos   = (Position){0, 0};
        i.type  = RibbedPlateArmour;
        i.value = 28;
        i.nDice  = 1;
        i.strReq = 18;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.2f; // Legendary reinforced plate
        da_append(inventory, i);
        break;
    }
    case MithrilChainMail:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Chain Mail");
        i.pos   = (Position){0, 0};
        i.type  = MithrilChainMail;
        i.value = 7;
        i.nDice = 4;
        i.strReq = 18;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.1f; // Mythical mithril armor
        da_append(inventory, i);
        break;
    }
    case MithrilPlateMail:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Plate Mail");
        i.pos   = (Position){0, 0};
        i.type  = MithrilPlateMail;
        i.value = 35;
        i.nDice  = 1;
        i.strReq = 19;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.08f; // Mythical mithril plate
        da_append(inventory, i);
        break;
    }
    case AdamantitePlateMail:{
        i.name = malloc(128);
        strcpy(i.name, "Adamantite Plate Mail");
        i.pos   = (Position){0, 0};
        i.type  = AdamantitePlateMail;
        i.value = 40;
        i.nDice  = 1;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.05f; // Mythical adamantite armor
        da_append(inventory, i);
        break;
    }
    case BronzeDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Bronze Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BronzeDragonScaleMail;
        i.value = 30;
        i.nDice  = 1;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.1f; // Mythical dragon scale
        da_append(inventory, i);
        break;
    }
    case BlackDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Black Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BlackDragonScaleMail;
        i.value = 30;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 20;
        i.itemChance = 0.1f; // Mythical dragon scale
        da_append(inventory, i);
        break;
    }
    case BlueDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Blue Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BlueDragonScaleMail;
        i.value = 30;
        i.nDice  = 1;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.strReq = 20;
        i.itemChance = 0.1f; // Mythical dragon scale
        da_append(inventory, i);
        break;
    }
    case WhiteDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "White Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = WhiteDragonScaleMail;
        i.value = 30;
        i.nDice  = 1;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.08f; // Mythical dragon scale
        da_append(inventory, i);
        break;
    }
    case GoldDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Gold Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = GoldDragonScaleMail;
        i.value = 30;
        i.nDice  = 1;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.08f; // Mythical dragon scale
        da_append(inventory, i);
        break;
    }
    case ShiningDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Shining Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = ShiningDragonScaleMail;
        i.value = 10;
        i.nDice  = 3;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.06f; // Mythical special dragon scale
        da_append(inventory, i);
        break;
    }
    case ChaosDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Chaos Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = ChaosDragonScaleMail;
        i.value = 10;
        i.nDice  = 3;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.06f; // Mythical special dragon scale
        da_append(inventory, i);
        break;
    }
    case GreenDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Green Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = GreenDragonScaleMail;
        i.value = 10;
        i.nDice  = 3;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.05f; // Mythical special dragon scale
        da_append(inventory, i);
        break;
    }
    case LawDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Law Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = LawDragonScaleMail;
        i.value = 10;
        i.nDice  = 3;
        i.strReq = 20;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.05f; // Mythical special dragon scale
        da_append(inventory, i);
        break;
    }
    case RedDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Red Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = RedDragonScaleMail;
        i.value = 10;
        i.nDice  = 3;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.04f; // Mythical special dragon scale
        da_append(inventory, i);
        break;
    }
    case BalanceDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Balance Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = BalanceDragonScaleMail;
        i.value = 10;
        i.nDice  = 3;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.04f; // Mythical special dragon scale
        da_append(inventory, i);
        break;
    }
    case MultiHuedDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Multi-Hued Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = MultiHuedDragonScaleMail;
        i.value = 30;
        i.nDice  = 1;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.03f; // Legendary multi-dragon scale
        da_append(inventory, i);
        break;
    }
    case PowerDragonScaleMail:{
        i.name = malloc(128);
        strcpy(i.name, "Power Dragon Scale Mail");
        i.pos   = (Position){0, 0};
        i.type  = PowerDragonScaleMail;
        i.value = 40;
        i.nDice  = 1;
        i.strReq = 20;
        i.to    = EQUIPTED_ARMOR;
        i.isEqu = isEqu;
        i.itemChance = 0.02f; // Ultimate dragon scale armor
        da_append(inventory, i);
        break;
    }
    //
    case SmallBuckler:{
        i.name = malloc(128);
        strcpy(i.name, "Small Buckler");
        i.pos   = (Position){0, 0};
        i.type  = SmallBuckler;
        i.value = 1;
        i.nDice  = 1;
        i.strReq = 12;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 4.5f; // Common small shield
        da_append(inventory, i);
        break;
    }
    case WoodenRoundShield:{
        i.name = malloc(128);
        strcpy(i.name, "Wooden Round Shield");
        i.pos   = (Position){0, 0};
        i.type  = WoodenRoundShield;
        i.value = 3;
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.strReq = 12;
        i.itemChance = 4.0f; // Common basic shield
        da_append(inventory, i);
        break;
    }
    case ReinforcedWoodenShield:{
        i.name = malloc(128);
        strcpy(i.name, "Reinforced Wooden Shield");
        i.pos   = (Position){0, 0};
        i.type  = ReinforcedWoodenShield;
        i.value = 2;
        i.nDice  = 2;
        i.strReq = 12;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 3.5f; // Uncommon reinforced shield
        da_append(inventory, i);
        break;
    }
    case IronRoundShield:{
        i.name = malloc(128);
        strcpy(i.name, "Iron Round Shield");
        i.pos   = (Position){0, 0};
        i.type  = IronRoundShield;
        i.value = 5;
        i.nDice  = 1;
        i.strReq = 12;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 3.0f; // Uncommon metal shield
        da_append(inventory, i);
        break;
    }
    case SpikedShield:{
        i.name = malloc(128);
        strcpy(i.name, "Spiked Shield");
        i.pos   = (Position){0, 0};
        i.type  = SpikedShield;
        i.value = 5;
        i.nDice  = 1;
        i.to    = EQUIPTED_SHIELD;
        i.strReq = 12;
        i.isEqu = isEqu;
        i.itemChance = 2.5f; // Rare specialty shield
        da_append(inventory, i);
        break;
    }
    case HeaterShield:{
        i.name = malloc(128);
        strcpy(i.name, "Heater Shield");
        i.pos   = (Position){0, 0};
        i.type  = HeaterShield;
        i.value = 3;
        i.nDice  = 2;
        i.strReq = 12;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 2.0f; // Rare knightly shield
        da_append(inventory, i);
        break;
    }
    case SteelKiteShield:{
        i.name = malloc(128);
        strcpy(i.name, "Steel Kite Shield");
        i.pos   = (Position){0, 0};
        i.type  = SteelKiteShield;
        i.value = 7;
        i.nDice  = 1;
        i.strReq = 13;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 1.5f; // Very rare quality shield
        da_append(inventory, i);
        break;
    }
    case TowerShield:{
        i.name = malloc(128);
        strcpy(i.name, "Tower Shield");
        i.pos   = (Position){0, 0};
        i.type  = TowerShield;
        i.value = 9;
        i.nDice  = 1;
        i.strReq = 14;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 1.0f; // Very rare large shield
        da_append(inventory, i);
        break;
    }
    case MithrilShield:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Shield");
        i.pos   = (Position){0, 0};
        i.type  = MithrilShield;
        i.value = 4;
        i.nDice  = 2;
        i.strReq = 14;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 0.3f; // Legendary mithril shield
        da_append(inventory, i);
        break;
    }
    case DragonscaleShield:{
        i.name = malloc(128);
        strcpy(i.name, "Dragonscale Shield");
        i.pos   = (Position){0, 0};
        i.type  = DragonscaleShield;
        i.value = 7;
        i.nDice  = 1;
        i.strReq = 14;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 0.2f; // Legendary dragon scale shield
        da_append(inventory, i);
        break;
    }
    case AdamantiteShield:{
        i.name = malloc(128);
        strcpy(i.name, "Adamantite Shield");
        i.pos   = (Position){0, 0};
        i.type  = AdamantiteShield;
        i.value = 10;
        i.nDice  = 1;
        i.strReq = 15;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 0.1f; // Mythical adamantite shield
        da_append(inventory, i);
        break;
    }
    case AegisOfReflection:{
        i.name = malloc(128);
        strcpy(i.name, "Aegis of Reflection");
        i.pos   = (Position){0, 0};
        i.type  = AegisOfReflection;
        i.value = 6;
        i.nDice  = 2;
        i.strReq = 15;
        i.to    = EQUIPTED_SHIELD;
        i.isEqu = isEqu;
        i.itemChance = 0.05f; // Ultimate magical shield
        da_append(inventory, i);
        break;
    }

    case LeatherCap:{
        i.name = malloc(128);
        strcpy(i.name, "Leather Cap");
        i.pos   = (Position){0, 0};
        i.type  = LeatherCap;
        i.value = 1;
        i.nDice = 1;
        i.strReq = 12;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 4.5f; // Common headgear
        da_append(inventory, i);
        break;
    }
    case PaddedHood:{
        i.name = malloc(128);
        strcpy(i.name, "Padded Hood");
        i.pos   = (Position){0, 0};
        i.type  = PaddedHood;
        i.value = 2;
        i.nDice = 1;
        i.strReq = 12;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 4.0f; // Common light helmet
        da_append(inventory, i);
        break;
    }
    case IronCap:{
        i.name = malloc(128);
        strcpy(i.name, "Iron Cap");
        i.pos   = (Position){0, 0};
        i.type  = IronCap;
        i.value = 3;
        i.nDice = 1;
        i.strReq = 13;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 3.5f; // Uncommon metal helmet
        da_append(inventory, i);
        break;
    }
    case NasalHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Nasal Helm");
        i.pos   = (Position){0, 0};
        i.type  = NasalHelm;
        i.value = 2;
        i.nDice = 2;
        i.strReq = 13;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 3.0f; // Uncommon full helmet
        da_append(inventory, i);
        break;
    }
    case Spangenhelm:{
        i.name = malloc(128);
        strcpy(i.name, "Spangenhelm");
        i.pos   = (Position){0, 0};
        i.type  = Spangenhelm;
        i.value = 5;
        i.nDice = 1;
        i.strReq = 13;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 2.5f; // Rare quality helmet
        da_append(inventory, i);
        break;
    }
    case Bascinet:{
        i.name = malloc(128);
        strcpy(i.name, "Bascinet");
        i.pos   = (Position){0, 0};
        i.type  = Bascinet;
        i.value = 2;
        i.nDice = 3;
        i.strReq = 13;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 2.0f; // Rare advanced helmet
        da_append(inventory, i);
        break;
    }
    case GreatHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Great Helm");
        i.pos   = (Position){0, 0};
        i.type  = GreatHelm;
        i.value = 4;
        i.nDice = 2;
        i.strReq = 14;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 1.5f; // Very rare full helmet
        da_append(inventory, i);
        break;
    }
    case MithrilHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Mithril Helm");
        i.pos   = (Position){0, 0};
        i.type  = MithrilHelm;
        i.value = 7;
        i.nDice = 1;
        i.strReq = 14;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 0.5f; // Extremely rare mithril helmet
        da_append(inventory, i);
        break;
    }
    case AdamantiteHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Adamantite Helm");
        i.pos   = (Position){0, 0};
        i.type  = AdamantiteHelm;
        i.value = 2;
        i.nDice = 3;
        i.strReq = 14;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 0.3f; // Legendary adamantite helmet
        da_append(inventory, i);
        break;
    }
    case DragonboneHelm:{
        i.name = malloc(128);
        strcpy(i.name, "Dragonbone Helm");
        i.pos   = (Position){0, 0};
        i.type  = DragonboneHelm;
        i.value = 1;
        i.nDice = 8;
        i.strReq = 14;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 0.2f; // Legendary dragonbone helmet
        da_append(inventory, i);
        break;
    }
    case CrownOfWisdom:{
        i.name = malloc(128);
        strcpy(i.name, "Crown of Wisdom");
        i.pos   = (Position){0, 0};
        i.type  = CrownOfWisdom;
        i.value = 3;
        i.nDice = 1;
        i.strReq = 11;
        i.to    = EQUIPTED_HEAD;
        i.isEqu = isEqu;
        i.itemChance = 0.1f; // Mythical magical crown
        da_append(inventory, i);
        break;
    }
    
    case LetherBoots:{
        i.name = malloc(128);
        strcpy(i.name, "Lether Boots");
        i.pos   = (Position){0, 0};
        i.type  = LetherBoots;
        i.value = 1;
        i.nDice = 1;
        i.strReq = 10;
        i.to    = EQUIPTED_LEGS;
        i.isEqu = isEqu;
        i.itemChance = 4.5f; // Common footwear
        da_append(inventory, i);
        break;
    }

    case MetalBoots:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Boots");
        i.pos   = (Position){0, 0};
        i.type  = MetalBoots;
        i.value = 3;
        i.nDice = 1;
        i.strReq = 13;
        i.to    = EQUIPTED_LEGS;
        i.isEqu = isEqu;
        i.itemChance = 3.0f; // Uncommon armored boots
        da_append(inventory, i);
        break;
    }

    case LetherGloves:{
        i.name = malloc(128);
        strcpy(i.name, "Lether Gloves");
        i.pos   = (Position){0, 0};
        i.type  = LetherGloves;
        i.value = 1;
        i.nDice = 1;
        i.strReq = 13;
        i.to    = EQUIPTED_HAND;
        i.isEqu = isEqu;
        i.itemChance = 4.5f; // Common handwear
        da_append(inventory, i);
        break;
    }

    case MetalGloves:{
        i.name = malloc(128);
        strcpy(i.name, "Metal Gloves");
        i.pos   = (Position){0, 0};
        i.type  = MetalGloves;
        i.value = 2;
        i.nDice = 1;
        i.strReq = 13;
        i.to    = EQUIPTED_HAND;
        i.isEqu = isEqu;
        i.itemChance = 3.0f; // Uncommon armored gloves
        da_append(inventory, i);
        break;
    }

    case Bow:{
        i.name = malloc(128);
        strcpy(i.name, "Bow");
        i.pos   = (Position){0, 0};
        i.type  = Bow;
        i.value = 3; 
        i.strReq = 13;
        i.nDice  = rand()%2+1;
        i.to    = EQUIPTED_RANGE;
        i.isEqu = isEqu;
        i.itemChance = 3.5f; // Uncommon ranged weapon
        da_append(inventory, i);
        break;
    }
    case Arrows:{
        i.name = malloc(128);
        strcpy(i.name, "Arrow");
        i.pos   = (Position){0, 0};
        i.type  = Arrows;
        i.stats = (Stats){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        i.value = 3 + rand()%20; 
        i.nDice = 0;
        i.strReq = 12;
        i.to    = EQUIPTED_MUTITION;
        i.fire  = Bow;
        i.isEqu = isEqu;
        i.itemChance = 5.0f; // Very common ammunition
        da_append(inventory, i);
        break;
    }
    case Tourch:{
        i.name = malloc(128);
        strcpy(i.name, "Tourch");
        i.pos   = (Position){0, 0};
        i.type  = Tourch;
        i.stats = (Stats){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        i.value = rand()%100 + 100; 
        i.value = 100;
        i.nDice = 0;
        i.to    = EQUIPTED_TOURCH;
        i.isEqu = isEqu;
        i.itemChance = 4.0f; // Common utility item
        da_append(inventory, i);
        break;
    }
    default:
        ASSERT("Not defined item");
        break;
    }
    }
}


int equipt_item(Item_DA* inventory, int whatItem){
    
    //Un
    
        for(int i = 0; i < inventory->count; i++){
        if(inventory->items[i].isEqu == true && inventory->items[i].to == inventory->items[whatItem].to){
            if(inventory->items[i].isCursed == true){
                return true;

            }
            inventory->items[i].isEqu = false;
            break;
        }
    }
        inventory->items[whatItem].isEqu = true;
        return false;
        
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
            printf("%s\n", ITEM_NAMES[(Item_Type)list->items[i].type]);
            add_item_to_inventory((Item_Type)list->items[i].type, inventory, Scroll_No, Potion_No, 1, false);
        }
    }
   // exit(-1);
}

void free_item(Item_DA* inventory, int item){
    if(inventory->items[item].name != NULL)
    free(inventory->items[item].name);
    inventory->items[item].type = -1;
    da_remove_unordered(inventory, item);
}
//Tbd other arrs
void random_item_generator(Item_DA* inventory, Position pos){
    const float chance = rand_f32() ;
    static int randomIter = 0;
    printf("random iter %d\n", randomIter++);
    const float chanceItem[] = {3.0,5.0,4.5,4.0,4.0,3.5,3.0,3.0,2.5,2.5,2.0,3.5,2.0,2.5,1.5,2.5,2.0,2.0,1.5,1.5,1.0,1.5,1.5,1.0,1.0,1.5,1.0,1.0,1.0,0.8,0.7,0.7,0.5,0.5,0.4,0.3,0.8,0.5,0.3,0.2,0.1,0.1,4.5,5.0,4.5,4.0,3.5,3.0,2.5,2.0,1.5,2.0,1.5,1.0,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.08,0.05,0.1,0.1,0.1,0.08,0.08,0.06,0.06,0.05,0.05,0.04,0.04,0.03,0.02,4.5,4.0,3.5,3.0,2.5,2.0,1.5,1.0,0.3,0.2,0.1,0.05,4.5,4.0,3.5,3.0,2.5,2.0,1.5,0.5,0.3,0.2,0.1,4.5,3.0,4.5,3.0,3.5,5.0,4.0}; 
    if(chance <= 0.30){
        int type = 0;
        while(1){
            type = (rand()%Item_Num)%(sizeof(chanceItem) / sizeof(float)); 
            float chanceS = rand_f32()*100.0f;
            if(chanceS < chanceItem[type]){
                break;
            }
        }
        
        add_item_to_inventory(type, inventory, Scroll_No, Potion_No, false, false);
        //inventory->items[inventory->count].pos = pos;  
        }
    else if(chance > 0.30  && chance <= 0.50){
         int potion_type = (rand()%(Potion_Num - 1) + 1); 
         //printf("Porion\n");
         add_item_to_inventory(Potion, inventory, Scroll_No, potion_type, false, false);
         //printf("Porion\n");
    }    
	else{
		const float chanceScroll[] = {4.0,4.5,3.0,3.0,2.5,1.5,3.5,3.0,2.0,3.0,3.5,2.5,2.0,1.5,2.0,2.5,2.0,1.0,0.5,1.5,1.0,1.0,0.5,3.0};
        int scrollType = rand()%(Scroll_Num - 1) + 1;
        while(1){
            scrollType = (rand()%(Scroll_Num - 1) + 1); 
            float chanceS = rand_f32()*100.0f;
            if(chanceS < chanceScroll[scrollType%(sizeof(chanceScroll) / sizeof(float))]){
                break;
            }
        }
        add_item_to_inventory(Scroll, inventory, scrollType, Potion_No, false, false);

		}
       
       DROP(pos); 

      
}

