#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <SoftwareSerial.h>

#define RX      D5
#define TX      D6

SoftwareSerial mySerial(RX, TX); // RX, TX

void send_command(char);
void get_valueprint(void);
String get_value(void);



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  WiFiManager wifiManager;
  wifiManager.setBreakAfterConfig(true);
  wifiManager.resetSettings();
  Serial.println("set up!");
  if (!wifiManager.autoConnect("radonsensor", "")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("connected...yeey :)");


  Serial.println("local ip");
  Serial.println(WiFi.localIP());

  
}

void loop() { // run over and over

    char key = 'p';
  
    send_command(key);
    Serial.println(get_value());

      HTTPClient http;
      http.begin("http://insert?radon_data="+get_value()); //send sensor value 
      int httpCode = http.GET();
  
          // httpCode will be negative on error
          if(httpCode > 0) {
              // HTTP header has been send and Server response header has been handled
              Serial.printf("[HTTP] GET... code: %d\n", httpCode);
              Serial.println("success");

              // file found at server
              if(httpCode == HTTP_CODE_OK) {
                  String payload = http.getString();
                  Serial.println(payload);
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
          http.end();
  
    delay(1000);

}

void send_command(char command)
{
  switch(command)
  {
    case 's':
      mySerial.print("s");
      break;
    case 'c':
      mySerial.print("c");
      break;
    case 'p':
      mySerial.print("p");
    break;
    case 'r':
      mySerial.print("r");
    break;
    default:
      mySerial.print("c");
    break;
  }
}

void get_valueprint(void)
{

  String buffer = "";
  
  while(mySerial.available())
  {
    char c = mySerial.read();
    buffer += c;
    delay(100);    

    if(c == '\r\n')
    {
      break;
    }
  }
  Serial.println(buffer);
  buffer = "";
  mySerial.flush();
  
}

String get_value(void)
{

  String buffer = "";
  
  while(mySerial.available())
  {
    char c = mySerial.read();
    buffer += c;
    delay(100);    

    if(c == '\r\n')
    {
      break;
    }
  }
  mySerial.flush();
  
  return buffer;
  
}
