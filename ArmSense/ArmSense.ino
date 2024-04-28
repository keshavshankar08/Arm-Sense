#include <Arduino.h>
#include <BluetoothSerial.h>

int EMG_Module_Pins[6] = {25, 4, 26, 14, 27, 32};
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ArmSense");
  SerialBT.setPin("9999");
}

void loop() {
  int EMG_Module_Values[6];
  for (int i = 0; i < 6; i++) {
    EMG_Module_Values[i] = analogRead(EMG_Module_Pins[i]);
  }

  String SensorData = String(EMG_Module_Values[0]) + "," + 
                      String(EMG_Module_Values[1]) + "," + 
                      String(EMG_Module_Values[2]) + "," + 
                      String(EMG_Module_Values[3]) + "," + 
                      String(EMG_Module_Values[4]) + "," + 
                      String(EMG_Module_Values[5]) + ".";
  
  SerialBT.println(SensorData);
  Serial.println(SensorData);
  delay(10);
}
