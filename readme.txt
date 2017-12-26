Demo of ATIS OS-IoT library for ETSI IoT Week, 2017

This software is intended to run on a Dragonboard 410C

Dependencies

# Libsoc
sudo apt-get install libsoc-dev
# Build tools
sudo apt-get install automake libtool

96BoardsGPIO from:
https://github.com/96Boards/96BoardsGPIO
(Note: Skip the lobsoc installation step, just install 96BoardsGPIO)

ATIS OS-IoT library. See:
http://os-iot.org/
Note that this repo already includes a pre-built library for the Dragonboard architecture.


Configuration

sender_settings.txt
Line 1: Address and port of CSE
Line 2: URL for the sender's web server (for subscription notifications)

receiver_settings.txt
Line 1: Address and port of CSE

