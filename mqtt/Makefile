# Copyright (C) 2015 NIPE-SYSTEMS
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

MCU = atmega8
F_CPU = 16000000UL

.PHONY: all node node-program init clean

all: node

# Compile node program

node: init bin/obj/node.o bin/obj/node-mqtt-subset.o
	avr-gcc -mmcu=$(MCU) -I. -gdwarf-2 -DF_CPU=$(F_CPU) -O1 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -Wundef -o bin/node.elf bin/obj/node.o bin/obj/node-mqtt-subset.o -lm
	avr-objcopy -O ihex -R .eeprom bin/node.elf bin/node.hex
	@echo
	@avr-size --mcu=$(MCU) --format=avr bin/node.elf

# Flash node program

node-program: node
	avrdude -p $(MCU) -P usbasp -c usbasp -U flash:w:bin/node.hex

# Initializes directories

init:
	mkdir -p bin
	mkdir -p bin/obj

bin/obj/node.o: node.c
	avr-gcc -c -mmcu=$(MCU) -I. -gdwarf-2 -DF_CPU=$(F_CPU) -O1 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -Wundef -o bin/obj/node.o node.c

bin/obj/node-mqtt-subset.o: node-mqtt-subset.c
	avr-gcc -c -mmcu=$(MCU) -I. -gdwarf-2 -DF_CPU=$(F_CPU) -O1 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -Wundef -o bin/obj/node-mqtt-subset.o node-mqtt-subset.c

# Clean

clean:
	rm -Rf bin