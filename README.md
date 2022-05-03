# Theengs

[![License: GPL v3](https://img.shields.io/badge/license-GPL%20v3-brightgreen.svg?style=flat-square)](http://www.gnu.org/licenses/gpl-3.0)

### Features

* Support many Bluetooth Low Energy sensors
* MQTT support


## Documentation

#### Dependencies

You will need a C++17 compiler and Qt 6.3+ (with additional librairies).  
For Android builds, you'll need the appropriates JDK (11) SDK (23+) and NDK (22+). You can customize Android build environment using the `assets/android/gradle.properties` file.  
For Windows builds, you'll need the MSVC 2019+ compiler.  
For macOS and iOS builds, you'll need Xcode installed.  

Qt 6 'Additional Librairies':
- Qt 5 Compatibility module
- Qt Charts
- Qt Connectivity
- Qt Image Formats
- Qt WebSockets

#### Building QtMqtt

https://github.com/qt/qtmqtt

https://github.com/qt/qtmqtt/archive/refs/tags/v6.3.0.zip

```bash
mkdir build_desktop
cd build_desktop/
/home/usr/dev/Qt/6.3.0/gcc_64/bin/qt-configure-module ..
cmake --build .
cmake --install .
```

#### Building Theengs

```bash
$ git clone https://github.com/theengs/app.git TheengsApp --recurse-submodules
$ cd TheengsApp/
$ qmake
$ make
```

#### Using Theengs

##### Android

The Android operating system requires applications to ask for device location permission in order to scan for nearby Bluetooth Low Energy sensors. Android 10+ will ask for _ACCESS_FINE_LOCATION_, while Android 6+ will only ask for _ACCESS_COARSE_LOCATION_.  
The location permission is only needed while scanning for new sensors, not for updating data. You can learn more on Android developper [website](https://developer.android.com/guide/topics/connectivity/bluetooth/permissions#declare-android11-or-lower).

Some devices also require the GPS to be turned on while scanning for new sensors. This requirement is not documented and there is not much that can be done about it.  

##### iOS

The application will ask you for permission to use Bluetooth. You can learn more on Apple [website](https://support.apple.com/HT210578).

##### Linux ('live mode' and 'historical data')

While reading Flower Care and RoPot historical entry count, the sensors usually freeze for up to a second, and the Linux kernel consider that to be a connection timeout.  
To be able to get the historical data working on Linux, you'll need to increase the "supervision timeout" value (while root):

```bash
# echo 100 > /sys/kernel/debug/bluetooth/hci0/supervision_timeout
```

You could also give Theengs binary the _net_raw_ and _net_admin_ capabilities, so that it could be allowed to changes the supervision timeout on its own. But at the moment that's not fully implemented.

```bash
# setcap 'cap_net_raw,cap_net_admin+eip' theengs
```


#### Third party projects used by Theengs

* [Qt](https://www.qt.io) ([LGPL 3](https://www.gnu.org/licenses/lgpl-3.0.txt))
* [QtMqtt](https://www.qt.io) ([GPL 3](https://www.gnu.org/licenses/gpl-3.0.txt))
* [StatusBar](https://github.com/jpnurmi/statusbar) ([MIT](https://opensource.org/licenses/MIT))
* [ekkesSHAREexample](https://github.com/ekke/ekkesSHAREexample) ([license](https://github.com/ekke/ekkesSHAREexample/blob/master/LICENSE))
* [SingleApplication](https://github.com/itay-grudev/SingleApplication) ([MIT](https://opensource.org/licenses/MIT))
* RC4 code from Christophe Devine ([GPL 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt))
* Graphical resources: [assets/COPYING](assets/COPYING)


## Get involved!

#### Developers

You can browse the code on the GitHub page, submit patches and pull requests! Your help would be greatly appreciated ;-)

#### Users

You can help us find and report bugs, suggest new features, help with translation, documentation and more! Visit the Issues section of the GitHub page to start!


## License

Theengs is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.  
Read the [LICENSE](LICENSE) file or [consult the license on the FSF website](https://www.gnu.org/licenses/gpl-3.0.txt) directly.
