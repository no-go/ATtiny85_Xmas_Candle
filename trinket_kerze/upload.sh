#!/bin/bash

# set to 1MHz
avrdude -B 1000 -c usbasp -p t85 -U lfuse:w:0x62:m
# flash
avrdude -c usbasp -p t85 -B 200 -U flash:w:trinket_kerze.ino.tiny8.hex:i 
