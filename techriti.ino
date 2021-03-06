//We always have to include the library
#include <LedControl.h>

 int switch1;
 int switch2;

int lastButtonState1;
int lastButtonState2;
int buttonState;
int buttonPin1=6;
int buttonPin2=7;
// the current reading from the input pin
   // the previous reading from the input pin
int lastButtonState = LOW;
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime1 = 0;  // the last time the output pin was toggled
long debounceDelay1 = 50;    // the debounce time; increase if the output flickers

int debounceDelay;

int B_row=1;
int B_col=4;
int P_left=3 , P_right=5;
boolean ns = true; 
boolean ew = true;
int Bricks[][8]={{0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,1,1,1,1,1,1,0},
                 {0,1,1,1,1,1,1,0},
                 {0,1,1,1,1,1,1,0}};

int paddle[]={0,0,0,1,1,1,0,0};

int lastDebounceTime;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin(9600);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  for(int i=0;i<8;i++)
   for(int j=0;j<8;j++)
    if(Bricks[i][j]==1)
      lc.setLed(0,i,j,true);
  pinMode(7, INPUT);
  pinMode(6, INPUT);//used for switch
  for(int i=0;i<8;i++)
  if(paddle[i]==1)
  lc.setLed(0,0,i,true);
}

void movePaddle(int dir)
{
  /*
  if(dir==1 && P_right <7)
  {
    
    lc.setLed(0,0,P_left,false);
    lc.setLed(0,0,P_right+1,true);
    P_left++;P_right++;
    
  }*/
  
  if(dir==1 && P_right <7)
  {
    
    lc.setLed(0,0,P_left-1,true);
    lc.setLed(0,0,P_right,false);
    P_left--;P_right--;
    
  }else if(dir==-1 && P_left>0)
  {
    lc.setLed(0,0,P_left,false);
    lc.setLed(0,0,P_right+1,true);
    P_left++;P_right++;
  }
  
}
void moveball()
  { 
    
    lc.setLed(0,B_row,B_col,false);
    if (ns == false && ew==false) // left means ew false 
    {
      B_row--;
      B_col--;
    }
    
  else if (ns == false && ew == true)
    {
      B_row--;
      B_col++;
    }
   else if (ns == true && ew==false)
    {
      B_row++;
      B_col--;
    }
    
  else if (ns == true && ew == true)
    {
      B_row++;
      B_col++;
    }
     lc.setLed(0,B_row,B_col,true); 
  }
 
 void Check()
 {
   if (B_row==0 || B_row==7)
   ns=!ns;
   else if(Bricks[B_row][B_col]==1)
   {ns=!ns;
   Bricks[B_row][B_col]=0;
   }
   if (B_col==0 || B_col==7)
   ew=!ew;
   
   
 }
 
 void debounce(int reading, int &lastButtonState,int dir)
{
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH ) {
        movePaddle(dir);
      }
      lastButtonState = reading;
}
  }
}
 
   
 void loop()
 {  switch1 = digitalRead(7);Serial.println("Switch1");Serial.println(switch1);
 switch2 = digitalRead(6); Serial.println("Switch2");Serial.println(switch2);

 /*
 if (switch1==1)
 {movePaddle(-1);}
if(switch2==1)
{movePaddle(1);} 
*/
    // read the state of the switch into a local variable:
 /*
  int left = digitalRead(buttonPin1);
  debounce(left,lastButtonState1,1);
  int right=digitalRead(buttonPin2);
  debounce(right,lastButtonState2,-1);
  */
  
   moveball();
  Check();
  delay(5000);
 }
