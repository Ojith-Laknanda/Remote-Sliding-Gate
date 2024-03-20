#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

#define A 3
#define B 4
#define C 5
#define D 6   //power down

#define reel1 8 //open side
#define reel2 9 //close side


#define control1 11
#define control2 12

#define safty 13




void setup() {

  lcd.begin();
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);

  pinMode(reel1, INPUT);
  pinMode(reel2, INPUT);

  pinMode(control1, OUTPUT);
  pinMode(control2, OUTPUT);

  pinMode(safty, INPUT);  

  Serial.begin(115200);


  digitalWrite(control1, LOW);
  digitalWrite(control2, LOW);

  
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  delay(1000);                                    // change this value
  lcd.clear();

}

void loop() {
   /*
  Serial.print("reel1 ->"); Serial.println(digitalRead(reel1)); Serial.print("reel2 ->");
  Serial.println(digitalRead(reel2)); delay(200); Serial.println();
   
  Serial.print("A ->");
  Serial.println(digitalRead(A)); Serial.print("B ->");
  Serial.println(digitalRead(B)); Serial.print("C ->");
  Serial.println(digitalRead(C)); Serial.print("D ->");
  Serial.println(digitalRead(D)); delay(500);
  Serial.println();
 

*/

  digitalWrite(control1, LOW);
  digitalWrite(control2, LOW);
  Serial.println("Ready");

  while (digitalRead(A) == 0 && digitalRead(B) == 0 && digitalRead(C) == 0 && digitalRead(D) == 0 ) {
    int saftyyy=digitalRead(safty);
    Serial.print("saftyyy ->");Serial.println(digitalRead(safty));
    Serial.println("Ready");
    delay(100);
    lcd.noBacklight();

  }

  int open_gate1 = digitalRead(A);
  Serial.print("openGate1--->");
  Serial.println(open_gate1);

  int close_gate1 = digitalRead(B);
  Serial.print("closeGate1--->");
  Serial.println(close_gate1);

  int immediate_stop = digitalRead(C);
  Serial.print("immediate_stop--->");
  Serial.println(immediate_stop);

  int light_on = digitalRead(D);
  Serial.print("power down--->");
  Serial.println(light_on);
  Serial.println("");
  delay(1000);

  


  if (open_gate1 == 1) {
    openGate();
  } else if (close_gate1 == 1) {
    closeGate();
    
  }


  delay(500);
  lcd.backlight();
  lcd.setCursor(5, 1);
  lcd.print("STANDBY!");

  delay(2000);
  lcd.clear();
  lcd.noBacklight();

  
}


void openGate() {

  Serial.println("gate open");
  if(digitalRead(reel1) == 1){
    Serial.println("open");
    digitalWrite(control1, HIGH);
    digitalWrite(control2, LOW);
  }
  int close_gate1 = 0;
  int immediate_stop1 = 0;
 
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("GATE OPENING");
  lcd.setCursor(0, 3);
  lcd.print("<----");
//  delay(2000);
//  lcd.clear();
//    lcd.noBacklight();
//    


  while (!(immediate_stop1 == 1 || close_gate1 == 1 || digitalRead(reel2) == 0  )) { 
    Serial.println("<---------------------------------");
    
    immediate_stop1 = digitalRead(C);
    close_gate1 = digitalRead(B);
    
    Serial.println(immediate_stop1);
    Serial.println(close_gate1);
    
  }
  delay(200);
    lcd.backlight();
    Serial.println("Gate opened");
    lcd.setCursor(0, 3);
    lcd.print("GATE OPENED");
    delay(1000);
    lcd.clear();
    lcd.noBacklight();
  

  Serial.println("");
  if (immediate_stop1 == 1) {
    override1();
  } else if (close_gate1 == 1 ) {
    closeGate();
  }

  digitalWrite(control1, HIGH);
  digitalWrite(control2, HIGH);

  lcd.clear();
  lcd.noBacklight();
}

void closeGate() {

   int immediate_stop2 = 0;
  int open_gate1 = 0;
  int saftyyy=9;
  Serial.println("gate closing");
  if(digitalRead(reel2) == 1){
    Serial.println("closing");
  digitalWrite(control1, LOW);
  digitalWrite(control2, HIGH);}
  
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("GATE CLOSING");
  lcd.setCursor(0, 3);
  lcd.print("---->");
//  delay(2000);
//  lcd.clear();
//  lcd.noBacklight();
//  // Serial.print("ir2 ->"); Serial.println(digitalRead(ir2));


  while (!(immediate_stop2 == 1 || open_gate1 == 1 || digitalRead(reel1) == 0 || digitalRead(safty) == 1 )) { 
    Serial.println("--------------------------------->");
    
    Serial.println(immediate_stop2);
    Serial.println(open_gate1);

    immediate_stop2 = digitalRead(C);
    open_gate1 = digitalRead(A);
    saftyyy=digitalRead(safty);
    Serial.print("saftyyy ->");Serial.println(digitalRead(safty));
    
  }
  delay(500);
    lcd.backlight();
    Serial.println("Gate closed");
    lcd.setCursor(0, 3);
    lcd.print("GATE CLOSED");
    delay(1000);
    lcd.clear();
    lcd.noBacklight();
  

  if (immediate_stop2 == 1) {
    override1();
  } else if (open_gate1 == 1 || saftyyy==1 ) {
    openGate();
  }
  
  digitalWrite(control1, HIGH);
  digitalWrite(control2, HIGH);

  lcd.clear();
  lcd.noBacklight();

}

void override1() {

  Serial.println("override! gate stop");
  digitalWrite(control1, HIGH);
  digitalWrite(control2, HIGH);

  lcd.clear();
  lcd.noBacklight();

  lcd.backlight();
  lcd.setCursor(3, 1);
  lcd.print("OVERRIDE!");
  lcd.setCursor(0, 2);
  lcd.print("GATE STOPPED");


  delay(3000);
  lcd.clear();
  lcd.noBacklight();
  /*   while(digitalRead(A)==0 && digitalRead(B)==0 && digitalRead(C)==0 && digitalRead(D)==0){
        int i=0;
        Serial.print("i = ");
        Serial.println(i);
        i++;
     }
  */
}
