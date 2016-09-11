 
/*
 * This sketch implements a 3-button text entry device.
 */


#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

// Buttom State (0==Wait,1=Listen,2=WaitForRelease)
int state = 0;
int inputOne = 0;
int inputTwo = 0;
int inputThree = 0;

int valueOne = 0;
int valueTwo = 0;
int valueThree = 0;


// This routine runs only once upon reset
void setup() {
  RGB.control(true);
  Serial.begin(9600);
}

// This routine loops forever
void loop() {
  /*
  RGB.color(255, 0, 0);                 // set LED to RED
  delay(500);
  
  RGB.color(0, 255 ,0);                 // set LED to GREEN
  delay(500);
  
  RGB.color(0, 0,255);                 // set LED to BLUE
  delay(500);
  */

  readInputs();

  // 
  if( inputOne > 3500 ){
    valueOne = 0;
  }
  else if( inputOne > 1800 ){
    valueOne = 1;
  }
  else if( inputOne > 800 ){
    valueOne = 2;
  }
  else{
    valueOne = -1;
  }
  // 
  if( inputTwo > 3500 ){
    valueTwo = 0;
  }
  else if( inputTwo > 1800 ){
    valueTwo = 1;
  }
  else if( inputTwo > 800 ){
    valueTwo = 2;
  }
  else{
    valueTwo = -1;
  }
  // 
  if( inputThree > 3500 ){
    valueThree = 0;
  }
  else if( inputThree > 1800 ){
    valueThree = 1;
  }
  else if( inputThree > 800 ){
    valueThree = 2;
  }
  else{
    valueThree = -1;
  }
  
  if( state==0 ){

    Serial.print('[');
    Serial.print(valueOne);
    Serial.print(',');
    Serial.print(valueTwo);
    Serial.print(',');
    Serial.print(valueThree);
    Serial.println(']');

    if( valueOne >= 0 && valueTwo >= 0 && valueThree >= 0 ){
      state = 1;
    }
    /*
    RGB.color(127*valueOne, 127*valueTwo, 127*valueThree); 
      
    int inputValue = valueOne + valueTwo*3 + valueThree*9;
    char c;
    if( inputValue == 26 ){
      c = ' ';
    }else{
      c = 'a' + inputValue;
    }
    Serial.println( c );
    */
    
  }
  else if( state==1 ){
    if( valueOne == -1 || valueTwo == -1 || valueThree == -1 ){
      state = 0;
    }
  }

  delay(200);
}

void readInputs(){
  // Read the input on analog pins 0, 1, 2:
  inputOne = analogRead(A0);
  inputTwo = analogRead(A1);
  inputThree = analogRead(A2);
  delay(1);        // delay in between reads for stability

  /*
  // print out the value you read:
  Serial.print(inputOne);
  Serial.print(' ');
  Serial.print(inputTwo);
  Serial.print(' ');
  Serial.println(inputThree);
  */
}

