## Prueba del Gps 

He seguido este [ejemplo](https://github.com/Xinyuan-LilyGO/LilyGO-T-A76XX/blob/main/examples/GPS_BuiltIn/GPS_BuiltIn.ino) 


Funciona y la salida en el terminal es:

````
Start modem...
AT
AT
ERROR
AT
AT
OK

AT+CGMM

+CPIN: READY

SMS DONE
AT+CGMM
SIM7670G-MNGV

OK
[7231] ### Modem: +CPIN: READY

SMS DONE
AT+CGMM
SIM7670G-MNGV
Model Name:+CPIN: READY

SMS DONE
AT+CGMM
SIM7670G-MNGV
AT+SIMCOMATI
AT+SIMCOMATI
Manufacturer: SIMCOM INCORPORATED
Model: SIM7670G-MNGV
Revision: xxxxxxxxxxxxxxxxxxx
SIM767XM5A_B01V03_231207
IMEI: xxxxxxxxxxxxxxxxxxx

OK
Enabling GPS/GNSS/GLONASS
AT+CGDRT=4,1
AT+CGDRT=4,1
OK
AT+CGSETV=4,1
AT+CGSETV=4,1
OK
AT+CGNSSPWR=1
AT+CGNSSPWR=1
OK

GPS Enabled
AT+CGNSSIPR=115200
AT+CGNSSIPR=115200
OK
Requesting current GPS/GNSS/GLONASS location
AT+CGNSSINFO
AT+CGNSSINFO
+CGNSSINFO: ,,,,,,,,

OK
Couldn't get GPS/GNSS/GLONASS location, retrying in 15s.
Requesting current GPS/GNSS/GLONASS location
AT+CGNSSINFO
AT+CGNSSINFO
+CGNSSINFO: ,,,,,,,,

OK
Couldn't get GPS/GNSS/GLONASS location, retrying in 15s.
Requesting current GPS/GNSS/GLONASS location
AT+CGNSSINFO
AT+CGNSSINFO
+CGNSSINFO: ,,,,,,,,

OK
Couldn't get GPS/GNSS/GLONASS location, retrying in 15s.
Requesting current GPS/GNSS/GLONASS location
AT+CGNSSINFO
AT+CGNSSINFO
+CGNSSINFO: x,x,x,x,x,x,N,x,W,x,x,x,x,x,x,x,x,x

OK
FixMode:3
Latitude:xx.xxxxxxx      Longitude:-x.xxxxxx
Speed:0.04      Altitude:526.00
Visible Satellites:5    Used Satellites:0
Accuracy:1.20
Year:2025       Month:4 Day:18
Hour:17 Minute:37       Second:42
Retrieving GPS/GNSS/GLONASS location again as a string
AT+CGNSSINFO
AT+CGNSSINFO
+CGNSSINFO: x,x,x,x,x,x,N,x,W,x,x,x,x,x,x,x,x,x

OK
GPS/GNSS Based Location String:x,x,x,x,x,x,N,x,W,x,x,x,x,x,x,x,x,x
Disabling GPS
AT+CGNSSPWR=0
AT+CGNSSPWR=0
OK
````

<br><br>
![result](docs/result.png)
<br><br>



