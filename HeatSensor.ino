const int sensorPin = A0;   // Pin for temp sensor
float baselineTemp;         // FPV to store base temperature
const int greenLEDPin = 9;  // Pin # for green LED (unused)
const int blueLEDPin = 10;  // Pin # for blue LED
const int redLEDPin = 11;   // Pin # for red LED
int initialReading = 0;     // Counter to see when queue is full

float rollingAvg[10];       // Array used to find normalized value

int redValue = 0;           // Stores value passed to red LED
int greenValue = 0;         // Stores value passed to green LED
int blueValue = 0;          // Stores value passed to blue LED

void setup() {
  Serial.begin(9600);       // open a serial port
  
  // Voltage converted to temperature at runtime
  float sensorValue = analogRead(sensorPin);
  baselineTemp = (((sensorValue/1024)*5)-.5)*100;

  // Set LED pins as outputs
  pinMode(greenLEDPin,OUTPUT); // Not used
  pinMode(redLEDPin,OUTPUT); 
  pinMode(blueLEDPin,OUTPUT);

  // Turn on the blue LED and pass it a value of 255
  analogWrite(blueLEDPin, 255);
} // setup

void loop() {
  // Analog-to-digital converter value
  float sensorValue = analogRead(sensorPin);
  // ADC value/1024 * 5 = voltage
  float voltage = (sensorValue/1024) * 5;
  // Find the temperature from the voltage
  float temperature = (voltage -.5) * 100;
  // Var which will store the rolling average of temperatures
  float normalizedValue;
  // Var which will store the upper bound temperature which
  // will read "warm"
  float upperBound = 0; 
  // Var which will hold the 0-255 equivalent of the
  // difference in temperatures 
  float conversionValue;
  
  // Normalized value will become the average of the
  // temperatures in the queue
  normalizedValue = enqueue(temperature);

  // If the initial reading counter is too small, we increment
  if (initialReading < 11)
    initialReading += 1;
  // If the initial reading counter = 10, we assign the base
  // temperature becauase the queue has just been filled
  if (initialReading == 10){
    baselineTemp = normalizedValue;
  } // if

  // Amount the temperature is over baselineTemp
  float difference = normalizedValue - baselineTemp;

// =============================================================
  // The sensor is accurate to the tenths place so that means
  // that we have 10x values between the baselineTemp and the
  // upperBound value where x is the difference between them.
  // upperBound = baselineTemp + 6;  // Smoother
  // upperBound = baselineTemp + 5;    // Works in more rooms
  // upperBound = baselineTemp + 4;
  upperBound = baselineTemp + 3;
  
  // Assign conversionValue the value returned from conversion()
  // which is a function to convert temperature average to a 
  // value between 0 and 255
  conversionValue = conversion(difference);

  // Use the conversion value to determine the 0-255 value of the
  // red and blue LEDs
  redValue = 0 + conversionValue;
  blueValue = 255 - conversionValue;
  
  // Pass the values to the LEDs to make them light up to the
  // desired brightness
  analogWrite(blueLEDPin, blueValue);
  analogWrite(redLEDPin, redValue);
// =============================================================
  
  // Output the desired values from the variables whose values
  // have been computed above
  
  Serial.print("Baseline temperature: ");
  // If the queue has been filled...
  if (initialReading > 10){
    // ...print normally
    Serial.print(baselineTemp);
    Serial.println(" degrees celsius");
    Serial.print("Upper bound: ");
    Serial.print(upperBound);
    Serial.println(" degrees celsius");
  } // if
  // Otherwise, let the user know we haven't gather enough data
  else
    Serial.println("PROCESSING");
    
  // Skip a line between the baselineTemp and the outputs
  // required for the lab
  Serial.println();
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Normalized Sensor Value: ");
  // If the queue has been filled...
  if (initialReading > 10)
    // ...print normally
    Serial.println(normalizedValue);
  // Otherwise, let the user know we haven't gather enough data
  else
    Serial.println("PROCESSING");
  Serial.print("Volts: ");
  Serial.println(voltage);
  Serial.print("Degrees Celsius: ");
  Serial.println(temperature);
  Serial.print("Over Threshold ");
  Serial.println(difference);
  Serial.print("Red Value: ");
  Serial.println(redValue);
  Serial.print("Blue Value: ");
  Serial.println(blueValue);

  // Skip a line between Serial outputs
  Serial.println();

  // delay(1);
} // loop

// Enqueue will return the avg temperature gathered by the sensor
float enqueue(float temperature){
  int i;                  // Variable to store counter value
  float avg = 0;          // Variable to store the avg we will return

  dequeue();              // Dequeue the front value
  
  // Replace the last index's value with the newest temperature
  rollingAvg[9] = temperature;

  // Find the sum of every value in rollingAvg
  for(i = 0; i < 10; i++){
    if (rollingAvg[i] != 0)
      avg += rollingAvg[i];
  } // for

  // Divide the sum by the number of values in rollingAvg
  avg /= 10;

  // Return the avg
  return avg;
} // enqueue

// Dequeue will just remove the oldest data point and swap
// all values forward in the queue
void dequeue(){
  int i;        // Variable to store counter value

  // Swap all values forward in the queue
  for(i = 0; i < 9; i++){
    rollingAvg[i] = rollingAvg[i+1];
  } // for
} // dequeue

// Checks to see if the queue is empty
bool isEmpty(){
  bool isEmpty = false;   // Value we will return

  // If the first index is null...
  if (rollingAvg[0] == 0)
    // ...then the queue is empty
    isEmpty = true;

  // Return whether the queue is empty or not
  return isEmpty;
} // isEmpty

// conversion() is the function which finds a value to
// pass to the LEDs between 0-255 based on the
// normalized temperature which we found with the
// queue and the functions above
int conversion(float difference){
  
  // FPV to store the value we will return
  float conversionValue;
  
  // The conversionValue will be equal the difference
  // between the normalizedTemp and the baselineTemp
  // divided by 0.1. We do this because the sensor
  // reads temperature values accurate to the tenths
  // place. By doing this, we find how many 0.1
  // increments we are above the baselineTemp. Next,
  // we multiply that value by 4.25 or 5.1. Why?
  // Our upper bound is x degrees above the baseline
  // temperature, and since the sensor reads temperatures
  // out to the tenths place, it means that there are 10x
  // potential values between the baselineTemp and our
  // upper bound. When we divide 255 (possible values for
  // the LEDs) by 10x, we get a 4.25 or 5.1 depending on
  // which upperBound we decide to use. Therefore, for 
  // every 0.1 degree increment over the baselineTemp, 
  // we need to add 4.25 or 5.1 respectively to the 
  // value we will pass the LEDs.

  // For upperBound is +6
  // conversionValue = (difference / 0.1) * 4.25;
  // For upperBound is +5
  // conversionValue = (difference / 0.1) * 5.1;
  // For upperBound is +4
  // conversionValue = (difference / 0.1) * 6.38;
  // For upperBound is +3
  conversionValue = (difference / 0.1) * 8.5;
  
  // If the temperature is over the upper bound...
  if (conversionValue > 255)
    // ...we max out the LED value
    conversionValue = 255;
  // If the temperature is below the baselineTemp...
  if (conversionValue < 0)
    // ...we just pass the minimum value
    conversionValue = 0;

  // Return the conversionValue
  return conversionValue;
} // conversion
