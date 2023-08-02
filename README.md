# Netcalc
Program converts values from the IP address and subnet mask to network values.
It can retrieve data from the network interface.

## Required dependencies
  - pkg-config
  - GTK 3 Libray
    - libgtk-3-dev (for Debian)
    - gtk3-devel (for Fedora, openSUSE)
    - gtk3 (for ArchLinux)
    - gtk+ (for Slackware)

## TODO
  - [ ] Optimize font for GTK window to snap build
  - [x] Add MAC address to interface output
  - [x] Add Gateway address to interface output
  - [ ] Add DNS address to interface output

## Compile
```sh
mkdir build
cd build
cmake ..
make
```
### Install
```sh
sudo make install
```
### Uninstall
```sh
sudo make uninstall
```
### Cmake build type
Debug type is a draft version, release is ready to install.
Default type is release
```sh
cmake -DCMAKE_BUILD_TYPE=Release ../
cmake -DCMAKE_BUILD_TYPE=Debug ../
```

## Install from snapstore
[![netcalc](https://snapcraft.io//netcalc/badge.svg)](https://snapcraft.io/netcalc)
[![netcalc](https://snapcraft.io//netcalc/trending.svg?name=0)](https://snapcraft.io/netcalc)

```sh
snap install netcalc
```
### Images
<p align="center">
  <img src="https://dashboard.snapcraft.io/site_media/appmedia/2023/07/netcalc-8.png">
  <img src="https://dashboard.snapcraft.io/site_media/appmedia/2023/07/netcalc-1.png" width="40%">
  <img src="https://dashboard.snapcraft.io/site_media/appmedia/2023/07/netcalc-2.png" width="40%">
  <img src="https://dashboard.snapcraft.io/site_media/appmedia/2023/07/netcalc-3.png" width="40%">
  <img src="https://dashboard.snapcraft.io/site_media/appmedia/2023/07/netcalc-4.png" width="40%">
</p>
