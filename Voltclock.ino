

//=========================================================
//
// GoFlo Voltclock 1.2
// -----------------------------------
//
//
// GoFlo 10.06.2015
//
//
// File for the Voltclock with five 10V meters
//
// Updates:
// ----------
// + Month/Day meters added
// + Lights
// + Lightssensor
// + Metertesting at startup
//
//==========================================================


// Add DCF77 Library 
#include <DCF77.h>
#include <Time.h>

// Inputpin DCF Receiver
// Achtung: Bei Änderung des PINs auf den entsprechenden Interrupt achten oder neu setzen
// mittels attachInterrupt
#define DCF_PIN 2

// Interrupt for the receiver
#define DCF_INTERRUPT 0
time_t time;


// Debugging
boolean debug = true;

// Calibrating
boolean calibrate = false;

// Variablen definieren für LED Ausgänge und PIN Nummer zuweisen
const int HOUR_PIN        = 9;
const int MINUTE_PIN      = 11;
const int SECOND_PIN      = 10;
const int DAY_PIN         = 6;
const int MONTH_PIN       = 5;

// LED Pin festlegen
const int LED_PIN         = 3;

// Lichtsensor PIN festlegen
const int SENSOR_PIN      = A0;

// Nightmode hours (disable light)
const int nighton  = 23;
const int nightoff = 7;

// Uhrenmodus 12h oder 24h
const int hourmode = 12;

// Maxwert für Anzeigenaussteuerung
const int maxval = 232;

// Ablage Messwert Beleuchtungssensor
int readBrightness = 0;

// Uhrenvariablen initialisieren
int tmpmonth = 8;
int tmphour = 11;
int tmpminute = 12;
int tmpyear = 2014;
int tmpday = 21;
int tmpsecond = 0;


// Neues DCF Objekt erstellen, Variable ist der digitale 
// Eingangspin auf dem Arduino-Board
DCF77 funkuhr=DCF77(DCF_PIN,DCF_INTERRUPT,true);




// Arduino Setup
// -----------------------------------------------------
void setup() {                

  // Serial starten
  Serial.begin(9600);

  // Ausgabe auf serieller Konsole
  Serial.println("-- Voltclock 1.2 by GoFlo -- "); 
  Serial.println("---------------------------- "); 
  Serial.println(" "); 
  Serial.println("-- Setup wird durchgefuehrt -- "); 
  Serial.println("    . Variablen initialisiert");
  
  // LED Pins als Outputs festlegen
  pinMode(HOUR_PIN, OUTPUT); 
  pinMode(MINUTE_PIN, OUTPUT); 
  pinMode(SECOND_PIN, OUTPUT); 
  pinMode(DAY_PIN, OUTPUT); 
  pinMode(MONTH_PIN, OUTPUT); 
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  
  Serial.println("    . Pinmodes festgelegt"); 
 
  // Ausgänge auf LOW setzen / ausschalten
  analogWrite(HOUR_PIN, 0);
  analogWrite(MINUTE_PIN, 0);
  analogWrite(SECOND_PIN, 0);
  analogWrite(DAY_PIN, 0);
  analogWrite(MONTH_PIN, 0);
  analogWrite(LED_PIN, 0);
      
  Serial.println("    . Alle Ausgaenge auf LOW");
  
  // Anzeigen testen
  testMeters();
    
  // Uhr starten
  funkuhr.Start();
  Serial.println("    . Uhr starten");
  
  
  // Ausgabe Setup fertig
  Serial.println("-- Setup done -- "); 
  Serial.println(" "); 
    
}  //Ende void setup()


// // Test Meters
// ----------------------------------------------------------
void calibrateMeters() {
  // Stundenanzeige testen 
  Serial.println("    . Kalibrierlauf zur Skalaerstellung - Stunden");
   
       for (int i=1; i <= 12; i++){
         Serial.println(i);
         int cal = i*maxval/12;
         analogWrite(HOUR_PIN, cal);
         delay(10000);
       } 
  analogWrite(HOUR_PIN, 0);
  
  // Minutenanzeige testen 
  Serial.println("    . Kalibrierlauf zur Skalaerstellung - Minuten");
   
       for (int i=1; i <= 59; i++){
         Serial.println(i);
         int cal = i*maxval/59;
         analogWrite(MINUTE_PIN, cal);
         delay(10000);
       } 
   analogWrite(MINUTE_PIN, 0);
   
   // Sekundenanzeige testen 
   Serial.println("    . Kalibrierlauf zur Skalaerstellung - Sekunden");
   
       for (int i=1; i <= 59; i++){
         Serial.println(i);
         int cal = i*maxval/59;
         analogWrite(SECOND_PIN, cal);
         delay(10000);
       } 
   analogWrite(SECOND_PIN, 0);
   
   
   // Tagesanzeige testen 
   Serial.println("    . Kalibrierlauf zur Skalaerstellung - Tag");
   
       for (int i=1; i <= 31; i++){
         Serial.println(i);
         int cal = i*maxval/31;
         analogWrite(DAY_PIN, cal);
         delay(10000);
       } 
   analogWrite(DAY_PIN, 0);
   
   // Monatsanzeige testen 
   Serial.println("    . Kalibrierlauf zur Skalaerstellung - Monat");
   
       for (int i=1; i <= 12; i++){
         Serial.println(i);
         int cal = i*maxval/12;
         analogWrite(MONTH_PIN, cal);
         delay(10000);
       } 
   analogWrite(MONTH_PIN, 0);
   
}


// Test Meters
// ----------------------------------------------------------
void testMeters() {
  // Stundenanzeige testen 
  Serial.println("    . Test der Stundenanzeige");
  
  for (int i=0; i <= maxval; i++){
      analogWrite(HOUR_PIN, i);
      delay(10);
   } 
  
  // Minutenanzeige testen
  Serial.println("    . Test der Minutenanzeige");
  
  for (int i=0; i <= maxval; i++){
      analogWrite(MINUTE_PIN, i);
      delay(10);
   } 
  
  // Sekundenanzeige
  Serial.println("    . Test der Sekundenanzeige");
  
  for (int i=0; i <= maxval; i++){
      analogWrite(SECOND_PIN, i);
      delay(10);
   } 
   
  // Tagesanzeige
  Serial.println("    . Test der Tagesanzeige");
  
  for (int i=0; i <= maxval; i++){
      analogWrite(DAY_PIN, i);
      delay(10);
   } 
  
  // Monthanzeige
  Serial.println("    . Test der Monatsanzeige");
  
  for (int i=0; i <= maxval; i++){
      analogWrite(MONTH_PIN, i);
      delay(10);
   } 
   
  delay(1000);
  analogWrite(HOUR_PIN, 0);
  analogWrite(MINUTE_PIN, 0);
  analogWrite(SECOND_PIN, 0);
  analogWrite(DAY_PIN, 0);
  analogWrite(MONTH_PIN, 0);
  
}  // Ende testMeters()




// Calculate the clock time
// ----------------------------------------------------------
void readclock() {
  
  // Get data from DCF receiver
  time_t DCFtime = funkuhr.getTime();
  if (DCFtime!=0)
  {
    Serial.println("Time is updated");
    setTime(DCFtime);
    }
  
  // Copy to temporary variables
  tmpmonth = month();
  tmphour = hour();
  tmpminute = minute();
  tmpyear = year();
  tmpday = day();
  tmpsecond = second();
  
  if (debug) {
    // Show time on console
    Serial.print("Uhrzeit:   ");
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(" ");
    Serial.print(day());
    Serial.print(" ");
    Serial.print(month());
    Serial.print(" ");
    Serial.print(year());
    Serial.println(); 
    Serial.println(); 
    delay(1000);
  }
  
}  // End readclock()





// Mod value representation for console output
// ---------------------------------------------------
void printDigits(int digits){
  
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
  
}  // End printDigits()


// Lighting on
// ---------------------------------------------------
void LED_on(){
     // Switch on LEDs 
     analogWrite(LED_PIN, 254);
   
}  // End LED_on()


// Lighting off
// ---------------------------------------------------
void LED_off(){
     // Switch off LEDs 
     analogWrite(LED_PIN, 0);
  
}  // End LED_on()


// Dim lighting
// ---------------------------------------------------
void LED_dim(int value){
     // Dim LEDs 
     analogWrite(LED_PIN, value);
  
}  // End LED_on()



// Adjust Hour Meter
// ----------------------------------------------------------
void setHour() {
  
   // Set 12 hour mode
   if (hourmode == 12) {
      
     // PM
     if (tmphour > 12) {
      
            // Calculate Value for meter
            int pinhour = (tmphour-12)*maxval/12;
   
            // Write value to pin
            analogWrite(HOUR_PIN, pinhour);
            
            if (debug) {
               Serial.print("PWM-Werte: ");
               Serial.print(pinhour);
            }
     }
     
     // AM
     if (tmphour >= 0 && tmphour <= 12) {
       
            // Calculate Value for meter
            int pinhour = tmphour*maxval/12;
   
            // Write value to pin
            analogWrite(HOUR_PIN, pinhour);
            
             if (debug) {
                Serial.print("PWM-Werte: ");
                Serial.print(pinhour);
             }
     }
   }
   
   
   // Set 24 hour Mode
   if(hourmode == 24) {
     
          // Calculate Value for meter
          int pinhour = tmphour*maxval/23;
   
          // Write value to pin
          analogWrite(HOUR_PIN, pinhour);
       
       if (debug) {
          Serial.print("PWM-Werte: ");
          Serial.print(pinhour);
       }
   }
}   





// Adjust Minute Meter
// ----------------------------------------------------------
void setMinute() {
  
   // Calculate Value for meter
   int pinmin = tmpminute*maxval/59;
   
   // Write value to pin
   analogWrite(MINUTE_PIN, pinmin);
   
   if (debug) {
      Serial.print(" ");
      Serial.print(pinmin);
   }
}



// Adjust Seconds Meter
// ----------------------------------------------------------
void setSecond() {
  
   // Calculate Value for meter
   int pinsec = tmpsecond*maxval/59;
   
   // Write value to pin
   analogWrite(SECOND_PIN, pinsec);
  
   if (debug) {
      Serial.print(" ");
      Serial.print(pinsec);
      
   }
}



// Adjust Day Meter
// ----------------------------------------------------------
void setDay() {
  
   // Calculate Value for meter
   int pinday = tmpday*maxval/31;
   
   // Write value to pin
   analogWrite(DAY_PIN, pinday);
   
   if (debug) {
      Serial.print(" ");
      Serial.print(pinday);
   }
}



// Adjust Months Meter
// ----------------------------------------------------------
void setMonth() {
  
   // Calculate Value for meter
   int pinmon = tmpmonth*maxval/12;
   
   // Write value to pin
   analogWrite(MONTH_PIN, pinmon);
   
   if (debug) {
      Serial.print(" ");
      Serial.print(pinmon);
      Serial.println();
   }
}

 

// Adjust light
// -----------------------------------------------------------
void setBrightness() {
   
   int val;
   //Disable lights at night 
   if ((tmphour > nighton) || (tmphour < nightoff)) {
        LED_off();
   }
  
   // Adjust lights to ambient light
   else {
      readBrightness = analogRead(A0);
      val = 255 - (map(analogRead(A0), 0, 1023, 0 ,220));
      LED_dim(val);   
   } 

   if (debug) {
      Serial.print("Lightsensor: ");
      Serial.print(val);
      Serial.println();
   }
  
}




// Mainloop
// -----------------------------------------------------------
void loop() {
  
  // Should me test the meters?
  if (calibrate) {
    calibrateMeters();
  }
  
  // Normal Mode
  else {
     // Get time
     readclock();
  
     // Measure ambient light and adjust lights
     setBrightness();
  
     // Set meters
     setHour();
     setMinute();
     setSecond();
     setDay();
     setMonth();
  }
} // End of Mainloop 


// EOF
