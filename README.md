# QtPy-Globe
3D Globe for QtPy and SSD1306 OLED

Puts a rotating 3D wireframe globe on the screen. Cartesian coordinates are stored in globe_coords.h.

The QtPy_globe_tools.ino sketch turns latitude and longitude coordinate into x,y,z coordinates. Latitude and longitude coordinates are stored in lat_and_lon.h.

UnoR4_Globe.ino works on an Uno R4 and a QtPy ESP32 S2.  Uses a more detailed version of the globe with additional vertices - big_globe_coords.h
