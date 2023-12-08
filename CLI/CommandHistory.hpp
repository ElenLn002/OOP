#ifndef COMMANDHISTORY_HPP
#define COMMANDHISTORY_HPP

#include <vector>
#include <string>

class CommandHistory{
public:
  void addToHistory(std::string addedCmd);

private:
  std::vector<std::string> history;

};
#endif //COMMANDHISTORY_HPP
