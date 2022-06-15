//Griffin Heyrich
//BU_MBL 6/2022
//the function of this set of code is to utilize the pyfirmata class to read in from file where coordinates are being sent and send them to each individual lcd board

#include <LiquidCrystal.h>
#include <Firmata.h>

const int rs = 12, en1 = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en1, d4, d5, d6, d7);

const int en2 = 10; 
LiquidCrystal lcd2(rs, en2, d4, d5, d6, d7);

const int en3 = 9;
LiquidCrystal lcd3(rs, en3, d4, d5, d6, d7); 

String pos1 = "";
String pos2 = "";
String pos3 = "";


void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd2.begin(16, 2);
  lcd3.begin(16, 2);
    
  lcd.print("Hola, amigo!");
  lcd2.print("Hola, amigo!"); 
  lcd3.print("Hola, amigo!");
  
  Firmata.attach(STRING_DATA, stringDataCallback);
  Firmata.begin();
}


void loop() 
{
  delay(100); //not surte if needed or not need to test
  while(Firmata.available() )
  {
    Firmata.processInput(); // this sends incoming data to callback function
  }
}


void stringDataCallback(char* strdata)
{
  
  lcd.clear();
  lcd2.clear();
  lcd3.clear();
  
  lcd.print("pos1: ");
  lcd2.print("pos2: "); 
  lcd3.print("pos3: ");
  
  lcd.setCursor(0,1);
  lcd2.setCursor(0,1);
  lcd3.setCursor(0,1);
  lcd.blink();
  lcd2.blink();
  lcd3.blink();
  
  processStr(strdata); //send to process string to break into each coordinate
  
  lcd.print(pos1);
  lcd2.print(pos2);
  lcd3.print(pos3);

}


void processStr(char* strdata)
{

  int num_space = 0;
  String str(strdata);
  pos1 = "";
  pos2 = "";
  pos3 = ""; // reset the string to empty at the beginning of the loo[p
  
  for (int i = 0; i < str.length(); i++)  
  {
    if (isspace(str[i]))
    {
      num_space+=1;
    }
    if (num_space == 3) 
    {
      return; // if the string has been properly converted all the way, return to call
    }
    
    if (!(isspace(str[i])) && num_space == 0) //x
    {
      pos1 += str[i];
    }
    if (!(isspace(str[i])) && num_space == 1)  //y 
    {
      pos2 +=str[i];
    }
    if (!(isspace(str[i])) && num_space == 2) //z
    {
      pos3 +=str[i];
    }
  }
}
