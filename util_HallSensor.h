class HallSensor {
  private:
      int sensorPin;
      bool usePullup;
  public:
    HallSensor(int pin, bool enablePullup = false) : sensorPin(pin), usePullup(enablePullup) {
        pinMode(sensorPin, enablePullup ? INPUT_PULLUP : INPUT);
    }

    int read() {
        return digitalRead(sensorPin);
    }
};