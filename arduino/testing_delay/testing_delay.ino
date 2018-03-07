
#include <SoftwareSerial.h>


SoftwareSerial myserial(10, 11); // RX D5=14, TX D6=12

#define CheckPin        0 //check door on/off

void send_command(char);
void get_valueprint(void);
String get_value(void);
int check_open();
void delay_hour(unsigned int); //delay hour


int open_status = 0;


void setup()
{
    Serial.begin(9600);
    myserial.begin(9600); 
    Serial.println("set");
    pinMode(CheckPin, INPUT);
    
}


void loop()
{
  int commaPosition;
    delay_hour(1);
   // char key = 'p';
    char key = 'c';
    String data;
    int com;
  
    send_command(key);
    //Serial.println(get_value());
    data = get_value();
    Serial.println(":::::: ");
    Serial.println(data);
    Serial.println(":::::: ");
    do
    {
      com = data.indexOf(',');
      if(com != -1)
      {
        Serial.println(data.substring(0, com));
        data = data.substring(com+1, data.length());
      }else{
        if(data.length() >0)
        {
          Serial.println(data);
        }
      }
    }while(com >= 0);
    delay(5000);
    delay(1000);
}


void send_command(char command)
{
  switch(command)
  {
    case 's':
      myserial.print("s");
      break;
    case 'c':
      myserial.print("c");
      break;
    case 'p':
      myserial.print("p");
    break;
    case 'r':
      myserial.print("r");
    break;
    default:
      myserial.print("c");
    break;
  }
}

void get_valueprint(void)
{

  String buffer = "";
  
  while(myserial.available())
  {
    char c = myserial.read();
    buffer += c;
    delay(1000);    

    if(c == '\r\n')
    {
      break;
    }
  }
  Serial.println(buffer);
  buffer = "";
  myserial.flush();
  
}

String get_value(void)
{

  String buffer = "";
  
  while(myserial.available())
  {
    char c = myserial.read();
    buffer += c;
    delay(100);    

    if(c == '\r\n')
    {
      break;
    }
  }
  myserial.flush();
  
  return buffer;
  
}


int check_open()
{
    open_status = digitalRead(CheckPin);

    return open_status;
}

void delay_hour(unsigned int num)
{
    unsigned int delay_time = num *60*60;
    
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
