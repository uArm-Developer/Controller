# Snake game

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/snake_game/image/Poster.jpg)
 
## How to upload firmware
###1.Using Arduino IDE
1. Download this project [**snake_game.ino**](src/). 
   Learn how to download single file from GitHub [https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub](https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub "url")

2. Conﬁgure Arduino IDE，select the board as "Arduino/Genuino Mega or Mega 2560", Select the COM that allocated randomly by your computer, please refer to the following picture:

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/snake_game/image/tool_set.jpg)

3. Press the "Upload" button to upload ﬁrmware.

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/snake_game/image/upload.jpg)
###2.Using XLoadr
* Download the [hex](hex/)
* Download and extract [XLoader](http://xloader.russemotto.com/XLoader.zip).
* Open XLoader and select your uArm's COM port from the drop down menu on the lower left.
* Select the appropriate device from the dropdown list titled "Device".
* Check that Xloader set the correct baud rate for the device: 115200 for Mega (ATMEGA2560).
* Now use the browse button on the top right of the form to browse to your hex file.
* Once your hex file is selected, click "Upload"
The upload process generally takes about 10 seconds to finish. Once completed, a message will appear in the bottom left corner of XLoader telling you how many bytes were uploaded. If there was an error, it would show instead of the total bytes uploaded. Steps should be similar and may be done through the command prompt.

## How to use the demo

**1.Press the "Reset" button, reset the system.**

**2.Use the Joystick to control the movement (e.g. move around,up and down) when playing the snake game.**