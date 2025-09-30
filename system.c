// systems.c
#include "system.h"
#include <stdio.h>

// Render system: Draws entities with position and renderable
//extern Texture2D temp;

//static Vector3 player_position;

// Helper struct for sorting entities
typedef struct EntityDistance {
	int index;
	float distanceSqr;
	} EntityDistance;


static int compareEntityDistance(const void *a, const void *b) {
	const EntityDistance *ea = (const EntityDistance*)a;
	const EntityDistance *eb = (const EntityDistance*)b;


	if (ea->distanceSqr < eb->distanceSqr) return 1;
	if (ea->distanceSqr > eb->distanceSqr) return -1;
	return 0;
	}

void render_system(World* world, EngineData* engine, Sprite_DA *sprites) {
	CompMask mask = COMP_POSITION | COMP_RENDER;
	Vector3 player_position = (Vector3) {
		world->position[0].x, 0.4f, world->position[0].y
		};

	// Temporary array for sorting
	static EntityDistance sortedEntities[MAX_ENTITIES];
	int entityCount = 0;
		for (int i = 1; i < MAX_ENTITIES; i++) {
			//if(world->visibe[(int)world->position[i].y][(int)world->position[i].x] == true)
			if ((world->masks[i] & mask) == mask) {
				const Vector3 pos = (Vector3) {
					(float)world->position[i].x, 0.4f, (float)world->position[i].y
					};
				sortedEntities[entityCount].index = i;
				sortedEntities[entityCount].distanceSqr = Vector3DistanceSqr(pos, player_position);
				entityCount++;
			}
		}


	qsort(sortedEntities, entityCount, sizeof(EntityDistance), compareEntityDistance);
	for (int j = 0; j < entityCount; j++) {
		const int i = sortedEntities[j].index;
		const float distance = sortedEntities[j].distanceSqr;
		Sprite s = sprites->items[world->renderable[i].type];
		const Position* p = &world->position[i];
		const Vector3 pos = (Vector3) {
			(float)p->x - 0.001f, 0.4f, (float)p->y - 0.001f
			};
		//DrawBillboard(engine->camera, temp, pos, s.scale, WHITE);
		//if(world->visibe[(int)p->y][(int)p->x] == true)
		{
			if(distance > engine->drawDistance){
				Color c = BLACK;
				c.a = 255;
				DrawRectangle(pos.x, pos.z, 500, 500, c);
			}
			
				

			else if(world->renderable[i].type == S_OpenDoor || world->renderable[i].type == S_ClosedDoor){
				
				DrawBillboard(engine->camera, s.texture, pos, 1.6f, WHITE);	
			}
			else if(world->renderable[i].type >= S_Sword && world->renderable[i].type < S_Plant){
				DrawBillboard(engine->camera, s.texture, pos, 0.5f, WHITE);
			}
			else if(world->renderable[i].type == S_Plant){
				DrawBillboard(engine->camera, s.texture, pos, 1.0f, WHITE);
			}
			else if(world->renderable[i].type == S_PlantBig){
				DrawBillboard(engine->camera, s.texture, pos, 2.0f, WHITE);
			}	
			else if(world->input[i].isFinishedAttack == true)	
				DrawBillboard(engine->camera, s.texture, pos,s.scale + rand_f32()/5.0f, WHITE);
			else
				DrawBillboard(engine->camera, s.texture, pos,s.scale, WHITE);		
			}
			
		}

		//Render gas
		for(int y = 0; y < world->map.h; y++){
			for(int x = 0; x < world->map.w; x++){
				if(world->gasMap[y][x].type != gasNo){
					const int sType = S_BasicGas + world->gasMap[y][x].type;
					DrawBillboard(engine->camera, sprites->items[sType].texture, (Vector3){x, 0.4, y}, 1.0, WHITE);
					
					//DrawCube((Vector3){x+engine->camera.position.x, 0.4, y+engine->camera.position.y}, 50, 50, 50, RED);
					//exit(-1);
				}
				
			
			}	
		}

	}




#define DIRECTIONS 4
static Position get_lowest_tile_dikstra(World *world, int sx, int sy) {
    Position p = {sx, sy};
    float min = 256.0f;
	calculate_diakstra_map(world, sx, sy, true);
    // 4 dir
    //const int directions = 8;
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

    for (int i = 0; i < DIRECTIONS; i++) {
        int x = sx + dirs[i][0];
        int y = sy + dirs[i][1];
        if (world->map.walling[y][x] != '#' &&
            world->map.walling[y][x] != '+' &&
            min > world->dikstra[y][x] && world->dikstra[y][x] != 255.0f) {
            min = world->dikstra[y][x];
            p.x = x;
            p.y = y;
        }
    }

    return p;
}
static Position get_lowest_tile_dikstra_player(World *world, int sx, int sy, int px, int py) {
    Position p = {sx, sy};
    float min = 256.0f;
	calculate_diakstra_map(world, px, py, true);
    // 4 dir
    //const int directions = 8;
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

    for (int i = 0; i < DIRECTIONS; i++) {
        int x = sx + dirs[i][0];
        int y = sy + dirs[i][1];
        if (world->map.walling[y][x] != '#' &&
            world->map.walling[y][x] != '+' &&
            min > world->dikstra[y][x] && world->dikstra[y][x] != 255.0f) {
            min = world->dikstra[y][x];
            p.x = x;
            p.y = y;
        }
    }

    return p;
}



static Position get_highest_tile_dikstra(World *world, int sx, int sy) {
    Position p = {sx, sy};
    float max = -1000000.0f;
	calculate_diakstra_map(world, sx, sy, true);
   //const int directions = 8;
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

    for (int i = 0; i < DIRECTIONS; i++) {
        int x = sx + dirs[i][0];
        int y = sy + dirs[i][1];

        if (world->map.walling[y][x] != '#' &&
            (x != world->position[0].x || y != world->position[0].y) &&
            max < world->dikstra[y][x]) {
            max = world->dikstra[y][x];
            p.x = x;
            p.y = y;
        }
    }

    return p;
}
static Position get_random_tile_dikstra(World *world, int sx, int sy) {
    calculate_diakstra_map(world, sx, sy, true);
	//const int directions = 8;
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
    int count = 0;
    while (count < 10) {
        int i = rand() % DIRECTIONS;
        int x = sx + dirs[i][0];
        int y = sy + dirs[i][1];

        if (world->dikstra[y][x] != 255 &&
            world->map.walling[y][x] != '#' &&
            world->map.walling[y][x] != '+') 
        {
            return (Position){x, y};
        }
        count++;
    }

    return (Position){sx, sy}; // fallback
}






//Cast ray from player for now
static void cast_ray(World* world, EngineData* engine, float x, float y, int ent) {

	float ox,oy;
	ox = world->position[0].x;
	oy = world->position[0].y;

	for(int i = 0; i < 1000; i++) {
		int ix = ((int)ox)%(world->map.w  - 1);
		int iy = ((int)oy)%(world->map.h  - 1);
		if(ix < 0){
			ix = 0;
		}
		if(iy < 0){
			iy = 0;
		}
		world->visibe[iy][ix] = true;
		if(ent == 0)
			world->isExpMap[iy][ix] = 1;
	
		if(world->map.walling[iy][ix] == '#' || world->map.walling[iy][ix] == '+') {
			return;
			}
		else if((rand_f32() < CHANCE_NOSEE) && world->map.walling[iy][ix] == '"'){
			return;
		}	
		ox+=x;
		oy+=y;
		};
		DROP(engine);
	}
#define CLEAR_VISON_FIELD(ptr) memset(ptr, false, MAP_WIDTH * MAP_HEIGHT * sizeof(int)) 	
static void field_of_vison(World* world, EngineData* engine, int ent) {
	float x,y;
	CLEAR_VISON_FIELD(&world->visibe);
	int xE = ((int)world->position[ent].x) % (MAP_WIDTH - 1);
	int yE = ((int)world->position[ent].y) % (MAP_HEIGHT - 1);
	if(xE < 0)
		xE = 0;
	if(yE < 0)
		yE = 0;	
	//world->map.walling[yE][xE] = '#';
	for(int i = 0; i < 360; i++) {
		x = cos((float)i*0.01745f); //to rad
		y = sin((float)i*0.01745f);
		cast_ray(world, engine, x, y, ent);
		};
	//world->map.walling[yE][xE] = 0;		
	//world->visibe[yE][xE] = false;

	}

static uint8_t is_player_visible_by_monster(World* world, float x, float y){
	
	if(world->visibe[(int)y][(int)x] == true){
		return 1;
	}
	return 0;
}	

/*
    AI systems
        If damage > morale
           if can-run-away-from-player
              run-away-from-player
           else if can-attack-player
              attack-player
           else stand-still
        else if too-far-from-player
             AND can-attack-player
             AND can-move-toward-player
             if  random < charge-probability
                 move-toward-player     
             else attack-player
        else if too-close-to-character
             AND can-attack-player
             AND can-move-away-from-player
             if random < retreat-probability
                move-away-from-player
             else attack-player
        else if can-attack-player
             attack-player
        else if too-far-from-player 
             AND can-move-toward-player
             move-toward-player
        else if too-close-to-player
             AND can-move-away-from-player
             move-away-from-player
        else stand-still

*/



static void set_memory_wandering(World* world, int ent){
	int x = 0;
	int y = 0;
	int is = false;
	while(!is){
		x = rand()%(world->map.w - 1);
		y = rand()%(world->map.h - 1);
		float distance = (x - world->position[ent].x)*(x - world->position[ent].x) 
		+ (y - world->position[ent].y) * (y - world->position[ent].y);
		//TBD other 
		if(world->map.walling[y][x] != '#' && distance >= 25){
			world->state[ent].lastSeenX = x;
			world->state[ent].lastSeenY = y;
			world->state[ent].memoryTimer = 20;
			is = true;
			}
		}
}




void monster_change_state_system(World* world, EngineData *engine) {
    CompMask mask = COMP_POSITION | COMP_MONSTER | COMP_STATE | COMP_STATS;

    // Player position reference
    const int playerX = world->position[0].x;
    const int playerY = world->position[0].y;
	field_of_vison(world, engine, 0);	

    for (int i = 1; i < MAX_ENTITIES; i++) {
        if ((world->masks[i] & mask) != mask || world->input[i].isMoving) 
            continue;
		//field_of_vison(world, engine, i);
        

        bool isVisible = is_player_visible_by_monster(world, world->position[i].x, world->position[i].y);
        int damageTaken = world->health[i].max - world->health[i].current;



        // --- FEAR AND MORALE SYSTEM ---
        world->state[i].fear += damageTaken * 0.01f; 
        if (world->state[i].fear < 0) world->state[i].fear = 0;

        // --- MEMORY SYSTEM ---
        if (isVisible) {
            world->state[i].lastSeenX = playerX;
            world->state[i].lastSeenY = playerY;
            world->state[i].memoryTimer = 5; // lasts 5 turns
        } else if (world->state[i].memoryTimer > 0) {
            world->state[i].memoryTimer--;
        }

        // --- STATE DECISION TREE ---

        // Very low health logic
        if (world->health[i].current == 0.1f*world->health[i].max) {
            if (rand_f32() < world->state[i].chancesR) {
                world->state[i].current = STATE_RUNING;
            } else if (rand_f32() < 0.1f) { // CHANCE_INCREMENT_HEALTH
                world->health[i].current++;
                world->state[i].current = STATE_HUNTING;
            } else {
                world->state[i].current = STATE_BESERK;
            }
            continue;
        }

        // Stamina check
        //if (world->stamina[i].current <= 0) {
        //    world->state[i].current = STATE_RESTING;
        //    continue;
        //}

        // Fear-based running
        if (world->state[i].fear > world->stats[i].morale) {
            world->state[i].current = STATE_RUNING;
            continue;
        }

        // Player is wounded - aggressive response
        if (world->health[0].current <= (int)(0.3f * world->health[0].max)) {
            world->state[i].current = STATE_HUNTING;
            continue;
        }

        bool hasMemory = (world->state[i].memoryTimer > 0);
        
 
 
        // If monster can see player or remembers last seen pos and not hunting
        if ((isVisible || hasMemory) && world->state[i].current != STATE_HUNTING) {
            // Perception vs stealth check
            int perceptionMonster = rand() % 10 + world->stats[i].perception;
            int stealthPlayer =  rand() % 10 + world->stats[0].stealth;
            

            if (engine->isTorchEqu) {
                stealthPlayer -= 10;    // torch makes player easier to see
            }

            if (perceptionMonster > stealthPlayer) {
                float chanceH = rand_f32();
                float chanceR = rand_f32();

                if (world->state[i].chancesH > chanceH) {
                    world->state[i].current = STATE_HUNTING;
                } else if (world->state[i].chancesR > chanceR) {
                    world->state[i].current = STATE_RUNING;
                } else {
                    world->state[i].current = STATE_SEARCHING;
                }
            } else {
                // Wander when player is stealthy
                if (rand_f32() < world->state[i].chancesW) {
					set_memory_wandering(world, i);
                    world->state[i].current = STATE_WANDERING;
                } else {
                    world->state[i].current = STATE_RESTING;
                }
            }
        } 
        else {
            // No player info - wander or rest
            if (world->state[i].current == STATE_WANDERING) {
                if (isVisible && rand_f32() < world->state[i].chancesH) {
                    world->state[i].current = STATE_HUNTING;
                } else if (rand_f32() < world->state[i].chancesR) {
                    world->state[i].current = STATE_RESTING;
                }
            } 
            else if (world->state[i].current == STATE_HUNTING && 
                     rand_f32() < world->state[i].chancesR) {
                world->state[i].current = STATE_RESTING;
                // Optional: add message "You stop hearing noises"
            }
            else if (world->state[i].current == STATE_RESTING && 
                     rand_f32() < world->state[i].chancesW) {
				set_memory_wandering(world, i);		
                world->state[i].current = STATE_WANDERING;
            }
            else if (rand_f32() < world->state[i].chancesW) {
                // Set random wander target
                set_memory_wandering(world, i);
                world->state[i].current = STATE_SEARCHING;
            }
            else {
                world->state[i].current = STATE_RESTING;
            }
        }

        // --- GROUP ALERTING ---
        if (world->state[i].current == STATE_HUNTING) {
            for (int j = 1; j < MAX_ENTITIES; j++) {
                if (i == j) continue;
                if ((world->masks[j] & mask) == mask) {
                    int dx = world->position[i].x - world->position[j].x;
                    int dy = world->position[i].y - world->position[j].y;
                    if (dx*dx + dy*dy < 25) { // within 5 tiles
                        if (world->state[j].current != STATE_HUNTING) {
                            world->state[j].current = STATE_ALERTED;
                            world->state[j].memoryTimer = 3 + rand()%10;
                            world->state[j].lastSeenX = playerX;
                            world->state[j].lastSeenY = playerY;
                        }
                    }
                }
            }
        }
    }
}


//SMART STUFFS
void monster_state_system(World* world, EngineData *engine) {
	DROP(engine)

	CompMask mask = COMP_POSITION | COMP_MONSTER;
	//calculate_diakstra_map(world, world->position[0].x, world->position[0].y, 1);
	for (int i = 1; i < MAX_ENTITIES; i++) {
		if ((world->masks[i] & mask) == mask && world->input[i].isMoving == false ) {

			// Add movement logic here
			//CHECK FOR TILE
			//
		
			//Calculate distances
			float distance = Vector2Distance(world->position[i], world->position[0]);
			int  isAtt = false;
			if(distance <= 1.41f && distance >= 1.0f && (world->state[i].current != STATE_RUNING)) {
				world->input[i].isMoving = ATTACK;
				isAtt = true;
				//world->input[i].isFinishedAttack = false;
				}
			//Rang	e
			else if(distance <= 5.0f && distance >= 3.0f && (world->state[i].current != STATE_RUNING) 
			&& world->visibe[(int)world->position[i].y][(int)world->position[i].x] && rand_f32() < world->state[i].chancesRe){
				//Check if bow equipted
				int rID = is_item_of_type_equ(&world->inventory[i], EQUIPTED_RANGE);
				int mID = is_item_of_type_equ(&world->inventory[i], EQUIPTED_MUTITION);
				//MESSAGE_F("Range attack %s", world->name[i]);

				
				if(((rID != -1) && (mID != -1))){
					//exit(-1);
					if(world->inventory[i].items[mID].fire == world->inventory[i].items[rID].type){

					world->input[i].isMoving = ATTACK_RANGE;
					isAtt = true;
					//MESSAGE_F("Range %d", i);
					//exit(-1);
				}
			}}	
			if(!isAtt) {
				Position p;
				
				if(world->state[i].current == STATE_WANDERING){
				
						p = get_lowest_tile_dikstra_player(world, world->position[i].x, world->position[i].y, 
						world->state[i].lastSeenX, world->state[i].lastSeenY );
					
					//p = get_random_tile_dikstra(world, world->position[i].x, world->position[i].y);
					
				}
				else if(world->state[i].current == STATE_HUNTING){
					
					p = get_lowest_tile_dikstra(world, world->position[i].x, world->position[i].y);
				}
				else if(world->state[i].current == STATE_RESTING){
					
					p = world->position[i];
				}
				else if(world->state[i].current == STATE_ALERTED || world->state[i].current == STATE_SEARCHING){
					p = get_lowest_tile_dikstra_player(world, world->position[i].x, world->position[i].y, 
							world->state[i].lastSeenX, world->state[i].lastSeenY );
				}
				else if(world->state[i].current == STATE_SEARCHING){
					p = get_lowest_tile_dikstra_player(world, world->position[i].x, world->position[i].y, 
							world->state[i].lastSeenX, world->state[i].lastSeenY );			
				}
				//else if(world->state[i].current == STATE_)	
				else{
					p = get_highest_tile_dikstra(world, world->position[i].x, world->position[i].y);
				}
				
				//Change door for op
				const int xD = (int)p.x;
				const int yD = (int)p.y; 
				if(world->map.walling[yD][xD] == '+'){
				for(int i = 1; i < MAX_ENTITIES; i++){
				if((world->position[i].x == xD) &&  (world->position[i].y == yD)){
				//exit(-1);
					world->renderable[i].type = S_OpenDoor;
					//MESSAGE("eNT OP");
				}
		}
				}
				world->input[i].nextPosition = p;
				world->input[i].isMoving = MOVE;
				world->input[i].moveLerpAlpha = 0.0f;
				world->dikstra[(int)p.y][(int)p.x] = 255.0f;
				world->dikstra[(int)world->position[i].y][(int)world->position[i].x] = 255;
				}

			//printf("Monster %d thinks(%d %d)...\n", i, world->position[i].x, world->position[i].y);
			}
		}

	}

// Health system: Checks for dead entities
void health_system(World* world, EngineData *engine) {
	CompMask mask = COMP_HEALTH | COMP_MONSTER;

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if(i == 0){
			if(world->health[0].current <= 0){
				exit(-1);
			}
		}
		else if (((world->masks[i] & mask) == mask) && world->health[i].current <= 0) {
			MESSAGE_F("Entity %d died!\n", i);
			inventory_to_map(world, i);
			destroy_entity(world, i);
			}
		}
	}

//Hiden doors and other stufs
void player_door_system(World* world, EngineData *engine){
	int x = ((int)engine->nextPosition.x%world->map.w);
	int y = ((int)engine->nextPosition.z%world->map.h);
	
	if(world->map.walling[y][x] == '+'){
		MESSAGE("You open a door\n");
		world->map.walling[y][x] = '-';
		for(int i = 1; i < MAX_ENTITIES; i++){
			if((world->position[i].x == engine->nextPosition.x) &&  (world->position[i].y == engine->nextPosition.z)){
				//exit(-1);
				world->renderable[i].type = S_OpenDoor;
			}
		}
	}
	//All other open the door

}	

int pick_item_from_ground(World* world, EngineData *engine){
	
	Position player = world->position[0];
	
	for(int i = 0; i < world->items.count; i++){
		
		Item item = world->items.items[i];
		if(player.x == item.pos.x && player.y == item.pos.y){
			item.pos.x = 0;
			item.pos.y = 0;
			da_append(&world->inventory[0], item);
			da_remove_unordered(&world->items, i);
			//Search ent
			for(int j = 1; j < MAX_ENTITIES; j++){
				if(player.x == world->position[j].x && player.y == world->position[j].y){
					destroy_entity(world, j);
					break;
				}
			}
			return true;
			break;
		}		
	}
	return false;
	DROP(engine);
}

///*Tbd type
static void spawn_projectile(World* world, int ent, EngineData *engine){
	int projectile = create_entity(world);
	add_tag(world, projectile, COMP_PROJEC);
	//add_tag(world, projectile, COMP_MONSTER);
	add_component(world, projectile, COMP_POSITION, &(Position) {
			world->position[ent].x + 0.1f, world->position[ent].y  + 0.1f
			});
	add_component(world, projectile, COMP_RENDER, &(Renderable){
		(S_Arrow)
	});
	//add_component(world, projectile, COMP_INPUT, &(Input){0});	
	add_component(world, projectile, COMP_STATS, &(Stats){
		world->stats[ent].str, world->stats[ent].dex, world->stats[ent].inte, world->stats[ent].cons, world->stats[ent].morale,
		world->stats[ent].perception, world->stats[ent].stealth, world->stats[ent].dmgMax, world->stats[ent].dmgMin
	});
	//Player
	if(ent == 0){
		const int dx  = (int)roundf(sinf(engine->playerYaw));
		const int dz  = (int)roundf(cosf(engine->playerYaw));
		float x = world->position[0].x + 10*dx;
		float y = world->position[0].y + 10*dz;
		//MESSAGE_F("(%f %f) (%f %f)", x, world->position[0].x,  y, world->position[0].y);
		world->input[projectile].nextPosition = (Position){x, y};
		world->input[projectile].isMoving = MOVE;
		world->input[projectile].isFinishedAttack = true;
		world->input[projectile].entProjectile = ent;
		engine->isEntMoving = true;
		//exit(-1);
	}
	else{
		const float x = world->position[0].x+0.001f;
		const float y = world->position[0].y+0.001;
		//MESSAGE_F("(%f %f) (%f %f)", x, world->position[0].x,  y, world->position[0].y);
		world->input[projectile].nextPosition = (Position){x, y};
		world->input[projectile].isMoving = MOVE;
		world->input[projectile].isFinishedAttack = true;
		world->input[projectile].entProjectile = ent;
		engine->isEntMoving = true;
	}	
	DROP(engine);			
}
//*/

void projectile_system(World* world, EngineData *engine){
	CompMask mask = COMP_POSITION | COMP_STATS | COMP_PROJEC | COMP_STATS;
	
	for(int i = 0; i < MAX_ENTITIES; i++){
		if((world->masks[i] & mask) == mask){
			Position projectile = world->position[i];
			const int x = (int)projectile.x;
			const int y = (int)projectile.y;
			if(world->map.walling[y][x] == '#' || world->map.walling[y][x] == '+'){
				//world->input[i].isFinishedAttack = true;
				destroy_entity(world, i);
				continue;
				//exit(-1);
			}
			else if(world->input[i].isMoving == NOT){
			
				destroy_entity(world, i);
				//exit(-1);
			}
			if(world->input[i].entProjectile != 0){
				float distance = Vector2Distance(world->position[i], world->position[0]);
				//MESSAGE_F("Distance %f", distance);
				if(distance < 2.5f){
						//MESSAGE_F("Distance %f", distance);
						//destroy_entity(world, i);
						int dmg = attack_dmg_callculations(world,  world->input[i].entProjectile, 0);
						world->health[0].current-=dmg;
						//MESSAGE_F("PLAYER ATTACK health %d", world->health[0].current);
						MESSAGE_F("You are atacked by %s", world->name[world->input[i].entProjectile])
						//MESSAGE_F("Player health %d", world->health[0].current);
						if(dmg == 0){
							MESSAGE("You sustained no dmg");
						}
						else{
							MESSAGE_F("You are hit for %d", dmg);
						}
						
						destroy_entity(world, i);
						//exit(-1);
						break;
						//exit(-1);
					}
			}
			else{
				for(int j = 0; j < MAX_ENTITIES; j++){
				if(j != i && ((world->masks[j] & COMP_MONSTER))){
					float distance = Vector2Distance(world->position[i], world->position[j]);
					
					if(distance < 1.1f && world->input[i].entProjectile != j){
						MESSAGE_F("Distance %f", distance);
						//destroy_entity(world, i);
						int dmg = attack_dmg_callculations(world,  world->input[i].entProjectile, j);
						world->health[j].current-=dmg;
						MESSAGE_F("PLAYER ATTACK health %d", world->health[j].current);
						destroy_entity(world, i);
						//exit(-1);
						break;
						//exit(-1);
					}
					
				}
			}
			
				 
			/**/
			}	
		}
	}
	DROP(engine);
}



//Shoud have just position to move
void input_system(World* world, EngineData *engine) {
	//CompMask mask = COMP_INPUT;
	//Input curent = world->input[0];
	//DROP(world);
	if (!engine->isMoving) {
		engine->nextPosition = engine->camera.position;

		if (IsKeyPressed(KEY_Q)) {
			engine->targetYaw -= PI/2.0f;
			engine->isMoving = true;
			engine->moveLerpAlpha = 0.0f;
			engine->isRotation = true;

			}

		if (IsKeyPressed(KEY_E)) {
			engine->targetYaw += PI/2.0f;
			engine->isMoving = true;
			engine->moveLerpAlpha = 0.0f;
			engine->isRotation = true;
			}
		if(IsKeyPressed(KEY_SPACE)){
			engine->isEntMoving = true;
			engine->isMoving = true;
			engine->isGasRun = true;
		}
		if(IsKeyPressed(KEY_A)){
			int rID = is_item_of_type_equ(&world->inventory[0], EQUIPTED_RANGE);
			int mID = is_item_of_type_equ(&world->inventory[0], EQUIPTED_MUTITION);
			if((rID != -1) || ((mID == -1) && (world->inventory[0].items[mID].fire == world->inventory[0].items[rID].type))){
				if(world->inventory[0].items[mID].value > 0){
					world->inventory[0].items[mID].value--;
					if(world->inventory[0].items[mID].value == 0){
						da_remove_unordered(&world->inventory[0], mID);
					}
					spawn_projectile(world, 0, engine);
					engine->isMoving = true;
					engine->isEntMoving = true;
					
				}
				else{
					MESSAGE("No arrows");	
				}
				
			}
			else{
				MESSAGE("No range");
			}

			
		}
		
		if(IsKeyPressed(KEY_P)){
			//Tbd list
			engine->isRenderPickup = true;
			engine->tempItemList.count = 0;
			setup_item_system(world, engine);
			/*int is = pick_item_from_ground(world, engine);
			if(is){
				MESSAGE("Picked");
			}
			else{
				MESSAGE("No iteme");
			}*/

		}
		if(IsKeyPressed(KEY_I)){
			engine->isRenderInventory = (engine->isRenderInventory) ? 0 : 1;
			engine->whatItem = 0;
		}

		if(IsKeyPressed(KEY_H)){
			engine->isRenderStats = (engine->isRenderStats) ? 0 : 1;
		}

		if (IsKeyDown(KEY_W)) {
			engine->isRotation = false;
			engine->isGasRun = true;
			int dx = (int)roundf(sinf(engine->playerYaw));
			int dz = (int)roundf(cosf(engine->playerYaw));
			engine->nextPosition.x += dx;
			engine->nextPosition.z += dz;
			const int x = (int)engine->nextPosition.x;
			const int y = (int)engine->nextPosition.z;
			//if(world->map.walling[y][x] == '~'){
			//	engine->nextPosition.y = 0.1f;
			//}
			//else{
			//	engine->nextPosition.y = 0.6f;
			//}
			//calculate_diakstra_map(world, world->position[0].x, world, world->position[0].y);
			calculate_diakstra_map(world, world->position[0].x, world->position[0].y, 1);
			if(world->dikstra[y][x] >= 255 ) {
				//MESSAGE("aTTCA");
				
				int whatMonster = is_monster_in_next_postition(world,engine->nextPosition.x, engine->nextPosition.z); 
				if(whatMonster){
					int dmg = attack_dmg_callculations(world, 0, whatMonster);
					world->health[whatMonster].current-=dmg;
					MESSAGE_F("You atacked %s", world->name[whatMonster])
				//MESSAGE_F("Player health %d", world->health[0].current);
					if(dmg == 0){
						MESSAGE("It sustained no dmg");
					}
					else{
						MESSAGE_F("You hit it for %d", dmg);
					}
					
				}
					
				engine->nextPosition.x -= dx;
				engine->nextPosition.z -= dz;
				
				}
				
			engine->isMoving = true;
			engine->isEntMoving = true;
			engine->moveLerpAlpha = 0.0f;
				
				
		
			
			//Tbd to ENGINE
			}

		if (IsKeyPressed(KEY_S)) {
			engine->isGasRun = true;
			int dx = (int)roundf(sinf(engine->playerYaw));
			int dz = (int)roundf(cosf(engine->playerYaw));
			engine->nextPosition.x -= dx;
			engine->nextPosition.z -= dz;
			const int x = (int)engine->nextPosition.x;
			const int y = (int)engine->nextPosition.z;
			if(world->map.walling[y][x] == '~'){
				engine->nextPosition.y = 0.1f;
			}
			else{
				engine->nextPosition.y = 0.6f;
			}
			if(world->dikstra[y][x] >= 255 ) {
				int whatMonster = is_monster_in_next_postition(world,engine->nextPosition.x, engine->nextPosition.z); 
				if(whatMonster){
					int dmg = attack_dmg_callculations(world, 0, whatMonster);
					world->health[whatMonster].current-=dmg;
					MESSAGE_F("PLAYER ATTACK health %d", world->health[whatMonster].current);
				}
					
				engine->nextPosition.x += dx;
				engine->nextPosition.z += dz;
				}
				
			engine->isMoving = true;
			engine->isEntMoving = true;
			engine->moveLerpAlpha = 0.0f;
			///engine->isGasRun = true;
			}
			
		if(IsKeyPressed(KEY_M)){
			engine->isRenderMap = true;
		}	

		}

	}



void update_player_position_system(World* world, EngineData* engine) {

	float MOVE_SPEED;
	if(engine->isRotation)
		MOVE_SPEED = 2.0f;
	else 
		MOVE_SPEED = 5.0f;
	const float TILE_SIZE  = 1.0f;

	DROP(world);
	if (engine->isMoving) {

		engine->moveLerpAlpha += GetFrameTime() * MOVE_SPEED;
		if (engine->moveLerpAlpha >= 1.0f) {
			engine->moveLerpAlpha = 1.0f;
			engine->isMoving = false;
			//engine->isEntMoving = true;
			//exit(-1)
			}
			

		}

	engine->playerYaw = Lerp(engine->playerYaw, engine->targetYaw, engine->moveLerpAlpha);


	Vector3 targetVisualPos = { engine->nextPosition.x * TILE_SIZE, 0.0f, engine->nextPosition.z * TILE_SIZE };
	engine->camera.position = Vector3Lerp(engine->camera.position, targetVisualPos, engine->moveLerpAlpha);


	engine->camera.position.x = engine->nextPosition.x;
	engine->camera.position.y = engine->nextPosition.y;


	engine->camera.target.x = engine->camera.position.x + sinf(engine->playerYaw);
	engine->camera.target.z = engine->camera.position.z + cosf(engine->playerYaw);
	engine->camera.target.y = engine->camera.position.y; // Keep the camera level
	//UPDATE PLAYER pos
	world->position[0].x = engine->camera.position.x;
	world->position[0].y = engine->camera.position.z;
	}



void update_entity_position_system(World* world, EngineData* engine) {
	const float MOVE_SPEED = 2.0f;
	const float MOVE_SPEED_PROJECTILE = 0.1f;
	const float TILE_SIZE  = 1.0f;

	CompMask mask = COMP_POSITION;
	for (int i = 1; i < MAX_ENTITIES; i++) {
		if ((world->masks[i] & mask) == mask) {
			if(world->input[i].isMoving == MOVE ) {
				//pROJECILE
				if(world->masks[i] & COMP_PROJEC){
					world->input[i].moveLerpAlpha += GetFrameTime() * MOVE_SPEED_PROJECTILE;	
				}
				else{
					world->input[i].moveLerpAlpha += GetFrameTime() * MOVE_SPEED;
				}
				
				if (world->input[i].moveLerpAlpha >= 1.0f) {
					world->input[i].moveLerpAlpha = 1.0f;
					world->input[i].isMoving = NOT;
					//world->dikstra

					//LOG("Entyty moved to (%d %d) from %d %d", world->input[i].nextPosition.x, world->input[i].nextPosition.y,
					//world->position[i].x, world->position[i].y);
					engine->isEntMoving = false;
					//exit(-1);
					}
				Vector2 targetVisualPos = { world->input[i].nextPosition.x * TILE_SIZE, world->input[i].nextPosition.y * TILE_SIZE };
				const Vector2 v1 = {world->position[i].x + 0.0001f, world->position[i].y+ 0.0001f};
				const Vector2 v2 = Vector2Lerp(v1, targetVisualPos,world->input[i].moveLerpAlpha);
				world->position[i].x = (float)v2.x;
				world->position[i].y = (float)v2.y;
				
				//LOG("NEsto\n")
				}
			}

		}
	}

	void monster_attack_system(World* world, EngineData* engine){
		for (int i = 1; i < MAX_ENTITIES; i++) {
			if(world->input[i].isMoving == ATTACK && world->input[i].isFinishedAttack == false){
				int dmg = attack_dmg_callculations(world, i, 0);
				//MESSAGE("Monster attack");
				MESSAGE_F("You are atacked by %s", world->name[i])
				//MESSAGE_F("Player health %d", world->health[0].current);
				if(dmg == 0){
					MESSAGE("You sustained no dmg");
				}
				else{
					MESSAGE_F("You are hit for %d", dmg);
				}
				world->input[i].isMoving = NOT;
				world->input[i].isFinishedAttack = true;
				world->health[0].current-=dmg;
				world->stats[i].perception+=5;
			}
			else if(world->input[i].isMoving == ATTACK_RANGE && world->input[i].isFinishedAttack == false){
				//world->input[i].isMoving = NOT;
				world->input[i].isFinishedAttack = true;
			
				int rID = is_item_of_type_equ(&world->inventory[i], EQUIPTED_RANGE);
				int mID = is_item_of_type_equ(&world->inventory[i], EQUIPTED_MUTITION);
				if(((rID != -1) || (mID == -1)) && (world->inventory[i].items[mID].fire == world->inventory[i].items[rID].type)){
					if(world->inventory[i].items[mID].value > 0){
						world->inventory[i].items[mID].value--;
					if(world->inventory[i].items[mID].value == 0){
						da_remove_unordered(&world->inventory[i], mID);
					}
					spawn_projectile(world, i, engine);
					//MESSAGE("pROJECTILE");
				} //else MESSAGE("Test");
			}
			}
				//exit(-1);
			}
		}	
	


	
void reset_attack_input(World* world, EngineData* engine){ 
	DROP(engine);
	for(int i = 1; i < MAX_ENTITIES; i++){
		world->input[i].isFinishedAttack = false;
		world->input[i].isMoving = NOT;
		world->input[i].moveLerpAlpha = 0.0f;
	}
}
//static int isTorchEqu	
//For player for now later for ent
void lighting_system(World* world, EngineData* engine){
	//int is  = false;
	for(int i = 0; i < world->inventory[0].count; i++){
		const Item it = world->inventory[0].items[i];
		if((it.type == Tourch) && it.isEqu == true){
			world->inventory[0].items[i].value--;
			if(world->inventory[0].items[i].value == 0){
				da_remove_unordered(&world->inventory[0], i);
				world->ambientStrenght = world->saveAmbientStrenght;
				//engine->drawDistance = 50 - 1.0f / world->ambientStrenght;
				//if(engine->drawDistance < 10){
				//		engine->drawDistance = 10;
				//}
				engine->isTorchEqu = false;
				break;
			}
			engine->drawDistance = 200;
			world->ambientStrenght = world->saveAmbientStrenght + 0.2f;
			engine->isTorchEqu = true;
			//exit(-1);
			break;			

		}
	}
	if(!engine->isTorchEqu){
		engine->drawDistance = 50 - 1.0f / (world->ambientStrenght + 0.0000001f);
		world->ambientStrenght = world->saveAmbientStrenght;
		if(engine->drawDistance < 10){
			//exit(-1);

			engine->drawDistance = 10;
			engine->isTorchEqu = false;
		}
	}
}

//This magic do a adding stuffs depending on source and then thru map difuse motion of gas so i need to store some sep da or map 
void gas_system(World *world, EngineData *engine){
	CompMask mask = COMP_POSITION | COMP_GAS;
	engine->isGasRun = false;
	static int counter = 0;
	MESSAGE_F("Difusion %d", counter++);
	int dirs[8][2] = {
        { 0, -1}, // Up
        { 0,  1}, // Down
        {-1,  0}, // Left
        { 1,  0}, // Right
        {-1, -1}, // Up-left
        {-1,  1}, // Down-left
        { 1, -1}, // Up-right
        { 1,  1}  // Down-right
    };
	
	for(int i = 0; i < MAX_ENTITIES; i++){
		if((world->masks[i] & mask) == mask){
			const Position p = world->position[i];
			const int x = ((int)p.x % (world->map.w - 1));
			const int y = ((int)p.y % (world->map.h - 1));
			for(int j = 0; j < 8; j++){
				const int mapX = (x + dirs[j][0])%(world->map.w - 1);
				const int mapY = (y + dirs[j][1])%(world->map.h - 1); 
				if(world->map.walling[mapY][mapX] != '#'){
					if(world->gasMap[mapY][mapX].type == gasNo)
					world->gasMap[mapY][mapX] = (Gas)world->gas[i];
					else if(world->gasMap[mapY][mapX].type == world->gas[i].type){
						world->gasMap[mapY][mapX].timeToStay += world->gas[i].timeToStay; 
					}
				}
			}

		}
	}
	
	//On map stuffs 
	for(int y = 2; y < world->map.h - 2; y++){
		for(int x = 2; x < world->map.w - 1; x++){
			if(world->gasMap[y][x].type != gasNo){
				int i = rand()%8;
				//const int j = rand()%2;
				//Halve the value
				if(world->gasMap[y][x].timeToStay <= 0){
					world->gasMap[y][x].type = gasNo;
								
				}
				else{
					const int mapX = (x + dirs[i][0])%(world->map.w - 1);
					const int mapY = (y + dirs[i][1])%(world->map.h - 1);
					
					world->gasMap[y][x].timeToStay /=2;
					if(world->map.walling[mapY][mapX] != '#'){
						world->gasMap[mapY][mapX].color = world->gasMap[y][x].color;
						world->gasMap[mapY][mapX].isActive = world->gasMap[y][x].isActive;
						world->gasMap[mapY][mapX].timeToStay+= world->gasMap[y][x].timeToStay;
						world->gasMap[mapY][mapX].type = world->gasMap[y][x].type;
					}
					

				}

			}
		}
	}	
//exit(-1);

}