 🔒 Arduino Alpha Board Security System — Intrusion Detection

This project implements an effective security system using the Arduino Alpha Board. It features intrusion detection based on light and temperature sensors, status LEDs, a buzzer, and manual arm/disarm buttons. The system detects abnormal environmental conditions and triggers both visual and audio alerts.



 📦 Components Used

 Component                Description                                                               

 Arduino Alpha Board      Main microcontroller                                                 
 LED (Red)                Indicates the system is **armed**                                    
 LED (Green)              Indicates the system is **disarmed**                                 
 LED (Yellow)             Signals active surveillance and alerts                               
 Buzzer                   Sounds in both **armed** and **alert** states                        
 Light Sensor (LDR)       Detects ambient light level                                          
 Temperature Sensor       Detects environmental temperature                                    
 Push Buttons             Used to arm or disarm the system                                     
 IR Transmitter/Receiver  Reserved for future intrusion detection using beam break or motion logic 



 🚦 System Behavior

 ✅ Armed

 Triggered when:
Arm button is pressed (`analogRead ≈ 1023`)
Ambient light is low (value ≤ `LIGHT_THRESHOLD`)
 System enters active surveillance mode:

Red LED turns ON
Yellow LED turns ON
 Buzzer is activated
 Sensor readings are continuously monitored.


 ❌ Disarmed
Triggered when:

  Disarm button is pressed
  OR Arm button is not pressed
  Green LED turns ON
Red, Yellow LEDs and buzzer are OFF
 Sensor input is ignored.

 ⚠️ Alert / Intrusion Detection

Active only while the system is armed, and:

  Light level rises above `LIGHT_THRESHOLD` (e.g., flashlight intrusion)
  Temperature drops below `TEMP_THRESHOLD` (environmental anomaly)
  Yellow LED blinks
Buzzer pulses to signal an alert condition



 🔧 Thresholds & Calibration

Tune the system sensitivity using these constants:


const int LIGHT_THRESHOLD = 100;  // Lower = more sensitive to brightness
const int TEMP_THRESHOLD  = 500;  // Lower = more tolerant to cold


 📏 Calibration Steps

1. Upload the code and open the Serial Monitor.
2. Record values of `lightVal` and `tempVal` under:

 Normal (safe) conditions
 Alert-triggering (e.g., bright light, cold air) conditions
3. Adjust the thresholds:

 Increase `LIGHT_THRESHOLD` to reduce sensitivity to ambient light.
 Decrease `TEMP_THRESHOLD` to avoid false alarms in cooler environments.

 Example:

If `lightVal` reads \~150 normally and \~500 with a flashlight:

cpp
const int LIGHT_THRESHOLD = 400;




 🛠️ Future Enhancements

 Add IR-based intrusion detection
 Display sensor data and system status  
 Implement remote alerts using Wi-Fi or Bluetooth
 Save system state 



