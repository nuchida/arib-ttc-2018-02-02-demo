Demo of ATIS OS-IoT library for ARIB-TTC oneM2M Developer Tutorial Seminar 2018.

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
Note that this repo only contains demo application source files.


Configuration

sender_settings.txt
Line 1: Address and port of CSE

receiver_settings.txt
Line 1: Address and port of CSE
Line 2: URL for the sender's web server (for subscription notifications)
