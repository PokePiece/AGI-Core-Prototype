// agirc.c — Expanded core logic flow with modular calls

#include "agirc.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Forward declarations of stub component functions
void sensor_io_collect();
void cognition_process();
void goal_system_evaluate();
void action_exec_perform();
void memory_store_episode();

static bool is_running = false;
static agirc_event_callback_t registered_callback = NULL;

int agirc_init(const char* config_path) {
    printf("[agirc] Initializing runtime with config: %s\n", config_path ? config_path : "(null)");
    // TODO: Initialize subsystem states here
    is_running = false;
    return 0;
}

int agirc_start(void) {
    if (is_running) {
        printf("[agirc] Runtime already running.\n");
        return 1;
    }
    printf("[agirc] Starting runtime loop.\n");
    is_running = true;
    return 0;
}

void agirc_stop(void) {
    if (!is_running) {
        printf("[agirc] Runtime not running.\n");
        return;
    }
    printf("[agirc] Stopping runtime loop.\n");
    is_running = false;
}

void agirc_tick(void) {
    if (!is_running) {
        printf("[agirc] Runtime tick called but runtime not running.\n");
        return;
    }
    printf("[agirc] Tick - running cognitive cycle.\n");

    sensor_io_collect();
    cognition_process();
    goal_system_evaluate();
    action_exec_perform();
    memory_store_episode();

    if (registered_callback) {
        registered_callback("TickCompleted", NULL);
    }
}

int agirc_send_sensor_data(const void* data, size_t size) {
    printf("[agirc] Received sensor data of size %zu bytes.\n", size);
    // TODO: Buffer/process sensor data here or forward to sensor_io module
    return 0;
}

int agirc_get_cognition_state(void* buffer, size_t* size) {
    if (!buffer || !size || *size == 0) return 1;

    const char* dummy_state = "CognitionStatePlaceholder";
    size_t needed = strlen(dummy_state) + 1;
    if (*size < needed) {
        *size = needed;
        return 2;
    }
    memcpy(buffer, dummy_state, needed);
    *size = needed;
    printf("[agirc] Provided cognition state to caller.\n");
    return 0;
}

int agirc_store_memory_snapshot(const void* data, size_t size) {
    printf("[agirc] Storing memory snapshot of size %zu bytes.\n", size);
    return 0;
}

int agirc_load_memory_snapshot(void* buffer, size_t* size) {
    if (!buffer || !size || *size == 0) return 1;

    const char* dummy_snapshot = "MemorySnapshotPlaceholder";
    size_t needed = strlen(dummy_snapshot) + 1;
    if (*size < needed) {
        *size = needed;
        return 2;
    }
    memcpy(buffer, dummy_snapshot, needed);
    *size = needed;
    printf("[agirc] Loaded memory snapshot to caller.\n");
    return 0;
}

void agirc_register_callback(agirc_event_callback_t callback) {
    registered_callback = callback;
    printf("[agirc] Event callback registered.\n");
}
