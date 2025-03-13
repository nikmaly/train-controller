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
  /**
   * Constructor for LineManager.
   * @param {String} name - The name of the line manager.
   * @param {Signal*} signals - The array of signals.
   * @param {int} signalCount - The number of signals.
   * @param {Turnout*} turnouts - The array of turnouts.
   * @param {int} turnoutCount - The number of turnouts.
   */
  LineManager(const String& name, Signal* signals, int signalCount, Turnout* turnouts, int turnoutCount)
      : name(name), signals(signals), signalCount(signalCount), turnouts(turnouts), turnoutCount(turnoutCount), lastSignalIndex(-1) {}

  /**
   * Updates the line manager.
   */
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

  /**
   * Gets the name of the line manager.
   * @returns {String} The name of the line manager.
   */
  String getName() const {
    return name;
  }

  /**
   * Sets the state of a turnout by index.
   * @param {int} index - The index of the turnout.
   * @param {bool} state - The new state of the turnout.
   */
  void setTurnoutState(int index, bool state) {
    if (index >= 0 && index < turnoutCount) {
      turnouts[index].setSwitchState(state);
    }
  }

  /**
   * Gets the state of a turnout by index.
   * @param {int} index - The index of the turnout.
   * @returns {bool} The state of the turnout.
   */
  bool getTurnoutState(int index) const {
    if (index >= 0 && index < turnoutCount) {
      return turnouts[index].getSwitchState();
    }
    return false;
  }

  /**
   * Sets the state of a turnout by name.
   * @param {String} name - The name of the turnout.
   * @param {bool} state - The new state of the turnout.
   */
  void setTurnoutState(const String& name, bool state) {
    for (int i = 0; i < turnoutCount; i++) {
      if (turnouts[i].getName() == name) {
        turnouts[i].setSwitchState(state);
        break;
      }
    }
  }

  /**
   * Gets the state of a turnout by name.
   * @param {String} name - The name of the turnout.
   * @returns {bool} The state of the turnout.
   */
  bool getTurnoutState(const String& name) const {
    for (int i = 0; i < turnoutCount; i++) {
      if (turnouts[i].getName() == name) {
        return turnouts[i].getSwitchState();
      }
    }
    return false;
  }

  /**
   * Sets the state of a signal by index.
   * @param {int} index - The index of the signal.
   * @param {bool} state - The new state of the signal.
   */
  void setSignalState(int index, bool state) {
    if (index >= 0 && index < signalCount) {
      signals[index].setState(state);
    }
  }

  /**
   * Sets the state of a signal by name.
   * @param {String} name - The name of the signal.
   * @param {bool} state - The new state of the signal.
   */
  void setSignalState(const String& name, bool state) {
    for (int i = 0; i < signalCount; i++) {
      if (signals[i].getName() == name) {
        signals[i].setState(state);
        break;
      }
    }
  }

  /**
   * Gets the state of a signal by index.
   * @param {int} index - The index of the signal.
   * @returns {bool} The state of the signal.
   */
  bool getSignalState(int index) const {
    if (index >= 0 && index < signalCount) {
      return signals[index].getState();
    }
    return true;
  }

  /**
   * Gets the state of a signal by name.
   * @param {String} name - The name of the signal.
   * @returns {bool} The state of the signal.
   */
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
