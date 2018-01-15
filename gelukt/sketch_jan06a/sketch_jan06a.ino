#include <FreqMeasure.h>

void setup() {
  Serial.begin(57600);
  pinMode(13,INPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  FreqMeasure.begin();
}

double sum=0;
int count=0;
float lowest = 50;
float highest = 0;
float grootte =50;
float b[10][2];
int newfreqzone;
int oldfreqzone=0;
int i = 0;


void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      //Serial.println(frequency);
      sum = 0;
      count = 0;
      if(frequency<lowest){
          lowest=frequency;
         /*Serial.print("new lowest: ");
         Serial.println(lowest);*/
         berekenGrootte();
        
          }else if(frequency>highest){
        highest=frequency;
       /* Serial.print("new highest: ");
         Serial.println(highest);*/
         berekenGrootte();
        }
        i = 0;
        while(frequency > b[i][1]){
           i++;
          }
          newfreqzone=i;
          if(newfreqzone>oldfreqzone){
            oldfreqzone=newfreqzone;
            front();
            
            }
            else if(newfreqzone<oldfreqzone){
              oldfreqzone=newfreqzone;
              back();
            }
            leftOrRight(frequency);
       
           /* if(resetbtn==LOW){
              Serial.println("reset");
              }
     /*if(frequency>1000){
        digitalWrite(3,HIGH);
        delay(1000);
        digitalWrite(3,LOW);
        }
        else{
          digitalWrite(5,HIGH);
          delay(1000);
          digitalWrite(5,LOW);
          }*/
      
      
    }
  }
       int resetbtn = digitalRead(13);
       if(resetbtn==HIGH){
           reset();
          }
         
             /*Serial.println(resetbtn);
             Serial.println("reset");*/
}
void berekenGrootte(){
  grootte = highest-lowest;
   /*Serial.print("new grootte: ");
          Serial.println(grootte);*/
  verdeel();
  }
  void verdeel(){
    float plength = grootte/10;
    b[0][0]= lowest;
    b[0][1]= lowest+plength;
      /*Serial.print("low: ");
    Serial.println(b[0][0]);
     Serial.print("high: ");
    Serial.println(b[0][1]);*/
   float startvalue = lowest+plength;
    for (int i=1;i<10;i++){
      b[i][0]=startvalue;
      b[i][1]=startvalue+plength;
      startvalue=startvalue+plength;
    /*Serial.println(b[i][0]);
    Serial.println(b[i][1]);*/

      }
    
   
    }
 void leftOrRight(float f){
  /* float l=b[i][0];
    float h=b[i][1];
    float gem = (l+h)/2;
    if(f>gem){
      left();
      Serial.println("left");
      }
      else{
        right();
        Serial.println("right");
       }*/
       if (i<3){
        left();
        }else if((i<5) && (i<=8)){
          left();
          }
          else{
            right();
            }
  }
    void front(){
      digitalWrite(2,LOW);
      
      digitalWrite(5,HIGH);
      }
    void back(){
      digitalWrite(5,LOW);
    
      digitalWrite(2,HIGH);
      }
    void left(){
      digitalWrite(4,LOW);
      delay(500);
      digitalWrite(3,HIGH);
      delay(1000);
      }
    void right(){
      digitalWrite(3,LOW);
        delay(500);
      digitalWrite(4,HIGH);
      delay(1000);
      }
void reset(){
  sum=0;
  count=0;
  lowest = 50;
  highest = 0;
  grootte =50;
  b[10][2];
  newfreqzone;
  oldfreqzone=0;
  i = 0;
  digitalWrite(2,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
   digitalWrite(3,LOW);
 }

