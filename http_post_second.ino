/**
 * @file http_post_second.ino
 * @author Eltaj Amirli
 * @brief TimerCAM HTTP POST and polling
 * @version 0.1
 * @date 2024-04-11
 *
 *
 * @Hardwares: TimerCAM
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * TimerCam-arduino: https://github.com/m5stack/TimerCam-arduino
 * Espressif-esp32-camera: https://github.com/espressif/esp32-camera
 */


#include "M5TimerCAM.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "TP-Link_E740";
const char* password = "69762765";
// const char* ssid = "Galaxy Note102f5e";
// const char* password = "gnsc1386";
String fullUrl = "http://martin-upward-lately.ngrok-free.app/image";
String captureUrl = "http://martin-upward-lately.ngrok-free.app/should_capture";
WiFiClient wifi;
HTTPClient http;


void setup() {
    TimerCAM.begin();

    if (!TimerCAM.Camera.begin()) {
        Serial.println("Camera Init Fail");
        return;
    }
    Serial.println("Camera Init Success");

    // TimerCAM.Camera.sensor->set_pixformat(TimerCAM.Camera.sensor,
    //                                       PIXFORMAT_JPEG);
    // TimerCAM.Camera.sensor->set_framesize(TimerCAM.Camera.sensor,
                                        //  FRAMESIZE_SVGA);
    //SVGA
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
        // http.begin(fullUrl); // Initialize HTTPClient with the URL
    }
    else{
      Serial.println("Wifi not connected");
    }
    } 


bool shouldCapture() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient httpCapture;
        httpCapture.begin(captureUrl); // Start connection to check the capture command
        int httpCode = httpCapture.GET(); // Send the GET request

        if (httpCode == HTTP_CODE_OK) {
            String payload = httpCapture.getString(); // Get the request response payload
            httpCapture.end(); // Close the connection

            // Parse the JSON response to check "capture_now"
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, payload);
            bool capture_now = doc["capture_now"]; // Extract the capture_now value

            return capture_now;
        } else {
            Serial.printf("Failed to check capture status, HTTP code: %d\n", httpCode);
            httpCapture.end(); // Ensure the connection is closed even if there was an error
            return false;
        }
    }
    return false;
}


bool initializeCamera() {
// Attempt to initialize the camera
    if (!TimerCAM.Camera.begin()) {
        Serial.println("Camera bool Init Fail");
        return false; // Camera initialization failed
    }
    

    Serial.println("Camera bool Init Success");
    // TimerCAM.Camera.sensor->set_pixformat(TimerCAM.Camera.sensor, PIXFORMAT_JPEG);
    // TimerCAM.Camera.sensor->set_framesize(TimerCAM.Camera.sensor, FRAMESIZE_SVGA);
    TimerCAM.Camera.sensor->set_vflip(TimerCAM.Camera.sensor, 1);
    TimerCAM.Camera.sensor->set_hmirror(TimerCAM.Camera.sensor, 0);
    
    return true; // Camera initialized successfully
}

void loop() {
    // Ensure WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected. Attempting to reconnect...");
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            delay(500);
        }
        Serial.println("Reconnected to WiFi.");
    }

    // Check if it's time to capture
    if (shouldCapture()) {
        Serial.println("Capture command received.");
        
        if (!TimerCAM.Camera.get()) {

          initializeCamera();
          TimerCAM.Camera.get();
      }
       else{
            Serial.println("Making POST request");
            http.begin(fullUrl); // Ensure HTTP is initialized for the image post endpoint
            http.addHeader("Content-Type", "image/jpeg");
            int httpResponseCode = http.POST(TimerCAM.Camera.fb->buf, TimerCAM.Camera.fb->len);

            if (httpResponseCode > 0) {
                Serial.printf("[HTTP] POST... code: %d\n", httpResponseCode);
            } else {
                Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
            }

            http.end(); // Close connection
            TimerCAM.Camera.free(); // Free the camera frame buffer
       }
        Serial.println("Wait five seconds");
        delay(1000); // Delay before the next loop iteration
    } else {
      
        Serial.println("No capture command. Checking again soon.");
        delay(3000); // Delay a bit longer if not capturing
    }
}










