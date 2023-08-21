void *getTransform(void *player) {
    if (!player) return NULL;
    static const auto get_transform_injected = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x281F63C));
    return (void *) get_transform_injected(player);
}
Vector3 get_position(void *transform) {
    if (!transform)return Vector3();
    Vector3 position;
    static const auto get_position_injected = reinterpret_cast<Vector3(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x282E9CC));
    position = get_position_injected(transform);
    return position;
}
Vector3 WorldToScreenPoint(void *transform, Vector3 test) {
    if (!transform)return Vector3();
    Vector3 position;
    static const auto WorldToScreenPoint_Injected = reinterpret_cast<uint64_t(__fastcall *)(void *,Vector3, int, Vector3 &)>(getAbsoluteAddress("libil2cpp.so", 0x27F46BC));
      WorldToScreenPoint_Injected(transform, test, 4, position);
      return position;
}
void *get_camera() {
    static const auto get_camera_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress("libil2cpp.so", 0x27F5034));
    return (void *) get_camera_injected();
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

