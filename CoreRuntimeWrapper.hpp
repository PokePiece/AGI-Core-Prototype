// CoreRuntimeWrapper.hpp

#ifndef CORERUNTIMEWRAPPER_HPP
#define CORERUNTIMEWRAPPER_HPP

#include <string>
#include <functional>

extern "C" {
#include "agirc.h"
}

class CoreRuntimeWrapper {
public:
    using EventCallback = std::function<void(const std::string& eventName, void* eventData)>;

    CoreRuntimeWrapper();
    ~CoreRuntimeWrapper();

    bool initialize(const std::string& configPath);
    bool start();
    void stop();
    void tick();

    bool sendSensorData(const void* data, size_t size);
    bool getCognitionState(char* buffer, size_t& size);
    bool storeMemorySnapshot(const void* data, size_t size);
    bool loadMemorySnapshot(char* buffer, size_t& size);

    void registerEventCallback(EventCallback callback);

private:
    static void eventCallbackTrampoline(const char* eventName, void* eventData);
    static CoreRuntimeWrapper* instance; // singleton pointer for static callback

    EventCallback userCallback;
};

#endif // CORERUNTIMEWRAPPER_HPP
