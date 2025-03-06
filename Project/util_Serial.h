/**
 * @typedef {Object} SerialCommand
 * @property {String} target - The target of the command (e.g., "motor").
 * @property {String} action - The action to be performed (e.g., "stop", "direction", "speed").
 * @property {String} value - The value associated with the action (e.g., "forward", "backward", speed value).
 */
struct SerialCommand {
  String target;
  String action;
  String value;

  bool isValid() {
    return target.length() > 0 && action.length() > 0;
  }
};

class SerialHandler {

  public:

    /**
     * Reads a command from the serial input.
     * @returns {SerialCommand} The parsed command.
     */
    SerialCommand readCommand() {
      SerialCommand command = {"", "", ""};

      if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input == "s") {
          command.target = "motor";
          command.action = "stop";
        } else if (input == "f") {
          command.target = "motor";
          command.action = "direction";
          command.value = "forward";
        } else if (input == "b") {
          command.target = "motor";
          command.action = "direction";
          command.value = "backward";
        } else if (input.startsWith("change track")) {
          command.target = "motor";
          command.action = "change track";

          if (input.length() > 12) {
            String trackName = input.substring(12);
            trackName.trim();
            command.value = trackName;
          }
        } else if (input.startsWith("servo ")) {
          int firstSpace = input.indexOf(' ');
          int secondSpace = input.indexOf(' ', firstSpace + 1);
          command.target = "servo";
          command.action = input.substring(firstSpace + 1, secondSpace);
          command.value = input.substring(secondSpace + 1);
        } else { 
          int speedValue = input.toInt();

          if (speedValue >= 0 && speedValue <= 100) {
            command.target = "motor";
            command.action = "speed";
            command.value = String(speedValue);
          } else {
            Serial.println("Invalid input. Enter 's', 'f', 'b', 'change track [track name]' or a number 0-100.");
          }
        }
      }
      return command;
    }
};