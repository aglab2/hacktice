#include <ultra64.h>

/**
 * @file debug_box.c
 * Draws 3D boxes for debugging purposes
 * Originally written by Synray, modified by Fazana.
 *
 * How to use:
 *
 * Just call debug_box() whenever you want to draw one!
 *
 * debug_box by default takes two arguments: a center and bounds vec3f.
 * This will draw a box starting from the point (center - bounds) to (center + bounds).
 *
 * Use debug_box_rot to draw a box rotated in the xz-plane.
 *
 * If you want to draw a box by specifying min and max points, use debug_box_pos() instead.
 */

#include "debug_box.h"

#include "sm64.h"
#include "behavior_data.h"
#include "cfg.h"
#include "colors.h"
#include "game/area.h"
#include "game/display.h"
#include "game/game.h"
#include "game/geo_misc.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"

#define DEBUG_POOL_SIZE (0x80570000 - 0x80560000)
#define ALIGN8(val) (((val) + 0x7) & ~0x7)

struct DebugPool
{
    char pool[DEBUG_POOL_SIZE];
};

#define gDebugPools ((struct DebugPool*) 0x80560000)

static Gfx* gDebugPoolHead;
static u8* gDebugPoolAllocTail;
static int gDebugPoolWhenToReset = -1;
static int gDebugPoolLastType = -1; 
extern struct GfxPool gGfxPools[2];

static void debug_pool_init()
{
    int idx = gGfxPool == &gGfxPools[0] ? 0 : 1;
    gDebugPoolHead = (Gfx*) &gDebugPools[idx];
    if (gDebugPoolLastType != idx)
    {
        int reset = 0;
        if (gDebugPoolLastType == -1)
        {
            reset = 1;
            gDebugPoolWhenToReset = idx;
        }
        else
        {
            if (gDebugPoolWhenToReset == idx)
            {
                reset = 1;
            }
        }

        gDebugPoolLastType = idx;
        if (reset)
        {
            gDebugPoolAllocTail = (u8*) 0x80560000;
        }
    }
}

static void* debug_pool_alloc(u32 size)
{
    void *ptr = NULL;

    size = ALIGN8(size);
    gDebugPoolAllocTail -= size;
    ptr = gDebugPoolAllocTail;
    return ptr;
}

/**
 * The max amount of debug boxes before debug_box() just returns.
 * You can set this to something higher, but you might run out of space in the gfx pool.
 */
#define MAX_DEBUG_BOXES 512

enum DebugBoxFlags {
    DEBUG_SHAPE_BOX      = (1 << 0), // 0x01
    DEBUG_SHAPE_CYLINDER = (1 << 1), // 0x02
    DEBUG_UCODE_DEFAULT  = (1 << 2), // 0x04
#ifdef OBJECTS_REJ
    DEBUG_UCODE_REJ      = (1 << 3), // 0x08
#else
    DEBUG_UCODE_REJ      = DEBUG_UCODE_DEFAULT,
#endif
    DEBUG_BOX_CLEAR      = (1 << 4), // 0x10
};

f32 gScaleFactor = 4.f;

extern s16 *gEnvironmentRegions;
#define NUM_CELLS                   (2 * LEVEL_BOUNDARY_MAX / CELL_SIZE)
#define CELL_SIZE          0x400   //  1024, NUM_CELLS = 16
#define GET_CELL_COORD(p)   ((((s32)(p / gScaleFactor) + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & (NUM_CELLS - 1));

#define is_outside_level_bounds(xPos, zPos) \
    (((xPos / gScaleFactor) <= -LEVEL_BOUNDARY_MAX) ||     \
     ((xPos / gScaleFactor) >=  LEVEL_BOUNDARY_MAX) ||     \
     ((zPos / gScaleFactor) <= -LEVEL_BOUNDARY_MAX) ||     \
     ((zPos / gScaleFactor) >=  LEVEL_BOUNDARY_MAX))

#define SURFACE_IS_INSTANT_WARP(cmd)            (((cmd) >= SURFACE_INSTANT_WARP_1B) && ((cmd) < SURFACE_INSTANT_WARP_1B + INSTANT_WARP_INDEX_STOP))

#define TC_B_OFF	-0.5
#define TC_B(p)		(((p) + TC_B_OFF) * 32)
#define ST_B(s, t)	{TC_B(s), TC_B(t)}

Vtx debug_box_mesh[32] = {
	{{{    0,    0, -100}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   50,  100,  -87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   50,    0,  -87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{    0,  100, -100}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -50,    0,  -87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -50,  100,  -87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -87,    0,  -50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -87,  100,  -50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{ -100,    0,    0}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{ -100,  100,    0}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -87,    0,   50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -87,  100,   50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -50,    0,   87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  -50,  100,   87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{    0,    0,  100}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{    0,  100,  100}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   50,    0,   87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   50,  100,   87}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   87,    0,   50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   87,  100,   50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  100,    0,    0}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{  100,  100,    0}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   87,    0,  -50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{   87,  100,  -50}, 0, ST_B( 0, 32), {0x00, 0x00, 0x00, 0xFF}}},
	{{{ -100,    0,  100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{ -100,  100,  100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{ -100,  100, -100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{  100,    0,  100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{ -100,    0, -100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{  100,  100, -100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{  100,  100,  100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{  100,    0, -100}, 0, ST_B( 0, 32), {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx dl_debug_box_verts[] = {
	gsSPVertex(debug_box_mesh, 32, 0),
	gsSP2Triangles(24, 25, 26, 0, 27, 25, 24, 0),
	gsSP2Triangles(28, 27, 24, 0, 24, 26, 28, 0),
	gsSP2Triangles(28, 26, 29, 0, 29, 26, 25, 0),
	gsSP2Triangles(29, 25, 30, 0, 27, 30, 25, 0),
	gsSP2Triangles(31, 30, 27, 0, 28, 31, 27, 0),
	gsSP2Triangles(28, 29, 31, 0, 31, 29, 30, 0),
	gsSPEndDisplayList(),
};

Gfx dl_debug_cylinder_verts[] = {
	gsSPVertex(debug_box_mesh, 24, 0),
	gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
	gsSP2Triangles( 4,  3,  0, 0x0,  4,  5,  3, 0x0),
	gsSP2Triangles( 6,  5,  4, 0x0,  6,  7,  5, 0x0),
	gsSP2Triangles( 8,  7,  6, 0x0,  8,  9,  7, 0x0),
	gsSP2Triangles(10,  9,  8, 0x0, 10, 11,  9, 0x0),
	gsSP2Triangles(12, 11, 10, 0x0, 12, 13, 11, 0x0),
	gsSP2Triangles(14, 13, 12, 0x0, 14, 15, 13, 0x0),
	gsSP2Triangles(16, 15, 14, 0x0, 16, 17, 15, 0x0),
	gsSP2Triangles(18, 17, 16, 0x0, 18, 19, 17, 0x0),
	gsSP2Triangles(20, 19, 18, 0x0, 20, 21, 19, 0x0),
	gsSP2Triangles(22, 21, 20, 0x0, 22, 23, 21, 0x0),
	gsSP2Triangles( 2, 23, 22, 0x0,  2,  1, 23, 0x0),
	gsSP2Triangles(23,  1,  3, 0x0, 23,  3,  7, 0x0),
	gsSP2Triangles( 3,  5,  7, 0x0,  7, 15, 23, 0x0),
	gsSP2Triangles( 7, 11, 15, 0x0,  7,  9, 11, 0x0),
	gsSP2Triangles(11, 13, 15, 0x0, 15, 17, 19, 0x0),
	gsSP2Triangles(15, 19, 23, 0x0, 19, 21, 23, 0x0),
	gsSPEndDisplayList(),
};

static u8 hitboxView  = FALSE;
static u8 surfaceView = FALSE;

/**
 * Internal struct containing box info
 */
struct DebugBox {
    u32 color;
    Vec3s center;
    Vec3s bounds;
    s16 yaw;
    u8 type;
};

struct DebugVert {
    Vec3s pos;
    Vec3f normal;
};

static struct DebugBox sBoxes[MAX_DEBUG_BOXES];
static s16 sNumBoxes = 0;

extern Mat4 gMatStack[32]; // XXX: Hack

/**
 * The debug boxes' default transparency
 */
#define DBG_BOX_ALPHA     0x7F
/**
 * The debug boxes' default color. sCurBoxColor is reset to this every frame.
 */
#define DBG_BOX_DEF_COLOR 0xFF0000

/**
 * The color that new boxes will be drawn with.
 */
u32 sCurBoxColor = ((DBG_BOX_ALPHA << 24) | DBG_BOX_DEF_COLOR);

/**
 * The allocated size of a rotated box's dl
 */
#define DBG_BOX_DLSIZE ((s32)((6 * sizeof(Gfx)) + (8 * sizeof(Vtx))))

/**
 * Sets up the RCP for drawing the boxes
 */
static const Gfx dl_debug_box_begin[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT),
    gsSPEndDisplayList(),
};

static const Gfx dl_visual_surface[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL, G_RM_NOOP2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

static const Gfx dl_debug_box_end[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

static u8 viewCycle = 0;

// Puppyprint will call this from elsewhere.
static void debug_box_input(void) {
    if (gPlayer1Controller->buttonPressed & R_JPAD) {
        viewCycle++;
        if (viewCycle > 3) {
            viewCycle = 0;
        }
        hitboxView = viewCycle == 1 || viewCycle == 3;
        surfaceView = viewCycle == 2 || viewCycle == 3;
    }
}

static s16 gVisualSurfaceCount;
static s32 gVisualOffset;
extern s32 gSurfaceNodesAllocated;
extern s32 gSurfacesAllocated;

#define NUM_SPATIAL_PARTITIONS 3

static void iterate_surfaces_visual(s32 x, s32 z, Vtx *verts) {
    struct SurfaceNode *node;
    struct Surface *surf;
    s32 i = 0;
    ColorRGB col = COLOR_RGB_RED;

    if (is_outside_level_bounds(x, z)) return;

    s32 cellX = GET_CELL_COORD(x);
    s32 cellZ = GET_CELL_COORD(z);

    for (i = 0; i < (2 * NUM_SPATIAL_PARTITIONS); i++) {
        switch (i) {
            case 0: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; colorRGB_copy(col, (ColorRGB)COLOR_RGB_GREEN ); break;
            case 1: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; colorRGB_copy(col, (ColorRGB)COLOR_RGB_GREEN ); break;
            case 2: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; colorRGB_copy(col, (ColorRGB)COLOR_RGB_BLUE  ); break;
            case 3: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; colorRGB_copy(col, (ColorRGB)COLOR_RGB_BLUE  ); break;
            case 4: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; colorRGB_copy(col, (ColorRGB)COLOR_RGB_RED   ); break;
            case 5: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; colorRGB_copy(col, (ColorRGB)COLOR_RGB_RED   ); break;
        }

        while (node != NULL) {
            surf = node->surface;
            node = node->next;

            if (SURFACE_IS_INSTANT_WARP(surf->type)) {
                make_vertex(verts, (gVisualSurfaceCount + 0), surf->vertex1[0] * gScaleFactor, surf->vertex1[1] * gScaleFactor, surf->vertex1[2] * gScaleFactor, 0, 0, 0xFF, 0xA0, 0x00, 0x80);
                make_vertex(verts, (gVisualSurfaceCount + 1), surf->vertex2[0] * gScaleFactor, surf->vertex2[1] * gScaleFactor, surf->vertex2[2] * gScaleFactor, 0, 0, 0xFF, 0xA0, 0x00, 0x80);
                make_vertex(verts, (gVisualSurfaceCount + 2), surf->vertex3[0] * gScaleFactor, surf->vertex3[1] * gScaleFactor, surf->vertex3[2] * gScaleFactor, 0, 0, 0xFF, 0xA0, 0x00, 0x80);
            } else {
                make_vertex(verts, (gVisualSurfaceCount + 0), surf->vertex1[0] * gScaleFactor, surf->vertex1[1] * gScaleFactor, surf->vertex1[2] * gScaleFactor, 0, 0, col[0], col[1], col[2], 0x80);
                make_vertex(verts, (gVisualSurfaceCount + 1), surf->vertex2[0] * gScaleFactor, surf->vertex2[1] * gScaleFactor, surf->vertex2[2] * gScaleFactor, 0, 0, col[0], col[1], col[2], 0x80);
                make_vertex(verts, (gVisualSurfaceCount + 2), surf->vertex3[0] * gScaleFactor, surf->vertex3[1] * gScaleFactor, surf->vertex3[2] * gScaleFactor, 0, 0, col[0], col[1], col[2], 0x80);
            }

            gVisualSurfaceCount += 3;
        }
    }
}

typedef Collision TerrainData;

static void iterate_surfaces_envbox(Vtx *verts) {
    TerrainData *p = gEnvironmentRegions;
    ColorRGB col = COLOR_RGB_YELLOW;
    s32 i = 0;

    if (p != NULL) {
        s32 numRegions = *p++;
        for (i = 0; i < numRegions; i++) {
            make_vertex(verts, (gVisualSurfaceCount + 0), p[1], p[5], p[2], 0, 0, col[0], col[1], col[2], 0x80);
            make_vertex(verts, (gVisualSurfaceCount + 1), p[1], p[5], p[4], 0, 0, col[0], col[1], col[2], 0x80);
            make_vertex(verts, (gVisualSurfaceCount + 2), p[3], p[5], p[2], 0, 0, col[0], col[1], col[2], 0x80);

            make_vertex(verts, (gVisualSurfaceCount + 3), p[3], p[5], p[2], 0, 0, col[0], col[1], col[2], 0x80);
            make_vertex(verts, (gVisualSurfaceCount + 4), p[1], p[5], p[4], 0, 0, col[0], col[1], col[2], 0x80);
            make_vertex(verts, (gVisualSurfaceCount + 5), p[3], p[5], p[4], 0, 0, col[0], col[1], col[2], 0x80);

            gVisualSurfaceCount += 6;
            gVisualOffset       += 6;
            p                   += 6;
        }
    }
}

// VERTCOUNT = The highest number divisible by 6, which is less than the maximum vertex buffer divided by 2.
// The vertex buffer is 64 if OBJECTS_REJ is enabled, 32 otherwise.
//! TODO: Why can this only use half of the vertex buffer?
#ifdef OBJECTS_REJ
#define VERTCOUNT 30
#else
#define VERTCOUNT 12
#endif // OBJECTS_REJ

static void visual_surface_display(Vtx *verts, s32 iteration) {
    s32 vts = (iteration ? gVisualOffset : gVisualSurfaceCount);
    s32 vtl = 0;
    s32 count = VERTCOUNT;
    s32 ntx = 0;

    while (vts > 0) {
        if (count == VERTCOUNT) {
            ntx = MIN(VERTCOUNT, vts);
            gSPVertex(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(verts + (gVisualSurfaceCount - vts)), ntx, 0);
            count = 0;
            vtl   = VERTCOUNT;
        }

        if (vtl >= 6) {
            gSP2Triangles(gDebugPoolHead++, (count + 0),
                                              (count + 1),
                                              (count + 2), 0x0,
                                              (count + 3),
                                              (count + 4),
                                              (count + 5), 0x0);
            vts   -= 6;
            vtl   -= 6;
            count += 6;
        } else if (vtl >= 3) {
            gSP1Triangle(gDebugPoolHead++, (count + 0),
                                             (count + 1),
                                             (count + 2), 0x0);
            vts   -= 3;
            vtl   -= 3;
            count += 3;
        }
    }
}

static s32 iterate_surface_count(s32 x, s32 z) {
    struct SurfaceNode *node;
    s32 i = 0;
    s32 j = 0;
    TerrainData *p = gEnvironmentRegions;
    s32 numRegions;

    if (is_outside_level_bounds(x, z)) return 0;

    s32 cellX = GET_CELL_COORD(x);
    s32 cellZ = GET_CELL_COORD(z);

    for (i = 0; i < (2 * NUM_SPATIAL_PARTITIONS); i++) {
        switch (i) {
            case 0: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; break;
            case 1: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; break;
            case 2: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; break;
            case 3: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; break;
            case 4: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; break;
            case 5: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; break;
        }

        while (node != NULL) {
            node = node->next;
            j++;
        }
    }
    if (p != NULL) {
        numRegions = *p++;
        j += (numRegions * 6);
    }

    return j;
}

static void visual_surface_loop(void) {
    if (!gSurfaceNodesAllocated
     || !gSurfacesAllocated
     || !gMarioState->marioObj) {
        return;
    }
    Mtx *mtx   = debug_pool_alloc(sizeof(Mtx));
    Vtx *verts = debug_pool_alloc((iterate_surface_count(gMarioState->pos[0], gMarioState->pos[2]) * 3) * sizeof(Vtx));

    gVisualSurfaceCount = 0;
    gVisualOffset       = 0;

    if ((mtx == NULL) || (verts == NULL)) {
        return;
    }
    mtxf_to_mtx(mtx, gMatStack[1]);

    gSPDisplayList(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(dl_visual_surface));

    gSPMatrix(gDebugPoolHead++, mtx, (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));

    iterate_surfaces_visual(gMarioState->pos[0], gMarioState->pos[2], verts);

    visual_surface_display(verts, 0);

    iterate_surfaces_envbox(verts);

    gDPSetRenderMode(gDebugPoolHead++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);

    visual_surface_display(verts, 1);

    gSPPopMatrix(gDebugPoolHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(dl_debug_box_end));
}

/**
 * Adds a box to the list to be rendered this frame.
 *
 * If there are already MAX_DEBUG_BOXES boxes, does nothing.
 */
static void append_debug_box(Vec3f center, Vec3f bounds, s16 yaw, s32 type) {
    if (hitboxView) {
        if (sNumBoxes >= MAX_DEBUG_BOXES) return;

        vec3f_to_vec3s(sBoxes[sNumBoxes].center, center);
        vec3f_to_vec3s(sBoxes[sNumBoxes].bounds, bounds);

        sBoxes[sNumBoxes].yaw   = yaw;
        sBoxes[sNumBoxes].color = sCurBoxColor;
        sBoxes[sNumBoxes].type  = type;
        if (!(sBoxes[sNumBoxes].type & (DEBUG_UCODE_REJ | DEBUG_UCODE_DEFAULT))) {
            sBoxes[sNumBoxes].type |= DEBUG_UCODE_DEFAULT;
        }
        ++sNumBoxes;
    }
}

/**
 * Draw new boxes with the given color.
 * Color format is 32-bit ARGB.
 * If the alpha component is zero, DBG_BOX_ALPHA (0x7f) will be used instead.
 * Ex: 0xFF0000 becomes 0x7FFF0000
 */
static void debug_box_color(u32 color) {
    if ((color >> 24) == 0) color |= (DBG_BOX_ALPHA << 24);
    sCurBoxColor = color;
}

/**
 * Draws a debug box from (center - bounds) to (center + bounds)
 * To draw a rotated box, use debug_box_rot()
 *
 * @see debug_box_rot()
 */
static void debug_box(Vec3f center, Vec3f bounds, s32 type) {
    append_debug_box(center, bounds, 0, type);
}

/**
 * Draws a debug box from (center - bounds) to (center + bounds), rotating it by `yaw`
 */
static void debug_box_rot(Vec3f center, Vec3f bounds, s16 yaw, s32 type) {
    append_debug_box(center, bounds, yaw, type);
}

/**
 * Draws a debug box from pMin to pMax, rotating it in the xz-plane by `yaw`
 */
static void debug_box_pos_rot(Vec3f pMin, Vec3f pMax, s16 yaw, s32 type) {
    Vec3f center, bounds;

    bounds[0] = ((pMax[0] - pMin[0]) / 2.0f);
    bounds[1] = ((pMax[1] - pMin[1]) / 2.0f);
    bounds[2] = ((pMax[2] - pMin[2]) / 2.0f);

    vec3f_sum(center, pMin, bounds);

    append_debug_box(center, bounds, yaw, type);
}

/**
 * Draws a debug box from pMin to pMax
 * To draw a rotated box this way, use debug_box_pos_rot()
 *
 * @see debug_box_pos_rot()
 */
static void debug_box_pos(Vec3f pMin, Vec3f pMax, s32 type) {
    debug_box_pos_rot(pMin, pMax, 0x0, type);
}

static void render_box(int index) {
    struct DebugBox *box = &sBoxes[index];
    s32 color = box->color;

    // Translate to the origin, rotate, then translate back, effectively rotating the box about its center
    Mtx *mtx       = debug_pool_alloc(sizeof(Mtx));
    Mtx *translate = debug_pool_alloc(sizeof(Mtx));
    Mtx *rotate    = debug_pool_alloc(sizeof(Mtx));
    Mtx *scale     = debug_pool_alloc(sizeof(Mtx));

    if ((mtx       == NULL)
     || (translate == NULL)
     || (rotate    == NULL)
     || (scale     == NULL)) return;

    mtxf_to_mtx(mtx, gMatStack[1]);
    guTranslate(translate, box->center[0],  box->center[1],  box->center[2]);
    guRotate(rotate, ((box->yaw / (f32)0x10000) * 360.0f), 0, 1.0f, 0);
    guScale(scale, ((f32) box->bounds[0] * 0.01f),
                   ((f32) box->bounds[1] * 0.01f),
                   ((f32) box->bounds[2] * 0.01f));

    gSPMatrix(gDebugPoolHead++, mtx,       (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
    gSPMatrix(gDebugPoolHead++, translate, (G_MTX_MODELVIEW | G_MTX_MUL  | G_MTX_NOPUSH));
    gSPMatrix(gDebugPoolHead++, rotate,    (G_MTX_MODELVIEW | G_MTX_MUL  | G_MTX_NOPUSH));
    gSPMatrix(gDebugPoolHead++, scale,     (G_MTX_MODELVIEW | G_MTX_MUL  | G_MTX_NOPUSH));

    gDPSetEnvColor(gDebugPoolHead++, ((color >> 16) & 0xFF),
                                       ((color >>  8) & 0xFF),
                                       ((color      ) & 0xFF),
                                       ((color >> 24) & 0xFF));

    if (box->type & DEBUG_SHAPE_BOX) {
        gSPDisplayList(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(dl_debug_box_verts));
    }
    if (box->type & DEBUG_SHAPE_CYLINDER) {
        gSPDisplayList(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(dl_debug_cylinder_verts));
    }

    gSPPopMatrix(gDebugPoolHead++, G_MTX_MODELVIEW);
}

static void render_debug_boxes(s32 type) {
    s32 i;

    debug_box_color(DBG_BOX_DEF_COLOR);

    if (sNumBoxes == 0) return;
    if (gAreaUpdateCounter < 3) return;

    gSPDisplayList(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(dl_debug_box_begin));

    for (i = 0; i < sNumBoxes; ++i) {
        if ((type & DEBUG_UCODE_DEFAULT) && (sBoxes[i].type & DEBUG_UCODE_DEFAULT)) render_box(i);
        if ((type & DEBUG_UCODE_REJ    ) && (sBoxes[i].type & DEBUG_UCODE_REJ    )) render_box(i);
    }

    if (type & DEBUG_BOX_CLEAR) {
        sNumBoxes = 0;
    }
    gSPDisplayList(gDebugPoolHead++, VIRTUAL_TO_PHYSICAL(dl_debug_box_end));
}

void DebugBox_renderHook()
{
    debug_pool_init();
    if (Hacktice_gConfig.showCollision)
    {
        gSPDisplayList(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(gDebugPoolHead));

        visual_surface_loop();
        render_debug_boxes(DEBUG_UCODE_DEFAULT | DEBUG_BOX_CLEAR);

        gSPEndDisplayList(gDebugPoolHead);
    }
}

void DebugBox_hitboxHook(struct Object *node)
{
    Vec3f bnds1, bnds2;
    // This will create a cylinder that visualises their hitbox.
    // If they do not have a hitbox, it will be a small white cube instead.
    if (node->oIntangibleTimer != -1) {
        vec3f_set(bnds1, node->oPosX, (node->oPosY - node->hitboxDownOffset), node->oPosZ);
        vec3f_set(bnds2, node->hitboxRadius, node->hitboxHeight-node->hitboxDownOffset, node->hitboxRadius);
        if (node->behavior == segmented_to_virtual((const BehaviorScript*) 0x13000780)
            || node->behavior == segmented_to_virtual((const BehaviorScript*) 0x13000afc)
            || node->behavior == segmented_to_virtual((const BehaviorScript*) 0x1300075c)) {
            debug_box_color(COLOR_RGBA32_DEBUG_WARP);
        } else {
            debug_box_color(COLOR_RGBA32_DEBUG_HITBOX);
        }

        debug_box(bnds1, bnds2, (DEBUG_SHAPE_CYLINDER | DEBUG_UCODE_REJ));
        vec3f_set(bnds1, node->oPosX, (node->oPosY - node->hitboxDownOffset), node->oPosZ);
        vec3f_set(bnds2, node->hurtboxRadius, node->hurtboxHeight, node->hurtboxRadius);
        debug_box_color(COLOR_RGBA32_DEBUG_HURTBOX);
        debug_box(bnds1, bnds2, (DEBUG_SHAPE_CYLINDER | DEBUG_UCODE_REJ));
    } else {
        vec3f_set(bnds1, node->oPosX, (node->oPosY - 15), node->oPosZ);
        vec3f_set(bnds2, 30, 30, 30);
        debug_box_color(COLOR_RGBA32_DEBUG_POSITION);
        debug_box(bnds1, bnds2, (DEBUG_SHAPE_BOX | DEBUG_UCODE_REJ));
    }
}
