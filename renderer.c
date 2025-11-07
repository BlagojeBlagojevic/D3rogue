#include "renderer.h"

//Let be brige be hear

EngineData* init_engine(World *world, int player_entity_id, const char* name_atlas, const char* water_atlas) {
	const Position p =  world->position[player_entity_id];



	//Tbd from map file

	EngineData *engine 		  = malloc(1*sizeof(EngineData));
	engine->isRenderInventory = false;
	engine->isRenderPickup    = false;
	engine->isRenderMap       = false;
	engine->isRenderStats     = false;
	engine->is2d              = true;
	//engine->tempStr = (Str){0};
	memset(&engine->tempStr, 0, sizeof(Str));
	//We see
	engine->tempItemList = (Num){0};
	engine->whatItem = 0;
	engine->itemThrowId = -1;
	
	//Zbog kog kurc ovo ne radi
	//free(world->items.items);
	//xmprint(world->map);


	Image map_image;
	map_image.width  = world->map.w;
	map_image.height = world->map.h;
	map_image.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
	uint8_t *data = malloc(map_image.width * map_image.height);
	for(int y = 0; y < world->map.h; y++ ) {
		for(int x = 0; x < world->map.w; x++ ) {
			if(world->map.walling[y][x] == '#') {
				data[y*world->map.w+x] = 255; //WALL
				}
			else {
				data[y* world->map.w+x] = 0; //FLOOR
				}
				world->dikstra[y][x] = 0;
				world->isExpMap[y][x] = false;
				world->visibe[y][x] = 0;
		        world->gasMap[y][x] = (Gas){0};
		        world->trapMap[y][x] =  (Trap){0};;
		       // world->fire[y][x] = (Fire){0};
			}
			
		}
	map_image.data = data;
	//Unloaded at the end

	//engine->texture = LoadTextureFromImage(map_image);



	engine->camera.position = (Vector3) {
		(float)p.x, 0.6f, (float)p.y
		};
	engine->camera.target = (Vector3) {
		0.185f, 0.6f, 0.0f
		};
	engine->camera.up = (Vector3) {
		0.01f, 1.0f, 0.01f
		};
	engine->camera.fovy = 60.0f;
	engine->camera.projection = CAMERA_PERSPECTIVE;
	  

	engine->mesh = GenMeshCubicmap(map_image, (Vector3) {
		1.0f, 1.0f, 1.0f
		});
	engine->model = LoadModelFromMesh(engine->mesh);
	
	engine->nextPosition = engine->camera.position;
	engine->playerYaw = 0.0f;
	engine->targetYaw = 0.0f;
	engine->isMoving = false;
	engine->drawDistance = 100;

	Texture texture_matirial = LoadTexture(name_atlas); ;
	engine->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_matirial;

	engine->modelPosition = (Vector3) {
		0.0f, 0.0f, 0.0f
		};

	UnloadImage(map_image);
	#ifdef __EMSCRIPTEN__
	SetTargetFPS(60);
	#else
	SetTargetFPS(60);
	#endif
	engine->isEntMoving = false;
	engine->isMoving = false;
	engine->isGasRun = false;
	//Water stuffs
	//C img
	bool isFirst = false;
	engine->water =  LoadTexture(water_atlas);
	engine->fire  = LoadTexture("assets/la.jpeg"); 

	//engine->modelW = LoadModelFromMesh(engine->mesh);
	//Texture textureW_matirial = LoadTexture(water_atlas); ;
	//engine->modelW.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureW_matirial;
	//UnloadImage(waterImage);
	return engine;
	}



EngineData* init_engine_soft(World *world, int player_entity_id, EngineData *engine) {
	const Position p =  world->position[player_entity_id];



	//Tbd from map file

	
	engine->isRenderInventory = false;
	engine->isRenderPickup    = false;
	engine->isRenderMap       = false;
	engine->isRenderStats     = false;
	//engine->tempStr = (Str){0};
	memset(&engine->tempStr, 0, sizeof(Str));
	//We see
	engine->tempItemList = (Num){0};
	engine->whatItem = 0;
	engine->itemThrowId = -1;
	
	//Zbog kog kurc ovo ne radi
	//free(world->items.items);
	//xmprint(world->map);


	Image map_image;
	map_image.width  = world->map.w;
	map_image.height = world->map.h;
	map_image.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
	uint8_t *data = malloc(map_image.width * map_image.height);
	for(int y = 0; y < world->map.h; y++ ) {
		for(int x = 0; x < world->map.w; x++ ) {
			if(world->map.walling[y][x] == '#') {
				data[y*world->map.w+x] = 255; //WALL
				}
			else {
				data[y* world->map.w+x] = 0; //FLOOR
				}
				world->dikstra[y][x] = 0;
				world->isExpMap[y][x] = false;
				world->visibe[y][x] = 0;
		        world->gasMap[y][x] = (Gas){0};
		        world->trapMap[y][x] =  (Trap){0};;
		       // world->fire[y][x] = (Fire){0};
			}
			
		}
	map_image.data = data;
	//Unloaded at the end

	//engine->texture = LoadTextureFromImage(map_image);



	engine->camera.position = (Vector3) {
		(float)p.x, 0.6f, (float)p.y
		};
	engine->camera.target = (Vector3) {
		0.185f, 0.6f, 0.0f
		};
	engine->camera.up = (Vector3) {
		0.01f, 1.0f, 0.01f
		};
	engine->camera.fovy = 60.0f;
	engine->camera.projection = CAMERA_PERSPECTIVE;

	engine->mesh = GenMeshCubicmap(map_image, (Vector3) {
		1.0f, 1.0f, 1.0f
		});
	engine->model = LoadModelFromMesh(engine->mesh);
	
	engine->nextPosition = engine->camera.position;
	engine->playerYaw = 0.0f;
	engine->targetYaw = 0.0f;
	engine->isMoving = false;
	if(world->ambientStrenght != 0)
		engine->drawDistance = 50 - 1.0f / world->ambientStrenght;
    else	
		engine->drawDistance = 10;
	if(engine->drawDistance < 10){
        engine->drawDistance = 10;
    }


	

	engine->mesh = GenMeshCubicmap(map_image, (Vector3) {
		1.0f, 1.0f, 1.0f
		});
	engine->model = LoadModelFromMesh(engine->mesh);
	
	engine->nextPosition = engine->camera.position;
	engine->playerYaw = 0.0f;
	engine->targetYaw = 0.0f;
	engine->isMoving = false;
	engine->drawDistance = 100;

	Texture texture_matirial = LoadTexture("assets/tex.png"); ;
	engine->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_matirial;

	engine->modelPosition = (Vector3) {
		0.0f, 0.0f, 0.0f
		};

	UnloadImage(map_image);
	#ifdef __EMSCRIPTEN__
	SetTargetFPS(60);
	#else
	SetTargetFPS(60);
	#endif
	engine->isEntMoving = false;
	engine->isMoving = false;
	engine->isGasRun = false;
	//Water stuffs
	//C img
	bool isFirst = false;
	
	//engine->width = 1200;
    //engine->height = 700;
    // Initialize messages and sprites
    //engine->messeges.count = 0;
    //engine->messeges.capacity = 0;
    //engine->messeges.items = NULL;
    //engine->drawDistance = 50 - 1.0f / world->ambientStrenght;
    //if(engine->drawDistance < 10){
    //    engine->drawDistance = 10;
    //}
	
	//engine->modelW = LoadModelFromMesh(engine->mesh);
	//Texture textureW_matirial = LoadTexture(water_atlas); ;
	//engine->modelW.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureW_matirial;
	//UnloadImage(waterImage);
	return engine;
	}

	


//Tbd move water fire into a sprite_Da	
void free_engine(EngineData *engine){
	//UnloadTexture(engine->water);
	//UnloadTexture(engine->fire);
	//UnloadTexture(engine->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture);
	//free(engine);
	//UnloadMesh(engine->mesh);
	UnloadModel(engine->model);
}


void render_loop(World *world, EngineData *engine) {
	DROP(world);

	ClearBackground(RAYWHITE);

	//BeginMode3D(engine->camera);
	//LOG("model %s", engine->model);
	DrawModel(engine->model, engine->modelPosition, 1.0f, WHITE);
	//DrawCube((Vector3){0, 0, 0}, 10, 10, 10, GREEN);
	//EndMode3D();

	DrawFPS(10, 10);

	//UpdateCamera(&engine->camera, CAMERA_FREE);
	}


	
void render_map(World *world, EngineData *engine){
	//ENTIRE MAP
	const int sizeX = engine->width  / 150;
	const int sizeY = engine->height / 150;
	const Color colorBacg = {0x18, 0x18, 0x18, 255};
	///Color c = WHITE;
	///c.a = 255;
	Color c = {0x18, 0x18, 0x18, 255};
	
	//MAP
	DrawRectangle(0, 0, engine->width, engine->height, c);
	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			if((world->map.walling[y][x] == ' ' || world->map.walling[y][x] == '*') && world->isExpMap[y][x] == 1)
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLACK);
			if(world->map.walling[y][x] == '#'&& world->isExpMap[y][x] == 1){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, colorBacg);
			}
			
			if((world->map.walling[y][x] == '+' || world->map.walling[y][x] == '-') && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLACK);
				DrawText("+", x*sizeX, y*sizeY , 10, GREEN);
			
			}
				
			if((world->map.walling[y][x] == '~') && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLUE);
				DrawText("~", x*sizeX, y*sizeY , 10, BLUE);
			
			}

			if((world->map.walling[y][x] == Tile_Dwater) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLUE);
				DrawText("~", x*sizeX, y*sizeY , 10, BLUE);
			
			}

			if((world->map.walling[y][x] == Tile_Lava) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, ORANGE);
				//DrawText("", x*sizeX, y*sizeY , 10, RED);
			
			}
			if((world->map.walling[y][x] == Tile_Fire) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLACK);
				DrawText("^", x*sizeX, y*sizeY , 10, ORANGE);
			}
			if((world->map.walling[y][x] == Tile_Caz) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BROWN);
				DrawText(";", x*sizeX, y*sizeY , 10, WHITE);
			
			}
			if((world->map.walling[y][x] == Tile_DownS) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, WHITE);
				DrawText("<", x*sizeX, y*sizeY , 20, WHITE);
			
			}
			if((world->map.walling[y][x] == Tile_UpS) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLACK);
				DrawText(">", x*sizeX, y*sizeY , 20, WHITE);
			
			}
			
				
			if((world->map.walling[y][x] == '\"' || world->map.walling[y][x] == Tile_BGrass) && world->isExpMap[y][x]){
				DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLACK);
				DrawText("\"", x*sizeX, y*sizeY , 10, GREEN);
				
			}
				
			//DrawRectangle(x*sizeX, y*sizeY, sizeX, sizeY, BLACK);		
		}
	}

	//Render monsters
	 CompMask mask = COMP_POSITION | COMP_RENDER | COMP_MONSTER;
	if(world->status[0].telepatyTurn > 0)
	for(int i = 0; i < MAX_ENTITIES; i++){
		if((world->masks[i] & mask) == mask){
		DrawText("M", world->position[i].x * sizeX, world->position[i].y * sizeY, 10,  RED);		
		}
	}
	
	 DrawText("@", world->position[0].x * sizeX, world->position[0].y * sizeY, 10,  GREEN);
	//for(int i = 1; i < MAX_ENTITIES; i++){
	//	if ((world->masks[i] & mask) == mask){
	//		DrawRectangle(world->position[i].x*sizeX, world->position[i].y*sizeY, sizeX, sizeY, WHITE);
	//	}
	//}
	if(IsKeyPressed(KEY_C)){
		engine->isRenderMap = false;
	}

}	
	

void render_map_testing(World *world, EngineData *engine){
	DROP(engine);
	//ENTIRE MAP
	const int sizeX = 1200 / 80;
	const int sizeY = 800 / 80;
	
	//MAP
	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			if(world->map.walling[y][x] == '#')
			DrawText("#", x*sizeX, y*sizeY , 10, GREEN);
			if(world->map.walling[y][x] == '+')
			DrawText("+", x*sizeX, y*sizeY , 10, GREEN);
			if(world->gasMap[y][x].type != gasNo)
			DrawText("P", x*sizeX, y*sizeY , 10, BLUE);
					
		}
	}
	 CompMask mask = COMP_POSITION | COMP_RENDER;
	 DrawText("@", world->position[0].x * sizeX, world->position[0].y * sizeY, 10,  RAYWHITE);
	for(int i = 1; i < MAX_ENTITIES; i++){
		if ((world->masks[i] & mask) == mask){
			DrawText("M", world->position[i].x * sizeX, world->position[i].y * sizeY,10, RED);
		}
	}
	
}


void render_stats_(World* world, const int x, int y, int w, int h){
	DrawRectangle(x, y, w, h, (Color){0X18, 0X18, 0X18, 128});
	char* tempStr = malloc(STR_SIZE);
	snprintf(tempStr, STR_SIZE, "Health: %d/%d", world->health[0].current, world->health[0].max);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);y+=30;

	snprintf(tempStr, STR_SIZE, "Dmg: %d - %d", world->stats[0].dmgMin,  world->stats[0].dmgMax);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Def: %d", world->stats[0].defence);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);y+=30;

	
	snprintf(tempStr, STR_SIZE, "Str: %d", world->stats[0].str);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Dex: %d", world->stats[0].dex);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);


	snprintf(tempStr, STR_SIZE, "Int: %d", world->stats[0].inte);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Cons: %d", world->stats[0].cons);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Stealth: %d", world->stats[0].stealth);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);
	
	snprintf(tempStr, STR_SIZE, "Exp: %d", world->expPlayer);
	DrawText(tempStr, x, y+=20, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);


	
	free(tempStr);
	
}


//Tet for now be able to be set up
void render_event_messages(EngineData *engine, const int x, const int y, const int w, const int h){
	Color c = BLACK;
	
	c.a = 128;
	
	//Tbd some texture
	DrawRectangle(x, y, w, h, c);
	//Ren c mes
	//Tbd num messages thru func
	if(engine->messeges.items != NULL || engine->messeges.count > 0)
	for(int i = 0; i < 5; i++){
		const int index = engine->messeges.count - i - 1;
		if(index < 0){
			break;
		}
		const int xPos = x + 10;
		int yPos = y + 10 + 20 * i;
		DrawText(engine->messeges.items[index], xPos, yPos, 20, WHITE);
		
		
	}	
}	



void load_sprites(Sprite_DA *sprites, const char* name){

	char *content = malloc(MAX_SIZE_OF_JSON);
	memset(content, '\0', MAX_SIZE_OF_JSON);
	FILE *f = fopen(name, "r");
	if(f == NULL) {
		ASSERT("Sprite JSON does not exist\n\n");
		//TBD Error windows popup or something
		}
	const int  size = fread(content, sizeof(char), MAX_SIZE_OF_JSON, f);
	DROP(size);
	LOG("%s\n", content);
	cJSON *json = cJSON_Parse(content);
	
	ERR_JSON(json);
	cJSON *s = cJSON_GetObjectItemCaseSensitive(json, "Sprite");
	ERR_JSON(s);
	cJSON *temp = NULL;
	cJSON_ArrayForEach(temp, s) {
		cJSON *path  = cJSON_GetObjectItemCaseSensitive(temp, "path");
		cJSON *scale = cJSON_GetObjectItemCaseSensitive(temp, "scale"); 
		ERR_JSON(path);
		ERR_JSON(scale);
		Sprite s;
		s.scale   = (float)scale->valuedouble;
		s.texture = LoadTexture(path->valuestring); 
		da_append(sprites, s);
		}
	cJSON_Delete(json);
	fclose(f);
	f = fopen("nonEntJSON.json", "r");
	if(f == NULL){
		ASSERT("Non Existaned file");
	}
	memset(content, '\0', MAX_SIZE_OF_JSON);
	const int  sa = fread(content, sizeof(char), MAX_SIZE_OF_JSON, f);
	DROP(sa);
	json = cJSON_Parse(content);
	ERR_JSON(json);
	cJSON *path = cJSON_GetObjectItemCaseSensitive(json , "Paths");
	ERR_JSON(path);
	temp = NULL;
	cJSON_ArrayForEach(temp, path) {
		Sprite s;
		s.scale   = 3;
		s.texture = LoadTexture(temp->valuestring);
		da_append(sprites, s);
	}
	free(content);
	//Textures for poison
	Image map_image = GenImageColor(500, 500, (Color){255, 0, 0, 50});
	Sprite sp;
	sp.scale = 1;
	sp.texture = LoadTextureFromImage(map_image);
	da_append(sprites, sp);
				
	//



}

/*
void render_droped_items(World *world, EngineData *engine, Sprite_DA* sprites){
	for(int i = 0; i < world->items.count; i++){
		Position p = world->items.items[i].pos;
		//MESSAGE_F("%d %d", (int)p.x, (int)p.y);
		printf("%d %d\n", (int)p.x, (int)p.y);
		const Vector3 pos = (Vector3) {
			(float)p.x, 0.01f, (float)p.y - 0.5f
			};
		DrawBillboard(engine->camera, sprites->items[PileItem].texture, pos, 0.7f, WHITE);
		//DrawBillboard(engine->camera, s.texture, pos, 1.6f, WHITE);	
		//DrawRectangle(p.x, p.y, 100, 100, RED);
	}
}
*/
void render_stats_update(World* world, EngineData *engine){
	DrawRectangle(0, 0, engine->width, engine->height, (Color){0x18, 0x18, 0x18, 255});
	//Stats 
	DrawRectangle(50, 100 + 50*engine->whatItem, engine->width, 20, RED );
	int x = 50, y = 50;
	//DrawRectangle(50, 50, engine->width, engine->height, (Color){0X18, 0X18, 0X18, 128});
	char* tempStr = malloc(STR_SIZE);
	snprintf(tempStr, STR_SIZE, "Health: %d/%d", world->health[0].current, world->health[0].max);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Dmg: %d - %d", world->stats[0].dmgMin,  world->stats[0].dmgMax);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Def: %d", world->stats[0].defence);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	
	snprintf(tempStr, STR_SIZE, "Str: %d", world->stats[0].str);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Dex: %d", world->stats[0].dex);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);


	snprintf(tempStr, STR_SIZE, "Int: %d", world->stats[0].inte);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Cons: %d", world->stats[0].cons);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	snprintf(tempStr, STR_SIZE, "Stealth: %d", world->stats[0].stealth);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);
	
	snprintf(tempStr, STR_SIZE, "Exp: %d", world->expPlayer);
	DrawText(tempStr, x, y+=50, 20, WHITE);
	memset(tempStr, '\0', STR_SIZE);

	


	if(IsKeyPressed(KEY_C)){
		engine->whatItem = 0;
		engine->isRenderStats = false;
	}
	if(IsKeyPressed(KEY_UP)){
		if(engine->whatItem > 0){
			engine->whatItem--;			
		}
		else{
			engine->whatItem = 8;
		}
	}
	
	if(IsKeyPressed(KEY_DOWN)){
		if(8 > engine->whatItem ){
			engine->whatItem++;			
		}
		else{
			engine->whatItem = 0;
		}
	}	
	if(IsKeyPressed(KEY_RIGHT)){
		switch (engine->whatItem){
		//HEALTH
		case 0:{
			if(world->expPlayer - 100 > 0){
				world->health[0].max+=1;
				world->expPlayer -= 100;
			}
			break;
		}
		//DMG
		case 1:{
			if(world->expPlayer - 1000 > 0){
				if(world->stats[0].dmgMax > world->stats[0].dmgMin + 2){
					if(rand_f32() < 0.5)
						world->stats[0].dmgMax+=1;
					else 
						world->stats[0].dmgMin+=1;
				}
				else{
					world->stats[0].dmgMax+=1;
				}
			world->expPlayer-=1000;	
			}
				
			break;
		}	
		//DEF
		case 2:{
			if(world->expPlayer - 1000 > 0){
				world->stats[0].defence+=1;
				world->expPlayer-=1000;	
			}

				break;
		}	
		//STR
		case 3:{
			if(world->expPlayer - 1000 > 0){
				world->stats[0].str+=1;
				world->expPlayer-=1000;	
			}

				break;
		}
		//DEX
		case 4:{
			if(world->expPlayer - 1000 > 0){
				world->stats[0].dex+=1;
				world->expPlayer-=1000;	
			}

				break;
		}
		//INT
		case 5:{
			if(world->expPlayer - 1000 > 0){
				world->stats[0].inte+=1;
				world->expPlayer-=1000;	
			}

				break;
		}
		//CONS
		case 6:{
			if(world->expPlayer - 1000 > 0){
				world->stats[0].cons+=1;
				world->expPlayer-=1000;	
			}

				break;
		}
		//Stealth
		case 7:{
			if(world->expPlayer - 1000 > 0){
				world->stats[0].stealth+=1;
				world->expPlayer-=1000;	
			}

				break;
		}



		default:
			break;
		}

	}

	
}







//Tbd Rename to inventory system
void render_inventory_system(World* world, Item_DA* inventory, EngineData* engine){

	if(engine->tempStr.count == 0)
	for(int i = 0; i < inventory->count; i++){
		char *itemStr = malloc(STR_SIZE);
	    char *tempStr = malloc(STR_SIZE);
		
		memset(itemStr, 0, STR_SIZE);
		memset(tempStr, 0, STR_SIZE);
		if(inventory->items[i].type == Scroll 
			&& world->identScrools[inventory->items[i].scroll] == false){
			if(strcpy(itemStr, "Scroll of unown origin") == NULL){
				ASSERT("String overflow");
			}
		}
		else if(inventory->items[i].type == Potion 
			&& world->identPotions[inventory->items[i].potion] == false){
			if(strcpy(itemStr, "Potion of unown origin") == NULL){
				ASSERT("String overflow");
			}
		}
		else
		if(strcpy(itemStr, inventory->items[i].name) == NULL){
			ASSERT("String overflow");
		}
		if(strcat(itemStr, "               ") == NULL){
			ASSERT("String overflow");
		}
		//Render dice if no scroll
		if(inventory->items[i].type != Scroll && inventory->items[i].type != Potion){

			snprintf(tempStr, STR_SIZE, "D%d_", inventory->items[i].nDice);		
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
			}
			snprintf(tempStr, STR_SIZE, "%d  ", inventory->items[i].value);		
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
		}
			snprintf(tempStr, STR_SIZE, "    <%d>  ", inventory->items[i].strReq);		
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
		}
		
		}
		//If change max amount of stats for items change hear
		//Stats are renderd only if ident
		if(inventory->items[i].isIdent){
			
		if(inventory->items[i].stats.cons != 0){
			memset(tempStr, 0, STR_SIZE);
			snprintf(tempStr, STR_SIZE, "Cons %d, ", inventory->items[i].stats.cons);
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
			}
			}
		
		if(inventory->items[i].stats.dex != 0){
			memset(tempStr, 0, STR_SIZE);
			snprintf(tempStr, STR_SIZE, "Dex %d, ", inventory->items[i].stats.dex);
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
			}
		}	
		
		if(inventory->items[i].stats.inte != 0){
			memset(tempStr, 0, STR_SIZE);
			snprintf(tempStr, STR_SIZE, "Inte %d, ", inventory->items[i].stats.inte);
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
			}
		}
		
		if(inventory->items[i].stats.str != 0){
			memset(tempStr, 0, STR_SIZE);
			snprintf(tempStr, STR_SIZE, "Str %d, ", inventory->items[i].stats.str);
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
			}
		}
		if(inventory->items[i].isCursed == true){
			memset(tempStr, 0, STR_SIZE);
			snprintf(tempStr, STR_SIZE, "curesed");
			if(strcat(itemStr, tempStr) == NULL){
				ASSERT("String overflow");
			}
		}
		}

		if(inventory->items[i].isEqu == true){
			if(inventory->items[i].to == EQUIPTED_WEPON){
				if(strcat(itemStr, "Wielded") == NULL){
					ASSERT("String overflow");
				}
			}
			else if(inventory->items[i].to == EQUIPTED_RANGE){
				if(strcat(itemStr, "Wielded Range") == NULL){
					ASSERT("String overflow");
				}
			}
			
			else{
				if(strcat(itemStr, "Equipted") == NULL){
					ASSERT("String overflow");
				}
			}	
			
		}
			
		da_append(&engine->tempStr, itemStr);
		//MESSAGE_F("%s", engine->tempStr.items[engine->tempStr.count - 1]);	
		free(tempStr);
	}
	//free(itemStr);
	//

	//Red str
	const Color tBLACK = (Color){0, 0, 0, 220};
	const int fontWidth = 20;
	DrawRectangle(0, 0, engine->width, engine->height, tBLACK); 

	for(int i = 0; i < engine->tempStr.count; i++){
		if(i == engine->whatItem){
			DrawRectangle(50, 50 + i * 20, engine->width, fontWidth, WHITE);
		}
	
		DrawText(engine->tempStr.items[i], 50, 50 + i * 20, fontWidth, RED);
			
	}


		//PlayerInventory Load
	//Let logic be hear for disabling enbling and cordination
	if(IsKeyPressed(KEY_C)){
			engine->isRenderInventory = (engine->isRenderInventory) ? 0 : 1;
			for(int i = 0; i < engine->tempStr.count; i++){
				free(engine->tempStr.items[i]);
			}
			engine->tempStr.count = 0;
			engine->whatItem = 0;
		}
	if(IsKeyPressed(KEY_T)){
			engine->itemThrowId = engine->whatItem;
			engine->whatAction = EQUIPTED_ARMOR;
			engine->isRenderInventory = (engine->isRenderInventory) ? 0 : 1;
			for(int i = 0; i < engine->tempStr.count; i++){
				free(engine->tempStr.items[i]);
			}
			engine->tempStr.count = 0;
			engine->whatItem = 0;
		}	
	if(IsKeyPressed(KEY_UP)){
		if(engine->whatItem > 0){
			engine->whatItem--;			
		}
		else{
			engine->whatItem = engine->tempStr.count - 1;
		}
	}
	
	if(IsKeyPressed(KEY_DOWN)){
		if((engine->tempStr.count - 1) > engine->whatItem ){
			engine->whatItem++;			
		}
		else{
			engine->whatItem = 0;
		}
	}
	if(IsKeyPressed(KEY_RIGHT)){
		if(inventory->items[engine->whatItem].to >= EQUIPTED_ARMOR 
			&& inventory->items[engine->whatItem].to <= EQUIPTED_HEAD){
			int isCursed = equipt_item(&world->inventory[0], engine->whatItem);
			if(isCursed == true){
				MESSAGE("Not posible to remove cuss it is cursed");
			}
			for(int i = 0; i < engine->tempStr.count; i++){
				free(engine->tempStr.items[i]);
			}
			engine->tempStr.count = 0;
			//exit(-1);
		}
		else{
			engine->whatAction = inventory->items[engine->whatItem].to; //Dispach systems
			engine->isRenderInventory = (engine->isRenderInventory) ? 0 : 1;
			engine->itemAction = engine->whatItem;
			for(int i = 0; i < engine->tempStr.count; i++){
				free(engine->tempStr.items[i]);
			}
			engine->tempStr.count = 0;
			engine->whatItem = 0;
			
		}
		
	}
}

void setup_item_system(World* world, EngineData* engine){
	engine->tempItemList.count = 0;
	//MESSAGE_F("Items count %d", world->items.count);
	for(int i = 0; i < world->items.count; i++){
		const float dist = Vector2Distance(world->position[0], world->items.items[i].pos);
		//if(world->position[0].x == world->items.items[i].pos.x &&  world->position[0].y == world->items.items[i].pos.y)
		if(dist <= 1.1f){
			da_append(&engine->tempItemList, i);
			//exit(-1);
		}
	}
}


void render_pickup_system(World* world, Item_DA* inventory, EngineData* engine){
	setup_item_system(world, engine);
	if(engine->tempItemList.count != 0 && engine->tempStr.count == 0)
	for(int i = 0; i < engine->tempItemList.count; i++){
		//exit(-1);
		//if(engine->tempItemList.items[])
		char *itemStr = malloc(STR_SIZE);
	    char *tempStr = malloc(STR_SIZE);
		int what = engine->tempItemList.items[i];
		memset(itemStr, 0, STR_SIZE);
		memset(tempStr, 0, STR_SIZE);
		if(inventory->items[what].type == Scroll 
			&& world->identScrools[inventory->items[what].scroll] == false){
			if(strcpy(itemStr, "Scroll of unown origin") == NULL){
				ASSERT("String overflow");
			}
		}
		else if(inventory->items[what].type == Potion 
			&& world->identPotions[inventory->items[what].potion] == false){
			if(strcpy(itemStr, "Potion of unown origin") == NULL){
				ASSERT("String overflow");
			}
		}
		else if(strcpy(itemStr, inventory->items[what].name) == NULL){
			ASSERT("String overflow");
		}
		//if(strcpy(itemStr, inventory->items[what].name) == NULL){
		//	ASSERT("String overflow");
	//	}
		if(strcat(itemStr, "               ") == NULL){
			ASSERT("String overflow");
		}
		if(inventory->items[what].type != Scroll){
		snprintf(tempStr, STR_SIZE, "D%d_", inventory->items[what].nDice);		
		if(strcat(itemStr, tempStr) == NULL){
			ASSERT("String overflow");
		}
		
		snprintf(tempStr, STR_SIZE, "%d  ", inventory->items[what].value);		
		if(strcat(itemStr, tempStr) == NULL){
			ASSERT("String overflow");
		}
		}
	
		if(inventory->items[what].isEqu == true){
			if(inventory->items[what].to == EQUIPTED_WEPON){
				if(strcat(itemStr, "Wielded") == NULL){
					ASSERT("String overflow");
				}
			}
			else{
				if(strcat(itemStr, "Equipted") == NULL){
					ASSERT("String overflow");
				}
			}	
			
		}
			
		da_append(&engine->tempStr, itemStr);
		//MESSAGE_F("%s", engine->tempStr.items[engine->tempStr.count - 1]);	
		free(tempStr);
	}
	//free(itemStr);
	//

	//Red str
	const Color tBLACK = (Color){0, 0, 0, 220};
	const int fontWidth = 20;
	DrawRectangle(0, 0, engine->width, engine->height, tBLACK); 

	for(int i = 0; i < engine->tempStr.count; i++){
		if(i == engine->whatItem){
			DrawRectangle(50, 50 + i * 20, engine->width, fontWidth, WHITE);
		}
		if(engine->tempStr.items[i] != NULL)
		DrawText(engine->tempStr.items[i], 50, 50 + i * 20, fontWidth, RED);
			
	}


		//PlayerInventory Load
	//Let logic be hear for disabling enbling and cordination
	if(IsKeyPressed(KEY_C)){
			engine->isRenderPickup = (engine->isRenderPickup) ? 0 : 1;
			engine->tempItemList.count = 0;
			for(int i = 0; i < engine->tempStr.count; i++){
				free(engine->tempStr.items[i]);
			}
			engine->tempStr.count = 0; 
		}
	if(IsKeyPressed(KEY_UP)){
		if(engine->whatItem > 0){
			engine->whatItem--;			
		}
		else{
			engine->whatItem = engine->tempStr.count - 1;
		}
	}
	
	if(IsKeyPressed(KEY_DOWN)){
		if((engine->tempStr.count - 1) > engine->whatItem ){
			engine->whatItem++;			
		}
		else{
			engine->whatItem = 1;
		}
	}

	if(IsKeyPressed(KEY_RIGHT) && engine->tempItemList.count != 0){
		//Pickup item from list
		const int n = engine->tempItemList.items[engine->whatItem];
		Item what = world->items.items[n];
		
		da_append(&world->inventory[0], what);
		//setup_item_system(world, engine);
		
		for(int i = 0; i < engine->tempStr.count; i++){
			free(engine->tempStr.items[i]);
		}	

		da_remove_unordered(&world->items, n);
		//free_item(&world->items, n);
		da_remove_unordered(&engine->tempItemList, engine->whatItem);
		
		//for(int i = 0; i < engine->tempStr.count; i++){
		//	free(engine->tempStr.items[i]);
		//}
		engine->whatItem = 0;
		engine->tempStr.count = 0;
		setup_item_system(world, engine);
		//setup_item_system(world, engine);
		//Remove rendering item from world
	
		for(int i = 1; i < MAX_ENTITIES; i++){
			if((world->masks[i] & COMP_RENDER) == COMP_RENDER)
			if(what.type == (world->renderable[i].type - S_Sword)){
				const float distance = Vector2Distance(world->position[0], world->position[i]);
				if(distance <= 1.1f){
					destroy_entity(world, i);
					//exit(-1);
					break;
				}

			}
		}		
	}

}


//void render_trow_system(World *world, EngineData* engine);