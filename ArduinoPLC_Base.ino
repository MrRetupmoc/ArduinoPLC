/*------------------------------------------------------------------------------------------------------
                              Author : Evan Richinson aka MrRetupmoc42
               
Arduino PLC with Sinking Moffsets for Output and 1/5 Resistor Analog Input for 25vDC Inputs
   
March 21th 2016   : Wrote PLC Scan Process + Memory Input, Output and Bits + Scan Time Calculation
                   
-------------------------------------------------------------------------------------------------------*/

//Config Deafult Values    -------------------------------------------------------------------------------

unsigned long scantime_init;
unsigned long scantime_end;
int i = 0; //Loop Counter
int inputVoltageThreshold = ((5.0 / 1024) * 1); // > 1v Threshold for Analog Input to Digital

//Config of Arduino PLC Pins   ----------------------------------------------------------------------------

/*//if UNO
int Input_MAX = 6;
int Output_MAX = 11;
byte Input[] = {A5, A4, A3, A2, A1, A0};
int Output[Output_MAX] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
*/

//if MEGA
const int Input_MAX = 16;
const int Output_MAX = 11;
byte Input_Analog_Pins[Input_MAX] = {A15, A14, A13, A12, A11, A10, A9, A8, A7, A6, A5, A4, A3, A2, A1, A0};
int Output_Digital_Pins[Output_MAX] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

//---------------------------------------------------------------------------------------------------------

//Read Input Memory
bool Input_Analog[Input_MAX]; //Start, Stop

//Memory Bits and Bytes, Words and Nonesence
bool Memory_bool[16]; //System_Running, 
//int Memory_int[16];

//Write Output Momory
bool Output_Digital[Input_MAX]; //Red Light, Green Light

//----------------------------------------------------------------------------------------------------------

void setup() {
  // Loops pin creation...
  for(i = 0; i < Input_MAX; i++) { //Init input Pins
    pinMode(Input_Analog_Pins[i], INPUT);
  }

  for(i = 0; i < Output_MAX; i++) { //Init output Pins
    pinMode(Output_Digital_Pins[i], OUTPUT);
  }

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  //Start Scan Time    ---------------------------------------------------------------
  scantime_init = millis();
  
  
  //Input Pull    --------------------------------------------------------------------
  for(i = 0; i < Input_MAX; i++) { //Read Pins and Set Input Array
    if (analogRead(Input_Analog_Pins[i]) > inputVoltageThreshold) Input_Analog[i] = true;
    else Input_Analog[i] = false;
  }


  //Process Control    ----------------------------------------------------------------

  //If Start Pressed + Stop NOT Pressed Turn On System Running
  if(Input_Analog[0] && Input_Analog[1]) Memory_bool[0] = true;
  
  //If Stop Pressed then System Running Set False
  if(!Input_Analog[0]) Memory_bool[0] = false;


  //Green Light = System Running
  Output_Digital[0] = Memory_bool[0];
  
  //Red Light != System Running
  Output_Digital[0] != Memory_bool[0];

  //End Process Control    ------------------------------------------------------------


  //Output Write    -------------------------------------------------------------------
  for(i = 0; i < Output_MAX; i++) { //Read input Pins
    if (Output_Digital[i]) digitalWrite(Output_Digital_Pins[i], HIGH);
    else digitalWrite(Output_Digital_Pins[i], LOW);
  }


  //Calc and Print Scantime    --------------------------------------------------------
  scantime_end = millis();
  
  Serial.print("Scantime: ");
  Serial.println(scantime_end - scantime_init);
  

  //Slowdown Code Speed ?!    --------------------------------------------------------
  //delay(1);
}
