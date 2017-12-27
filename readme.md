# Software for demo of ATIS OS-IoT library for ARIB-TTC Developer Tutorial Seminar, 2018

## Overview

This repository contains the source code used for the OS-IoT Demo at ARIB-TTC Developer Tutorial Seminar, 2018. This demo is based on the source code used for the OS-IoT Demo at ETSI IoT week, 2017 developed by ATIS with minor modifications.

The demo consists four applications:
1. A oneM2M sender, running on a DragonBoard 410C, which acts as a light switch.
2. A oneM2M receiver, also running on a DragonBoard 410C, which acts as a controlled light.
3. A oneM2M CSE running on a DragonBoard 410c. For the demo the Eclipse OM2M IN-CSE version 1.1.0 was used in its default configuration except for the cseBaseAddress.

The first two elements are all applications build using the ATIS OS-IoT library and the source code
for these is contained in this repository. 

### Demo Operation

The receiver creates oneM2M AE and container resources in the CSE and create a subscription to the container.

When a button is pressed on the "sender" a new oneM2M contentInstance resrouce is created in the containers belonging to the receiver.
This causes a notification to these entities which can change the state of the lights they are controlling.

### Demo Configuration

The files in this repository are configured for the hardware and network configuration used in the demo, which is shown below:

```
IP Addr            Node
192.168.11.16      Linaro Debian Linux DragonBoard 410C running the CSE
192.168.11.17      Linaro Debian Linux DragonBoard 410C running the receiver
192.168.11.15      Linaro Debian Linux DragonBoard 410C running the sender 
```

### Demo Limitations

The demo aims to show the use of OS-IoT to read and write oneM2M resources. It does not attempt to include all aspects of a real application. In particular note that:
1. The CSE should be run before any of the clients (sender and receiver). Real applications should be flexible in terms of sequencing.
2. The code assumes static addressing for nodes read from configuration files. In real applications addresses would be discovered or configured by other means.
3. The sender is statically bound to particular receivers by the code. In real applications a GUI would be provided to manage the association between controllers and receivers.
4. In this version no security is applied.

## Building and Running The Applications (sender and receiver)

The code for the sender and receiver are contained in the root directory of this repository. ATIS OS-IoT library and other required files are NOT included in this repository. Those should be build separately using OS-IoT.

Build and Install OS-IoT:

https://www.os-iot.org/build-and-install/

Once you build OS-IoT, then you can clone this repository.

git clone https://github.com/nuchida/arib-ttc-2018-02-02-demo

Then you need to create libraryies and copy it along with the other files to the repository folder you created above.

https://www.os-iot.org/documentation/linking-with-your-own-applications/

To build the applications you should first install the dependencies and then use ```make``` from the appropriate directory.

The demo can be run by starting the executable files created by the make, e.g. ```sudo ./sender```. Note that the CSE must be running before the clients are started. Note also that ```sender``` and ```receiver``` require superuser privs (start with sudo) as they write directly to hardware.

### Dependencies

#### Sender and Receiver

You will need to install 96BoardsGPIO and its depenencies.

```
# Libsoc
sudo apt-get install libsoc-dev
# Build tools
sudo apt-get install automake libtool
```

96BoardsGPIO from:

https://github.com/96Boards/96BoardsGPIO

(Note: Skip the lobsoc installation step, just install 96BoardsGPIO)


## Sender and Receiver Hardware

For a general introduction on using DragonBoard 410C GPIO see:

https://www.96boards.org/blog/access-gpio-pins-programmatically/

(though some of this information is a little out of date)

For GPIO connector pin-out see:

https://developer.qualcomm.com/download/db410c/gpio-usage-low-speed-connector-application-note.pdf

(note that the software info in this document is for Android rather than Linaro Debian).

For this demo, 96Boards Sensor Mezzanine Board is used so that we can use Grove sensors.
https://github.com/96boards/Sensor_Mezzanine_Getting_Started/blob/master/README.md

For the sender, a push-button should be connected to AB connector on the 96Boards Sensor Mezzanine Board.

For the receiver, an LED should be connected to AB connector on the 96Boards Sensor Mezzanine Board..

## Configuration Files

```
sender_settings.txt
Line 1: Address and port of CSE

receiver_settings.txt
Line 1: Address and port of CSE
Line 2: URL for the sender's web server (for subscription notifications)

```


## LICENSE
Please see the files ```LICENSE.md``` in this package for the licensing terms and the requirements
