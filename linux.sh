linux_unified_script = r"""#!/bin/bash

echo "--- vidM: Unified Linux Installer (Debian & Arch) ---"

if [ -f /etc/debian_version ]; then
    echo "[System: Debian/Ubuntu Detected]"
    sudo apt-get update
    sudo apt-get install -y libsdl2-dev libavcodec-dev libavformat-dev libswscale-dev libavutil-dev qt6-base-dev build-essential cmake

elif [ -f /etc/arch-release ]; then
    echo "[System: Arch Linux Detected]"
    sudo pacman -Syu --needed base-devel cmake sdl2 ffmpeg qt6-base

else
    echo "[Unknown Linux Distribution] Attempting generic build..."
fi

echo "Compiling vidM Media Engine..."
gcc main_engine.c controls.c player_impl.c -o vidM_engine -lSDL2 -lavcodec -lavformat -lswscale -lavutil

if [ $? -eq 0 ]; then
    echo "Successfully built vidM_engine for your Linux distribution."
else
    echo "Build failed. Please ensure all dev headers are installed."
fi
"""

with open('vidM_linux_unified.sh', 'w') as f:
    f.write(linux_unified_script)

import os
os.chmod('vidM_linux_unified.sh', 0o755)
print("Unified Linux installer 'vidM_linux_unified.sh' created for Arch and Debian.")
