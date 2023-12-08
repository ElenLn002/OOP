#include "CommandHistory.hpp"

void CommandHistory::addToHistory(std:string& addedCmd){
  history.push_back(addedCmd);
}
