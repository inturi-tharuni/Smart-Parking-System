#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

Servo myservo;

#define ir_enter 2
#define ir_back 4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8

int S1 = 0;
int S2 = 0;
int S3 = 0;
int S4 = 0;

int slot = 4;

int flag1 = 0;
int flag2 = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(ir_car1, INPUT);
    pinMode(ir_car2, INPUT);
    pinMode(ir_car3, INPUT);
    pinMode(ir_car4, INPUT);

    pinMode(ir_enter, INPUT);
    pinMode(ir_back, INPUT);

    myservo.attach(3);
    myservo.write(90);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0,0);
    lcd.print("SMART PARKING");

    lcd.setCursor(0,1);
    lcd.print("SYSTEM");

    delay(3000);

    lcd.clear();

    Read_Sensor();

    int total = S1 + S2 + S3 + S4;
    slot = slot - total;
}

void loop()
{
    Read_Sensor();

    lcd.setCursor(0,0);
    lcd.print("Available:");
    lcd.print(slot);
    lcd.print("   ");

    lcd.setCursor(0,1);
    lcd.print("S1:");
    lcd.print(S1 ? "F" : "E");

    lcd.setCursor(8,1);
    lcd.print("S2:");
    lcd.print(S2 ? "F" : "E");

    lcd.setCursor(0,2);
    lcd.print("S3:");
    lcd.print(S3 ? "F" : "E");

    lcd.setCursor(8,2);
    lcd.print("S4:");
    lcd.print(S4 ? "F" : "E");

    if(digitalRead(ir_enter)==0 && flag1==0)
    {
        if(slot>0)
        {
            flag1=1;

            if(flag2==0)
            {
                myservo.write(180);
                slot--;
            }
        }
        else
        {
            lcd.clear();
            lcd.print("PARKING FULL");
            delay(1500);
        }
    }

    if(digitalRead(ir_back)==0 && flag2==0)
    {
        flag2=1;

        if(flag1==0)
        {
            myservo.write(180);
            slot++;
        }
    }

    if(flag1==1 && flag2==1)
    {
        delay(1000);

        myservo.write(90);

        flag1=0;
        flag2=0;
    }

    delay(100);
}

void Read_Sensor()
{
    S1 = digitalRead(ir_car1)==0;
    S2 = digitalRead(ir_car2)==0;
    S3 = digitalRead(ir_car3)==0;
    S4 = digitalRead(ir_car4)==0;
}