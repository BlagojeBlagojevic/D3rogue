#ifndef _RENDERER_H
#define _RENDERER_H

#include <string.h>
#include <stdlib.h>
#include "ecs.h"
#include "raylib.h"
#include "raymath.h"
#include "da_arr.h"
#include "cJSON/cJSON.h"


//Str is for storing the mesages for game engine

//Use this for sending text to render in the screen


typedef struct {
	int 	count;
	int 	capacity;
	char** items;
	} Str;

typedef struct{
	Model    model;
	Mesh     mesh;
}ModelMesh;

typedef struct {
	ModelMesh *items;
	int count;
	int capacity;
}ModelMesh_DA;



typedef struct{
	int width;
	int height;
	Camera   camera;
	Model    model;
	Mesh     mesh;
	Vector3  modelPosition;
	Vector3  nextPosition;
	float    playerYaw;
	float    targetYaw;
	uint8_t  isMoving;
	int      isRotation; 
	uint8_t  isAnyMoving;
	uint8_t  isEntMoving;
	uint8_t  isGasRun;
	float    moveLerpAlpha;
	Str      messeges;

	//Actions items
	int      isRenderInventory;
	int      whatItem; 
	//Tbd we will see if this 	
	Item_Equipted   whatAction;
	int             itemAction;
	int      systemAction;
	Str      tempStr;

	int      isRenderMap;
	Texture2D water;
	Texture2D fire;
	
	//Items temp 
	int      isRenderPickup;
	int      isRenderStats;
	int      isRenderTrade;
	Num      tempItemList;

	//Water model mesh
	//Model    modelW;
	//Mesh     meshW;
//	ModelMesh_DA water;
	//Vector3  modelPositionW;
	int drawDistance;
	int isTorch;
	int isTorchEqu;
	int depth;
	int itemThrowId;
	int is2d;


}EngineData;

typedef struct{
	Texture2D texture;
	int scale;
}Sprite;

typedef struct{
	int 	count;
	int 	capacity;
	Sprite* items;
}Sprite_DA;



EngineData* init_engine(World *world, int player_entity_id, const char* name_atlas, const char* water_atlas);

EngineData* init_engine_soft(World *world, int player_entity_id, EngineData *engine);

void free_engine(EngineData *engine);

void render_loop(World *world, EngineData *engine);

void render_map_testing(World *world, EngineData *engine);

void render_map(World *world, EngineData *engine);

void render_event_messages(EngineData *engine, const int x, const int y, const int w, const int h);

void render_stats_update(World* world, EngineData *engine);

void render_stats_(EngineData *engine, World* world, const int x, int y, int w, int h);

void load_sprites(Sprite_DA *sprites, const char* name);

void render_droped_items(World *world, EngineData *engine, Sprite_DA* sprites);

void render_inventory_system(World* world, Item_DA* inventory, EngineData* engine);

void render_trade_system(World* world, EngineData* engine);

void setup_item_system(World* world, EngineData* engine);

void render_pickup_system(World* world, Item_DA* inventory, EngineData* engine);



#endif