# Slider

 # Caution
 **The firmware of uArm Swift Pro must upgrade to V4.3.0 or later.**
# Software
01.[Arduino IDE](http://www.arduino.cc/)

02.[slider.ino](https://github.com/uArm-Developer/Controller/tree/master/scene_demo/slider/src/slider) for Controller 

03.[uArmPro_V4.X.X.hex](https://github.com/uArm-Developer/SwiftProForArduino/tree/Version_V4.0/hex) for uArm

 #  Download
You can download the code by two ways.
 
One of ways to download the code:
 
1.Download the project  [slider](https://github.com/uArm-Developer/Controller/tree/master/scene_demo/slider). 
Click [this](https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub) to learn how to download single directory from GitHub.

2.Conﬁgure Arduino IDE，select the board as "Arduino/Genuino Mega or Mega 2560", Select the COM that allocated randomly by your computer, please refer to the following picture:
 
 ![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/slider/img/download(1).png)
 
3.Press the "Upload" button to upload ﬁrmware.

![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/slider/img/download(2).png)

The other way to download the code:

1.Download the [hex](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/slider/hex/slider.ino.hex).

2.Download and extract [XLoader](http://xloader.russemotto.com/XLoader.zip).

3.Open XLoader and select your controller's COM port from the drop down menu on the lower left.

4.Select the appropriate device from the dropdown list titled "Device".

5.Check that Xloader set the correct baud rate for the device: 115200 for Mega (ATMEGA2560).

6.Now use the browse button on the top right of the form to browse to your hex file.

7.Once your hex file is selected, click "Upload" The upload process generally takes about 3 seconds to finish. Once completed, a message will appear in the bottom left corner of XLoader telling you how many bytes were uploaded. If there was an error, it would show instead of the total bytes uploaded. Steps should be similar and may be done through the command prompt.
# Connect
1.Sensor cable connection

 ![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/slider/img/connecting%20with%20module.jpg)
 
2.Connect uArm Swift Pro Communication interface and the power supply cable
 
 ![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/slider/img/connecting%20with%20uarm.jpg)
 
# Getting Started
The firmware of uArm Controller has been written before leaving the factory.

Finish the work with connecting  cable and give power.

refer to [document](https://github.com/uArm-Developer/Controller/tree/master/scene_demo/slider/doc)