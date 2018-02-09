
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void send_command(char);
void get_valueprint(void);
String get_value(void);



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  Serial.println("set up!");
}

void loop() { // run over and over

    char key = 'p';
  
    send_command(key);
    Serial.println(get_value());
  
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
