# Vision scratch cube
# caution
The firmware of uArm Swift Pro must  to be  [UArmSwiftPro_2ndUART.hex](http://download.ufactory.cc/developer/swift/uArm_Swift_Pro_2nd_uart_Firmware_20180724.zip).
# Software
1.[Arduino IDE](www.arduino.cc)

2.[OpenMV IDE](www.openmv.io)

3.[Vision.ino](https://github.com/uArm-Developer/Controller/tree/master/scene_demo/vision_scratch%20cube/code%20for%20Controller/controller-vision) for Controller

4.[Color_tracking_test.py](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/code%20for%20openmv/color_tracking_test.py) for OpenMV 

5.[UArmSwiftPro_2ndUART.hex](http://download.ufactory.cc/developer/swift/uArm_Swift_Pro_2nd_uart_Firmware_20180724.zip) for uArm

#Download

**You can download the code by two ways**.
 
***One of ways to download the code***(This way can not change the code ):

1.Download the [hex](https://github.com/uArm-Developer/Controller/tree/master/scene_demo/vision_scratch%20cube/hex) named controller-vision.ino.hex，Click [this](https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub) to learn how to download single file from GitHub..

2.Download and extract [XLoader](http://xloader.russemotto.com/XLoader.zip).

3.Open XLoader and select your controller's COM port from the drop down menu on the lower left.

4.Select the appropriate device from the dropdown list titled "Device".

5.Check that Xloader set the correct baud rate for the device: 115200 for Mega (ATMEGA2560).

6.Now use the browse button on the top right of the form to browse to your hex file.

7.Once your hex file is selected, click "Upload" The upload process generally takes about 3 seconds to finish. Once completed, a message will appear in the bottom left corner of XLoader telling you how many bytes were uploaded. If there was an error, it would show instead of the total bytes uploaded. Steps should be similar and may be done through the command prompt.

![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/img/xloder.png)

***The other way to download the code***:
(If you want to change the code in the firmware, you need to download the firmware in the following way)

1.Download the project  [vision_scratch cube](https://github.com/uArm-Developer/Controller/tree/master/scene_demo/vision_scratch%20cube). 
Click [this](https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub) to learn how to download single directory from GitHub.

2.Conﬁgure Arduino IDE，select the board as "Arduino/Genuino Mega or Mega 2560", Select the COM that allocated randomly by your computer, please refer to the following picture:
 
 ![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/img/download(1).png)

3.Open the "Manage Libraries".

![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/img/library(1).png)

4.Install u8glib.

![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/img/library(2).png)

5.Press the "Upload" button to upload ﬁrmware.

![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/img/download(2).png)

# Connect
![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/vision_scratch%20cube/img/connect.jpg)

# Getting Started
The firmware of uArm Controller has been written before leaving the factory.

Finish the work with connecting  cable and give power.