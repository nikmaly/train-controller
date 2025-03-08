#ifndef RAILWAY_MANAGER_H
#define RAILWAY_MANAGER_H

#include "LineManager.h"

class RailwayManager {
 private:
  LineManager* lineManagers;
  int lineManagerCount;

 public:
  RailwayManager(LineManager* lineManagers, int lineManagerCount)
      : lineManagers(lineManagers), lineManagerCount(lineManagerCount) {}

  void update() {
    for (int i = 0; i < lineManagerCount; i++) {
      lineManagers[i].update();
    }
  }

  LineManager* getLineManagerByName(const String& name) {
    for (int i = 0; i < lineManagerCount; i++) {
      if (lineManagers[i].getName() == name) {
        return &lineManagers[i];
      }
    }
    return nullptr;
  }

  LineManager* getLineManagerByIndex(int index) {
    if (index >= 0 && index < lineManagerCount) {
      return &lineManagers[index];
    }
    return nullptr;
  }
};

#endif // RAILWAY_MANAGER_H
