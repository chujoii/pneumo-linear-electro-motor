/*
  created 2013.04.13
  by Roman V. Prikhodchenko chujoii@gmail.com
  license GPL
*/



// strange but lcd.print(12);	not work - after upload only led blinking 
//             lcd.print(String(12)); not work - blinking
// wokr lcd.print("12"); work
//
//	char buf[12]; // "-2147483648\0"
//	itoa(7, buf, 10);
//	lcd.print(buf);
 

#include <encoder.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display



char buf[9]; // menu_max_value_length


encoder enc(2, 3, 0);


int btn = 4;


int vibro_a = 10;
int vibro_b = 11;

boolean changes = true;


void eintrptwrapper()
{
	enc.encoderhalf();
	changes = true;
}

void setup ()
{
	lcd.init();                      // initialize the lcd 
	
	// Print a message to the LCD.
	lcd.backlight();

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("setup [ok]");

	
	pinMode(btn, INPUT);
	digitalWrite(btn, HIGH);

	attachInterrupt(0, eintrptwrapper, CHANGE);
	attachInterrupt(1, eintrptwrapper, CHANGE);

	pinMode(vibro_a, OUTPUT);
	pinMode(vibro_b, OUTPUT);

}



void loop ()
{
	int a;
	a = enc.get_angle()>>2;
	if (a < 0) {a=0;};
	if (changes){
		changes = false;
		
		lcd.clear();
		lcd.setCursor(0,0);
		
		itoa(a, buf, 10); // fixme need use sprintf ?
		
		lcd.print(buf);
	}


	delay(a);
	
	digitalWrite(vibro_a, HIGH);
	digitalWrite(vibro_b, LOW);

	delay(a);

	digitalWrite(vibro_a, LOW);
	digitalWrite(vibro_b, HIGH);
}

