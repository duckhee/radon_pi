#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>


#define RX      D5
#define TX      D6
#define CheckPin1    D1


SoftwareSerial mySerial(RX, TX); // RX, TX


void send_command(char); //send sensor command
void get_valueprint(void); //get serial printf value
String get_value(void); //get string value
String get_command(String url); //connect web server and get command
void send_value(String url, String radon_value, String door_value); //send web server


int check_open();//String); //check door on/off

String get_key = "";

bool get_command_flag;
bool send_value_flag;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(CheckPin1, INPUT);
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

    String url = ""; //server url 

    get_command_flag = false;
    send_value_flag = false;

    char key = get_command(url).charAt(0);
    Serial.print("get command ::: ");
    Serial.println(key);
    Serial.println(get_command(url));
    //char key = 's';
    
    if(get_command_flag){
        send_command(key);
        String radon_data = get_value();
        String door_data = (String)check_open();
        do{
            send_value(url, radon_data, door_data);
            Serial.println("send server");
        }while(send_value_flag == false);
        Serial.println("send value success");
    }else{
        Serial.println("get command failed");
    }
    

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

int check_open()//String checking)
{
  int open_status = 0;
  //open_status = digitalRead(checking);
  open_status = digitalRead(CheckPin1);

  return open_status;
}

String get_command(String url)
{
     HTTPClient http;
      http.begin("http://" + url); //send sensor value 
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
                  get_command_flag = true; // command flag on
                  return payload;
              }else{
                get_command_flag = false; // command flag on
                return "c";
              }
              
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
              get_command_flag = false; // command flag on
              return "c";
             
          }
          http.end();
  
    delay(1000);
}

void send_value(String url, String data_value, String door_value)
{
      HTTPClient http;
      http.begin("http://"+url+"?radon_value="+data_value +"&door_data="+door_value); //send sensor value 
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
                  send_value_flag = true;//send value flag on
              }else{
                  send_value_flag = false;//send value flag on
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
              send_value_flag = false;//send value flag on
          }
          http.end();
  
    delay(1000);
}
