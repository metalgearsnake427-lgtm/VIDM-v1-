#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdbool.h>

typedef struct {
    bool is_paused;
    bool request_replay;
    long current_frame;
} PlaybackState;

void init_controls(PlaybackState *state);
void toggle_pause(PlaybackState *state);
void trigger_replay(PlaybackState *state);
void reset_replay_flag(PlaybackState *state);

#endif
"""

with open('controls.h', 'w') as f:
    f.write(controls_h_content)
print("controls.h written successfully.")
