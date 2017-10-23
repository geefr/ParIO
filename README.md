# ParIO
Parallel port library for general IO

Tests:
pariotest is provided to test functionality, at the moment the port number is hardcoded in main.cpp
USAGE: pariotest
All data pins on the port will toggle on/off for 10 seconds

Troubleshooting:
- Errors claiming the port: Check the output of 'cat /proc/sys/dev/parport/parportN/devices/active'. The 'lp' driver specifically cannot share access to the port, and will claim it on boot. Use 'rmmod lp' to let pario claim the port.

