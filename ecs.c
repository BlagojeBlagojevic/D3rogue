
#define INF 255
#include "ecs.h"
#include <stdlib.h>
#include <string.h>

//Init of what ent coude be 
void load_global_ent(Global_Ent_DA* ent, const char* name){

	char *content = malloc(MAX_SIZE_OF_JSON);
	memset(content, '\0', MAX_SIZE_OF_JSON);
	FILE *f = fopen(name, "r");
	if(f == NULL) {
		ASSERT("Sprite JSON does not exist\n\n");
		//TBD Error windows popup or something
		}
	const int  size = fread(content, sizeof(char), MAX_SIZE_OF_JSON, f);
	DROP(size);
	//LOG("%s\n", content);
	cJSON *json = cJSON_Parse(content);
	//free(content);
	ERR_JSON(json);
	cJSON *e = cJSON_GetObjectItemCaseSensitive(json, "ent");
	ERR_JSON(e);
	cJSON *temp = NULL;
	Global_Ent g = {0};
	cJSON_ArrayForEach(temp, e){
		cJSON* name          = cJSON_GetObjectItemCaseSensitive(temp, "name");
		ERR_JSON(name);
		g.name = malloc(128); 
		strcpy(g.name, name->valuestring);
		cJSON* cOMP_POSITION = cJSON_GetObjectItemCaseSensitive(temp, "COMP_POSITION");ERR_JSON(cOMP_POSITION);
		{
				cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_POSITION, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					
					g.masks |= COMP_POSITION; //is inferd after	
					//exit(-1);
				} 
			}
		
		cJSON* cOMP_RENDER   = cJSON_GetObjectItemCaseSensitive(temp, "COMP_RENDER"); 
		ERR_JSON(cOMP_RENDER);
		{
				cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_RENDER, "is");
				ERR_JSON(is);
				if(is->valueint == true){
				
					cJSON* type = cJSON_GetObjectItemCaseSensitive(cOMP_RENDER, "type");
					ERR_JSON(type);
					g.renderable.type = (Sprite_Type)type->valueint;  
					g.masks |= COMP_RENDER;	
					//exit(-1);
				} 
			}
		cJSON* cOMP_HEALTH   = cJSON_GetObjectItemCaseSensitive(temp, "COMP_HEALTH"); 
		ERR_JSON(cOMP_HEALTH);
		{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_HEALTH, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					
					cJSON* health = cJSON_GetObjectItemCaseSensitive(cOMP_HEALTH, "health");
					ERR_JSON(health);
					cJSON* maxhealth = cJSON_GetObjectItemCaseSensitive(cOMP_HEALTH, "maxhealth");
					ERR_JSON(maxhealth);
					g.health.current = health->valueint;
					g.health.max = maxhealth->valueint;
					g.masks |= COMP_HEALTH; //is inferd after	
					//exit(-1);
				}
		}
		cJSON* cOMP_MONSTER  = cJSON_GetObjectItemCaseSensitive(temp, "COMP_MONSTER"); 
		ERR_JSON(cOMP_MONSTER);{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_MONSTER, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					g.masks |= COMP_MONSTER;
				}
		}
	
		cJSON* cOMP_PLAYER   = cJSON_GetObjectItemCaseSensitive(temp, "COMP_PLAYER"); 
		ERR_JSON(cOMP_PLAYER);{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_PLAYER, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					g.masks |= COMP_PLAYER;
				}
		}
		cJSON* cOMP_INPUT    = cJSON_GetObjectItemCaseSensitive(temp, "COMP_INPUT"); 
		ERR_JSON(cOMP_INPUT);{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_INPUT, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					g.masks |= COMP_INPUT;
					//g.input.z = 0.4
					cJSON* isAqua = cJSON_GetObjectItemCaseSensitive(temp, "aqua");
					ERR_JSON(isAqua);
					g.input.isAquatic = isAqua->valueint;
				}
		}
		cJSON* cOMP_STATS    = cJSON_GetObjectItemCaseSensitive(temp, "COMP_STATS"); 
		ERR_JSON(cOMP_STATS);{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					
					cJSON* str = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "str");
					ERR_JSON(str);
					g.stats.str = str->valueint;
					
					cJSON* dex = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "dex");
					ERR_JSON(dex);
					g.stats.dex = dex->valueint;
					
					cJSON* inte = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "inte");
					ERR_JSON(inte);
					g.stats.inte = inte->valueint;

					cJSON* cons = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "cons");
					ERR_JSON(cons);
					g.stats.cons = cons->valueint;
					
					cJSON* morale = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "morale");
					ERR_JSON(morale);
					g.stats.morale = morale->valueint;
				
					cJSON* perception = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "perception");
					ERR_JSON(perception);
					g.stats.perception = perception->valueint;
				
					cJSON* stealth = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "stealth");
					ERR_JSON(stealth);
					g.stats.stealth = stealth->valueint;
					
					cJSON* dmgmax = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "dmgmax");
					ERR_JSON(dmgmax);
					g.stats.dmgMax = dmgmax->valueint;

					cJSON* dmgmin = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "dmgmin");
					ERR_JSON(dmgmin);
					g.stats.dmgMin = dmgmin->valueint;

					
					cJSON* defence = cJSON_GetObjectItemCaseSensitive(cOMP_STATS, "defence");
					ERR_JSON(defence);
					g.stats.defence = defence->valueint;
					
					
					g.masks |= COMP_STATS;
				}
		}
		cJSON* cOMP_STATE    = cJSON_GetObjectItemCaseSensitive(temp, "COMP_STATE"); 
		ERR_JSON(cOMP_STATE);{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "is");
				ERR_JSON(is);
				if(is->valueint == true){
					//"is":true, "current":0, "chancesR":0.5, "chancesH":0.5, "chancesW":0.5, "chancesRe":0.5, "chancesB":0.5
					cJSON* current = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "current");
					ERR_JSON(current);
					g.state.current = (State_Monster)current->valueint;
					
					cJSON* chanceR = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceR");
					ERR_JSON(chanceR);
					g.state.chancesR = (float)chanceR->valuedouble;
					
					cJSON* chanceH = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceH");
					ERR_JSON(chanceH);
					g.state.chancesH = (float)chanceH->valuedouble;

					cJSON* chanceW = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceW");
					ERR_JSON(chanceW);
					g.state.chancesW = (float)chanceW->valuedouble;

					//cJSON* chanceRe = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceRe");
					//ERR_JSON(chanceRe);
					//g.state.chancesRe = (float)chanceRe->valuedouble;

					cJSON* chanceB = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceB");
					ERR_JSON(chanceB);
					g.state.chancesB = (float)chanceB->valuedouble;
					cJSON* chanceRange = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceRange");
					ERR_JSON(chanceRange);
					g.state.chanceRange = (float)chanceRange->valuedouble;
					
					
					g.masks |= COMP_STATE;
				}
		}	
		cJSON* cOMP_OPEN     = cJSON_GetObjectItemCaseSensitive(temp, "COMP_OPEN");
		ERR_JSON(cOMP_OPEN);{
			cJSON* is = cJSON_GetObjectItemCaseSensitive(cOMP_OPEN, "is");
			if(is->valueint == true){
				ASSERT("Not implemnted");
			}
		}
		
		//Items
		cJSON*  ITEMS  = cJSON_GetObjectItemCaseSensitive(temp, "ITEMS");
		cJSON*  I;
		//int counter = 0;
		g.item = (ChanceItem_DA){0};
		//da_append(&g.item, item);
		ERR_JSON(ITEMS);
		cJSON_ArrayForEach(I, ITEMS) {
		ChanceItem item = {0,0.0f};
		cJSON *chance_obj = cJSON_GetObjectItem(I, "chance");
		cJSON *name_obj = cJSON_GetObjectItem(I, "name");
		
		if (chance_obj && name_obj) {
			item.chance = (float)chance_obj->valuedouble;
			const char *item_name = name_obj->valuestring;
			
			for(int i = 0; i < Item_Num && item_name != NULL; i++){
				if(strcmp(item_name, ITEM_NAMES[i]) == 0){
					printf("%s %f\n", ITEM_NAMES[i], item.chance);
					item.type = (Item_Type)i;
					da_append(&g.item, item);
					break;
				}
			}
		}
	}
		g.state.territoryRadius = 100;
		printf("\n");	
		da_append(ent, g);
	}
	//exit(-1);
	cJSON_Delete(json);	
	//exit(-1);
}


// Initialize ECS world
void init_world(World* world) {
	world->nMonster = 0;
	memset(world->isExpMap, false, sizeof(int) * MAP_HEIGHT*MAP_WIDTH);
	for (int i = 0; i < MAX_ENTITIES; i++) {
		world->masks[i] = 0;
		world->inventory[i] = (Item_DA){0};
		world->free_list[i] = MAX_ENTITIES - 1 - i;
		}
	for(Scroll_Type i = 0; i < Scroll_Num; i++){
		//Tbd ident if(i == )
		world->identScrools[i] = false;
	}	
	for(Potion_Type i = 0; i < Potion_Num; i++){
		world->identPotions[i] = false;
	}	
	world->identScrools[Scroll_Identif] = true;
	world->tempStatsPlayer = (TempStats_DA){0};
	world->num_free = MAX_ENTITIES;
	world->tempGen = NULL;
	world->expPlayer = 0;
	world->nutrition = 10000;
	//world->expPlayer = 10060;

	}

// Create new entity
int create_entity(World* world) {
	if (world->num_free == 0) return -1;  // No space

	int id = world->free_list[--world->num_free];
	world->masks[id] = 0;  // Reset component mask
	return id;
	}

// Destroy entity
void destroy_entity(World* world, int entity) {
	if((world->masks[entity] & COMP_MONSTER) == COMP_MONSTER){
		world->nMonster--;
	}
	world->masks[entity] = 0;  // Mark as inactive
	world->position[entity] = (Vector2){0, 0}; //Cuzz COMP_POSITION is 0 bit
	world->input[entity].isMoving = NOT;
	world->input[entity].isFinishedAttack = true;
	world->input[entity].moveLerpAlpha = 0.0;
	world->free_list[world->num_free++] = entity;  // Add to free list
	//world->inventory[entity].count = 0;

	}

// Add component to entity
void add_component(World* world, int entity, CompType type, void* data) {
	world->masks[entity] |= type;

	switch (type) {
		case COMP_POSITION:
			world->position[entity] = *(Position*)data;
			break;
		case COMP_RENDER:
			world->renderable[entity] = *(Renderable*)data;
			break;
		case COMP_HEALTH:
			world->health[entity] = *(Health*)data;
			break;
		case COMP_INPUT: {
				if(!(world->masks[entity] & COMP_POSITION)) {
					ASSERT("Need to have position to be able have a input component");
					}
				//world->input[entity] = *(Input*)data;
				break;
				}
		case COMP_STATS:
			world->stats[entity] = *(Stats*)data;
			break;
		case COMP_STATE:
			world->state[entity] = *(State*)data;
			break;
		case COMP_GAS:
			world->gas[entity] = *(Gas*)data;
			break;
		case COMP_SPELL:
			world->spell[entity] = *(Spell*)data;
			break;
		case COMP_FIRE:
			world->fire[entity] = *(Fire*)data;
			break;
		case COMP_STATUS:
			world->status[entity] = *(StatusEffects*)data;
			break;
		case COMP_PROJEC:
			world->projectile[entity] = *(Projectile*)data;
			break;
		case COMP_OPEN:
			ASSERT("Not implemneted OPEN");
			break;
		;					
		// Handle other components
		default:
			ASSERT("Unrechable Component");
			break;
		}
	}

// Tag component (no data)
void add_tag(World* world, int entity, CompType tag) {
	world->masks[entity] |= tag;
	if(tag == COMP_MONSTER)
		world->nMonster++;
	}

// Remove component/tag
void remove_component(World* world, int entity, CompType type) {
	world->masks[entity] &= ~type;
	}



void add_spell_depending_on_T(World world,  int monster){
	switch (monster){
	case Abomination:
		
		break;
	
	default:
		//No spell
		break;
	}
	DROP(world);
}	


void add_components_to_ent_depending_on_T(World* world, Global_Ent_DA* ent, int monster, int type, Vector2 p){
	Global_Ent e = ent->items[type];
	
	//add_trap(world, TRAP_BEAR, (int)p.x, (int)p.y);
	world->name[monster] = e.name;
	//DO not change order
	if(e.masks & COMP_POSITION){
		add_component(world, monster, COMP_POSITION, &(Position) {
			p.x, p.y 
			});
	}
	if(e.masks & COMP_RENDER){
		add_component(world, monster, COMP_RENDER, &(Renderable) {
			(Sprite_Type)(e.renderable.type),
			});

	}
	if(e.masks & COMP_HEALTH){
		add_component(world, monster, COMP_HEALTH, &(Health) {
			e.health.current, e.health.max
		});
	}
	if(e.masks & COMP_STATS){
	add_component(world, monster, COMP_STATS,  &(Stats) {
		e.stats.str, e.stats.dex, e.stats.inte, e.stats.cons, e.stats.morale, e.stats.perception, e.stats.perception, e.stats.dmgMax, e.stats.dmgMin
		,e.stats.defence	
	});
	}

	add_component(world, monster, COMP_INPUT, &(Input){
		(Position){p.x, p.y}, 0.0f, 0.0f, 0.0f, true, true, 0, 0  
	} );

	//Bar gas
	if(type == Abomination || type == Zombie){
		add_component(world, monster, COMP_GAS, &(Gas){gasSwamp, 1, 1, RED});
	}


	if(e.masks & COMP_STATE){
		add_component(world, monster, COMP_STATE,  &(State) {
			e.state.current, e.state.chancesR, e.state.chancesH, e.state.chancesW, e.state.chancesRe, e.state.chancesB, 
			e.state.chanceRange, 0, 1, 1, 0, (10 + rand()%50), (Position)world->position[monster], 0
		});
	}
	if (e.masks & COMP_MONSTER){
		add_tag(world, monster, COMP_MONSTER);	
	}
	//Tbd in json all this stuffs
	if(type == Imp || type == FireDemon){
		add_component(world, monster, COMP_FIRE, &(Fire){1, 0});
	}
	else{
		add_component(world, monster, COMP_FIRE, &(Fire){0, 0});
	}
	
	add_component(world, monster, COMP_STATUS, &(StatusEffects){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	//world->status[monster].confusionTurn = 1000;

	//Spell system added
	//Remove after testing
	if(0){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Hook, 0, 20, 20});
	}
	else if(type == Necromancer){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Ghoul, 20, 20});
	}
	else if(type == Wagon){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Zombie, 20, 20});
	}
	else if(type == Acolyte || type == AcolyteD){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Shout, 0, 20, 20});
		
	}
	else if(type == Banshee){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Dmg, 15, 4, 4});
	}
	else if(type == Abomination){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Hook, 0, 20, 20});
	}
	else if(type == Spider){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Web, 3, 20, 20});
	}
	else if(type == SpiderMage){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Spider, 20, 20});
	}
	else if(type == Vampire){	
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Bat, 10, 10});
	}
	else if(type == ObsidanStatue){	
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Obsidian, DMG, 10, 10});
	}
	else if(type == Anubis){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Anubis, 0, 30, 30});
	}
	else if(type == OrcRaider){
		if(rand_f32() < 0.5f)
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Blink, 0, 30, 30});
	}
	else if(type == OrcShaman){
		if(rand_f32() < 0.5f)
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Wolf, 10, 10});
		else 
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Obsidian, HEAL, 10, 10});

	}
	else if(type == OrcWarloc){
		if(rand_f32() < 0.7f)
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Obsidian, DMG, 10, 10});
		else 
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Sacrifice, RedOrc, 10, 10});
	}
	else if(type == OrcSamurai){
		if(rand_f32() < 0.9f)
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Mirror, OrcSamurai, 30, 30});
		else 
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Blink, 0, 10, 10});
	}
	else if(type == OrcWarchief){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_WarCray, 1, 30, 30});
	}
	else if(type == OrcScout){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_OrcScout, 1, 10, 10});
	}
	else if(type == GoblinWarlord){
		//Goblins
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_WarCray, 2, 30, 30});
	}
	else if(type == GoblinBarrack){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_GoblinBarrack, 0, 100, 100});
	}
	else if(type == MindFlayer){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Confusion, 0, 20, 20});
	}
	else if(type == Lich){
		if(rand_f32() < 0.6f)
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Phantom, 10, 10});
		else 
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, SoulReaper, 10, 10});
	}
	else if(type == BeholderKin){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_ReduceStr, 0, 10, 10});
	}
	else if(type == Manes){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Blink, 0, 10, 10});
	}
	else if(type == FlashDemon){
		if(rand_f32() < 0.9)
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Dmg, 10, 20, 20});
		else 
			add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Abomination, 20, 20});
	}
	else if(type == FireDemon){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Imp, 10, 10});
	}
	else if(type == Kraken){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Hook, 0, 10, 10});
	}	
	else if(type == WaterDemon){
		add_component(world, monster, COMP_SPELL, &(Spell){Spell_Summon, Kraken, 10, 10});
	}
	else{
		//add_component(world, monster, COMP_SPELL, &(Spell){Spell_Shout, 0, 20, 20});
	}
	
	if (e.item.count > 0) {
		//exit(-1);
	   //world->inventory[monster] = (Item_DA){0};
 	   add_items_from_list(&e.item, &world->inventory[monster]);
	}
	//inventory_to_map(world, monster);
	
	//add_item_to_inventory(Sword, &world->inventory[monster], true);	
    //add_item_to_inventory(Sword, &world->inventory[monster],false);
	//add_item_to_inventory(LetherGloves, &world->inventory[monster], true);
	//add_item_to_inventory(Bow, &world->inventory[monster], true);
	//add_item_to_inventory(Arrows, &world->inventory[monster], true);
	//add_item_to_inventory(Tourch, &world->inventory[monster], false);
	//add_item_to_inventory(LeatherArmor, &world->inventory[monster], true);
	//add_item_to_inventory(LeatherArmor, &world->inventory[monster], false);
	//add_item_to_inventory(LeatherArmor, &world->inventory[monster], false);
	//add_item_to_inventory(LeatherArmor, &world->inventory[monster], false);

}	



//MAP STUFF
#include "raymath.h"
#define MIN_DOOR_SPAWN_DISTANCE 10.0f
static int check_tiles_around(int tx, int ty, World* world){
	int count = 0;
	for(int y = ty - 1; y <= ty + 1; y++){
		for(int x = tx - 1; x <= tx + 1; x++){
		//printf("%c", world->map.walling[y][x]);
		if(world->map.walling[y][x] == '#'){
				count++;
				//exit(-1);
			}
		else if(world->map.walling[y][x] == '*'){
			count = 0;
			break;
		}	
		}
	}
	//if(count > 0)
	//printf("\nCount %d\n", count);
	if(count == 8) return -1;
	return (count>=6) ? 1 : 0;
}
static int check_distances(int x, int y, Position_DA *p, World* world){
	const int tiles = check_tiles_around(x, y, world);
	if(tiles == 0)
		return 0;
	else if(tiles == -1){
		return -1;
	}	
	float min = 100;
	Position current = {(float)x, (float)y};
	for(int i = 0; i < p->count; i++){
		float dist = Vector2Distance((Vector2)current, (Vector2)p->items[i]);
		if(dist < min){
			min = dist;
		}
	}
	 return (min>=MIN_DOOR_SPAWN_DISTANCE) ? 1 : 0;
}


static void generate_doors(World* world, Global_Ent_DA *ent){
	Position_DA p = {0};
	for(int y = 2; y < world->map.h - 2; y++){
		for(int x = 2; x < world->map.w - 2; x++){
		if(world->map.walling[y][x] == '+'){
				
			int distance = check_distances(x, y, &p, world);
				if(distance == 1){
					//exit(-1);
					int door = create_entity(world);
					add_component(world, door, COMP_POSITION, &(Position) {
						(float)x, (float)y
						});
					add_component(world, door, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(ClosedDoor),
						});
					Position pp = (Position){(float)x, (float)y}; 
					//world->map.walling[y][x] = ' ';	
					da_append(&p, pp);
				}
				else if(distance == -1){
					world->map.walling[y][x] = '#';
				}
				else{
					world->map.walling[y][x] = ' ';
				}

			}

		}
		
	}
	DROP(ent);
	//free(p.items);

}

static void remove_non_posible_elements(World* world){
	//Put end
	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			if(x == 0){
				world->map.walling[y][x] = '#';
			}
			else if(y == 0){
				world->map.walling[y][x] = '#';
			}
			else if(x == world->map.w - 1){
				world->map.walling[y][x] = '#';
			}
			else if(y == world->map.h - 1){
				world->map.walling[y][x] = '#';
			}

		}
	}

}

//Let for now have somthig like 20 squares range
void generate_enviroment_depending_on_type(World* world, int x, int y){
	const int width  = 20;
	const int height = 20; 
	if(x <= width){
		x = width + 1;
	}
	if(x >= world->map.w - width){
		x = world->map.w - width - 1;
	}
	if(y <= height){
		y = height + 1;
	}
	if(y >= world->map.h - height){
		y = world->map.h - height - 1;
	}
	for(int  yy = y; yy < y + height; yy++){
		for(int  xx = x - width; xx < x + width; xx++){
			
			if(world->map.walling[yy][xx] == ' ' && (rand_f32() < (1.0f / (Vector2Distance((Vector2){x, y}, (Vector2){xx, yy}) + 1.0f)))){
			printf("x , y = %d %d\n", yy, xx);	
			int plantID = create_entity(world);
			
			add_component(world, plantID, COMP_POSITION, &(Position){(float)xx, (float)yy});
			add_component(world, plantID, COMP_RENDER, &(Renderable) {
			(Sprite_Type)(S_Plant)});
			world->map.walling[yy][xx] = '"'; //For now it will have some
		}
		

	}
	}	
	
}

static void add_enviroment(World* world){
	const int dirs[8][2] = {
        { 0, -1}, // Up
        { 0,  1}, // Down
        {-1,  0}, // Left
        { 1,  0}, // Right
        {-1, -1}, // Up-left
        {-1,  1}, // Down-left
        { 1, -1}, // Up-right
        { 1,  1}  // Down-right
    };

	for (int y = 1; y < world->map.h - 1; y++){
		for (int x = 1; x < world->map.w - 1; x++){
			if(world->map.walling[y][x] ==  '\"'){
				int plantID = create_entity(world);
				add_component(world, plantID, COMP_POSITION, &(Position){(float)x, (float)y});
				//add_component(world, plantID, COMP_HEALTH, &(Health) {
				//	20, 20
				//});
				if(rand_f32() < CHANCE_BIGPLANT){
					add_component(world, plantID, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_PlantBig)});
						world->map.walling[y][x] = '\'';
				}
				else
					add_component(world, plantID, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_Plant)});
			}
		//	else if(world->map.walling[y][x] ==  '\''){
		//		int plantID = create_entity(world);
		//		add_component(world, plantID, COMP_POSITION, &(Position){(float)x, (float)y});
		//		add_component(world, plantID, COMP_RENDER, &(Renderable) {
		//		(Sprite_Type)(S_PlantBig)});
		//	}
			else if(world->map.walling[y][x] == Tile_UpS){
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				//add_component(world, plantID, COMP_HEALTH, &(Health) {
				//	20, 20
				//});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_UpS)});
						
			}
			else if(world->map.walling[y][x] == Tile_DownS){
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				//add_component(world, plantID, COMP_HEALTH, &(Health) {
				//	20, 20
				//});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_DownS)});
				
						
			}
			else if(world->map.walling[y][x] == Tile_Armory){
				//exit(-1);
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_Armory)});
				add_tag(world, sEnt, COMP_SHOP);
				const int numItem = 5 + rand()%5; //All are same percent
				for(int i = 0; i < numItem; i++){
					const int whatItem = LeatherArmor + rand()%(MetalGloves - LeatherArmor);
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], Scroll_No, Potion_No, false, false);		
				}
				
			}
			else if(world->map.walling[y][x] == Tile_Wepon){
				//exit(-1);
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_WeponS)});
				add_tag(world, sEnt, COMP_SHOP);
				//const int numItem = 5 + rand()%5; //All are same percent
				const int numItem = 5 + rand()%5; //All are same percent
				for(int i = 0; i < numItem; i++){
					const int whatItem = rand()%DMace;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], Scroll_No, Potion_No, false, false);		
				}
				
				
			}
			else if(world->map.walling[y][x] == Tile_Genera){
				//exit(-1);
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_GeneralS)});
				add_tag(world, sEnt, COMP_SHOP);
			
				for(int i = 0; i < 2 + rand()%3; i++){
					const int whatItem = Food;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], Scroll_No, Potion_No, false, false);		
				}
				for(int i = 0; i < rand()%3; i++){
					const int whatItem = Tourch;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], Scroll_No, Potion_No, false, false);		
				}
				for(int i = 0; i < rand()%2; i++){
					const int whatItem = Potion;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], Scroll_No, (rand()%(Potion_Num - 1) + 1), false, false);		
				}
				for(int i = 0; i < rand()%2; i++){
					const int whatItem = Scroll;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], (rand()%(Scroll_Num - 1) + 1), Potion_No, false, false);		
				}

			}
			else if(world->map.walling[y][x] == Tile_Pot){
				//exit(-1);
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_PotionS)});
				add_tag(world, sEnt, COMP_SHOP);
				//const int numItem = 5 + rand()%5; //All are same percent
				const int numItem = 5 + rand()%5; //All are same percent
				for(int i = 0; i < numItem; i++){
					const int whatItem = Potion;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], Scroll_No, (rand()%(Potion_Num - 1) + 1), false, false);		
				}
			}
			
			else if(world->map.walling[y][x] == Tile_Scro){
				//exit(-1);
				int sEnt = create_entity(world);
				add_component(world, sEnt, COMP_POSITION, &(Position){(float)x, (float)y});
				add_component(world, sEnt, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_ScrollS)});
				add_tag(world, sEnt, COMP_SHOP);
				//const int numItem = 5 + rand()%5; //All are same percent
				const int numItem = 5 + rand()%5; //All are same percent
				for(int i = 0; i < numItem; i++){
					const int whatItem = Scroll;
					add_item_to_inventory((Item_Type)whatItem, &world->inventory[sEnt], (rand()%(Scroll_Num - 1) + 1), Potion_No, false, false);		
				}
			}

			else if(world->map.walling[y][x] == Tile_Water || world->map.walling[y][x] == Tile_Dwater){
				int count = 0;
				for(int i = 0; i < 8; i++){
					if(world->map.walling[y + dirs[i][0]][x + dirs[i][1]] == Tile_Water 
					|| world->map.walling[y  + dirs[i][0]][x  + dirs[i][1]] == Tile_Dwater){
						count++;
					}
					if(count >= 7){
						world->map.walling[y][x] = Tile_Dwater;
					}
				}
			} 
		}	
	}
	
	xmprint(world->map);
	//exit(-1);
}


void generate_map(World* world, Global_Ent_DA *ent) {
	//3 change for shape
	int nRoom  = rand()%60 + 20;
	world->nMonster = 0;
	//nRoom = 20;

	int what =  rand()%10;
	int whatS = rand()%4;

	switch (what)
	{
		case 7:
			world->map = xmgen(MAP_WIDTH, MAP_HEIGHT, 1, 100);
			xmgen_add_enviroment(&world->map, '\"', 0, 0, MAP_WIDTH, MAP_HEIGHT, 0.7);
			break;
		case 0:
			world->map = xmgen(MAP_WIDTH, MAP_HEIGHT, 1, nRoom);
			xmgen_add_enviroment(&world->map, '\"', 0, 0, MAP_WIDTH, MAP_HEIGHT, 0.7);
		break;
		case 6:
		case 1:
			world->map = xmgen_graph(MAP_WIDTH, MAP_HEIGHT, nRoom, 8, 10, 2);
			xmgen_add_enviroment(&world->map, '\"', 0, 0, MAP_WIDTH, MAP_HEIGHT, 0.7f);
		break;
		case 2:
		case 3:
			world->map = xmgen_brogue(MAP_WIDTH, MAP_HEIGHT, nRoom, 8, 20);
		break;
		case 8: 
		case 9:
			world->map = xmgen_brogue(MAP_WIDTH, MAP_HEIGHT, nRoom, 5, 10);
		break;
		case 4:
			world->map = xmgen_maze(MAP_WIDTH, MAP_HEIGHT, 30, 30);
		break;
		case 5:
			world->map = xmgen_room_maze(MAP_WIDTH, MAP_HEIGHT, 30, 30, 4, 5, 5);		
		break;
	
		default:
			break;
	}
		if(whatS == 0){
		//xmgen_add_enviroment(&world->map, '"', 0, 0, MAP_WIDTH, MAP_HEIGHT, rand_f32() / 10.0f);	
		world->ambientStrenght = 0.00f;
	}
		
	else if(whatS == 2){
		world->ambientStrenght = 1.0f;
		//exit(-1);
	}		
	else{
		//xmgen_add_enviroment(&world->map, '~', 0, 0, MAP_WIDTH, MAP_HEIGHT, 0.55);
		world->ambientStrenght = rand_f32() / 2.0f;    // 0.0 - 0.1 PROB LIGHTING POWER
	}
	
	
	xmgen_add_enviroment(&world->map, Tile_Water, 0, 0, MAP_WIDTH, MAP_HEIGHT, 0.55);
	//world->ambientStrenght = 0.0f;
	//world->ambientStrenght = 1.0f;
	//Save ambient strenght
	world->saveAmbientStrenght = world->ambientStrenght;
	
	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			world->gasMap[y][x].type = gasNo;
		}	
	}

	xmprint(world->map);
	generate_doors(world, ent);
	remove_non_posible_elements(world);

	xmprint(world->map);
	
	
	add_enviroment(world);
	//exit(-1);
	while(1) {
		int x = rand()%world->map.w, y = rand()%world->map.h;
		
		if(world->map.walling[y][x] != '#' && world->map.walling[y][x] != '+') {
			world->position[0] = (Position) {
				x, y
				};
			break;
			}
		}

	//GeneerateEnttyis
	for(int i = 0; i < 20; i++) {
		Position p = {0, 0};
		while(1) {

			int x = rand()%world->map.w, y = rand()%world->map.h;
			calculate_diakstra_map(world, world->position[0].x, world->position[0].y, 1);
			if(world->map.walling[y][x] != '#' && world->map.walling[y][x] != '+' ) {
				//world->position[0] = (Position){x, y};
				p.x = x;
				p.y = y;
				break;
				}

			}
		int monster = create_entity(world);
		add_component(world, monster, COMP_POSITION, &(Position) {
			p.x, p.y
			});
		//add_component(world, monster, COMP_GAS, &(Gas){gasStun, true, 10, RED});	
		int type =  rand()%Monster_Num;
		//int type = GiantRat;

		//int type = SPit;
		//int type;
		//int what = rand()%4;
		//if(what == 3)
	//		type = Zombie;
	//	else 
	//		type = Acolyte + what;
//
		if(type == 0){
			type = Spider;
		}
		printf("Type %d\n\n", type); 
		add_components_to_ent_depending_on_T(world, ent, monster, type, p);
		if(type == Succubus){
			world->renderable[monster].type = S_Abomination +  rand()%(S_Lich - S_Abomination - 1);
		}
		//Jus gas
		if(rand_f32() <= 0.05f){
			int gas = create_entity(world);
			//rand()%2+2
			add_component(world, gas, COMP_GAS, &(Gas){gasSwamp, 1, 20, RED});
			add_component(world, gas, COMP_POSITION, &(Position) {
			p.x, p.y
			});
		}

		}
		for(int i  = 0; i < 50; i++){
		int x = rand()%world->map.w;
			int y = rand()%world->map.h;
			generate_enviroment_depending_on_type(world, x, y);

		}
		}

	//exit(-1);
	/*
		Image temp;
		temp.width  = mapM.w;
		temp.height = mapM.h;
		temp.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
		uint8_t *data = malloc(temp.width*temp.height);
		for(int y = 0; y < mapM.h; y++ ) {
			for(int x = 0; x < mapM.h; x++ ) {
				if(mapM.walling[y][x] == '#') {
					data[y*mapM.w+x] = 255;
					}
				else {
					data[y*mapM.w+x] = 0;
					}
				}
			}
		temp.data = data;
		ExportImage(temp, "temp.png");
	//*/

	//}

/*
void calculate_diakstra_map(World *world, int goalX, int goalY, uint8_t isEnt) {
    // Initialize all tiles to a high value (255)
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            world->dikstra[y][x] = 255.0f;
        }
    }

    world->dikstra[goalY][goalX] = 0.0f; // Goal has a distance of 0
    
    // Setup queue for the Breadth-First Search
    Vector2* queue = calloc(world->map.h * world->map.w, sizeof(Vector2));
    int front = 0, back = 0;

    queue[back++] = (Vector2){ (float)goalX, (float)goalY };

    // --- MODIFICATION START ---
    // Changed from 8 directions to 4 directions: N, E, S, W
    const int dx[4] = {  0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1,  0 };
    // --- MODIFICATION END ---

    while (front < back) {
        Vector2 p = queue[front++];
        const int x = (int)p.x;
        const int y = (int)p.y;
        float current_dist = world->dikstra[y][x];
        
        // --- MODIFICATION START ---
        // Loop now iterates 4 times instead of 8
        for (int dir = 0; dir < 4; dir++) {
        // --- MODIFICATION END ---
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // Boundary and wall checks
            if (nx < 0 || ny < 0 || nx >= MAP_WIDTH || ny >= MAP_HEIGHT) continue;
            if (world->map.walling[ny][nx] == '#') continue;

            // If we found a shorter path, update it and add to the queue
            if (world->dikstra[ny][nx] > current_dist + 1.0f) {
                world->dikstra[ny][nx] = current_dist + 1.0f;
                queue[back++] = (Vector2){ (float)nx, (float)ny };
            }
        }
    }
    free(queue);

    // Post-processing: Ensure walls are impassable
  

    // Post-processing: Make entity locations temporarily impassable for other entities
    if(isEnt ) {
        for(int i = 0; i < MAX_ENTITIES; i++){
            CompMask mask = COMP_MONSTER | COMP_POSITION;
            if((mask & world->masks[i]) == mask){
                world->dikstra[(int)world->position[i].y][(int)world->position[i].x] = 255.0f;
                world->dikstra[(int)world->input[i].nextPosition.y][(int)world->input[i].nextPosition.x] = 255.0f;
            }
        }
        // Make player location impassable
        world->dikstra[(int)world->position[0].y][(int)world->position[0].x] = 255.0f;
    }
}	
//*/

	
///*
void calculate_diakstra_map(World *world, int goalX, int goalY, uint8_t isEnt) {
    	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			world->dikstra[y][x] = (float)255.0f;
			}

		world->dikstra[goalY][goalX] = 0.0f;
		Vector2* queue = calloc(world->map.h * world->map.w, sizeof(Vector2));
		int front = 0, back = 0;

		queue[back++] = (Vector2) {
			goalX, goalY
			};

		// 8 directions: N, NE, E, SE, S, SW, W, NW
		const int dx[8] = {  0,  1, 1,  1,  0, -1, -1, -1 };
		const int dy[8] = { -1, -1, 0,  1,  1,  1,  0, -1 };

		while (front < back) {
			Vector2 p = queue[front++];
			const int x =  (int)roundf(p.x);
			const int y = (int)roundf(p.y);
			float current_dist = world->dikstra[y][x];

			for (int dir = 0; dir < 8; dir++) {
				int nx = p.x + dx[dir];
				int ny = p.y + dy[dir];

				if (nx < 0 || ny < 0 || nx >= MAP_WIDTH || ny >= MAP_HEIGHT) continue;
				if (world->map.walling[ny][nx] == '#' ) continue;   //NOT 255

				if (world->dikstra[ny][nx] > current_dist + 1.0f) {
					world->dikstra[ny][nx] = current_dist + 1.0f;
					queue[back++] = (Vector2) {
						nx, ny
						};
					}
				}
			}
		free(queue);
		}
	//world->dikstra[(int)world->position[0].y][(int)world->position[0].x] = INF;
    // Post-processing: Set goal to INF and walls to 255
   // world->dikstra[goalY][goalX] = INF;
   ///*
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (world->map.walling[y][x] == Tile_Wall) {
                world->dikstra[y][x] = 255.0f;
            }
			else if(world->map.walling[y][x] == Tile_Fire || world->map.walling[y][x] == Tile_Lava || world->map.walling[y][x] == Tile_Fire){
				if(world->dikstra[y][x] != 255.0f){
					world->dikstra[y][x] = 200;
				}
			}
        }
    }

		if(isEnt)
		for(int i = 0; i < MAX_ENTITIES; i++){
    	CompMask mask = COMP_MONSTER | COMP_POSITION;
    	if((mask & world->masks[i]) == mask){
    		world->dikstra[(int)world->position[i].y][(int)world->position[i].x] = 255;
			world->dikstra[(int)world->input[i].nextPosition.y][(int)world->input[i].nextPosition.x] = 255;
			//Around ent if monster add a +1 to tile value to disipate arround	
			///*
		
		}
		}

		//pLAYER
		world->dikstra[(int)world->position[0].y][(int)world->position[0].x] = 255; 
		
}
//*/


int is_monster_in_next_postition(World* world, float x, float y){
	CompMask mask = COMP_MONSTER;
	const Vector2 pos = {x, y};
	for(int i = 1; i < MAX_ENTITIES; i++){
		
		const float dis = Vector2Distance(world->position[i], pos);
		if((mask & world->masks[i]) == mask){
			if((dis < 1.0f)){
				//exit(-1);
				//printf("Monster %d", i);
				return i;
			}
			
		}
	}
	//printf("Monster %d", 0);
	return 0;
}

//Checks for player
int is_monster_on_position(World* world, float x, float y){
	CompMask mask = COMP_MONSTER;
	const Vector2 pos = {x, y};
	const float dis = Vector2Distance(world->position[0], pos);
	if(dis < 0.5){
		///exit(-1);
		return 0; //Player
	}
	for(int i = 1; i < MAX_ENTITIES; i++){
		
		const float dis = Vector2Distance(world->position[i], pos);
		//&& (world->position[i].x == x && world->position[i].y == y)
		if((mask & world->masks[i]) == mask && dis < 0.5f){
				return i;	
		}
	}
	//printf("Monster %d", 0);
	return -1;

}

int is_position_on_position(World* world, float x, float y){
	CompMask mask = COMP_POSITION;
	const Vector2 pos = {x, y};
	if(world->position[0].x == x && world->position[0].y == y){
		///exit(-1);
		return 0; //Player
	}
	for(int i = 1; i < MAX_ENTITIES; i++){
		
		const float dis = Vector2Distance(world->position[i], pos);
		//&& (world->position[i].x == x && world->position[i].y == y)
		if((mask & world->masks[i]) == mask && dis < 0.5f){
				return i;	
		}
	}
	//printf("Monster %d", 0);
	return -1;

}



//DEXTERTY is basicly a doge chance
//If get a higher then dex dogfe
//else -- dmg clamp to a max strenght  

#define D1_20 (rand()%20 + 1)
#define D1(x) (rand()%(x) + 1)

static int  Dn_X(int n, int x){
int max = 0, changeMax = 0; 
for(int i = 0; i < n; i++){
	if(x > 0)
	changeMax = rand()%x + 1; 
	//if(changeMax > max) 
	max += changeMax;}

	return max;	
}



int attack_dmg_callculations(World* world, int attacker, int defender, int isRange){

	//CALCULATION FOR ENGEGING IN COMBAT
	//IT WILL ROLLL A DICESS FOR const of bests
	//if > that creature will get + 1 turn of stunn
	const int aCons = rand()%world->stats[attacker].cons;
	const int dCons = rand()%world->stats[defender].cons;
	if(rand_f32() < 1.0f){
		if(aCons > dCons){
			
			world->state[defender].current = STATE_STUN;
			world->state[defender].stunTurn+=2;
			//world->state[attacker].stunTurn-=1;
			//CLAMP(world->state[attacker].stunTurn, 0, 100);
		}
		else{
			world->state[attacker].current = STATE_STUN;
			world->state[attacker].stunTurn+=2;
			//world->state[defender].stunTurn-=1;
			//CLAMP(world->state[defender].stunTurn, 0, 100);
		}
	}
	
	int dmgATTACK = D1(world->stats[attacker].str);
	int dmgValue   = world->stats[attacker].dmgMin + rand()%(world->stats[attacker].dmgMax - world->stats[attacker].dmgMin);
	int armorValue = world->stats[defender].defence;
	int dogeDEFFENCE =0;
	if(world->stats[defender].dex != 0)
		dogeDEFFENCE = D1(world->stats[defender].dex);
	//Attacker add to stats
	for(int i = 0; i < world->inventory[attacker].count; i++){
		const Item item = world->inventory[attacker].items[i];
		if(item.isEqu == true){
			//Tbd store
			if(item.to == EQUIPTED_WEPON && !isRange){
				//MESSAGE_F("Used %s", item.name);
				//exit(-1);
				const int v = Dn_X(item.nDice, item.value);
				if(attacker == 0){
					if(item.strReq > world->stats[0].str){
						const float chanceToNoUse = 0.20 + 0.1*(item.strReq - world->stats[0].str);
						if(rand_f32() < chanceToNoUse){
							printf("No use attt");
							dmgValue-= v + 1;
						}
					}
				} 
				
				dmgValue+=v;
			}
			else if(item.to == EQUIPTED_RANGE && isRange){
				const int v = Dn_X(item.nDice, item.value);
				if(attacker == 0){
					if(item.strReq > world->stats[0].str){
						const float chanceToNoUse = 0.20 + 0.1*(item.strReq - world->stats[0].str);
						if(rand_f32() < chanceToNoUse){
							printf("No use attt");
							dmgValue-= v + 1;
						}
					}
				} 
				
				dmgValue+=v;		
			}
			dmgATTACK+=item.stats.str;
		}		
	}
	

	for(int i = 0; i < world->inventory[defender].count; i++){
		const Item item = world->inventory[defender].items[i];
		if(item.isEqu == true){
			//Tbd store
			if(item.to == EQUIPTED_SHIELD || item.to == EQUIPTED_ARMOR 
			|| item.to == EQUIPTED_HEAD  || item.to == EQUIPTED_LEGS
			|| item.to == EQUIPTED_HAND ){
				const int v = Dn_X(item.nDice, item.value);
				if(defender == 0){
					if(item.strReq > world->stats[0].str){
						const float chanceToNoUse = 0.20 + 0.1*(item.strReq - world->stats[0].str);
						if(rand_f32() < chanceToNoUse){
							printf("No use def");
							armorValue-= v + 1;
						}
					}
				} 
				armorValue+=v;
				//exit(-1)
			}
			dogeDEFFENCE +=item.stats.dex;
		}		
	}
	int AC = armorValue; //4 types equipted for armor
	//For testing
	if(defender == 0)
	LOG("AC %d\n", AC);
	//lIKE A CRIT
	//if(dmgATTACK == world->stats[attacker].str){
	//	dmgValue += 2;
		//return 10;
	//}

	if(dmgATTACK == 0){
		return 0;
	}
	else if(dogeDEFFENCE > dmgATTACK) {
		return 0;
	}
	else{

		int d = dmgValue - AC;
		if(d < 0){
			d = 0;
		}
		return d;
	}
}


#define CHANCE_TO_DROP 0.99f
void inventory_to_map(World* world, int entity){
	Item_DA *inventory = &world->inventory[entity];
	const float x = world->position[entity].x;
	const float y = world->position[entity].y;

	for(int j = 0; j < inventory->count; j++) {
		float chance = rand_f32();
		if(CHANCE_TO_DROP >= chance) {
			Item item = inventory->items[j];
			item.pos.x = (int)x;
			item.pos.y = (int)y;
			item.isEqu = false;
			da_append(&world->items, item);
			
			int it = create_entity(world);
			uint8_t whatI = item.type + S_Sword;
			add_component(world, it, COMP_RENDER, &(Renderable){whatI});
			add_component(world, it, COMP_POSITION, &(Position){x, y});
		}
	}
	world->inventory[entity].count = 0;

}


void add_trap(World* world, Trap_Types type, int x, int y){
	world->trapMap[y][x].trap = type;
	world->trapMap[y][x].value = 0;
	switch (type){
	case TRAP_POISON:
		world->trapMap[y][x].value = 1000;
		break; 
	case TRAP_ACID:
		world->trapMap[y][x].value = 1000;
		break; 
	case TRAP_FIRE:
	
		break;
	case TRAP_STUN:
		world->trapMap[y][x].value = rand()%10;
		break;
	case TRAP_TELEPORT:
		break;
	case TRAP_BEAR:
		world->trapMap[y][x].value = rand()%5;
		break;
	case TRAP_SUMMON:
		break;
		/* code */
		break;
	
	default:
		break;
	}
}




//Lets assume that tiles from start are 10 10
static void generate_monster_of_type(World *world, Global_Ent_DA *ent, Position p, Monster_Type type){
	//Get type 
	
		int monster = create_entity(world);
		add_component(world, monster, COMP_POSITION, &(Position) {
			p.x, p.y
			});

 
		add_components_to_ent_depending_on_T(world, ent, monster, type, p);
		if(type == Succubus){
			world->renderable[monster].type = S_Abomination +  rand()%(S_Lich - S_Abomination - 1);
		}
}


void generate_monster_generator(World* world, Generator* gen, Position pos, Global_Ent_DA *ent){
		Position monsterPos = pos;
		int minX = pos.x - 10;
		CLAMP(minX, 0, MAP_WIDTH);
		int minY = pos.y - 10;
		CLAMP(minY, 0, MAP_HEIGHT);
		int counter = 0;
		for(int i = 0; i < gen->nMonsters; i++)
		while(1){
			if((counter++) > 100) break;
			//calculate_diakstra_map(world, world->position[i].x, world->position[i].y, 1);
			int x = (rand()%10 + minX);
			int y = (rand()%10 + minY);
			
			CLAMP(x, 0, MAP_WIDTH);
			CLAMP(y, 0, MAP_HEIGHT);
			//printf("%d %d\n", x, y);
			if(world->map.walling[y][x] == Tile_Dirt || world->map.walling[y][x] == TIle_Grass || world->map.walling[y][x] == Tile_BGrass){
				//if(world->dikstra[y][x] != 255)
				{
					//Type of monster
					Monster_Type type = Zombie;
					while(1){
						int k = rand()%gen->monsters.count;
						if(rand_f32() < gen->monsters.items[k].chance){
							type = gen->monsters.items[k].type;
							break;
						}
					}

					generate_monster_of_type(world, ent, (Position){x, y}, type);
					printf("%s %d %d\n", Monster_Names[type], x, y);
					//exit(-1);
					break;
				}
			}
		}
		


}

#define CHANCE_SHOP 0.5f
void generate_level(World* world, int level, Generator_DA *generators, Global_Ent_DA *ent){
	//40% B, 30% N, 25% G, 5% RM
	if(world->tempGen != NULL){
		free(world->tempGen->items);
		//exit(-1);
		 //world->tempGen = NULL;
	}
		

	float whatLevel = rand_f32();
	int maxRooms = rand()%10 + 15;
	//int maxRooms = ;
	if(whatLevel <= 0.4){
		
		world->map = xmgen_brogue(MAP_WIDTH, MAP_HEIGHT, maxRooms, 8, 9 + rand()%12);
		xmgen_add_enviroment(&world->map, TIle_Grass, 0, 0, MAP_WIDTH, MAP_HEIGHT, (0.45 + rand_f32() / 10.0f));
		xmgen_add_enviroment(&world->map, Tile_Water, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, 20, 20, 0.4);
		
		if(rand_f32() < 0.4)
			xmgen_add_lake(&world->map, Tile_Caz, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f));

		if(rand_f32() < 0.7)
			xmgen_add_lake(&world->map, Tile_Water, rand()%MAP_WIDTH, rand()%MAP_HEIGHT, 20, 20, 0.4);
		
		if(rand_f32() < 0.3){
			xmgen_add_lake(&world->map, Tile_Lava, 0, 0, MAP_WIDTH, MAP_HEIGHT, 0.55);
		}
	}
	//whatLevel > 0.4f && whatLevel <= 0.3f
	else if(whatLevel > 0.4f && whatLevel <= 0.7f){
		int grid = 1 + rand()%5;
		world->map = xmgen(MAP_WIDTH, MAP_HEIGHT, grid, maxRooms);
		xmgen_add_enviroment(&world->map, TIle_Grass, 0, 0, MAP_WIDTH, MAP_HEIGHT, (0.45 + rand_f32() / 10.0f));

		if(rand_f32() < 0.2f){
			int what = rand()%4;
			if(what >= 2 && what < 4)
				xmgen_add_lake(&world->map, Tile_Caz, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f));
			else if(what == 1)
				xmgen_add_lake(&world->map, Tile_Water, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f));
			else
				xmgen_add_lake(&world->map, Tile_Lava, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f)); 	
		}
		//if(rand_f32() < 0.8)
	}
	//whatLevel > 0.7f && whatLevel <= 0.9f
	else if(whatLevel > 0.7f && whatLevel <= 0.95f){
		world->map = xmgen_graph(MAP_WIDTH, MAP_HEIGHT, maxRooms, 5, 10, rand()%2);
		xmgen_add_enviroment(&world->map, TIle_Grass, 0, 0, MAP_WIDTH, MAP_HEIGHT, (0.45 + rand_f32() / 10.0f));
		if(rand_f32() < 0.5f)
			xmgen_add_lake(&world->map, Tile_Water, MAP_WIDTH/4, MAP_HEIGHT/4, 30, 30, 0.4);
		if(rand_f32() < 0.2f){
			int what = rand()%4;
			if(what >= 2 && what < 4)
				xmgen_add_lake(&world->map, Tile_Caz, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f));
			else if(what == 1)
				xmgen_add_lake(&world->map, Tile_Water, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f));
			else
				xmgen_add_lake(&world->map, Tile_Lava, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f)); 	
		}
	}
	else{
		world->map = xmgen_room_maze(MAP_WIDTH, MAP_HEIGHT, 60, 20, maxRooms, 5, 6+rand()%5);
		xmgen_add_enviroment(&world->map, TIle_Grass, 0, 0, MAP_WIDTH, MAP_HEIGHT, (0.45 + rand_f32() / 10.0f));
		if(rand_f32() < 0.3f){
			xmgen_add_lake(&world->map, Tile_Caz, 0, 0, MAP_WIDTH, MAP_HEIGHT,  (0.45 + rand_f32() / 10.0f));
		}

	}
	
	//For this prob ight map 
	world->ambientStrenght = rand_f32() / 2.0f;    // 0.0 - 0.1 PROB LIGHTING POWER
	if(rand_f32() < 0.33)
		world->ambientStrenght = 0;
	world->saveAmbientStrenght = world->ambientStrenght;
	

	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			world->gasMap[y][x].type = gasNo;
		}	
	}
	//Entrance 
		while(1) {
		int x = rand()%world->map.w, y = rand()%world->map.h;
		
		if(world->map.walling[y][x] == Tile_Dirt  || world->map.walling[y][x] == TIle_Grass || world->map.walling[y][x] == Tile_BGrass) {
			world->position[0] = (Position) {
				x, y
				};
			break;
			}
		}
	generate_doors(world, ent);
	remove_non_posible_elements(world);
	for(int i = 0; i < rand()%5; i++){
		
		while(1){
		const int x = rand()%world->map.w; 
		const int y = rand()%world->map.h;
		calculate_diakstra_map(world, x, y, 0);
		if(world->dikstra[y][x] < 255 
		&& (world->map.walling[y][x] == Tile_Dirt || world->map.walling[y][x] == TIle_Grass || world->map.walling[y][x] == Tile_BGrass )){
			add_trap(world, rand()%TRAP_NUM, x, y);
			break;
		}
	}
	}
	//Generate down stairs ad up stairs
	//for(int i = 0; i < 100; i++)
	while(1){
		const int x = rand()%world->map.w; 
		const int y = rand()%world->map.h;
		calculate_diakstra_map(world, x, y, 0);
		if(world->dikstra[y][x] < 255 
		&& (world->map.walling[y][x] == Tile_Dirt || world->map.walling[y][x] == TIle_Grass || world->map.walling[y][x] == Tile_BGrass )){
			world->map.walling[y][x] = Tile_DownS;
			break;
		}
	}
	//for(int i = 0; i < 100; i++)
	while(1){
		const int x = rand()%world->map.w; 
		const int y = rand()%world->map.h;
		calculate_diakstra_map(world, x, y, 0);
		if(world->dikstra[y][x] < 255 
		&& (world->map.walling[y][x] == Tile_Dirt || world->map.walling[y][x] == TIle_Grass || world->map.walling[y][x] == Tile_BGrass )){
			world->map.walling[y][x] = Tile_UpS;
			break;
		}
	}
	//Stores
	//for(int i = 0; i < 100; i++)
	if(rand_f32() < CHANCE_SHOP){
		while(1){
			int x = rand()%world->map.w;
			int y = rand()%world->map.h; 
			if(world->map.walling[y][x] == Tile_Dirt){
				float chance  = rand_f32();
				if(chance <= 0.3f){
					world->map.walling[y][x] = Tile_Genera;
				}
				else if(chance < 0.5){
					world->map.walling[y][x] = Tile_Wepon;
				}
				else if(chance < 0.6){
					world->map.walling[y][x] = Tile_Armory;
				}
				else if(chance < 0.8){
					world->map.walling[y][x] = Tile_Pot;
				}
				else{
					world->map.walling[y][x] = Tile_Scro;
				}	
				break;
			}
			
		
		}
	}
	
	add_enviroment(world);
	xmprint(world->map);
	
	//Temp fix for this to be global var
	static Generator_DA temp = (Generator_DA){0};
	temp = (Generator_DA){0};
	for(int i = 0; i < generators->count; i++){
		
		printf("%d (%d %d %d)", i, generators->items[i].startDepth, generators->items[i].endDepth, level);
		if((generators->items[i].startDepth <= level) && (generators->items[i].endDepth >= level)){
			printf("lOOP");
			da_append(&temp, generators->items[i]);
		}
	}

	
	//Get ge  n
	//Tbd machines for secret puzzle rooms or somthing
	int nItems  = 3 + rand()%2;
	while(nItems > 0){
		const int x = rand()%world->map.w;
		const int y = rand()%world->map.h;
		if(world->map.walling[y][x] == Tile_Dirt){
			random_item_generator(&world->items, (Position){(float)x, (float)y});
			nItems--;
			printf("items %d %d\n", nItems, world->items.count);
			if(world->items.count > 0){
				int it = create_entity(world);
				uint8_t whatI = world->items.items[world->items.count - 1].type + S_Sword;
				world->items.items[world->items.count - 1].pos = (Position){(float)x, (float)y};
				add_component(world, it, COMP_POSITION, &(Position){world->items.items[world->items.count - 1].pos.x, 
					world->items.items[world->items.count - 1].pos.y});
				add_component(world, it, COMP_RENDER, &(Renderable){whatI});
			}
		}
							

	}
	//exit(-1);
	print_all_generators(&temp);
	//exit(-1);
	Position_DA dist = {0}; 
	int numIt = 0;	
	while(world->nMonster < 12){
		
		numIt++;
		if(numIt == 1000){
			break;
		}
		int genNumber = 0;
		Position pos = (Position){0.0f, 0.0f};
		int numInt = 0;
		
		while(1){
			if(numInt++ > 100)
				break;
			 
			genNumber= rand()%temp.count;
			//genNumber = 0;
			//const int level = temp.items[genNumber].chances.count;
			printf("%d %f\n", level, temp.items[genNumber].chances.items[level]);
			
			if(temp.items[genNumber].chances.items[level] < 0.0f)
				temp.items[genNumber].chances.items[level] *= -1.0f; 
			else if(temp.items[genNumber].chances.items[level] == 0.0f)
				temp.items[genNumber].chances.items[level] = 1.0f;
			if(rand_f32() < temp.items[genNumber].chances.items[level]){
				break;
			}
		}

		//Position for generator 
		int iterNumInt1 = 0;
		while(1){
			iterNumInt1++;
			if(iterNumInt1 > 1000){
				break;
			}
			const int x = rand()%MAP_WIDTH; 
			const int y = rand()%MAP_HEIGHT;
			if(world->map.walling[y][x] != Tile_Dirt || world->map.walling[y][x] != TIle_Grass){
				int is = true;
				for(int j = 0; j < dist.count; j++){
					if(Vector2DistanceSqr(dist.items[j], (Vector2){(float)x, (float)y}) < 100){
						is = false;
						break;
					}
				}
				if(is == true){
					pos = (Position){(float)x, (float)y};
					da_append(&dist, pos);
					generate_monster_generator(world, &temp.items[genNumber], pos, ent);
					break;
				}
			}

		}
		 

		
		//Generate position

		//generate_monster_of_type(world, ent, &temp.items[genNumber]);

	}
	

	//exit(-1);

	//free(temp.items);
	world->tempGen = &temp;
	free(dist.items);




	
//	generate_monster_of_type(world, ent, Zombie);
//	generate_monster_of_type(world, ent, Zombie);
//	generate_monster_of_type(world, ent, Zombie);
}




void load_global_generator(Generator_DA* generators, const char* name){
    char *content = malloc(MAX_SIZE_OF_JSON);
    memset(content, '\0', MAX_SIZE_OF_JSON);
    FILE *f = fopen(name, "r");
    if(f == NULL) {
        ASSERT("Generators JSON does not exist\n\n");
    }
    const int size = fread(content, sizeof(char), MAX_SIZE_OF_JSON, f);
    DROP(size);
    cJSON *json = cJSON_Parse(content);
    ERR_JSON(json);
    
    // Get the Generators array
    cJSON *generators_json = cJSON_GetObjectItemCaseSensitive(json, "Generators");
    if (cJSON_IsArray(generators_json)) {
        cJSON *generator_json = NULL;
        cJSON_ArrayForEach(generator_json, generators_json) {
            Generator generator = {0};
            
            // Parse Depths
            cJSON *depths_json = cJSON_GetObjectItemCaseSensitive(generator_json, "Depths");
            if (depths_json) {
                cJSON *start_json = cJSON_GetObjectItemCaseSensitive(depths_json, "start");
                cJSON *end_json = cJSON_GetObjectItemCaseSensitive(depths_json, "end");
				cJSON *nMonster = cJSON_GetObjectItemCaseSensitive(depths_json, "nMonster");
                if (cJSON_IsNumber(start_json) && cJSON_IsNumber(end_json) && cJSON_IsNumber(nMonster))  {
                    generator.startDepth = start_json->valueint;
                    generator.endDepth = end_json->valueint;
					generator.nMonsters = nMonster->valueint;
                }
            }
            
            // Parse Chances array
            cJSON *chances_json = cJSON_GetObjectItemCaseSensitive(generator_json, "Chances");
            if (cJSON_IsArray(chances_json)) {
                cJSON *chance_json = NULL;
                cJSON_ArrayForEach(chance_json, chances_json) {
                    if (cJSON_IsNumber(chance_json)) {
                        da_append(&generator.chances, (float)chance_json->valuedouble);
                    }
                }
            }
            
            // Parse MonsterGenerator array
            cJSON *monsters_json = cJSON_GetObjectItemCaseSensitive(generator_json, "MonsterGenerator");
            if (cJSON_IsArray(monsters_json)) {
                cJSON *monster_json = NULL;
                cJSON_ArrayForEach(monster_json, monsters_json) {
                    Monster_Generator monster_gen = {0};
                    
                    cJSON *name_json = cJSON_GetObjectItemCaseSensitive(monster_json, "Monstername");
                    cJSON *chance_json = cJSON_GetObjectItemCaseSensitive(monster_json, "chance");
                    
                    if (cJSON_IsString(name_json) && cJSON_IsNumber(chance_json)) {
                        // Find the monster type from Monster_Names array
                        const char* monster_name = name_json->valuestring;
                        int monster_type = -1;
                        
                        // Search through Monster_Names to find the matching index
                        for (size_t i = 0; i < sizeof(Monster_Names) / sizeof(Monster_Names[0]); i++) {
                            if (strcmp(Monster_Names[i], monster_name) == 0) {
                                monster_type = i;
                                break;
                            }
                        }
                        
                        if (monster_type != -1) {
                            monster_gen.type = (Monster_Type)monster_type;
                            monster_gen.chance = (float)chance_json->valuedouble;
                            da_append(&generator.monsters, monster_gen);
                        }
                    }
                }
            }
            
            // Append the completed generator to the generators array
            da_append(generators, generator);
			generator = (Generator){0};
        }
    }
    
    cJSON_Delete(json);
    free(content);
    fclose(f);
}

void print_all_generators(Generator_DA* generators) {
    if (generators == NULL || generators->count == 0) {
        printf("No generators loaded.\n");
        return;
    }

    printf("=== GENERATORS (%d total) ===\n\n", generators->count);

    for (int i = 0; i < generators->count; i++) {
        Generator* gen = &generators->items[i];
        
        printf("Generator %d:\n", i + 1);
        printf("  Depths: %d to %d with %d monsters\n", gen->startDepth, gen->endDepth, gen->nMonsters);
        
        // Print chances
        printf("  Chances (%d): [", gen->chances.count);
        for (int j = 0; j < gen->chances.count; j++) {
            printf("%.3f", gen->chances.items[j]);
            if (j < gen->chances.count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        
        // Print monsters
        printf("  Monsters (%d):\n", gen->monsters.count);
        for (int j = 0; j < gen->monsters.count; j++) {
            Monster_Generator* monster_gen = &gen->monsters.items[j];
            const char* monster_name = "Unknown";
            
            // Safely get monster name from Monster_Names array
            if (monster_gen->type >= 0 && monster_gen->type < (int)(sizeof(Monster_Names) / sizeof(Monster_Names[0]))) {
                monster_name = Monster_Names[monster_gen->type];
            }
            
            printf("    - %s: %.1f%% chance\n", monster_name, monster_gen->chance * 100.0f);
        }
        printf("\n");
    }
}