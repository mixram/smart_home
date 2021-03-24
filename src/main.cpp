
// #include <Arduino.h>

// /*INPUT*/
// #define HALLWAY_I 41   //for button near the flat door
// #define HALL_I 37      //for button right of the hallway door
// #define BATHROOM1_I 33 //for button left of the bathroom door and button in the bathroom
// #define BATHROOM2_I 22 //for button in the bathroom
// #define KITCHEN_I 26   //for button near the kitchen
// #define BEDROOM_T_I 30 //for button left of the bedroom door
// #define BEDROOM_M_I 34 //for button left of the bedroom door
// #define BEDROOM_B_I 38 //for button left of the bedroom door
// #define SCONCE1_I 42   //for button on the brace_1
// #define SCONCE2_I 46   //for button on the brace_2

// /*OUTPUT*/
// //hallway relay
// #define HALLWAY_LIGHT_O A3     //for light in the hallway
// #define BATHROOM_FAN_O A5      //for fan in the bathroom
// #define BATHROOM_LIGHT_O A4    //for light in the bathroom
// #define KITCHEN_MAIN_O A0      //for main light in the kitchen
// #define KITCHEN_ADD_O A1       //for additional light in the kitchen
// #define KITCHEN_BACKLIGHT_O A2 //for backlight in the kitchen
// //hall relay
// #define HALL_LIGHT_O 45    //for light in the hall
// #define DINING_LIGHT_O 47  //for dining zone light
// #define BEDROOM_LIGHT_O 53 //for light in the bedroom
// #define SCONCE1_LIGHT_O 49 //for brace_1 light
// #define SCONCE2_LIGHT_O 51 //for brace_2 light

// /*INPUTS STATES*/
// bool hallwayLastState = LOW;
// bool hallwayCurrState = LOW;
// bool hallLastState = LOW;
// bool hallCurrState = LOW;
// bool bathroom1LastState = LOW;
// bool bathroom1CurrState = LOW;
// bool bathroom2LastState = LOW;
// bool bathroom2CurrState = LOW;
// bool kitchenLastState = LOW;
// bool kitchenCurrState = LOW;
// bool bedroomTLastState = LOW;
// bool bedroomTCurrState = LOW;
// bool bedroomMLastState = LOW;
// bool bedroomMCurrState = LOW;
// bool bedroomBLastState = LOW;
// bool bedroomBCurrState = LOW;
// bool sconce1LastState = LOW;
// bool sconce1CurrState = LOW;
// bool sconce2LastState = LOW;
// bool sconce2CurrState = LOW;

// /*OUTPUTS STATES*/
// bool hallwayLightIsOn = true;
// bool hallLightIsOn = false; //because the light is engaged in start script
// bool bathroomLightIsOn = true;
// bool bathroomFanIsOn = true;
// bool kitchenMainLightIsOn = true;
// bool kitchenAddLightIsOn = true;
// bool kitchenBackLightIsOn = true;
// bool diningLightIsOn = true;
// bool bedroomLightIsOn = true;
// bool sconce1IsOn = true;
// bool sconce2IsOn = true;

// /*OTHER*/
// bool printAccepted = true;

// void setup()
// {
//   //initial state
//   digitalWrite(HALLWAY_LIGHT_O, HIGH);
//   digitalWrite(HALL_LIGHT_O, HIGH);
//   digitalWrite(BATHROOM_LIGHT_O, HIGH);
//   digitalWrite(BATHROOM_FAN_O, HIGH);
//   digitalWrite(KITCHEN_MAIN_O, HIGH);
//   digitalWrite(KITCHEN_ADD_O, HIGH);
//   digitalWrite(KITCHEN_BACKLIGHT_O, HIGH);
//   digitalWrite(DINING_LIGHT_O, HIGH);
//   digitalWrite(BEDROOM_LIGHT_O, HIGH);
//   digitalWrite(SCONCE1_LIGHT_O, HIGH);
//   digitalWrite(SCONCE2_LIGHT_O, HIGH);

//   Serial.begin(9600);
//   while (Serial.available())
//     ;

//   print("Initializing variables...");

//   //setting input pins
//   pinMode(HALLWAY_I, INPUT);
//   pinMode(HALL_I, INPUT);
//   pinMode(BATHROOM1_I, INPUT);
//   pinMode(BATHROOM2_I, INPUT);
//   pinMode(KITCHEN_I, INPUT);
//   pinMode(BEDROOM_T_I, INPUT);
//   pinMode(BEDROOM_M_I, INPUT);
//   pinMode(BEDROOM_B_I, INPUT);
//   pinMode(SCONCE1_I, INPUT);
//   pinMode(SCONCE2_I, INPUT);

//   //setting output pins
//   pinMode(HALLWAY_LIGHT_O, OUTPUT);
//   pinMode(HALL_LIGHT_O, OUTPUT);
//   pinMode(BATHROOM_LIGHT_O, OUTPUT);
//   pinMode(BATHROOM_FAN_O, OUTPUT);
//   pinMode(KITCHEN_MAIN_O, OUTPUT);
//   pinMode(KITCHEN_ADD_O, OUTPUT);
//   pinMode(KITCHEN_BACKLIGHT_O, OUTPUT);
//   pinMode(DINING_LIGHT_O, OUTPUT);
//   pinMode(BEDROOM_LIGHT_O, OUTPUT);
//   pinMode(SCONCE1_LIGHT_O, OUTPUT);
//   pinMode(SCONCE2_LIGHT_O, OUTPUT);

//   print("Initializing variables has finished.");

//   print("Configuring peripherals state...");

//   //switch ON the devices
//   digitalWrite(HALL_LIGHT_O, LOW);

//   print("Peripherals are configured.");
// }

// void loop()
// {
//   //debounced value of button (pressed or released)
//   hallwayCurrState = debounce(hallwayLastState, HALLWAY_I);
//   hallCurrState = debounce(hallLastState, HALL_I);
//   bathroom1CurrState = debounce(bathroom1LastState, BATHROOM1_I);
//   bathroom2CurrState = debounce(bathroom2LastState, BATHROOM2_I);
//   kitchenCurrState = debounce(kitchenLastState, KITCHEN_I);
//   bedroomTCurrState = debounce(bedroomTLastState, BEDROOM_T_I);
//   bedroomMCurrState = debounce(bedroomMLastState, BEDROOM_M_I);
//   bedroomBCurrState = debounce(bedroomBLastState, BEDROOM_B_I);
//   sconce1CurrState = debounce(sconce1LastState, SCONCE1_I);
//   sconce2CurrState = debounce(sconce2LastState, SCONCE2_I);

//   /*HALLWAY+HALL*/
//   if (hallwayLastState == LOW && hallwayCurrState == HIGH)
//   {
//     print("HALLWAY_I is pressed.");

//     delay(400);

//     hallwayCurrState = debounce(hallwayLastState, HALLWAY_I);
//     if (hallwayCurrState == HIGH)
//     {
//       print("HALLWAY_I is still pressed!");

//       if (hallwayLightIsOn == false || hallLightIsOn == false)
//       {
//         hallwayLightIsOn = true;
//         hallLightIsOn = true;
//       }
//       else
//       {
//         hallwayLightIsOn = false;
//         hallLightIsOn = false;
//       }
//     }
//     else
//     {
//       hallwayLightIsOn = !hallwayLightIsOn;
//     }
//   }

//   /*HALL+DINNING*/
//   if (hallLastState == LOW && hallCurrState == HIGH)
//   {
//     print("HALL_I is pressed.");

//     delay(400);

//     hallCurrState = debounce(hallLastState, HALL_I);
//     if (hallCurrState == HIGH)
//     {
//       print("HALL_I is still pressed!");

//       diningLightIsOn = !diningLightIsOn;
//       print("diningLightIsOn=" + String(diningLightIsOn));
//     }
//     else
//     {
//       hallLightIsOn = !hallLightIsOn;
//       print("hallLightIsOn=" + String(hallLightIsOn));
//     }
//   }

//   /*BATHROOM*/
//   //botton1
//   if (bathroom1LastState == LOW && bathroom1CurrState == HIGH)
//   {
//     print("BATHROOM1_I is pressed.");

//     delay(400);

//     bathroom1CurrState = debounce(bathroom1LastState, BATHROOM1_I);
//     if (bathroom1CurrState == HIGH)
//     {
//       Serial.println("BATHROOM1_I is still pressed!");

//       bathroomFanIsOn = !bathroomFanIsOn;
//       print("bathroomFanIsOn=" + String(bathroomFanIsOn));
//     }
//     else
//     {
//       bathroomLightIsOn = !bathroomLightIsOn;
//       print("bathroomLightIsOn=" + String(bathroomLightIsOn));
//     }
//   }
//   //botton2
//   if (bathroom2LastState == LOW && bathroom2CurrState == HIGH)
//   {
//     print("BATHROOM2_I is pressed.");

//     delay(400);

//     bathroom2CurrState = debounce(bathroom2LastState, BATHROOM2_I);
//     if (bathroom2CurrState == HIGH)
//     {
//       print("BATHROOM2_I is still pressed!");

//       bathroomFanIsOn = !bathroomFanIsOn;
//     }
//     else
//     {
//       bathroomLightIsOn = !bathroomLightIsOn;
//     }
//   }

//   /*KITCHEN*/
//   //if now pressed and previously was released - I may do needed logic.
//   if (kitchenLastState == LOW && kitchenCurrState == HIGH)
//   {
//     print("KITCHEN_I is pressed.");

//     //wait to check if button still pressed
//     delay(400);

//     kitchenCurrState = debounce(kitchenLastState, KITCHEN_I);
//     if (kitchenCurrState == HIGH)
//     {
//       print("KITCHEN_I is still pressed!");

//       //if we are here - it means "long-press" logic should be switched on/off
//       kitchenAddLightIsOn = !kitchenAddLightIsOn;

//       //wait to check if button still pressed
//       delay(400);

//       kitchenCurrState = debounce(kitchenLastState, KITCHEN_I);
//       if (kitchenCurrState == HIGH)
//       {
//         print("KITCHEN_I is STILL pressed!");

//         //if we are here - it means "long-long-press" logic should be switched on/off
//         kitchenAddLightIsOn = !kitchenAddLightIsOn;
//         kitchenBackLightIsOn = !kitchenBackLightIsOn;
//       }
//     }
//     else
//     {
//       //if we are here - it means "short-press" logic should be switched on/off
//       kitchenMainLightIsOn = !kitchenMainLightIsOn;
//       print("kitchenMainLightIsOn=" + String(kitchenMainLightIsOn));
//     }
//   }

//   /*BEDROOM+SCONCES*/
//   //buttonT
//   if (bedroomTLastState == LOW && bedroomTCurrState == HIGH)
//   {
//     print("BEDROOM_T_I is pressed.");

//     delay(400);

//     bedroomTCurrState = debounce(bedroomTLastState, BEDROOM_T_I);
//     if (bedroomTCurrState == HIGH)
//     {
//       print("BEDROOM_T_I is still pressed!");

//       if (sconce1IsOn == false || sconce2IsOn == false)
//       {
//         sconce1IsOn = true;
//         sconce2IsOn = true;
//       }
//       else
//       {
//         sconce1IsOn = false;
//         sconce2IsOn = false;
//       }
//     }
//     else
//     {
//       bedroomLightIsOn = !bedroomLightIsOn;
//     }
//   }
//   //buttonM
//   if (bedroomMLastState == LOW && bedroomMCurrState == HIGH)
//   {
//     print("BEDROOM_M_I is pressed.");

//     delay(400);

//     bedroomMCurrState = debounce(bedroomMLastState, BEDROOM_M_I);
//     if (bedroomMCurrState == HIGH)
//     {
//       print("BEDROOM_M_I is still pressed!");

//       diningLightIsOn = !diningLightIsOn;
//     }
//     else
//     {
//       hallLightIsOn = !hallLightIsOn;
//     }
//   }
//   //buttonB
//   if (bedroomBLastState == LOW && bedroomBCurrState == HIGH)
//   {
//     print("BEDROOM_B_I is pressed.");

//     delay(400);

//     bedroomBCurrState = debounce(bedroomBLastState, BEDROOM_B_I);
//     if (bedroomBCurrState == HIGH)
//     {
//       print("BEDROOM_B_I is still pressed!");

//       hallwayLightIsOn = true;
//       hallLightIsOn = true;
//       bathroomLightIsOn = true;
//       bathroomFanIsOn = true;
//       kitchenMainLightIsOn = true;
//       kitchenAddLightIsOn = true;
//       kitchenBackLightIsOn = true;
//       diningLightIsOn = true;
//     }
//     else
//     {
//       hallwayLightIsOn = !hallwayLightIsOn;
//     }
//   }

//   /*SCONCE1+BEDROOM*/
//   if (sconce1LastState == LOW && sconce1CurrState == HIGH)
//   {
//     Serial.println("SCONCE1_I is pressed.");

//     delay(400);

//     sconce1CurrState = debounce(sconce1LastState, SCONCE1_I);
//     if (sconce1CurrState == HIGH)
//     {
//       print("SCONCE1_I is still pressed!");

//       bedroomLightIsOn = !bedroomLightIsOn;
//     }
//     else
//     {
//       sconce1IsOn = !sconce1IsOn;
//     }
//   }

//   /*SCONCE2+BEDROOM*/
//   if (sconce2LastState == LOW && sconce2CurrState == HIGH)
//   {
//     print("SCONCE2_I is pressed.");

//     delay(400);

//     sconce2CurrState = debounce(sconce2LastState, SCONCE2_I);
//     if (sconce2CurrState == HIGH)
//     {
//       print("SCONCE2_I is still pressed!");

//       bedroomLightIsOn = !bedroomLightIsOn;
//     }
//     else
//     {
//       sconce2IsOn = !sconce2IsOn;
//     }
//   }

//   //set HALLWAY_LIGHT_O state
//   digitalWrite(HALLWAY_LIGHT_O, hallwayLightIsOn);
//   //set HALL_LIGHT_O state
//   digitalWrite(HALL_LIGHT_O, hallLightIsOn);
//   //set BATHROOM_LIGHT_O state
//   digitalWrite(BATHROOM_LIGHT_O, bathroomLightIsOn);
//   //set BATHROOM_FAN_O state
//   digitalWrite(BATHROOM_FAN_O, bathroomFanIsOn);
//   //set KITCHEN_MAIN_O state
//   digitalWrite(KITCHEN_MAIN_O, kitchenMainLightIsOn);
//   //set KITCHEN_ADD_O state
//   digitalWrite(KITCHEN_ADD_O, kitchenAddLightIsOn);
//   //set KITCHEN_BACKLIGHT_O state
//   digitalWrite(KITCHEN_BACKLIGHT_O, kitchenBackLightIsOn);
//   //set DINING_LIGHT_O state
//   digitalWrite(DINING_LIGHT_O, diningLightIsOn);
//   //set BEDROOM_LIGHT_O state
//   digitalWrite(BEDROOM_LIGHT_O, bedroomLightIsOn);
//   //set SCONCE1_LIGHT_O state
//   digitalWrite(SCONCE1_LIGHT_O, sconce1IsOn);
//   //set SCONCE2_LIGHT_O state
//   digitalWrite(SCONCE2_LIGHT_O, sconce2IsOn);

//   //save current button state to use on the next loop
//   hallwayLastState = hallwayCurrState;
//   hallLastState = hallCurrState;
//   bathroom1LastState = bathroom1CurrState;
//   bathroom2LastState = bathroom1CurrState;
//   kitchenLastState = kitchenCurrState;
//   bedroomTLastState = bedroomTCurrState;
//   bedroomMLastState = bedroomMCurrState;
//   bedroomBLastState = bedroomBCurrState;
//   sconce1LastState = sconce1CurrState;
//   sconce2LastState = sconce2CurrState;
// }

// void print(String text)
// {
//   if (printAccepted)
//   {
//     Serial.println(text);
//   }
// }

// bool debounce(bool last,
//               int btn)
// {
//   bool current = digitalRead(btn);
//   if (last != current)
//   {
//     delay(5);
//     current = digitalRead(btn);

//     print(String("Button ") + String(btn) + String(" new state: ") + String(current) + ".");
//   }

//   return current;
// }