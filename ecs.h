#ifndef _ECS_H
#define _ECS_H
#include "da_arr.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "cJSON/cJSON.h"

#include "Map/Map.h"

//#include "raymath.h"

#include "raylib.h"
#include "common.h"
#include "item.h"


// ECS world container
typedef struct {
	CompMask masks[MAX_ENTITIES];  // Component mask per entity

	// Component arrays (indexed by entity ID)
	char*      name[MAX_ENTITIES];
	Position   position[MAX_ENTITIES];
	Renderable renderable[MAX_ENTITIES];
	Health     health[MAX_ENTITIES];
	Input      input[MAX_ENTITIES];  //this is just for player prob just one element other array for monsters or use this
	Stats      stats[MAX_ENTITIES];
	State      state[MAX_ENTITIES];
	Gas        gas[MAX_ENTITIES];
	Spell      spell[MAX_ENTITIES];
	Item_DA    inventory[MAX_ENTITIES];
	Projectile projectile[MAX_ENTITIES];
	int        free_list[MAX_ENTITIES];  // Recycled entity IDs
	int        num_free;                 // Free list count
	Map        map;
	int        isExpMap[MAP_HEIGHT][MAP_WIDTH];
	float      dikstra[MAP_HEIGHT][MAP_WIDTH];
	int        visibe[MAP_HEIGHT][MAP_WIDTH];
	Gas        gasMap[MAP_HEIGHT][MAP_WIDTH];
	Trap       trapMap[MAP_HEIGHT][MAP_WIDTH];
	Fire       fire[MAX_ENTITIES];
	StatusEffects status[MAX_ENTITIES];
	Item_DA    items;
	float      ambientStrenght;           //
	float      saveAmbientStrenght;
	int        nMonster;
	int        identScrools[Scroll_Num];
	int        identPotions[Potion_Num];
	TempStats_DA tempStatsPlayer;
	int         level;
	int         expPlayer;

	} World;

//Shoud	
typedef struct{
	char*    name;
	CompMask masks;
	//Components
	Position position;
	Renderable renderable;
	Health health;
	Input  input;
	Stats  stats;
	State  state;
	ChanceItem_DA item;

}Global_Ent;

typedef struct{
	int capacity;
	int count;
	Global_Ent *items;

}Global_Ent_DA;


typedef struct{
	int count;
	int capacity;
	Position *items;


}Position_DA;


typedef struct{
	int 	count;
	int	 	capacity;
	float  *items;
}Float_DA;


typedef struct{
	Monster_Type type;
	float        chance;
}Monster_Generator;

typedef struct{
	int 	count;
	int	 	capacity;
	Monster_Generator  *items;
}Monster_Generator_DA;



typedef struct{
	int   startDepth;
	int   endDepth;
	int   nMonsters;
	Tiles tiles;
	Float_DA chances;
	Monster_Generator_DA monsters;
}Generator;

typedef struct{
	int 		count;
	int	 		capacity;
	Generator  *items;
}Generator_DA;



void load_global_ent(Global_Ent_DA* ent, const char* name);
void init_world(World* world);
int  create_entity(World* world);
void destroy_entity(World* world, int entity);
void add_component(World* world, int entity, CompType type, void* data);
void add_tag(World* world, int entity, CompType tag);
void add_components_to_ent_depending_on_T(World* world, Global_Ent_DA* ent, int monster, int type, Vector2 p);
void remove_component(World* world, int entity, CompType type);
void generate_map(World* world, Global_Ent_DA *ent);
void calculate_diakstra_map(World *world, int goalX, int goalY, uint8_t isEnt);
int is_monster_in_next_postition(World* world, float x, float y);
int is_monster_on_position(World* world, float x, float y);
int is_position_on_position(World* world, float x, float y);
int attack_dmg_callculations(World* world, int attacker, int defender, int isRange);
void inventory_to_map(World* world, int entity);
void add_trap(World* world, Trap_Types type, int x, int y);
void generate_level(World* world, int level, Generator_DA *generators, Global_Ent_DA *ent);
void load_global_generator(Generator_DA* generators, const char* name);
void print_all_generators(Generator_DA* generators);



#endif