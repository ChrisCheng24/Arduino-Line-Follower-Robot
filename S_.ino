int LinputPin = A1;
int MinputPin = A2;
int RinputPin = A3;
//int flag=2;
int L = 0;
int M = 0;
int R = 0;
int smooth (int pin){
const int numReadings = 10;
int readings[numReadings]; // the readings from the analog input
int readIndex = 0; // the index of the current reading
int total = 0; // the running total
int average = 0; // the average
int inputPin = pin;
Serial.begin(9600);
for (int thisReading = 0; thisReading < numReadings; thisReading++) { // initialize
readings[thisReading] = 0;
}
total = total - readings[readIndex]; // subtract the last reading
readings[readIndex] = analogRead(inputPin); // read from the sensor
total = total + readings[readIndex]; // add the reading to the total
readIndex = readIndex + 1; // advance to the next position in the array
if (readIndex >= numReadings) { // wrap around to the beginning if at the end
readIndex = 0;
}
average = total / numReadings; // calculate the average
Serial.println(average);
delay(10);
}




void setup() {
  Serial.begin(9600);
 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  //delay(10000);
}


void loop() {
  Serial.print(analogRead(LinputPin));
  Serial.print("---");
  Serial.print(analogRead(MinputPin));
  Serial.print("---");
  Serial.print(analogRead(RinputPin));
  Serial.print("-----");
  Serial.print(L);
  Serial.print("---");
  Serial.print(M);
  Serial.print("---");
  Serial.print(R);
  Serial.print("---");
  Serial.println(analogRead(A0));
  
  if(analogRead(LinputPin)>700){ //720~840
    L=1;
  }else{
    L=0;
  }  
  if(analogRead(MinputPin)>700){  //640~760
    M=1;
  }else{
    M=0;
  }
  if(analogRead(RinputPin)>700){  //720~730
    R=1;
  }else{
    R=0;
  }
  
  if(L==0 && M==1 && R==0){    //前進
    analogWrite(5, 0);
    analogWrite(6, 50);
    analogWrite(10, 50);
    analogWrite(11, 0);
  }  
  if(L==1 && M==1 && R==0){    //向左(小)
    analogWrite(5, 0);
    analogWrite(6, 80);
    analogWrite(10, 40);
    analogWrite(11, 0);
  } 
  if(L==0 && M==1 && R==1){    //向右(小)
    analogWrite(5, 0);
    analogWrite(6, 30);
    analogWrite(10, 90);
    analogWrite(11, 0);
  } 
  if(L==1 && M==0 && R==0){    //向左(大)
    analogWrite(5, 0);
    analogWrite(6, 100);
    analogWrite(10, 40);
    analogWrite(11, 0);
  }
  if(L==0 && M==0 && R==1){    //向右(大)
    analogWrite(5, 0);
    analogWrite(6, 30);
    analogWrite(10, 100);
    analogWrite(11, 0);
  }
  if(L==1 && M==1 && R==1){    //停
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
  }
  if(L==1 && M==0 && R==1){    //停
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
  }  

  
  if(analogRead(A0)>580/*&&flag==1*/){   //遇到障礙-->進行迴避
    /*analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(1000);*/
    analogWrite(6, 80);   //左轉
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(600);
    /*analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(100);*/
    analogWrite(6, 60);   //直走
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 60);
    delay(700);
    /*analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(100);*/
    analogWrite(6, 0);    //右轉
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 60);
    delay(800);
    /*analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(100);*/
    analogWrite(6, 60);   //直走
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 60);
    delay(1000);
   /* analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(100);*/
    analogWrite(6, 0);    //右轉
    analogWrite(5, 60);
    analogWrite(11, 0);
    analogWrite(10, 70);
    delay(450);
    analogWrite(6, 60);   //直走
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 60);
    if(M==1&&L==1&&R==1){
   /* analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(100);*/
    analogWrite(6, 60);   //直走
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 60);
    delay(300);
    analogWrite(6, 60);   //左轉(找回後對準軌道)
    analogWrite(5, 0);
    analogWrite(11, 60);
    analogWrite(10, 0);
    delay(550);
    analogWrite(6, 0);
    analogWrite(5, 0);
    analogWrite(11, 0);
    analogWrite(10, 0);
    delay(100);
    }
    //flag=0;
  } 
     
  delay(50);
}
