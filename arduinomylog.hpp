#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT arduinomylog : public contract
{
public:
  using contract::contract;

  ACTION login(name username);
  ACTION temperature(name username, uint64_t sensor_uid, string date, string temp, string humi);
  ACTION resetall();

private:
 
  TABLE user_info
  {
    name username;
    uint64_t temperature_count = 0;
    auto primary_key() const { return username.value; }
  };
  typedef multi_index<name("whitelist"), user_info> whitelist_table;

  TABLE sensor_temperature
  {
    uint64_t id;
    name username;
    uint64_t sensor_uid;
    string date;
    string temp;
    string humi;
    auto primary_key() const { return id; }
    auto secondary_key() const { return username.value; }
  };
  typedef multi_index<name("logs"), sensor_temperature> logs_table;

};