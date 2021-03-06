/*
 * Copyright (c) 2018 Mustafa Ozcelikors
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     YAKALA project
 *
 * Author:
 *    M.Ozcelikors <mozcelikors@gmail.com>
 *
 */

#include "systeminfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <QString>
#include <QFile>
#include <QTextStream>

// To debug, uncomment below, and run 'valgrind -v ./yakala'
//#define DEBUG 1

// TODO: Debug the process killing.

// TODO: Read own MAC address correctly.

SystemInfo::SystemInfo()
{}

void SystemInfo::readMACAddress(QString ip_addr)
{
	FILE *fp;

	fp = popen ((QString("ifconfig | grep -B ")+ip_addr+QString(" | head -1 | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}' | head -1 2>/dev/null")).toLocal8Bit(),"r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("mac=%s\n", this->buffer);
#endif
		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->mac_addr, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);

}

QString SystemInfo::getMACAddress(void)
{
	return this->mac_addr;
}

void SystemInfo::readMemoryTotal (void)
{
	FILE *fp;
	int tmp_mem_total;

	fp = popen ("timeout 5 cat /proc/meminfo | grep MemTotal | sed 's/[^0-9]*//g' 2>/dev/null ","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("memtotal=%s\n", this->buffer);
#endif
		sscanf(buffer, "%d", &tmp_mem_total);

		this->memory_total = (tmp_mem_total/1024.0)/1024.0;
	}
	else
	{
		this->memory_total = 0;
	}
	fclose(fp);
}

void SystemInfo::readMemoryFree (void)
{
	FILE *fp;
	int tmp_mem_free;

	fp = popen ("timeout 5 cat /proc/meminfo | grep MemFree | sed 's/[^0-9]*//g' 2>/dev/null ","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("memfree=%s\n", this->buffer);
#endif
		sscanf(buffer, "%d", &tmp_mem_free);

		this->memory_free = (tmp_mem_free/1024.0)/1024.0;
	}
	else
	{
		this->memory_free = 0;
	}
	fclose(fp);
}

void SystemInfo::readCpuUsage (void)
{
	FILE *fp;
	int tmp_cpu_usage;

	fp = popen ("timeout 5 awk -v a=\"$(awk '/cpu /{print $2+$4,$2+$4+$5}' /proc/stat; sleep 0.5)\" '/cpu /{split(a,b,\" \"); print 100*($2+$4-b[1])/($2+$4+$5-b[2])}'  /proc/stat 2>/dev/null ","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("cpuusage=%s\n", this->buffer);
#endif
		sscanf(buffer, "%d", &tmp_cpu_usage);

		this->cpu_usage = (tmp_cpu_usage);
	}
	else
	{
		this->cpu_usage = 0;
	}
	fclose(fp);
}

void SystemInfo::readCpuModel (void)
{
	FILE *fp;

	fp = popen ("timeout 5 cat /proc/cpuinfo | grep -m1 'model name' | sed 's/.*: //' 2>/dev/null","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("cpumodel=%s\n", this->buffer);
#endif
		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->cpu_model, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);
}


void SystemInfo::readCpuCount (void)
{
	FILE *fp;
	int tmp_cpu_count;

	fp = popen ("timeout 5 cat /proc/cpuinfo | grep 'processor' | tail -1 | sed 's/[^0-9]*//g'","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("cpucount=%s\n", this->buffer);
#endif

		sscanf(buffer, "%d", &tmp_cpu_count);

		buffer[0] = 0; //Clear array

		this->cpu_count = (tmp_cpu_count + 1);
	}
	else
	{
		this->cpu_count = 0;
	}
	fclose(fp);
}

void SystemInfo::readDistro (void)
{
	FILE *fp;

	fp = popen ("timeout 5 cat /etc/os-release | grep PRETTY_NAME | sed -e 's#.*=\\(\\)#\1#' | sed 's/\\\"//g' ","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("distro=%s\n", this->buffer);
#endif
		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->distro, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);
}

void SystemInfo::readKernelRelease (void)
{
	FILE *fp;

	fp = popen ("timeout 5 uname -r","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("kernel=%s\n", this->buffer);
#endif
		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->kernel_release, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);
}

void SystemInfo::readArchitecture (void)
{
	FILE *fp;

	fp = popen ("timeout 5 uname -i","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("arch=%s\n", this->buffer);
#endif

		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->architecture, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);
}

void SystemInfo::readHostname (void)
{
	FILE *fp;

	fp = popen ("timeout 5 hostname","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("hostname=%s\n", this->buffer);
#endif
		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->hostname, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);
}

void SystemInfo::readIP (void)
{
	FILE *fp;

	fp = popen ("timeout 5 ifconfig | grep 'inet addr:' | grep '192.168' | cut -d: -f2 | awk '{ print $1}'","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("ip=%s\n", this->buffer);
#endif
		//sscanf(buffer, "%s", &tmp_cpu_usage);

		strncpy (this->ip, buffer, strlen(buffer));

		buffer[0] = 0; //Clear array
	}
	else
	{

	}
	fclose(fp);
}

void SystemInfo::readDiskTotal (void)
{
	FILE *fp;
	int tmp_disk_space_total;

	fp = popen ("timeout 5 df -k / -l --output=size | tail -1","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("disktotal=%s\n", this->buffer);
#endif

		sscanf(buffer, "%d", &tmp_disk_space_total);

		buffer[0] = 0; //Clear array

		this->disk_space_total = ((tmp_disk_space_total)/1024.0)/1024.0;
	}
	else
	{
		this->disk_space_total = 0;
	}
	fclose(fp);
}

void SystemInfo::readDiskUsed (void)
{
	FILE *fp;
	int tmp_disk_space_used;

	fp = popen ("timeout 5 df -k / -l --output=used | tail -1","r");

	if (fp != NULL)
	{
		while (1)
		{
			if (fgets(this->buffer, MAX_BUFSIZE, fp) == NULL) break;
			//puts(this->buffer);
		}
#ifdef DEBUG
		printf ("diskused=%s\n", this->buffer);
#endif
		sscanf(buffer, "%d", &tmp_disk_space_used);

		buffer[0] = 0; //Clear array

		this->disk_space_used = ((tmp_disk_space_used)/1024.0)/1024.0;
	}
	else
	{
		this->disk_space_used = 0;
	}
	fclose(fp);
}

float SystemInfo::getMemoryTotal (void)
{
	return this->memory_total;
}

float SystemInfo::getMemoryFree (void)
{
	return this->memory_free;
}

float SystemInfo::getMemoryPercentage (void)
{
	this->memory_percentage = ((this->memory_total - this-> memory_free) / this->memory_total) * 100.0;
	return this->memory_percentage;
}

float SystemInfo::getCpuUsage (void)
{
	return this->cpu_usage;
}

char * SystemInfo::getCpuModel (void)
{
	return this->cpu_model;
}

int SystemInfo::getCpuCount (void)
{
	return this->cpu_count;
}

char* SystemInfo::getDistro (void)
{
	return this->distro;
}

char* SystemInfo::getKernelRelease (void)
{
	return this->kernel_release;
}

char* SystemInfo::getArchitecture (void)
{
	return this->architecture;
}

char* SystemInfo::getHostname (void)
{
	return this->hostname;
}

char* SystemInfo::getIP (void)
{
	return this->ip;
}

float SystemInfo::getDiskSpaceTotal (void)
{
	return this->disk_space_total;
}

float SystemInfo::getDiskSpaceUsed (void)
{
	return this->disk_space_used;
}

int SystemInfo::getDiskPercentage (void)
{
	this->disk_percentage = (this->disk_space_used / this->disk_space_total) * 100.0;
	return this->disk_percentage;
}

void SystemInfo::readSysLogs (void)
{
	this->syslog_out.clear();
	this->lsusb_out.clear();
	this->dmesg_out.clear();
	this->ifconfig_out.clear();

	/* Syslog */
	QFile MyFile3("/var/log/syslog");
	if (MyFile3.open(QIODevice::ReadWrite))
	{
		QTextStream in3 (&MyFile3);
		QString line3;
		while (!in3.atEnd())
		{
			line3 = in3.readLine();
			this->syslog_out.append(line3);
			this->syslog_out.append("\n");
		}
		MyFile3.close();
	}

	/* Dmesg */
	FILE *fp;
	fp = popen ("timeout 5 dmesg > /tmp/yakala.dmesg ","w");
	fclose(fp);

	QFile MyFile4("/tmp/yakala.dmesg");
	if (MyFile4.open(QIODevice::ReadWrite))
	{
		QTextStream in3 (&MyFile4);
		QString line3;
		while (!in3.atEnd())
		{
			line3 = in3.readLine();
			this->dmesg_out.append(line3);
			this->dmesg_out.append("\n");
		}
		MyFile4.close();
	}

	/* Ifconfig */
	FILE *fp2;
	fp2 = popen ("timeout 5 ifconfig > /tmp/yakala.ifconfig ","w");
	fclose(fp2);

	QFile MyFile5("/tmp/yakala.ifconfig");
	if (MyFile5.open(QIODevice::ReadWrite))
	{
		QTextStream in3 (&MyFile5);
		QString line3;
		while (!in3.atEnd())
		{
			line3 = in3.readLine();
			this->ifconfig_out.append(line3);
			this->ifconfig_out.append("\n");
		}
		MyFile5.close();
	}

	/* Lsusb */
	FILE *fp3;
	fp3 = popen ("timeout 5 lsusb > /tmp/yakala.lsusb ","w");
	fclose(fp3);

	QFile MyFile6("/tmp/yakala.lsusb");
	if (MyFile6.open(QIODevice::ReadWrite))
	{
		QTextStream in3 (&MyFile6);
		QString line3;
		while (!in3.atEnd())
		{
			line3 = in3.readLine();
			this->lsusb_out.append(line3);
			this->lsusb_out.append("\n");
		}
		MyFile6.close();
	}
}

QString SystemInfo::getSysLogOut (void)
{
	return this->syslog_out;
}

QString SystemInfo::getDmesgOut (void)
{
	return this->dmesg_out;
}

QString SystemInfo::getIfconfigOut (void)
{
	return this->ifconfig_out;
}

QString SystemInfo::getLsusbOut (void)
{
	return this->lsusb_out;
}
