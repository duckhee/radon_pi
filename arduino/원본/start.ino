#include <SoftReset.h> 

 

#define LOG_PERIOD 60000
#define MAX_PERIOD 60000

 

String inputString = "";         
boolean stringComplete = false; 
float sensorData = 0;       

float CF = 1; //
int data_array60[60] = {};
int num = 0;
float sum = 0;
float avg = 0;
float pCi = 0;

unsigned long d, h, m, h2 = 0;
unsigned long cycle = 0;
unsigned long counts = 0;
unsigned long cpm;
unsigned int multiplier;    
unsigned long previousMillis;


void output() {
  Serial.print("O");
}

void tube_impulse() {
      counts++;
      output();  
}

 
void setup() { 
  Serial.begin(9600);
  attachInterrupt(0, tube_impulse, RISING);
  pinMode(2, INPUT); 
  inputString.reserve(4);
  
  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;


}
 

// 빨간색 부분에서 통신관련 소스를 수정해주시면 됩니다

void loop() {

  sensorData = pCi;
  unsigned long currentMillis = millis();

  char read_data;
  if (Serial.available())
  {
    read_data = Serial.read(); 


        // 명령어 's'가 들어왔을 경우
     if ( read_data == 's' ) {

      
    stringComplete = true;
    if (stringComplete) {
    int sensorDataX100 = (sensorData * 100);
    inputString += sensorDataX100 / 1000;
    inputString += (sensorDataX100 % 1000) / 100;
    inputString += (sensorDataX100 % 100) / 10;
    inputString += (sensorDataX100 % 10);



    if(cycle > 59) {
    Serial.println(inputString); }
    else Serial.println("wait for 60minuite...");    
    
    // 데이터 초기화 및 flag 초기화:
    inputString = "";
    stringComplete = false;
    }
   }

   

        //c입력시 프로그램 통신상태 확인
    if ( read_data == 'c' ) {

      if(cycle > 59) {  
    Serial.print(",");
    Serial.print(cycle);
    Serial.print(",min");
    Serial.print(",60avg,");
    Serial.print(avg);    
    Serial.print(",pCi,");
    Serial.print(pCi, 2);    
    Serial.println(",RS-S-180113-T1");    
    } 
    else Serial.println("wait for 60minuite..."); }    

   

    //r입력시 프로그램 리셋
    if ( read_data == 'r' ) {
        Serial.println("Reset..... OK");
        delay(50);
        soft_restart();        
    }       
  }

//아래부분은 건드리지 말아주세요

  if (currentMillis - previousMillis > LOG_PERIOD) {
    cycle++;
    num++; //60분 배열용

    m++;  //minute
    if (num > 59) num = 60;      
    previousMillis = currentMillis; 
    cpm = counts * multiplier;

    data_array60[m - 1] = cpm; 
    
    if (num < 60) sum = sum + data_array60[m - 1];

    else if (num > 59) {
      sum = 0;
      
      for (int i = 0 ; i < 60 ; i++) {
        sum = sum + data_array60[i];
      }      
    }
     
    avg = sum / num;

    if (m > 59) {
      m = 0; 
      h++; 
      h2++;
      if (h > 23) {
        d++; 
        h = 0;
      }
    }

    pCi = avg * CF;

    
    if( cycle >50) {

    if( m % 10 == 0 ) {
    Serial.print(",");
    Serial.print(cycle);
    Serial.print(",min");  
    Serial.print(",60avg,");
    Serial.print(avg);    
    Serial.print(",pCi,");
    Serial.print(pCi, 2);
    Serial.println(",RS-S-180113-T1");  
    }
    }    
    counts = 0;


  }       

}

 

 

 

 
