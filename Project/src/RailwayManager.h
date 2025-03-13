#ifndef RAILWAY_MANAGER_H
#define RAILWAY_MANAGER_H

#include "LineManager.h"

class RailwayManager {
 private:
  LineManager* lineManagers;
  int lineManagerCount;

 public:
  /**
   * Constructor for RailwayManager.
   * @param {LineManager*} lineManagers - The array of line managers.
   * @param {int} lineManagerCount - The number of line managers.
   */
  RailwayManager(LineManager* lineManagers, int lineManagerCount)
      : lineManagers(lineManagers), lineManagerCount(lineManagerCount) {}

  /**
   * Updates all line managers.
   */
  void update() {
    for (int i = 0; i < lineManagerCount; i++) {
      lineManagers[i].update();
    }
  }

  /**
   * Gets a line manager by name.
   * @param {String} name - The name of the line manager.
   * @returns {LineManager*} The line manager with the specified name, or nullptr if not found.
   */
  LineManager* getLineManagerByName(const String& name) {
    for (int i = 0; i < lineManagerCount; i++) {
      if (lineManagers[i].getName() == name) {
        return &lineManagers[i];
      }
    }
    return nullptr;
  }

  /**
   * Gets a line manager by index.
   * @param {int} index - The index of the line manager.
   * @returns {LineManager*} The line manager at the specified index, or nullptr if out of range.
   */
  LineManager* getLineManagerByIndex(int index) {
    if (index >= 0 && index < lineManagerCount) {
      return &lineManagers[index];
    }
    return nullptr;
  }
};

#endif // RAILWAY_MANAGER_H
