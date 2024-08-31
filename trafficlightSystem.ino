/* Some context for someone looking in the code:
There is 12 leds for all the car traffic lights, as well 4 leds for all the pedestrians traffic lights. They're arranged by cardinal
points, so they're in 4 groups of 3 leds. Each group is facing an specific cardinal point. An example is led 13, 12 and 11, who are 
facing NORTH because the cars in that line are going to the NORTH. In the other way, leds on pin 10, 9 and 8 are facing EAST because 
the cars in that line are going to the EAST, and so. 

EVERY traffic light depends on the main one, who is facing NORTH (pins 13, 12 and 11). So if the main one changes his status, every
one changes too. An example is: Traffic light facing NORTH is on green light (status = true), the ones facing SOUTH also changes to
true, turning on the green led, but the ones facing EAST and WEST turns red (status = false), and so the pedestrians ones. 

In the array of pins, the order goes like this:
- 13, 12, 11 = red, yellow, green pins for the NORTH facing traffic light.
- 10, 9, 8 = same colors in the same order pins for the EAST facing traffic light.
- 7, 6, 5 = same colors in the same order for the SOUTH facing traffic light.
- 4, 3, 2 = same colors in the same order for the WEST facing traffic light.

*/
// Initialize the variables for the entire code.
bool firstExecute = true;
bool tlNorthStatus = true, tlEastStatus = false, tlSouthStatus = false, tlWestStatus = false;
bool pNorthStatus = false, pEastStatus = false;

int tlNorth[] = {11, 12, 13};
int tlEast[] = {8, 9, 10};
int tlSouth[] = {5, 6, 7};
int tlWest[] = {2, 3, 4};

int pNorth[] = {A5, A4};
int pEast[] = {A3, A2};

int secondsOnRed = 10000, secondsOnYellow = 2000, secondsOnGreen = 11000, secondsOfSecurity = 1500;


// Declare functions where we setup the environment.
void environmentSetup(){
  if (firstExecute){
    Serial.println("First execute. Initializing environment...");
    allLedsOff();
    ledOn(tlNorth[0]);
    ledOn(tlSouth[0]);
    ledOn(tlEast[2]);
    ledOn(tlWest[2]);
    ledOn(pNorth[0]);
    ledOn(pEast[1]);
    Serial.println("Done.");
    firstExecute = false;
  }
}

void allLedsOff(){
  for (int i=0; i < 3; i++){
    ledOff(tlNorth[i]);
    ledOff(tlEast[i]);
    ledOff(tlSouth[i]);
    ledOff(tlWest[i]);
    }
  for (int i = 0; i < 2; i++){  
    ledOff(pNorth[i]);
    ledOff(pEast[i]);
  }
}

void setup()
{
  for (int i = 0; i < 3; i++){
    pinMode(tlNorth[i], OUTPUT);
    pinMode(tlEast[i], OUTPUT);
    pinMode(tlSouth[i], OUTPUT);
    pinMode(tlWest[i], OUTPUT);
  }

  for (int i = 0; i < 2; i++){
    pinMode(pNorth[i], OUTPUT);
    pinMode(pEast[i], OUTPUT);
  }
  Serial.begin(9600);
}

// Beginning of the main process.
void loop(){
  environmentSetup();
  trafficLightLoop();
}

// functions to turn on an off the selected leds.
void ledOn(int pinColor){
  Serial.print("Turning on led on pin: ");
  Serial.println(pinColor);
  digitalWrite(pinColor, HIGH);

}

void ledOff(int pinColor){
  Serial.print("Turning off led on pin: ");
  Serial.println(pinColor);
  digitalWrite(pinColor, LOW);
}

/* void ledLoop(int pin){
  Serial.print("Initializing loop on pin: ");
  Serial.println(pin);
  delay(3000);
  ledOn(pin);
  ledOff(pin);
  Serial.println("Done.");
}
*/

void trafficLightLoop(){
  verifyMainTrafficLightStatus();
  trafficLightController();
  checkCurrentStatus();
}

void verifyMainTrafficLightStatus(){
  if (tlNorthStatus){
    updateTrafficLightsStatus(true, true, false, false, true, false);
  } else {
    updateTrafficLightsStatus(false, false, true, true, false, true);
  }
  
}



void trafficLightController(){
  if (tlNorthStatus) {
    delay(secondsOnGreen);
    ledOff(tlNorth[0]);
    ledOff(tlSouth[0]);
    ledOn(tlNorth[1]);
    ledOn(tlSouth[1]);
    delay(secondsOnYellow);
    ledOff(tlNorth[1]);
    ledOff(tlSouth[1]);
    ledOn(tlNorth[2]);
    ledOn(tlSouth[2]);
    delay(secondsOfSecurity);
    ledOff(tlEast[2]);
    ledOff(tlWest[2]);
    ledOn(tlEast[0]);
    ledOn(tlWest[0]);
    ledOff(pNorth[0]);
    ledOff(pEast[1]);
    ledOn(pNorth[1]);
    ledOn(pEast[0]);
    updateTrafficLightsStatus(false, false, true, true, false, true);
  } else {
    delay(secondsOnGreen);
    ledOff(tlEast[0]);
    ledOff(tlWest[0]);
    ledOn(tlEast[1]);
    ledOn(tlWest[1]);
    delay(secondsOnYellow);
    ledOff(tlEast[1]);
    ledOff(tlWest[1]);
    ledOn(tlEast[2]);
    ledOn(tlWest[2]);
    delay(secondsOfSecurity);
    ledOff(tlNorth[2]);
    ledOff(tlSouth[2]);
    ledOn(tlNorth[0]);
    ledOn(tlSouth[0]);
    ledOff(pNorth[1]);
    ledOff(pEast[0]);
    ledOn(pNorth[0]);
    ledOn(pEast[1]);
    updateTrafficLightsStatus(true, true, false, false, true, false);
  }
}

// The next two functions are only for test purposes. 
void updateTrafficLightsStatus(bool tlNorth, bool tlSouth, bool tlEast, bool tlWest, bool pNorth, bool pEast){
  tlNorthStatus = tlNorth;
  tlSouthStatus = tlSouth;
  tlEastStatus = tlEast;
  tlWestStatus = tlWest;
  pNorthStatus = pNorth;
  pEastStatus = pEast;
}


void checkCurrentStatus(){
  Serial.println("----------------");
  Serial.println("Updated status: ");
  Serial.print("North: ");
  Serial.println(tlNorthStatus);
  Serial.print("East: ");
  Serial.println(tlEastStatus);
  Serial.print("South: ");
  Serial.println(tlSouthStatus);
  Serial.print("West: ");
  Serial.println(tlWestStatus);
  Serial.print("Pedestrian North: ");
  Serial.println(pNorthStatus);
  Serial.print("Pedestrian East: ");
  Serial.println(pEastStatus);
}



