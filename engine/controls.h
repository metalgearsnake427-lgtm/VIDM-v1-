const char *controls_h_content = 
"#ifndef CONTROLS_H\n"
"#define CONTROLS_H\n\n"
"#include <stdbool.h>\n\n"
"typedef struct {\n"
"    bool is_paused;\n"
"    bool request_replay;\n"
"    long current_frame;\n"
"} PlaybackState;\n\n"
"void init_controls(PlaybackState *state);\n"
"void toggle_pause(PlaybackState *state);\n"
"void trigger_replay(PlaybackState *state);\n"
"void reset_replay_flag(PlaybackState *state);\n\n"
"#endif\n";

with open('controls.h', 'w') as f:
    f.write(controls_h_content)
print("controls.h written successfully.")
