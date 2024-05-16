#pragma once
#include <cstdint>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <nlohmann/json.hpp>
#include <ostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

class Helper {
private:
  std::string key;
  void _find(std::stringstream &ss, const std::string &player_id,
             const std::string &nickname_to_search, uint8_t query_size,
             uint32_t controlled_offset) const; // Helper function, should not to be exposed.

public:
  explicit Helper(std::string);

  Helper() = delete;

  [[nodiscard]] json sendRequest(const std::string &url) const;

  [[nodiscard]] std::string findMatch(const std::string &player_id, const std::string &nickname_to_search) const;
};
