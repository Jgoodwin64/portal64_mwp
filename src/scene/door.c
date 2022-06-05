#include "door.h"

#include "../graphics/render_scene.h"
#include "defs.h"
#include "../models/models.h"
#include "../scene/dynamic_scene.h"
#include "signals.h"
#include "../math/mathf.h"
#include "../util/time.h"

#include "../build/assets/models/props/door_01.h"

#define OPEN_VELOCITY   8.0f

void doorRender(void* data, struct RenderScene* renderScene) {
    struct Door* door = (struct Door*)data;
    Mtx* matrix = renderStateRequestMatrices(renderScene->renderState, 1);
    transformToMatrixL(&door->rigidBody.transform, matrix, SCENE_SCALE);

    props_door_01_default_bones[PROPS_DOOR_01_DOORL_BONE].position.x = door->openAmount * -0.55f * SCENE_SCALE;
    props_door_01_default_bones[PROPS_DOOR_01_DOORR_BONE].position.x = door->openAmount * 0.55f * SCENE_SCALE;

    Mtx* armature = renderStateRequestMatrices(renderScene->renderState, PROPS_DOOR_01_DEFAULT_BONES_COUNT);
    transformToMatrixL(&props_door_01_default_bones[PROPS_DOOR_01_FRAME_BONE], &armature[PROPS_DOOR_01_FRAME_BONE], 1.0f);
    transformToMatrixL(&props_door_01_default_bones[PROPS_DOOR_01_DOORL_BONE], &armature[PROPS_DOOR_01_DOORL_BONE], 1.0f);
    transformToMatrixL(&props_door_01_default_bones[PROPS_DOOR_01_DOORR_BONE], &armature[PROPS_DOOR_01_DOORR_BONE], 1.0f);

    renderSceneAdd(renderScene, door_01_gfx, matrix, door_01_material_index, &door->rigidBody.transform.position, armature);
}

void doorInit(struct Door* door, struct Transform* at, int roomA, int roomB, int doorwayIndex, int signalIndex) {
    // collisionObjectInit(&cube->collisionObject, &gCubeCollider, &cube->rigidBody, 1.0f);
    // collisionSceneAddDynamicObject(&cube->collisionObject);

    // cube->collisionObject.body->flags |= RigidBodyFlagsGrabbable;

    door->rigidBody.transform = *at;

    door->dynamicId = dynamicSceneAdd(door, doorRender, &door->rigidBody.transform, 1.7f);
    door->signalIndex = signalIndex;
    door->openAmount = 0.0f;
}

void doorUpdate(struct Door* door) {
    float targetOpenAmount = signalsRead(door->signalIndex) ? 1.0f : 0.0f;
    door->openAmount = mathfMoveTowards(door->openAmount, targetOpenAmount, OPEN_VELOCITY * FIXED_DELTA_TIME);
}