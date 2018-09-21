#include "verticalbox.h"
#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  VerticalBox window;
  window.resize(1280, 720);
  window.setWindowTitle("Test GPS");
  window.show();

  return app.exec();
}
