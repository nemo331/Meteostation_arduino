// Meteostation5 by Azat 
// Показывает дату время, температуру, влажность (зарезервировано место под давление)
// Звонок будильника по времени
// Установка 2 будильников
// + исполнительное устройство через реле
#include "DHT.h"
#define DHTPIN 2 // пин подключения контакта DATA
#define DHTTYPE DHT11 // DHT 11

#include <LiquidCrystal.h>
#include <DS1302.h>


// Init the DS1302
DS1302 rtc(8, 9, 10);
Time t;
// Init the LCD
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
DHT dht(DHTPIN, DHTTYPE);
int hhum = 0;
int ttemp = 0;
int bzzPin = 13;
      int h_a = 0; // Часы будильника 1
      int m_a = 0;  // Минуты будильника 1
      int h_a2 = 0; // Часы будильника 2
      int m_a2 = 0;  // Минуты будильника 2
      int alarm1 = 0;  // будильник 1 выключен
      int alarm2 = 0;  // будильник 2 выключен
int relay = 3;
const int POT_0 = 0; // Порт нажатия клавиши 0
int valpot_0 = 0; // переменная для хранения клавиши 0
const int POT_1 = 1; // Порт нажатия клавиши 1
int valpot_1 = 0; // переменная для хранения клавиши 1
    
    void bzz(int _bzzTime) 
    {
    for(int i=0;i<5;i++)
      {
      tone(bzzPin,2500,_bzzTime);
      delay(_bzzTime);
      tone(bzzPin,2000,_bzzTime);
      delay(_bzzTime);
      tone(bzzPin,1500,_bzzTime);
      delay(_bzzTime);
      }
    }
    
    void AnlPrer() // обработка данных аналоговых портов на редактирование будильника
    {
      // контроль нажатия клавиш
      if(analogRead(POT_0)>500&&analogRead(POT_1)>500)
      {
        digitalWrite (relay, LOW);
        lcd.clear();lcd.setCursor(0,0);
        lcd.print("Reset alarms");
        alarm1 = 0;  // будильник 1 выключен
        alarm2 = 0;  // будильник 2 выключен
        delay (2000);
      }
      
      if(analogRead(POT_0)>500) // Установка первого будильника
      {
        digitalWrite (relay, LOW);
        lcd.clear();lcd.setCursor(0,0);
        lcd.print("Alarm 1 set!!!");
        lcd.setCursor(0,1);
        lcd.print("Current: ");
        if (alarm1 ==0)
                {lcd.setCursor(8,1);
                lcd.print("Off");}
                else { 
                lcd.setCursor(8,1);
                lcd.print(h_a); 
                lcd.setCursor(10,1);
                lcd.print(":"); 
                lcd.setCursor(11,1);
                lcd.print(m_a);
                }
        delay (2000);
      
      if(analogRead(POT_0)>500)
      {
        lcd.clear();lcd.setCursor(0,0);
        lcd.print("Alarm 1.Hours:");lcd.setCursor(0,1);
        for(int y =  h_a  ;   y <  25;   y +=1)    
        { 
          if (y >= 24)
          {y = 0; lcd.setCursor(0,1); lcd.print("    ");}
          lcd.setCursor(0,1);
          lcd.print(y);
          alarm1 = 1;
          h_a = y;// Часы будильника
          
          if(analogRead(POT_0)<500) break;
          delay (500);
        }
      }
      
      if(analogRead(POT_1)>500)
      {
        lcd.clear();lcd.setCursor(0,0);
        lcd.print("Alarm 1.Minutes:");lcd.setCursor(0,1);
        for(int z =  m_a  ;   z <  61;   z +=1)    
        { 
          if (z >= 60)
          {z = 0; lcd.setCursor(0,1); lcd.print("    ");}
          lcd.setCursor(0,1);
          lcd.print(z);
          alarm1 = 1;
           m_a = z;// Минуты будильника
          if(analogRead(POT_1)<500) break;
          delay (300);
        }
      }
     }
     
             if(analogRead(POT_1)>500) // Установка второго будильника
              {
                digitalWrite (relay, LOW);
                lcd.clear();lcd.setCursor(0,0);
                lcd.print("Alarm 2 set!!!");
                lcd.setCursor(0,1);
                lcd.print("Current: ");
                if (alarm2 == 0)
                {lcd.setCursor(8,1);
                lcd.print("Off");}
                else { 
                lcd.setCursor(8,1);
                lcd.print(h_a2); 
                lcd.setCursor(10,1);
                lcd.print(":"); 
                lcd.setCursor(11,1);
                lcd.print(m_a2);
                }
                delay (2000);
              
              if(analogRead(POT_0)>500)
              {
                lcd.clear();lcd.setCursor(0,0);
                lcd.print("Alarm 2.Hours:");lcd.setCursor(0,1);
                for(int w =  h_a2  ;   w <  25;   w +=1)    
                { 
                  if (w >= 24)
                  {w = 0; lcd.setCursor(0,1); lcd.print("    ");}
                  lcd.setCursor(0,1);
                  lcd.print(w);
                  alarm2 = 1;
                  h_a2 = w;// Часы будильника
                  if(analogRead(POT_0)<500) break;
                  delay (500);
                }
              }
              
              if(analogRead(POT_1)>500)
              {
                lcd.clear();lcd.setCursor(0,0);
                lcd.print("Alarm 2.Minutes:");lcd.setCursor(0,1);
                for(int v =  m_a2  ;   v <  61;   v +=1)    
                { 
                  if (v >= 60)
                  {v = 0; lcd.setCursor(0,1); lcd.print("    ");}
                  lcd.setCursor(0,1);
                  lcd.print(v);
                  alarm2 = 1;
                  m_a2 = v;// Минуты будильника
                  if(analogRead(POT_1)<500) break;
                  delay (300);
                }
              }
             }
    }
    
void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  pinMode(bzzPin,OUTPUT);
  pinMode(relay ,OUTPUT );
  // Setup LCD to 16x2 characters
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
  // Установка даты, времени и дня недели в DS1302
  //rtc.setDOW(SUNDAY);        // Set Day-of-Week to FRIDAY
  //rtc.setTime(21, 37, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(23, 1, 2020);   // Set the date to August 6th, 2010
}

void loop()
{
    // получение с датчика данных влажности и температуры
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  // преобразование типа
  hhum = (int) hum;
  ttemp = (int) temp;
  if (isnan(temp) || isnan(hum)) // ошибка получения данных
  {
  lcd.clear();lcd.setCursor(0,1);
  lcd.print("Failed to read");
  }
  else // вывести данные на ЖКИ
  {
  //lcd.clear();
  
  lcd.setCursor(0,1);
  lcd.print("H");lcd.print(hhum); lcd.println("%   ");
  lcd.setCursor(5,1);
  lcd.print("T"); lcd.print(ttemp);lcd.println("*C  ");
  lcd.setCursor(11,1);
  if (alarm1 ==0) {
  lcd.print("f1 ");}
  else { lcd.print("n1 ");}
  lcd.setCursor(14,1);
  if (alarm2 ==0) {
  lcd.print("f2 ");}
  else { lcd.print("n2 ");}
  }
  
  // Display time centered on the upper line
  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeStr()); //FORMAT_SHORT - без секунд, иначе пустое поле
  t = rtc.getTime();
  // Display abbreviated Day-of-Week in the lower left corner
  //lcd.setCursor(13, 1);
  //lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  // Display date 
  //lcd.setCursor(5, 0);
  //lcd.print("    ");
  lcd.setCursor(8, 0);
  lcd.print(rtc.getDateStr(FORMAT_SHORT));
  //Serial.println(t.hour, DEC);
  //Serial.println(t.min, DEC);
  AnlPrer(); // Обработка нажатий кнопок для установки будильников
  
  if (hhum>45) // Условие срабатывания второго будильника (уровень влажности и в перспективе давления)
  {
      if (alarm2 !=0)
       { if ( t.hour == h_a2 && t.min == m_a2) // проверка будильника
        {
          digitalWrite (relay, HIGH) ;// и включение реле
          bzz(300); // если время совпало проигрывание мелодии
          lcd.clear();lcd.setCursor(0,0);
          lcd.print("Alarm 2");
          
        }
       }
  }
   else{
     if (alarm1 !=0)  
     {if ( t.hour == h_a && t.min == m_a) // проверка будильника
      {
        digitalWrite (relay, HIGH) ;// и включение реле
        bzz(500); // если время совпало проигрывание мелодии
        lcd.clear();lcd.setCursor(0,0);
        lcd.print("Alarm 1");
        
      }
     }
  }
  delay (1000);    // Wait one second before repeating :)
}
