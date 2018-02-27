#define CHECK     8

int checkstatus = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(CHECK, INPUT);
}

void loop()
{
  checkstatus = digitalRead(CHECK);
  Serial.println(checkstatus);

  delay(1000);
}
