#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

#define RX      15
#define TX      12
#define CheckPin1    D0
#define CheckPin2    D1
#define CheckPin3    D2
#define CheckPin4    D3
#define CheckPin5    D4

SoftwareSerial swSer(RX, TX, false, 256); // RX, TX


void send_command(char); //send sensor command
void get_valueprint(void); //get serial printf value
String get_value(void); //get string value
String get_command(String url); //connect web server and get command
void send_value(String url, String radon_value, String door_value); //send web server
void delay_hour(unsigned int); //delay hour

int checking_open1(void);//checking door1 on/off
int checking_open2(void);//checking door2 on/off
int checking_open3(void);//checking door3 on/off
int checking_open4(void);//checking door4 on/off
int checking_open5(void);//checking door5 on/off
//int check_open();//String); //check door on/off

String get_key = "";
char get_commandkey;

bool get_command_flag = false;
bool send_value_flag = false;

bool loop_flag1 = false;
bool loop_flag2 = false;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  swSer.begin(9600);
  pinMode(CheckPin1, INPUT);
  WiFiManager wifiManager;
  wifiManager.setBreakAfterConfig(true);
  wifiManager.resetSettings();
  Serial.println("set up!");
  if (!wifiManager.autoConnect("radon", "")) {
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

    String url = "192.168.0.34:3000"; //server   url 
    Serial.print("debug url ::::::");
    Serial.println(url);
    get_command_flag = false;
    send_value_flag = false;
    
    //first time get radon value
    if(!loop_flag1){
      delay_hour(1);
      loop_flag1 = true;
    }
    
    //char key = get_command(url).charAt(0);
    //Serial.print("get command ::: ");
    //Serial.println(key);
    //Serial.println(get_command(url));
    char key = 'c';
    
    if(get_command_flag){
        send_command(key);
        String radon_data = get_value();


        String door_data = (String)checking_open1();

        String door_value1 = (String)checking_open1();
        String door_value2 = (String)checking_open2();
        String door_value3 = (String)checking_open3();
        String door_value4 = (String)checking_open4();
        String door_value5 = (String)checking_open5();

        Serial.print("debug radon_value :::::::");
        Serial.print(radon_data);
        Serial.print(",  door value :::::::");
        Serial.println(door_data);
        
        Serial.print(",  door value1 :::::::");
        Serial.println(door_value1);
        Serial.print(",  door value2 :::::::");
        Serial.println(door_value2);
        Serial.print(",  door value3 :::::::");
        Serial.println(door_value3);
        Serial.print(",  door value4 :::::::");
        Serial.println(door_value4);
        Serial.print(",  door value5 :::::::");
        Serial.println(door_value5);

        do{
            send_value(url, radon_data, door_data);
            Serial.println("send server");
        }while(send_value_flag == false);
        Serial.println("send value success");
    }else{
        Serial.println("get command failed");
    }

    delay(1000);

}





void send_command(char command)
{
  switch(command)
  {
    case 's':
      swSer.print("s");
      break;
    case 'c':
      swSer.print("c");
      break;
    case 'p':
      swSer.print("p");
    break;
    case 'r':
      swSer.print("r");
    break;
    default:
      swSer.print("c");
    break;
  }
}

void get_valueprint(void)
{

  String buffer = "";
  
  while(swSer.available())
  {
    char c = swSer.read();
    buffer += c;
    delay(1000);    

    if(c == '\r\n')
    {
      break;
    }
  }
  Serial.println(buffer);
  buffer = "";
  swSer.flush();
  
}

String get_value(void)
{

  String buffer = "";
  
  while(swSer.available())
  {
    char c = swSer.read();
    buffer += c;
    delay(1000);    

    if(c == '\r\n')
    {
      break;
    }
  }
  swSer.flush();
  
  return buffer;
  
}


int checking_open1()
{
  int open_status = 0;
  //open_status = digitalRead(checking);
  open_status = digitalRead(CheckPin1);

  return open_status;
}

int checking_open2()
{
  int open_status = 0;
  //open_status = digitalRead(checking);
  open_status = digitalRead(CheckPin2);

  return open_status;
}

int checking_open3()
{
  int open_status = 0;
  open_status = digitalRead(CheckPin3);

  return open_status;
}

int checking_open4()
{
  int open_status = 0;
  open_status = digitalRead(CheckPin4);

  return open_status;
}


int checking_open5()
{
  int open_status = 0;
  open_status = digitalRead(CheckPin5);

  return open_status;
}

String get_command(String url)
{
     HTTPClient http;
      http.begin("http://" + url+"/get_command"); //send sensor value 
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
      http.begin("http://"+url+"/insert?radon_value="+data_value +"&door_data1="+door_value); //send sensor value 
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


void send_value_all(String url, String data_value, String door_value1, String door_value2, String door_value3, String door_value4, String door_value5)
{
      HTTPClient http;
      http.begin("http://"+url+"/insert?radon_value="+data_value +"&door_data1="+door_value1+"&door_data2="+door_value2+"&door_data3="+door_value3+"&door_data4="+door_value4+"&door_data5="+door_value5); //send sensor value 
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

void delay_hour(unsigned int num)
{
    unsigned int delay_time = num * 60*60;
    
    for(int i = 0; i < delay_time; i++)
    {
        delay(1000);
        Serial.println(i);
    }
   
   // Serial.print(count);
  //  Serial.print("delay ");
   // Serial.print(count);
   // Serial.println("min");
}
