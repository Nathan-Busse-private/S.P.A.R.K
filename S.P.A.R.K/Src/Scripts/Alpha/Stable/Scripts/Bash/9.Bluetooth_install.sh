sudo apt-get install python-bluetooth

sudo bluetoothctl
[bluetooth]# power on
[bluetooth]# agent on
[bluetooth]# discoverable on
[bluetooth]# pairable on
[bluetooth]# scan on

pair <44:16:FA:01:1D:E5>
