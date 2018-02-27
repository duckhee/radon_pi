
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#define CheckPin        8 //check door on/off

void send_command(char);
void get_valueprint(void);
String get_value(void);
int check_open();

int open_status = 0;


void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600); 
    pinMode(CheckPin, INPUT);
    Serial.println("set");
}

void loop()
{
    char key = 'p';

    send_command(key);
    Serial.println(get_value());
    if(check_open() == true)
    {
        Serial.println("door open");
    }else{
        Serial.println("door close");
    }
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
    open_status = digitalRead(CheckPin);

    return open_status;
}