enum E_AgentType {
    // Fields
    value__,
    None = -1,
    Player = 0,
    Walker1 = 1,
    ZombieSlow1 = 2,
    ZombieFast1 = 3,
    Berserker = 4,
    Infectator = 5,
    Armored = 6,
    Meleer = 7,
    Bomber = 8,
    Temelin = 9,
    Butcher = 10,
    Grenadier = 11,
    Lightning = 12,
    Mother = 13,
    TougherZombie = 14,
    Spider = 15,
    Medic = 20,
    Gunsmith = 21,
    Scientist = 22,
    Smuggler = 23,
    Engineer = 24,
    FemaleFriend = 25,
    MaleFriend = 26,
    Thabo = 27,
    Adamos = 28,
    Hank = 29,
    Casual = 30,
    Combat = 31,
    Guard = 32,
    Ranger = 33,
    TNT = 34,
    PlayerProxy = 35,
    ChickenZombie = 36,
    Max = 37
};

void *getTransform(void *player) {
    if (!player) return NULL;

    unsigned long get_Transform_offset = 0;
#if defined(__aarch64__)
    get_Transform_offset = 0xA2076C;
#else
    get_Transform_offset = 0x4EEEA0;
#endif
    static const auto get_transform_ = reinterpret_cast<uint64_t(__fastcall *)(void *)>(
            getAbsoluteAddress("libil2cpp.so", get_Transform_offset));
    void * get_transform_ret =  (void *) get_transform_(player);
    return get_transform_ret;
}

Vector3 get_position(void *transform) {
    if (!transform)return Vector3();

    Vector3 position;
    unsigned long get_position_offset = 0;
#if defined(__aarch64__)
    get_position_offset = 0x16E9DC4;
#else
    get_position_offset = 0x1439B04;
#endif
    static const auto get_position_ = reinterpret_cast<void(__fastcall *)(void *, Vector3&)>(
            getAbsoluteAddress("libil2cpp.so", get_position_offset));
    get_position_(transform, position);
    return position;
}

Matrix4x4 get_worldToCameraMatrix(void *camera){
    if (!camera)return Matrix4x4();

    Matrix4x4 matrix4X4;
    unsigned long get_worldToCameraMatrix_offset = 0;
#if defined(__aarch64__)
    get_worldToCameraMatrix_offset = 0x125E534;
#else
    get_worldToCameraMatrix_offset = 0xEDC6F4;
#endif
    static const auto get_worldToCameraMatrix_Injected = reinterpret_cast<void(__fastcall *)(void *, Matrix4x4&)>(
            getAbsoluteAddress("libil2cpp.so", get_worldToCameraMatrix_offset));
    get_worldToCameraMatrix_Injected(camera, matrix4X4);
    return matrix4X4;
}

Matrix4x4 get_projectionMatrix(void *camera){
    if (!camera)return Matrix4x4();

    Matrix4x4 matrix4X4;
    unsigned long get_projectionMatrix_offset = 0;
#if defined(__aarch64__)
    get_projectionMatrix_offset = 0x125E69C;
#else
    get_projectionMatrix_offset =  0xEDC904;
#endif
    static const auto get_projectionMatrix_Injected = reinterpret_cast<void(__fastcall *)(void *, Matrix4x4 &)>(
            getAbsoluteAddress("libil2cpp.so", get_projectionMatrix_offset));
    get_projectionMatrix_Injected(camera, matrix4X4);
    return matrix4X4;
}

Vector3 WorldToScreenPoint(void *camera, Vector3 test) {
    if (!camera)return Vector3();

    Vector3 position;
    unsigned long WorldToScreenPoint_offset = 0;
#if defined(__aarch64__)
    WorldToScreenPoint_offset = 0x125E848;
#else
    WorldToScreenPoint_offset = 0xEDCB60;
#endif
    static const auto WorldToScreenPoint_Injected = reinterpret_cast<uint64_t(__fastcall *)(void *,Vector3, int, Vector3 &)>(
            getAbsoluteAddress("libil2cpp.so", WorldToScreenPoint_offset));
      WorldToScreenPoint_Injected(camera, test, 4, position);
      return position;
}

void *get_camera() {
    unsigned long get_camera_offset = 0;
#if defined(__aarch64__)
    get_camera_offset = 0x125EE40;
#else
    get_camera_offset = 0xEDD360;
#endif
    static const auto get_main = reinterpret_cast<uint64_t(__fastcall *)()>(
            getAbsoluteAddress("libil2cpp.so", get_camera_offset));
    return (void *) get_main();
}

Vector3 GetPlayerLocation(void *player) {
    return get_position(getTransform(player));
}

bool getIsPlayer(void *player) {
    if (!player) return NULL;

    unsigned long getIsPlayer_offset = 0;
#if defined(__aarch64__)
    getIsPlayer_offset = 0xA2079C;
#else
    getIsPlayer_offset = 0x4EEED0;
#endif
    static const auto get_IsPlayer = reinterpret_cast<bool (*)(void *)>(
            getAbsoluteAddress("libil2cpp.so", getIsPlayer_offset));
    return get_IsPlayer(player);
}

int getAgentType(void *player) {
    if (!player) return NULL;

    unsigned long getAgentType_offset = 0;
#if defined(__aarch64__)
    getAgentType_offset = 0xA1D58C;
#else
    getAgentType_offset = 0x4EB404;
#endif
    static const auto get_AgentType = reinterpret_cast<int (*)(void *)>(
            getAbsoluteAddress("libil2cpp.so", getAgentType_offset));
    return get_AgentType(player);
}

bool getIsDead(void *player) {
    if (!player) return NULL;

    unsigned long isDead_offset = 0;
#if defined(__aarch64__)
    isDead_offset = 0xA24584;
#else
    isDead_offset = 0x4F3FF8;
#endif
    static const auto isDead = reinterpret_cast<float(*)(void *, float)>(
            getAbsoluteAddress("libil2cpp.so", isDead_offset));
    return isDead(player, 0) == 0 ? true : false;
}

bool PlayerAlive(void *player) {
    return player != NULL && getIsDead(player) == false;
}

bool IsPlayerDead(void *player) {
    return player == NULL || getIsDead(player);
}

