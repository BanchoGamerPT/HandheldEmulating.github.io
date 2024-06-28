#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>
#include <BleGamepad.h>

#define PS_X 2
#define PS_CIRCLE 3
#define PS_TRIANGLE 4
#define PS_SQUARE 1

#define PS_L1 5
#define PS_R1 6
#define PS_L2 7
#define PS_R2 8

#define PS_SELECT 9
#define PS_START 10
#define PS_PSBUTTON 13

#define PS_L3 11
#define PS_R3 12

#define PS_DPU 13
#define PS_DPD 14
#define PS_DPR 16
#define PS_DPL 15

//x ○ △ □
#define X_BUTTON D5
#define CIRCLE_BUTTON D6
#define TRIANGLE_BUTTON D3
#define SQUARE_BUTTON D4

//triggers
#define R1_BUTTON D13
#define R2_BUTTON 0
#define L1_BUTTON 0
#define L2_BUTTON 0

//menu
#define START_BUTTON D2
#define SELECT_BUTTON 
#define PS_BUTTON 

//JOYSTICKS BUTTONS
#define R3_BUTTON D12
#define L3_BUTTON 0

//dpad
//#define dp_right D7
//#define dp_left D5
#define DP_UP 
#define DP_DOWN 
#define DP_RIGHT 
#define DP_LEFT 

//JOYSTICKS
#define LEFT_VRX_JOYSTICK 
#define LEFT_VRY_JOYSTICK 
#define RIGHT_VRX_JOYSTICK A0
#define RIGHT_VRY_JOYSTICK A1

#define NUM_BUTTONS_MASTER 8
#define NUM_BUTTONS_SLAVE 8

//ordered arrays with pins and button codes for the master arduino
int buttonsMaster[NUM_BUTTONS_MASTER] = {X_BUTTON, CIRCLE_BUTTON, TRIANGLE_BUTTON, SQUARE_BUTTON, R1_BUTTON, R2_BUTTON, START_BUTTON, R3_BUTTON};
int GamepadButtonsMaster[NUM_BUTTONS_MASTER] = {PS_X, PS_CIRCLE, PS_TRIANGLE, PS_SQUARE, PS_R1, PS_R2, PS_START, PS_R3};
//ordered arrays with pins and button codes for the slave arduino
int GamepadButtonsSlave[NUM_BUTTONS_SLAVE] = {PS_L1, PS_L2, PS_SELECT, PS_DPU, PS_DPD, PS_DPR, PS_DPL, PS_L3};

uint16_t rightVrxJoystickLecture = 0;
uint16_t rightVryJoystickLecture = 0;

uint16_t rightVrxJoystickValue = 0;
uint16_t rightVryJoystickValue = 0;

BleGamepad bleGamepad("Maker101 Gamepad", "Maker101 Home");
BleGamepadConfiguration bleGamepadConfig;

typedef struct ESP_message {
    int inputs[NUM_BUTTONS_SLAVE];
    uint16_t joystick[2];
} ESP_message;

ESP_message message;

void OnDataRecv (const uint8_t* mac, const uint8_t *data, int length)
{
  memcpy(&message, data, sizeof(message));

  for (int i = 0; i < 7; i++)
  {
    if (message.inputs[i])
    {
      bleGamepad.press(GamepadButtonsSlave[i]);
      Serial.println(message.inputs[i]);
    }
    else
    {
      bleGamepad.release(GamepadButtonsSlave[i]);
    }
  }
  bleGamepad.setLeftThumb(message.joystick[0], message.joystick[1]);

    Serial.print(message.joystick[0]);
    Serial.print("\t");
    Serial.print(message.joystick[1]);
    Serial.println();
}

void setup()
{
  delay(1000);
  Serial.begin(115200);

  for(int i=0; i<NUM_BUTTONS_MASTER; i++){
    pinMode(buttonsMaster[i], INPUT_PULLUP);
  }

  bleGamepadConfig.setAutoReport(false);
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setVid(0xe502);
  bleGamepadConfig.setPid(0xabcd);
  bleGamepadConfig.setHatSwitchCount(4);
  bleGamepad.begin(&bleGamepadConfig);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  Serial.println(WiFi.macAddress());
}

void loop()
{
  if(bleGamepad.isConnected()){
  //Joysticks lecture
  rightVrxJoystickLecture = analogRead(RIGHT_VRX_JOYSTICK);
  rightVryJoystickLecture = analogRead(RIGHT_VRY_JOYSTICK);

  //Compute joysticks value
  rightVrxJoystickValue = map(rightVrxJoystickLecture, 0, 4095, 0, 32737);
  rightVryJoystickValue = map(rightVryJoystickLecture, 0, 4095, 0, 32737);
  }

  for(int i=0; i<NUM_BUTTONS_MASTER; i++){
    if(!digitalRead(buttonsMaster[i])){
      bleGamepad.press(GamepadButtonsMaster[i]);

      Serial.println(buttonsMaster[i]);     
      Serial.println(GamepadButtonsMaster[i]);     
      Serial.println();     
      Serial.println();     
    }
    else{
      bleGamepad.release(GamepadButtonsMaster[i]);      
    }
    bleGamepad.setRightThumb(rightVrxJoystickValue, rightVryJoystickValue);
  }
  bleGamepad.sendReport();
}
