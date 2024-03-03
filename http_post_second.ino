/**
 * @file http_post.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief TimerCAM HTTP Post Test
 * @version 0.1
 * @date 2023-12-28
 *
 *
 * @Hardwares: TimerCAM
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * TimerCam-arduino: https://github.com/m5stack/TimerCam-arduino
 * ArduinoHttpClient: https://github.com/arduino-libraries/ArduinoHttpClient
 */

#include "M5TimerCAM.h"
#include <WiFi.h>
// #include <ArduinoHttpClient.h>
#include <HTTPClient.h>
const char ssid[] = "Wifi";
const char password[] = "Password";

String server =  "http://38ef-193-190-253-145.ngrok-free.app";
String path = "/image";
String fullUrl = server + path;
WiFiClient wifi;
HTTPClient http;


void setup() {
    TimerCAM.begin();

    if (!TimerCAM.Camera.begin()) {
        Serial.println("Camera Init Fail");
        return;
    }
    Serial.println("Camera Init Success");

    TimerCAM.Camera.sensor->set_pixformat(TimerCAM.Camera.sensor,
                                          PIXFORMAT_JPEG);
    TimerCAM.Camera.sensor->set_framesize(TimerCAM.Camera.sensor,
                                         FRAMESIZE_SVGA);
    // TimerCAM.Camera.sensor->set_quality(TimerCAM.Camera.sensor,8);
    TimerCAM.Camera.sensor->set_vflip(TimerCAM.Camera.sensor, 1);
    TimerCAM.Camera.sensor->set_hmirror(TimerCAM.Camera.sensor, 0);

    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    // Wait for connection
    // Initialize serial, camera, and WiFi as before
    while(WiFi.status()!=WL_CONNECTED){
        Serial.println("WIfi not connected yet");
        delay(500);
    }
    if(WiFi.status() == WL_CONNECTED){
      Serial.println("Wifi connected !!!!!!");
        http.begin(fullUrl); // Initialize HTTPClient with the URL
    }
    else{
      Serial.println("Wifi not connected");
    }
    } 
    
void loop() {
    if (TimerCAM.Camera.get()) {
        Serial.println("Making POST request");
         http.addHeader("Content-Type", "image/jpeg");
         //display_image(TimerCAM.Camera.fb->width, TimerCAM.Camera.fb->height, TimerCAM.Camera.fb->format, TimerCAM.Camera.fb->buf, TimerCAM.Camera.fb->len);
         //int httpResponseCode = http.POST((uint8_t*)TimerCAM.Camera.fb->buf, TimerCAM.Camera.fb->len);
          int httpResponseCode = http.POST(TimerCAM.Camera.fb->buf, TimerCAM.Camera.fb->len);
        //int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
          if(httpResponseCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpResponseCode);
  }}

else {
  Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
}

        http.end(); //Close connection
        Serial.println("Wait five seconds");
        TimerCAM.Camera.free();
        delay(5000);
    }
}





