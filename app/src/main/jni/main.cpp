#include <list>
#include <vector>
#include <string>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "Unity/Vector2.h"
#include "Unity/Vector3.h"
#include "Unity/Vector4.h"
#include "Unity/Rect.h"
#include "Unity/Color.h"
#include "Unity/Quaternion.h"
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Includes/Chams.h"
#include "Includes/MonoString.h"
#include "Includes/Strings.h"
#include "KittyMemory/MemoryPatch.h"
#include "menu.h"
#include "NepDraw.h"
#include "hooks.h"
#include "ESPManager.h"
ESPManager *espManager;
NepEsp es;

#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

bool ESP, ESPLine;

void DrawESP(NepEsp esp, int screenWidth, int screenHeight) {
    //esp.DrawText(Color::Yellow(), "NepMods", Vector2(screenWidth / 2, screenHeight / 1.2), 17);

    if (ESP) {
        //Code Goes Inside it
        //判断敌人数量是否为空
        if (espManager->enemies->empty()) {
            return;
        }
        //遍历所有敌人
        for (int i = 0; i < espManager->enemies->size(); i++) {
            //Code Goes Here
            void *Player = (*espManager->enemies)[i]->object;

            //判断血量（是否存活
            if (PlayerAlive(Player)) {
                //Code Goes Here
                //获取玩家世界坐标
                Vector3 PlayerPos = GetPlayerLocation(Player);
                //获得相机对象
                void *Cam = get_camera();
                if(Cam){
                    __android_log_print(ANDROID_LOG_DEBUG, "reverccqin", "Cam : %p", Cam);
                    //将世界坐标转化为屏幕坐标(内部通过相机对象获取其中的viewMatrix视图矩阵，然后与世界坐标进行矩阵转换后得到屏幕坐标
                    Vector3 PosNew = WorldToScreenPoint(Cam, PlayerPos);


                    //获得视图矩阵 viewMatrix
                    Matrix4x4 viewMatrix = get_worldToCameraMatrix(Cam);

                    //获得裁剪（投影）矩阵projectionMatrix
                    Matrix4x4 projectionMatrix = get_projectionMatrix(Cam);

                    // vp 组合矩阵
                    Matrix4x4 Matix_VP_LastFrame =  viewMatrix * projectionMatrix;

                    // 世界坐标
                    Vector4* tmp_pos = new Vector4(PlayerPos.x, PlayerPos.y, PlayerPos.z, 1);

                    // vp组合矩阵 * 世界坐标 == 裁剪坐标（投影坐标）
                    Vector4 clipPos = *tmp_pos * Matix_VP_LastFrame;

                    // 投影坐标经过透视除法后得到 屏幕坐标比例值，x与y是比例，需要*屏幕的宽度和高度
                    // w < 0则说明物体不再视角范围内，不需要在屏幕中显示
                    float x = 0.5f + 0.5f * clipPos.x / clipPos.w;
                    float y = 0.5f + 0.5f * clipPos.y / clipPos.w;

                    //如果离相机的位置很近就不画了
                    // clipPos.w < 1.f 也可以
                    if (PosNew.z < 1.f) continue;
                    //More Code Here
                    //画线的起点：屏幕的上方中间位置
                    Vector2 DrawFrom = Vector2(screenWidth / 2, 0);
                    //画线的终点
                    Vector2 DrawTo = Vector2((screenWidth - (screenWidth - x * screenWidth)) + 5,
                                             (screenHeight - y * screenHeight - 80.0f));
                    if (ESPLine) {
                        esp.DrawLine(Color::Red(), 2, DrawFrom, DrawTo);
                    }
                }

            } else {
                espManager->removeEnemyGivenObject(Player);
            }
        }

    }

}
extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_DrawOn(JNIEnv *env, jclass type, jobject espView, jobject canvas) {
                es = NepEsp(env, espView, canvas);
    if (es.isValid()){
        DrawESP(es, es.getWidth(), es.getHeight());
    }

 }


void *enemyPlayer = NULL;
void (*update)(void *player);
void _update(void *player) {
    if (player != NULL) {
        update(player);
        enemyPlayer = player;
    }
    if (ESP) {
        if (enemyPlayer) {
            espManager->tryAddEnemy(player);
        }
        espManager->updateEnemies(NULL);
    }
}


void *hack_thread(void *) {
    ProcMap il2cppMap;
    do {
        il2cppMap = KittyMemory::getLibraryMap("libil2cpp.so");
        sleep(1);
    } while (!isLibraryLoaded("libil2cpp.so") && mlovinit());
    espManager = new ESPManager();

    do {
        sleep(1);
    } while (!isLibraryLoaded (OBFUSCATE("libMyLibName.so")));

    
    MSHookFunction((void *) getAbsoluteAddress("libil2cpp.so", 0x973E3C), (void *) &_update, (void **) &update);
    return NULL;
}

extern "C" {
JNIEXPORT jobjectArray
JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;
    const char *features[] = {
            OBFUSCATE("0_Toggle_Enable Esp"),//0
            OBFUSCATE("1_Toggle_ESP Line"),//1


    };
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}


JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    switch (featNum) {
        case 0:
            ESP = boolean;
            break;
        case 1:
            ESPLine = boolean;

            break;

    }
}
}

__attribute__((constructor))
void lib_main() {

    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

