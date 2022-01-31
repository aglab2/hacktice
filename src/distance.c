#include "distance.h"
#include "types.h"

#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "PR/ultratypes.h"

#include "cfg.h"

typedef struct Object Object;

static struct Object *_obj_find_nearest_object_with_behavior(Object* me, const BehaviorScript *behavior, f32* dist)
{
    uintptr_t* behaviorAddr = (uintptr_t*) segmented_to_virtual(behavior);
    struct Object *closestObj = NULL;
    struct Object *obj;
    struct ObjectNode *listHead;
    f32 minDist = 0x20000;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != 0 && obj != me) {
                f32 objDist = dist_between_objects(me, obj);
                if (objDist < minDist) {
                    closestObj = obj;
                    minDist = objDist;
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }

    *dist = minDist;
    return closestObj;
}

void Distance_onNormal()
{
    if (!gMarioObject)
        return;

    f32 dist;
    if (Config_showDistanceFromClosestRed())
    {
        Object* obj = _obj_find_nearest_object_with_behavior(gMarioObject, (const BehaviorScript*) 0x13003eac, &dist);
        if (obj)
            print_text_fmt_int(20, 20, "R %d", dist / 50);
    }
    if (Config_showDistanceFromClosestSecret())
    {
        Object* obj = _obj_find_nearest_object_with_behavior(gMarioObject, (const BehaviorScript*) 0x13003f1c, &dist);
        if (obj)
            print_text_fmt_int(20, 40, "S %d", dist / 50);
    }
}
