#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include "pitches.h"
#include "melody.h"

byte cols[5][8] = {
    {B10000, B10000, B10000, B10000, B10000, B10000, B10000},
    {B11000, B11000, B11000, B11000, B11000, B11000, B11000},
    {B11100, B11100, B11100, B11100, B11100, B11100, B11100},
    {B11110, B11110, B11110, B11110, B11110, B11110, B11110},
    {B11111, B11111, B11111, B11111, B11111, B11111, B11111}
};

const char speakerPin = 53;
Kuznetchik kuzya;
Gangsta Idibek;
Hallelujah shrek;
Dora dura;
MortalKombat fatality;

void setup () {
  pinMode (speakerPin, OUTPUT);  
  Serial.begin(9600);
  for (int symNum = 0; symNum < 5; ++symNum)
    lcd.createChar(symNum, cols[symNum]);   

  lcd.begin (16, 2);
}

enum playlist {
  kuznechik = 0,
  gangsta,
  hallelujah,
  dora,
  mk,
  end_playlist,
  menu,
};

char curMusic = menu;
int mark = 1;
int flag = 0;
int menuBlink = 666;
char curChange = 0;

void handler (char event) {
    switch (event) {
      case next:  curMusic = (curMusic + 1) % end_playlist; flag = 0; noTone(speakerPin); delay(500); break;
      case prev:  curMusic = (curMusic - 1 + end_playlist) % end_playlist; flag = 0; noTone(speakerPin); delay(500); break;
      case up:    curMusic = end_playlist;
                  noTone(speakerPin);
                  if (mark != 10)
                    ++mark;
                  break;
      case pause: curMusic %= end_playlist; flag = 0; noTone(speakerPin); break;
      case down:  noTone(speakerPin);
                  if (flag != 1)
                    curMusic = menu;
                  if (mark != 10 && flag == 1)
                    ++mark;
                  break;
    }
}       

void menuHandler (char event) {
    switch (event) {
      case down:
      case next:  curChange = (curChange + 1) % end_playlist; break;
      case up:
      case prev:  curChange = (curChange - 1 + end_playlist) % end_playlist; break;
      case pause:  curMusic = curChange; menuBlink = 666; break;
    }
}

void loop() {
  
  switch (curMusic) {
    case kuznechik:   handler (kuzya.sing (speakerPin, lcd));  break;
    case gangsta:     handler (Idibek.sing (speakerPin, lcd)); break;
    case hallelujah:  handler (shrek.sing (speakerPin, lcd));  break;
    case dora:        handler (dura.sing (speakerPin, lcd));   break;
    case mk:          handler (fatality.sing (speakerPin, lcd)); break;
    case end_playlist: {
                        if (!flag) {
                          lcd.clear ();
                          lcd.setCursor (0, 0);
                          lcd.print ("Rate our project");
                          flag = 1;
                        }
                        lcd.setCursor (7, 1);
                        lcd.print (mark);
                        handler (onClick ());
                        break;
    }
    case menu:      {
                        if (curChange != menuBlink) {
                          menuBlink = curChange;
                          lcd.clear ();
                          lcd.setCursor (0, 0);
                          lcd.print ("Choose melody");
                          lcd.setCursor (0, 1);
                          switch (curChange) {
                            case kuznechik:  lcd.print ("Kuznechik");  break;
                            case gangsta:    lcd.print ("Gangsta");  break;
                            case hallelujah: lcd.print ("Hallelujah");  break;
                            case dora:       lcd.print ("Vturilas");  break;
                            case mk:         lcd.print ("Mortal Kombat");  break;
                          }
                        }
                        menuHandler (onClick ());
                        break;
    }
  }
}
