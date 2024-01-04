![logo](_static/rpistreamer_web_logo.png)



# **RpiStreamer**

**v1.1.0**





# Table of contents


- [Versions](#versions)
- [Overview](#1-overview)
- [Config file](#2-config-file)
- [Software Install](#3-software-install)
- [Raspberry PI 4 configuration](#4-raspberry-pi-4-configuration)



# Versions

**Table 1** - Library versions.

| Version | Release date | What's new     |
| ------- | ------------ | -------------- |
| 1.0.0   | 11.09.2023   | First version. |
| 1.1.0   | 19.09.2023   | VSourceLibCamera and VSourceOpenCv support is implemented. |




# 1. Overview

**RpiStreamer** is application to stabilise and stream video on the Raspberry Pi 4B platform. The application captures video frames, stabilize them, compress them efficiently using hardware acceleration in H.264 format, and streams using different frameworks (ffmpeg, gstreamer, v4l2rtspserver, etc.). The application offers flexibility in managing external streaming processes, allowing users to choose between popular tools such as GStreamer, FFmpeg, v4l2rtspserver etc, for video streaming. The application is delivered to customers as source code (including all libraries) with detailded documentation. The application can be uesed as template of video processing pipeline and can be easily modifyed. The application offers fast start with video processing on Raspberry PI. Application structure:

![structure](_static/rpistreamer_principle.png)

**RpiStreamer uses following libraries**:

[VSourceV4L2](https://github.com/ConstantRobotics-Ltd/VSourceV4l2) C++ library designed to capture video from V4L2 compatible video sources (MIPI camera, USB video capture cards, UDB cameras). However, VSourceLibCamera or VSourceOpenCv libraries are also available as video source. Selection of video source library is made by application automatically by checking provided video source name. Video source name examples :

**Table 2** - Examples of video source name.
| VSourceV4L2 | VSourceLibCamera | VSourceOpenCv |
| ----------- | ---------------- | ------------- |
| /dev/video0 (device file)  | 0 (camera number) | test.mp4 (video file) |

[VStabiliserOpenCv](https://github.com/ConstantRobotics-Ltd/VStabiliserOpenCv) C++ library perform video stabilisation.

[VCodecV4L2](https://github.com/ConstantRobotics-Ltd/VCodecV4L2) C++ library designed to compress video into the H.264 or JPEG format with hardware acceleration.

[VOutputV4L2](https://www.constantrobotics.com/voutputv4l2) C++ library designed to write compressed video (H.264 or JPEG) to virtual video device.  This virtual device acts as the endpoint for the stabilized and compressed video feed.

[ChildProcess](https://www.constantrobotics.com/childprocess) C++ library designed to run external process (video streaming v4l2rtspserver, ffmpeg or gstreamer).



# 2. Config file

**RpiStreamer** application reads config file **/home/pi/Config/RpiStreamer.json**. Config file content: 

```bash
{
    "Params": {
        "videoSource": {
            "custom1": 0.0,
            "custom2": 0.0,
            "custom3": 0.0,
            "exposureMode": 1,
            "focusMode": 1,
            "fourcc": "YU12",
            "fps": 60.0,
            "gainMode": 1,
            "height": 1080,
            "logLevel": 2,
            "source": "/dev/video0",
            "width": 1920
        },
        "videoStabiliser": {
            "aFilterCoeff": 0.8999999761581421,
            "aOffsetLimit": 10.0,
            "constAOffset": 0.0,
            "constXOffset": 0,
            "constYOffset": 0,
            "enable": true,
            "scaleFactor": 4,
            "transparentBorder": true,
            "type": 0,
            "xFilterCoeff": 0.8999999761581421,
            "xOffsetLimit": 250,
            "yFilterCoeff": 0.8999999761581421,
            "yOffsetLimit": 250
        },
        "videoStream": {
            "bitrateKbps": 2500,
            "command": "v4l2rtspserver",
            "fps": 10,
            "gopSize": 30,
            "h264Profile": 0,
            "params": "-W 1920 -H 1080 -F 60 -P 7031 /dev/video4",
            "videoDevice": "/dev/video4"
        }
    }
}
```

**Table 3** - Config file params.

| Parameter                         | type| Description                                                  |
| ----------------------------------|-----| ------------------------------------------------------------ |
| videoSource/logLevel     | int    | Logging mode. Values: 0 - Disable, 1 - Only file, 2 - Only terminal, 3 - File and terminal. |
| videoSource/source       | string | Video source: file, video stream, video device, camera num, etc. |
| videoSource/fourcc       | string | FOURCC: RGB24, BGR24, YUYV, UYVY, GRAY, YUV24, NV12, NV21, YU12, YV12. Value says to video source class which pixel format preferable for output video frame. Particular video source class can ignore this params during initialization. Parameters should be set before initialization. |
| videoSource/width        | int    | Frame width. User can set frame width before initialization or after. Some video source classes may set width automatically. |
| videoSource/height       | int    | Frame height. User can set frame height before initialization or after. Some video source classes may set height automatically. |
| videoSource/gainMode     | int    | Gain mode. Value depends on implementation but it is recommended to keep default values: 0 - Manual control, 1 - Auto. |
| videoSource/gain         | int    | Gain value. Value: 0(min for particular video source class) - 65535(max for particular video source class). |
| videoSource/exposureMode | int    | Exposure mode. Value depends on implementation but it is recommended to keep default values: 0 - Manual control, 1 - Auto. |
| videoSource/exposure     | int    | Exposure value. Value: 0(min for particular video source class) - 65535(max for particular video source class). |
| videoSource/focusMode    | int    | Focus mode. Value depends on implementation but it is recommended to keep default values: 0 - Manual control, 1 - Auto. |
| videoSource/focusPos     | int    | Focus position. Value: 0(full near) - 65535(full far).       |
| videoSource/cycleTimeMks | int    | Video capture cycle time. **VSource** class sets this value automatically. This parameter means time interval between two captured video frame. |
| videoSource/fps          | float  | FPS. User can set frame FPS before initialization or after. Some video source classes may set FPS automatically. |
| videoSource/isOpen       | bool   | Open flag. false - not open, true - open.                    |
| videoSource/custom1      | float  | Custom parameter. Depends on implementation.                 |
| videoSource/custom2      | float  | Custom parameter. Depends on implementation.                 |
| videoSource/custom3      | float  | Custom parameter. Depends on implementation.                 |
| videoStabiliser/scaleFactor                             | int   | Scale factor. Value: If 1 the library will process original frame size, if 2 the library will scale original frame size by 2, if 3 - by 3. VStabiliserOpenCv class supports 2D FFT algorithm which scales input image to wise 512x512 or 256x256 depends on scale factor. To chose particular size (512x512 or 256x256) the library devide input frame height by scale factor. If result >= 512 the library will use 512x512 size for internal algorithms. Otherwise the library will use 256x256 size. |
| videoStabiliser/xOffsetLimit                            | int   | Maximum horizontal image shift in pixels per video frame. If image shift bigger than this limit the library will compensate only xOffsetLimit shift. |
| videoStabiliser/yOffsetLimit                            | int   | Maximum vertical image shift in pixels per video frame. If image shift bigger than this limit the library will compensate only yOffsetLimit shift. |
| videoStabiliser/aOffsetLimit                            | float | Maximum rotational image angle in radians per video frame. If image absolute rotational angle bigger than this limit the library will compensate only aOffsetLimit angle. |
| videoStabiliser/xFilterCoeff                            | float | Horizontal smoothing coefficient of constant camera movement. Values [0-1]: 0 - the library will not compensate for constant camera motion, video will not be stabilized, 1 - no smoothing of constant camera motion (the library will compensate for the current picture drift completely without considering constant motion). **If set 0 the library will detect necessary coefficients automatically.** |
| videoStabiliser/yFilterCoeff                            | float | Vertical smoothing coefficient of constant camera movement. Values [0-1]: 0 - the library will not compensate for constant camera motion, video will not be stabilized, 1 - no smoothing of constant camera motion (the library will compensate for the current picture drift completely without considering constant motion). **If set 0 the library will detect necessary coefficients automatically.** |
| videoStabiliser/aFilterCoeff                            | float | Rotational smoothing coefficient of constant camera movement. Values [0-1]: 0 - the library will not compensate for constant camera motion, video will not be stabilized, 1 - no smoothing of constant camera motion (the library will compensate for the current picture drift completely without considering constant motion). **If set 0 the library will detect necessary coefficients automatically.** |
| videoStabiliser/enable                                  | bool  | Enable/disable stabilisation.                                |
| videoStabiliser/transparentBorder                       | bool  | Enable/disable transparent borders.                          |
| videoStabiliser/constXOffset                            | int   | Constant horizontal image offset in pixels. The library will add this offset to each processed video frame. This values used for boresight correction. |
| videoStabiliser/constYOffset                            | int   | Constant vertical image offset in pixels. The library will add this offset to each processed video frame. This values used for boresight correction. |
| videoStabiliser/constAOffset                            | float | Constant rotational angle in radians. The library will add this offset to each processed video frame. This values used for boresight correction. |
| videoStabiliser/instantXOffset                          | int   | Value of horizontal offset (pixels) implemented to last processed video frame. |
| videoStabiliser/instantYOffset                          | int   | Value of vertical offset (pixels) implemented to last processed video frame. |
| videoStabiliser/instantAOffset                          | int   | Value of rotation angle (radians) implemented to last processed video frame. |
| videoStabiliser/type                                    | int   | Three types of stabilisation algorithm are implemented in the library:<br />**0 -** **2D based on FFT**. Fastest algorithm but only for 2D stabilisation. Works stable for low light conditions and for low contrast images.<br />**1 -** **2D based on optical flow**. Gives good accuracy but lower speed as 2D FFT and requires contrast objects on video.<br />**2 -** **3D based on optical flow**. Gives best accuracy but lower speed as 2D FFT and requires contrast objects on video. |
| videoStream/bitrateKbps       | int       | Bitrate for streaming in kbit/s.                             |
| videoStream/command           | string    | Command for streamer such as v4l2rtspserver.                 |
| videoStream/fps               | int       | fps of encoding and stream.                                  |
| videoStream/gopSize           | int       | gop (group of picture) size for h264 encoding.               |
| videoStream/h264Profile       | int       | H264 profile: 0 - Baseline, 1 - Main, 2 - High.              |
| videoStream/params            | string    | Parameters for streaming application.                        |
| videoStream/videoDevice       | string    | Virtual video device name such as /dev/video4.               |



# 3. Software install



**3.1.** Connect to raspberry via SSH: **ssh pi@raspberrypi**. **WARNING:** If you work with Windows we recommend delete information about previous connections. Go to folder **C:/Users/[your user name]/.ssh**. Open file **known_hosts** is exists in text editor. Delete all lines **“raspberrypi”**.

**3.2.** Create necessary folders (App, Config and Log) in home directory (**/home/pi**):

```bash
mkdir App
mkdir Config
mkdir Log
```

**3.3.** Copy application **RpiStreamer** to folder **/home/App**.

**3.4.** Run application first time to create config file.

```bash
cd /home/pi/App
sudo chmod +x RpiStreamer
sudo ./RpiStreamer  or  sudo ./RpiStreamer -v
```

After first start the application will create config file **/home/pi/Config/RpiStreamer.json** (see **Software configuration** section) with default parameters. After each start application creates virtual video devices: **/dev/video4**, **/dev/video5** and **/dev/video6**. If you run application not from user you will be asked about **sudo** password.

**3.5.** You can run application manually or you can add application to auto start as **systemd** servive. To add application as **systemd** service create service file:

```bash
sudo nano /etc/systemd/system/rpistreamer.service
```

and add content:

```bash
[Unit]
Description=RpiStreamer

Wants=network.target
After=syslog.target network-online.target

[Service]
Type=simple
ExecStart=/home/pi/App/RpiStreamer
Restart=on-failure
RestartSec=10
KillMode=control-group
KillSignal=SIGTERM
[Install]
WantedBy=multi-user.target
```

**3.6.** Save **ctrl + s** and close **ctrl + x**.

**3.7.** Reload **systemd** services:

```bash
sudo systemctl daemon-reload
```

**3.8.** Command to control service:

Start service:

```bash
sudo systemctl start rpistreamer
```

Enable for auto start:

```bash
sudo systemctl enable rpistreamer
```

Stop service:

```bash
sudo systemctl stop rpistreamer
```

Check status:

```bash
sudo systemctl status rpistreamer
```



# 4. Raspberry PI 4 configuration



## 4.1. OS install

**4.1.1.** Download [**Raspberry PI imager**](https://www.raspberrypi.com/software/).

**4.1.2.** Choose Operating System: Raspberry Pi OS (other) -> Raspberry Pi OS Lite (64-bit)

**4.1.3.** Choose storage (MicroSD) card. If it possible use 128 GB MicroSD.

**4.1.4.** Set additional options: do not set hostname “raspberrypi.local”, enable SSH (Use password authentication), set username **"pi"** and password **"pi"**, configure wireless LAN according your settings. You will need wi-fi for software installation, set appropriate time zone and wireless zone.

**4.1.5.** Save changes and push “Write” button. After push “Yes” to rewrite data on MicroSD. At the end remove MicroSD.

**4.1.6.** Insert MicroSD in Raspberry and power up Raspberry.



## 4.2. LAN configuration

**4.2.1.** Configure LAN IP address on your PC. For Windows 11 got to Settings -> Network & Internet -> Advanced Network Settings -> More network adapter options. Click right button on LAN connection used to connect to Raspberry PI and chose “Properties”. Double click on “Internet Protocol Version 4 (TCP/IPv4)”. Set static IP address 192.168.0.1 and mask 255.255.255.0.

**4.2.2.** Connect raspberry via LAN cable. After power up you don’t know IP address of Raspberry board but you can connect to raspberry via SSH using “raspberrypi” name. In Windows 11 open windows terminal or power shell terminal and type command **ssh pi@raspberrypi**. After connection type yes to establish authenticity. **WARNING:** If you work with Windows we recommend delete information about previous connections. Go to folder **C:/Users/[your user name]/.ssh**. Open file **known_hosts** is exists in text editor. Delete all lines **“raspberrypi”**.

**4.2.3.** You have to set static IP address in Raspberry PI but not **NOW**. After static IP set you will lose wi-fi connection which you need for software installation.



## 4.3. Install updates and dependencies

**4.3.1.** Connect to raspberry via SSH: **ssh pi@raspberrypi**. **WARNING:** If you work with Windows we recommend delete information about previous connections. Go to folder **C:/Users/[your user name]/.ssh**. Open file **known_hosts** is exists in text editor. Delete all lines **“raspberrypi”**.

**4.3.2.** Update system:

```bash
sudo apt-get update
sudo apt-get -y upgrade
sudo apt-get dist-upgrade
sudo apt install raspberrypi-kernel-headers
sudo reboot
```

*Note* : If you upgraded your kernel version (for example rpi-upgrade) after installing kernel headers, it is recommended to remove kernel headers and then reinstall.

**4.3.3.** Connect to raspberry via SSH **ssh pi@raspberrypi** after reboot. **WARNING:** If you work with Windows we recommend delete information about previous connections. Go to folder **C:/Users/[your user name]/.ssh**. Open file **known_hosts** is exists in text editor. Delete all lines **“raspberrypi”**.

**4.3.4.** Install additional software (if some libs not supported juts remove them from command):

```bash
sudo apt-get -y install build-essential cmake libx264-dev libjpeg-dev ninja-build git meson
sudo apt-get -y install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
sudo apt-get install libopencv-dev
sudo apt-get -y install ffmpeg libavcodec-dev libavutil-dev libavformat-dev libavdevice-dev libavfilter-dev
sudo apt-get -y install v4l2loopback-utils
```

**4.3.5.** Install **v4l2rtspserver** application for first tests. Link for software and instructuions: [v4l2rtspserver](https://github.com/mpromonet/v4l2rtspserver).



## 4.4. Setup hight perfomance mode

**4.4.1.** Open config file:

```bash
sudo nano /boot/config.txt
```

**4.4.2.** Add line at the end of file:

```bash
force_turbo=1
arm_freq=2000
arm_freq_min=2000
over_voltage=6
```

**4.4.2.** Save changes **ctrl+s** and close **ctrl+x**. Reboot raspberry **sudo reboot**.



## 4.5. V4L2 camera stack configuration

RpiStreamer works with V4L2 compatible cameras. To enable legacy camera support in Raspberry PI you have to change system settings.

**4.5.1.** Run configuration manager:

```bash
sudo raspi-config
```

**4.5.2.** Select “Interface Options” -> “Legacy camera”. After select **yes**.

**4.5.3.** Go to **Finish** menu and close configuration manager.

**4.5.4.** Reboot raspberry **sudo reboot**.



## 4.6. Static IP configuration on Raspberry.

**4.6.1.** Connect to raspberry via SSH **ssh pi@raspberrypi** after reboot. **WARNING:** If you work with Windows we recommend delete information about previous connections. Go to folder **C:/Users/[your user name]/.ssh**. Open file **known_hosts** is exists in text editor. Delete all lines **“raspberrypi”**.

**4.6.2.** Open config file:

```bash
sudo nano /etc/dhcpcd.conf
```

**4.6.3.** Go dawn to file and delete the comments in the following lines and set IP 192.168.0.2:

```bash
interface eth0
static ip_address=192.168.0.2/24
static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=192.168.0.2
static domain_name_servers=192.168.0.2 8.8.8.8 fd51:42f8:caae:d92e::1
```

**4.6.4.** Save changes **ctrl + s** and exit **ctrl + x**. Reboot after **sudo reboot**.

**4.6.5.** After configuring static IP you can connect to to raspberry by IP.

```bash
ssh pi@192.168.0.2
```
