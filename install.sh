#!/bin/bash

# Installes prerequisites and builds 'yakala'

## Check for the distro
if [ -f /etc/os-release ]; then
    # freedesktop.org and systemd
    . /etc/os-release
    OS=$NAME
    VER=$VERSION_ID
elif type lsb_release >/dev/null 2>&1; then
    # linuxbase.org
    OS=$(lsb_release -si)
    VER=$(lsb_release -sr)
elif [ -f /etc/lsb-release ]; then
    # For some versions of Debian/Ubuntu without lsb_release command
    . /etc/lsb-release
    OS=$DISTRIB_ID
    VER=$DISTRIB_RELEASE
elif [ -f /etc/debian_version ]; then
    # Older Debian/Ubuntu/etc.
    OS=Debian
    VER=$(cat /etc/debian_version)
elif [ -f /etc/SuSe-release ]; then
    # Older SuSE/etc.
    ...
elif [ -f /etc/redhat-release ]; then
    # Older Red Hat, CentOS, etc.
    ...
else
    # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
    OS=$(uname -s)
    VER=$(uname -r)
fi

## Get which directory we're at
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

## Check for packages

echo "Checking for required packages..."

## Check for qt5-default
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' qt5-default | grep "install ok installed")
echo "Checking for qt5-default: $PKG_OK"
if [ "" == "$PKG_OK" ]; then
  echo "No qt5. Setting up qt5."
  sudo apt-get --force-yes --yes install qt5-default
fi

## Check for nmap
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' 'nmap' | grep "install ok installed")
echo "Checking for nmap: $PKG_OK"
if [ "" == "$PKG_OK" ]; then
  echo "No nmap. Setting up nmap."
  sudo apt-get --force-yes --yes install nmap
fi


## Check for gksu
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' 'gksu' | grep "install ok installed")
echo "Checking for gksu: $PKG_OK"
if [ "" == "$PKG_OK" ]; then
  echo "No gksu. Setting up gksu."
  sudo apt-get --force-yes --yes install gksu
fi

## Check for usbutils
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' 'usbutils' | grep "install ok installed")
echo "Checking for usbutils: $PKG_OK"
if [ "" == "$PKG_OK" ]; then
  echo "No usbutils. Setting up usbutils."
  sudo apt-get --force-yes --yes install usbutils
fi

## Check for xterm
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' 'xterm' | grep "install ok installed")
echo "Checking for xterm: $PKG_OK"
if [ "" == "$PKG_OK" ]; then
  echo "No xterm. Setting up xterm."
  sudo apt-get --force-yes --yes install xterm
fi


## Make
echo "Compiling yakala..."
qmake yakala.pro 
rm -rf build && mkdir -p build
make
make install

## Install Ubuntu font
sudo mkdir -p ~/.fonts
sudo cp $DIR/gui/Ubuntu-R.ttf /usr/local/share/fonts/
sudo cp $DIR/gui/Ubuntu-R.ttf ~/.fonts
fc-cache

## Create desktop shortcut
printf "[Desktop Entry]\nEncoding=UTF-8\nVersion=1.0\nType=Application\nName=Yakala\nIcon=$DIR/gui/icon2.ico\nExec=gksudo -k -u root $DIR/build/yakala\nCategories=Application;Network;Security;" > /home/$SUDO_USER/.local/share/applications/yakala.desktop
sudo chmod +x /home/$SUDO_USER/.local/share/applications/yakala.desktop
cp /home/$SUDO_USER/.local/share/applications/yakala.desktop /home/$SUDO_USER/Desktop/yakala.desktop
sudo chmod +x /home/$SUDO_USER/Desktop/yakala.desktop

echo "Done. Run the executable in build/yakala."
echo "If you like it, set up an alias for it ;)"
