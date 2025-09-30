#include "Map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define toss(t, n) ((t*) malloc((n) * sizeof(t)))
#define zero(a) (memset(&(a), 0, sizeof(a)))

typedef int (*const Direction)(const void*, const void*);

typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point* point;
    int count;
    int max;
} Points;

typedef struct {
    Point a;
    Point b;
    Point c;
} Tri;

typedef struct {
    Tri* tri;
    int count;
    int max;
} Tris;

typedef struct {
    Point zer;
    Point one;
} Flags;

static void bomb(const char* const message, ...) {
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    exit(1);
}

static char** reset(char** block, const int h, const int w, const int blok) {
    for (int row = 0; row < h; row++)
        for (int col = 0; col < w; col++)
            block[row][col] = blok;
    return block;
}

static char** bnew(const int h, const int w, const int blok) {
    char** block = toss(char*, h);
    for (int row = 0; row < h; row++)
        block[row] = toss(char, w);
    return reset(block, h, w, blok);
}

static Map mnew(const int h, const int w) {
    Map map;
    zero(map);
    map.h = h;
    map.w = w;
    map.walling = bnew(map.h, map.w, '#');
    return map;
}

static int psame(const Point a, const Point b) {
    return a.x == b.x && a.y == b.y;
}

static int fl(const float x) {
    return (int)x - (x < (int)x);
}

static Point snap(const Point a, const int grid) {
    const Point out = {
        (float)fl(a.x / grid) * grid,
        (float)fl(a.y / grid) * grid,
    };
    return out;
}

static Points psnew(const int max) {
    const Points ps = { toss(Point, max), 0, max };
    return ps;
}

static Points psadd(Points ps, const Point p) {
    if (ps.count == ps.max)
        bomb("points size limitation reached\n");
    ps.point[ps.count++] = p;
    return ps;
}

static int psfind(const Points ps, const Point p) {
    for (int i = 0; i < ps.count; i++)
        if (psame(ps.point[i], p))
            return true;
    return false;
}

static Tris tsnew(const int max) {
    const Tris ts = { toss(Tri, max), 0, max };
    return ts;
}

static Tris tsadd(Tris tris, const Tri tri) {
    if (tris.count == tris.max)
        bomb("tris size limitation reached\n");
    tris.tri[tris.count++] = tri;
    return tris;
}

static int reveql(const Tri a, const Tri b) {
    return psame(a.a, b.b) && psame(a.b, b.a);
}

static int foreql(const Tri a, const Tri b) {
    return psame(a.a, b.a) && psame(a.b, b.b);
}

static int alligned(const Tri a, const Tri b) {
    return foreql(a, b) || reveql(a, b);
}

static void emark(Tris edges, const Flags flags) {
    for (int i = 0; i < edges.count; i++) {
        const Tri edge = edges.tri[i];
        for (int j = 0; j < edges.count; j++) {
            if (i == j)
                continue;
            const Tri other = edges.tri[j];
            if (alligned(edge, other))
                edges.tri[j].c = flags.one;
        }
    }
}

static Tris ejoin(Tris tris, const Tris edges, const Point p, const Flags flags) {
    for (int j = 0; j < edges.count; j++) {
        const Tri edge = edges.tri[j];
        if (psame(edge.c, flags.zer)) {
            const Tri tri = { edge.a, edge.b, p };
            tris = tsadd(tris, tri);
        }
    }
    return tris;
}

static int outob(const Point p, const int w, const int h) {
    return p.x < 0 || p.y < 0 || p.x >= w || p.y >= h;
}

static int incircum(const Tri t, const Point p) {
    const float ax = t.a.x - p.x;
    const float ay = t.a.y - p.y;
    const float bx = t.b.x - p.x;
    const float by = t.b.y - p.y;
    const float cx = t.c.x - p.x;
    const float cy = t.c.y - p.y;
    const float det =
        (ax * ax + ay * ay) * (bx * cy - cx * by) -
        (bx * bx + by * by) * (ax * cy - cx * ay) +
        (cx * cx + cy * cy) * (ax * by - bx * ay);
    return det > 0.0f;
}

static Tris ecollect(Tris edges, const Tris in, const Flags flags) {
    for (int i = 0; i < in.count; i++) {
        const Tri tri = in.tri[i];
        const Tri ab = { tri.a, tri.b, flags.zer };
        const Tri bc = { tri.b, tri.c, flags.zer };
        const Tri ca = { tri.c, tri.a, flags.zer };
        edges = tsadd(edges, ab);
        edges = tsadd(edges, bc);
        edges = tsadd(edges, ca);
    }
    return edges;
}

static Tris delaunay(const Points ps, const int w, const int h, const int max, const Flags flags) {
    Tris in = tsnew(max);
    Tris out = tsnew(max);
    Tris tris = tsnew(max);
    Tris edges = tsnew(max);
    Tri* dummy = tris.tri;
    const Tri super = { { (float)-w, 0.0f }, { 2.0f * w, 0.0f }, { w / 2.0f, 2.0f * h } };
    tris = tsadd(tris, super);
    for (int j = 0; j < ps.count; j++) {
        in.count = out.count = edges.count = 0;
        const Point p = ps.point[j];
        for (int i = 0; i < tris.count; i++) {
            const Tri tri = tris.tri[i];
            if (incircum(tri, p))
                in = tsadd(in, tri);
            else out = tsadd(out, tri);
        }
        edges = ecollect(edges, in, flags);
        emark(edges, flags);
        out = ejoin(out, edges, p, flags);
        tris = out;
    }
    free(dummy);
    free(in.tri);
    free(edges.tri);
    return tris;
}

static Points prand(const int w, const int h, const int max, const int grid, const int border) {
    Points ps = psnew(max);
    for (int i = ps.count; i < ps.max; i++) {
        const Point p = {
            (float)(rand() % (w - border) + border / 2),
            (float)(rand() % (h - border) + border / 2),
        };
        const Point snapped = snap(p, grid);
        ps = psadd(ps, snapped);
    }
    return ps;
}

static Point sub(const Point a, const Point b) {
    const Point out = { a.x - b.x, a.y - b.y };
    return out;
}

static float mag(const Point a) {
    return sqrtf(a.x * a.x + a.y * a.y);
}

static float len(const Tri edge) {
    return mag(sub(edge.b, edge.a));
}

static int descending(const void* a, const void* b) {
    const Tri ea = *(const Tri*)a;
    const Tri eb = *(const Tri*)b;
    return len(ea) < len(eb) ? 1 : len(ea) > len(eb) ? -1 : 0;
}

static void sort(const Tris edges, const Direction direction) {
    qsort(edges.tri, edges.count, sizeof(Tri), direction);
}

static int connected(const Point a, const Point b, const Tris edges, const Flags flags) {
    Points todo = psnew(edges.max);
    Points done = psnew(edges.max);
    Tris reach = tsnew(edges.max);
    todo = psadd(todo, a);
    int connection = false;
    while (todo.count != 0 && connection != true) {
        const Point removed = todo.point[--todo.count];
        done = psadd(done, removed);
        reach.count = 0;
        for (int i = 0; i < edges.count; i++) {
            const Tri edge = edges.tri[i];
            if (psame(edge.c, flags.one))
                continue;
            if (psame(edge.a, removed))
                reach = tsadd(reach, edge);
        }
        for (int i = 0; i < reach.count; i++) {
            if (psame(reach.tri[i].b, b)) {
                connection = true;
                break;
            }
            if (!psfind(done, reach.tri[i].b))
                todo = psadd(todo, reach.tri[i].b);
        }
    }
    free(todo.point);
    free(reach.tri);
    free(done.point);
    return connection;
}

static void revdel(Tris edges, const int w, const int h, const Flags flags) {
    sort(edges, descending);
    for (int i = 0; i < edges.count; i++) {
        Tri* edge = &edges.tri[i];
        if (outob(edge->a, w, h)
            || outob(edge->b, w, h)) {
            edge->c = flags.one;
            continue;
        }
        edge->c = flags.one;
        if (!connected(edge->a, edge->b, edges, flags)) edge->c = flags.zer;
    }
}

static void mdups(const Tris edges, const Flags flags) {
    for (int i = 0; i < edges.count; i++)
        for (int j = 0; j < edges.count; j++) {
            if (psame(edges.tri[j].c, flags.one))
                continue;
            if (psame(edges.tri[i].c, flags.one))
                continue;
            if (reveql(edges.tri[i], edges.tri[j]))
                edges.tri[j].c = flags.one;
        }
}

static void mroom(const Map map, const Point where, const int w, const int h) {
    for (int i = -w; i <= w; i++)
        for (int j = -h; j <= h; j++) {
            const int xx = where.x + i;
            const int yy = where.y + j;
            if (yy >= 0 && yy < map.h && xx >= 0 && xx < map.w) {
                map.walling[yy][xx] = ' ';
            }
        }
}

static void mcorridor(const Map map, const Point a, const Point b) {
    const Point step = sub(b, a);
    const Point delta = {
        step.x > 0.0f ? 1.0f : step.x < 0.0f ? -1.0f : 0.0f,
        step.y > 0.0f ? 1.0f : step.y < 0.0f ? -1.0f : 0.0f,
    };
    const int sx = abs(step.x);
    const int sy = abs(step.y);
    const int dx = delta.x;
    const int dy = delta.y;
    int x = a.x;
    int y = a.y;
    for (int i = 0; i < sx; i++) {
        x += dx;
        if (y >= 0 && y < map.h && x >= 0 && x < map.w) {
            map.walling[y][x] = '+';
        }
    }
    for (int i = 0; i < sy; i++) {
        y += dy;
        if (y >= 0 && y < map.h && x >= 0 && x < map.w) {
            map.walling[y][x] = '+';
        }
    }
    if (y >= 0 && y < map.h && x >= 0 && x < map.w) {
        map.walling[y][x] = '*';
    }
}

static void mpillar(const Map map, const Point where, const int w, const int h) {
    int type = rand() % 3;
    if (type == 1) {
        int numPIllar = rand() % 10 + 2;
        for (int i = 0; i < numPIllar; i++) {
            int xx = where.x + rand() % w;
            int yy = where.y + rand() % h;
            if (yy >= 0 && yy < map.h && xx >= 0 && xx < map.w) {
                if (map.walling[yy][xx] == ' ') {
                    map.walling[yy][xx] = '#';
                }
            }
        }
    } else if (type == 2) {
        const int xx = where.x + w / 2;
        const int yy = where.y + h / 2;
        if (yy + 1 < map.h && xx + 1 < map.w && yy >= 0 && xx >= 0) {
            map.walling[yy][xx] = '#';
            map.walling[yy + 1][xx] = '#';
            map.walling[yy][xx + 1] = '#';
            map.walling[yy + 1][xx + 1] = '#';
        }
    }
}


static void bone(const Map map, const Tri e, const int w, const int h) {
    mroom(map, e.a, w, h);
    mpillar(map, e.a, w, h);
    mroom(map, e.b, w, h);
    mpillar(map, e.b, w, h);
    mcorridor(map, e.a, e.b);
}

static void carve(const Map map, const Tris edges, const Flags flags, const int grid) {
    for (int i = 0; i < edges.count; i++) {
        const Tri e = edges.tri[i];
        if (psame(e.c, flags.one))
            continue;
        const int min = 2;
        const int size = grid / 2 - min;
        const int w = min + rand() % size;
        const int h = min + rand() % size;
        bone(map, e, w, h);
    }
}

Map xmgen(const int w, const int h, const int grid, const int max) {
    srand(time(0));
    const Flags flags = { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
    const int border = 3 * grid;
    const Points ps = prand(w, h, max, grid, border);
    const Tris tris = delaunay(ps, w, h, 9 * max, flags);
    const Tris edges = ecollect(tsnew(27 * max), tris, flags);
    revdel(edges, w, h, flags);
    const Map map = mnew(h, w);
    mdups(edges, flags);
    carve(map, edges, flags, grid);
    free(tris.tri);
    free(ps.point);
    free(edges.tri);
    return map;
}

void xmclose(const Map map) {
    for (int row = 0; row < map.h; row++)
        free(map.walling[row]);
    free(map.walling);
}

void xmprint(const Map map) {
    for (int row = 0; row < map.h; row++)
        for (int col = 0; col < map.w; col++)
            printf("%c%s", map.walling[row][col], col == map.w - 1 ? "\n" : "");
    putchar('\n');
}

typedef struct {
    int x, y, w, h;
} Rect;
static Rect* room_list = NULL;
static int room_count = 0;

static void carve_room(Map map, Rect r) {
    int room_x = r.x + rand() % (r.w / 4) + 1;
    int room_y = r.y + rand() % (r.h / 4) + 1;
    int room_w = r.w - (room_x - r.x) * 2;
    int room_h = r.h - (room_y - r.y) * 2;
    if (room_w < 3 || room_h < 3) return;
    for (int y = room_y; y < room_y + room_h; y++) {
        for (int x = room_x; x < room_x + room_w; x++) {
            if (y > 0 && y < map.h - 1 && x > 0 && x < map.w - 1) {
                map.walling[y][x] = ' ';
            }
        }
    }
    room_list[room_count++] = (Rect){ room_x, room_y, room_w, room_h };
}

static void create_corridor(Map map, int x1, int y1, int x2, int y2) {
    int x = x1, y = y1;
    while (x != x2 || y != y2) {
        if (abs(x - x2) > abs(y - y2) && x != x2) {
            if (x < x2) x++; else x--;
        } else if (y != y2) {
            if (y < y2) y++; else y--;
        }
        if (y >= 0 && y < map.h && x >= 0 && x < map.w && map.walling[y][x] == '#') {
            map.walling[y][x] = '+';
        }
    }
}

static void bsp_split(Map map, Rect r, int min_size) {
    if (r.w < min_size * 2 && r.h < min_size * 2) {
        carve_room(map, r);
        return;
    }
    int split_vertical = rand() % 2;
    if (r.w > r.h * 1.5) split_vertical = 1;
    if (r.h > r.w * 1.5) split_vertical = 0;
    if (split_vertical) {
        if (r.w < min_size * 2) {
            carve_room(map, r);
            return;
        }
        int split_x = r.x + (r.w / 4) + rand() % (r.w / 2);
        Rect r1 = { r.x, r.y, split_x - r.x, r.h };
        Rect r2 = { split_x, r.y, r.w - (split_x - r.x), r.h };
        bsp_split(map, r1, min_size);
        bsp_split(map, r2, min_size);
    } else {
        if (r.h < min_size * 2) {
            carve_room(map, r);
            return;
        }
        int split_y = r.y + (r.h / 4) + rand() % (r.h / 2);
        Rect r1 = { r.x, r.y, r.w, split_y - r.y };
        Rect r2 = { r.x, split_y, r.w, r.h - (split_y - r.y) };
        bsp_split(map, r1, min_size);
        bsp_split(map, r2, min_size);
    }
}

Map xmgen_bsp(const int w, const int h, const int min_room_size) {
    srand(time(0));
    Map map = mnew(h, w);
    room_list = toss(Rect, (w * h) / (min_room_size * min_room_size));
    room_count = 0;
    Rect initial_rect = { 1, 1, w - 2, h - 2 };
    bsp_split(map, initial_rect, min_room_size);
    for (int i = 0; i < room_count - 1; i++) {
        Rect r1 = room_list[i];
        Rect r2 = room_list[i + 1];
        int x1 = r1.x + r1.w / 2;
        int y1 = r1.y + r1.h / 2;
        int x2 = r2.x + r2.w / 2;
        int y2 = r2.y + r2.h / 2;
        create_corridor(map, x1, y1, x2, y2);
    }
    free(room_list);
    room_list = NULL;
    room_count = 0;
    return map;
}

Map xmgen_drunk(const int w, const int h, const float floor_goal_percent) {
    srand(time(0));
    Map map = mnew(h, w);
    int floor_count = 0;
    const int total_tiles = w * h;
    const int floor_goal = total_tiles * floor_goal_percent;
    int walker_x = w / 2;
    int walker_y = h / 2;
    int max_iterations = total_tiles * 10;
    int iterations = 0;
    while (floor_count < floor_goal && iterations < max_iterations) {
        if (map.walling[walker_y][walker_x] == '#') {
            map.walling[walker_y][walker_x] = ' ';
            floor_count++;
        }
        int move = rand() % 4;
        switch (move) {
        case 0: walker_y--; break;
        case 1: walker_y++; break;
        case 2: walker_x--; break;
        case 3: walker_x++; break;
        }
        if (walker_x < 1) walker_x = 1;
        if (walker_x >= w - 1) walker_x = w - 2;
        if (walker_y < 1) walker_y = 1;
        if (walker_y >= h - 1) walker_y = h - 2;
        iterations++;
    }
    return map;
}

static int count_wall_neighbors(Map map, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + j;
            int ny = y + i;
            if (nx < 0 || ny < 0 || nx >= map.w || ny >= map.h || map.walling[ny][nx] == '#') {
                count++;
            }
        }
    }
    return count;
}

Map xmgen_cellular(const int w, const int h, const float wall_percent, const int iterations) {
    srand(time(0));
    Map map = mnew(h, w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (x == 0 || x == w - 1 || y == 0 || y == h - 1) {
                map.walling[y][x] = '#';
            } else {
                map.walling[y][x] = ((float)rand() / RAND_MAX) < wall_percent ? '#' : ' ';
            }
        }
    }
    char** buffer_map = bnew(h, w, '#');
    for (int iter = 0; iter < iterations; iter++) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (x == 0 || x == w - 1 || y == 0 || y == h - 1) {
                    buffer_map[y][x] = '#';
                    continue;
                }
                int wall_neighbors = count_wall_neighbors(map, x, y);
                if (map.walling[y][x] == '#') {
                    if (wall_neighbors < 4) {
                        buffer_map[y][x] = ' ';
                    } else {
                        buffer_map[y][x] = '#';
                    }
                } else {
                    if (wall_neighbors > 4) {
                        buffer_map[y][x] = '#';
                    } else {
                        buffer_map[y][x] = ' ';
                    }
                }
            }
        }
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                map.walling[y][x] = buffer_map[y][x];
            }
        }
    }
    for (int row = 0; row < map.h; row++)
        free(buffer_map[row]);
    free(buffer_map);
    return map;
}


#define PERLIN_TABLE_SIZE 256
static int p[2 * PERLIN_TABLE_SIZE];

static void init_perlin() {
    int perm[PERLIN_TABLE_SIZE];
    for (int i = 0; i < PERLIN_TABLE_SIZE; i++) perm[i] = i;
    for (int i = 0; i < PERLIN_TABLE_SIZE; i++) {
        int swap_idx = rand() % PERLIN_TABLE_SIZE;
        int temp = perm[i];
        perm[i] = perm[swap_idx];
        perm[swap_idx] = temp;
    }
    for (int i = 0; i < PERLIN_TABLE_SIZE; i++) {
        p[i] = p[i + PERLIN_TABLE_SIZE] = perm[i];
    }
}

static float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
static float lerp(float t, float a, float b) { return a + t * (b - a); }
static float grad(int hash, float x, float y) {
    int h = hash & 3;
    float u = h < 2 ? x : y;
    float v = h < 2 ? y : x;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
static float perlin(float x, float y) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    float u = fade(x);
    float v = fade(y);
    int A = p[X] + Y;
    int B = p[X + 1] + Y;
    return lerp(v, lerp(u, grad(p[A], x, y), grad(p[B], x - 1, y)),
        lerp(u, grad(p[A + 1], x, y - 1), grad(p[B + 1], x - 1, y - 1)));
}

Map xmgen_perlin(const int w, const int h, const float threshold) {
    srand(time(0));
    init_perlin();
    Map map = mnew(h, w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float noise_val = perlin((float)x * 0.1f, (float)y * 0.1f);
            if (noise_val > threshold) {
                map.walling[y][x] = ' ';
            }
        }
    }
    return map;
}


static void ca_flood_fill(int x, int y, char** tiles, int w, int h, int region_id, int** regions) {
    if (x < 0 || y < 0 || x >= w || y >= h || regions[y][x] != 0 || tiles[y][x] == '#') {
        return;
    }
    regions[y][x] = region_id;
    ca_flood_fill(x + 1, y, tiles, w, h, region_id, regions);
    ca_flood_fill(x - 1, y, tiles, w, h, region_id, regions);
    ca_flood_fill(x, y + 1, tiles, w, h, region_id, regions);
    ca_flood_fill(x, y - 1, tiles, w, h, region_id, regions);
}

static void isolate_largest_region(char** tiles, int w, int h) {
    int** regions = toss(int*, h);
    for (int i = 0; i < h; i++) {
        regions[i] = toss(int, w);
        memset(regions[i], 0, w * sizeof(int));
    }

    int region_id = 1;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (tiles[y][x] == ' ' && regions[y][x] == 0) {
                ca_flood_fill(x, y, tiles, w, h, region_id, regions);
                region_id++;
            }
        }
    }

    if (region_id <= 2) {
        for (int i = 0; i < h; i++) free(regions[i]);
        free(regions);
        return;
    }

    int* region_sizes = calloc(region_id, sizeof(int));
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (regions[y][x] != 0) {
                region_sizes[regions[y][x]]++;
            }
        }
    }

    int largest_region_id = 0;
    int max_size = 0;
    for (int i = 1; i < region_id; i++) {
        if (region_sizes[i] > max_size) {
            max_size = region_sizes[i];
            largest_region_id = i;
        }
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (regions[y][x] != largest_region_id) {
                tiles[y][x] = '#';
            }
        }
    }

    free(region_sizes);
    for (int i = 0; i < h; i++) free(regions[i]);
    free(regions);
}

static void generate_ca_shape(char** tiles, int w, int h) {
    float wall_chance = 0.55f;
    for(int y=0; y<h; y++) for(int x=0; x<w; x++) {
        tiles[y][x] = (rand() % 100 < wall_chance * 100) ? '#' : ' ';
    }
    
    char** buffer = bnew(h, w, '#');
    for (int i = 0; i < 5; i++) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int neighbors = 0;
                for(int dy=-1; dy<=1; dy++) for(int dx=-1; dx<=1; dx++) {
                    if(dx==0 && dy==0) continue;
                    int nx = x+dx, ny = y+dy;
                    if(nx < 0 || ny < 0 || nx >= w || ny >= h || tiles[ny][nx] == '#') {
                        neighbors++;
                    }
                }
                if (tiles[y][x] == '#') {
                    buffer[y][x] = (neighbors >= 2) ? '#' : ' ';
                } else {
                    buffer[y][x] = (neighbors >= 5) ? '#' : ' ';
                }
            }
        }
        for(int y=0; y<h; y++) memcpy(tiles[y], buffer[y], w * sizeof(char));
    }
    for(int y=0; y<h; y++) free(buffer[y]);
    free(buffer);

    isolate_largest_region(tiles, w, h);
}

static BrogueRoom create_brogue_room(int min_size, int max_size) {
    BrogueRoom room;
    room.w = min_size + rand() % (max_size - min_size);
    room.h = min_size + rand() % (max_size - min_size);
    room.tiles = bnew(room.h, room.w, '#');

    int type = rand() % 3;
    if (type == 0) {
        for (int y = 1; y < room.h - 1; y++) for (int x = 1; x < room.w - 1; x++) room.tiles[y][x] = ' ';
    } else if (type == 1) {
        int cx = room.w / 2, cy = room.h / 2;
        int radius = fmin(cx, cy) - 1;
        for (int y = 0; y < room.h; y++) for (int x = 0; x < room.w; x++) {
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius) {
                room.tiles[y][x] = ' ';
            }
        }
    } else {
        generate_ca_shape(room.tiles, room.w, room.h);
    }

    room.door_x[0] = 1 + rand() % (room.w - 2); room.door_y[0] = 0;
    room.door_x[1] = room.w - 1;              room.door_y[1] = 1 + rand() % (room.h - 2);
    room.door_x[2] = 1 + rand() % (room.w - 2); room.door_y[2] = room.h - 1;
    room.door_x[3] = 0;                       room.door_y[3] = 1 + rand() % (room.h - 2);

    if (rand() % 100 < 15) {
        int hw = room.w + 6, hh = room.h + 6;
        char** hallway_tiles = bnew(hh, hw, '#');
        for(int y=0; y<room.h; y++) for(int x=0; x<room.w; x++) {
            hallway_tiles[y+3][x+3] = room.tiles[y][x];
        }

        int hall_dir = rand() % 4;
        if (hall_dir == 0) {
            for(int y=0; y<=3; y++) hallway_tiles[y][hw/2] = ' ';
            for(int i=0; i<4; i++) { room.door_x[i] = hw/2; room.door_y[i] = 0; }
        } else if (hall_dir == 1) {
            for(int x=room.w+3; x<hw; x++) hallway_tiles[hh/2][x] = ' ';
            for(int i=0; i<4; i++) { room.door_x[i] = hw-1; room.door_y[i] = hh/2; }
        } else if (hall_dir == 2) {
            for(int y=room.h+3; y<hh; y++) hallway_tiles[y][hw/2] = ' ';
            for(int i=0; i<4; i++) { room.door_x[i] = hw/2; room.door_y[i] = hh-1; }
        } else {
            for(int x=0; x<=2; x++) hallway_tiles[hh/2][x] = ' ';
            for(int i=0; i<4; i++) { room.door_x[i] = 0; room.door_y[i] = hh/2; }
        }

        for(int y=0; y<room.h; y++) free(room.tiles[y]); free(room.tiles);
        room.tiles = hallway_tiles;
        room.w = hw; room.h = hh;
    }

    return room;
}

Map xmgen_maze(const int wR, const int hR, const int w, const int h) {
    // Ensure width and height are odd and at least 3 for a proper maze structure
    int maze_w = (w % 2 == 0) ? w + 1 : w;
    if (maze_w < 3) maze_w = 3;
    int maze_h = (h % 2 == 0) ? h + 1 : h;
    if (maze_h < 3) maze_h = 3;

    srand(time(0));
    Map map = mnew(wR, hR); // mnew creates a map filled with '#' characters

    // Stack for the depth-first search algorithm
    int* stack_x = toss(int, maze_w * maze_h);
    int* stack_y = toss(int, maze_w * maze_h);
    int stack_top = 0;

    // Start carving the maze from cell (1, 1)
    int cx = 1;
    int cy = 1;
    map.walling[cy][cx] = ' '; // Mark as part of the maze path

    // Push the starting cell onto the stack
    stack_x[stack_top] = cx;
    stack_y[stack_top] = cy;
    stack_top++;

    // Directions for neighbors (N, E, S, W), moving 2 cells at a time
    int dx[] = {0, 2, 0, -2};
    int dy[] = {-2, 0, 2, 0};
    // Directions for walls between cells, moving 1 cell at a time
    int wall_dx[] = {0, 1, 0, -1};
    int wall_dy[] = {-1, 0, 1, 0};

    while (stack_top > 0) {
        // Get the current cell from the top of the stack
        cx = stack_x[stack_top - 1];
        cy = stack_y[stack_top - 1];

        // Find all unvisited neighbors
        int valid_neighbors[4];
        int neighbor_count = 0;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            // Check if the neighbor is within bounds and is a wall (i.e., unvisited)
            if (nx > 0 && nx < maze_w - 1 && ny > 0 && ny < maze_h - 1 && map.walling[ny][nx] == '#') {
                valid_neighbors[neighbor_count++] = i;
            }
        }

        if (neighbor_count > 0) {
            // If there are unvisited neighbors, pick one randomly
            int rand_idx = rand() % neighbor_count;
            int chosen_dir = valid_neighbors[rand_idx];

            // Calculate the new cell's coordinates
            int nx = cx + dx[chosen_dir];
            int ny = cy + dy[chosen_dir];
            // and the wall between the current and new cell
            int wx = cx + wall_dx[chosen_dir];
            int wy = cy + wall_dy[chosen_dir];

            // Carve a path to the new cell
            map.walling[wy][wx] = ' ';
            map.walling[ny][nx] = ' ';

            // Push the new cell onto the stack to visit from
            stack_x[stack_top] = nx;
            stack_y[stack_top] = ny;
            stack_top++;

        } else {
            // If there are no unvisited neighbors, backtrack
            stack_top--;
        }
    }

    // Carve an entrance at the top-left
    map.walling[1][0] = ' ';
    // Carve an exit at the bottom-right
    map.walling[maze_h - 2][maze_w - 1] = ' ';
    
    // Free the memory used by the stack
    free(stack_x);
    free(stack_y);

    return map;
}

Map xmgen_room_maze(const int wR, const int hR, const int w, const int h, const int num_rooms_to_try, const int min_room_size, const int max_room_size) {
    // 1. Initialization
    // Ensure dimensions are odd and provide a minimum size
    int maze_w = (w % 2 == 0) ? w + 1 : w;
    if (maze_w < 15) maze_w = 15;
    int maze_h = (h % 2 == 0) ? h + 1 : h;
    if (maze_h < 15) maze_h = 15;

    srand(time(0));
    Map map = mnew(wR, hR);

    Rect* rooms = toss(Rect, num_rooms_to_try);
    int room_count = 0;

    // 2. Place Rooms
    for (int i = 0; i < num_rooms_to_try && room_count < num_rooms_to_try; i++) {
        // Generate room dimensions (must be odd)
        int rw = min_room_size + (rand() % (max_room_size - min_room_size + 1));
        if (rw % 2 == 0) rw++;
        int rh = min_room_size + (rand() % (max_room_size - min_room_size + 1));
        if (rh % 2 == 0) rh++;

        // Generate room position (must be odd to align with maze grid)
        int rx = (rand() % ((maze_w - rw - 2) / 2)) * 2 + 1;
        int ry = (rand() % ((maze_h - rh - 2) / 2)) * 2 + 1;

        Rect new_room = {rx, ry, rw, rh};
        
        // Check for overlaps with previously placed rooms
        bool overlap = false;
        for (int j = 0; j < room_count; j++) {
            Rect other = rooms[j];
            if (new_room.x < other.x + other.w && new_room.x + new_room.w > other.x &&
                new_room.y < other.y + other.h && new_room.y + new_room.h > other.y) {
                overlap = true;
                break;
            }
        }
        
        if (!overlap) {
            rooms[room_count++] = new_room;
        }
    }

    // Carve rooms into the map as floor space
    for (int i = 0; i < room_count; i++) {
        Rect r = rooms[i];
        for (int y = r.y; y < r.y + r.h; y++) {
            for (int x = r.x; x < r.x + r.w; x++) {
                map.walling[y][x] = ' ';
            }
        }
    }

    // 3. Generate Maze in the remaining wall areas
    for (int y = 1; y < maze_h; y += 2) {
        for (int x = 1; x < maze_w; x += 2) {
            if (map.walling[y][x] == '#') {
                // This point is an uncarved wall, start a maze from here
                int* stack_x = toss(int, maze_w * maze_h);
                int* stack_y = toss(int, maze_w * maze_h);
                int stack_top = 0;

                stack_x[stack_top] = x;
                stack_y[stack_top] = y;
                stack_top++;
                map.walling[y][x] = '.'; // Use '.' as a temporary marker for maze paths

                int dx[] = {0, 2, 0, -2};
                int dy[] = {-2, 0, 2, 0};
                int wall_dx[] = {0, 1, 0, -1};
                int wall_dy[] = {-1, 0, 1, 0};

                while (stack_top > 0) {
                    int cx = stack_x[stack_top - 1];
                    int cy = stack_y[stack_top - 1];

                    int valid_neighbors[4];
                    int neighbor_count = 0;
                    for (int k = 0; k < 4; k++) {
                        int nx = cx + dx[k];
                        int ny = cy + dy[k];
                        if (nx > 0 && nx < maze_w - 1 && ny > 0 && ny < maze_h - 1 && map.walling[ny][nx] == '#') {
                            valid_neighbors[neighbor_count++] = k;
                        }
                    }

                    if (neighbor_count > 0) {
                        int rand_idx = rand() % neighbor_count;
                        int chosen_dir = valid_neighbors[rand_idx];
                        int nx = cx + dx[chosen_dir];
                        int ny = cy + dy[chosen_dir];
                        int wx = cx + wall_dx[chosen_dir];
                        int wy = cy + wall_dy[chosen_dir];

                        map.walling[wy][wx] = '.';
                        map.walling[ny][nx] = '.';

                        stack_x[stack_top] = nx;
                        stack_y[stack_top] = ny;
                        stack_top++;
                    } else {
                        stack_top--;
                    }
                }
                free(stack_x);
                free(stack_y);
            }
        }
    }

    // 4. Connect rooms to the maze by adding doors
    for (int i = 0; i < room_count; i++) {
        Rect r = rooms[i];
        Point doors[r.w * 2 + r.h * 2];
        int door_count = 0;

        // Find potential door locations around the room's perimeter
        // Check North and South walls
        for (int x = r.x; x < r.x + r.w; x++) {
            if (r.y - 2 > 0 && map.walling[r.y - 2][x] == '.') doors[door_count++] = (Point){(float)x, (float)r.y - 1};
            if (r.y + r.h + 1 < maze_h && map.walling[r.y + r.h + 1][x] == '.') doors[door_count++] = (Point){(float)x, (float)r.y + r.h};
        }
        // Check West and East walls
        for (int y = r.y; y < r.y + r.h; y++) {
            if (r.x - 2 > 0 && map.walling[y][r.x - 2] == '.') doors[door_count++] = (Point){(float)r.x - 1, (float)y};
            if (r.x + r.w + 1 < maze_w && map.walling[y][r.x + r.w + 1] == '.') doors[door_count++] = (Point){(float)r.x + r.w, (float)y};
        }

        // If any potential doors were found, pick one randomly to guarantee a connection
        if (door_count > 0) {
            Point door = doors[rand() % door_count];
            map.walling[(int)door.y][(int)door.x] = '+'; // Carve a door
        }
        // Note: if a room has 0 potential doors, it means it's completely walled off
        // by other rooms. This can be avoided with better room placement parameters.
    }

    // 5. Finalize the map
    // Turn all temporary maze paths into final floor tiles
    for (int y = 0; y < maze_h; y++) {
        for (int x = 0; x < maze_w; x++) {
            if (map.walling[y][x] == '.') {
                map.walling[y][x] = ' ';
            }
        }
    }
    
    free(rooms);
    return map;
}


// Helper function to check connectivity between two points
static int is_connected(Map map, Point start, Point end) {
    if (start.x < 0 || start.y < 0 || start.x >= map.w || start.y >= map.h) return 0;
    if (end.x < 0 || end.y < 0 || end.x >= map.w || end.y >= map.h) return 0;
    
    // Create visited grid
    int** visited = toss(int*, map.h);
    for (int y = 0; y < map.h; y++) {
        visited[y] = toss(int, map.w);
        memset(visited[y], 0, map.w * sizeof(int));
    }
    
    // Directions for neighbors (up, right, down, left)
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    
    // Simple stack for DFS
    Point* stack = toss(Point, map.w * map.h);
    int stack_top = 0;
    
    // Start DFS from start point
    stack[stack_top++] = start;
    visited[(int)start.y][(int)start.x] = 1;
    
    while (stack_top > 0) {
        Point current = stack[--stack_top];
        
        // If reached end point, success
        if ((int)current.x == (int)end.x && (int)current.y == (int)end.y) {
            for (int y = 0; y < map.h; y++) free(visited[y]);
            free(visited);
            free(stack);
            return 1;
        }
        
        // Check neighbors
        for (int i = 0; i < 4; i++) {
            int nx = (int)current.x + dx[i];
            int ny = (int)current.y + dy[i];
            
            if (nx >= 0 && ny >= 0 && nx < map.w && ny < map.h && 
                !visited[ny][nx] && map.walling[ny][nx] != '#') {
                visited[ny][nx] = 1;
                stack[stack_top++] = (Point){(float)nx, (float)ny};
            }
        }
    }
    
    // Cleanup and return not connected
    for (int y = 0; y < map.h; y++) free(visited[y]);
    free(visited);
    free(stack);
    return 0;
}

// Find closest point in room to given point
static Point find_closest_room_point(Map map, Point p, int room_x, int room_y, int room_w, int room_h) {
    Point closest = {-1, -1};
    float min_dist = -1;
    
    for (int y = room_y; y < room_y + room_h; y++) {
        for (int x = room_x; x < room_x + room_w; x++) {
            if (y < 0 || x < 0 || y >= map.h || x >= map.w) continue;
            if (map.walling[y][x] != ' ') continue; // Only consider floor tiles
            
            float dist = sqrtf((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));
            if (min_dist < 0 || dist < min_dist) {
                min_dist = dist;
                closest = (Point){(float)x, (float)y};
            }
        }
    }
    return closest;
}

static void add_lake(Map* map, char tile, int x, int y,  int w, int h, float lakePercent){
    Map lake = xmgen_cellular(w, h, lakePercent, 200);
    for(int yL = 0; yL < lake.h; yL++){
        for(int xL = 0; xL < lake.w; xL++){
            if(lake.walling[yL][xL] == ' '){
                int xM = (xL + x)%map->w;
                int yM = (yL + y)%map->h; 
                if(xM == 0){
                    xM = 1;
                }
                if(yM == 0){
                    yM = 1;
                } 
                //printf("%d %d\n", xM, yM);
                map->walling[yM][xM] = tile;
            }
        }
    }
    //exit(-1)
    xmclose(lake);
}

static void add_enviroment(Map* map, char tile, int x, int y,  int w, int h, float lakePercent){
    Map lake = xmgen_cellular(w, h, lakePercent, 200);
    for(int yL = 0; yL < lake.h; yL++){
        for(int xL = 0; xL < lake.w; xL++){
            if(lake.walling[yL][xL] == ' ' ){
                int xM = (xL + x)%map->w;
                int yM = (yL + y)%map->h; 
                if(xM == 0){
                    xM = 1;
                }
                if(yM == 0){
                    yM = 1;
                } 
                //printf("%d %d\n", xM, yM);
                if(map->walling[yM][xM] == ' ')
                    map->walling[yM][xM] = tile;
            }
        }
    }
    //exit(-1)
    xmclose(lake);
}


Map xmgen_brogue(const int w, const int h, const int max_rooms, const int min_size, const int max_size) {
    srand(time(0));
    Map map = mnew(h, w);
    
    // Store rooms for water feature addition
    Rect* rooms = toss(Rect, max_rooms);
    int room_count = 0;

    BrogueRoom first_room = create_brogue_room(min_size, max_size);
    int start_x = (w / 2) - (first_room.w / 2);
    int start_y = (h / 2) - (first_room.h / 2);
    for (int y = 0; y < first_room.h; y++) {
        for (int x = 0; x < first_room.w; x++) {
            if (first_room.tiles[y][x] == ' ') {
                if(start_y + y >= 0 && start_y + y < h && start_x + x >= 0 && start_x + x < w)
                    map.walling[start_y + y][start_x + x] = ' ';
            }
        }
    }
    // Record first room
    rooms[room_count++] = (Rect){start_x, start_y, first_room.w, first_room.h};
    
    for(int y=0; y<first_room.h; y++) 
        free(first_room.tiles[y]); 
    free(first_room.tiles);

    int rooms_placed = 1;
    int attempts = 0;

    while (rooms_placed < max_rooms && attempts < 2000) {
        attempts++;
        BrogueRoom new_room = create_brogue_room(min_size, max_size);

        Point* perimeter = toss(Point, w * h);
        int perimeter_count = 0;
        for (int y = 1; y < h - 1; y++) {
            for (int x = 1; x < w - 1; x++) {
                if (map.walling[y][x] == '#') {
                    if (map.walling[y - 1][x] == ' ' || map.walling[y + 1][x] == ' ' ||
                        map.walling[y][x - 1] == ' ' || map.walling[y][x + 1] == ' ') {
                        perimeter[perimeter_count++] = (Point){(float)x, (float)y};
                    }
                }
            }
        }

        if (perimeter_count == 0) {
            free(perimeter);
            break;
        }

        bool placed = false;
        for (int p_idx = 0; p_idx < perimeter_count; p_idx++) {
            int rand_idx = p_idx + rand() % (perimeter_count - p_idx);
            Point temp = perimeter[p_idx]; perimeter[p_idx] = perimeter[rand_idx]; perimeter[rand_idx] = temp;
        }

        for (int p_idx = 0; p_idx < perimeter_count && !placed; p_idx++) {
            Point attach_point = perimeter[p_idx];

            for (int door_idx = 0; door_idx < 4; door_idx++) {
                int place_x = attach_point.x - new_room.door_x[door_idx];
                int place_y = attach_point.y - new_room.door_y[door_idx];

                if (place_x < 1 || place_y < 1 || place_x + new_room.w > w - 1 || place_y + new_room.h > h - 1) {
                    continue;
                }

                bool overlap = false;
                for (int y = 0; y < new_room.h; y++) {
                    for (int x = 0; x < new_room.w; x++) {
                        if (new_room.tiles[y][x] == ' ' && map.walling[place_y + y][place_x + x] == ' ') {
                            overlap = true;
                            break;
                        }
                    }
                    if (overlap) break;
                }

                if (!overlap) {
                    // Store placement coordinates for connection check
                    int placed_room_x = place_x;
                    int placed_room_y = place_y;
                    int placed_room_w = new_room.w;
                    int placed_room_h = new_room.h;

                    // Place the room's floor tiles
                    for (int y = 0; y < new_room.h; y++) {
                        for (int x = 0; x < new_room.w; x++) {
                            if (new_room.tiles[y][x] == ' ') {
                                map.walling[place_y + y][place_x + x] = ' ';
                            }
                        }
                    }
                    
                    // Carve the connecting door
                    map.walling[(int)attach_point.y][(int)attach_point.x] = ' ';

                    // Record room placement
                    rooms[room_count++] = (Rect){placed_room_x, placed_room_y, placed_room_w, placed_room_h};
                    
                    // 1. Check connectivity to main map
                    Point room_center = {
                        (float)(placed_room_x + placed_room_w/2),
                        (float)(placed_room_y + placed_room_h/2)
                    };
                    Point main_center = {w/2.0f, h/2.0f}; // Center of first room

                    if (!is_connected(map, room_center, main_center)) {
                        // 2. Find closest points between room and main map
                        Point room_point = {-1, -1};
                        Point map_point = {-1, -1};
                        float min_dist = -1;
                        
                        // Iterate through all floor tiles in new room
                        for (int ry = placed_room_y; ry < placed_room_y + placed_room_h; ry++) {
                            for (int rx = placed_room_x; rx < placed_room_x + placed_room_w; rx++) {
                                if (ry < 0 || rx < 0 || ry >= h || rx >= w) continue;
                                if (map.walling[ry][rx] != ' ') continue;
                                
                                // Find closest floor tile in main map
                                for (int y = 0; y < h; y++) {
                                    for (int x = 0; x < w; x++) {
                                        if (map.walling[y][x] != ' ') continue;
                                        
                                        // Skip points in the new room
                                        if (y >= placed_room_y && y < placed_room_y + placed_room_h &&
                                            x >= placed_room_x && x < placed_room_x + placed_room_w) continue;
                                        
                                        float dist = sqrtf((x - rx)*(x - rx) + (y - ry)*(y - ry));
                                        if (min_dist < 0 || dist < min_dist) {
                                            min_dist = dist;
                                            room_point = (Point){(float)rx, (float)ry};
                                            map_point = (Point){(float)x, (float)y};
                                        }
                                    }
                                }
                            }
                        }
                        
                        // 3. Create corridor if valid points found
                        if (min_dist >= 0) {
                            create_corridor(map, 
                                (int)room_point.x, (int)room_point.y,
                                (int)map_point.x, (int)map_point.y);
                        }
                    }

                    placed = true;
                    rooms_placed++;
                    break;
                }
            }
        }
        
        free(perimeter);
        for(int y=0; y<new_room.h; y++) 
            free(new_room.tiles[y]); 
        free(new_room.tiles);
    }
    int wallCount = 0;
    for(int y = 0; y < map.h; y++){
        for(int x = 0; x < map.w; x++){
            if(map.walling[y][x] == '#'){
                wallCount++;
            }
        }
    } 
    //Check if map is not gen 
    if(wallCount == (map.h*map.w)){
        xmclose(map);
        return xmgen_brogue(w, h, max_rooms, min_size, max_size);
    }

    add_enviroment(&map, '\"', 0, 0, w, h, 0.6f);
    bool isLake = false;
    while(!isLake){
        int x = rand()%w;
        int y = rand()%h;
        if(map.walling[y][x] == ' '){
            
            //add_lake(&map, '~', x, y, 30, 30, 0.5);
           // add_enviroment(&map, '~',  x, y, 20, 20, 0.5f);
            isLake = true;
            //xmprint(map);
            //printf("x %d y %d\n", x, y);
           // exit(-1);
        }
    }
    //ADD grass 
   
    //add_enviroment(&map, '\'', 0, 0, w, h, 0.5f);
    free(rooms);
    return map;
}