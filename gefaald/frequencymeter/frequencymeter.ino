int incomingAudio;


void setup(){
    Serial.begin(9600);  

}

void loop(){
  incomingAudio = analogRead(A0);//read voltage at A0
  //incomingAudio = (incomingAudio+1)/4 - 1;//scale from 10 bit (0-1023) to 8 bit (0-255)
//  if (incomingAudio<0){//deal with negative numbers
//    incomingAudio = 0;
//  }
  PORTD = incomingAudio;
  Serial.println(PORTD);

}

