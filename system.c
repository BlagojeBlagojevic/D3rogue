// systems.c
#include "system.h"
#include <stdio.h>

 #ifndef __EMSCRIPTEN__
#define STB_PERLIN_IMPLEMENTATION
#endif
#include "stb_perlin.h"


// Render system: Draws entities with position and renderable
//extern Texture2D temp;

//static Vector3 player_position;

// Helper struct for sorting entities
typedef struct EntityDistance {
	int index;
	int stableId;
	float distanceSqr;
	
	} EntityDistance;

static int compareEntityDistance(const void *a, const void *b) {
    const EntityDistance *ea = (const EntityDistance*)a;
    const EntityDistance *eb = (const EntityDistance*)b;

    // Direct comparison without epsilon
    if (ea->distanceSqr < eb->distanceSqr) return 1;
    if (ea->distanceSqr > eb->distanceSqr) return -1;
    
    // Final tie-breaker using the stable ID
    return (ea->stableId - eb->stableId);
}

static float perlin_noise(float x, float y, float z) {
    // You can use stb_perlin.h or implement your own
    // For now, let's assume you have a function that returns noise between -1 and 1
    return stb_perlin_noise3(x, y, z, 0, 0, 0);
}

static void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    // Set desired texture to be enabled while drawing following vertex data
    rlSetTexture(texture.id);

    // Vertex data transformation can be defined with the commented lines,
    // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
    //rlPushMatrix();
        // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
        //rlTranslatef(2.0f, 0.0f, 0.0f);
        //rlRotatef(45, 0, 1, 0);
        //rlScalef(2.0f, 2.0f, 2.0f);

        rlBegin(RL_QUADS);
            rlColor4ub(color.r, color.g, color.b, color.a);
            // Front Face
            rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
            // Back Face
            rlNormal3f(0.0f, 0.0f, - 1.0f);     // Normal Pointing Away From Viewer
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
            // Top Face
            rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Bottom Left Of The Texture and Quad
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Bottom Right Of The Texture and Quad
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
            // Bottom Face
            rlNormal3f(0.0f, - 1.0f, 0.0f);     // Normal Pointing Down
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Top Right Of The Texture and Quad
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Top Left Of The Texture and Quad
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
            // Right face
            rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
            // Left Face
            rlNormal3f( - 1.0f, 0.0f, 0.0f);    // Normal Pointing Left
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
        rlEnd();
    //rlPopMatrix();

    rlSetTexture(0);
}


void stable_sort_entities(EntityDistance *array, int count) {
    for (int i = 1; i < count; i++) {
        EntityDistance key = array[i];
        int j = i - 1;
        
        // Move elements that should come after key
        while (j >= 0 && 
               (array[j].distanceSqr < key.distanceSqr || 
               (array[j].distanceSqr == key.distanceSqr && array[j].index > key.index))) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}




void render_system(World* world, EngineData* engine, Sprite_DA *sprites) {

	{
		float time = GetTime();
			
		BeginBlendMode(BLEND_ALPHA); // enable transparency blending

		for (int y = 0; y < world->map.h; y++) {
			for (int x = 0; x < world->map.w; x++) {
				if (world->map.walling[y][x] == Tile_Water) {
					const Vector3 pos = { (float)x, 0.0f, (float)y};	
					float dist = Vector3DistanceSqr((Vector3)pos, (Vector3){world->position[0].x, 0.4, world->position[0].y});
					if(dist < engine->drawDistance)
						DrawCubeTexture(engine->water, pos, 1.0, 0.0, 1.0, BLUE);
					}
				else if (world->map.walling[y][x] == Tile_Dwater) {
					const Vector3 pos = { (float)x, 0.0f, (float)y};	
					float dist = Vector3DistanceSqr((Vector3)pos, (Vector3){world->position[0].x, 0.4, world->position[0].y});
					if(dist < engine->drawDistance)
						DrawCubeTexture(engine->water, pos, 1.0, 0.0, 1.0, DARKBLUE);
					}	
				else if(world->map.walling[y][x] == Tile_Lava){
					const Vector3 pos = { (float)x, 0.0f, (float)y};	
					float dist = Vector3DistanceSqr((Vector3)pos, (Vector3){world->position[0].x, 0.4, world->position[0].y});
					if(dist < engine->drawDistance)
						DrawCubeTexture(engine->fire, pos, 1.0, 0.0, 1.0, ORANGE);					
				}
				else if(world->map.walling[y][x] == Tile_Fire){
					const Vector3 pos = { (float)x, 0.0f, (float)y};	
					float dist = Vector3DistanceSqr((Vector3)pos, (Vector3){world->position[0].x, 0.4, world->position[0].y});
					if(dist < engine->drawDistance)
						DrawCubeTexture(engine->fire, pos, 1.0, 0.00, 1.0, RED);					
				}

				else if(world->map.walling[y][x] == Tile_Caz){
					const Vector3 pos = { (float)x, 0.0f, (float)y};	
					float dist = Vector3DistanceSqr((Vector3)pos, (Vector3){world->position[0].x, 0.4, world->position[0].y});
					if(dist < engine->drawDistance)
						DrawCubeTexture(engine->fire, pos, 1.0, 0.0, 1.0, BLACK);					
				}	
				}
			}
		EndBlendMode(); // disable blending
	}





	CompMask mask = COMP_POSITION | COMP_RENDER;
	Vector3 player_position =// engine->camera.position;
	(Vector3) {
		world->position[0].x, 0.4, world->position[0].y
			
	};

	// Temporary array for sorting
	static EntityDistance sortedEntities[MAX_ENTITIES];

	int entityCount = 0;
	for (int i = 1; i < MAX_ENTITIES; i++) {
    if ((world->masks[i] & mask) == mask) {
        Vector3 pos = (Vector3){
            (float)world->position[i].x, 0.4, (float)world->position[i].y
        };
		

        sortedEntities[entityCount].index = i;
        sortedEntities[entityCount].distanceSqr = Vector3DistanceSqr(pos, player_position);
        sortedEntities[entityCount].stableId = i; // Use entity index as stable ID
        ++entityCount;
    }
}

	//if(!engine->isGasRun)
	qsort(sortedEntities, entityCount, sizeof(EntityDistance), compareEntityDistance);
	for (int j = 0; j < entityCount; j++) {
		const int i = sortedEntities[j].index;
		const float distance = sortedEntities[j].distanceSqr;
		const Sprite s = sprites->items[world->renderable[i].type];
		const Position* p = &world->position[i];
		const Vector3 pos = (Vector3) {
			(float)p->x, 0.4f, (float)p->y
			};
		//DrawBillboard(engine->camera, temp, pos, s.scale, WHITE);
		//if(world->visibe[(int)p->y][(int)p->x] == true)
		{
			if(distance > engine->drawDistance){
			//	Color c = BLACK;
			//	c.a = 255;
			//	DrawRectangle(pos.x, pos.z, 500, 500, c);
			}
			//Tbd shader 
			else if(world->status[0].hallucinationTurn > 0){
				const int nS = rand()%S_Sprite_Num;
				const Sprite s = sprites->items[nS];
				DrawBillboard(engine->camera, s.texture, pos, 1.0f, WHITE);
			}
				

			else if(world->renderable[i].type == S_OpenDoor || world->renderable[i].type == S_ClosedDoor){
				
				DrawBillboard(engine->camera, s.texture, pos, 1.6f, WHITE);	
			}
			else if(world->renderable[i].type >= S_Sword && world->renderable[i].type < S_Plant){
				DrawBillboard(engine->camera, s.texture, pos, 0.5f, WHITE);
			}
			else if(world->renderable[i].type == S_Plant){
				DrawBillboard(engine->camera, s.texture, (Vector3){pos.x, 0.1, pos.z}, 1.0f, WHITE);
			}
			else if(world->renderable[i].type == S_PlantBig){
				DrawBillboard(engine->camera, s.texture, pos, 2.0f, WHITE);
			}	
			else if(world->input[i].isFinishedAttack == true)	
				DrawBillboard(engine->camera, s.texture, pos,s.scale + rand_f32()/5.0f, WHITE);	
				
			else
				DrawBillboard(engine->camera, s.texture, pos,s.scale, WHITE);		
				
			}
			
			//Tbd somthing bether for healthbars
			//if(world->renderable[i].type <= S_WaterDemon && world->renderable[i].type >= S_Abomination){
			//	Image hBar  = GenImageColor(100, 100, (Color){0, 0, 0, 0});
			//	const float width = (float)(world->health[i].max - world->health[i].current) / (float)world->health[i].max;
				//ImageDrawRectangle(&hBar, 0, 0, 99*width, 20, WHITE);   
				//Texture temp = LoadTextureFromImage(hBar);
			//	DrawCube((Vector3){pos.x, pos.y + 0.3, pos.z}, 1.0, 0.1, 0.1, WHITE);
				//DrawBillboard(engine->camera, temp, (Vector3){pos.x, pos.y + 0.3, pos.z},s.scale, WHITE);
				//UnloadImage(hBar);
				//UnloadTexture(temp);
			//}
			
		}

		//Render gas
/*	for (int y = 0; y < world->map.h; y++) {
		for (int x = 0; x < world->map.w; x++) {
			if (world->gasMap[y][x].type != gasNo) {
				int type = world->gasMap[y][x].type;
				float time = GetTime();
				
				// Base position with vertical offset
				Vector3 pos = { (float)x, 0.3f, (float)y };
				
				// Multi-frequency noise for more organic movement
				float noiseX = sinf(time * 0.8f + x * 0.15f + y * 0.1f + rand_f32()/50.0f) * 0.7f;
				float noiseZ = cosf(time * 0.6f + x * 0.12f - y * 0.08f + rand_f32()/50.0f) * 0.7f;
				float noiseY = (sinf(time * 1.2f + (x + y) * 0.2f) + 1.0f + rand_f32()/50.0f) * 0.5f;
				
				// Breathing effect with multiple frequencies
				float breath1 = sinf(time * 1.5f + (x + y) * 0.25f);
				float breath2 = cosf(time * 0.8f + (x - y) * 0.15f);
				float alpha = 30 + 70 * ((breath1 * 0.6f + breath2 * 0.4f) * 0.5f + 0.5f);
				
				// Density variation - some areas thicker than others
				float density = 0.7f + 0.3f * sinf(x * 0.3f) * cosf(y * 0.3f);
				alpha *= density;
				
				Color c = gasColor[type];
				
				// Make gas more translucent and atmospheric
				c.a = (unsigned char)Clamp(alpha, 20, 120);
				
				// Soft, organic jitter that changes slowly
				float jitterX = noiseX * 0.2f;
				float jitterZ = noiseZ * 0.2f;
				float jitterY = noiseY * 0.15f;
				
				pos.x += jitterX;
				pos.z += jitterZ;
				pos.y += jitterY;
				
				// Vary cube size for more natural look
				float sizeVariation = 0.8f + 0.3f * sinf(time * 0.5f + (x + y) * 0.1f);
				Vector3 size = { 
					2.9f * sizeVariation, 
					2.7f * sizeVariation, 
					2.9f * sizeVariation 
				};
				
				// Draw with blending for softer appearance
				DrawCubeV(pos, size, c);
				
				// Optional: Add a second, more transparent layer for depth
				if (alpha > 60) {
					Color layer2 = c;
					layer2.a = (unsigned char)(c.a * 0.4f);
					Vector3 pos2 = { pos.x + jitterX * 0.3f, pos.y + 0.2f, pos.z + jitterZ * 0.3f };
					DrawCubeV(pos2, (Vector3){size.x * 1.1f, size.y * 1.0f, size.z * 1.1f}, layer2);
				}
			}
		}
	}*/
    float time = GetTime();

    BeginBlendMode(BLEND_ALPHA); // enable transparency blending

    for (int y = 0; y < world->map.h; y++) {
        for (int x = 0; x < world->map.w; x++) {
            if (world->gasMap[y][x].type != gasNo) {
                int type = world->gasMap[y][x].type;
                
                // Base position
                Vector3 pos = { (float)x, 0, (float)y };
                
                // Sample Perlin noise at multiple frequencies for organic fog
                float noise1 = perlin_noise(x * 0.1f, y * 0.1f, time * 0.1f);
                float noise2 = perlin_noise(x * 0.05f + 100.0f, y * 0.05f + 100.0f, time * 0.05f);
                float noise3 = perlin_noise(x * 0.02f + 200.0f, y * 0.02f + 200.0f, 0); // static base
                
                // Combine noises for density
                float density = (noise1 * 0.5f + noise2 * 0.3f + noise3 * 0.2f) * 0.5f + 0.5f;
                density = Clamp(density, 0.0f, 1.0f);
                
                if (density > 0.2f) {
                    // Fog height
                    float height = 0.3f + 0.7f * density;
                    
                    // Gentle drifting
                    float driftX = perlin_noise(x * 0.08f, time * 0.2f, y * 0.08f) * 0.4f;
                    float driftZ = perlin_noise(x * 0.08f + 50.0f, time * 0.2f + 50.0f, y * 0.08f) * 0.4f;
                    float driftY = perlin_noise(x * 0.1f, y * 0.1f, time * 0.3f) * 0.1f;
                    
                    pos.x += driftX;
                    pos.z += driftZ;
                    pos.y = 0.1f + driftY + height * 0.1f;
                    
                    // Fog color with blending
                    Color fogColor = gasColor[type];
                    float baseAlpha = (float)fogColor.a;
                    
                    // Blend alpha with density and random variation
                    float alpha = baseAlpha * (1.5f + density * 0.5f);
                    //alpha *= 0.7f + ((float)rand() / RAND_MAX) * 0.3f;
                    
                    fogColor.a = (unsigned char)Clamp(alpha, 20.0f, 100.0f);
                    
                    // Keep cube size as before
                    float size = 0.5 + 1.8f * density;
                    float dist = Vector3DistanceSqr((Vector3)pos, (Vector3){world->position[0].x, 0.4, world->position[0].y});
					if(dist < engine->drawDistance)
                    	DrawCubeV(pos, (Vector3){size, height, size}, fogColor);
                }
            }
        }
    }

    EndBlendMode(); // disable blending

	//RenderWater



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
        if (world->map.walling[y][x] != Tile_Wall &&
            world->map.walling[y][x] != Tile_CDoor &&
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
        if (world->map.walling[y][x] != Tile_Wall &&
            world->map.walling[y][x] != Tile_Dwater && world->map.walling[y][x] != Tile_Fire && world->map.walling[y][x] != Tile_Lava &&
            min > world->dikstra[y][x] && world->dikstra[y][x] != 255.0f) {
			min = world->dikstra[y][x];
            p.x = x;
            p.y = y;
        }
    }

    return p;
}

static Position get_highest_tile_dikstra_player(World *world, int sx, int sy, int px, int py) {
    Position p = {sx, sy};
    float min = 0.0f;
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
        if (world->map.walling[y][x] != Tile_Wall &&
           world->map.walling[y][x] != Tile_Dwater  && world->map.walling[y][x] != Tile_Fire &&  world->map.walling[y][x] != Tile_Lava &&
            min < world->dikstra[y][x] && world->dikstra[y][x] != 255.0f) {
            min = world->dikstra[y][x];
            p.x = x;
            p.y = y;
        }
    }

    return p;
}



Position get_highest_tile_dikstra(World *world, int sx, int sy) {
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
            (x != world->position[0].x || y != world->position[0].y)  && world->map.walling[y][x] != Tile_Dwater &&
            max < world->dikstra[y][x]) {
            max = world->dikstra[y][x];
            p.x = x;
            p.y = y;
        }
    }

    return p;
}
Position get_random_tile_dikstra(World *world, int sx, int sy) {
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
			world->state[ent].memoryTimer = rand()%10 + 1;
			is = true;
			}
		}
}



// Make monster state system more interesting for player // systems.c
void monster_change_state_system(World* world, EngineData *engine) {
    CompMask mask = COMP_POSITION | COMP_MONSTER | COMP_STATE | COMP_STATS;

    const int playerX = world->position[0].x;
    const int playerY = world->position[0].y;
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
	int sP = 0;
	for(int i = 0; i < 8; i++){
		
		if(world->map.walling[playerY + dirs[i][0]][playerX + dirs[i][1]] == '#'){
			sP+=1; //Hide player
		}
	}
	if(engine->isTorch){
			sP+=10;
		}
	
	field_of_vison(world, engine, 0); // Calculate player's field of vision

    for (int i = 1; i < MAX_ENTITIES; i++) {
        if ((world->masks[i] & mask) != mask || world->input[i].isMoving)
            continue;

        // --- 1. SENSORY AND SITUATIONAL AWARENESS ---
        bool isVisible = is_player_visible_by_monster(world, world->position[i].x, world->position[i].y);
        float healthRatio = world->health[i].current / (float)world->health[i].max;
        float playerHealthRatio = world->health[0].current / (float)world->health[0].max;
        float distanceToPlayer = Vector2Distance(world->position[i], world->position[0]);
		int peception = rand()%(world->stats[i].perception + 1) - rand()%(world->stats[i].stealth + 1) - sP; 
        
		//if(engine->)
		
		// --- 2. MEMORY SYSTEM ---
		if(world->state[i].current == STATE_STUN){
			if(world->state[i].stunTurn > 0){
				world->state[i].stunTurn--;
				world->state[i].current = STATE_STUN;
				//return;
			}
			else{
				world->state[i].current = STATE_RESTING;
			}
			//MESSAGE_F("Stun %d", world->state[i].stunTurn);
		}
		else{
        if (isVisible && peception > 0) {
            world->state[i].lastSeenX = playerX;
            world->state[i].lastSeenY = playerY;
            world->state[i].memoryTimer = 5; // Remember for 15 turns
        } else if (world->state[i].memoryTimer > 0) {
            world->state[i].memoryTimer--;
        }
        bool hasMemory = (world->state[i].memoryTimer > 0);

        // --- 3. CONFIDENCE AND FEAR CALCULATION ---
        int allyCount = 0;
        for (int j = 1; j < MAX_ENTITIES; j++) {
            if (i == j || (world->masks[j] & mask) != mask) continue;
            // Check for nearby allies (within 8 tiles)
            if (Vector2DistanceSqr(world->position[i], world->position[j]) < 64) {
                allyCount++;
            }
        }

        // Confidence is high if healthy, with friends, and facing a wounded player.
        float confidence = (healthRatio * 0.5f) + (allyCount * 0.25f) - (playerHealthRatio * 0.7f);
        
        // Fear is based on damage taken.
        world->state[i].fear = (1.0f - healthRatio);
        
        // --- 4. HIGH-PRIORITY STATE OVERRIDES ---
        
        // BERSERK: Critically wounded monsters might go berserk.
        if (healthRatio < 0.2f && rand_f32() < 0.4f) { // 40% chance when near death
            world->state[i].current = STATE_BERSERK;
            continue;
        }

        // FLEEING: If fear outweighs confidence and morale, the monster will run.
        if ((world->state[i].fear > confidence + world->stats[i].morale || rand_f32() < world->state[i].chancesR)) {
            world->state[i].current = STATE_RUNING;
            continue;
        }

        // --- 5. CORE BEHAVIORAL DECISION TREE ---

        if ((isVisible || hasMemory) && peception > 0) {
            // -- A. MONSTER IS AWARE OF THE PLAYER --
            
            // Add randomness to break predictable patterns
            float behaviorRandom = rand_f32();
            
            // PATROLLING CHANCE: Even when aware, sometimes monsters prioritize territory
            if (behaviorRandom < 0.15f) { // 15% chance to ignore player temporarily
                float distToHome = Vector2Distance(world->position[i], world->state[i].home);
                if (distToHome > world->state[i].territoryRadius * 0.7f) {
                    world->state[i].current = STATE_TERRITORIAL;
                    continue;
                }
            }
            
            // RESTING CHANCE: Tired monsters might rest even when aware (if feeling safe)
            if (behaviorRandom < 0.08f && healthRatio > 0.7f && distanceToPlayer > 8.0f) {
                world->state[i].current = STATE_RESTING;
                continue;
            }
            
            // WANDERING CHANCE: Distracted monsters might wander
            if (behaviorRandom < 0.1f && distanceToPlayer > 6.0f) {
                set_memory_wandering(world, i);
                world->state[i].current = STATE_WANDERING;
                continue;
            }

            // HUNTING: High confidence or facing a very weak player.
            if ((confidence > 0.5f || playerHealthRatio < 0.25f)) {
                // Add uncertainty: even confident monsters might stalk instead
                if (rand_f32() < 0.2f && distanceToPlayer > 4.0f) { // 20% chance to stalk instead
                    world->state[i].current = STATE_STALKING;
                } else {
                    world->state[i].current = STATE_HUNTING;
                }
            }
            // STALKING: Aware, but not confident enough to engage directly.
            else if (confidence > 0.1f && distanceToPlayer > 5.0f) {
                world->state[i].current = STATE_STALKING;
            }
            // SEARCHING: Lost sight of the player, will move to last known location.
            else {
                // Sometimes searching monsters get bored and return to normal activities
                if (rand_f32() < 0.3f && !isVisible) {
                    float distToHome = Vector2Distance(world->position[i], world->state[i].home);
                    if (distToHome > world->state[i].territoryRadius * 0.5f) {
                        world->state[i].current = STATE_TERRITORIAL;
                    } else {
                        world->state[i].current = STATE_WANDERING;
                    }
                } else {
                    world->state[i].current = STATE_SEARCHING;
                }
            }

        } else {
            // -- B. MONSTER IS IDLE OR UNAWARE --
            float distToHome = Vector2Distance(world->position[i], world->state[i].home);

            // TERRITORIAL: If monster has a home and has strayed too far, return.
            if (distToHome > world->state[i].territoryRadius) {
                world->state[i].current = STATE_TERRITORIAL;
            }
            // WANDERING or RESTING cycle with more variety
            else {
                if (world->state[i].current == STATE_RESTING) {
                    if(rand_f32() < 0.2f) { // 20% chance to start wandering
                        set_memory_wandering(world, i); // Find a new random point
                        world->state[i].current = STATE_WANDERING;
                    } else if (rand_f32() < 0.05f) { // 5% chance to patrol territory
                        world->state[i].current = STATE_TERRITORIAL;
                    }
                } else if (world->state[i].current == STATE_WANDERING) {
                    if(rand_f32() < 0.15f) { // 15% chance to start resting
                        world->state[i].current = STATE_RESTING;
                    } else if (rand_f32() < 0.1f) { // 10% chance to patrol
                        world->state[i].current = STATE_TERRITORIAL;
                    }
                } else {
                    // Default to wandering if in an unexpected state
                    if(rand_f32() < 0.1f) {
                        world->state[i].current = STATE_RESTING;
                    } else if(world->state[i].current != STATE_STUN) {
                        set_memory_wandering(world, i);
                        world->state[i].current = STATE_WANDERING;
                    }
                }
            }
        }
        
        // --- 6. GROUP ALERTING ---
        if (world->state[i].current == STATE_HUNTING || world->state[i].current == STATE_STALKING) {
            for (int j = 1; j < MAX_ENTITIES; j++) {
                if (i == j || (world->masks[j] & mask) != mask) continue;

                if (Vector2DistanceSqr(world->position[i], world->position[j]) < 36) { // Alert radius of ~6 tiles
                    if (world->state[j].current != STATE_HUNTING && world->state[j].current != STATE_RUNING && world->state[j].current != STATE_STUN) {
                        // Not all monsters get alerted - some might ignore the alert
                        if (rand_f32() < 0.7f) { // 70% chance to respond to alert
                            world->state[j].current = STATE_ALERTED;
                            world->state[j].memoryTimer = 5; // Alerted monsters remember for a while
                            world->state[j].lastSeenX = playerX;
                            world->state[j].lastSeenY = playerY;
                        }
                    }
                }
            }
        }
    }
	}
}


static void spell_system(World* world, EngineData* engine, Global_Ent_DA* ent, int i){
	//MESSAGE_F("SPELL SYSTEM %d", i);
	const Spell spell = world->spell[i];
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
	switch (spell.type)
	{
	case Spell_Summon:{
		//MESSAGE("SpellSumoon");
		//
	
		int is = -1;
		float x = 0;
		float y = 0;
		for(int j = 0; j < 8; j++){
			
			x = world->position[0].x + dirs[j][0];
			y = world->position[0].y + dirs[j][0];
			//MESSAGE_F("%f %f", x, y)
			is = is_monster_on_position(world, x, y);
			if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
				break;
				//MESSAGE("Summon");
			}

		}
		if(is == -1){
			const Vector2 pos  = (Vector2){x, y}; 
			const int monster = create_entity(world); 
			add_components_to_ent_depending_on_T(world, ent, monster, spell.value, pos);
			world->state[monster].current = STATE_HUNTING;
			//world->spell[monster].type = Spell_No;
			//MESSAGE_F("Sumoon %d/%d", world->spell[i].passTurn, world->spell[i].cooldown);
			world->spell[i].passTurn = 0;
			world->spell[monster].passTurn = 0;
		}
		else{
			//MESSAGE("No ");
		}
		world->spell[i].passTurn = 0;
		break;	
	}
		 
	case Spell_Stun:{
		int intP = rand()%(world->stats[0].inte + 1);
		int intM = rand()%(world->stats[i].inte + 1);
		if(intM > intP){
			world->state[0].stunTurn += world->spell[i].value;
		}
		MESSAGE("You are stuned");
		world->spell[i].passTurn = 0;
		break;
	}	

	case Spell_Blink:{
		int x = (int)world->position[0].x; 
		int y = (int)world->position[0].y;
		//exit(-1);
		MESSAGE("Blink");
		for(int j = 0; j < 4; j++){
			
			const int xM = x + dirs[j][0];
			const int yM = y + dirs[j][1]; 
			if(world->map.walling[yM][xM] != '#' && is_monster_on_position(world, x, y) != -1){
				MESSAGE("Enemy blink on you");
				world->position[i] = (Vector2){(float)xM, (float)yM};
				world->spell[i].passTurn = 0;
				break;
			}
		}
		world->spell[i].passTurn = 0;
		break;
	}
	//Just gas exp for now
	case Spell_Explode:{
		float dist = Vector2Distance((Vector2)world->position[i],(Vector2) world->position[0]);
		
		if(dist < 2.0){
			MESSAGE("Exploded");
			world->health[i].current = 0;
			world->spell[i].passTurn = 0;
			for(int j = 0; j < 8; j++){
				int x = world->position[i].x + dirs[j][0];
				int y = world->position[i].y + dirs[j][1];
				world->gasMap[y][x] = (Gas){spell.value, false, 1000, RED};
			}
		}
			world->spell[i].passTurn = 0;
		break;
	}

	case Spell_Dmg:{
		int intP = rand()%(world->stats[0].inte + 1);
		int intM = rand()%(world->stats[i].inte + 1);
		//MESSAGE("Spell Dmg");
		world->spell[i].passTurn = 0;
		if(intM > intP){
			MESSAGE_F("You are dmg by spell %d", spell.value);
			world->health[0].current -= spell.value;
		}
		world->spell[i].passTurn = 0;
		break;
	}
	case Spell_Teleport:{
		int is = false;
		while(!is){
			int x = rand()%(world->map.w - 1);
			int y = rand()%(world->map.h - 1);
			if(world->map.walling[y][x] == ' '){
				is = true;
				//VALUE 1 self 0 player
				if(spell.value == 1){
					//Tbd do dts if health 0 0r player 0
					world->position[i] = (Position){(float)x, (float)y};
				}	
				else if(spell.value == 0){
					MESSAGE("YOu have been teleported");
				 	world->position[0] = (Position){(float)x, (float)y};
					engine->nextPosition = (Vector3){(float)x, 0.6, (float)y};
				}
				
			}
		}
		world->spell[i].passTurn = 0;
		break;
	}

	case Spell_Shout:{
		MESSAGE("You hear someon shout");
		world->spell[i].passTurn = 0;
		for (int j = 1; j < MAX_ENTITIES; j++) {
                if (i == j || (world->masks[j] & COMP_MONSTER) != COMP_MONSTER) continue;

                if (Vector2DistanceSqr(world->position[i], world->position[j]) < 200) { // Alert radius of ~6 tiles
						int intP = rand()%(world->stats[0].inte + 1);
						int intM = rand()%(world->stats[i].inte + 1);
                        if (intM > intP) { // alert if higer then player i mean
                            world->state[j].current = STATE_HUNTING;
                            world->state[j].memoryTimer = 10; // Alerted monsters remember for a while
                            world->state[j].lastSeenX = world->position[0].x;
                            world->state[j].lastSeenY = world->position[0].y;
                        }
                    }
                }

				break;
            }
		case Spell_Hook:{
			int x = (int)world->position[i].x; 
			int y = (int)world->position[i].y;
			//exit(-1);
			//MESSAGE("Blink");
			for(int j = 0; j < 8; j++){
				
				const int xM = x + dirs[j][0];
				const int yM = y + dirs[j][1]; 
				if(world->map.walling[yM][xM] != '#' && is_monster_on_position(world, x, y) != -1){
					MESSAGE("Enemy hooks youu");
					world->position[0] = (Vector2){(float)xM, (float)yM};
					engine->nextPosition = (Vector3){(float)xM, 0.6, (float)yM};
					world->spell[i].passTurn = 0;
					break;
				}
			}
			world->spell[i].passTurn = 0;
			break;
		}
			 
	case Spell_Web:{
		int intP = rand()%(world->stats[0].inte + 1);
		int intM = rand()%(world->stats[i].inte + 1);
		if(intM > intP){
			world->state[0].stunTurn += world->spell[i].value;
			MESSAGE("You are cought in web");
		}
		
		world->spell[i].passTurn = 0;
		break;
	}		
	case Spell_Obsidian:{
		//GEt ent bufff
		int j = 0;
		for( ;j < MAX_ENTITIES; j++){
			if((world->masks[j] & COMP_MONSTER) == COMP_MONSTER){
				if(j == i) continue;
				int distance = Vector2DistanceSqr(world->position[j], world->position[i]);
				if(distance < 100 && i != j){
					break;
				}
			}
		}
		if(j == MAX_ENTITIES - 1){
			//exit(-1);
			break;

		}
		else{
			world->spell[i].passTurn = 0;
			if(world->spell[i].value == DMG){
				const int dmg = 1 + rand()%3;  //DMG 0-4
				world->stats[j].dmgMax+=dmg;
				MESSAGE("Obsidan buff dmg");
			}
			else if(world->spell->value == HEAL){
				int health = 5 + rand()%3; //5 - 8
				world->health[j].current += health;
				world->health[j].max += health;
				CLAMP(world->health[j].current, 0, world->health[j].max);
				MESSAGE("Obsidan buff health and maxHealth");
			}
		}

		break;
		
	}	

	case Spell_Anubis:{
		int is = false;
		world->spell[i].passTurn = 0;
		while (!is){
			int x = rand()%10 - 5 + (int)world->position[i].x;
			int y = rand()%10 - 5 + (int)world->position[i].y;
			CLAMP(x, 1, (MAP_WIDTH  - 1));
			CLAMP(y, 1, (MAP_HEIGHT - 1));
			if(world->map.walling[y][x] != Tile_Wall){
				if(world->trapMap[y][x].trap == TRAP_NO){
					world->trapMap[y][x].trap = TRAP_SUMMON;
					world->trapMap[y][x].value = Zombie;
					is = true;
				}
			}
				
		}
		

		break;
	}
	case Spell_OrcScout:{
		int is = false;
		world->spell[i].passTurn = 0;
		while (!is){
			int x = rand()%10 - 5 + (int)world->position[i].x;
			int y = rand()%10 - 5 + (int)world->position[i].y;
			CLAMP(x, 1, (MAP_WIDTH  - 1));
			CLAMP(y, 1, (MAP_HEIGHT - 1));
			if(world->map.walling[y][x] != Tile_Wall){
				if(world->trapMap[y][x].trap == TRAP_NO){
					world->trapMap[y][x].trap = TRAP_SUMMON;
					world->trapMap[y][x].value = Wolf;
					is = true;
				}
			}
				
		}
		

		break;
	}
	case Spell_Sacrifice:{
		int monster = create_entity(world);
		add_components_to_ent_depending_on_T(world, ent, monster, spell.value, world->position[i]);
		MESSAGE("You felt blood magic");
		destroy_entity(world, i);
		break;
	}
	case Spell_Mirror:{
		MESSAGE("MirrorImage");
		for(int k = 0; k < 4; k++){
		int is = -1;
		float x = 0;
		float y = 0;
		for(int j = 0; j < 8; j++){
			
			x = world->position[i].x + dirs[j][0];
			y = world->position[i].y + dirs[j][1];
			//MESSAGE_F("%f %f", x, y)
			is = is_monster_on_position(world, x, y);
			if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
				break;
				//MESSAGE("Summon");
			}

		}
		if(is == -1){
			const Vector2 pos  = (Vector2){(int)x, (int)y}; 
			int monster = create_entity(world); 
			add_components_to_ent_depending_on_T(world, ent, monster, spell.value, pos);
			world->state[monster].current = STATE_STUN;
			world->state[monster].lastSeenX = world->position[0].x;
			world->state[monster].lastSeenY = world->position[0].y;
			world->state[monster].memoryTimer = 50;
			world->spell[monster].type = Spell_No;
			world->spell[monster].value = 0;
			world->spell[monster].cooldown = 100000;
			world->health[monster].max = 5;
			world->stats[monster].dmgMin = 0;
			world->stats[monster].dmgMax = 1;
			world->health[monster].current = 5;
			
		}
		else{};
		}
		world->spell[i].passTurn = 0;
		break;	
	}

	case Spell_WarCray:{
		//1 are orcs
		if(spell.value == 1){
			MESSAGE("You hear a war cray");
			for(int j = 0; j < MAX_ENTITIES; j++){
				if((world->masks[j] & COMP_MONSTER) == COMP_MONSTER)
				if(world->renderable[j].type >= S_OrcWarrior && world->renderable[j].type <= S_OrcWarchief){
					world->state[j].current = STATE_ALERTED;
					world->state[j].lastSeenX = world->position[j].x;
					world->state[j].lastSeenY = world->position[j].y;
					world->state[j].memoryTimer = 20;

				}
			}
		}
		//Goblins
		else if(spell.value == 2){
			MESSAGE("You hear a war cray");
			for(int j = 0; j < MAX_ENTITIES; j++){
				if((world->masks[j] & COMP_MONSTER) == COMP_MONSTER)
				if(world->renderable[j].type >= S_GoblinWarrior && world->renderable[j].type <= S_GoblinWarlord){
					world->state[j].current = STATE_ALERTED;
					world->state[j].lastSeenX = world->position[j].x;
					world->state[j].lastSeenY = world->position[j].y;
					world->state[j].memoryTimer = 20;

				}
			}
		}
		world->spell[i].passTurn = 0;
		break;	

	}
	case Spell_GoblinBarrack:{
		MESSAGE("GoblinBarrack");
		for(int k = 0; k < 6; k++){
		int is = -1;
		float x = 0;
		float y = 0;
		for(int j = 0; j < 8; j++){
			
			x = world->position[i].x + dirs[j][0];
			y = world->position[i].y + dirs[j][1];
			//MESSAGE_F("%f %f", x, y)
			is = is_monster_on_position(world, x, y);
			if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
				break;
				//MESSAGE("Summon");
			}

		}
		if(is == -1){
			const Vector2 pos  = (Vector2){(int)x, (int)y}; 
			int monster = create_entity(world); 
			const float chance = rand_f32();
			if(chance < 0.6f)
				add_components_to_ent_depending_on_T(world, ent, monster, GoblinWarrior, pos);
			else if(chance > 0.6 && chance < 0.9)
				add_components_to_ent_depending_on_T(world, ent, monster, GoblinArcher, pos);
			else 
				add_components_to_ent_depending_on_T(world, ent, monster, GoblinWarlord, pos);

			world->state[monster].current = STATE_HUNTING;		
		}
		else{};
		}
		world->spell[i].passTurn = 0;
		break;	
	}
	case Spell_Confusion:{
		int intP = rand()%(world->stats[0].inte + 1);
		int intM = rand()%(world->stats[i].inte + 1);
		if(intM > intP && world->status[0].confusionImune == false){
			
				//MESSAGE("You are confusedc");
				world->status[0].confusionTurn += rand()%10;
			
		}
		
		world->spell[i].passTurn = 0;
		break;
	}
	case Spell_ReduceStr:{
		int intP = rand()%(world->stats[0].inte + 1);
		int intM = rand()%(world->stats[i].inte + 1 + 100);
		if(intM > intP && world->stats[0].str >= 5){
		MESSAGE_F("You fill weaker %d", world->stats[0].str);
		world->stats[0].str--;
			for(int z = 1; z < MAX_ENTITIES; z++){
				if((world->masks[z] & COMP_MONSTER) == COMP_MONSTER){
						world->stats[z].str++;
						}
					}
		}

		world->spell[i].passTurn = 0;
		break;		
		}	
		

	default:
		break;
	}
}


//SMART STUFFS
void monster_state_system(World* world, EngineData *engine, Global_Ent_DA* ent) {
	DROP(engine)

	CompMask mask = COMP_POSITION | COMP_MONSTER;
	//calculate_diakstra_map(world, world->position[0].x, world->position[0].y, 1);
	for (int i = 1; i < MAX_ENTITIES; i++) {
		if ((world->masks[i] & mask) == mask && world->input[i].isMoving == false ) {
			if(world->renderable[i].type == S_FireDemon){
				const int x = (int)world->position[i].x;
				const int y = (int)world->position[i].y;
				world->map.walling[y][x] = Tile_Fire;
			}
			else if(world->renderable[i].type == S_WaterDemon){
				const int x = (int)world->position[i].x;
				const int y = (int)world->position[i].y;
				world->map.walling[y][x] = Tile_Water;
				
			}

			//Spell cooldown
			if((world->masks[i] & mask) == COMP_SPELL){
				if(world->spell[i].type != Spell_No){
					if(world->spell[i].cooldown > world->spell[i].passTurn){
						world->spell[i].passTurn++;
					}
				}
			}
		
		
			//Calculate distances
			float distance = Vector2Distance(world->position[i], world->position[0]);
			int  isAtt = false;
				
			if((world->status[i].confusionTurn > 0 || world->status[i].hallucinationTurn > 0)){
					
				}
			else if(distance <= 10.0f && distance >= 0.0f && (world->masks[i] & COMP_SPELL) == COMP_SPELL 
			&& (world->state[i].current != STATE_RUNING || world->state[i].current != STATE_WANDERING || world->state[i].current != STATE_STUN) 
			&& is_player_visible_by_monster(world, world->position[i].x, world->position[i].y)){
				if(world->spell[i].cooldown == world->spell[i].passTurn 
					&& is_player_visible_by_monster(world, world->position[i].x, world->position->y)){
					spell_system(world, engine, ent, i);
					isAtt = true;
					//world->spell[i].passTurn = 0;
				}
				
			}	
				
			if((world->status[i].confusionTurn > 0 || world->status[i].hallucinationTurn > 0) && rand()%10 == 0){
					
				}
			else if(world->renderable[i].type == S_Garg && world->state[i].current == STATE_STUN){} //DO nothing
			else if(world->renderable[i].type == S_ObsidanStatue){}
			else if(distance <= 1.41f && distance >= 1.0f && (world->state[i].current != STATE_RUNING) && !isAtt) {
				world->input[i].isMoving = ATTACK;
				isAtt = true;
				//world->input[i].isFinishedAttack = false;
				}
			//Rang	e
			else if(distance <= 8.0f && distance >= 3.0f && (world->state[i].current != STATE_RUNING) 
			&& world->visibe[(int)world->position[i].y][(int)world->position[i].x] && rand_f32() < world->state[i].chanceRange){
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
			
			if(!isAtt && world->input[i].isMoving == NOT) {
				Position p;
				//Use this to just skip of all non alowed monsters to move so buildings
				if(world->renderable[i].type == S_SPit){
					p = world->position[i];
				}
				else if(world->renderable[i].type == S_GoblinBarrack){
					p = world->position[i];
				}
				else if(world->renderable[i].type == S_Kraken){
					p = world->position[i];
				}
				else if(world->state[i].current == STATE_STUN){
					p = world->position[i];
				}
				else if((world->status[i].confusionTurn > 0 || world->status[i].hallucinationTurn > 0)){
					p = get_random_tile_dikstra(world, world->position[i].x, world->position[i].y);
				}

				

				else if(world->state[i].current == STATE_WANDERING){
				
						p = get_lowest_tile_dikstra_player(world, world->position[i].x, world->position[i].y, 
						world->state[i].lastSeenX, world->state[i].lastSeenY );
					
					//p = get_random_tile_dikstra(world, world->position[i].x, world->position[i].y);
					
				}
				else if(world->state[i].current == STATE_HUNTING || world->state[i].current == STATE_BERSERK){
					p = get_lowest_tile_dikstra_player(world, world->position[i].x, world->position[i].y, 
						world->position[0].x, world->position[i].y);
					
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
				else if(world->state[i].current == STATE_STALKING){
					p = get_lowest_tile_dikstra(world, world->position[i].x, world->position[i].y);
				}
				//else if(world->state[i].current == STATE_)	
				else{
					p = get_highest_tile_dikstra_player(world, world->position[i].x, world->position[i].y, world->position[0].x ,world->position[0].y);
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
void health_system(World* world, Global_Ent_DA* ent, EngineData *engine) {
	CompMask mask = COMP_HEALTH;

	for (int i = 0; i < MAX_ENTITIES; i++) {
		if(i == 0){
			if(world->health[0].current <= 0){
				exit(-1);
			}
		}
		else if (((world->masks[i] & mask) == mask) && world->health[i].current <= 0) {
			MESSAGE_F("Entity %d died!\n", i);
			
			//Death stuff
			//Wolf Call of the pack 80% chance
			for(int j = 0; j < MAX_ENTITIES; j++){
				if((world->masks[j] & COMP_MONSTER) == COMP_MONSTER){
					if(world->renderable[j].type == S_Wolf){
					if(rand_f32() < 0.8f){
					//exit(-1);
						world->state[j].current = STATE_ALERTED;
						world->state[j].lastSeenX = (int)world->position[0].x;
						world->state[j].lastSeenY = (int)world->position[0].y;
						world->state[j].memoryTimer = 20;
						}
					}
				}
			}
			//Accolyt rez
			if(world->renderable[i].type >= S_Acolyte && world->renderable[i].type <= S_AcolyteS){
					int is = false;
					int k = 0;
					for(; k < MAX_ENTITIES; k++){
						if(world->renderable[k].type == S_SPit){
							is = true;
							//exit(-1);
							break;
						}
					}
					if(is == true){
						//exit(-1);
						MESSAGE("You fill a surge of dark energy");
						const int type = AcolyteD + (world->renderable[i].type - S_Acolyte);
						int monster = create_entity(world);
						add_components_to_ent_depending_on_T(world, ent, monster, type, (Vector2)world->position[k]); 
						world->state[monster].current = STATE_HUNTING;
						world->state[monster].lastSeenX = (int)world->position[0].x;
						world->state[monster].lastSeenY = (int)world->position[0].y;
						world->state[monster].memoryTimer = 20;
						
					}
				}
			//Garg statue
			else if(world->renderable[i].type == S_Garg){
				int monster = create_entity(world);
				add_components_to_ent_depending_on_T(world, ent, monster, Garg, (Vector2)world->position[i]); 
				world->state[monster].current = STATE_STUN;
				world->state[monster].stunTurn = 30;
				MESSAGE("Garg became stone");
				//world->state[monster].
			}
			//Obsidan Statue	
			else if(world->renderable[i].type == S_ObsidanStatue){
				int monster = create_entity(world);
				add_components_to_ent_depending_on_T(world, ent, monster, ObsidanStatue, (Vector2)world->position[i]); 
				world->state[monster].current = STATE_STUN;
				world->state[monster].stunTurn = 30;
				MESSAGE("Obsidian became stone");
				//world->state[monster].
			}

			//Bloat exploding or no
			else if(world->renderable[i].type == S_Bloat){
				const int x = world->position[i].x;
				const int y = world->position[i].y;
				world->gasMap[y][x].type = rand()%gasNum;
				world->gasMap[y][x].timeToStay = 1000;
			}
			//Tbd pinkjely when confusion
			//LetsBe acid
			else if(world->renderable[i].type == S_PinkJelly && rand_f32() < 0.2f){
				const int x = world->position[i].x;
				const int y = world->position[i].y;
				world->gasMap[y][x].type = gasAcid;
				world->gasMap[y][x].timeToStay = 1000;
			}
			else if(world->renderable[i].type == S_GreenJelly && rand_f32() < 0.2f){
				const int x = world->position[i].x;
				const int y = world->position[i].y;
				world->gasMap[y][x].type = gasPoison;
				world->gasMap[y][x].timeToStay = 1000;
			}
			else if(world->renderable[i].type == S_BlueJelly && rand_f32() < 0.4f){
				const int x = world->position[i].x;
				const int y = world->position[i].y;
				world->gasMap[y][x].type = gasHealing;
				world->gasMap[y][x].timeToStay = 100;
			}

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
				//world->map.walling[y][x] = '-';
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


static int get_closest_visible(World *world){
	int   cIndex = -1;
	float lDist = 10000.0f;
	for(int i = 1; i < MAX_ENTITIES; i++){
		if(world->masks[i] & COMP_MONSTER){
			const int x = (int)world->position[i].x;
			const int y = (int)world->position[i].y;
			const int isV = is_player_visible_by_monster(world, x, y);
			if(isV){
				const float dist = Vector2Distance(world->position[0], world->position[i]);
				if(dist < lDist){
					cIndex = i;
					lDist = dist;
				}
			}
		}
	}
	return cIndex;
}

///*Tbd type
static void spawn_projectile(World* world, int ent, ProjeciteType type, int itemID,  EngineData *engine){
	int projectile = create_entity(world);
	//add_tag(world, projectile, COMP_PROJEC);
	//add_tag(world, projectile, COMP_MONSTER);
	add_component(world, projectile, COMP_PROJEC, &(Projectile) {
			type, itemID
			});

	
	add_component(world, projectile, COMP_POSITION, &(Position) {
			world->position[ent].x + 0.1f, world->position[ent].y  + 0.1f
			});
	add_component(world, projectile, COMP_RENDER, &(Renderable){
		(Sprite_Type)type
	});
	//add_component(world, projectile, COMP_INPUT, &(Input){0});	
	add_component(world, projectile, COMP_STATS, &(Stats){
		world->stats[ent].str, world->stats[ent].dex, world->stats[ent].inte, world->stats[ent].cons, world->stats[ent].morale,
		world->stats[ent].perception, world->stats[ent].stealth, world->stats[ent].dmgMax, world->stats[ent].dmgMin,
		0
	});
	//Player
	if(ent == 0){

		//For streight line 
		/*
		const int dx  = (int)roundf(sinf(engine->playerYaw));
		const int dz  = (int)roundf(cosf(engine->playerYaw));
		float x = world->position[0].x + 10*dx;
		float y = world->position[0].y + 10*dz;
		//MESSAGE_F("(%f %f) (%f %f)", x, world->position[0].x,  y, world->position[0].y);
		*/
		//For close
		
		int cIndex = get_closest_visible(world);
		if(cIndex == -1){
			MESSAGE("We do not see any enemy");
		}
		else{
			const float x = world->position[cIndex].x;
			const float y = world->position[cIndex].y;
			world->input[projectile].nextPosition = (Position){x, y};
			world->input[projectile].isMoving = MOVE;
			world->input[projectile].isFinishedAttack = true;
			world->input[projectile].entProjectile = ent;
			engine->isEntMoving = true;
		}		


		
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
			//	TBD other when be
			{
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
				if(world->projectile[i].type == P_Potion && world->input[i].entProjectile == 0){
					const int id = world->projectile[i].itemID;
					if(id != -1)
					switch (world->inventory[0].items[id].potion){
					
						case Potion_Poison:{
							//MESSAGE("You used a poison potion");
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasPoison, false, 1000, gasColor[gasPoison]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}
						case Potion_Gas:{
							//MESSAGE("You used a gas like potion");
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasSwamp, false, 1000, gasColor[gasSwamp]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}	
						case Potion_Acid:{
							//MESSAGE("You used a acid like potion");
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasAcid, false, 1000, gasColor[gasAcid]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}	
						case Potion_HealingGas:{
							MESSAGE_F("You used a gas like healing potion %d", id);
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasHealing, false, 1000, gasColor[gasHealing]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}
						default:
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							//exit(-1);
							break;
					}	

				}
				else
					destroy_entity(world, i);
				//exit(-1);
			}
			if(world->input[i].entProjectile != 0){
				if(world->projectile[i].type == P_Arrow){
				float distance = Vector2Distance(world->position[i], world->position[0]);
				//MESSAGE_F("Distance %f", distance);
				if(distance < 2.5f){
						//MESSAGE_F("Distance %f", distance);
						//destroy_entity(world, i);
						int dmg = attack_dmg_callculations(world,  world->input[i].entProjectile, 0, true);
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
				else if(world->projectile[i].type == P_Potion){
		
				}
			}
			else{
				for(int j = 0; j < MAX_ENTITIES; j++){
				if(j != i && ((world->masks[j] & COMP_MONSTER))){
					float distance = Vector2Distance(world->position[i], world->position[j]);
					
					if(distance < 2.1f && world->input[i].entProjectile != j){
						if(world->projectile[i].type == P_Arrow){
						MESSAGE_F("Distance %f", distance);
						//destroy_entity(world, i);
						int dmg = attack_dmg_callculations(world,  world->input[i].entProjectile, j, true);
						world->health[j].current-=dmg;
						MESSAGE_F("PLAYER ATTACK health %d", world->health[j].current);
						destroy_entity(world, i);
						//exit(-1);
						break;
						//exit(-1);
					}
					else if(world->projectile[i].type == P_Potion){
						//MESSAGE("pOTION PROJECTILE");
						//exit(-1);
					MESSAGE("pOTION PROJECTILE");
					
					const int id = world->projectile[i].itemID;
					//exit(-1);
					if(id != -1)
					switch (world->inventory[0].items[id].potion){
					
						case Potion_Poison:{
							//MESSAGE("You used a poison potion");
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasPoison, false, 1000, gasColor[gasPoison]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}
						case Potion_Gas:{
							//MESSAGE("You used a gas like potion");
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasSwamp, false, 1000, gasColor[gasSwamp]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}	
						case Potion_Acid:{
							//MESSAGE("You used a acid like potion");
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasAcid, false, 1000, gasColor[gasAcid]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}	
						case Potion_HealingGas:{
							MESSAGE_F("You used a gas like healing potion %d", id);
							world->identPotions[world->inventory[0].items[id].potion] = true;
							const int x = (int)world->position[i].x;
							const int y = (int)world->position[i].y;
							world->gasMap[y][x] = (Gas){gasHealing, false, 1000, gasColor[gasHealing]};
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							break;}
						default:
							destroy_entity(world, i);
							free_item(&world->inventory[0], id);
							//exit(-1);
							break;
					}	
					

					}
					}
					
				}
			}
			
				 
			/**/
			}	
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

		if(world->status[0].confusionTurn > 0){
			const int key = GetKeyPressed();
			
			const int what = rand()%5;
			if (what == 0 && key) {
			engine->targetYaw -= PI/2.0f;
			engine->isMoving = true;
			engine->moveLerpAlpha = 0.0f;
			engine->isRotation = true;

			}

		if (what == 1 && key) {
			engine->targetYaw += PI/2.0f;
			engine->isMoving = true;
			engine->moveLerpAlpha = 0.0f;
			engine->isRotation = true;
			}
		else if(what == 2 && key){
			if(world->state[0].stunTurn > 0){
				world->state[0].stunTurn--;
				engine->isEntMoving = true;
				engine->isMoving = false;
				engine->isGasRun = true;
				MESSAGE_F("Stun turn %d", world->state[0].stunTurn);
				return;
			}
			engine->isEntMoving = true;
			engine->isMoving = true;
			engine->isGasRun = true;
		}
		else if (key){
			{
			if(world->state[0].stunTurn > 0){
					world->state[0].stunTurn--;
					engine->isMoving = true;
					engine->isEntMoving = true;
					engine->isRotation = false;
					int dx = (int)roundf(sinf(engine->playerYaw));
					int dz = (int)roundf(cosf(engine->playerYaw));
					//engine->nextPosition.x -= dx;
					//engine->nextPosition.z -= dz;
					const int x = (int)engine->nextPosition.x + dx;
					const int y = (int)engine->nextPosition.z + dz;
				
					if(world->dikstra[y][x] >= 255 ) {
					int whatMonster = is_monster_in_next_postition(world,(float)x, (float)y); 
					if(whatMonster){
						int dmg = attack_dmg_callculations(world, 0, whatMonster, false);
						world->health[whatMonster].current-=dmg;
						MESSAGE_F("PLAYER ATTACK health %d", world->health[whatMonster].current);
						//exit(-1);
					}
					}
				
					MESSAGE_F("Stun turn %d", world->state[0].stunTurn);
					return;
			}

			engine->isRotation = false;
			engine->isGasRun = true;
			int dx = (int)roundf(sinf(engine->playerYaw));
			int dz = (int)roundf(cosf(engine->playerYaw));
			engine->nextPosition.x += dx;
			engine->nextPosition.z += dz;
			const int x = (int)engine->nextPosition.x;
			const int y = (int)engine->nextPosition.z;
			calculate_diakstra_map(world, world->position[0].x, world->position[0].y, 1);
			if(world->dikstra[y][x] >= 255 ) {
				//MESSAGE("aTTCA");
				
				int whatMonster = is_monster_in_next_postition(world,engine->nextPosition.x, engine->nextPosition.z); 
				if(whatMonster){
					int dmg = attack_dmg_callculations(world, 0, whatMonster, false);
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
			engine->moveLerpAlpha = 0.00001f;
				
				
		
			
			//Tbd to ENGINE
			}
		}

		}

		else if (IsKeyPressed(KEY_Q)) {
			engine->targetYaw -= PI/2.0f;
			engine->isMoving = true;
			engine->moveLerpAlpha = 0.0f;
			engine->isRotation = true;

			}

		else if(IsKeyPressed(KEY_E)) {
			engine->targetYaw += PI/2.0f;
			engine->isMoving = true;
			engine->moveLerpAlpha = 0.0f;
			engine->isRotation = true;
			}
		else if(IsKeyPressed(KEY_SPACE)){
			if(world->state[0].stunTurn > 0){
				world->state[0].stunTurn--;
				engine->isEntMoving = true;
				engine->isMoving = false;
				engine->isGasRun = true;
				MESSAGE_F("Stun turn %d", world->state[0].stunTurn);
				return;
			}
			engine->isEntMoving = true;
			engine->isMoving = true;
			engine->isGasRun = true;
			
		}
		//
		if(IsKeyPressed(KEY_A)){
			int rID = is_item_of_type_equ(&world->inventory[0], EQUIPTED_RANGE);
			int mID = is_item_of_type_equ(&world->inventory[0], EQUIPTED_MUTITION);
			
			if((rID == -1) || ((mID == -1)))
				return;
			if((world->inventory[0].items[mID].fire == world->inventory[0].items[rID].type)){
				//MESSAGE_F("%d %d", rID, mID);
				if(world->inventory[0].items[mID].value > 0){
					world->inventory[0].items[mID].value--;
					if(world->inventory[0].items[mID].value == 0){
						da_remove_unordered(&world->inventory[0], mID);
						return;
					}
					spawn_projectile(world, 0, world->inventory[0].items[mID].type + S_Sword, 0, engine);
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
			if(world->state[0].stunTurn > 0){
					world->state[0].stunTurn--;
					engine->isMoving = true;
					engine->isEntMoving = true;
					engine->isRotation = false;
					int dx = (int)roundf(sinf(engine->playerYaw));
					int dz = (int)roundf(cosf(engine->playerYaw));
					//engine->nextPosition.x -= dx;
					//engine->nextPosition.z -= dz;
					const int x = (int)engine->nextPosition.x + dx;
					const int y = (int)engine->nextPosition.z + dz;
				
					if(world->dikstra[y][x] >= 255 ) {
					int whatMonster = is_monster_in_next_postition(world,(float)x, (float)y); 
					if(whatMonster){
						int dmg = attack_dmg_callculations(world, 0, whatMonster, false);
						world->health[whatMonster].current-=dmg;
						MESSAGE_F("PLAYER ATTACK health %d", world->health[whatMonster].current);
						//exit(-1);
					}
					}
				
					MESSAGE_F("Stun turn %d", world->state[0].stunTurn);
					return;
			}

			engine->isRotation = false;
			engine->isGasRun = true;
			int dx = (int)roundf(sinf(engine->playerYaw));
			int dz = (int)roundf(cosf(engine->playerYaw));
			engine->nextPosition.x += dx;
			engine->nextPosition.z += dz;
			const int x = (int)engine->nextPosition.x;
			const int y = (int)engine->nextPosition.z;
			calculate_diakstra_map(world, world->position[0].x, world->position[0].y, 1);
			if(world->dikstra[y][x] >= 255 ) {
				//MESSAGE("aTTCA");
				
				int whatMonster = is_monster_in_next_postition(world,engine->nextPosition.x, engine->nextPosition.z); 
				if(whatMonster){
					int dmg = attack_dmg_callculations(world, 0, whatMonster, false);
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
			engine->moveLerpAlpha = 0.00001f;
				
				
		
			
			//Tbd to ENGINE
			}

		if (IsKeyPressed(KEY_S)) {
				if(world->state[0].stunTurn > 0){
					world->state[0].stunTurn--;
					engine->isMoving = true;
					engine->isEntMoving = true;
					engine->isRotation = false;
					int dx = (int)roundf(sinf(engine->playerYaw));
					int dz = (int)roundf(cosf(engine->playerYaw));
					//engine->nextPosition.x -= dx;
					//engine->nextPosition.z -= dz;
					const int x = (int)engine->nextPosition.x - dx;
					const int y = (int)engine->nextPosition.z - dz;
				
					if(world->dikstra[y][x] >= 255 ) {
					int whatMonster = is_monster_in_next_postition(world,(float)x, (float)y); 
					if(whatMonster){
						int dmg = attack_dmg_callculations(world, 0, whatMonster, false);
						world->health[whatMonster].current-=dmg;
						MESSAGE_F("PLAYER ATTACK health %d", world->health[whatMonster].current);
					}
					}
				
					MESSAGE_F("Stun turn %d", world->state[0].stunTurn);
					return;
			}

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
					int dmg = attack_dmg_callculations(world, 0, whatMonster, false);
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


	Vector3 targetVisualPos = { engine->nextPosition.x * TILE_SIZE, 0.6f, engine->nextPosition.z * TILE_SIZE };
	Vector2 temp = {engine->camera.position.x, engine->camera.position.z};
	engine->camera.position = Vector3Lerp(engine->camera.position, targetVisualPos, engine->moveLerpAlpha);


	//engine->camera.position.x = engine->nextPosition.x;
	//engine->camera.position.y = engine->nextPosition.y;

	engine->camera.target = Vector3Lerp(engine->camera.position, (Vector3){ engine->camera.position.x + sinf(engine->playerYaw), engine->camera.position.y, engine->camera.position.z + cosf(engine->playerYaw)}, 
	engine->moveLerpAlpha );
	//engine->camera.target.x = engine->camera.position.x + sinf(engine->playerYaw);
	//engine->camera.target.z = engine->camera.position.z + cosf(engine->playerYaw);
	//engine->camera.target.y = engine->camera.position.y; // Keep the camera level
	//UPDATE PLAYER pos
	world->position[0].x = engine->camera.position.x;
	world->position[0].y = engine->camera.position.z;
	}

void update_entity_position_system(World* world, EngineData* engine) {
	const float MOVE_SPEED = 2.0f;
	const float MOVE_SPEED_PROJECTILE = 0.1f;
	const float TILE_SIZE  = 1.0f;

	CompMask mask = COMP_POSITION;
	//engine->isAnyMoving = false;
	for (int i = 1; i < MAX_ENTITIES; i++) {
		if ((world->masks[i] & mask) == mask) {
			if(world->input[i].isMoving == MOVE ) {
				//pROJECILE
				//engine->isAnyMoving = true;
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

	void monster_attack_system(World* world, Global_Ent_DA* ent, EngineData* engine){
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
		

	//	engine->isAnyMoving = false;
		for (int i = 1; i < MAX_ENTITIES; i++) {
			
	
			if(world->input[i].isMoving == ATTACK && world->input[i].isFinishedAttack == false){
				
				int dmg = attack_dmg_callculations(world, i, 0, false);
				//MESSAGE("Monster attack");
				MESSAGE_F("You are atacked by %s", world->name[i])
				//MESSAGE_F("Player health %d", world->health[0].current);
				if(dmg == 0){
					//MESSAGE("You sustained no dmg");
				}
				else{
					MESSAGE_F("You are hit for %d", dmg);
					//Bats attacks feeed a BatLords
					if(world->renderable[i].type == S_Bat){
						for(int j = 0; j < MAX_ENTITIES; j++){
							if((world->masks[j] & COMP_RENDER) == COMP_RENDER){
								if(world->renderable[j].type == S_Vampire){
									MESSAGE("You fill a surge of blood magic");
									world->health[j].current+=dmg;
									world->health[j].max+=dmg;
								}
								
							}
						}
					}
			//Let for now pinkjely 30 chance to multi 		
			else if(world->renderable[i].type == S_PinkJelly && rand_f32() < 0.3f){
										
				int is = -1;
				float x = 0;
				float y = 0;
				for(int j = 0; j < 8; j++){
											
					x = world->position[0].x + dirs[j][0];
					y = world->position[0].y + dirs[j][1];
											//MESSAGE_F("%f %f", x, y)
					is = is_monster_on_position(world, x, y);
					if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
						break;
											//MESSAGE("Summon");
							}
							}
						if(is == -1){
							MESSAGE("PinkJelly multiplays");
							const Vector2 pos  = (Vector2){x, y}; 
							const int monster = create_entity(world); 
							add_components_to_ent_depending_on_T(world, ent, monster, PinkJelly, pos);
							world->state[monster].current = STATE_HUNTING;
							world->spell[monster].type = Spell_No;
										//MESSAGE_F("Sumoon %d/%d", world->spell[i].passTurn, world->spell[i].cooldown);
							world->spell[i].passTurn = 0;
								}
							else{
										//MESSAGE("No ");
								}
				}
				else if(world->renderable[i].type == S_GreenJelly && rand_f32() < 0.3f){
										
				int is = -1;
				float x = 0;
				float y = 0;
				for(int j = 0; j < 8; j++){
											
					x = world->position[0].x + dirs[j][0];
					y = world->position[0].y + dirs[j][1];
											//MESSAGE_F("%f %f", x, y)
					is = is_monster_on_position(world, x, y);
					if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
						break;
											//MESSAGE("Summon");
							}
							}
						if(is == -1){
							MESSAGE("GreenJelly multiplays");
							const Vector2 pos  = (Vector2){x, y}; 
							const int monster = create_entity(world); 
							add_components_to_ent_depending_on_T(world, ent, monster, GreenJelly, pos);
							world->state[monster].current = STATE_HUNTING;
							world->spell[monster].type = Spell_No;
										//MESSAGE_F("Sumoon %d/%d", world->spell[i].passTurn, world->spell[i].cooldown);
							world->spell[i].passTurn = 0;
								}
							else{
										//MESSAGE("No ");
								}
				}

				else if(world->renderable[i].type == S_BlueJelly && rand_f32() < 0.3f){
										
				int is = -1;
				float x = 0;
				float y = 0;
				for(int j = 0; j < 8; j++){
											
					x = world->position[0].x + dirs[j][0];
					y = world->position[0].y + dirs[j][1];
											//MESSAGE_F("%f %f", x, y)
					is = is_monster_on_position(world, x, y);
					if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
						break;
											//MESSAGE("Summon");
							}
							}
						if(is == -1){
							MESSAGE("BlueJelly multiplays");
							const Vector2 pos  = (Vector2){x, y}; 
							const int monster = create_entity(world); 
							add_components_to_ent_depending_on_T(world, ent, monster, BlueJelly, pos);
							world->state[monster].current = STATE_HUNTING;
							world->spell[monster].type = Spell_No;
										//MESSAGE_F("Sumoon %d/%d", world->spell[i].passTurn, world->spell[i].cooldown);
							world->spell[i].passTurn = 0;
								}
							else{
										//MESSAGE("No ");
								}
				}
				else if(world->renderable[i].type == S_Toad){
					if(world->status[0].hallucinationTurn <= 0){
						if(rand_f32() < 0.99)
						world->status[0].hallucinationTurn = rand()%10;
					}
				}
				else if(world->renderable[i].type == S_Imp){
					if(rand_f32() < 0.25f){
						if(world->fire[0].imuneToFire == false)
							world->fire[0].isOnFire = 1;
					}
				}
				else if(world->renderable[i].type == S_SoulReaper && dmg > 0){
					MESSAGE("You fill a bload magic");
					world->health[0].max-=dmg;
					for(int z = 1; z < MAX_ENTITIES; z++){
						if((world->masks[z] & COMP_MONSTER) == COMP_MONSTER){
							world->health[z].current+=dmg;
							world->health[z].max+=dmg;
						}

					}
				}
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
					spawn_projectile(world, i,  world->inventory[0].items[mID].type + S_Sword, 0,  engine);
					//MESSAGE("pROJECTILE");
				} //else MESSAGE("Test");
			}
			}
				//exit(-1);
				
			}
			engine->isAnyMoving = false;
            for (int i = 1; i < MAX_ENTITIES; i++) {
                if (world->input[i].isMoving != NOT) {
                    engine->isAnyMoving = true;
                    break;
                }
				}
				if (!engine->isAnyMoving) {
					engine->isEntMoving = false;
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
#define CHANCE_ACID_ITEM 0.25f
void gas_system(World *world, EngineData *engine){
	CompMask mask = COMP_POSITION | COMP_GAS;
	engine->isGasRun = false;
	//static int counter = 0;
	//MESSAGE_F("Difusion %d", counter++);
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
	
	for(int i = 0; i < MAX_ENTITIES; i++){
		if((world->masks[i] & mask) == mask && world->gas[i].isActive == 1){
			const Position p = world->position[i];
			const int x = ((int)p.x % (world->map.w - 1));
			const int y = ((int)p.y % (world->map.h - 1));
			if(world->map.walling[y][x] == Tile_Fire){
				world->gas[i].isActive = false;
				world->gas[i].type = gasNo;
			}
			for(int j = 0; j < 8 ; j++){
				const int mapX = (x + dirs[j][0])%(world->map.w - 1);
				const int mapY = (y + dirs[j][1])%(world->map.h - 1); 
				if(world->map.walling[mapY][mapX] != '#' ){
					if(world->gasMap[mapY][mapX].type == gasNo)
					world->gasMap[mapY][mapX] = (Gas)world->gas[i];
					else if(world->gasMap[mapY][mapX].type == world->gas[i].type ){
						world->gasMap[mapY][mapX].timeToStay += world->gas[i].timeToStay; 
					}
				}
			}

		}
	}
	
	//On map stuffs 
	for(int y = 2; y < world->map.h - 2; y++){
		for(int x = 2; x < world->map.w - 2; x++){
			if(world->gasMap[y][x].type != gasNo){
				int i = rand()%8;
				//Efects for gass 
				int ent = is_monster_on_position(world, x, y);
				if(ent != -1){
				switch (world->gasMap[y][x].type){
					
					case gasSwamp:{
						//IF on fire spawn fire around 8 tiles if gasSwamp
						if(world->map.walling[y][x] == Tile_Fire || world->map.walling[y][x] == Tile_Lava){
							//exit(-1);
							//MESSAGE("Gas fire ON LAVA");
							world->map.walling[y][x] = Tile_Fire;
							world->gasMap[y][x].type = gasNo;
							for(int j = 0; j < 8; j++){
								const int xG = x + dirs[j][0];
								const int yG = y + dirs[j][1];
								if(world->gasMap[yG][xG].type == gasSwamp){
									world->map.walling[yG][xG] = Tile_Fire;
									world->gasMap[yG][xG].type = gasNo;
							//		MESSAGE("Gas fire");
								}
							}
						}


						break;
					}

					case gasHealing:{
						int incr = rand()%5;
						world->health[ent].current+= incr;
						CLAMP(world->health[ent].current, 0, world->health[ent].max);
						if(ent == 0)
							MESSAGE_F("You are in heal gas you get %d", incr);		
						break;
						}	
					case gasPoison:{

					
						int dec = rand()%10;
						world->health[ent].current-= dec;
						if(world->status[ent].poisonImune == false)
							world->status[ent].poisonTurn+=1;
						CLAMP(world->health[ent].current, 1, world->health[ent].max);
						if(ent == 0){
							MESSAGE_F("You are in poison");
							if(dec != 0)
								MESSAGE_F("You take %d dmg", dec);
						}		
						break;	
						}
					case gasAcid:{

					
						int decA = rand()%2;
						//Special for player accid of armor
						if(ent == 0 && rand_f32() < CHANCE_ACID_ITEM){
							for(int j = 0; j < world->inventory[0].count; j++){
								const Item item = world->inventory[0].items[j];
								
								if(item.isEqu == true && item.to == EQUIPTED_ARMOR){
									if(item.value > 0){
										world->inventory[0].items[j].value-=1;
										MESSAGE("Your armor take 1 dmg");
									}
								}
							}
						}
						world->health[ent].current-= decA;
						CLAMP(world->health[ent].current, 1, world->health[ent].max);
						if(ent == 0){
							MESSAGE("You are in acid gas");
							if(decA != 0)
								MESSAGE_F("You take %d dmg", decA);
						}
	
						break;
						}
					case gasStun:{

					
						int stun = rand()%10;
						world->state[ent].current = STATE_STUN;
						world->state[ent].stunTurn += stun;
						CLAMP(world->state[ent].stunTurn, 0, 10);
						if(ent == 0){
							MESSAGE_F("You are in black gas");
							MESSAGE("You are stuned");
						}		
						break;	
					}	
					//ca
					default:
						break;
				}
				}	

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




//Let for now just for player and block all other
#define CHANCE_DROWN 0.99f
#define CHANCE_WASH_ITEM 0.99f
void water_system(World *world, EngineData* engine){
	//for(int)
	const int x = (int)world->position[0].x;
	const int y = (int)world->position[0].y;
	if(world->map.walling[y][x] == Tile_Dwater && world->status[0].levitationTurn <= 0){
		
		MESSAGE("You are in deep water");
		const float chanceDrown = rand_f32();
		const float chanceWash  = rand_f32();
		if(CHANCE_DROWN >= chanceDrown){
			MESSAGE("Stream pull you");
			int dmg = rand()%20;
			MESSAGE_F("You take %d dmg", dmg);
			world->health[0].current -= dmg;
			CLAMP(world->health[0].current, 0, world->health[0].max);
		}
		if(CHANCE_WASH_ITEM >= chanceWash && world->inventory[0].count > 0){
			int item = rand()%world->inventory[0].count;
			MESSAGE_F("Stream pull item %s", world->inventory[0].items[item].name);
			da_remove_unordered(&world->inventory[0], item);


		}
	}
	//Tbd check this stuffs 
	for(int i = 0; i < MAX_ENTITIES; i++){
		if(world->map.walling[y][x] == Tile_Water && world->status[i].levitationTurn <= 0 && world->fire[i].isOnFire > 0){
			world->fire[i].isOnFire = false;
		}
	}

	DROP(engine);
}

void fire_system(World *world, EngineData* engine){
	CompMask mask = COMP_POSITION;
	
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
	for(int y = 0; y < world->map.h; y++){
		for(int x = 0; x < world->map.w; x++){
			if(world->map.walling[y][x] == Tile_Fire && rand_f32() < 0.33f){
				world->map.walling[y][x] = Tile_Dirt;

			}
		}
	}


	for(int i = 0; i < MAX_ENTITIES; i++){
		if((world->masks[i] & mask) == mask){
			if(rand_f32() < 0.25f)
				world->fire[i].isOnFire = false;
				
			const Position p = world->position[i];
			const int x = ((int)p.x % (world->map.w - 1));
			const int y = ((int)p.y % (world->map.h - 1));
			if(world->map.walling[y][x] == Tile_Dwater || world->map.walling[y][x] == Tile_Water){
				world->fire[i].isOnFire = false;
			}

			if(world->fire[i].isOnFire == true){
				int dmg = rand()%10;
				world->health[i].current -= dmg;
				CLAMP(world->health[i].current, 0, world->health[i].max);
				if(i == 0)
					MESSAGE_F("You took %d dmg from fire", dmg);
				if(world->renderable[i].type == S_Plant || world->renderable[i].type == S_PlantBig){
					destroy_entity(world, i);
					
				}				
				if(world->map.walling[y][x] == TIle_Grass){
					world->map.walling[y][x] = Tile_Fire;
				}
			}
			if(world->map.walling[y][x] == Tile_Lava || world->map.walling[y][x] == Tile_Fire){
				//Tbd imune to fire 
				if(i == 0)
					MESSAGE("You are in fire");
				if(world->fire[i].imuneToFire == false && world->status[i].levitationTurn <= 0){
					world->fire[i].isOnFire = true;
					if(world->map.walling[y][x] != Tile_Lava  && world->status[i].levitationTurn <= 0)
						world->map.walling[y][x] = Tile_Fire;

					Clamp(world->health[i].current, 0, world->health[i].max);
					for(int j = 0; j < 8; j++){
						int ent = is_position_on_position(world, x+dirs[j][0], y+dirs[j][1]);
						//If is renderable	
						if(ent  != -1){
							//SPREED FIRE
							if(rand_f32() < 0.9f){
								if(world->fire[ent].imuneToFire == false && world->status[i].levitationTurn <= 0)
						//			world->fire[ent].isOnFire = true;
								if(world->map.walling[y+dirs[j][1]][x+dirs[j][0]] != Tile_Lava && world->status[i].levitationTurn <= 0)
									world->map.walling[y+dirs[j][1]][x+dirs[j][0]] = Tile_Fire;
									//MESSAGE("Spreding");
							}
						}
					}
				}
			}
			
		}
	}
}



void trap_system(World* world, Global_Ent_DA *ent, EngineData* engine){
	CompMask mask = COMP_MONSTER;
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

	for(int i = 0; i < MAX_ENTITIES; i++){
		if(i == 0 || ((world->masks[i] & mask) == mask)){
			const int x = (int)world->position[i].x;
			const int y = (int)world->position[i].y;
			if(world->trapMap[y][x].trap != TRAP_NO){
				switch (world->trapMap[y][x].trap){
					case TRAP_POISON:
						world->gasMap[y][x] = (Gas){gasPoison, 0, world->trapMap[y][x].value, RED};	
						if(rand_f32() < 0.5f)
							world->trapMap[y][x].trap = TRAP_NO;		
						break; 
					case TRAP_ACID:
						world->gasMap[y][x] = (Gas){gasAcid, 0, world->trapMap[y][x].value, RED};	
						if(rand_f32() < 0.5f)
							world->trapMap[y][x].trap = TRAP_NO;
						break; 
					case TRAP_FIRE:
						world->map.walling[y][x] = Tile_Fire;
						world->trapMap[y][x].trap = TRAP_NO;
						break;
					case TRAP_STUN:
						world->state[i].stunTurn = world->trapMap[y][x].value;
						world->state[i].current  = STATE_STUN;
						world->trapMap[y][x].trap = TRAP_NO;
						break;
					case TRAP_TELEPORT:{

					
						int xT  = 0, yT = 0;
						while(1){
							xT = rand()%(world->map.w - 2) + 1;
							yT = rand()%(world->map.h - 2) + 1;
							if(world->map.walling[yT][xT] == Tile_Dirt || world->map.walling[yT][xT] == TIle_Grass 
								|| world->map.walling[yT][xT] == Tile_Water){
								break;
							}
						}
						
						world->position[i] = (Position){(float)xT, (float)yT};
						if(i == 0){
							engine->nextPosition = (Vector3){(float)xT, 0.6, (float)yT};
							MESSAGE("You are teleported");
						}
						break;
						}
					case TRAP_BEAR:
						world->health[i].current -= world->trapMap[y][x].value;
						CLAMP(world->health[i].current, 0, world->health[i].max);
						if(i == 0){
							MESSAGE("You steped in bear trap");
							MESSAGE_F("You took %d dmg", world->trapMap[y][x].value);
						}	
						if(rand_f32() < 0.1f)
							world->trapMap[y][x].trap = TRAP_NO;
						break;
					case TRAP_SUMMON:{
						world->trapMap[y][x].trap = TRAP_NO;
						int to = world->trapMap[y][x].value;	
						int is = -1;
						float x = 0;
						float y = 0;
						for(int j = 0; j < 8; j++){
							
							x = world->position[0].x + dirs[j][0];
							y = world->position[0].y + dirs[j][0];
							//MESSAGE_F("%f %f", x, y)
							is = is_monster_on_position(world, x, y);
							if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
								break;
								//MESSAGE("Summon");
							}

						}
						if(is == -1){
							MESSAGE("You step on summon trap");
							const Vector2 pos  = (Vector2){x, y}; 
							const int monster = create_entity(world); 
							add_components_to_ent_depending_on_T(world, ent, monster, to, pos);
							world->state[monster].current = STATE_HUNTING;
							world->spell[monster].type = Spell_No;
						}
						else{
							//MESSAGE("No ");
						}
						break;
					
					}	
					
					default:
						break;
					}
			}

		}
	}
	DROP(engine);
}


void status_system(World* world, EngineData* engine){
	for(int i = 0; i < MAX_ENTITIES; i++){
		if((world->masks[i] & COMP_STATUS) == COMP_STATUS){
			if(world->status[i].poisonTurn > 0){
				world->status[i].poisonTurn--;
				const int dmg = rand()%4;
				world->health[i].current-=dmg;
				CLAMP(world->health[i].current, 0, world->health[i].max);
				if(i == 0){
					MESSAGE_F("You took a %d dmg by poison", dmg);
				}
			}
			if(world->status[i].confusionTurn > 0){
				world->status[i].confusionTurn--;
				//MESSAGE_F("You are confuse %d", world->status[i].confusionTurn);
				if(i == 0){
					MESSAGE_F("You are confuse");
				}
			}
			if(world->status[i].hallucinationTurn > 0){
				world->status[i].hallucinationTurn--;
				if(i == 0)
				MESSAGE_F("You halucinating");
			}
			if(world->status[i].levitationTurn > 0){
				world->status[i].levitationTurn--;
				//MESSAGE_F("You are confuse %d", world->status[i].confusionTurn);
				if(i == 0){
					MESSAGE_F("You are levitating for %d turn", world->status[i].levitationTurn);
				}
			}
			if(world->status[i].telepatyTurn > 0){
				world->status[i].telepatyTurn--;
				//MESSAGE_F("You are confuse %d", world->status[i].confusionTurn);
				if(i == 0){
					//MESSAGE_F("You are levitating for %d turn", world->status[i].levitationTurn);
				}
			}
			
		}
	}
	DROP(engine);
}

#define VALUE_IDENTF 5
void scroll_system(World *world, Global_Ent_DA *ent, EngineData* engine){
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
	

	if(engine->whatAction == EQUIPTED_USE_SCROL){
		const Item item = world->inventory[0].items[engine->itemAction];
		MESSAGE("Scroll");
		if(item.isCursed == false){
		switch (item.scroll)
		{
		case Scroll_Fate:{
			while(1){
                world->inventory[0].items[engine->itemAction].scroll = rand()%Scroll_Num;
                if(world->inventory[0].items[engine->itemAction].scroll != Scroll_No 
					&& world->inventory[0].items[engine->itemAction].scroll != Scroll_Fate)
                    break;
            }
			world->identScrools[Scroll_Fate] = true;
			scroll_system(world, ent, engine);
			break;
		}

		case Scroll_Teleport:{
			if(world->identScrools[item.scroll] == false){
				MESSAGE("This is the teleport scroll");
				world->identScrools[item.scroll] = true;

			}
			int is = false;
			while(!is){
				int x = rand()%(world->map.w - 1);
				int y = rand()%(world->map.h - 1);
				if(world->map.walling[y][x] == ' '){
					is = true;
					MESSAGE("YOu have been teleported");
					world->position[0] = (Position){(float)x, (float)y};
					engine->nextPosition = (Vector3){(float)x, 0.6, (float)y};
					engine->isMoving = true;
				}
				
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Identif:{
			MESSAGE("You used a scroll of identify");
			MESSAGE("Check the inventory to see what is identif");
			for(int i = 0; i < world->inventory[0].count; i++){
				
				if(world->inventory[0].items[i].isIdent == false){
					//ROll D1_(Int)
					int intel = rand()%world->stats[0].inte;
					if(intel >= VALUE_IDENTF){
						world->inventory[0].items[i].isIdent = true;
						if(world->inventory[0].items[i].type == Scroll){
							world->identScrools[world->inventory[0].items[i].scroll] = true;
						}
						else if(world->inventory[0].items[i].type == Potion){
							world->identPotions[world->inventory[0].items[i].potion] = true;
						}
					}
				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}			

		case Scroll_EnchantW:{
			MESSAGE("You used a scroll of enchant wepon");
			world->identScrools[Scroll_EnchantW] = true;
			for(int i = 0; i < world->inventory[0].count; i++){
				
				if(world->inventory[0].items[i].isEqu == true &&  world->inventory[0].items[i].to == EQUIPTED_WEPON){
					world->inventory[0].items[i].isIdent = true;
					const float chance = rand_f32();
					//Str
					if(chance <= 0.4f){
						world->inventory[0].items[i].stats.str+=1;
					}
					//Dex
					else if(chance > 0.4 && chance <= 0.5f){
						world->inventory[0].items[i].stats.dex+=1;
					}
					//Int
					else if(chance > 0.5 && chance <= 0.55f){
						world->inventory[0].items[i].stats.inte+=1;
					}
					//Cons
					else if(chance > 0.55 && chance <= 0.6f){
						world->inventory[0].items[i].stats.cons+=1;
					}
					//Dmg
					else if(chance > 0.6 && chance <= 0.95f){
						world->inventory[0].items[i].value+=1;
					}
					//Dice // 5%
					else{
						world->inventory[0].items[i].nDice+=1;
					}

				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
			case Scroll_EnchantA:{
			MESSAGE("You used a scroll of enchant armor");
			world->identScrools[Scroll_EnchantA] = true;
			for(int i = 0; i < world->inventory[0].count; i++){
				
				if(world->inventory[0].items[i].isEqu == true &&  world->inventory[0].items[i].to == EQUIPTED_ARMOR){
					world->inventory[0].items[i].isIdent = true;
					const float chance = rand_f32();
					//Str
					if(chance <= 0.4f){
						world->inventory[0].items[i].stats.str+=1;
					}
					//Dex
					else if(chance > 0.4 && chance <= 0.5f){
						world->inventory[0].items[i].stats.dex+=1;
					}
					//Int
					else if(chance > 0.5 && chance <= 0.55f){
						world->inventory[0].items[i].stats.inte+=1;
					}
					//Cons
					else if(chance > 0.55 && chance <= 0.6f){
						world->inventory[0].items[i].stats.cons+=1;
					}
					//Dmg
					else if(chance > 0.6 && chance <= 0.95f){
						world->inventory[0].items[i].value+=1;
					}
					//Dice // 5%
					else{
						world->inventory[0].items[i].nDice+=1;
					}

				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
	
		case Scroll_SummonMonster:{
		
		MESSAGE("You used a scroll of summon monster");
		world->identScrools[Scroll_SummonMonster] = true;
		int is = -1;
		float x = 0;
		float y = 0;
		for(int j = 0; j < 8; j++){
			
			x = world->position[0].x + dirs[j][0];
			y = world->position[0].y + dirs[j][0];
			//MESSAGE_F("%f %f", x, y)
			is = is_monster_on_position(world, x, y);
			if(is == -1 && (world->map.walling[(int)y][(int)x] != '#')){
				break;
				//MESSAGE("Summon");
			}

		}
		if(is == -1){
			const Vector2 pos  = (Vector2){x, y}; 
			const int monster = create_entity(world); 
			int type = rand()%(Monster_Num-1)  + 1;
			add_components_to_ent_depending_on_T(world, ent, monster, type, pos);
			world->state[monster].current = STATE_HUNTING;
			//world->spell[monster].type = Spell_No;
			//MESSAGE_F("Sumoon %d/%d", world->spell[i].passTurn, world->spell[i].cooldown);
			world->spell[monster].passTurn = 0;
		}
		else{
			//MESSAGE("No ");
		}
		free_item(&world->inventory[0], engine->itemAction);
		break;
	}
		case Scroll_Acq:{
			MESSAGE("You used a scroll of acquairmenent");
			MESSAGE("Check the inventory to see what item you got");
			world->identScrools[Scroll_Acq] = true;
			float chance = rand_f32();
			//Item
			if(chance <= 0.6){
				int type = rand()%Item_Num;
				add_item_to_inventory(type, &world->inventory[0], Scroll_No,  Potion_No, false, false);

			}
			else{
				int scrollType = rand()%Scroll_Num;
				add_item_to_inventory(Scroll, &world->inventory[0], scrollType,  Potion_No, false, false);
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
		case Scroll_Stun:
		case Scroll_Scare:
		case Scroll_Hunt:
		case Scroll_Confuse:
		case Scroll_Negation:
		case Scroll_Incinarat:
		case Scroll_Sacrifice:{
			world->identScrools[item.scroll] = true;
			switch (item.scroll){
				case Scroll_Stun:
					MESSAGE("This is the scroll of stun");
					break;
				case Scroll_Scare:
					MESSAGE("This is the scroll of scare");
					break;
				case Scroll_Confuse:
					MESSAGE("This is the scroll of confusion");
					break;
				
				case Scroll_Hunt:
					MESSAGE("This is the scroll of hunting");
					break;
			
				case Scroll_Negation:
					MESSAGE("This is the scroll of negation");
					break;
				
				case Scroll_Incinarat:
					MESSAGE("This is the scroll of incineration");
					break;	
				case Scroll_Sacrifice:
					MESSAGE("This is the scroll of sacrifice");
					break;	
					
					default:
						ASSERT("NO he");
						break;
					}

			//Loop thru all and then on type do the efects
			for(int i = 1; i < MAX_ENTITIES; i++){
				if((COMP_MONSTER & world->masks[i]) == COMP_MONSTER){
					switch (item.scroll)
					{
					case Scroll_Stun:
						world->state[i].current = STATE_STUN;
						world->state[i].stunTurn+=rand()%20;
						break;
					case Scroll_Scare:
						world->state[i].current = STATE_RUNING;
						world->state[i].chancesH = 0;
						world->state[i].chancesRe = 0;
						world->state[i].chancesW = 0;
						world->state[i].chanceRange = 0;
						world->state[i].chancesR = 0.99f;
						break;
					case Scroll_Confuse:
						if(world->status[i].confusionImune == false)
							world->status[i].confusionTurn += rand()%20;
						break;
				
					case Scroll_Hunt:
						world->state[i].current = STATE_HUNTING;
						world->state[i].chancesH = 0.99;
						world->state[i].chancesRe = 0;
						world->state[i].chancesW = 0;
						world->state[i].chanceRange = 0;
						world->state[i].chancesR = 0.00f;
						break;
					//WHat negate
					case Scroll_Negation:
						if(world->renderable[i].type == S_ObsidanStatue || world->renderable[i].type == S_Garg)
						{
							const float dist = Vector2DistanceSqr((Vector2)world->position[0], (Vector2)world->position[i]);
							//100 Distance
							if(dist <= 100)
								destroy_entity(world, i);
						
						}
						break;	

						case Scroll_Incinarat:
						//if(world->renderable[i].type == S_ObsidanStatue || world->renderable[i].type == S_Garg)
						{
							const float dist = Vector2DistanceSqr((Vector2)world->position[0], (Vector2)world->position[i]);
							//100 Distance
							if(dist <= 100)
								if(world->fire[i].imuneToFire == false){
									const int chanceM = rand()%world->stats[i].inte;
									const int chanceP = rand()%world->stats[0].inte;
									if(chanceP > chanceM)
										world->fire[i].isOnFire = true;
								}								
						
						}
						break;	

						case Scroll_Sacrifice:{
							const float dist = Vector2DistanceSqr((Vector2)world->position[0], (Vector2)world->position[i]);
							
							if(dist <= 4){
								//1 str 2 dex 3 int 4 const 5 maxHealth - 5
							int whatStats = rand()%4;
							switch (whatStats){
							case 1:
								world->stats[0].str--;
								CLAMP(world->stats[0].str, 1, 25);
								break;
							case 2:
								world->stats[0].dex--;
								CLAMP(world->stats[0].dex, 1, 25);
								break;	
							case 3:
								world->stats[0].inte--;
								CLAMP(world->stats[0].inte, 1, 25);
								break;
							case 0:
								world->health[0].max-=5;
								world->health[0].current-=5;
								CLAMP(world->health[0].max, 1, 100000);
								CLAMP(world->health[0].current, 0, world->health[0].max);
								break;	
							default:
								break;
							}
							
							destroy_entity(world, i);
							}
								
						
						}
						break;	

					
					default:
						ASSERT("NO he");
						break;
					}
				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}

		case Scroll_Levitation:{
			MESSAGE("You used a scroll of levitation");
			world->status[0].levitationTurn+= 10 + rand()%5;
			world->identScrools[Scroll_Levitation] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
		case Scroll_Telepaty:{
			MESSAGE("You used a scroll of telepaty");
			world->status[0].telepatyTurn+= 10 + rand()%5;
			world->identScrools[Scroll_Telepaty] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
		case Scroll_Water:{
			MESSAGE("You used a scroll of water");
			//world->status[0].telepatyTurn+= 10 + rand()%5;
			const int x = (int)world->position[0].x;
			const int y = (int)world->position[0].y;
			world->map.walling[y][x] = Tile_Water;
			world->identScrools[Scroll_Water] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_MagicMaping:{
			MESSAGE("You used a scroll of magic maping");
			world->identScrools[Scroll_MagicMaping] = true;
			for(int y = 0; y < world->map.h; y++){
				for(int x = 0; x < world->map.w; x++){
					world->isExpMap[y][x] = 1;
				}
			}
			world->identScrools[Scroll_Amnesia] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Recharging:{
			MESSAGE("You used a scroll of recharging");
			MESSAGE("You fill a refreshed");
			world->health[0].current = world->health[0].max;
			world->status[0].confusionTurn = 0;
			world->status[0].poisonTurn = 0;
			world->status[0].poisonTurn = 0;
			world->fire[0].isOnFire = false;
			world->state[0].stunTurn = 0;
			world->identScrools[Scroll_Recharging] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Amnesia:{
			MESSAGE("You used a scroll of amnesia");
			world->status[0].confusionTurn = 0;
			world->identScrools[Scroll_MagicMaping] = true;
			for(int y = 0; y < world->map.h; y++){
				for(int x = 0; x < world->map.w; x++){
					world->isExpMap[y][x] = 0;
				}
			}
			for(int j = 0; j < Scroll_Num; j++){
				world->identScrools[j] = false;
			}
			for(int j = 0; j < world->inventory[0].count; j++){
				world->inventory[0].items[j].isIdent = false;
			}
			//Tbd other stuffs
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
		case Scroll_Gambler:{
			MESSAGE("You used a scroll of gambling");
			int whatStats = rand()%4;
			switch (whatStats){
				case 1:
					world->stats[0].str = rand()%18;
					CLAMP(world->stats[0].str, 1, 25);
					MESSAGE_F("Str %d", world->stats[0].str);
					break;
				case 2:
					world->stats[0].dex = rand()%18;;
					CLAMP(world->stats[0].dex, 1, 25);
					MESSAGE_F("Dex %d", world->stats[0].dex);
					break;	
				case 3:
					world->stats[0].inte = rand()%18;;
					CLAMP(world->stats[0].inte, 1, 25);
					MESSAGE_F("Inte %d", world->stats[0].inte);
					break;
				case 0:
					world->stats[0].cons = rand()%18;
					CLAMP(world->stats[0].cons, 1, 25);
					MESSAGE_F("Cons %d", world->stats[0].cons);
					break;
					
				default:
					break;
				}
			world->identScrools[Scroll_Gambler] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}	
		case Scroll_Calcific:{
			MESSAGE("You used a scroll of calfication");
			world->identScrools[Scroll_Calcific] = true;
			for(int y = 0; y < world->map.h; y++){
				for(int x = 0; x < world->map.w; x++){
					if(world->map.walling[y][x] == Tile_Caz){
						world->map.walling[y][x] = Tile_Dirt;
					}
				}
			}
			//world->identScrools[Scroll_Amnesia] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}

		case Scroll_Bprince:{
			MESSAGE("You used a scroll of blod princ");
			//world->identScrools[Scroll_Calcific] = true;
			free_item(&world->inventory[0], engine->itemAction);
			for(int j = 0; j < world->inventory[0].count; j++){
				if(rand_f32() < 0.5f){
					free_item(&world->inventory[0], j);
					j--;
					//break;
				}
			}
			world->health[0].current+=15;
			world->health[0].max+=15;
			world->identScrools[Scroll_Bprince] = true;
			
			break;
		}
		case Scroll_RemoveCurse:{
			MESSAGE("You used a scroll of remove curse");
			
			for(int i = 0; i < world->inventory[0].count; i++){
				if(rand_f32() < 0.33f)
					world->inventory[0].items[i].isCursed = false;
				
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
		default:
			ASSERT("Not implemented");
			break;
		}
		}
		else{
		switch (item.scroll)
		{
		case Scroll_Fate:{
			MESSAGE("This is cursed scroll of fate");
			MESSAGE("You felt weaker");
			world->identScrools[Scroll_Fate] = true;
			world->health[0].max -=10;
			CLAMP(world->health[0].max, 0, 1000000);
			world->health[0].current -=10;
			CLAMP(world->health[0].current, 0, 1000000);
			world->identScrools[Scroll_Fate] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Identif:{
			MESSAGE("You used a cursed scroll of identify");
			MESSAGE("Check the inventory to see what is non identif");
			for(int i = 0; i < world->inventory[0].count; i++){
				
				if(world->inventory[0].items[i].isIdent == false){
					//ROll D1_(Int)
					int intel = rand()%world->stats[0].inte;
					if(intel >= VALUE_IDENTF){
						world->inventory[0].items[i].isIdent = false;
						if(world->inventory[0].items[i].type == Scroll){
							world->identScrools[world->inventory[0].items[i].scroll] = false;
						}
					}
				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}	
		case Scroll_Teleport:{
			if(world->identScrools[item.scroll] == false){
				MESSAGE("This is the cursed  teleport scroll");
				world->identScrools[item.scroll] = true;

			}
			//Tbd lower level 
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}		
		
		case Scroll_EnchantW:{
			MESSAGE("You used a cursed scroll of enchant wepon");
			world->identScrools[Scroll_EnchantW] = true;
			
			for(int i = 0; i < world->inventory[0].count; i++){
				
				if(world->inventory[0].items[i].isEqu == true &&  world->inventory[0].items[i].to == EQUIPTED_WEPON){
					world->inventory[0].items[i].isCursed = true;
					world->inventory[0].items[i].isIdent = true;
					
					const float chance = rand_f32();
					//Str
					if(chance <= 0.4f){
						world->inventory[0].items[i].stats.str-=2;
					}
					//Dex
					else if(chance > 0.4 && chance <= 0.5f){
						world->inventory[0].items[i].stats.dex-=1;
					}
					//Int
					else if(chance > 0.5 && chance <= 0.55f){
						world->inventory[0].items[i].stats.inte-=1;
					}
					//Cons
					else if(chance > 0.55 && chance <= 0.6f){
						world->inventory[0].items[i].stats.cons-=1;
					}
					//Dmg
					else if(chance > 0.6 && chance <= 0.95f){
						world->inventory[0].items[i].value-=1;
					}
					//Dice // 5%
					else{
						world->inventory[0].items[i].nDice-=1;
					}

				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		
			case Scroll_EnchantA:{
			MESSAGE("You used cursed scroll of enchant armor");
			world->identScrools[Scroll_EnchantA] = true;
			for(int i = 0; i < world->inventory[0].count; i++){
				
				if(world->inventory[0].items[i].isEqu == true &&  world->inventory[0].items[i].to == EQUIPTED_ARMOR){
					world->inventory[0].items[i].isIdent = true;
					world->inventory[0].items[i].isCursed = true;
					const float chance = rand_f32();
					//Str
					if(chance <= 0.4f){
						world->inventory[0].items[i].stats.str-=2;
					}
					//Dex
					else if(chance > 0.4 && chance <= 0.5f){
						world->inventory[0].items[i].stats.dex-=2;
					}
					//Int
					else if(chance > 0.5 && chance <= 0.55f){
						world->inventory[0].items[i].stats.inte+=1;
					}
					//Cons
					else if(chance > 0.55 && chance <= 0.6f){
						world->inventory[0].items[i].stats.cons+=1;
					}
					//Dmg
					else if(chance > 0.6 && chance <= 0.95f){
						world->inventory[0].items[i].value+=1;
					}
					//Dice // 5%
					else{
						world->inventory[0].items[i].nDice+=1;
					}

				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Acq:{
			MESSAGE("You used cursed scroll of acquiremnet");
			world->identScrools[Scroll_Acq] = true;
			free_item(&world->inventory[0], engine->itemAction);
			for(int i = 0; i < world->inventory[0].count; i++){
				if(rand_f32() < 0.5f){
				free_item(&world->inventory[0], i);
				if(rand_f32() < 0.89f)
					break;		
				}
			}
			
			break;
		}
		case Scroll_Stun:{
			world->identScrools[Scroll_Stun] = true;
			free_item(&world->inventory[0], engine->itemAction);
			MESSAGE("You used cursed scroll of stun;");
			world->state[0].current = STATE_STUN;
			world->state[0].stunTurn+=rand()%20;
			break;
		}
			
		case Scroll_Confuse:{
			world->identScrools[Scroll_Confuse] = true;
			free_item(&world->inventory[0], engine->itemAction);
			MESSAGE("You used cursed scroll of confusion;");
			//world->state[0].current = STATE_STUN;
			if(world->status[0].confusionImune == false)
				world->status[0].confusionTurn+=rand()%10;
			break;
		}
		case Scroll_Negation:{
				world->identScrools[Scroll_Negation] = true;
				free_item(&world->inventory[0], engine->itemAction);
				MESSAGE("You used cursed scroll of negation");
				//Tbd summon gargs
				break;
		}
		case Scroll_Incinarat:{
			world->identScrools[Scroll_Incinarat] = true;
			free_item(&world->inventory[0], engine->itemAction);
			MESSAGE("You used cursed scroll of incineration;");
			//world->state[0].current = STATE_STUN;
			if(world->fire[0].imuneToFire == false)
				world->fire[0].isOnFire = true;
			break;
		}
		case Scroll_MagicMaping:{
			MESSAGE("You used a cursed scroll of magic maping");
			world->identScrools[Scroll_MagicMaping] = true;
			for(int y = 0; y < world->map.h; y++){
				for(int x = 0; x < world->map.w; x++){
					world->isExpMap[y][x] = 0;
				}
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Recharging:{
			MESSAGE("You used a cursed  scroll of recharging");
			world->health[0].current = 10;
			if(rand_f32() < 0.5f)
			world->status[0].confusionTurn = 5;
			world->identScrools[Scroll_Recharging] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Bprince:
		case Scroll_Sacrifice:{
			MESSAGE("You used a cursed  scroll");
			world->health[0].current = 0;
			world->identScrools[Scroll_Bprince] = true;
			world->identScrools[Scroll_Sacrifice] = true;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_Calcific:{
			MESSAGE("You used a cursed  scroll of calcification");
			const int x = (int)world->position[0].x;
			const int y = (int)world->position[0].y;
			world->identScrools[Scroll_Calcific] = true;
			world->map.walling[y][x] = Tile_Caz;
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}
		case Scroll_RemoveCurse:{
			MESSAGE("You used a cursed scroll of remove curse");
			
			for(int i = 0; i < world->inventory[0].count; i++){
				if(rand_f32() < 0.33f)
					world->inventory[0].items[i].isCursed = true;

				
			}
			free_item(&world->inventory[0], engine->itemAction);
			break;
		}



			default:
				free_item(&world->inventory[0], engine->itemAction);
				MESSAGE("Nothing hapends");
				break;
		}
	}
		engine->whatAction = EQUIPTED_ARMOR;
		engine->itemAction = 0;
	}

}

void potion_system(World *world, EngineData *engine){
	if(engine->whatAction == EQUIPTED_USE_POTION){
		const Item item = world->inventory[0].items[engine->itemAction];
		world->identPotions[item.potion] = true;
		MESSAGE("Potion");
		switch (item.potion)
		{
			case Potion_Healing:{
				int health = 5 + rand()%10;
				if(item.isCursed == true){
					MESSAGE("You used cursed potion of healing");
					world->health[0].current -= health;
				}
				else{
					MESSAGE("You used potion of healing");
					world->health[0].current += health;
				}
				CLAMP(world->health[0].current, 0, world->health[0].max);
				free_item(&world->inventory[0], engine->itemAction);

				break;
			}
			case Potion_Str:{
				//int str = 5 + rand()%10;
				if(item.isCursed == true){
					MESSAGE("You used cursed potion of strenght");
					world->stats[0].str--;
				}
				else{
					MESSAGE("You used potion of strenght");
					world->stats[0].str++;
				}
				CLAMP(world->stats[0].str, 0, 25);
				free_item(&world->inventory[0], engine->itemAction);
				break;	
			}
			case Potion_Int:{
				//int str = 5 + rand()%10;
				if(item.isCursed == true){
					MESSAGE("You used cursed potion of intelegenc");
					world->stats[0].inte--;
				}
				else{
					MESSAGE("You used potion of int");
					world->stats[0].inte++;
				}
				CLAMP(world->stats[0].inte, 0, 25);
				free_item(&world->inventory[0], engine->itemAction);
				break;	
			}	
			case Potion_Size:{
				//int str = 5 + rand()%10;
				if(item.isCursed == true){
					MESSAGE("You used cursed potion of size");
					world->stats[0].cons--;
				}
				else{
					MESSAGE("You used potion of size");
					world->stats[0].cons++;
				}
				CLAMP(world->stats[0].cons, 0, 25);
				free_item(&world->inventory[0], engine->itemAction);
				break;
				}
			case Potion_Att:{
				//int str = 5 + rand()%10;
				if(item.isCursed == true){
					MESSAGE("You used cursed potion of att");
					world->stats[0].dmgMax--;
				}
				else{
					MESSAGE("You used potion of att");
					world->stats[0].dmgMax++;
				}
				CLAMP(world->stats[0].dmgMax, world->stats[0].dmgMin + 1, 25);
				free_item(&world->inventory[0], engine->itemAction);
				break;
				}
			case Potion_Def:{
				//int str = 5 + rand()%10;
				if(item.isCursed == true){
					MESSAGE("You used cursed potion of def");
					world->stats[0].defence--;
				}
				else{
					MESSAGE("You used potion of def");
					world->stats[0].defence++;
				}
				CLAMP(world->stats[0].defence, -25, 25);
				free_item(&world->inventory[0], engine->itemAction);
				break;	
			}	
			case Potion_Poison:{
				MESSAGE("You used a poison potion");
				const int x = (int)world->position[0].x;
				const int y = (int)world->position[0].y;
				world->gasMap[y][x] = (Gas){gasPoison, false, 1000, gasColor[gasPoison]};
				free_item(&world->inventory[0], engine->itemAction);
				break;}
			case Potion_Gas:{
				MESSAGE("You used a gas like potion");
				const int x = (int)world->position[0].x;
				const int y = (int)world->position[0].y;
				world->gasMap[y][x] = (Gas){gasSwamp, false, 1000, gasColor[gasSwamp]};
				free_item(&world->inventory[0], engine->itemAction);
				break;}	
			case Potion_Acid:{
				MESSAGE("You used a acid like potion");
				const int x = (int)world->position[0].x;
				const int y = (int)world->position[0].y;
				world->gasMap[y][x] = (Gas){gasAcid, false, 1000, gasColor[gasAcid]};
				free_item(&world->inventory[0], engine->itemAction);
				break;}	
			case Potion_HealingGas:{
				MESSAGE("You used a gas like healing potion");
				const int x = (int)world->position[0].x;
				const int y = (int)world->position[0].y;
				world->gasMap[y][x] = (Gas){gasHealing, false, 1000, gasColor[gasHealing]};
				free_item(&world->inventory[0], engine->itemAction);
				break;}	
				


			
			default:
				free_item(&world->inventory[0], engine->itemAction);
				break;
		}
	}
	engine->whatAction = EQUIPTED_ARMOR;
	engine->itemAction = 0;
}


void throw_system(World *world, EngineData *engine){
	if(engine->itemThrowId != -1){
		if(world->inventory[0].items[engine->itemThrowId].type == Potion)
		spawn_projectile(world, 0, P_Potion, engine->itemThrowId, engine);
		MESSAGE("Throw");
		engine->itemThrowId = -1;
	}
}