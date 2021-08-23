const { Api, JsonRpc, RpcError } = require('eosjs');
const { JsSignatureProvider } = require('eosjs/dist/eosjs-jssig');
const fetch = require('node-fetch');
const { TextEncoder, TextDecoder } = require('util');
const defaultPrivateKey = "[YOUR_PRIVATE_KEY_HERE]"; // active key on Jungle3 TestNet (eosio v.2.1.0) for arduinomylog
const signatureProvider = new JsSignatureProvider([defaultPrivateKey]);
const rpc = new JsonRpc('https://[API_ENDPOINT]', { fetch }); // a valid API Endpoint on Jungle3 TestNet
const api = new Api({ rpc, signatureProvider, textDecoder: new TextDecoder(), textEncoder: new TextEncoder() });
const UTENTEauth = "arduinomylog";

async function TEMPinserisci (UTENTEauth) {
          let response = await fetch('https://[ARDUINO_IP_HERE]') // your arduino's IP
          let users = await response.json()
try{
const result = await api.transact({
    actions: [{
      account: 'arduinomylog',
      name: 'temperature',

      authorization: [{
        actor: 'arduinomylog',
        permission: 'active'
      }],

      data: {
        username: 'arduinomylog',
        sensor_uid: '1',
        date: (Date.now()),
        temp: users.WeatherStation[0].temperature,
        humi: users.WeatherStation[0].humidity
  },
    }]
  },{
    blocksBehind: 3,
    expireSeconds: 30,
  });
  console.dir(result);
} catch (e) {
console.log('\nCaught exception: ' + e);
if (e instanceof RpcError)
  console.log(JSON.stringify(e.json, null, 2))}};

TEMPinserisci (UTENTEauth);
