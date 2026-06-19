#include "controls.h"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h> 


typedef struct {
    bool is_paused;
    bool request_replay;
    int current_frame;
} PlaybackState;

void init_controls(PlaybackState *state) {
    if (state == NULL) return;
    state->is_paused = false;
    state->request_replay = false;
    state->current_frame = 0;
}

void toggle_pause(PlaybackState *state) {
    if (state == NULL) return;
    state->is_paused = !state->is_paused;
    printf("[Engine] Playback %s.\n", state->is_paused ? "Paused" : "Resumed");
}

void trigger_replay(PlaybackState *state) {
    if (state == NULL) return;
    state->request_replay = true;
    state->current_frame = 0;
    printf("[Engine] Replay Requested.\n");
}

void reset_replay_flag(PlaybackState *state) {
    if (state == NULL) return;
    state->request_replay = false;
}
