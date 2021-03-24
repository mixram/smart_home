#define SN "OurSmartHome"
#define SV "1.0"

//My Arduino is both note and gateway (https://www.mysensors.org/about/network)
#define MY_NODE_ID 1
#define MY_GATEWAY_SERIAL

#include <Arduino.h>
#include <MySensors.h>

/*INPUT*/
const int BTN_HALLWAY_PIN_I = 41;   //for button near the flat door
const int BTN_HALL_PIN_I = 37;      //for button right of the hallway door
const int BTN_BATHROOM1_PIN_I = 33; //for button left of the bathroom door and button in the bathroom
const int BTN_BATHROOM2_PIN_I = 22; //for button in the bathroom
const int BTN_KITCHEN_PIN_I = 26;   //for button near the kitchen
const int BTN_BEDROOM_T_PIN_I = 30; //for button left of the bedroom door
const int BTN_BEDROOM_M_PIN_I = 34; //for button left of the bedroom door
const int BTN_BEDROOM_B_PIN_I = 38; //for button left of the bedroom door
const int BTN_SCONCE1_PIN_I = 42;   //for button on the brace_1
const int BTN_SCONCE2_PIN_I = 46;   //for button on the brace_2

/*OUTPUT*/
//hallway relay
const int HALLWAY_LIGHT_RELAY_PIN_O = A3;     //for light in the hallway
const int BATHROOM_FAN_RELAY_PIN_O = A5;      //for fan in the bathroom
const int BATHROOM_LIGHT_RELAY_PIN_O = A4;    //for light in the bathroom
const int KITCHEN_MAIN_RELAY_PIN_O = A0;      //for main light in the kitchen
const int KITCHEN_ADD_RELAY_PIN_O = A1;       //for additional light in the kitchen
const int KITCHEN_BACKLIGHT_RELAY_PIN_O = A2; //for backlight in the kitchen
//hall relay
const int HALL_LIGHT_RELAY_PIN_O = 45;    //for light in the hall
const int DINING_LIGHT_RELAY_PIN_O = 47;  //for dining zone light
const int BEDROOM_LIGHT_RELAY_PIN_O = 53; //for light in the bedroom
const int SCONCE1_LIGHT_RELAY_PIN_O = 49; //for sconce_1 light
const int SCONCE2_LIGHT_RELAY_PIN_O = 51; //for sconce_2 light

/*SENSORS_ACTUATORS*/
//hallway
const int CHILD_ACTUATOR_ID_HALLWAY_LIGHT = HALLWAY_LIGHT_RELAY_PIN_O;         //register light in the hallway in HA
const int CHILD_ACTUATOR_ID_BATHROOM_FAN = BATHROOM_FAN_RELAY_PIN_O;           //register fan in the bathroom in HA
const int CHILD_ACTUATOR_ID_BATHROOM_LIGHT = BATHROOM_LIGHT_RELAY_PIN_O;       //register light in the bathroom in HA
const int CHILD_ACTUATOR_ID_KITCHEN_MAIN = KITCHEN_MAIN_RELAY_PIN_O;           //register main light in the kitchen in HA
const int CHILD_ACTUATOR_ID_KITCHEN_ADD = KITCHEN_ADD_RELAY_PIN_O;             //register additional light in the kitchen in HA
const int CHILD_ACTUATOR_ID_KITCHEN_BACKLIGHT = KITCHEN_BACKLIGHT_RELAY_PIN_O; //register backlight in the kitchen in HA
//hall
const int CHILD_ACTUATOR_ID_HALL_LIGHT = HALL_LIGHT_RELAY_PIN_O;       //register light in the hall in HA
const int CHILD_ACTUATOR_ID_DINING_LIGHT = DINING_LIGHT_RELAY_PIN_O;   //register dining zone light in HA
const int CHILD_ACTUATOR_ID_BEDROOM_LIGHT = BEDROOM_LIGHT_RELAY_PIN_O; //register light in the bedroom in HA
const int CHILD_ACTUATOR_ID_SCONCE1_LIGHT = SCONCE1_LIGHT_RELAY_PIN_O; //register sconce_1 light in HA
const int CHILD_ACTUATOR_ID_SCONCE2_LIGHT = SCONCE2_LIGHT_RELAY_PIN_O; //register sconce_2 light in HA
MyMessage msgHallwayLight(CHILD_ACTUATOR_ID_HALLWAY_LIGHT, V_STATUS);
MyMessage msgBathroomFan(CHILD_ACTUATOR_ID_BATHROOM_FAN, V_STATUS);
MyMessage msgBathroomLight(CHILD_ACTUATOR_ID_BATHROOM_LIGHT, V_STATUS);
MyMessage msgKitchenMainLight(CHILD_ACTUATOR_ID_KITCHEN_MAIN, V_STATUS);
MyMessage msgKitchenAddLight(CHILD_ACTUATOR_ID_KITCHEN_ADD, V_STATUS);
MyMessage msgKitchenBackLight(CHILD_ACTUATOR_ID_KITCHEN_BACKLIGHT, V_STATUS);
MyMessage msgHallLight(CHILD_ACTUATOR_ID_HALL_LIGHT, V_STATUS);
MyMessage msgDinningLight(CHILD_ACTUATOR_ID_DINING_LIGHT, V_STATUS);
MyMessage msgBedroomLight(CHILD_ACTUATOR_ID_BEDROOM_LIGHT, V_STATUS);
MyMessage msgSconce1Light(CHILD_ACTUATOR_ID_SCONCE1_LIGHT, V_STATUS);
MyMessage msgSconce1Light(CHILD_ACTUATOR_ID_SCONCE2_LIGHT, V_STATUS);

/*INPUTS STATES*/
bool hallwayLastState = LOW;
bool hallwayCurrState = LOW;
bool hallLastState = LOW;
bool hallCurrState = LOW;
bool bathroom1LastState = LOW;
bool bathroom1CurrState = LOW;
bool bathroom2LastState = LOW;
bool bathroom2CurrState = LOW;
bool kitchenLastState = LOW;
bool kitchenCurrState = LOW;
bool bedroomTLastState = LOW;
bool bedroomTCurrState = LOW;
bool bedroomMLastState = LOW;
bool bedroomMCurrState = LOW;
bool bedroomBLastState = LOW;
bool bedroomBCurrState = LOW;
bool sconce1LastState = LOW;
bool sconce1CurrState = LOW;
bool sconce2LastState = LOW;
bool sconce2CurrState = LOW;

/*OUTPUTS STATES*/
bool hallwayLightIsOn = true;
bool hallLightIsOn = false; //because the light is engaged in start script
bool bathroomLightIsOn = true;
bool bathroomFanIsOn = true;
bool kitchenMainLightIsOn = true;
bool kitchenAddLightIsOn = true;
bool kitchenBackLightIsOn = true;
bool diningLightIsOn = true;
bool bedroomLightIsOn = true;
bool sconce1IsOn = true;
bool sconce2IsOn = true;

/*OTHER*/
bool printAccepted = false;
int connectAttemptscounter = 0;
const int ACCEPTED_CONNECTION_ATTEMPTS = 20;
bool initialValueSent = false;

void before()
{
  //setting input pins
  pinMode(BTN_HALLWAY_PIN_I, INPUT);
  pinMode(BTN_HALL_PIN_I, INPUT);
  pinMode(BTN_BATHROOM1_PIN_I, INPUT);
  pinMode(BTN_BATHROOM2_PIN_I, INPUT);
  pinMode(BTN_KITCHEN_PIN_I, INPUT);
  pinMode(BTN_BEDROOM_T_PIN_I, INPUT);
  pinMode(BTN_BEDROOM_M_PIN_I, INPUT);
  pinMode(BTN_BEDROOM_B_PIN_I, INPUT);
  pinMode(BTN_SCONCE1_PIN_I, INPUT);
  pinMode(BTN_SCONCE2_PIN_I, INPUT);

  //setting output pins
  pinMode(HALLWAY_LIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(HALL_LIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(BATHROOM_LIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(BATHROOM_FAN_RELAY_PIN_O, OUTPUT);
  pinMode(KITCHEN_MAIN_RELAY_PIN_O, OUTPUT);
  pinMode(KITCHEN_ADD_RELAY_PIN_O, OUTPUT);
  pinMode(KITCHEN_BACKLIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(DINING_LIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(BEDROOM_LIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(SCONCE1_LIGHT_RELAY_PIN_O, OUTPUT);
  pinMode(SCONCE2_LIGHT_RELAY_PIN_O, OUTPUT);

  //initial state
  digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(HALL_LIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(BATHROOM_LIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(BATHROOM_FAN_RELAY_PIN_O, HIGH);
  digitalWrite(KITCHEN_MAIN_RELAY_PIN_O, HIGH);
  digitalWrite(KITCHEN_ADD_RELAY_PIN_O, HIGH);
  digitalWrite(KITCHEN_BACKLIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(DINING_LIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(BEDROOM_LIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(SCONCE1_LIGHT_RELAY_PIN_O, HIGH);
  digitalWrite(SCONCE2_LIGHT_RELAY_PIN_O, HIGH);

  //switch ON the devices
  digitalWrite(HALL_LIGHT_RELAY_PIN_O, LOW);
}

void setup()
{
  Serial.begin(9600);
  while (Serial.available())
    ;
}

void presentation()
{
  sendSketchInfo(SN, SV);
  present(CHILD_ACTUATOR_ID_HALLWAY_LIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_BATHROOM_FAN, S_BINARY);
  present(CHILD_ACTUATOR_ID_BATHROOM_LIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_KITCHEN_MAIN, S_BINARY);
  present(CHILD_ACTUATOR_ID_KITCHEN_ADD, S_BINARY);
  present(CHILD_ACTUATOR_ID_KITCHEN_BACKLIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_HALL_LIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_DINING_LIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_BEDROOM_LIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_SCONCE1_LIGHT, S_BINARY);
  present(CHILD_ACTUATOR_ID_SCONCE2_LIGHT, S_BINARY);
}

void loop()
{
  if (!initialValueSent && connectAttemptscounter < ACCEPTED_CONNECTION_ATTEMPTS)
  {
    print("Sending initial value");
    send(msgHallwayLight.set(hallwayLightIsOn));
    send(msgBathroomFan.set(hallLightIsOn));
    send(msgBathroomLight.set(bathroomLightIsOn));
    send(msgKitchenMainLight.set(bathroomFanIsOn));
    send(msgKitchenAddLight.set(kitchenMainLightIsOn));
    send(msgKitchenBackLight.set(kitchenAddLightIsOn));
    send(msgHallLight.set(kitchenBackLightIsOn));
    send(msgDinningLight.set(diningLightIsOn));
    send(msgBedroomLight.set(bedroomLightIsOn));
    send(msgSconce1Light.set(sconce1IsOn));
    send(msgSconce1Light.set(sconce2IsOn));

    print("Requesting initial value from controller");
    request(CHILD_ACTUATOR_ID_HALLWAY_LIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_BATHROOM_FAN, V_STATUS);
    request(CHILD_ACTUATOR_ID_BATHROOM_LIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_KITCHEN_MAIN, V_STATUS);
    request(CHILD_ACTUATOR_ID_KITCHEN_ADD, V_STATUS);
    request(CHILD_ACTUATOR_ID_KITCHEN_BACKLIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_HALL_LIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_DINING_LIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_BEDROOM_LIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_SCONCE1_LIGHT, V_STATUS);
    request(CHILD_ACTUATOR_ID_SCONCE2_LIGHT, V_STATUS);

    connectAttemptscounter++;
    print("Connection attempt " + String(connectAttemptscounter) + " out of " + String(ACCEPTED_CONNECTION_ATTEMPTS));

    wait(2000, C_SET, V_STATUS);
  }

  //debounced value of button (pressed or released)
  hallwayCurrState = debounce(hallwayLastState, BTN_HALLWAY_PIN_I);
  hallCurrState = debounce(hallLastState, BTN_HALL_PIN_I);
  bathroom1CurrState = debounce(bathroom1LastState, BTN_BATHROOM1_PIN_I);
  bathroom2CurrState = debounce(bathroom2LastState, BTN_BATHROOM2_PIN_I);
  kitchenCurrState = debounce(kitchenLastState, BTN_KITCHEN_PIN_I);
  bedroomTCurrState = debounce(bedroomTLastState, BTN_BEDROOM_T_PIN_I);
  bedroomMCurrState = debounce(bedroomMLastState, BTN_BEDROOM_M_PIN_I);
  bedroomBCurrState = debounce(bedroomBLastState, BTN_BEDROOM_B_PIN_I);
  sconce1CurrState = debounce(sconce1LastState, BTN_SCONCE1_PIN_I);
  sconce2CurrState = debounce(sconce2LastState, BTN_SCONCE2_PIN_I);

  /*HALLWAY+HALL*/
  if (hallwayLastState == LOW && hallwayCurrState == HIGH)
  {
    print(String(BTN_HALLWAY_PIN_I) + " is pressed.");

    delay(400);

    hallwayCurrState = debounce(hallwayLastState, BTN_HALLWAY_PIN_I);
    if (hallwayCurrState == HIGH)
    {
      print(String(BTN_HALLWAY_PIN_I) + " is still pressed!");

      if (hallwayLightIsOn == false || hallLightIsOn == false)
      {
        hallwayLightIsOn = true;
        hallLightIsOn = true;
      }
      else
      {
        hallwayLightIsOn = false;
        hallLightIsOn = false;
      }
    }
    else
    {
      hallwayLightIsOn = !hallwayLightIsOn;
    }

    send(msgHallwayLight.set(hallwayLightIsOn), true);
    send(msgHallLight.set(hallLightIsOn), true);
  }

  /*HALL+DINNING*/
  if (hallLastState == LOW && hallCurrState == HIGH)
  {
    print(String(BTN_HALL_PIN_I) + " is pressed.");

    delay(400);

    hallCurrState = debounce(hallLastState, BTN_HALL_PIN_I);
    if (hallCurrState == HIGH)
    {
      print(String(BTN_HALL_PIN_I) + " is still pressed!");

      diningLightIsOn = !diningLightIsOn;
      print("diningLightIsOn=" + String(diningLightIsOn));
    }
    else
    {
      hallLightIsOn = !hallLightIsOn;
      print("hallLightIsOn=" + String(hallLightIsOn));
    }

    send(msgDinningLight.set(diningLightIsOn), true);
    send(msgHallLight.set(hallLightIsOn), true);
  }

  /*BATHROOM*/
  //botton1
  if (bathroom1LastState == LOW && bathroom1CurrState == HIGH)
  {
    print("BTN_BATHROOM1_PIN_I is pressed.");

    delay(400);

    bathroom1CurrState = debounce(bathroom1LastState, BTN_BATHROOM1_PIN_I);
    if (bathroom1CurrState == HIGH)
    {
      Serial.println("BTN_BATHROOM1_PIN_I is still pressed!");

      bathroomFanIsOn = !bathroomFanIsOn;
      print("bathroomFanIsOn=" + String(bathroomFanIsOn));
    }
    else
    {
      bathroomLightIsOn = !bathroomLightIsOn;
      print("bathroomLightIsOn=" + String(bathroomLightIsOn));
    }
  }
  //botton2
  if (bathroom2LastState == LOW && bathroom2CurrState == HIGH)
  {
    print("BTN_BATHROOM2_PIN_I is pressed.");

    delay(400);

    bathroom2CurrState = debounce(bathroom2LastState, BTN_BATHROOM2_PIN_I);
    if (bathroom2CurrState == HIGH)
    {
      print("BTN_BATHROOM2_PIN_I is still pressed!");

      bathroomFanIsOn = !bathroomFanIsOn;
    }
    else
    {
      bathroomLightIsOn = !bathroomLightIsOn;
    }
  }

  /*KITCHEN*/
  //if now pressed and previously was released - I may do needed logic.
  if (kitchenLastState == LOW && kitchenCurrState == HIGH)
  {
    print("BTN_KITCHEN_PIN_I is pressed.");

    //wait to check if button still pressed
    delay(400);

    kitchenCurrState = debounce(kitchenLastState, BTN_KITCHEN_PIN_I);
    if (kitchenCurrState == HIGH)
    {
      print("BTN_KITCHEN_PIN_I is still pressed!");

      //if we are here - it means "long-press" logic should be switched on/off
      kitchenAddLightIsOn = !kitchenAddLightIsOn;

      //wait to check if button still pressed
      delay(400);

      kitchenCurrState = debounce(kitchenLastState, BTN_KITCHEN_PIN_I);
      if (kitchenCurrState == HIGH)
      {
        print("BTN_KITCHEN_PIN_I is STILL pressed!");

        //if we are here - it means "long-long-press" logic should be switched on/off
        kitchenAddLightIsOn = !kitchenAddLightIsOn;
        kitchenBackLightIsOn = !kitchenBackLightIsOn;
      }
    }
    else
    {
      //if we are here - it means "short-press" logic should be switched on/off
      kitchenMainLightIsOn = !kitchenMainLightIsOn;
      print("kitchenMainLightIsOn=" + String(kitchenMainLightIsOn));
    }
  }

  /*BEDROOM+SCONCES*/
  //buttonT
  if (bedroomTLastState == LOW && bedroomTCurrState == HIGH)
  {
    print("BTN_BEDROOM_T_PIN_I is pressed.");

    delay(400);

    bedroomTCurrState = debounce(bedroomTLastState, BTN_BEDROOM_T_PIN_I);
    if (bedroomTCurrState == HIGH)
    {
      print("BTN_BEDROOM_T_PIN_I is still pressed!");

      if (sconce1IsOn == false || sconce2IsOn == false)
      {
        sconce1IsOn = true;
        sconce2IsOn = true;
      }
      else
      {
        sconce1IsOn = false;
        sconce2IsOn = false;
      }
    }
    else
    {
      bedroomLightIsOn = !bedroomLightIsOn;
    }
  }
  //buttonM
  if (bedroomMLastState == LOW && bedroomMCurrState == HIGH)
  {
    print("BTN_BEDROOM_M_PIN_I is pressed.");

    delay(400);

    bedroomMCurrState = debounce(bedroomMLastState, BTN_BEDROOM_M_PIN_I);
    if (bedroomMCurrState == HIGH)
    {
      print("BTN_BEDROOM_M_PIN_I is still pressed!");

      diningLightIsOn = !diningLightIsOn;
    }
    else
    {
      hallLightIsOn = !hallLightIsOn;
    }
  }
  //buttonB
  if (bedroomBLastState == LOW && bedroomBCurrState == HIGH)
  {
    print("BTN_BEDROOM_B_PIN_I is pressed.");

    delay(400);

    bedroomBCurrState = debounce(bedroomBLastState, BTN_BEDROOM_B_PIN_I);
    if (bedroomBCurrState == HIGH)
    {
      print("BTN_BEDROOM_B_PIN_I is still pressed!");

      hallwayLightIsOn = true;
      hallLightIsOn = true;
      bathroomLightIsOn = true;
      bathroomFanIsOn = true;
      kitchenMainLightIsOn = true;
      kitchenAddLightIsOn = true;
      kitchenBackLightIsOn = true;
      diningLightIsOn = true;
    }
    else
    {
      hallwayLightIsOn = !hallwayLightIsOn;
    }
  }

  /*SCONCE1+BEDROOM*/
  if (sconce1LastState == LOW && sconce1CurrState == HIGH)
  {
    Serial.println("BTN_SCONCE1_PIN_I is pressed.");

    delay(400);

    sconce1CurrState = debounce(sconce1LastState, BTN_SCONCE1_PIN_I);
    if (sconce1CurrState == HIGH)
    {
      print("BTN_SCONCE1_PIN_I is still pressed!");

      bedroomLightIsOn = !bedroomLightIsOn;
    }
    else
    {
      sconce1IsOn = !sconce1IsOn;
    }
  }

  /*SCONCE2+BEDROOM*/
  if (sconce2LastState == LOW && sconce2CurrState == HIGH)
  {
    print("BTN_SCONCE2_PIN_I is pressed.");

    delay(400);

    sconce2CurrState = debounce(sconce2LastState, BTN_SCONCE2_PIN_I);
    if (sconce2CurrState == HIGH)
    {
      print("BTN_SCONCE2_PIN_I is still pressed!");

      bedroomLightIsOn = !bedroomLightIsOn;
    }
    else
    {
      sconce2IsOn = !sconce2IsOn;
    }
  }

  //set HALLWAY_LIGHT_RELAY_PIN_O state
  digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, hallwayLightIsOn);
  //set HALL_LIGHT_RELAY_PIN_O state
  digitalWrite(HALL_LIGHT_RELAY_PIN_O, hallLightIsOn);
  //set BATHROOM_LIGHT_RELAY_PIN_O state
  digitalWrite(BATHROOM_LIGHT_RELAY_PIN_O, bathroomLightIsOn);
  //set BATHROOM_FAN_RELAY_PIN_O state
  digitalWrite(BATHROOM_FAN_RELAY_PIN_O, bathroomFanIsOn);
  //set KITCHEN_MAIN_RELAY_PIN_O state
  digitalWrite(KITCHEN_MAIN_RELAY_PIN_O, kitchenMainLightIsOn);
  //set KITCHEN_ADD_RELAY_PIN_O state
  digitalWrite(KITCHEN_ADD_RELAY_PIN_O, kitchenAddLightIsOn);
  //set KITCHEN_BACKLIGHT_RELAY_PIN_O state
  digitalWrite(KITCHEN_BACKLIGHT_RELAY_PIN_O, kitchenBackLightIsOn);
  //set DINING_LIGHT_RELAY_PIN_O state
  digitalWrite(DINING_LIGHT_RELAY_PIN_O, diningLightIsOn);
  //set BEDROOM_LIGHT_RELAY_PIN_O state
  digitalWrite(BEDROOM_LIGHT_RELAY_PIN_O, bedroomLightIsOn);
  //set SCONCE1_LIGHT_RELAY_PIN_O state
  digitalWrite(SCONCE1_LIGHT_RELAY_PIN_O, sconce1IsOn);
  //set SCONCE2_LIGHT_RELAY_PIN_O state
  digitalWrite(SCONCE2_LIGHT_RELAY_PIN_O, sconce2IsOn);

  //save current button state to use on the next loop
  hallwayLastState = hallwayCurrState;
  hallLastState = hallCurrState;
  bathroom1LastState = bathroom1CurrState;
  bathroom2LastState = bathroom1CurrState;
  kitchenLastState = kitchenCurrState;
  bedroomTLastState = bedroomTCurrState;
  bedroomMLastState = bedroomMCurrState;
  bedroomBLastState = bedroomBCurrState;
  sconce1LastState = sconce1CurrState;
  sconce2LastState = sconce2CurrState;
}

void print(String text)
{
  if (printAccepted)
  {
    Serial.println(text);
  }
}

bool debounce(bool last,
              int btn)
{
  bool current = digitalRead(btn);
  if (last != current)
  {
    delay(5);
    current = digitalRead(btn);

    print(String("Button ") + String(btn) + String(" new state: ") + String(current) + ".");
  }

  return current;
}