#!/bin/bash
#18 1 27 2 22 3 23 4
for pin in 1 2 3 4 8; do
  /usr/local/bin/gpio export $pin out
  chmod -R g+w /sys/devices/virtual/gpio/gpio$pin
done

for pin in 25 29 28 27; do
  /usr/local/bin/gpio export $pin in
  chmod -R g+w /sys/devices/virtual/gpio/gpio$pin
done

