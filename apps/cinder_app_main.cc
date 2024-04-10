#include "adventure_app.h"

using adventure::AdventureApp;

void prepareSettings(AdventureApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(AdventureApp, ci::app::RendererGl, prepareSettings);