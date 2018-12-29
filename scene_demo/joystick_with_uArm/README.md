# Joystick control uArm

The uArmController controls uArm Swift Pro to move and control gripper to catch somethings.

# How to connect the uArm
1.Connect the uArm Controller and uArm Swift Pro with Type-C.
(The program use the UART2-TTL interface)

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/Controller_uArm.jpg)

2.Plug in the uArm Swift Pro.

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/Plug_uArm.jpg)

3.Connect the uArm Controller and Computer with USB.

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/Controller_PC.jpg)

# How to use the demo
1. Download this project **joystick_with_uArm.ino**. 
   Learn how to download single file from GitHub [https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub](https://github.com/uArm-Developer/SwiftProForArduino/wiki/How-to-download-single-file-from-GitHub "url")

2. Conﬁgure Arduino IDE，select the board as "Arduino/Genuino Mega or Mega 2560", Select the COM that allocated randomly by your computer, please refer to the following picture:

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/tool_set.jpg)

3. Open the "Manage Libraries".

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/install_lib.jpg) 

4. Install u8glib.

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/u8glib.jpg)

5. Press the "Upload" button to upload ﬁrmware.

&nbsp;&nbsp;&nbsp;&nbsp;![](https://github.com/uArm-Developer/Controller/blob/master/scene_demo/joystick_with_uArm/image/upload.jpg)

6. Test, and use the Joystick to control the movement of uArm (i.e. move around); use the rotary potentiometer to control the up-and-down motion of uArm; press button C to adjust the speed; press button D to open/close the gripper.


Video URL：https://www.youtube.com/watch?v=gX0F5BUDXgE 