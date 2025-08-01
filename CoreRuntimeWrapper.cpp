// CoreRuntimeWrapper.cpp

#include "CoreRuntimeWrapper.hpp"
#include <iostream>
#include <cstring>

CoreRuntimeWrapper* CoreRuntimeWrapper::instance = nullptr;

CoreRuntimeWrapper::CoreRuntimeWrapper() {
    instance = this;
    userCallback = nullptr;
}

CoreRuntimeWrapper::~CoreRuntimeWrapper() {
    stop();
    instance = nullptr;
}

bool CoreRuntimeWrapper::initialize(const std::string& configPath) {
    return agirc_init(configPath.c_str()) == 0;
}

bool CoreRuntimeWrapper::start() {
    return agirc_start() == 0;
}

void CoreRuntimeWrapper::stop() {
    agirc_stop();
}

void CoreRuntimeWrapper::tick() {
    agirc_tick();
}

bool CoreRuntimeWrapper::sendSensorData(const void* data, size_t size) {
    return agirc_send_sensor_data(data, size) == 0;
}

bool CoreRuntimeWrapper::getCognitionState(char* buffer, size_t& size) {
    int result = agirc_get_cognition_state(buffer, &size);
    if (result == 2) { // buffer too small
        std::cerr << "[CoreRuntimeWrapper] Buffer too small for cognition state.\n";
        return false;
    }
    return result == 0;
}

bool CoreRuntimeWrapper::storeMemorySnapshot(const void* data, size_t size) {
    return agirc_store_memory_snapshot(data, size) == 0;
}

bool CoreRuntimeWrapper::loadMemorySnapshot(char* buffer, size_t& size) {
    int result = agirc_load_memory_snapshot(buffer, &size);
    if (result == 2) { // buffer too small
        std::cerr << "[CoreRuntimeWrapper] Buffer too small for memory snapshot.\n";
        return false;
    }
    return result == 0;
}

void CoreRuntimeWrapper::registerEventCallback(EventCallback callback) {
    userCallback = std::move(callback);
    agirc_register_callback(eventCallbackTrampoline);
}

void CoreRuntimeWrapper::eventCallbackTrampoline(const char* eventName, void* eventData) {
    if (instance && instance->userCallback) {
        instance->userCallback(std::string(eventName), eventData);
    }
}
