#define SN "OurSmartHome"
#define SV "1.0"

//My Arduino is both note and gateway (https://www.mysensors.org/about/network)
#define MY_NODE_ID 1
#define MY_DEBUG
#define MY_GATEWAY_SERIAL

#include <Arduino.h>
#include <MySensors.h>

/*INPUT*/
const int BTN_HALLWAY_PIN_I = 41; //for button near the flat door

/*OUTPUT*/
//hallway relay
const int HALLWAY_LIGHT_RELAY_PIN_O = A3; //for light in the hallway

/*SENSORS_ACTUATORS*/
//hallway
const int CHILD_ACTUATOR_ID_HALLWAY_LIGHT = A3; //register light in the hallway in HA
MyMessage msgHallwayLight(CHILD_ACTUATOR_ID_HALLWAY_LIGHT, V_STATUS);

/*INPUTS STATES*/
bool hallwayLastState = LOW;
bool hallwayCurrState = LOW;

/*OUTPUTS STATES*/
bool hallwayLightIsOn = true;

/*OTHER*/
bool printAccepted = true;
int connectAttemptscounter = 0;
const int ACCEPTED_CONNECTION_ATTEMPTS = 10;
bool initialValueSent = false;

void before()
{
    //setting input pins
    pinMode(BTN_HALLWAY_PIN_I, INPUT);

    //setting output pins
    pinMode(HALLWAY_LIGHT_RELAY_PIN_O, OUTPUT);

    //initial state
    digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, HIGH);
}

void setup()
{
    Serial.begin(9600);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
}

void presentation()
{
    sendSketchInfo(SN, SV);
    present(CHILD_ACTUATOR_ID_HALLWAY_LIGHT, S_BINARY);
}

void loop()
{
    if (!initialValueSent && connectAttemptscounter < ACCEPTED_CONNECTION_ATTEMPTS)
    {
        print("Sending initial value");
        send(msgHallwayLight.set(hallwayLightIsOn));

        print("Requesting initial value from controller");
        request(CHILD_ACTUATOR_ID_HALLWAY_LIGHT, V_STATUS);

        connectAttemptscounter++;
        print("Connection attempt " + String(connectAttemptscounter) + " out of " + String(ACCEPTED_CONNECTION_ATTEMPTS));

        wait(2000, C_SET, V_STATUS);
    }

    hallwayCurrState = debounce(hallwayLastState, BTN_HALLWAY_PIN_I);

    /*HALLWAY+HALL*/
    if (hallwayLastState == LOW && hallwayCurrState == HIGH)
    {
        print("BTN_HALLWAY_PIN_I is pressed.");

        hallwayLightIsOn = !hallwayLightIsOn;
        send(msgHallwayLight.set(hallwayLightIsOn), true);
    }

    //set HALLWAY_LIGHT_RELAY_PIN_O state
    digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, hallwayLightIsOn);

    //save current button state to use on the next loop
    hallwayLastState = hallwayCurrState;
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
            hallwayLightIsOn = value;
            digitalWrite(HALLWAY_LIGHT_RELAY_PIN_O, hallwayLightIsOn);

            hallwayLastState = !hallwayLastState;
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