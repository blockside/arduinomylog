#include "arduinomylog.hpp"

ACTION arduinomylog::login(name username)
{
  require_auth(get_self());

  
  whitelist_table _whitelist(get_self(), get_self().value);


  auto msg_itr = _whitelist.find(username.value);
  if (msg_itr == _whitelist.end())
  {
    _whitelist.emplace(username, [&](auto &new_user) {
      new_user.username = username;
    });
    print("Insertd user: ", username);
  }
}

ACTION arduinomylog::temperature(name username, uint64_t sensor_uid, string date, string temp, string humi)
{
  require_auth(get_self());

  whitelist_table _whitelist(get_self(), get_self().value);
  auto user_itr = _whitelist.find(username.value);
  if (user_itr == _whitelist.end())
  {
  
    eosio::check(true == false, "Must insert a user!");
  }
  else
  {
   
    uint64_t current_count = user_itr->temperature_count;
    _whitelist.modify(user_itr, username, [&](auto &user) {
      user.temperature_count = current_count + 1;
    });

  
    logs_table _logs(get_self(), get_self().value);
    
    _logs.emplace(username, [&](auto &temperature) {
      temperature.id = _logs.available_primary_key();
      temperature.username = username;
      temperature.sensor_uid = sensor_uid;
      temperature.date = date;
      temperature.temp = temp;
      temperature.humi = humi;
    });
  }
}

ACTION arduinomylog::resetall()
{
  require_auth(get_self());

  whitelist_table _whitelist(get_self(), get_self().value);

  
  auto user_itr = _whitelist.begin();
  while (user_itr != _whitelist.end())
  {
    user_itr = _whitelist.erase(user_itr);
  }

  logs_table _logs(get_self(), get_self().value);

  
  auto temperature_itr = _logs.begin();
  while (temperature_itr != _logs.end())
  {
    temperature_itr = _logs.erase(temperature_itr);
  }
}

EOSIO_DISPATCH(arduinomylog, (login)(temperature)(resetall))