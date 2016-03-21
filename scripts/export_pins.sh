#!/bin/bash

for pin in 18 1 27 2 22 3 23 4; do
  /usr/local/bin/gpio export $pin out
  chmod -R g+w /sys/devices/virtual/gpio/gpio$pin
done
