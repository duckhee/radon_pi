
#include <SoftwareSerial.h>


SoftwareSerial swSer(14,12, false, 256); // RX D5, TX D6

#define CheckPin        D0 //check door on/off

void send_command(char);
void get_valueprint(void);
String get_value(void);
int check_open();

int open_status = 0;


void setup()
{
    Serial.begin(115200);
    swSer.begin(9600); 
    Serial.println("set");
    pinMode(CheckPin, INPUT);
    
}


void loop()
{
    char key = 'p';

    if(check_open() == true)
    {
        Serial.println("door close");
    }else{
        Serial.println("door open");
    }
    send_command(key);
    Serial.println(get_value());
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
    delay(100);    

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
    delay(100);    

    if(c == '\r\n')
    {
      break;
    }
  }
  swSer.flush();
  
  return buffer;
  
}


int check_open()
{
    open_status = digitalRead(CheckPin);

    return open_status;
}