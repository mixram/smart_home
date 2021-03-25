#define SN "OurSmartHome"
#define SV "1.0"

//My Arduino is both note and gateway (https://www.mysensors.org/about/network)
#define MY_NODE_ID 1
#define MY_DEBUG
#define MY_GATEWAY_SERIAL

//inverted logic for light management with 'minus' relay
#define LIGHT_IS_ON false
#define LIGHT_IS_OFF true
#define LIGHT_IS_ON_HA true
#define LIGHT_IS_OFF_HA false
#define BTN_IS_PRESSED HIGH
#define BTN_IS_RELEASED LOW

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
MyMessage msgSconce2Light(CHILD_ACTUATOR_ID_SCONCE2_LIGHT, V_STATUS);

/*INPUTS STATES*/
bool hallwayLastState = BTN_IS_RELEASED;
bool hallwayCurrState = BTN_IS_RELEASED;
bool hallLastState = BTN_IS_RELEASED;
bool hallCurrState = BTN_IS_RELEASED;
bool bathroom1LastState = BTN_IS_RELEASED;
bool bathroom1CurrState = BTN_IS_RELEASED;
bool bathroom2LastState = BTN_IS_RELEASED;
bool bathroom2CurrState = BTN_IS_RELEASED;
bool kitchenLastState = BTN_IS_RELEASED;
bool kitchenCurrState = BTN_IS_RELEASED;
bool bedroomTLastState = BTN_IS_RELEASED;
bool bedroomTCurrState = BTN_IS_RELEASED;
bool bedroomMLastState = BTN_IS_RELEASED;
bool bedroomMCurrState = BTN_IS_RELEASED;
bool bedroomBLastState = BTN_IS_RELEASED;
bool bedroomBCurrState = BTN_IS_RELEASED;
bool sconce1LastState = BTN_IS_RELEASED;
bool sconce1CurrState = BTN_IS_RELEASED;
bool sconce2LastState = BTN_IS_RELEASED;
bool sconce2CurrState = BTN_IS_RELEASED;

/*OUTPUTS STATES*/
bool hallwayLightIsOn = LIGHT_IS_OFF;
bool hallLightIsOn = LIGHT_IS_ON; //because the light is engaged in start script
bool bathroomLightIsOn = LIGHT_IS_OFF;
bool bathroomFanIsOn = LIGHT_IS_OFF;
bool kitchenMainLightIsOn = LIGHT_IS_OFF;
bool kitchenAddLightIsOn = LIGHT_IS_OFF;
bool kitchenBackLightIsOn = LIGHT_IS_OFF;
bool diningLightIsOn = LIGHT_IS_OFF;
bool bedroomLightIsOn = LIGHT_IS_OFF;
bool sconce1IsOn = LIGHT_IS_OFF;
bool sconce2IsOn = LIGHT_IS_OFF;

/*OTHER*/
bool printAccepted = true;
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
    digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(HALL_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(BATHROOM_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(BATHROOM_FAN_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(KITCHEN_MAIN_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(KITCHEN_ADD_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(KITCHEN_BACKLIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(DINING_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(BEDROOM_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(SCONCE1_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);
    digitalWrite(SCONCE2_LIGHT_RELAY_PIN_O, LIGHT_IS_OFF);

    //switch ON the devices
    digitalWrite(HALL_LIGHT_RELAY_PIN_O, LIGHT_IS_ON);
}

void setup()
{
    Serial.begin(9600);
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
        send(msgHallwayLight.set(calcStateForHA(hallwayLightIsOn)));
        send(msgBathroomFan.set(calcStateForHA(bathroomFanIsOn)));
        send(msgBathroomLight.set(calcStateForHA(bathroomLightIsOn)));
        send(msgKitchenMainLight.set(calcStateForHA(kitchenMainLightIsOn)));
        send(msgKitchenAddLight.set(calcStateForHA(kitchenAddLightIsOn)));
        send(msgKitchenBackLight.set(calcStateForHA(kitchenBackLightIsOn)));
        send(msgHallLight.set(calcStateForHA(hallLightIsOn)));
        send(msgDinningLight.set(calcStateForHA(diningLightIsOn)));
        send(msgBedroomLight.set(calcStateForHA(bedroomLightIsOn)));
        send(msgSconce1Light.set(calcStateForHA(sconce1IsOn)));
        send(msgSconce2Light.set(calcStateForHA(sconce2IsOn)));

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
    if (hallwayLastState == BTN_IS_RELEASED && hallwayCurrState == BTN_IS_PRESSED)
    {
        print("BTN_HALLWAY_PIN_I is pressed.");

        delay(400);

        hallwayCurrState = debounce(hallwayLastState, BTN_HALLWAY_PIN_I);
        if (hallwayCurrState == BTN_IS_PRESSED)
        {
            print("BTN_HALLWAY_PIN_I is still pressed!");

            if (hallwayLightIsOn == LIGHT_IS_ON || hallLightIsOn == LIGHT_IS_ON)
            {
                hallwayLightIsOn = LIGHT_IS_OFF;
                hallLightIsOn = LIGHT_IS_OFF;
                bathroomLightIsOn = LIGHT_IS_OFF;
                bathroomFanIsOn = LIGHT_IS_OFF;
                kitchenMainLightIsOn = LIGHT_IS_OFF;
                kitchenAddLightIsOn = LIGHT_IS_OFF;
                kitchenBackLightIsOn = LIGHT_IS_OFF;
                diningLightIsOn = LIGHT_IS_OFF;
            }
            else
            {
                hallwayLightIsOn = LIGHT_IS_ON;
                hallLightIsOn = LIGHT_IS_ON;
            }
        }
        else
        {
            hallwayLightIsOn = !hallwayLightIsOn;
        }

        send(msgHallwayLight.set(calcStateForHA(hallwayLightIsOn)), true);
        send(msgHallLight.set(calcStateForHA(hallLightIsOn)), true);
        send(msgBathroomLight.set(calcStateForHA(bathroomLightIsOn), true));
        send(msgBathroomFan.set(calcStateForHA(bathroomFanIsOn), true));
        send(msgKitchenMainLight.set(calcStateForHA(kitchenMainLightIsOn), true));
        send(msgKitchenAddLight.set(calcStateForHA(kitchenAddLightIsOn), true));
        send(msgKitchenBackLight.set(calcStateForHA(kitchenBackLightIsOn), true));
        send(msgDinningLight.set(calcStateForHA(diningLightIsOn), true));
    }

    /*HALL+DINNING*/
    if (hallLastState == BTN_IS_RELEASED && hallCurrState == BTN_IS_PRESSED)
    {
        print("BTN_HALL_PIN_I is pressed.");

        delay(400);

        hallCurrState = debounce(hallLastState, BTN_HALL_PIN_I);
        if (hallCurrState == BTN_IS_PRESSED)
        {
            print("BTN_HALL_PIN_I is still pressed!");

            diningLightIsOn = !diningLightIsOn;
            print("diningLightIsOn=" + String(diningLightIsOn));
        }
        else
        {
            hallLightIsOn = !hallLightIsOn;
            print("hallLightIsOn=" + String(hallLightIsOn));
        }

        send(msgDinningLight.set(calcStateForHA(diningLightIsOn)), true);
        send(msgHallLight.set(calcStateForHA(hallLightIsOn)), true);
    }

    /*BATHROOM*/
    //botton1
    if (bathroom1LastState == BTN_IS_RELEASED && bathroom1CurrState == BTN_IS_PRESSED)
    {
        print("BTN_BATHROOM1_PIN_I is pressed.");

        delay(400);

        bathroom1CurrState = debounce(bathroom1LastState, BTN_BATHROOM1_PIN_I);
        if (bathroom1CurrState == BTN_IS_PRESSED)
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

        send(msgBathroomFan.set(calcStateForHA(bathroomFanIsOn)), true);
        send(msgBathroomLight.set(calcStateForHA(bathroomLightIsOn)), true);
    }
    //botton2
    if (bathroom2LastState == BTN_IS_RELEASED && bathroom2CurrState == BTN_IS_PRESSED)
    {
        print("BTN_BATHROOM2_PIN_I is pressed.");

        delay(400);

        bathroom2CurrState = debounce(bathroom2LastState, BTN_BATHROOM2_PIN_I);
        if (bathroom2CurrState == BTN_IS_PRESSED)
        {
            print("BTN_BATHROOM2_PIN_I is still pressed!");

            bathroomFanIsOn = !bathroomFanIsOn;
        }
        else
        {
            bathroomLightIsOn = !bathroomLightIsOn;
        }

        send(msgBathroomFan.set(calcStateForHA(bathroomFanIsOn)), true);
        send(msgBathroomLight.set(calcStateForHA(bathroomLightIsOn)), true);
    }

    /*KITCHEN*/
    //if now pressed and previously was released - I may do needed logic.
    if (kitchenLastState == BTN_IS_RELEASED && kitchenCurrState == BTN_IS_PRESSED)
    {
        print("BTN_KITCHEN_PIN_I is pressed.");

        //wait to check if button still pressed
        delay(400);

        kitchenCurrState = debounce(kitchenLastState, BTN_KITCHEN_PIN_I);
        if (kitchenCurrState == BTN_IS_PRESSED)
        {
            print("BTN_KITCHEN_PIN_I is still pressed!");

            //if we are here - it means "long-press" logic should be switched on/off
            kitchenAddLightIsOn = !kitchenAddLightIsOn;

            //wait to check if button still pressed
            delay(400);

            kitchenCurrState = debounce(kitchenLastState, BTN_KITCHEN_PIN_I);
            if (kitchenCurrState == BTN_IS_PRESSED)
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

        send(msgKitchenAddLight.set(calcStateForHA(kitchenAddLightIsOn)), true);
        send(msgKitchenBackLight.set(calcStateForHA(kitchenBackLightIsOn)), true);
        send(msgKitchenMainLight.set(calcStateForHA(kitchenMainLightIsOn)), true);
    }

    /*BEDROOM+SCONCES*/
    //buttonT
    if (bedroomTLastState == BTN_IS_RELEASED && bedroomTCurrState == BTN_IS_PRESSED)
    {
        print("BTN_BEDROOM_T_PIN_I is pressed.");

        delay(400);

        bedroomTCurrState = debounce(bedroomTLastState, BTN_BEDROOM_T_PIN_I);
        if (bedroomTCurrState == BTN_IS_PRESSED)
        {
            print("BTN_BEDROOM_T_PIN_I is still pressed!");

            if (sconce1IsOn == LIGHT_IS_ON || sconce2IsOn == LIGHT_IS_ON)
            {
                sconce1IsOn = LIGHT_IS_OFF;
                sconce2IsOn = LIGHT_IS_OFF;
            }
            else
            {
                sconce1IsOn = LIGHT_IS_ON;
                sconce2IsOn = LIGHT_IS_ON;
            }
        }
        else
        {
            bedroomLightIsOn = !bedroomLightIsOn;
        }

        send(msgSconce1Light.set(calcStateForHA(sconce1IsOn)), true);
        send(msgSconce2Light.set(calcStateForHA(sconce2IsOn)), true);
        send(msgBedroomLight.set(calcStateForHA(bedroomLightIsOn)), true);
    }
    //buttonM
    if (bedroomMLastState == BTN_IS_RELEASED && bedroomMCurrState == BTN_IS_PRESSED)
    {
        print("BTN_BEDROOM_M_PIN_I is pressed.");

        delay(400);

        bedroomMCurrState = debounce(bedroomMLastState, BTN_BEDROOM_M_PIN_I);
        if (bedroomMCurrState == BTN_IS_PRESSED)
        {
            print("BTN_BEDROOM_M_PIN_I is still pressed!");

            diningLightIsOn = !diningLightIsOn;
        }
        else
        {
            hallLightIsOn = !hallLightIsOn;
        }

        send(msgDinningLight.set(calcStateForHA(diningLightIsOn)), true);
        send(msgHallLight.set(calcStateForHA(hallLightIsOn)), true);
    }
    //buttonB
    if (bedroomBLastState == BTN_IS_RELEASED && bedroomBCurrState == BTN_IS_PRESSED)
    {
        print("BTN_BEDROOM_B_PIN_I is pressed.");

        delay(400);

        bedroomBCurrState = debounce(bedroomBLastState, BTN_BEDROOM_B_PIN_I);
        if (bedroomBCurrState == BTN_IS_PRESSED)
        {
            print("BTN_BEDROOM_B_PIN_I is still pressed!");

            hallwayLightIsOn = LIGHT_IS_OFF;
            hallLightIsOn = LIGHT_IS_OFF;
            bathroomLightIsOn = LIGHT_IS_OFF;
            bathroomFanIsOn = LIGHT_IS_OFF;
            kitchenMainLightIsOn = LIGHT_IS_OFF;
            kitchenAddLightIsOn = LIGHT_IS_OFF;
            kitchenBackLightIsOn = LIGHT_IS_ON; //need to left the kitchen backlight switched on
            diningLightIsOn = LIGHT_IS_OFF;
        }
        else
        {
            hallwayLightIsOn = !hallwayLightIsOn;
        }

        send(msgHallwayLight.set(calcStateForHA(hallwayLightIsOn)), true);
        send(msgHallLight.set(calcStateForHA(hallLightIsOn)), true);
        send(msgBathroomLight.set(calcStateForHA(bathroomLightIsOn)), true);
        send(msgBathroomFan.set(calcStateForHA(bathroomFanIsOn)), true);
        send(msgKitchenMainLight.set(calcStateForHA(kitchenMainLightIsOn)), true);
        send(msgKitchenAddLight.set(calcStateForHA(kitchenAddLightIsOn)), true);
        send(msgKitchenBackLight.set(calcStateForHA(kitchenBackLightIsOn)), true);
        send(msgDinningLight.set(calcStateForHA(diningLightIsOn)), true);
    }

    /*SCONCE1+BEDROOM*/
    if (sconce1LastState == BTN_IS_RELEASED && sconce1CurrState == BTN_IS_PRESSED)
    {
        Serial.println("BTN_SCONCE1_PIN_I is pressed.");

        delay(400);

        sconce1CurrState = debounce(sconce1LastState, BTN_SCONCE1_PIN_I);
        if (sconce1CurrState == BTN_IS_PRESSED)
        {
            print("BTN_SCONCE1_PIN_I is still pressed!");

            bedroomLightIsOn = !bedroomLightIsOn;
        }
        else
        {
            sconce1IsOn = !sconce1IsOn;
        }

        send(msgBedroomLight.set(calcStateForHA(bedroomLightIsOn)), true);
        send(msgSconce1Light.set(calcStateForHA(sconce1IsOn)), true);
    }

    /*SCONCE2+BEDROOM*/
    if (sconce2LastState == BTN_IS_RELEASED && sconce2CurrState == BTN_IS_PRESSED)
    {
        print("BTN_SCONCE2_PIN_I is pressed.");

        delay(400);

        sconce2CurrState = debounce(sconce2LastState, BTN_SCONCE2_PIN_I);
        if (sconce2CurrState == BTN_IS_PRESSED)
        {
            print("BTN_SCONCE2_PIN_I is still pressed!");

            bedroomLightIsOn = !bedroomLightIsOn;
        }
        else
        {
            sconce2IsOn = !sconce2IsOn;
        }

        send(msgBedroomLight.set(calcStateForHA(bedroomLightIsOn)), true);
        send(msgSconce2Light.set(calcStateForHA(sconce2IsOn)), true);
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

void receive(const MyMessage &message)
{
    if (message.isAck())
    {
        print("This is an ack from gateway");
    }

    if (message.type == V_STATUS)
    {
        if (!initialValueSent)
        {
            print("Receiving initial value from controller");
            initialValueSent = true;
        }

        uint8_t sensor = message.sensor;
        uint8_t value = message.getBool();

        if (sensor == CHILD_ACTUATOR_ID_HALLWAY_LIGHT)
        {
            hallwayLightIsOn = calcStateFromHA(value);
            digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, hallwayLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_BATHROOM_FAN)
        {
            bathroomFanIsOn = calcStateFromHA(value);
            digitalWrite(BATHROOM_FAN_RELAY_PIN_O, bathroomFanIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_BATHROOM_LIGHT)
        {
            bathroomLightIsOn = calcStateFromHA(value);
            digitalWrite(BATHROOM_LIGHT_RELAY_PIN_O, bathroomLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_KITCHEN_MAIN)
        {
            kitchenMainLightIsOn = calcStateFromHA(value);
            digitalWrite(KITCHEN_MAIN_RELAY_PIN_O, kitchenMainLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_KITCHEN_ADD)
        {
            kitchenAddLightIsOn = calcStateFromHA(value);
            digitalWrite(KITCHEN_ADD_RELAY_PIN_O, kitchenAddLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_KITCHEN_BACKLIGHT)
        {
            kitchenBackLightIsOn = calcStateFromHA(value);
            digitalWrite(KITCHEN_BACKLIGHT_RELAY_PIN_O, kitchenBackLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_HALL_LIGHT)
        {
            hallLightIsOn = calcStateFromHA(value);
            digitalWrite(HALL_LIGHT_RELAY_PIN_O, hallLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_DINING_LIGHT)
        {
            diningLightIsOn = calcStateFromHA(value);
            digitalWrite(DINING_LIGHT_RELAY_PIN_O, diningLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_BEDROOM_LIGHT)
        {
            bedroomLightIsOn = calcStateFromHA(value);
            digitalWrite(BEDROOM_LIGHT_RELAY_PIN_O, bedroomLightIsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_SCONCE1_LIGHT)
        {
            sconce1IsOn = calcStateFromHA(value);
            digitalWrite(SCONCE1_LIGHT_RELAY_PIN_O, sconce1IsOn);
        }
        else if (sensor == CHILD_ACTUATOR_ID_SCONCE2_LIGHT)
        {
            sconce2IsOn = calcStateFromHA(value);
            digitalWrite(SCONCE2_LIGHT_RELAY_PIN_O, sconce2IsOn);
        }
    }
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

/**
 * Because of light and fan are operating with relay - it is necessary to invert HA response.
 * Response 'true' means 'light on!', but for the relay signal must be 'false'. So, conversion is needed.
 */
bool calcStateFromHA(bool state)
{
    return state ? LIGHT_IS_ON : LIGHT_IS_OFF;
}

/**
 * Because of light and fan are operating with relay - it is necessary to invert state for request to HA.
 * State 'false' means 'light on!', but for the HA state must be 'true'. So, conversion is needed.
 */
bool calcStateForHA(bool state)
{
    return state ? LIGHT_IS_OFF_HA : LIGHT_IS_ON_HA;
}