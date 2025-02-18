 ![logo](https://github.com/Nathan-Busse-private/S.P.A.R.K/assets/82398683/5ae9812e-52db-4cab-8d8a-45c9495b9309)

A robot dog with a heart.

# TO DO:

Hardware
------------

- [x]  Redesign tibia joint.
- [x]  Redesign gyro mount.
- [x]  Replace UNO with Raspberry Pi 4B.
- [x]  Add Arduino NANO
- [x]  Add a 5.1 volt 3 amp regulator.
- [ ]  Replace gel battery with lithium ion.
- [ ]  Add web-cams.
- [ ]  Add GPS.
  
C++
------------

- [x]  Make S.P.A.R.K walk.
- [x]  Control S.P.A.R.K through bluetooth.
- [x]  Add killswitch function.
- [x]  Make Serial_slave script
- [x]  Make S.P.A.R.K rest.
- [x]  Make S.P.A.R.K pivot.
- [x]  Make S.P.A.R.K sit.
- [ ]  Replace delay function with millis.
- [ ]  Perfect walking gaits.
- [ ]  Create PID algorithm to adjust IK to help S.P.A.R.K naviagate uneven terrain better.
- [ ]  Implement PID algorithm.

Java
------------

- [x]  Redesign S.P.A.R.K logo.
- [x]  Build a disributable apk file for the app.
- [x]  Create a Build history directory for the app.
- [ ]  Implement S.P.A.R.K setup and configuration settings through the app.

Python
-----------

- [x]  Work on object detection.
- [x]  Work on body tracker.
- [x]  Work on hand tracker.
- [x]  Work on Serial_master script
- [x]  Work on Bluetooth_command script.
- [ ]  Work on DNN.
- [ ]  Work on Body behavior animations.
- [ ]  Implement cloud update protacol.
- [ ]  Implement auto cloud backup protacol.
- [ ]  Implement SSH communication protacol.
- [ ]  Recover from power loss.
- [ ]  Work on object avoidance engine.
- [ ]  Work on autonomous navigation engine.
- [ ]  Work on speech recognition engine.
- [ ]  Work on personality matrix.
- [ ]  Work on diagnostic and status communication to S.P.A.R.K app.
- [ ]  Work on GPS communication protacol.

Bash
-----------

- [x] Work on Blueman installer script
- [x] Work on Bluetooth installer script
- [x] Work on Arduino setup script
- [x] Work on Bluetooth initializer script 

# Known bugs:

Hardware
-----------

- [x] Femur A & C is not alligned with Femur B & D.

C++
-----------

- [x] Rest mode takes 4 seconds to engage once S.P.A.R.K has been powered on.
- [x] Tibia B lifts first instead D causing S.P.A.R.K to lose balance at the first stride but recover there after.
- [ ] In Bluetooth Nightly V2 S.P.A.R.K walks on the spot when commanding him to move forward.
- [ ] Tibia do not lift off the ground propperly causing S.P.A.R.K to be unable to step over carpats. 

Java
-----------

- [x]  App doesn't transmit stop command automatically after connection in the app.
- [ ]  Device falls asleep when no input is given in the app after the devices set sleep time is lapsed.

Python
-----------


Bash
-----------
