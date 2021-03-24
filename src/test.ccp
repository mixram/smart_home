#define SN "MyTestSketch"
#define SV "0.2"

//My Arduino is both note and gateway (https://www.mysensors.org/about/network)
#define MY_NODE_ID 1
#define MY_DEBUG
#define MY_GATEWAY_SERIAL
// #define MY_BAUD_RATE 115200

#include <Arduino.h>
#include <MySensors.h>

/*INPUT*/
const int BTN1_PIN_I = 2;
const int BTN2_PIN_I = 3;

/*OUTPUT*/
const int LED1_PIN_O = 4;
const int LED2_PIN_O = 5;
const int LED3_PIN_O = 6;

/*INPUTS STATES*/
bool btn1CurrState = LOW;
bool btn1LastState = LOW;
bool btn2CurrState = LOW;
bool btn2LastState = LOW;

/*OUTPUTS STATES*/
bool light1IsOn = false;
bool light2IsOn = false;
bool light3IsOn = false;

  /*MY_SENSORS_ACTUATORS*/
const int CHILD_ACTUATOR_ID_LIGHT1 = 4;
const int CHILD_ACTUATOR_ID_LIGHT2 = 5;
const int CHILD_ACTUATOR_ID_LIGHT3 = 6;
bool initialValueSent = false;
MyMessage msgLight1(CHILD_ACTUATOR_ID_LIGHT1, V_STATUS);
MyMessage msgLight2(CHILD_ACTUATOR_ID_LIGHT2, V_STATUS);
MyMessage msgLight3(CHILD_ACTUATOR_ID_LIGHT3, V_STATUS);

/*OTHER*/
bool printAccepted = true;
int connectAttemptscounter = 0;
const int ACCEPTED_CONNECTION_ATTEMPTS = 20;

void before()
{
  pinMode(BTN1_PIN_I, INPUT);
  pinMode(BTN2_PIN_I, INPUT);
  pinMode(LED1_PIN_O, OUTPUT);
  pinMode(LED2_PIN_O, OUTPUT);
  pinMode(LED3_PIN_O, OUTPUT);

  //initial state
  digitalWrite(LED1_PIN_O, LOW);
  digitalWrite(LED2_PIN_O, LOW);
  digitalWrite(LED3_PIN_O, LOW);
}

void setup()
{
  // Serial.begin(115200);
  Serial.begin(9600);
  // while (Serial.available())
  //   ;
}

void presentation()
{
  sendSketchInfo(SN, SV);
  present(CHILD_ACTUATOR_ID_LIGHT1, S_BINARY);
  present(CHILD_ACTUATOR_ID_LIGHT2, S_BINARY);
  present(CHILD_ACTUATOR_ID_LIGHT3, S_BINARY);
}

void loop()
{
  if (!initialValueSent && connectAttemptscounter < ACCEPTED_CONNECTION_ATTEMPTS)
  {
    print("Sending initial value");
    send(msgLight1.set(light1IsOn));
    send(msgLight2.set(light2IsOn));
    send(msgLight3.set(light3IsOn));

    print("Requesting initial value from controller");
    request(CHILD_ACTUATOR_ID_LIGHT1, V_STATUS);
    request(CHILD_ACTUATOR_ID_LIGHT2, V_STATUS);
    request(CHILD_ACTUATOR_ID_LIGHT3, V_STATUS);

    connectAttemptscounter++;
    print("Connection attempt " + String(connectAttemptscounter) + " out of " + String(ACCEPTED_CONNECTION_ATTEMPTS));

    wait(2000, C_SET, V_STATUS);
  }

  btn1CurrState = debounce(btn1LastState, BTN1_PIN_I);
  btn2CurrState = debounce(btn2LastState, BTN2_PIN_I);

  if (btn1LastState == LOW && btn1CurrState == HIGH)
  {
    light1IsOn = !light1IsOn;
    send(msgLight1.set(light1IsOn), true);
  }
  if (btn2LastState == LOW && btn2CurrState == HIGH)
  {
    delay(400);

    btn2CurrState = debounce(btn2LastState, BTN2_PIN_I);
    if (btn2CurrState == HIGH)
    {
      light3IsOn = !light3IsOn;
      send(msgLight3.set(light3IsOn), true);
    }
    else
    {
      light2IsOn = !light2IsOn;
      send(msgLight2.set(light2IsOn), true);
    }
  }

  digitalWrite(LED1_PIN_O, light1IsOn);
  digitalWrite(LED2_PIN_O, light2IsOn);
  digitalWrite(LED3_PIN_O, light3IsOn);

  btn1LastState = btn1CurrState;
  btn2LastState = btn2CurrState;
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

    if (sensor == CHILD_ACTUATOR_ID_LIGHT1)
    {
      light1IsOn = value;
      digitalWrite(LED1_PIN_O, light1IsOn);

      btn1LastState = !btn1LastState;
    }
    else if (sensor == CHILD_ACTUATOR_ID_LIGHT2)
    {
      light2IsOn = value;
      digitalWrite(LED2_PIN_O, light2IsOn);

      btn2LastState = !btn2LastState;
    }
    else if (sensor == CHILD_ACTUATOR_ID_LIGHT3)
    {
      light3IsOn = value;
      digitalWrite(LED3_PIN_O, light3IsOn);

      btn2LastState = !btn2LastState;
    }
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
  }

  return current;
}

void print(String text)
{
  if (printAccepted)
  {
    Serial.println(text);
  }
}