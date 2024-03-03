/**
 * @file capture.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief TimerCAM Take Photo Test
 * @version 0.1
 * @date 2023-12-28
 *
 *
 * @Hardwares: TimerCAM
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * TimerCam-arduino: https://github.com/m5stack/TimerCam-arduino
 */
#include "M5TimerCAM.h"

void setup() {
  //Baud Rate is 300
    TimerCAM.begin();

    if (!TimerCAM.Camera.begin()) {
        Serial.println("Camera Init Fail");
        return;
    }
    Serial.println("Camera Init Success");
    Serial.printf("sensor : %d\n",TimerCAM.Camera.sensor->status.framesize);
    TimerCAM.Camera.sensor->set_pixformat(TimerCAM.Camera.sensor,
                                          PIXFORMAT_JPEG);
    TimerCAM.Camera.sensor->set_framesize(TimerCAM.Camera.sensor,
                                          FRAMESIZE_VGA);
    Serial.printf("sensor : %d\n",TimerCAM.Camera.sensor->status.framesize);

//USE VGA FOR 4:3 
    TimerCAM.Camera.sensor->set_vflip(TimerCAM.Camera.sensor, 1);
    TimerCAM.Camera.sensor->set_hmirror(TimerCAM.Camera.sensor, 0);
}

void loop() {

//TimerCam.Camera.get() captures the image
    if (TimerCAM.Camera.get()) {
        Serial.printf("pic size: %d\n", TimerCAM.Camera.fb->width);
        TimerCAM.Camera.free();
    }
    else{
      Serial.println("Failed to Capture");
    }
}


