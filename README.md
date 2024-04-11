ESP-32 TimerCam,M5TimerCAM board.
Functionalities: Capture photo + Wifi Connection + HTTP Post request to FastAPI server
Change the .fb_count, .grab_mode,.jpeg_quality, .frame_size accordingly, instead of using setFrameSize 

## Requirements
* M5Stack TimerCam Camera
* USB-C Cable
* Arduino IDE
## Note
When adjusting the frame size and jpeg quality, instead of using set functions of TimerCam.Camera.sensor, adjust those 2 variables by directly editing Camera_Class.cpp
