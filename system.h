#ifndef _SYSTEM_H
#define _SYSTEM_H



#include "renderer.h"
#include "da_arr.h"



void render_system(World* world, EngineData* engine, Sprite_DA *sprites);
void render_system2d(World* world, EngineData* engine, Sprite_DA *sprites);
//uSE THIS actions in isMoving


void monster_change_state_system(World* world, EngineData *engine);
void monster_state_system(World* world, EngineData *engine, Global_Ent_DA* ent);
//void monster_ai_system(World* world, EngineData *engine);

void monster_attack_system(World* world, Global_Ent_DA* ent, EngineData* engine);
void reset_attack_input(World* world, EngineData* engine);

void health_system(World* world, Global_Ent_DA* ent, EngineData *engine);
void regen_system(World *world);
void input_system(World* world, EngineData *engine);
void input_system2d(World* world, EngineData *engine);
void update_player_position_system(World* world, EngineData* engine);
void update_entity_position_system(World* world, EngineData* engine);
void player_door_system(World* world, EngineData *engine);

void projectile_system(World* world, EngineData *engine);

void perception_system(World *world, EngineData *engine);

void lighting_system(World* world, EngineData* engine);


void gas_system(World* world, EngineData* engine);
void water_system(World *world, EngineData* engine);
void fire_system(World *world, EngineData* engine);
void trap_system(World* world, Global_Ent_DA *ent, EngineData* engine);
void status_system(World* world, EngineData* engine);
void scroll_system(World *world, Global_Ent_DA *ent, EngineData* engine);
void potion_system(World *world, EngineData *engine);
void throw_system(World *world, EngineData *engine);
void level_system(World *world, Generator_DA *generators, Global_Ent_DA *ent, EngineData *engine);
void spawn_monster_system(World *world, Generator_DA *generators, Global_Ent_DA *ent, EngineData *engine);

void food_system(World *world, EngineData *engine);
void mushroom_system(World *world, EngineData *engine);
void nutrition_system(World *world, EngineData *engine);
void stamina_system(World *world, EngineData *engine);


void load_system(World* world, EngineData *engine, Generator_DA *generators);



#endif


