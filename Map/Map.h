#pragma once



typedef struct {
    char** tiles;
    int w;
    int h;
    // N, E, S, W doors
    int door_x[4];
    int door_y[4];
} BrogueRoom;


typedef struct
{
    char** walling;
    int h;
    int w;
}
Map;


Map xmgen(const int w, const int h, const int grid, const int max);
Map xmgen_graph(const int w, const int h, const int num_rooms, const int min_size, const int max_size, const int extra_connections);


//Map xmgen_bsp(const int w, const int h, const int min_room_size);


Map xmgen_drunk(const int w, const int h, float floor_goal_percent);

//Map xmgen_cellular(const int w, const int h, const float wall_percent, const int iterations);

Map xmgen_brogue(const int w, const int h, const int max_rooms, const int min_size, const int max_size);

//Map xmgen_perlin(const int w, const int h, const float threshold);

Map xmgen_maze(const int wR, const int hR, const int w, const int h);

Map xmgen_room_maze(const int wR, const int hR, const int w, const int h, const int num_rooms_to_try, const int min_room_size, const int max_room_size);

//Map xmgen_voronoi(const int w, const int h, const int num_seeds, const int min_room_size, const int max_room_size);


//Map xmgen_bsp_leaf(const int w, const int h, const int max_size,  const int min_size);

//Map xmgen_subtractive(const int w, const int h, const int carve_count);

//Map xmgen_rcd(const int w, const int h, const int num_rooms, const int min_size, const int max_size);

//Map xmgen_modules(const int w, const int h, const int num_modules);


void xmgen_add_lake(Map* map, char tile, int x, int y,  int w, int h, float lakePercent);
void xmgen_add_enviroment(Map* map, char tile, int x, int y,  int w, int h, float lakePercent);


void xmclose(const Map);

void xmprint(const Map);