
void *getTransform(void *player) {
    if (!player) return NULL;
    static const auto get_transform_ = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x281F63C));
    return (void *) get_transform_(player);
}
Vector3 get_position(void *transform) {
    if (!transform)return Vector3();
    Vector3 position;
    static const auto get_position_ = reinterpret_cast<Vector3(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x282E9CC));
    position = get_position_(transform);
    return position;
}

/*
	// RVA: 0x27F457C Offset: 0x27F457C VA: 0x27F457C
	private void get_worldToCameraMatrix_Injected(out Matrix4x4 ret) { }
 */
Matrix4x4 get_worldToCameraMatrix(void *camera){
    if (!camera)return Matrix4x4();
    Matrix4x4 matrix4X4;
    static const auto get_worldToCameraMatrix_Injected = reinterpret_cast<void(__fastcall *)(void *, Matrix4x4&)>(getAbsoluteAddress("libil2cpp.so", 0x27F457C));

    get_worldToCameraMatrix_Injected(camera, matrix4X4);
    return matrix4X4;
}

/*
    // RVA: 0x27F45D0 Offset: 0x27F45D0 VA: 0x27F45D0
	// private void get_projectionMatrix_Injected(out Matrix4x4 ret) { }
 */
Matrix4x4 get_projectionMatrix(void *camera){
    if (!camera)return Matrix4x4();
    Matrix4x4 matrix4X4;
    static const auto get_projectionMatrix_Injected = reinterpret_cast<void(__fastcall *)(void *, Matrix4x4 &)>(getAbsoluteAddress("libil2cpp.so", 0x27F45D0));
    get_projectionMatrix_Injected(camera, matrix4X4);
    return matrix4X4;
}


Vector3 WorldToScreenPoint(void *camera, Vector3 test) {
    if (!camera)return Vector3();
    Vector3 position;
    static const auto WorldToScreenPoint_Injected = reinterpret_cast<uint64_t(__fastcall *)(void *,Vector3, int, Vector3 &)>(getAbsoluteAddress("libil2cpp.so", 0x27F46BC));
      WorldToScreenPoint_Injected(camera, test, 4, position);
      return position;
}
void *get_camera() {
    static const auto get_main = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress("libil2cpp.so", 0x27F5034));
    return (void *) get_main();
}
Vector3 GetPlayerLocation(void *player) {
    return get_position(getTransform(player));
}

bool getIsDead(void *player) {
    if (!player) return NULL;
    static const auto isDead = reinterpret_cast<bool (__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x972F14));
    return isDead(player);
}

bool PlayerAlive(void *player) {
    return player != NULL && getIsDead(player) == false;
}

bool IsPlayerDead(void *player) {
    return player == NULL || getIsDead(player);
}

