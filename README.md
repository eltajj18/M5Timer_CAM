# M5Stack TimerCam Capture, Post and Polling to FastAPI server project

## Requirements
* M5Stack TimerCam Camera
* USB-C Cable
* Arduino IDE

## Functionalities
* Wi-Fi Connection
* Capturing a photo
* HTTP polling
* HTTP POST request
## FlowChart

![EE3-ESP32-Camera](https://github.com/eltajj18/M5Timer_CAM/assets/100543589/42a8bc26-7f73-42b8-aba2-887205f67f0a)

## Note
* When adjusting the frame size and jpeg quality, instead of using set functions of TimerCam.Camera.sensor, adjust those 2 variables (.jpeg_quality, .frame_size) by directly editing Camera_Class.cpp
* Remember to adjust the grab_mode as well :     .grab_mode     = CAMERA_GRAB_LATEST
* By doing so, you will avoid infamous green blurred image one get when capturing the image using TimerCam after the device goes into wakeup mode.
## Libraries
* I am using <a href = "https://github.com/m5stack/TimerCam-arduino">M5Stack TimerCam Arduino library </a> and <a href ="https://github.com/espressif/esp32-camera">Espressif esp32-camera library</a>

