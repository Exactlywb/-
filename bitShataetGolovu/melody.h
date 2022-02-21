#include "pitches.h"
#include <string.h>

struct notePlusDelay final {

    int note;
    int del;
};

enum clickEvents {
    next,
    prev,
    pause,
    up,
    down,
    noClick
};

char onClick () {
    int x = analogRead (A0);
    if (x > 1000) {
        return noClick;
    }

    while (analogRead (A0) < 1000)
        delay (1);

    if (x < 100) {
        return next;
    }
    if (x < 200) {
        return up;
    }
    if (x < 400){
        return down;
    }
    if (x < 600){
        return prev;
    }
    if (x < 800){
        return pause;
    } 
}

#define CLICKEVENT(name)    do { \
                                char tmp = onClick ();   \
                                if (tmp == pause) { \
                                    noTone (speakerPin);  \
                                    unsigned long beginPause = millis();  \
                                    lcd.setCursor (0, 1);   \
                                    lcd.print ("Pause");    \
                                    int button; \
                                    while ((button = onClick ()) != pause) {   \
                                        delay (1);  \
                                        if (button != noClick)   \
                                            return button;  \
                                    } \
                                    pauseTime += millis() - beginPause; \
                                    break; \
                                } \
                                if (tmp != noClick) {   \
                                    return tmp; \
                                }       \
                            }   while (0)

#define PRINT(name) do {    \
                        float decade = (millis() - timer - pauseTime) / (durationMelody * 20.0);  \
                        int snake = 1;  \
                        lcd.setCursor (5 + snake, 1);   \
                        for (; snake < 11 && decade > snake * 5; ++snake) {    \
                            lcd.setCursor (5 + snake, 1);   \
                            lcd.print (char(4));    \
                        }   \
                        lcd.print (char(int (decade) % 5));\
                    }   while (0)

#define SMARTCLICKEVENT(name, stopTime)     do { \
                                                int len = strlen (name);        \
                                                i = (i + 15) % 16;   \
                                                lcd.clear ();   \
                                                for (int j = 0; j < len; ++j) { \
                                                    lcd.setCursor ((i + j) % 16, 0);   \
                                                    lcd.print (name[j]);   \
                                                }   \
                                                lcd.setCursor (0, 1);   \
                                                lcd.print ("Play");    \
                                                PRINT(name);    \
                                                unsigned long curTime = millis();   \
                                                unsigned long printTime = millis();   \
                                                while (millis() - curTime < stopTime) { \
                                                    CLICKEVENT(name);   \
                                                    if (millis() - printTime > 33)  \
                                                        PRINT(name);    \
                                                    delay(1);   \
                                                }   \
                                            }   while (0)

class Dora final {

  short eighter  = 200;
  short quarter  = eighter * 2;
  short half     = quarter * 2;
  short whole    = whole * 2;
  const short duration = quarter;

  const notePlusDelay firstCouplet[50] = {

     {NOTE_A4, eighter},
     {NOTE_AS4, eighter + half + quarter},
     //
     {NOTE_F4, quarter},
     //
     {NOTE_E4, quarter},
     {NOTE_E4, eighter},
     {NOTE_G4, quarter},
     {NOTE_E4, quarter},
     {NOTE_E4, eighter + eighter},
     {NOTE_F4, eighter + half},
     {NOTE_F4, quarter},
     //
     {NOTE_E4, quarter},
     {NOTE_E4, eighter},
     {NOTE_A4, quarter},
     {NOTE_E4, quarter},
     {NOTE_E4, 2 * eighter},
     //
     {NOTE_F4, eighter + half},
     {NOTE_F4, quarter},
     //
     {NOTE_E4, quarter},
     {NOTE_E4, eighter},
     {NOTE_G4, eighter + quarter},
     {NOTE_E4, quarter},
     //
     {NOTE_E4, quarter + eighter},
     {NOTE_F4, eighter + quarter},
     {NOTE_A4, quarter + quarter},
     {NOTE_E4, quarter},
     {NOTE_D4, quarter},
     {NOTE_A4, eighter},
     {NOTE_AS4, eighter + half + quarter},  
     {NOTE_F4, quarter},
     //
     {NOTE_E4, quarter},
     {NOTE_E4, eighter},
     {NOTE_G4, quarter},
     {NOTE_E4, quarter},
     {NOTE_E4, 2 * eighter},
     //
     {NOTE_F4, eighter + half},
     {NOTE_F4, quarter},
     //
     {NOTE_E4, quarter},
     {NOTE_E4, eighter},
     {NOTE_A4, quarter},
     {NOTE_E4, quarter}, //40
     {NOTE_E4, 2 * eighter},
     //
     {NOTE_F4, eighter + half},
     {NOTE_F4, quarter}, 
     {NOTE_E4, quarter},
     {NOTE_E4, eighter},
     {NOTE_G4, eighter + quarter},
     {NOTE_E4, quarter},
     // 
     {NOTE_E4, quarter + eighter},
     {NOTE_F4, eighter + quarter},
     {NOTE_A4, 2 * quarter + eighter}
     //     
  };

  const notePlusDelay chores[56] = {

     {NOTE_F4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter}, //5
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, half + quarter}, //8
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, half + quarter},//11
     //
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, half + quarter + half},//14
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter}, //18
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, half + quarter}, //21
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, half + quarter},//24
     //
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, half},
     {NOTE_F4, eighter},
     {NOTE_A4, eighter + quarter + eighter},//29
     //
     {NOTE_F4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter}, //34
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, half + quarter}, //37
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, half + quarter},//40
     //
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, half + quarter + half},//43
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter}, //47
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, half + quarter}, //50
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, half + quarter},//53
     //
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, half + quarter}, //56
  };

  const notePlusDelay secondCouplet[126] = {

     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, quarter},//3
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, quarter},
     {NOTE_E4, eighter},
     {NOTE_E4, eighter},
     {NOTE_E4, quarter},//9
     //
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, quarter},//15
     //
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},//19
     //
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, quarter},//24
     //
     {NOTE_A4, eighter},
     {NOTE_G4, eighter},
     {NOTE_E4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, quarter},//30
     //
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, half},
     {NOTE_AS4,quarter},//34
     //
     {NOTE_A4, quarter},
     {NOTE_F4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, quarter},//39
     //
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},//45
     //
     {NOTE_AS4,eighter},
     {NOTE_E4, eighter},
     {NOTE_E4, eighter},
     {NOTE_E4, eighter},
     {NOTE_E4, half},//50
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},//54
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, quarter},
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},//59
     //
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},
     {NOTE_AS4,eighter},//67
     //
     {NOTE_A4, quarter},
     {NOTE_E4, quarter},
     {NOTE_E4, quarter},
     {NOTE_G4, quarter},//71
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, eighter},
     {NOTE_E4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, eighter},
     {NOTE_E4, eighter},//79
     //
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, quarter},//84
     //
     {NOTE_G5, eighter},
     {NOTE_G5, eighter},
     {NOTE_F5, eighter},
     {NOTE_F4, eighter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},//92
     //
     {NOTE_G5, eighter},
     {NOTE_G5, eighter},
     {NOTE_F5, quarter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},//99
     //
     {NOTE_F4, quarter},
     {NOTE_F4, quarter},
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},//103
     //
     {NOTE_G4, quarter},
     {NOTE_F4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_F4, quarter},//108
     //
     {NOTE_G5, eighter},
     {NOTE_G5, eighter},
     {NOTE_F5, half},
     {NOTE_A5, quarter},//112
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},//118
     //
     {NOTE_A4, quarter},
     {NOTE_E4, eighter},
     {NOTE_E4, eighter},
     {NOTE_G4, quarter},//122
     //
     {NOTE_F4, half},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_G4, quarter + eighter + half},//126

  };
    const int durationMelody = 119;
public:
    char sing (const char speakerPin, LiquidCrystal &lcd) const {
        
        int i = 0;
        const unsigned long timer = millis();
        unsigned long pauseTime = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Vturilas");
        lcd.setCursor (0, 1);
        lcd.print ("Play");

        for (char numNode = 0; numNode < 49; ++numNode) {
            
            tone (speakerPin, firstCouplet[numNode % 49].note, firstCouplet[numNode % 49].del);
            SMARTCLICKEVENT("Vturilas", firstCouplet[numNode % 49].del);
        }

        tone (speakerPin, firstCouplet[49].note, firstCouplet[49].del);
        SMARTCLICKEVENT("Vturilas", firstCouplet[49].del + eighter);

        //-----------------------------------------------------------------------------------------------------
        
        for (char numNode = 0; numNode < 55; ++numNode) {
            
            tone (speakerPin, chores[numNode % 55].note, chores[numNode % 55].del);
            SMARTCLICKEVENT("Vturilas", chores[numNode % 55].del);
        }

        tone (speakerPin, chores[55].note, chores[55].del);
        SMARTCLICKEVENT("Vturilas", chores[55].del + whole + half);

        //-----------------------------------------------------------------------------------------------------
        
        for (char numNode = 0; numNode < 49; ++numNode) {
            
            tone (speakerPin, secondCouplet[numNode % 49].note, secondCouplet[numNode % 49].del);
            SMARTCLICKEVENT("Vturilas", secondCouplet[numNode % 49].del);
        }

        tone (speakerPin, secondCouplet[49].note, secondCouplet[49].del);
        SMARTCLICKEVENT("Vturilas", secondCouplet[49].del + half);

        for (char numNode = 50; numNode < 111; ++numNode) {

            tone (speakerPin, secondCouplet[numNode % 111].note, secondCouplet[numNode % 111].del);
            SMARTCLICKEVENT("Vturilas", secondCouplet[numNode % 111].del);
        }

        tone (speakerPin, secondCouplet[111].note, secondCouplet[111].del);
        SMARTCLICKEVENT("Vturilas", secondCouplet[111].del + eighter);

        for (char numNode = 112; numNode < 126; ++numNode) {

            tone (speakerPin, secondCouplet[numNode % 126].note, secondCouplet[numNode % 126].del);
            SMARTCLICKEVENT("Vturilas", secondCouplet[numNode % 126].del);
        }

        //-----------------------------------------------------------------------------------------------------
        
        for (char numNode = 0; numNode < 55; ++numNode) {
            
            tone (speakerPin, chores[numNode % 55].note, chores[numNode % 55].del);
            SMARTCLICKEVENT("Vturilas", chores[numNode % 55].del);
        }

        tone (speakerPin, chores[55].note, chores[55].del);
        SMARTCLICKEVENT("Vturilas", chores[55].del + whole + half);

        return next;
    }
};

class Hallelujah final {

  short eighter  = 200;
  short quarter  = eighter * 2;
  short half     = quarter * 2;
  short whole    = whole * 2;
  const short duration = quarter;
  
  const notePlusDelay hallelujahCouplet[56] = {

     {NOTE_E4, eighter},
     {NOTE_F4, eighter},
     //
     {NOTE_G4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_A4, eighter + quarter},
     {NOTE_E4, eighter},
     //
     {NOTE_G4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_A4, quarter},
     {NOTE_A4, eighter},
     {NOTE_A4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_A4, quarter},
     {NOTE_A4, eighter},
     {NOTE_A4, quarter},
     {NOTE_A4, eighter},
     //
     {NOTE_A4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, quarter},
     {NOTE_E4, eighter},
     //
     {NOTE_G4, quarter},
     {NOTE_G4, 2 * eighter + 3 * quarter},
     //
     {NOTE_E4, eighter},
     {NOTE_F4, eighter},
     //
     {NOTE_G4, quarter},
     {NOTE_G4, eighter},
     {NOTE_G4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_A4, quarter},
     {NOTE_A4, eighter},
     {NOTE_B4, quarter},
     {NOTE_A4, eighter},
     //
     {NOTE_C5, quarter},
     {NOTE_C5, eighter},
     {NOTE_C5, quarter},
     {NOTE_C5, eighter},
     //
     {NOTE_C5, quarter},
     {NOTE_C5, eighter},
     {NOTE_D5, quarter},
     {NOTE_C5, eighter},
     //
     {NOTE_D5, quarter},
     {NOTE_D5, eighter},
     {NOTE_D5, quarter},
     {NOTE_D5, eighter},
     //
     {NOTE_E5, quarter},
     {NOTE_E5, eighter},
     {NOTE_E5, quarter},
     {NOTE_D5, eighter},
     //
     {NOTE_D5, quarter},
     {NOTE_C5, 2 * eighter + 3*quarter},
     //
  };

  const notePlusDelay hallelujahChores[19] = {
     {NOTE_E4, eighter},
     {NOTE_F4, eighter},
     //
     {NOTE_A4, quarter + eighter},
     {NOTE_A4, 2 * quarter + 2 * eighter},
     //
     {NOTE_A4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_E4, quarter + eighter},
     {NOTE_E4, 2 * quarter + 2 * eighter},
     //
     {NOTE_E4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_A4, quarter + eighter},
     {NOTE_A4, 2 * quarter + 2 * eighter},
     //
     {NOTE_A4, quarter},
     {NOTE_G4, eighter},
     //
     {NOTE_E4, quarter + 2 * eighter},
     {NOTE_F4, eighter},
     {NOTE_E4, eighter},
     //
     {NOTE_D4, half + quarter},
     //
     {NOTE_C4, half + quarter}
     //
  };
    const int durationMelody = 32;

public: 

    char sing (const char speakerPin, LiquidCrystal &lcd)  {

        int i = 0;
        const unsigned long timer = millis();
        unsigned long pauseTime = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hallelujah");
        lcd.setCursor (0, 1);
        lcd.print ("Play");

        for (char numNode = 0; numNode < 56; ++numNode) {
            
            tone (speakerPin, hallelujahCouplet[numNode % 56].note, hallelujahCouplet[numNode % 56].del);
            SMARTCLICKEVENT("Hallelujah", hallelujahCouplet[numNode % 56].del);
        }

        //-----------------------------------------------------------------------------------------------------
        
        for (char numNode = 0; numNode < 19; ++numNode) {
        
            tone (speakerPin, hallelujahChores[numNode % 19].note, hallelujahChores[numNode % 19].del);
            SMARTCLICKEVENT("Hallelujah", hallelujahChores[numNode % 19].del);
        }
        return next;
    }
};

class Gangsta final {

  short eighter  = 200;
  const short duration = 200;
  short quarter  = eighter * 2;
  short half     = quarter * 2;
  short whole    = whole * 2;

  const notePlusDelay gangstaCouplet[15] = {
    
    {NOTE_GS4, half + quarter}, 
    {NOTE_DS5, half},
    {NOTE_D5,  quarter},
    {NOTE_C5,  quarter},
    //
    {NOTE_B4,  half + quarter},
    {NOTE_C5,  half},
    {NOTE_D5,  quarter},
    {NOTE_DS5, quarter},
    //
    {NOTE_GS4, half + quarter}, 
    {NOTE_DS5, half},
    {NOTE_D5,  quarter},
    {NOTE_C5,  quarter},
    //
    {NOTE_B4,  half + eighter},
    {NOTE_C5,  half},
    {NOTE_G4,  half + eighter}
  };

  const notePlusDelay gangstaChores[16] = {
    
    {NOTE_DS5, quarter}, 
    {NOTE_F5, quarter},
    {NOTE_DS5,eighter},
    {NOTE_D5, quarter},
    {NOTE_C5, quarter},
    {NOTE_GS4, quarter},
    {NOTE_C5, eighter},
    {NOTE_C5, quarter},
    //
    {NOTE_B4, quarter},
    {NOTE_G4, eighter},
    {NOTE_D5, quarter},
    {NOTE_DS5, quarter + eighter}, 
    {NOTE_D5, eighter},
    {NOTE_C5, eighter},
    {NOTE_AS4, eighter},
    {NOTE_C5, half + quarter},
  };

    const int durationMelody = 25;

public:

    char sing (const char speakerPin, LiquidCrystal &lcd)  {

        int i = 0;
        const unsigned long timer = millis();
        unsigned long pauseTime = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gangsta");
        lcd.setCursor (0, 1);
        lcd.print ("Play");

        for (char numNode = 0; numNode < 15; ++numNode) {
        
            tone (speakerPin, gangstaCouplet[numNode % 15].note, gangstaCouplet[numNode % 15].del);
            SMARTCLICKEVENT("Gangsta", gangstaCouplet[numNode % 15].del);
        }

        //-----------------------------------------------------------------------------------------------------
        
        for (char numNode = 0; numNode < 31; ++numNode) {

            tone (speakerPin, gangstaChores[numNode % 16].note, gangstaChores[numNode % 16].del);
            SMARTCLICKEVENT("Gangsta", gangstaChores[numNode % 16].del);
        }
        tone (speakerPin, gangstaChores[15].note, gangstaChores[15].del);
        SMARTCLICKEVENT("Gangsta", gangstaChores[15].del);

        return next;
    }
};

class Kuznetchik final {
 
  short eighter  = 125;
  const short duration = 125;
  short quarter  = eighter * 2;
  short half     = quarter * 2;
  short whole    = whole * 2;

  const notePlusDelay pripev[17] = {
    
    {NOTE_A5, quarter}, 
    //
    {NOTE_B5, quarter },
    {NOTE_B5, eighter}, 
    {NOTE_B5, eighter},
    {NOTE_B5, quarter}, 
    {NOTE_B5, quarter},
    //
    {NOTE_C6, quarter },
    {NOTE_C6, eighter}, 
    {NOTE_C6, eighter},
    {NOTE_C6, quarter}, 
    {NOTE_C6, quarter},
    //
    {NOTE_C6, quarter},
    {NOTE_B5, quarter },
    {NOTE_A5, quarter },
    {NOTE_GS5,quarter},
    //
    {NOTE_A5, quarter },
    {NOTE_A5, half},
  };

  const notePlusDelay couplet[14] = {
    
    {NOTE_A5, quarter}, 
    {NOTE_E5, quarter},
    {NOTE_A5, quarter}, 
    {NOTE_E5, quarter},
    //
    {NOTE_A5, quarter}, 
    {NOTE_GS5,quarter},
    {NOTE_GS5,half   },
    //
    {NOTE_GS5,quarter}, 
    {NOTE_E5, quarter},
    {NOTE_GS5,quarter}, 
    {NOTE_E5, quarter},
    //
    {NOTE_GS5,quarter}, 
    {NOTE_A5, quarter},
    {NOTE_A5, half} 
  };

    const int durationMelody = 17;

public:

    char sing (const char speakerPin, LiquidCrystal &lcd)  {
        
        int i = 0;
        const unsigned long timer = millis();
        unsigned long pauseTime = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("kuznechik");
        lcd.setCursor (0, 1);
        lcd.print ("Play");

        for (char numNode = 0; numNode < 26; ++numNode) {

            tone (speakerPin, couplet[numNode % 14].note, couplet[numNode % 14].del);
            SMARTCLICKEVENT("Kuznechik", couplet[numNode % 14].del);

        }
        
        tone (speakerPin, couplet[13].note, couplet[13].del);
        SMARTCLICKEVENT("Kuznechik", half + quarter);

        //-----------------------------------------------------------------------------------------------------

        for (char numNode = 0; numNode < 33; ++numNode) {
        
            tone (speakerPin, pripev[numNode % 17].note, pripev[numNode % 17].del);
            SMARTCLICKEVENT("Kuznechik", pripev[numNode % 17].del);
        }
        
        tone (speakerPin, couplet[16].note, couplet[16].note);
        SMARTCLICKEVENT("Kuznechik", whole);

        return next;
    }
};

class MortalKombat final {

  short sixteenth = 110;
  short eighter   = sixteenth * 2;
  short quarter   = eighter * 2;
  short half      = quarter * 2;
  short whole     = whole * 2;
  const short duration = quarter;

  const notePlusDelay introduction[32] = {

     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_C5, eighter},
     {NOTE_A4, eighter}, 
     {NOTE_D5, eighter},
     {NOTE_A4, eighter},
     {NOTE_E5, eighter},
     {NOTE_D5, eighter},    
     //-----------------------------------------------------------------------------------------------------
     {NOTE_C5, eighter},
     {NOTE_C5, eighter},
     {NOTE_E5, eighter},
     {NOTE_C5, eighter}, 
     {NOTE_G5, eighter},
     {NOTE_C5, eighter},
     {NOTE_E5, eighter},
     {NOTE_C5, eighter},    
     //-----------------------------------------------------------------------------------------------------
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_AS4, eighter},
     {NOTE_G4, eighter}, 
     {NOTE_C5, eighter},
     {NOTE_G4, eighter},
     {NOTE_D5, eighter},
     {NOTE_C5, eighter}, 
     //
     {NOTE_F4, eighter},
     {NOTE_F4, eighter},
     {NOTE_A4, eighter},
     {NOTE_F4, eighter}, 
     {NOTE_C5, eighter},
     {NOTE_F4, eighter},
     {NOTE_C5, eighter},
     {NOTE_AS4, eighter}, 
  };

  const notePlusDelay couplet[18] = {

     {NOTE_A4, sixteenth},
     {NOTE_E5, eighter  },
     {NOTE_A4, sixteenth},
     {NOTE_C5, eighter  }, 
     {NOTE_A4, sixteenth},
     {NOTE_B4, eighter  },
     {NOTE_A4, sixteenth},
     {NOTE_C5, eighter  },  

     {NOTE_A4, sixteenth},  
     {NOTE_B4, eighter  },
     //-----------------------------------------------------------------------------------------------------
     {NOTE_A4, sixteenth},
     {NOTE_E5, eighter  },
     {NOTE_A4, sixteenth},
     {NOTE_C5, eighter  }, 
     {NOTE_A4, eighter  },
     {NOTE_G4, eighter  },
     {NOTE_G4, eighter  },
     {NOTE_A4, quarter  } 
  };

  const notePlusDelay bridge[25] = {

     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_G4,  eighter            },
     {NOTE_C5,  eighter            },
     //-----------------------------------------------------------------------------------------------------
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_G4,  eighter            },
     {NOTE_E4,  eighter            },//12
     //-----------------------------------------------------------------------------------------------------
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_G4,  eighter            },
     {NOTE_C5,  eighter            },//18
     //-----------------------------------------------------------------------------------------------------
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter + sixteenth},
     {NOTE_A4,  eighter            },
     {NOTE_A4,  eighter            },
     {NOTE_A4,  eighter            },
     {NOTE_A4,  eighter            },
     {NOTE_A4,  eighter            }//25
     //-----------------------------------------------------------------------------------------------------
  };

  const notePlusDelay conclusion[24] = {

     {NOTE_A4, eighter},
     {NOTE_A4, eighter},
     {NOTE_C5, eighter},
     {NOTE_A4, eighter}, 
     {NOTE_D5, eighter},
     {NOTE_A4, eighter},
     {NOTE_E5, eighter},
     {NOTE_D5, eighter},    
     //-----------------------------------------------------------------------------------------------------
     {NOTE_C5, eighter},
     {NOTE_C5, eighter},
     {NOTE_E5, eighter},
     {NOTE_C5, eighter}, 
     {NOTE_G5, eighter},
     {NOTE_C5, eighter},
     {NOTE_E5, eighter},
     {NOTE_C5, eighter},    
     //-----------------------------------------------------------------------------------------------------
     {NOTE_G4, eighter},
     {NOTE_G4, eighter},
     {NOTE_AS4, eighter},
     {NOTE_G4, eighter}, 
     {NOTE_C5, eighter},
     {NOTE_G4, eighter},
     {NOTE_D5, eighter},
     {NOTE_C5, eighter},  
     //-----------------------------------------------------------------------------------------------------
     
  };
    const int durationMelody = 65;
public:
    char sing (const char speakerPin, LiquidCrystal &lcd) const {
        
        int i = 0;
        const unsigned long timer = millis();
        unsigned long pauseTime = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mortal Kombat");
        lcd.setCursor (0, 1);
        lcd.print ("Play");

        for (int repeate = 0; repeate < 2; ++repeate)
            for (char numNode = 0; numNode < 32; ++numNode) {
                
                tone (speakerPin, introduction[numNode % 32].note, introduction[numNode % 32].del);
                SMARTCLICKEVENT("Mortal Kombat", introduction[numNode % 32].del);
            }     
       //-----------------------------------------------------------------------------------------------------
        for (char numNode = 0; numNode < 49; ++numNode) {
            
            tone (speakerPin, bridge[numNode % 25].note, bridge[numNode % 25].del);
            SMARTCLICKEVENT("Mortal Kombat", bridge[numNode % 25].del);
        }
        //-----------------------------------------------------------------------------------------------------

        tone (speakerPin, bridge[24].note, bridge[24].del);
        SMARTCLICKEVENT("Mortal Kombat", bridge[24].del + eighter);
        
        for (int repeate = 0; repeate < 2; ++repeate) {
            for (int loop = 0; loop < 3; ++loop)
                for (char numNode = 0; numNode < 10; ++numNode) {
                    
                    tone (speakerPin, couplet[numNode % 10].note, couplet[numNode % 10].del);
                    SMARTCLICKEVENT("Mortal Kombat", couplet[numNode % 10].del);
                }
            for (char numNode = 10; numNode < 18; ++numNode) {
                    
                    tone (speakerPin, couplet[numNode % 18].note, couplet[numNode % 18].del);
                    SMARTCLICKEVENT("Mortal Kombat", couplet[numNode % 18].del);
                }
        }
        //-----------------------------------------------------------------------------------------------------
        for (char numNode = 0; numNode < 24; ++numNode) {
            
            tone (speakerPin, bridge[numNode % 25].note, bridge[numNode % 25].del);
            SMARTCLICKEVENT("Mortal Kombat", bridge[numNode % 25].del);
        }
        for (int loop = 0; loop < 3; ++loop)
            for (char numNode = 0; numNode < 10; ++numNode) {
                
                tone (speakerPin, couplet[numNode % 10].note, couplet[numNode % 10].del);
                SMARTCLICKEVENT("Mortal Kombat", couplet[numNode % 10].del);
            }

        for (char numNode = 10; numNode < 18; ++numNode) {
                
            tone (speakerPin, couplet[numNode % 18].note, couplet[numNode % 18].del);
            SMARTCLICKEVENT("Mortal Kombat", couplet[numNode % 18].del);
        }

        //-----------------------------------------------------------------------------------------------------
        
        for (char numNode = 0; numNode < 24; ++numNode) {
                
            tone (speakerPin, conclusion[numNode % 24].note, conclusion[numNode % 24].del);
            SMARTCLICKEVENT("Mortal Kombat", conclusion[numNode % 24].del);
        }

        return next;
    }
};
