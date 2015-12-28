QtW100S
=======

Tool designed to control a Walkera QR W100S from a PC

Video is accessible on port 8080 (http://192.168.10.1:8080/?action=stream), but the stream is password protected (admin:admin123).
Commands must be sent through port 2001 of the helicopter.

This is what I got when I analyzed the packets:
- a packet of 18 bytes must be sent to the drone
- first byte seems constant and equal to 97 (base 10) while the remote is on
- last byte is a checksum
- throttle (values from 700 to 1500), rotation (600-1600), elevator (600-1600) and ailerons (600-1600) are each encoded on two bytes
- these values seem to be put twice in the packet

Therefore, the packet to be sent should look like this (code from workerthread.cpp):

```
char data[18];
data[0] = 97;
data[1] = throttle >> 8;
data[2] = throttle;
data[3] = rotation >> 8;
data[4] = rotation;
data[5] = elev >> 8;
data[6] = elev;
data[7] = aile >> 8;
data[8] = aile;
data[9] = aile >> 8;
data[10] = aile;
data[11] = throttle >> 8;
data[12] = throttle;
data[13] = rotation >> 8;
data[14] = rotation;
data[15] = elev >> 8;
data[16] = elev;
data[17] = 0;
for(int i=0; i<17; ++i)
  data[17] += data[i];
data[17] &= 255;
```
