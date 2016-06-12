#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10); // RX, TX



//keypad
int row[]={A1,A0,2,3};// Defining row pins of keypad connected to Arduino pins
int col[]={4,5,6,7};//Defining column pins of keypad connected to Arduino
int i,j,count=1,key_id=0,flag,entry=0;// See About the Program 
int col_scan;// Variable to identify a key press
char temp_press; // Variable to hold value of key press
char check[6],pass[6]; // See About the Program
int wrong = 0;

//LED
int rled = 13;
int gled = 12;

//motor
int motorPin = 8;
int motorPin2 = 11;

void setup()
{
  for(i=0;i<=3;i++)
  {
    pinMode(row[i],OUTPUT);
    pinMode(col[i],INPUT);
    digitalWrite(col[i],HIGH);
  }
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
Serial.begin(9600); // set the data rate for the SoftwareSerial port
mySerial.begin(9600);
pinMode(motorPin, OUTPUT);
pinMode(motorPin2, OUTPUT);
digitalWrite(gled,HIGH);
Serial.println("SET 5 Digit PASS");
}

/* Main Program Begins */

void loop()
{ 
  while(entry<=4)// Password Setting Loop begins
  {
    SetPassword();
  }
// Password Setting Loop Ends

  key_id=0;
if(wrong<3){
  keyscan(); // Scan for a Key Press

/* Actions on Key Press begins */

  if(key_id==1) // Condition to Check Key is Pressed
  {
    check[count]=temp_press;
    count++;

    /* Condition to Unlock Begins*/

    if(temp_press=='A')
    {
      checkPassword();
      if(flag==0)
      {
        digitalWrite(rled,LOW);
        digitalWrite(gled,HIGH);
        Serial.println();
        Serial.println("UNLOCKED");
        digitalWrite(motorPin,HIGH);
        delay(2000);
        digitalWrite(motorPin,LOW);
        wrong = 0;
      }
      else{
         Serial.println();
        Serial.println("WRONG PASSWORD");
        delay(200);
        Serial.println("LOCKED");

        wrong++;
        if(wrong>=3)
          Call();
      }
      count=1; // Resetting the counter variable
    }

    /* Condition to Unlock Ends*/

    /* Condition to Change Password Begins */

    else if(temp_press=='C')
    {
      checkPassword();
      if(flag==0)
      {
        digitalWrite(rled,LOW);
        digitalWrite(gled,HIGH);
        Serial.println();
        Serial.println("ENTER NEW PASS");
        key_id=0;
        entry=0;
        while(entry<=4)
          SetPassword();
      }
      else{
         Serial.println();
        Serial.println("WRONG PASSWORD");
      }
      count=1; // Resetting the counter variable
    }

    /* Condition to Change Password Ends */

    /* Condition to LOCK Begins*/

    else if(temp_press=='B')
    {
      digitalWrite(gled,LOW);
      digitalWrite(rled,HIGH);
       Serial.println();
      Serial.println("LOCKED");
       digitalWrite(motorPin2,HIGH);
       delay(2000);
       digitalWrite(motorPin2,LOW);

      count=1; // Resetting the counter variable
    }
/* Condition to LOCK Ends*/
  
  else if(temp_press=='D'){
    Serial.println();
    Serial.println("Sending password to registered Mobile no.");
    key_id = 0;
    count = 1;
    ForgotMessage();
  }
  }
  }
/* Actions on Key Press Ends*/
}

/* Main Program Ends */


void SetPassword() // Subroutine to SET User Defined Password
{
  keyscan();
  if(key_id==1)
  {
    if(temp_press=='A'||temp_press=='C'||temp_press=='B') // Condition to Check for an Invalid Keypress 
    {
      Serial.println("INVALID KEYS");
      entry=0;
    }
    else 
    {
      pass[entry]=temp_press;

    }
  }
  key_id=0;
  if(entry==5)
  {
    digitalWrite(gled,LOW);
    digitalWrite(rled,HIGH);
     Serial.println();
     Serial.write(13);
    Serial.println("PASSWORD SET & LOCKED");
  }
} // Subroutine to SET Password ENDS

char keyscan()// Subroutine to Scan Keypad for a Keypress
{
  for(i=0; i<=3; i++)
  {
    digitalWrite(row[0],HIGH);
    digitalWrite(row[1],HIGH);
    digitalWrite(row[2],HIGH);
    digitalWrite(row[3],HIGH);
    digitalWrite(row[i],LOW);
    for(j=0; j<=3; j++)
    {
      col_scan=digitalRead(col[j]);
      if(col_scan==LOW)
      {
        key_id=1;
        entry++;
        temp_press=keypress(i,j);
        Serial.print("X");
        delay(300);
        break;
      }
    }
  }
}// Subroutine to Scan Keypress Ends

char keypress(int i, int j) // Subroutine to Identify the value of Key pressed
{
  if(i==0&&j==0)
  {
    return('1');
  }
  else if(i==0&&j==1)
  {
    return('2');
  }
  else if(i==0&&j==2)
  {
    return('3');
  }
  else if(i==0&&j==3)
  {
    return('A');
  }
  else if(i==1&&j==0)
  {
    return('4');
  }
  else if(i==1&&j==1)
  {
    return('5');
  }
  else if(i==1&&j==2)
  {
    return('6');
  }
  else if(i==1&&j==3)
  {
    return('B');
  }
  else if(i==2&&j==0)
  {
    return('7');
  }
  else if(i==2&&j==1)
  {
    return('8');
  }
  else if(i==2&&j==2)
  {
    return('9');
  }
  else if(i==2&&j==3)
  {
    return('C');
  }
  else if(i==3&&j==0)
  {
    return('*');
  }
  else if(i==3&&j==1)
  {
    return('0');
  }
  else if(i==3&&j==2)
  {
    return('#');
  }
  else if(i==3&&j==3)
  {
    return('D');
  }
} // Subroutine to identify Keypress Ends

void checkPassword() // Subroutine to Check User Input Data with SET Password
{
  flag=0;
  for(i=1;i<=5&&flag==0;i++)
  {
    if(check[i]==pass[i])
      flag=0;
    else 
      flag=1;

  }
} // Subroutine to check password ends


void Call(){
  Serial.println("Security Alert!!!");
  delay(200);
  mySerial.println("ATD9481241202;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  delay(10000);
  Serial.println("Called ATD9481241202");
  AlertMessage();
}

void AlertMessage(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919481241202\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Alert!!! Someone is trying to break the LOCK...");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void ForgotMessage(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919481241202\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Your Requested Password...");
  for(i=1; i<=5; i++)
    mySerial.print(pass[i]);
  mySerial.println();// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


