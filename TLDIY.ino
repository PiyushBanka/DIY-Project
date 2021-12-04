int sensor1[] = {6,7};
int sensor2[] = {10,9};
int sensor1defaultvalue;
int sensor2defaultvalue;
int peoplecount = 0;
int width = 30;
String strng = "";

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup(){
  Serial.begin(9600); 
  delay(500);
  sensor1defaultvalue = measureDistance(sensor1);
  sensor2defaultvalue = measureDistance(sensor2);
  lcd.begin(16, 2);
  lcd.print("people count : ");
}

void loop(){
  //Read ultrasonic sensors
  int sensor1Value = measureDistance(sensor1);
  int sensor2Value = measureDistance(sensor2);
  
  //Process the data
  if(sensor1Value < sensor1defaultvalue - width && strng[0] != '1'){
    strng += "1";
  }else if(sensor2Value < sensor2defaultvalue - width && strng[0] != '2'){
    strng += "2";
  }
  
  if(strng.equals("12")){
    peoplecount++;  
    strng="";
    delay(500);
  }else if(strng.equals("21") && peoplecount > 0){
    peoplecount--;  
    strng="";
    delay(500);
  }

  // Displays the result
  Serial.print("number of people : ");
  Serial.println(peoplecount);
  lcd.setCursor(0,1);
  lcd.print(peoplecount);
}


//MEASURE DISTANCE FUNCTION
int measureDistance(int a[]) {
  pinMode(a[1], OUTPUT);
  digitalWrite(a[1], LOW);
  delayMicroseconds(2);
  digitalWrite(a[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(a[1], LOW);
  pinMode(a[0], INPUT);
  long duration = pulseIn(a[0], HIGH, 100000);
  return duration / 29 / 2;
}
