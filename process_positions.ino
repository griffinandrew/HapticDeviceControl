//Griffin Heyrich
//BU_MBL 6/2022
//the function of this set of code is to utilize the pyfirmata class to read in from file where coordinates
//are being sent and send them to each individual lcd board, as well as being mapped to the appropriate volume
//to be pumped into the chanmbers of our robot to create movement. 

#include <LiquidCrystal.h>
#include <Firmata.h>
#include <math.h>

const int rs = 12, en1 = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en1, d4, d5, d6, d7);

const int en2 = 10; 
LiquidCrystal lcd2(rs, en2, d4, d5, d6, d7);

const int en3 = 9;
LiquidCrystal lcd3(rs, en3, d4, d5, d6, d7); 

//omni device coordinates 
String posX = ""; String posY = ""; String posZ = "";

//omni device coordinates after converted to double
float pos_X = 0.0; float pos_Y = 0.0; float pos_Z = 0.0;

// abg coordinates "basis" vectors
float a1 = 0; float a2 = 1;
float b1 = -0.866; float b2 = -0.5;
float c1 = 0.866; float c2 = -0.5;

// Nunchuck position in abg coordinates
float alphaCoord = 0; float betaCoord = 0; float gammaCoord = 0;

// Chamber volume values
float alphaVol = 0; float betaVol = 0; float gammaVol = 0;

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
  delay(100);
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
  
  lcd.print("vol X: ");
  lcd2.print("vol Y: "); 
  lcd3.print("vol Z: ");
  
  lcd.setCursor(0,1);
  lcd2.setCursor(0,1);
  lcd3.setCursor(0,1);
  
  processStr(strdata); //send to process string to break into each coordinate

  //need to convert to char* before using atof()
  char*Xstr = &posX[0];
  char*Ystr = &posY[0];
  char*Zstr = &posZ[0];

  //converting char* to float
  pos_X = atof(Xstr);
  pos_Y = atof(Ystr) + 65.511 ; // bascailly  i am adjusting for the origin
  pos_Z = atof(Zstr) + 88.114; // note in jacobs he is subtracting the origin here i am adding
  
 
  alphaCoord = pos_Y;
  betaCoord = (pos_X * b1) + (pos_Y * b2);
  gammaCoord = (pos_X * c1) + (pos_Y * c2);

  //map the coordinate system to the appropriate volume 
  alphaVol = pos_Z + (312*alphaCoord/440); 
  betaVol = pos_Z + (312*betaCoord/440);
  gammaVol = pos_Z + (312*gammaCoord/440);

  //invert coordinates
  alphaCoord = -alphaCoord;
  betaCoord = -betaCoord;
  gammaCoord = -gammaCoord;

  //Constrain volume values from 0 to 100
  alphaVol = constrain(alphaVol, 0, 100);
  betaVol = constrain(betaVol, 0, 100);
  gammaVol = constrain(gammaVol, 0, 100);

  lcd.print(alphaVol);
  lcd2.print(betaVol);
  lcd3.print(gammaVol);
 
  analogWrite(3,alphaVol); // pin values will be different 
  analogWrite(5,betaVol);
  analogWrite(6,gammaVol);
 
}

void processStr(char* strdata)
{

  int num_space = 0;
  String str(strdata);
  posX = "";
  posY = "";
  posZ = ""; // reset the string to empty at the beginning of the loo[p
  
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
      posX += str[i];
    }
    if (!(isspace(str[i])) && num_space == 1)  //y 
    {
      posY +=str[i];
    }
    if (!(isspace(str[i])) && num_space == 2) //z
    {
      posZ +=str[i];
    }
  }
}
