#include "Helper.h"

Helper::Helper(std::string _key) 
  : key(std::move(_key)) {}

json Helper::sendRequest(const std::string &url) const {
  std::stringstream ss;
  json j;

  std::list<std::string> header;
  header.emplace_back("accept: application/json");
  header.emplace_back("Authorization: Bearer " + key);

  try {
    curlpp::Cleanup my_cleanup;
    curlpp::Easy my_request;

    my_request.setOpt<curlpp::options::Url>(url);
    my_request.setOpt<curlpp::options::HttpHeader>(header);
    my_request.setOpt<curlpp::options::WriteStream>(&ss);

    my_request.perform();
  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << std::endl;
  } catch (curlpp::LogicError &e) {
    std::cout << e.what() << std::endl;
  }

  ss >> j;
  return j;
}

std::string Helper::findMatch(const std::string &player_id,
                             const std::string &nickname_to_search) const {
  std::stringstream ss;
  uint32_t offset = 0;
  uint8_t query_size = 100;

  while (offset < 1000) {
    _find(ss, player_id, nickname_to_search, query_size, offset);
    offset += query_size;
  }

  return ss.str();
}

void Helper::_find(std::stringstream &ss, 
                  const std::string &player_id,
                  const std::string &nickname_to_search, 
                  uint8_t query_size,
                  uint32_t controlled_offset) const {

  std::string url =
    "https://open.faceit.com/data/v4/players/" + player_id +
    "/history?game=csgo&offset=" + std::to_string(controlled_offset) +
    "&limit=" + std::to_string(query_size);

  auto raw_json = sendRequest(url); 
  auto &temp_ret = raw_json.at("items");

  for (const auto &i : temp_ret) {
    const auto &players2 = i.at("teams").at("faction2").at("players");
    const auto &players1 = i.at("teams").at("faction1").at("players");
    bool skip = false; /* Flag for if it finds in first team, dont search
                          in second team.
                        */
    for (const auto &p : players2) {
      if (nickname_to_search == p.at("nickname").get<std::string>()) {
        ss << "https://www.faceit.com/en/csgo/"
              "room/"
           << i.at("match_id").get<std::string>() << "/scoreboard\n";
        skip = true;
        break;
      }
    }
    if (!skip) {
      for (const auto &p : players1) {
        if (nickname_to_search == p.at("nickname").get<std::string>()) {
          ss << "https://www.faceit.com/en/csgo/"
                "room/"
             << i.at("match_id").get<std::string>() << "/scoreboard\n";
          break;
        }
      }
    }
  }
}