// agirc.h — Core AGI Runtime C API

#ifndef AGIRC_H
#define AGIRC_H

#ifdef __cplusplus
extern "C" {
#endif

// Initialize the runtime environment, optionally with a config path.
// Returns 0 on success, nonzero on error.
int agirc_init(const char* config_path);

// Start the persistent runtime loop.
// Returns 0 on success, nonzero on error.
// This can run in blocking or non-blocking mode depending on implementation.
int agirc_start(void);

// Stop the runtime loop gracefully.
void agirc_stop(void);

// Manually trigger one tick of the runtime loop (for external loop integration).
void agirc_tick(void);

// Send raw sensor data to the runtime.
// Returns 0 on success, nonzero on error.
int agirc_send_sensor_data(const void* data, size_t size);

// Retrieve cognition state into a buffer.
// Returns 0 on success, nonzero on error.
int agirc_get_cognition_state(void* buffer, size_t* size);

// Store a snapshot of episodic memory.
// Returns 0 on success, nonzero on error.
int agirc_store_memory_snapshot(const void* data, size_t size);

// Load a snapshot of episodic memory.
// Returns 0 on success, nonzero on error.
int agirc_load_memory_snapshot(void* buffer, size_t* size);

// Event callback type signature.
typedef void (*agirc_event_callback_t)(const char* event_name, void* event_data);

// Register a callback for runtime events.
void agirc_register_callback(agirc_event_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif // AGIRC_H
