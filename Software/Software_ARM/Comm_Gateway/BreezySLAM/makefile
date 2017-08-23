# Makefile : builds libbreezyslam.so C++ library
#
# Original File from: 
# Copyright (C) Simon D. Levy 2014
#
# File was changed for Garfield-Project.
#
# This code is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as 
# published by the Free Software Foundation, either version 3 of the 
# License, or (at your option) any later version.
#
# This code is distributed in the hope that it will be useful,     
# but WITHOUT ANY WARRANTY without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License 
#  along with this code.  If not, see <http:#www.gnu.org/licenses/>.
#  You should also have received a copy of the Parrot Parrot AR.Drone 
#  Development License and Parrot AR.Drone copyright notice and disclaimer 
#  and If not, see 
#   <https:#projects.ardrone.org/attachments/277/ParrotLicense.txt> 
# and
#   <https:#projects.ardrone.org/attachments/278/ParrotCopyrightAndDisclaimer.txt>.


# Where you want to put the library
LIBDIR = .

CPPPATH = C:/Users/bauma/hspII_workplace/Software/Software_ARM/Comm_Gateway/BreezySLAM/cpp/
CPATH   = C:/Users/bauma/hspII_workplace/Software/Software_ARM/Comm_Gateway/BreezySLAM/c/

# Set library extension based on ARM architecture (=architecture of vehicle)
CFLAGS = -fPIC
LIBEXT = so

ARCH = armv7l

# Set SIMD compile params based on ARM architecture (=architecture of vehicle)
SIMD_FLAGS = -mfpu=neon


all: libbreezyslam.$(LIBEXT)

test: breezytest
	./breezytest


libbreezyslam.$(LIBEXT): 	algorithms.o  Scan.o Map.o WheeledRobot.o \
                         	coreslam.o coreslam_$(ARCH).o random.o ziggurat.o \
						 	serial_device.o hokuyo.o Laser.o
	arm-linux-gnueabihf-g++ -O3 -shared algorithms.o Scan.o Map.o WheeledRobot.o \
                        	coreslam.o coreslam_$(ARCH).o random.o ziggurat.o \
							serial_device.o hokuyo.o Laser.o\
          				 -o libbreezyslam.$(LIBEXT) -lm -std=c++11 -lpthread -mfpu=neon -fPIC 


algorithms.o: $(CPPPATH)algorithms.cpp $(CPPPATH)algorithms.hpp $(CPPPATH)Laser.hpp \
			  $(CPPPATH)Position.hpp $(CPPPATH)Map.hpp $(CPPPATH)Scan.hpp \
			  $(CPPPATH)Velocities.hpp $(CPPPATH)WheeledRobot.hpp $(CPATH)coreslam.h 
	arm-linux-gnueabihf-g++ -O3 -I$(CPATH) -c -Wall $(CFLAGS) $(CPPPATH)algorithms.cpp \
							-std=c++11 -lpthread -mfpu=neon -fPIC

Laser.o: $(CPPPATH)Laser.cpp $(CPPPATH)Laser.hpp $(CPATH)coreslam.h \
		 $(CPATH)hokuyo.h
	arm-linux-gnueabihf-g++ -O3 -I$(CPATH) -c -Wall $(CFLAGS) $(CPPPATH)Laser.cpp \
							-std=c++11 -lpthread -mfpu=neon -fPIC

Scan.o: $(CPPPATH)Scan.cpp $(CPPPATH)Scan.hpp $(CPPPATH)Velocities.hpp $(CPPPATH)Laser.hpp \
		$(CPATH)coreslam.h $(CPATH)hokuyo.h
	arm-linux-gnueabihf-g++ -O3 -I$(CPATH) -c -Wall $(CFLAGS) $(CPPPATH)Scan.cpp \
							-std=c++11 -lpthread -mfpu=neon -fPIC


serial_device.o : $(CPATH)serial_device.c $(CPATH)serial_device.h \
				  $(CPATH)message_utils.h
	arm-linux-gnueabihf-g++ -Wall -c -I$(CPATH)c $(CPATH)serial_device.c  \
							-std=c++11 -lpthread -mfpu=neon -fPIC

hokuyo.o : $(CPATH)hokuyo.c $(CPATH)hokuyo.h $(CPATH)message_utils.h
	arm-linux-gnueabihf-g++ -Wall -c -I$(CPATH) $(CPATH)hokuyo.c \
							-std=c++11 -lpthread -mfpu=neon -fPIC

Map.o: $(CPPPATH)Map.cpp $(CPPPATH)Map.hpp $(CPPPATH)Position.hpp $(CPPPATH)Scan.hpp \
	   $(CPATH)coreslam.h
	arm-linux-gnueabihf-g++ -O3 -I$(CPATH) -c -Wall $(CFLAGS) $(CPPPATH)Map.cpp \
							-std=c++11 -lpthread -mfpu=neon -fPIC

WheeledRobot.o: $(CPPPATH)WheeledRobot.cpp $(CPPPATH)WheeledRobot.hpp 
	arm-linux-gnueabihf-g++ -O3 -I$(CPATH) -c -Wall $(CFLAGS) $(CPPPATH)WheeledRobot.cpp \
							-std=c++11 -lpthread -mfpu=neon -fPIC

coreslam.o: $(CPATH)coreslam.c $(CPATH)coreslam.h
	arm-linux-gnueabihf-gcc -O3 -c -Wall $(CFLAGS) $(CPATH)coreslam.c \
							-std=c++11 -lpthread -mfpu=neon -fPIC

coreslam_$(ARCH).o: $(CPATH)coreslam_$(ARCH).c $(CPATH)coreslam.h
	arm-linux-gnueabihf-gcc -O3 -c -Wall $(CFLAGS) $(SIMD_FLAGS) $(CPATH)coreslam_$(ARCH).c \
							-std=c++11 -lpthread -mfpu=neon -fPIC

random.o: $(CPPPATH)../c/random.c
	arm-linux-gnueabihf-gcc -O3 -c -Wall $(CFLAGS) $(CPATH)random.c \
							-std=c++11 -lpthread -mfpu=neon -fPIC
	
ziggurat.o: $(CPATH)ziggurat.c
	arm-linux-gnueabihf-gcc -O3 -c -Wall $(CFLAGS) $(CPATH)ziggurat.c \
							-std=c++11 -lpthread -mfpu=neon -fPIC
	
install: libbreezyslam.$(LIBEXT)
	cp libbreezyslam.$(LIBEXT) $(LIBDIR)
	
doc:
	doxygen

clean:
	rm -rf  libbreezyslam.$(LIBEXT) *.o Documentation \#* *~
