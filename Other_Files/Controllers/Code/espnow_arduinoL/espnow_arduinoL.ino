#include <esp_now.h>
#include <WiFi.h>

//values for the buttons
#define PS_L1 5
#define PS_L2 7

#define PS_SELECT 9

#define PS_DPU 13
#define PS_DPD 14
#define PS_DPR 16
#define PS_DPL 15

#define PS_L3 11

//pins for the buttons
#define L1_BUTTON D13
#define L2_BUTTON 0

#define SELECT_BUTTON D6

#define DP_UP D9
#define DP_DOWN D11
#define DP_RIGHT D12
#define DP_LEFT D10

#define L3_BUTTON D7

#define LEFT_VRX_JOYSTICK A0
#define LEFT_VRY_JOYSTICK A1

// 7 buttons (dpad, L1, L2 and select) and 1 joystick
#define NUM_BUTTONS 8
#define NUM_JOYSTICKS 1 

int buttons[NUM_BUTTONS] = {L1_BUTTON, L2_BUTTON, SELECT_BUTTON, DP_UP, DP_DOWN, DP_RIGHT, DP_LEFT, L3_BUTTON};

int GamepadButtons[NUM_BUTTONS] = {PS_L1, PS_L2, PS_SELECT, PS_DPU, PS_DPD, PS_DPR, PS_DPL, PS_L3};

uint16_t leftVrxJoystickLecture = 0;
uint16_t leftVryJoystickLecture = 0;

uint8_t masterAddress[] = {0x34, 0x85, 0x18, 0x7A, 0x36, 0x20};

esp_now_peer_info_t masterInfo;

typedef struct ESP_message {
  //for all buttons + joystick y and x axis
  int inputs[NUM_BUTTONS];
  uint16_t joystick[NUM_JOYSTICKS*2];
} ESP_message;

ESP_message message;

void OnDataSent(const uint8_t *mac, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  Serial.begin(115200);

  for(int i=0; i<NUM_BUTTONS; i++){
    pinMode(buttons[i], INPUT_PULLUP);
  }

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(masterInfo.peer_addr, masterAddress, 6);
  masterInfo.channel = 0;
  masterInfo.encrypt = false;

  if (esp_now_add_peer(&masterInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop()
{
  leftVrxJoystickLecture = analogRead(LEFT_VRX_JOYSTICK);
  leftVryJoystickLecture = analogRead(LEFT_VRY_JOYSTICK);

  Serial.println(WiFi.macAddress());

  //Compute joysticks value
  message.joystick[0] = map(leftVryJoystickLecture, 0, 4095, 0, 32737);
  message.joystick[1] = map(leftVrxJoystickLecture, 0, 4095, 0, 32737);

  //Serial.print(message.joystick[0]);
  //Serial.print("\t");
  //Serial.print(message.joystick[1]);
  //Serial.println();

  //set the values of pressed buttons
  for(int i = 0; i < NUM_BUTTONS; i++)
  {
    if(!digitalRead(buttons[i])){
      message.inputs[i] = GamepadButtons[i];
      Serial.println(buttons[i]);     
      Serial.println(GamepadButtons[i]);   
      Serial.println();     
      Serial.println();   
    }
    else
    {
      message.inputs[i] = 0;
    }
  }
  esp_err_t result = esp_now_send(masterAddress, (uint8_t *) &message, sizeof(message));
   
  if (result == ESP_OK) {
    //Serial.println("Sent with success");
  }
  else {
    //Serial.println("Error sending the data");
  }
}
