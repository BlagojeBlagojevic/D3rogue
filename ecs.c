
#define INF 255
#include "ecs.h"
#include <stdlib.h>

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
	ERR_JSON(json);
	cJSON *e = cJSON_GetObjectItemCaseSensitive(json, "ent");
	ERR_JSON(e);
	cJSON *temp = NULL;
	Global_Ent g = {0};
	cJSON_ArrayForEach(temp, e){
		cJSON* name          = cJSON_GetObjectItemCaseSensitive(temp, "name");
		ERR_JSON(name);
		g.name = strdup(name->valuestring);
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

					cJSON* chanceRe = cJSON_GetObjectItemCaseSensitive(cOMP_STATE, "chanceRe");
					ERR_JSON(chanceRe);
					g.state.chancesRe = (float)chanceRe->valuedouble;

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
		printf("\n");	
		da_append(ent, g);
	}
	//exit(-1);
	cJSON_Delete(json);	
	//exit(-1);
}


// Initialize ECS world
void init_world(World* world) {
	memset(world->isExpMap, false, sizeof(int) * MAP_HEIGHT*MAP_WIDTH);
	for (int i = 0; i < MAX_ENTITIES; i++) {
		world->masks[i] = 0;
		world->inventory[i] = (Item_DA){0};
		world->free_list[i] = MAX_ENTITIES - 1 - i;
		}
	world->num_free = MAX_ENTITIES;
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
	world->masks[entity] = 0;  // Mark as inactive
	world->position[entity] = (Vector2){0, 0}; //Cuzz COMP_POSITION is 0 bit
	world->input[entity].isMoving = NOT;
	world->input[entity].isFinishedAttack = false;
	world->free_list[world->num_free++] = entity;  // Add to free list
	world->inventory[entity].count = 0;
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
		//case COMP_PROJEC:
		//	world->state[entity] = *(Projectile*)data;
		//	break;	
		
		case COMP_OPEN:
			ASSERT("Not implemneted OPEN");
			break;				
		// Handle other components
		default:
			ASSERT("Unrechable Component");
			break;
		}
	}

// Tag component (no data)
void add_tag(World* world, int entity, CompType tag) {
	world->masks[entity] |= tag;
	}

// Remove component/tag
void remove_component(World* world, int entity, CompType type) {
	world->masks[entity] &= ~type;
	}



static void add_components_to_ent_depending_on_T(World* world, Global_Ent_DA* ent, int monster, int type, Vector2 p){
	Global_Ent e = ent->items[type];
	world->name[monster] = e.name;
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
		});
	}
	if(e.masks & COMP_STATE){
		add_component(world, monster, COMP_STATE,  &(State) {
			e.state.current, e.state.chancesR, e.state.chancesH, e.state.chancesW, e.state.chancesRe, e.state.chancesB, 
			e.state.chanceRange, 0, 1, 1, 0
		});
	}
	if (e.masks & COMP_MONSTER){
		add_tag(world, monster, COMP_MONSTER);	
	}
	if (e.item.count > 0) {
 	   add_items_from_list(&e.item, &world->inventory[monster]);
	}
	
	
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
	for (int y = 0; y < world->map.h; y++){
		for (int x = 0; x < world->map.w; x++){
			if(world->map.walling[y][x] ==  '\"'){
				int plantID = create_entity(world);
				add_component(world, plantID, COMP_POSITION, &(Position){(float)x, (float)y});
				if(rand_f32() < CHANCE_BIGPLANT){
					add_component(world, plantID, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_PlantBig)});
						world->map.walling[y][x] = '\'';
				}
				else
					add_component(world, plantID, COMP_RENDER, &(Renderable) {
						(Sprite_Type)(S_Plant)});
			}
			else if(world->map.walling[y][x] ==  '\''){
				int plantID = create_entity(world);
				add_component(world, plantID, COMP_POSITION, &(Position){(float)x, (float)y});
				add_component(world, plantID, COMP_RENDER, &(Renderable) {
				(Sprite_Type)(S_PlantBig)});
			} 
		}	
	}
	
}


void generate_map(World* world, Global_Ent_DA *ent) {
	//3 change for shape
	int nRoom  = rand()%60 + 20;
	//nRoom = 20;

	int what =  rand()%10;
	int whatS = rand()%4;

	switch (what)
	{
		case 7:
			world->map = xmgen(MAP_WIDTH, MAP_HEIGHT, 1, 100);
			break;
		case 0:
			world->map = xmgen(MAP_WIDTH, MAP_HEIGHT, 1, nRoom);
		break;
		case 6:
		case 1:
			world->map = xmgen_graph(MAP_WIDTH, MAP_HEIGHT, nRoom, 8, 10, 2);
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
		//xmgen_add_enviroment(&world->map, '"', 0, 0, MAP_WIDTH, MAP_HEIGHT, rand_f32() / 10.0f);
		world->ambientStrenght = rand_f32() / 2.0f;    // 0.0 - 0.1 PROB LIGHTING POWER
	}
		
	//world->ambientStrenght = 0.0f;
	//world->ambientStrenght = 1.0f;
	//Save ambient strenght
	world->saveAmbientStrenght = world->ambientStrenght;
	
	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			world->gasMap[y][x].type = gasNo;
		}	
	}
	//memset(world->gasMap, MAP_HEIGHT*MAP_WIDTH, sizeof(Gas));

	
	//world->map = xmgen_bsp_leaf(MAP_WIDTH, MAP_HEIGHT, 10,  8);
	//
	//world->map = xmgen_bsp(MAP_WIDTH, MAP_HEIGHT, 10);
	//world->map = xmgen_subtractive(MAP_WIDTH, MAP_HEIGHT, 1);
	//world->map = Map xmgen_astar(const int w, const int h, const int num_rooms)
	//world->map = xmgen_modules(MAP_WIDTH, MAP_HEIGHT, 10);
	//world->map = xmgen_rcd(MAP_WIDTH, MAP_HEIGHT, nRoom, 8, 10);
	//world->map = xmgen_brogue(MAP_WIDTH, MAP_HEIGHT, nRoom, 8, 12);
	//world->map = xmgen_maze(MAP_WIDTH, MAP_HEIGHT, 30, 30);
	//world->map = xmgen_room_maze(MAP_WIDTH, MAP_HEIGHT, 30, 30, 4, 5, 5);
//	world->map = xmgen_lsystems(MAP_WIDTH, MAP_HEIGHT, 100, 10, "F");
	//world->map  = xmgen_voronoi(MAP_WIDTH, MAP_HEIGHT, 10, 8, 10);
	//world->map = xmgen_graph(MAP_WIDTH, MAP_HEIGHT, nRoom, 4, 8, 0);
	xmprint(world->map);
	//world->map = xmgen_perlin(MAP_WIDTH, MAP_HEIGHT, 0.01); 
	//xmprint(world->map);
	//S p pos
	generate_doors(world, ent);
	remove_non_posible_elements(world);
	//Gen araond non need  ends

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
		//add_component(world, monster, COMP_GAS, &(Gas){gasBasic, true, 10, RED});	
		int type =  rand()%Monster_Num;
		if(type == 0){
			type = Zombie;
		}
		printf("Type %d\n\n", type); 
		add_components_to_ent_depending_on_T(world, ent, monster, type, p);
		}
		for(int i  = 0; i < 50; i++){
			//int x = rand()%world->map.w;
			//int y = rand()%world->map.h;
			//generate_enviroment_depending_on_type(world, x, y);

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
void calculate_diakstra_map(World *world, int goalX, int goalY) {

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
				if (world->map.walling[ny][nx] == '#') continue;   //NOT 255

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
//		
	world->dikstra[goalY][goalX] = INF;
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if(world->map.walling[y][x] == '#')
				world->dikstra[y][x] = (float)INF;
			}
		}
	}	
*/

	
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
				if (world->map.walling[ny][nx] == '#') continue;   //NOT 255

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
            if (world->map.walling[y][x] == '#') {
                world->dikstra[y][x] = 255.0f;
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
			/*
			for(int j = 0; j < 8 && i != 0; j++){
				const int x = world->position[i].x + dirs[j][0];
				const int y = world->position[i].y + dirs[j][1];
				if(world->dikstra[y][x] != 255 && world->dikstra[y][x] != 0){
					world->dikstra[y][x] += 5.0f; 
				}
			}*/
		}
		}

		//pLAYER
		world->dikstra[(int)world->position[0].y][(int)world->position[0].x] = 255; 
		
}
//*/
/*
#include "raymath.h"
void calculate_diakstra_map(World *world, int goalX, int goalY, uint8_t isEnt){
	for (size_t y = 0; y < world->map.h; y++){
		for (size_t x = 0; x < world->map.w; x++){
			if(world->map.walling[y][x] != '#'){
				const Vector2 goal = (Vector2){goalX, goalY};
				Vector2 current = (Vector2){x, y};
				float distance = Vector2Distance(goal,current);
				world->dikstra[y][x] = distance;
			}
		else{
			world->dikstra[y][x] = 255.0f;
		}	
			
	}		
	}

	for(int i = 0; i < MAX_ENTITIES && isEnt; i++){
    	CompMask mask = COMP_MONSTER | COMP_POSITION;
    	if((mask & world->masks[i]) == mask){
    		world->dikstra[(int)world->position[i].y][(int)world->position[i].x] = 255;
			}
		}
		//pLAYER
		world->dikstra[(int)world->position[0].y][(int)world->position[0].x] = 255; 
		
	
}
*/

int is_monster_in_next_postition(World* world, float x, float y){
	CompMask mask = COMP_MONSTER;
	const Vector2 pos = {x, y};
	for(int i = 1; i < MAX_ENTITIES; i++){
		
		const float dis = Vector2Distance(world->position[i], pos);
		if((mask & world->masks[i]) == mask){
			if((dis < 1.0f)){
				//exit(-1);
				printf("Monster %d", i);
				return i;
			}
			
		}
	}
	printf("Monster %d", 0);
	return 0;
}

//DEXTERTY is basicly a doge chance
//If get a higher then dex dogfe
//else -- dmg clamp to a max strenght  

#define D1_20 (rand()%20 + 1)
#define D1(x) (rand()%(x) + 1)

static int  Dn_X(int n, int x){
int max = 0, changeMax = 0; 
for(int i = 0; i < n; i++){changeMax = rand()%x + 1; 
	//if(changeMax > max) 
	max += changeMax;}

	return max;	
}



int attack_dmg_callculations(World* world, int attacker, int defender){
	int dmgATTACK = D1(world->stats[attacker].str);
	int dmgValue   = world->stats[attacker].dmgMin + rand()%(world->stats[attacker].dmgMax - world->stats[attacker].dmgMin);
	int armorValue = 0;
	int dogeDEFFENCE = D1(world->stats[defender].dex);

	//Attacker add to stats
	for(int i = 0; i < world->inventory[attacker].count; i++){
		const Item item = world->inventory[attacker].items[i];
		if(item.isEqu == true){
			//Tbd store
			if(item.to == EQUIPTED_WEPON){
				//MESSAGE_F("Used %s", item.name);
				//exit(-1);
				dmgValue+=Dn_X(item.nDice, item.value);
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
				armorValue+=Dn_X(item.nDice, item.value);
				//exit(-1)
			}
			dogeDEFFENCE +=item.stats.dex;
		}		
	}
	int AC = armorValue; //4 types equipted for armor
	//For testing
	if(defender == 0)
	LOG("AC %d\n", AC);
	if(dmgATTACK == world->stats[attacker].str){
		dmgValue += 2;
		//return 10;
	}

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
	Item_DA inventory = world->inventory[entity];
	const int x = world->position[entity].x;
	const int y = world->position[entity].y;
	for(int i = 0; i < inventory.count; i++){
		float chance = rand_f32();
		if(CHANCE_TO_DROP >= chance){
			Item item = inventory.items[i];
			item.pos.x = x;
			item.pos.y = y;
			item.isEqu = false;
			da_append(&world->items, item);
			int it = create_entity(world);
			uint8_t whatI = item.type + S_Sword;
			add_component(world, it, COMP_RENDER, &(Renderable) {
				(Sprite_Type)(whatI),
				});
			add_component(world, it, COMP_POSITION, &(Position){
				x, y
			});	
		}

		//printf("1");
	}
}

