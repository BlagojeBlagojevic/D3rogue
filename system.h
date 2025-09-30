#ifndef _SYSTEM_H
#define _SYSTEM_H


#include "renderer.h"
#include "da_arr.h"

void render_system(World* world, EngineData* engine, Sprite_DA *sprites);
//uSE THIS actions in isMoving


void monster_change_state_system(World* world, EngineData *engine);
void monster_state_system(World* world, EngineData *engine);
//void monster_ai_system(World* world, EngineData *engine);

void monster_attack_system(World* world, EngineData* engine);
void reset_attack_input(World* world, EngineData* engine);

void health_system(World* world, EngineData *engine);
void input_system(World* world, EngineData *engine);
void update_player_position_system(World* world, EngineData* engine);
void update_entity_position_system(World* world, EngineData* engine);
void player_door_system(World* world, EngineData *engine);

void projectile_system(World* world, EngineData *engine);

void perception_system(World *world, EngineData *engine);

void lighting_system(World* world, EngineData* engine);


void gas_system(World* world, EngineData* engine);

#endif


