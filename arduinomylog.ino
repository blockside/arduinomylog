#include <Ethernet.h>
#include <TH02_dev.h>

// TH02_dev.h Library --> https://github.com/Seeed-Studio/Grove_Temper_Humidity_TH02/blob/master/library.properties


// ARDUINO UNO R3 BOARD
// ARDUINO ETHERNET 2 SHIELD
// DEVICE GROVE - TEMPERATURE&HUMIDITY SENSOR (HIGH-ACCURACY & MINI)


byte mac[] = { [[YOUR_MAC_ADDRESS_HERE]] };   // ex: 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC
IPAddress ip([IP_ADDRESS_HERE]);  // ex: 192,168,1,2

EthernetServer server(8080); // PORT ex: 8080

char documento_json_part1[] = "{\"WeatherStation\":[{\"location\":\"Trento - Italy\",\"temperature\":\"";
char documento_json_part2[] = "\",\"humidity\":\"";
char documento_json_part3[] = "\"}]}";

void setup() {
  Serial.begin(9600);
  delay(1000);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("\nserver is at ");
  Serial.println(Ethernet.localIP());

  

  TH02.begin();
  delay(100);
}
 
void loop() {


  EthernetClient client = server.available();
  if (client) {
    

    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && currentLineIsBlank) {
          
                 
          float temper = TH02.ReadTemperature();

          float hhumidity = TH02.ReadHhumidity();

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");  
          client.println();
          client.print( documento_json_part1 );
          client.print(temper);
          client.print( documento_json_part2 );
          client.print( hhumidity );
          client.print( documento_json_part3 );

 
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);

    client.stop();
    Serial.println("\nclient disonnected");
  }
}
