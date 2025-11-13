#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// LCD Pins
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Fingerprint Sensor Pins
SoftwareSerial mySerial(4, 5); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Servo and Switch Pins
const int sw = 2;
Servo s1;

// Buzzer Pin
const int buzzer = 7;

// Attendance Variables
int a = 0, b = 0, c = 0, d = 0, e=0;

void setup() {
  pinMode(sw, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  while (!Serial);
  delay(100);

  s1.attach(3);//pin 3
  finger.begin(57600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HALL TICKET");
  lcd.setCursor(0, 1);
  lcd.print("CHECKING SYSTEM");
  delay(3000);
  s1.write(0);//ensurres 0 degree
  lcd.clear();

  if (!finger.verifyPassword()) {
    while (1) {
      delay(1); // Halt system if fingerprint sensor is not found
    }
  }

  finger.getTemplateCount();//reads no f templates in fs
}

void loop() {
  int teacher;

  // Prompt to place the finger
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLEASE PUT ");
  lcd.setCursor(0, 1);
  lcd.print("FINGER TO ACCESS");
  delay(1000);

  // Check for a fingerprint
  if (finger.getImage() == FINGERPRINT_NOFINGER) {
    checkSwitch(); // Check the switch for absentee display
    return;
  }

  teacher = getFingerprintIDez(); // Get the fingerprint ID

  if (teacher == 1) {
    class1();
  } else if (teacher == 2) {
    class2();
  } else if (teacher == 3) {
    class3();
  } else if (teacher == 4) {
    class4();
  }else if (teacher==5){
    class5();
  } else if (teacher == -1) {
    // Finger detected but no match found
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UNAUTHORIZED");
    lcd.setCursor(0, 1);
    lcd.print("STUDENT");
    Serial.println("ALERT: UNAUTHORISED FINGER");
    digitalWrite(buzzer, HIGH); // Turn on the buzzer
    delay(2000);
    digitalWrite(buzzer, LOW);  // Turn off the buzzer
  }

  checkSwitch(); // Check the switch for absentee display after processing
}

void checkSwitch() {
  if (digitalRead(sw) == HIGH) { // If switch is pressed
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CHECKING FOR ");
    lcd.setCursor(0, 1);
    lcd.print("ABSENT");
    delay(2000); // Display message for 2 seconds

    // Display absentee list
    if (a == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME Deepa");
      lcd.setCursor(0, 1);
      lcd.print("ABSENT");
      Serial.println("NAME Deepa ABSENT");
      delay(5000);
    }
    if (b == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME Souj");
      lcd.setCursor(0, 1);
      lcd.print("ABSENT");
      Serial.println("NAME Souj ABSENT");
      delay(5000);
    }
    if (c == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME Suma");
      lcd.setCursor(0, 1);
      lcd.print("ABSENT");
      Serial.println("NAME Suma ABSENT");
      delay(5000);
    }
    if (d == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME Khush");
      lcd.setCursor(0, 1);
      lcd.print("ABSENT");
      Serial.println("NAME Khush ABSENT");
      delay(5000);
    }
    if (e == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NAME Nagu");
      lcd.setCursor(0, 1);
      lcd.print("ABSENT");
      Serial.println("NAME Nagu ABSENT");
      delay(5000);
    }
    delay(2000); // Wait before returning to normal operation
  }
}

void class1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AUTHORIZED");
  lcd.setCursor(0, 1);
  lcd.print("STUDENT");
  s1.write(90); // Unlock servo
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: Deepa");
  lcd.setCursor(0, 1);
  lcd.print("HT: 2GO21EC009");
  Serial.println("NAME: Deepa HALL TICKET NUMBER: 2GO21EC009");
  a = 1; // Mark as present
  s1.write(0); // Lock servo
  delay(5000);
}

void class2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AUTHORIZED");
  lcd.setCursor(0, 1);
  lcd.print("STUDENT");
  s1.write(90); // Unlock servo
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: Soujanya");
  lcd.setCursor(0, 1);
  lcd.print("HT: 2GO21EC045");
  Serial.println("NAME: Soujanya HALL TICKET NUMBER: 2GO21EC045");
  b = 1; // Mark as present
  s1.write(0); // Lock servo
  delay(5000);
}

void class3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AUTHORIZED");
  lcd.setCursor(0, 1);
  lcd.print("STUDENT");
  s1.write(90); // Unlock servo
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: Sumangala");
  lcd.setCursor(0, 1);
  lcd.print("HT:2GO21EC048");
  Serial.println("NAME:Sumangala HALL TICKET NUMBER: 2GO21EC048");
  c = 1; // Mark as present
  s1.write(0); // Lock servo
  delay(5000);
}

void class4() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AUTHORIZED");
  lcd.setCursor(0, 1);
  lcd.print("STUDENT");
  s1.write(90); // Unlock servo
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME:V Khushi");
  lcd.setCursor(0, 1);
  lcd.print("HT:2GO21EC051");
  Serial.println("NAME: V Khushi HALL TICKET NUMBER: 2GO21EC051");
  d = 1; // Mark as present
  s1.write(0); // Lock servo
  delay(5000);
}
void class5() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FINGER MATCHED");
  s1.write(90); // Unlock servo
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NAME: Srini");
  lcd.setCursor(0, 1);
  lcd.print("HT: 2GO22EC047");
  Serial.println("NAME: Srini HALL TICKET NUMBER: 2GO22EC047");
  e = 1; // Mark as present
  s1.write(0); // Lock servo
  delay(5000);
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) 
    return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
    return -1;

  return finger.fingerID;
}
