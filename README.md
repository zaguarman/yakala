# yakala
A visual helper tool for GNU/Linux. Made with love.

## Features 

* Show system statistics: CPU, Memory, Disk stats and system information
* Visualize recent CPU and Memory activity
* Search for files
* Search for networks
* SSH into networks
* See active TCP/UDP sockets
* Modify your aliases
* Search and kill processes
* List environment variables
* View system logs
* View driver messages
* View network interface messages
* Search for installed packages / uninstall them
* Search for available packages in apt cache

New features involve (as of March 1st, 2018):

* View system logs
* View driver messages
* View network interface messages
* Search for installed packages / uninstall them
* Search for available packages in apt cache

## Download Stable Release 0.8 using Debian/Ubuntu PPA:
https://launchpad.net/~mozcelikors/+archive/ubuntu/yakala
```bash
sudo add-apt-repository ppa:mozcelikors/yakala
sudo apt-get update
sudo apt-get install yakala
```

## Compiling from Source / Git VC:

```bash
git clone https://github.com/mozcelikors/yakala
cd yakala && sudo ./install.sh
```

## Animations

### System Information:

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/peekx1.gif)

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/peek2.gif)

### System Logs:

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/systemlogs.gif)

### Network:

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/peekx2.gif)

### File Searching:

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/peekx3.gif)

### Processes, Aliases, Variables:

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/peekx4.gif)

### Installed package Searching, Package cache searching

![alt text](https://raw.githubusercontent.com/mozcelikors/yakala/master/docs/img/aptcache.gif)


## Running

Installation script will automatically create a desktop icon for you. You can use that icon or execute the following to run Yakala:

```bash
cd <yakala-dir>/build
sudo ./yakala
```

## Contributions

Contributions are more than welcome. Please create a descriptive pull request.
