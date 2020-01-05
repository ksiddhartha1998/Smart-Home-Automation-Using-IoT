#include "SoftwareSerial.h"
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
TMRpcm voice;
String readvoice, temp;
const byte light = 4, charger = 5, heater = 6, fan = 7, tempSensor = A0;
byte stlig, stfan, stheat, stchar;
char c;
String commands[] = {"light", "fan", "heater", "charger", "all", "song", "joke", "temperature"};
int com, swit;
bool res;
bool check()
{
  if (swit == 1)
  {
    voice.play("erroron.wav");
    while (voice.isPlaying());
  }
  else
  {
    voice.play("erroroff.wav");
    while (voice.isPlaying());
  }
  while (1)
  {
    temp = "";
    while (Serial.available())
    {
      delay(10);
      c = Serial.read();
      temp += c;
    }
    if (temp.length() > 0)
    {
      temp.toLowerCase();
      if (temp == "yes")
      {
        return true;
      }
      else if (temp == "no")
      {
        return false;
      }
      else
      {
        voice.play("yesorno.wav");
        while (voice.isPlaying());
      }
    }
  }
}
void song ()
{
  int randomNumber = random(1, 11);
  char filename[15];
  sprintf(filename, "song%i.wav", randomNumber);
  voice.play(filename);
  while (voice.isPlaying())
  {
    temp = "";
    while (Serial.available())
    {
      delay(10);
      c = Serial.read();
      temp += c;
    }
    temp.toLowerCase();
    if (temp == "stop")
    {
      voice.stopPlayback();
      return;
    }
  }
}
void joke()
{
  int randomNumber = random(1, 4);
  char filename[15];
  sprintf(filename, "joke%i.wav", randomNumber);
  voice.play(filename);
  while (voice.isPlaying())
  {
    temp = "";
    while (Serial.available())
    {
      delay(10);
      c = Serial.read();
      temp += c;
    }
    temp.toLowerCase();
    if (temp == "stop")
    {
      voice.stopPlayback();
      return;
    }
  }
}
void room_temp()
{
  float Vin, Celcius;
  int temp;
  char filename[15];
  Vin = analogRead (tempSensor);
  Celcius = Vin*5/1023*100;
  temp = round(Celcius);
  if (temp <= 40 && temp >= 10);
  else
    temp = 0;
  sprintf(filename, "temp%i.wav", temp);
  voice.play(filename);
  while (voice.isPlaying());
}
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(charger, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
  digitalWrite(charger, HIGH);
  digitalWrite(light, HIGH);
  digitalWrite(fan, HIGH);
  digitalWrite(heater, HIGH);
  voice.speakerPin = 9;
  if (!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }
  voice.setVolume(5);
  voice.play("welcome.wav");
  while (voice.isPlaying());
  stlig = stfan = stheat = stchar = 0;
}
void loop()
{
  readvoice = "";
  while (Serial.available())
  {
    delay(10);
    c = Serial.read();
    readvoice += c;
  }
  if (readvoice.length() > 0)
  {
    int i = 0, j;
    com = -1;
    swit = -1;
    temp = "";
    readvoice.toLowerCase();
    while (i < readvoice.length())
    {
      while (readvoice[i] != ' ' && i < readvoice.length())
        temp = temp + readvoice[i++];
      for (j = 0; j < 8; j++)
      {
        if (temp == commands[j])
          com = j;
      }
      if (temp == "on")
        swit = 1;
      if (temp == "off")
        swit = 0;
      temp = "";
      i++;
    }
    if (com >= 0 && com <= 4)
    {
      if (swit != -1)
      {
        switch (com)
        {
          case 0 : if (swit != stlig)
            {
              stlig = swit;
              if (swit == 1)
              {
                digitalWrite(light, LOW);
                voice.play("lighton.wav");
                while (voice.isPlaying());
              }
              else
              {
                digitalWrite(light, HIGH);
                voice.play("lightoff.wav");
                while (voice.isPlaying());
              }
            }
            else
            {
              res = check();
              if (res == true)
              {
                swit == 1 ? swit = 0 : swit = 1;
                stlig = swit;
                if (swit == 1)
                {
                  digitalWrite(light, LOW);
                  voice.play("lighton.wav");
                  while (voice.isPlaying());
                }
                else
                {
                  digitalWrite(light, HIGH);
                  voice.play("lightoff.wav");
                  while (voice.isPlaying());
                }
              }
              else
              {
                voice.play("okay.wav");
                while (voice.isPlaying());
              }
            }
            break;
          case 1 : if (swit != stfan)
            {
              stfan = swit;
              if (swit == 1)
              {
                digitalWrite(fan, LOW);
                voice.play("fanon.wav");
                while (voice.isPlaying());
              }
              else
              {
                digitalWrite(fan, HIGH);
                voice.play("fanoff.wav");
                while (voice.isPlaying());
              }
            }
            else
            {
              res = check();
              if (res == true)
              {
                swit == 1 ? swit = 0 : swit = 1;
                stfan = swit;
                if (swit == 1)
                {
                  digitalWrite(fan, LOW);
                  voice.play("fanon.wav");
                  while (voice.isPlaying());
                }
                else
                {
                  digitalWrite(fan, HIGH);
                  voice.play("fanoff.wav");
                  while (voice.isPlaying());
                }
              }
              else
              {
                voice.play("okay.wav");
                while (voice.isPlaying());
              }
            }
            break;
          case 2 : if (swit != stheat)
            {
              stheat = swit;
              if (swit == 1)
              {
                digitalWrite(heater, LOW);
                voice.play("heaton.wav");
                while (voice.isPlaying());
              }
              else
              {
                digitalWrite(heater, HIGH);
                voice.play("heatoff.wav");
                while (voice.isPlaying());
              }
            }
            else
            {
              res = check();
              if (res == true)
              {
                swit == 1 ? swit = 0 : swit = 1;
                stheat = swit;
                if (swit == 1)
                {
                  digitalWrite(heater, LOW);
                  voice.play("heaton.wav");
                  while (voice.isPlaying());
                }
                else
                {
                  digitalWrite(heater, HIGH);
                  voice.play("heatoff.wav");
                  while (voice.isPlaying());
                }
              }
              else
              {
                voice.play("okay.wav");
                while (voice.isPlaying());
              }
            }
            break;
          case 3 : if (swit != stchar)
            {
              stchar = swit;
              if (swit == 1)
              {
                digitalWrite(charger, LOW);
                voice.play("chargeon.wav");
                while (voice.isPlaying());
              }
              else
              {
                digitalWrite(charger, HIGH);
                voice.play("chargoff.wav");
                while (voice.isPlaying());
              }
            }
            else
            {
              res = check();
              if (res == true)
              {
                swit == 1 ? swit = 0 : swit = 1;
                stchar = swit;
                if (swit == 1)
                {
                  digitalWrite(charger, LOW);
                  voice.play("chargeon.wav");
                  while (voice.isPlaying());
                }
                else
                {
                  digitalWrite(charger, HIGH);
                  voice.play("chargoff.wav");
                  while (voice.isPlaying());
                }
              }
              else
              {
                voice.play("okay.wav");
                while (voice.isPlaying());
              }
            }
            break;
          case 4 : if (swit == 1)
            {
              if ((stlig*stfan*stchar*stheat) == 0)
              {
                digitalWrite(charger, LOW);
                digitalWrite(light, LOW);
                digitalWrite(fan, LOW);
                digitalWrite(heater, LOW);
                stlig=1;stfan=1;stchar=1;stheat=1;
                voice.play("allon.wav");
                while (voice.isPlaying());
              }
              else
              {
                res = check();
                if (res == true)
                {
                  swit == 1 ? swit = 0 : swit = 1;
                  if (swit == 1)
                  {
                    digitalWrite(charger, LOW);
                    digitalWrite(light, LOW);
                    digitalWrite(fan, LOW);
                    digitalWrite(heater, LOW);
                    stlig=1;stfan=1;stchar=1;stheat=1;
                    voice.play("allon.wav");
                    while (voice.isPlaying());
                  }
                  else
                  {
                    digitalWrite(charger, HIGH);
                    digitalWrite(light, HIGH);
                    digitalWrite(fan, HIGH);
                    digitalWrite(heater, HIGH);
                    stlig=0;stfan=0;stchar=0;stheat=0;
                    voice.play("alloff.wav");
                    while (voice.isPlaying());
                  }
                }
                else
                {
                  voice.play("okay.wav");
                  while (voice.isPlaying());
                }
              }
            }
            else
            {
              if ((stlig+stfan+stchar+stheat)!=0)
              {
                digitalWrite(charger, HIGH);
                digitalWrite(light, HIGH);
                digitalWrite(fan, HIGH);
                digitalWrite(heater, HIGH);
                stlig=0;stfan=0;stchar=0;stheat=0;
                voice.play("alloff.wav");
                while (voice.isPlaying());
              }
              else
              {
                res = check();
                if (res == true)
                {
                  swit == 1 ? swit = 0 : swit = 1;
                  if (swit == 1)
                  {
                    digitalWrite(charger, LOW);
                    digitalWrite(light, LOW);
                    digitalWrite(fan, LOW);
                    digitalWrite(heater, LOW);
                    stlig=1;stfan=1;stchar=1;stheat=1;
                    voice.play("allon.wav");
                    while (voice.isPlaying());
                  }
                  else
                  {
                    digitalWrite(charger, HIGH);
                    digitalWrite(light, HIGH);
                    digitalWrite(fan, HIGH);
                    digitalWrite(heater, HIGH);
                    stlig=0;stfan=0;stchar=0;stheat=0;
                    voice.play("alloff.wav");
                    while (voice.isPlaying());
                  }
                }
                else
                {
                  voice.play("okay.wav");
                  while (voice.isPlaying());
                }
              }
            }
            break;
        }
      }
      else
      {
        voice.play("insuff.wav");
        while (voice.isPlaying());
      }
    }
    else if (com >= 5 && com <= 7)
    {
      switch (com)
      {
        case 5 : song();
          break;
        case 6 : joke();
          break;
        case 7 : room_temp();
          break;
      }
    }
    else
    {
      voice.play("error.wav");
      while (voice.isPlaying());
    }
  }
}
