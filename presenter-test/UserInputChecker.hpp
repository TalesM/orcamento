#pragma once

struct UserInputChecker {
  std::string command, result;
  UserInputChecker(const std::string &command, const std::string &result = "") : command(command), result(result)
  {
    using namespace std;
    if(command.size()) {
      cout << "Please, do " << command;
      if(result.size()) {
        cout << ", check if " << result;
      }
      cout << " and then exit." << endl;
    } else if(result.size()) {
      cout << "Check if " << result << " and then exit." << endl;
    }
  }
  ~UserInputChecker()
  {
    if(result.size() > 0) {
      using namespace std;
      cout << endl << "Did " << result << "? (y/n): ";
      string input;
      bool userInputPassed = false;
      for(;;) {
        cin >> input;
        if(input == "y" || input == "Y") {
          userInputPassed = true;
          break;
        } else if(input == "n" || input == "N") {
          break;
        }
      }
      INFO("'" << result << "' failed");
      CHECK(userInputPassed);
    }
  }
};