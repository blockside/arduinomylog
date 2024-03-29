ArduinoMyLog
============

## Project ArduinoMyLog - (EOS.io based)

This project will store into an EOS.io based Blockchain, the data of temperature and humidity provided by Arduino.

## Quick links and licensing references

- [EOSIO is a next-generation, open-source blockchain protocol with industry-leading transaction speed and flexible utility.](https://github.com/EOSIO)
- [Arduino library to control Grove Temper Humidity TH02](https://github.com/Seeed-Studio/Grove_Temper_Humidity_TH02)
- [NodeJS](https://nodejs.org)


## Tested for 

* ARDUINO UNO R3 BOARD with ARDUINO ETHERNET 2 SHIELD (https://store.arduino.cc)
* Grove - Temperature&Humidity Sensor (High-Accuracy & Mini) multifunctional sensor that gives you temperature and relative humidity 
(https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-High-Accuracy-Mini.html)


## Notice
This software is experimental and a work in progress. Data inserted into blockchain will be accessible to anyone.
Under no circumstances should these files be used in relation to any critical system(s).
Use of these files is at your own risk.
THE SOFTWARE IS PROVIDED "AS IS". See license file LICENSE.md for details.

## Quick start

* We assume that the arduinomylog.ino file has been loaded correctly on the Arduino and that by calling the Arduino IP in a browser we obtain a result similar to this:

{"WeatherStation":[{"location":"Trento - Italy","temperature":"26.25","humidity":"63.75"}]}

* Now we have to choose a blockchain, for this example based on EOSIO, on which storing the temperature and humidity data retrieved from the sensor installed on Arduino. For this example we'll use XPR Network Testnet; If you are not familiar with how an eosio-based blockchain works, it is recommended to read more information here: https://developers.eos.io
Then you can go to https://testnet.explorer.xprnetwork.org , and create your account. For this example account "arduinomylog" is used. 

* Enter directory arduinomylog and create the samrt contract that will store temperature and humidity data provided by Arduino:

eosio-cpp -version

eosio-cpp version 1.8.1

eosio-cpp -abigen arduinomylog.cpp -o arduinomylog.wasm

(Todo: add Ricardian data to Smart Contract)

* Deploy the Smart Contract:

cleos -u https://[API_ENDPOINT] set contract [CONTRACT_ACCOUNT] [CONTRACT_NAME_FOLDER_PATH] -p [ACTIVE_KEY]

Note: API_ENDPOINT's servers could be find on XPR Network Testnet
In this case:

cleos -u https://[API_ENDPOINT] set contract arduinomylog /PATH/TO/arduinomylog -p arduinomylog@active

* Insert your account into Whitelist table; in this case:

cleos -u https://[API_ENDPOINT] push transaction '{"delay_sec": 0,"max_cpu_usage_ms": 0,"actions": [{"account":"arduinomylog","name": "login","data": {"username":"arduinomylog"},"authorization": [{"actor": "arduinomylog","permission":"active"}]}]}'

* check that NodeJS is installed:

node -v

v14.17.4

npm -v

7.20.6

* check that EOSJS is installed (for this example we use v22.1.0 Release)

* insert your account's Private key, an API Endoint and your Arduino's IP, into file arduinomylog.js ; then change it's permissions:

chmod 700 arduinomylog.js

* intialize Nodejs and install software dependencies in order to obtain this package.json:

cat package.json

{
  "name": "arduinomylog",
  "version": "1.0.0",
  "description": "Temperature Humidity Logger",
  "main": "arduinomylog.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "",
  "license": "ISC",
  "dependencies": {
    "eosjs": "^22.1.0",
    "node-fetch": "^2.6.1",
    "util": "^0.12.4"
  }
}


## Usage

node arduinomylog.js


## Monitor

See your data on blockchain (accessible to anyone) by accessing a blockchain explorer; in this case:
https://testnet.explorer.xprnetwork.org/account/arduinomylog



## Optional

Modify file update.sh and add parameters to crontab to insert the temperature and humidity data into blockchain, every fifteen minutes:

0,15,30,45 * * * * /PATH/TO/update.sh
