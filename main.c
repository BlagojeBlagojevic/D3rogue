// main.c
#include<stdio.h>
#include "ecs.h"
#include "system.h"
#include "renderer.h"
#include <unistd.h>  // For sleep()
#include "Map/Map.h"




#define MAP_TESTING
#include<time.h>
int main() {
	srand(time(NULL));
	World world;
	init_world(&world);
	Global_Ent_DA entDA = {0};
	load_global_ent(&entDA, "entJSON.json");

	// Create player
	int player = create_entity(&world);
	add_component(&world, player, COMP_POSITION, &(Position) {
		0, 0
		});
	add_component(&world, player, COMP_HEALTH, &(Health) {
		100, 100
		});
	add_component(&world, player, COMP_STATS,  &(Stats) {
		20, 20, 20, 20, 0, 5, 5, 2, 1
	});	
	add_tag(&world, player, COMP_PLAYER);
	add_component(&world, player, COMP_INPUT, NULL);
	add_component(&world, player, COMP_GAS, &(Gas){gasBasic, true, 50, RED});
	//add_item_to_inventory(DMace, &world.inventory[player], true);
	//add_item_to_inventory(Sword, &world.inventory[player], false);
	add_item_to_inventory(Dagger, &world.inventory[player], false);
	add_item_to_inventory(LeatherArmor, &world.inventory[player], false);
	add_item_to_inventory(Bow, &world.inventory[player], false);
	//add_item_to_inventory(Arrows, &world.inventory[player], false);
	add_item_to_inventory(Arrows, &world.inventory[player], false);
	add_item_to_inventory(Tourch, &world.inventory[player], false);

	InitWindow(1100, 700, "raylib [models] example - cubesmap loading and drawing");
	
	Image a = LoadImage("assets/door/open.png");
	
	UnloadImage(a);
	generate_map(&world, &entDA);

	EngineData *engine = init_engine(&world, player, "assets/tex.png", "assets/wa.jpeg");
	engine->width = 1100;
	engine->height = 700;
	
	if(engine == NULL) {
		ASSERT("Not allocated ENGINE");
		}

	//EnableEventWaiting();

		


	//engine->messeges = {0};
	engine->messeges.count = 0;
	engine->messeges.capacity = 0;
	engine->messeges.items = NULL; 
	Sprite_DA sprites = {0};
	load_sprites(&sprites, "spriteJSON.json");

	MESSAGE("Da li ovo radi ili ne");
	DisableCursor();
	Shader lightingShader = LoadShader("shaders/lighting.vs", "shaders/lighting.fs");
    // Get shader locations for uniforms
    lightingShader.locs[0] = GetShaderLocation(lightingShader, "viewPos");
    int lightPosLoc = GetShaderLocation(lightingShader, "lightPos");
	int ambientStrenghtLoc = GetShaderLocation(lightingShader, "ambientStrength"); 
	int lightingOptionLoc = GetShaderLocation(lightingShader, "lightingOption");
	SetShaderValue(lightingShader, ambientStrenghtLoc, &world.ambientStrenght, SHADER_UNIFORM_FLOAT);
	
	engine->model.materials[0].shader = lightingShader;
	Shader blureShader = LoadShader(0, "shaders/blur.fs");
		


	RenderTexture2D target = LoadRenderTexture(engine->width, engine->height);
	
	//Draw distance 
	engine->drawDistance = 50 - 1.0f / world.ambientStrenght;
	if(engine->drawDistance < 10){
		engine->drawDistance = 10;
	}
	
	MESSAGE_F("Dist %d, Streng %f", engine->drawDistance, world.ambientStrenght);
	//sleep(20);
	//exit(-1);
	// Game loop
	while (!WindowShouldClose()) {
		SetShaderValue(lightingShader, lightPosLoc, &engine->camera.position, SHADER_UNIFORM_VEC3);
		SetShaderValue(lightingShader, lightingShader.locs[0], &engine->camera.position, SHADER_UNIFORM_VEC3);
		SetShaderValue(lightingShader, ambientStrenghtLoc, &world.ambientStrenght, SHADER_UNIFORM_FLOAT);
		//world.state[0].maxStamina = world.stats[0].cons;
		if(engine->isTorchEqu == true){
			int what = 3;
			SetShaderValue(lightingShader, lightingOptionLoc, &what, SHADER_UNIFORM_INT);
		}
		else{
			int what = 0;
			SetShaderValue(lightingShader, lightingOptionLoc, &what, SHADER_UNIFORM_INT);
		}	
		//UpdateLightValues(shader, lights);
		//projectile_system(&world, engine);
		//If rend inven disable
		if(!engine->isRenderInventory && !engine->isRenderPickup && !engine->isRenderMap  && !engine->isRenderStats ){
			if(engine->isGasRun){
				gas_system(&world, engine);
			}

			health_system(&world, engine);
			if(engine->isMoving == false && engine->isEntMoving == true) {
				monster_change_state_system(&world, engine);			
				monster_state_system(&world, engine);
				
				//perception_system(&world, engine);
				if(engine->isTorch == false){
					lighting_system(&world, engine);
					engine->isTorch = true;
				}
				
			//LOG("Move");
			//engine->isMoving = false;
			}
			if(engine->isEntMoving == false && engine->isMoving == false){
				reset_attack_input(&world, engine);
				input_system(&world, engine);
				player_door_system(&world, engine);
				
				engine->isTorch = false;
			}

		//health_system(&world);
			projectile_system(&world, engine);
			monster_attack_system(&world, engine);
			update_player_position_system(&world, engine);
			update_entity_position_system(&world, engine);

		}	
		
		BeginTextureMode(target);       // Enable drawing to texture
			ClearBackground(BLACK);	
			BeginMode3D(engine->camera);
		//LOG("model %s", engine->model);
			//
			
			DrawModel(engine->model, engine->modelPosition, 1.0f, WHITE);
			for(int i = 0; i < engine->water.count; i++)
				DrawModel(engine->water.items[i].model, engine->modelPosition, 1.0f, WHITE);
			render_system(&world, engine, &sprites);
		
			EndMode3D();
		EndTextureMode();
		
		
		BeginDrawing();
		
		
#ifdef MAP_TESTING

		render_map_testing(&world, engine);
		render_event_messages(engine, 400, 0 , 800, 200);
			
#else

		
			
		//Tbd relative to height
		render_event_messages(engine, 400, 0 , 800, 200);
			
		if(engine->isRenderInventory){
			render_inventory_system(&world, &world.inventory[0], engine);
		}
		if(engine->isRenderPickup){
			render_pickup_system(&world, &world.items, engine);
			
		}
		if(engine->isRenderMap){
			render_map(&world, engine);
		}
		if(engine->isRenderStats){
			render_stats(&world, &world.inventory[0], engine);
		}
		
		DrawFPS(10, 10);
		//render_loop(&world, engine);
#endif
		EndDrawing();	
		BeginShaderMode(blureShader);
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
        EndShaderMode();
		}

	return 0;
	}