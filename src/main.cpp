#include "Helper.h"
#include <iostream>

const std::string player_id = ""; // your id.
const std::string key = ""; // api that Faceit.com provide.

int main() {
  Helper helper(key);
  std::cout << helper.findMatch(player_id, "player_nickname_to_search");

  return 0;
}
