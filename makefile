# Make file for test
#

COMPFLAGS =  -Wall -std=c++11 -Os -ffunction-sections -fdata-sections -Wl,--gc-sections 
LINKFLAGS =  -Wall -std=c++11 -Os -ffunction-sections -fdata-sections -Wl,-rpath=. -Wl,--gc-sections -L.



all: sender receiver

.PHONY: all debug


debug: COMPFLAGS = -g -std=c++14
debug: LINKFLAGS = -g -std=c++14
debug: sender receiver


sender: sender.o
	c++ $(LINKFLAGS) -o sender sender.o \
	-lsoc -l96BoardsGPIO \
	-losiot -lxerces-c -lcurl -lpthread \
	


sender.o: sender.cxx
	c++ $(COMPFLAGS) -c sender.cxx 

receiver: receiver.o
	c++ $(LINKFLAGS) -o receiver receiver.o \
	-lsoc -l96BoardsGPIO \
	-losiot -lxerces-c -lcurl -lpthread \



receiver.o: receiver.cxx
	c++ $(COMPFLAGS) -c receiver.cxx
