


 /* AUDIONET CPU-CCB GEN-1 DEVICE FIRMWARE v.1.00 Beta
    --------------------------------------------------
    Firmware to drive the MSP430-G2553 controller with Rotary-Encoder, LCD Disply, Cooling system, ST-Relayis, Leds.
    ----------------------------------------------------------------------------------------------------------------
    Author Dr.-Ing. David Zohrabyan (R&D Department)
    ------------------------------------------------
    AUDIONET Research Labs. Berlin 07.07.2017
    ----------------------------------------- */

  #include <LiquidCrystal.h> 
  #include <math.h>
  
  int deciBells=0;
  int t_long_tetta=20000;
  int t_short_tetta=6000;
  
  const int probe1_lock_in=A0;
  const int probe2_lock_in=A1;
  const int probe3_lock_in=A2;
  const int probe4_lock_in=A3;
  const int probe5_lock_in=A4; 
  const int rel_sw1_port=P1_5;
  const int rel_sw2_port=P2_0;
  const int rel_sw3_port=P2_1;
  const int Vol_Knob=P2_6;
  const int Vol_Dir =P2_7;
  
  float probe1_stats=0;
  float probe2_stats=0;
  float probe3_stats=0;
  float probe4_stats=0;
  float probe5_stats=0;
  float probeX_Ave;
  float temperature_Kelvin;
  float temperature_Celsius;
  float R_Reference=5000;
  float R_Thermistor;
  
  volatile int Vol_Knob_stat=0;
  volatile int Vol_Dir_stat =0;
  
  LiquidCrystal lcd( P2_2, P2_3, P2_4, P2_5, P1_6, P1_7);
  
  void setup()
  {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Waking Up ...");
    delay(t_short_tetta);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Audionet Labs.");
    pinMode(P1_5, OUTPUT);
    pinMode(P2_0, OUTPUT);
    pinMode(P2_1, OUTPUT);
    pinMode(P2_6, INPUT);
    pinMode(P2_7, INPUT);
    attachInterrupt(Vol_Knob, encode_Rotor_func, FALLING); 
   }
  
 
  void loop()
  {      
         delay(t_short_tetta);
         lcd.clear();
         probe1_stats=analogRead(probe1_lock_in); 
         probe2_stats=analogRead(probe2_lock_in);
         probe3_stats=analogRead(probe3_lock_in);
         probe4_stats=analogRead(probe4_lock_in);
         probe5_stats=analogRead(probe5_lock_in);
         probeX_Ave=(probe1_stats+probe2_stats+probe3_stats+probe4_stats+probe5_stats)/5;
         R_Thermistor = (1024 *(R_Reference/probeX_Ave))- R_Reference;
         temperature_Kelvin = 0.22/(0.0002354 + 0.00006 * (logf(R_Thermistor)));
         temperature_Celsius = temperature_Kelvin-273;
         lcd.setCursor(0, 0);
         lcd.print("temp.=     C");
         lcd.setCursor(6, 0);
         lcd.print(temperature_Celsius, 2);   
         if(temperature_Celsius >= 20)
         {
           lcd.setCursor(1, 1);
           lcd.print("CONTROL>>ON"); 
           digitalWrite(rel_sw1_port, LOW);
           digitalWrite(rel_sw2_port, LOW);
           digitalWrite(rel_sw3_port, LOW);
         }
         else if(temperature_Celsius <= 19)
         {    
           lcd.setCursor(1, 1);
           lcd.print("CONTROL<<OFF");
           digitalWrite(rel_sw1_port, HIGH);
           digitalWrite(rel_sw2_port, HIGH);
           digitalWrite(rel_sw3_port, HIGH);
         }
         else
         {
           lcd.setCursor(1, 1);
           lcd.print(" On Standby....");
           digitalWrite(rel_sw1_port, HIGH);
           digitalWrite(rel_sw2_port, HIGH);
           digitalWrite(rel_sw3_port, HIGH);
         }
         delay(t_short_tetta);
  }
    void encode_Rotor_func()
    {
        lcd.clear();
        Vol_Knob_stat=digitalRead(Vol_Knob);    
        if(Vol_Knob_stat==0)
        {
          Vol_Dir_stat=digitalRead(Vol_Dir); 
          if(Vol_Dir_stat==0 && deciBells<=9)
          {
            deciBells++;
            lcd.setCursor(0, 0);
            lcd.print("VOLUME=   .");
            lcd.setCursor(7, 0);
            lcd.print(deciBells);
            lcd.setCursor(10, 0);
            lcd.print("dB's");
           }
        else if(Vol_Dir_stat==1 && deciBells >=-79)
        {
          deciBells--;
          lcd.setCursor(0, 0);
          lcd.print("VOLUME=   .");
          lcd.setCursor(7, 0);
          lcd.print(deciBells);
          lcd.setCursor(10, 0);
          lcd.print("dB's");
        }
       }
    }
   

