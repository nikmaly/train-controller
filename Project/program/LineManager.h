#ifndef LINE_MANAGER_H
#define LINE_MANAGER_H

#include "Signal.h"
#include "Turnout.h"

class LineManager {
 private:
  String name;
  Signal* signals;
  int signalCount;
  Turnout* turnouts;
  int turnoutCount;
  int lastSignalIndex;

 public:
  LineManager(const String& name, Signal* signals, int signalCount, Turnout* turnouts, int turnoutCount)
      : name(name), signals(signals), signalCount(signalCount), turnouts(turnouts), turnoutCount(turnoutCount), lastSignalIndex(-1) {}

  void update() {
    for (int i = 0; i < signalCount; i++) {
      if (signals[i].getHallSensorValue() == HIGH) {
        if (lastSignalIndex != -1) {
          signals[lastSignalIndex].setState(true);
        }
        signals[i].setState(false);
        lastSignalIndex = i;
      }
    }
  }

  String getName() const {
    return name;
  }

  void setTurnoutState(int index, bool state) {
    if (index >= 0 && index < turnoutCount) {
      turnouts[index].setSwitchState(state);
    }
  }

  bool getTurnoutState(int index) const {
    if (index >= 0 && index < turnoutCount) {
      return turnouts[index].getSwitchState();
    }
    return false;
  }

  void setTurnoutState(const String& name, bool state) {
    for (int i = 0; i < turnoutCount; i++) {
      if (turnouts[i].getName() == name) {
        turnouts[i].setSwitchState(state);
        break;
      }
    }
  }

  bool getTurnoutState(const String& name) const {
    for (int i = 0; i < turnoutCount; i++) {
      if (turnouts[i].getName() == name) {
        return turnouts[i].getSwitchState();
      }
    }
    return false;
  }

  void setSignalState(int index, bool state) {
    if (index >= 0 && index < signalCount) {
      signals[index].setState(state);
    }
  }

  void setSignalState(const String& name, bool state) {
    for (int i = 0; i < signalCount; i++) {
      if (signals[i].getName() == name) {
        signals[i].setState(state);
        break;
      }
    }
  }

  bool getSignalState(int index) const {
    if (index >= 0 && index < signalCount) {
      return signals[index].getState();
    }
    return true;
  }

  bool getSignalState(const String& name) const {
    for (int i = 0; i < signalCount; i++) {
      if (signals[i].getName() == name) {
        return signals[i].getState();
      }
    }
    return true;
  }
};

#endif // LINE_MANAGER_H
