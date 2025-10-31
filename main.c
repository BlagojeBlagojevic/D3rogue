// main.c
#include <stdio.h>
#include "ecs.h"
#include "system.h"
#include "renderer.h"
#include "Map/Map.h"
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define MAP_TESTING

// Increase matrix stack size for WebGL/raylib compatibility
#define RL_MAX_MATRIX_STACK_SIZE 64

// Global variables for Emscripten main loop
static World* g_world = NULL;
static EngineData* g_engine = NULL;
static Sprite_DA g_sprites = {0};
static Global_Ent_DA g_entDA = {0};
static Generator_DA g_generators = {0};
static Shader g_lightingShader = {0};
static Shader g_blureShader = {0};
static RenderTexture2D g_target = {0};


void main_loop(void) {
    if (WindowShouldClose()) {
        // Cleanup when window closes
        UnloadShader(g_lightingShader);
        UnloadShader(g_blureShader);
        UnloadRenderTexture(g_target);
        CloseWindow();
        //emscripten_cancel_main_loop();
        return;
    }

    // Update shader values
    SetShaderValue(g_lightingShader, GetShaderLocation(g_lightingShader, "lightPos"), &g_engine->camera.position, SHADER_UNIFORM_VEC3);
    SetShaderValue(g_lightingShader, g_lightingShader.locs[0], &g_engine->camera.position, SHADER_UNIFORM_VEC3);
    SetShaderValue(g_lightingShader, GetShaderLocation(g_lightingShader, "ambientStrength"), &g_world->ambientStrenght, SHADER_UNIFORM_FLOAT);
    
    //int lightingOption = g_engine->isTorchEqu ? 3 : 0;
    //SetShaderValue(g_lightingShader, GetShaderLocation(g_lightingShader, "lightingOption"), &lightingOption, SHADER_UNIFORM_INT);
    	if(g_engine->isTorchEqu == true){
			int what = 3;
			SetShaderValue(g_lightingShader,  GetShaderLocation(g_lightingShader, "lightingOption"), &what, SHADER_UNIFORM_INT);
		}
		else{
			int what = 0;
			SetShaderValue(g_lightingShader,  GetShaderLocation(g_lightingShader, "lightingOption"), &what, SHADER_UNIFORM_INT);
		}
    // Game systems
    if(!g_engine->isRenderInventory && !g_engine->isRenderPickup && !g_engine->isRenderMap  && !g_engine->isRenderStats ){
        if(g_engine->isGasRun){
            gas_system(g_world, g_engine);
            water_system(g_world, g_engine);
            fire_system(g_world, g_engine);
            trap_system(g_world, &g_entDA, g_engine);
            status_system(g_world, g_engine);
        }

        health_system(g_world, &g_entDA, g_engine);
        scroll_system(g_world, &g_entDA, g_engine);
        potion_system(g_world, g_engine);
        throw_system(g_world, g_engine);
        
        if(g_engine->isMoving == false && g_engine->isEntMoving == true) {
            monster_change_state_system(g_world, g_engine);			
            monster_state_system(g_world, g_engine, &g_entDA);
            monster_attack_system(g_world, &g_entDA, g_engine);
            
            if(g_engine->isTorch == false){
                lighting_system(g_world, g_engine);
                g_engine->isTorch = true;
            }
        }
        
        if(g_engine->isEntMoving == false && g_engine->isMoving == false){
            reset_attack_input(g_world, g_engine);
            input_system(g_world, g_engine);
            player_door_system(g_world, g_engine);
            g_engine->isTorch = false;
        }

        projectile_system(g_world, g_engine);
        update_player_position_system(g_world, g_engine);
        update_entity_position_system(g_world, g_engine);
    }	
    
    // Rendering
    BeginTextureMode(g_target);
        ClearBackground(BLACK);		
        BeginMode3D(g_engine->camera);
        
        // Draw world model
        DrawModel(g_engine->model, g_engine->modelPosition, 1.0f, WHITE);
        
        // Render entities with matrix stack management
        rlPushMatrix();
        render_system(g_world, g_engine, &g_sprites);
        rlPopMatrix();
        
        EndMode3D();
    EndTextureMode();
    
    // UI Rendering
    BeginDrawing();
       // ClearBackground(BLACK);
        render_event_messages(g_engine, 400, 0, 800, 200);
  
        if(g_engine->isRenderInventory){
            render_inventory_system(g_world, &g_world->inventory[0], g_engine);
        }
        if(g_engine->isRenderPickup){
            render_pickup_system(g_world, &g_world->items, g_engine);
        }
        if(g_engine->isRenderMap){
            render_map(g_world, g_engine);
        }
        if(g_engine->isRenderStats){
            render_stats(g_world, &g_world->inventory[0], g_engine);
        }
        
        DrawFPS(10, 10);
        
        // Apply post-processing shader
       
    EndDrawing();
	 BeginShaderMode(g_blureShader);
        DrawTextureRec(g_target.texture, 
                      (Rectangle){ 0, 0, (float)g_target.texture.width, (float)-g_target.texture.height }, 
                      (Vector2){ 0, 0 }, WHITE);
	 EndShaderMode();
}

int main() {
    // Initialize random seed
    #ifdef __EMSCRIPTEN__
    //srand(emscripten_get_now());
    #else
    srand(time(NULL));
    #endif
    
    World world;
    init_world(&world);
    Global_Ent_DA entDA = {0};
    Generator_DA generators = (Generator_DA){0};
    
    // Load game data
    load_global_ent(&entDA, "entJSON.json");
    load_global_generator(&generators, "genJSON.json");
    print_all_generators(&generators);
    
    // Create player entity
    int player = create_entity(&world);
    add_component(&world, player, COMP_POSITION, &(Position){0, 0});
    add_component(&world, player, COMP_HEALTH, &(Health){30, 30});
    add_component(&world, player, COMP_STATS, &(Stats){12, 6, 10, 10, 0, 5, 5, 2, 1, 0});	
    world.stats[0].stealth = 10;
    add_tag(&world, player, COMP_PLAYER);
    add_component(&world, player, COMP_INPUT, NULL);
    add_component(&world, player, COMP_FIRE, &(Fire){0, 0});
    add_component(&world, player, COMP_STATUS, &(StatusEffects){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    
    // Initialize window
    //SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);  
    InitWindow(1200, 700, "3D Roguelike");
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));

    // Initialize world items and inventory
    world.items = (Item_DA){0};
    for(int i = 0; i < MAX_ENTITIES; i++){
        world.inventory[i] = (Item_DA){0};
    }
    
    // Generate level and initialize engine
    generate_level(&world, 0, &generators, &entDA);
    EngineData *engine = init_engine(&world, player, "assets/tex.png", "assets/wa.jpeg");
    
    if(engine == NULL) {
        TraceLog(LOG_ERROR, "Failed to initialize engine");
        CloseWindow();
        return -1;
    }
    
    // Add starter items
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Teleport, false, false);
    add_item_to_inventory(Dagger, &world.inventory[player], Scroll_No, Potion_No, false, false);
    add_item_to_inventory(Robe, &world.inventory[player], Scroll_No, Potion_No, false, false);
 //   add_item_to_inventory(Robe, &world.inventory[player], Scroll_No, false, false);
 //   add_item_to_inventory(Robe, &world.inventory[player], Scroll_No, false, false);
 //   add_item_to_inventory(Robe, &world.inventory[player], Scroll_No, false, false);
    add_item_to_inventory(Bow, &world.inventory[player], Scroll_No, Potion_No, false, false);
    add_item_to_inventory(Arrows, &world.inventory[player], Scroll_No, Potion_No, false, false);
    add_item_to_inventory(Tourch, &world.inventory[player], Scroll_No, Potion_No, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Identif, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_MagicMaping, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Calcific, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Fate, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Fate, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Identif, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Teleport, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_EnchantW, false, false);
    // add_item_to_inventory(Scroll, &world.inventory[player], Scroll_EnchantA, false, false);
    //add_item_to_inventory(Scroll, &world.inventory[player], Scroll_SummonMonster, false, false);
    add_item_to_inventory(Scroll, &world.inventory[player], Scroll_Identif, Potion_No, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Healing, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Str, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Int, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Size, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Str, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Att, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Def, false, false);
    //add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Poison, false, false);
    add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Acid, false, false);
    add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_Gas, false, false);
    add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_HealingGas, false, false);
    add_item_to_inventory(Potion, &world.inventory[player], Scroll_No, Potion_HealingGas, false, false);

    engine->width  = GetMonitorWidth(monitor);
    engine->height = GetMonitorHeight(monitor);
    
    // Initialize messages and sprites
    engine->messeges.count = 0;
    engine->messeges.capacity = 0;
    engine->messeges.items = NULL;
    
    Sprite_DA sprites = {0};
    load_sprites(&sprites, "spriteJSON.json");
    
    MESSAGE("Game initialized");
    
    // For Emscripten, we can't disable cursor in the same way
    #ifndef __EMSCRIPTEN__
    DisableCursor();
    #endif
    //world.ambientStrenght = 0;
   
    g_lightingShader = LoadShader("shaders/lighting.vs", "shaders/lighting.fs");
       
    if (g_lightingShader.id == 0) {
        TraceLog(LOG_WARNING, "Failed to load lighting shader, using default");
    } else {
        // Setup shader uniforms
        g_lightingShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(g_lightingShader, "viewPos");
        SetShaderValue(g_lightingShader, GetShaderLocation(g_lightingShader, "ambientStrength"), 
                      &world.ambientStrenght, SHADER_UNIFORM_FLOAT);
        
        //if (engine->model.materialCount > 0) {
            engine->model.materials[0].shader = g_lightingShader;
        //}
    }
    
   
    g_blureShader = LoadShader(0, "shaders/blur.fs");
   // #endif
    
    if (g_blureShader.id == 0) {
        TraceLog(LOG_WARNING, "Failed to load blur shader");
    }
    
    // Create render texture
    g_target = LoadRenderTexture(engine->width, engine->height);
    
    // Calculate draw distance
    engine->drawDistance = 50 - 1.0f / world.ambientStrenght;
    if(engine->drawDistance < 10){
        engine->drawDistance = 10;
    }
    
    MESSAGE_F("Draw distance: %d, Ambient strength: %f", engine->drawDistance, world.ambientStrenght);
    
    // Store global pointers
    g_world = &world;
    g_engine = engine;
    g_sprites = sprites;
    g_entDA = entDA;
    g_generators = generators;
    
    // Start game loop
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
    #else
    while (!WindowShouldClose()) {
        main_loop();
    }
    
    // Cleanup
    UnloadShader(g_lightingShader);
    UnloadShader(g_blureShader);
    UnloadRenderTexture(g_target);
    CloseWindow();
    #endif

    return 0;
}

