/* SerialTemp example
 
 Copyright 2017 Isaac100

 This example writes the current temperarure in celsius
 and fahrenheit to the serial monitor.

*/
// ARDUINO UNO BOARD
// ARDUINO ETHERNET SHIELD
// TEMP DEVICE TMP36
#include <Ethernet.h>
#include <TMP36.h>
byte mac[] = { [YOUR_MAC_ADDRESS_HERE] };   // ex: 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC
IPAddress ip([IP_ADDRESS_HERE]);  // ex: 192,168,1,2
EthernetServer server([YOUR_PORT_HERE]); // ex: 8080
char documento_json_part1[] = "{\"WeatherStation\":[{\"location\":\"Trento - Italy\",\"temperature celsius\":\"";
char documento_json_part2[] = "\",\"temperature fahrenheit\":\"";
char documento_json_part3[] = "\"}]}";
//Create an instance of the TMP36 class and 
//define the pin the sensor is connected to
//If using 3.3v Arduino, change 5 to 3.3
TMP36 myTMP36(A0, 5.0); 
void setup() {
  Serial.begin(9600);
  delay(500);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("\nserver is at ");
  Serial.println(Ethernet.localIP());
}
void loop() {
EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && currentLineIsBlank) {
  float celsius = myTMP36.getTempC(); 
  float fahrenheit = myTMP36.getTempF();
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");  
          client.println();
          client.print( documento_json_part1 );
          client.print( celsius );
          client.print( documento_json_part2 );
          client.print( fahrenheit );
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
