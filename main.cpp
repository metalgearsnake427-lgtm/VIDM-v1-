#include <QApplication>
#include "interface.hpp"
#include "rust_bridge.cpp"

extern "C" {
    #include "player.h"
    #include "controls.h"
}

// Callback function to handle search results
void onSearchCompleted(const std::string& results) {
    // Handle the search results (e.g., update the GUI)
    // This function should be connected to a signal in the Rust bridge
}

int main(int argc, char *argv[]) {
    // Initialize the Qt GUI
    QApplication app(argc, argv);

    // Create the PSP/Spotify vibe interface
    PlaylistInterface gui;
    gui.setWindowTitle("VIDM");
    gui.show();

    // Connect the search completion signal to the callback
    RustBridge::instance().onSearchCompleted = onSearchCompleted;

    // Example of triggering the Rust Search via C++ Bridge
    RustBridge::instance().triggerSearch("In-game soundtrack");

    return app.exec();
}
