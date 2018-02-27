#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <SoftwareSerial.h>

#define RX      D5
#define TX      D6
#define CheckPin    D1


SoftwareSerial mySerial(RX, TX); // RX, TX


void send_command(char); //send sensor command
void get_valueprint(void); //get serial printf value
String get_value(void); //get string value
String get_command(void); //connect web server and get command
void send_value(String, String); //send web server


int check_open(void); //check door on/off

String get_key = "";

bool flag;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(CheckPin, INPUT);
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

    char command_key = (char)get_key;

    send_command(key);
    Serial.println(get_value());

    if(check_open == true)
    {
      Serial.println("door close");
    }else{
      Serial.println("door open");
    }

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

int check_open()
{
  int open_status = 0;

  open_status = digitalRead(CheckPin);

  return open_status;
}

String get_command()
{
     HTTPClient http;
      http.begin("http://get_command"); //send sensor value 
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
                  return payload;
              }else{
                return q;
              }
              
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
              return q;
          }
          http.end();
  
    delay(1000);
}

void send_value(String data_value, String door_value)
{
      HTTPClient http;
      http.begin("http://insert?radon_data="+data_value +"&door_data="+door_value); //send sensor value 
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
              }else{
                
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
          http.end();
  
    delay(1000);
}