#include<Servo.h>
Servo HORIZONTAL;
Servo VERTICAL1;
//Servo VERTICAL2;
int V1POS;
int DELAY = 250;
int TOL = 0;
//int V2POS = 60;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HORIZONTAL.attach(9); //Horizontal 360 Servo
  VERTICAL1.attach(10); // Vertical Servo 
  V1POS = 60;
  VERTICAL1.write(V1POS);
  delay(1000);
  //VERTICAL2.attach(11); // Vertical Servo 
}


void loop() {
  // put your main code here, to run repeatedly:
  int LDRTR = analogRead(0);
  int LDRTL = analogRead(1);
  int LDRBR = analogRead(2);
  int LDRBL = analogRead(3);
  
  
  int AVGT = (LDRTL + LDRTR) / 2;
  int AVGB = (LDRBR + LDRBL) / 2;
  int AVGR = (LDRTR + LDRBR) / 2;
  int AVGL = (LDRBL + LDRTL) / 2;

  int DIFFV = abs((AVGT - AVGB));
  int DIFFH = abs((AVGR - AVGL));


/*
 * Less than 92 will make it rotate clockwise
 * More than 92 will make it rotate anti-clockwise
*/
  
  if (DIFFH > TOL)
  {
    if (AVGR > AVGL)
    {
      HORIZONTAL.write(86);
    }
    if (AVGL > AVGR)
    {
      HORIZONTAL.write(98);
    }
    if (abs(AVGL - AVGR) <= 5) //<<<<-----------------------------VARIABLE
    {
      HORIZONTAL.write(92);
    }
  }

  if (DIFFV > TOL)
  {
    if( V1POS >= 179)
      {
        V1POS=170;
      }

    else if(V1POS <= 1)
      {
        V1POS=10;
      }
      
    if (AVGT > AVGB)
    {
      V1POS++;
    }
    else if (AVGB > AVGT)
    {
      V1POS--;
    }
     VERTICAL1.write(V1POS);
  }
  Serial.print("Vertical Servo Position: ");
  Serial.println(V1POS);
  Serial.print("Top Right LDR Reading: ");
  Serial.println(LDRTR);
  Serial.print("Top Left LDR Reading: ");
  Serial.println(LDRTL);
  Serial.print("Bottom Right LDR Reading: ");
  Serial.println(LDRBR);
  Serial.print("Bottom Left LDR Reading: ");
  Serial.println(LDRBL);
  delay(DELAY);
}
