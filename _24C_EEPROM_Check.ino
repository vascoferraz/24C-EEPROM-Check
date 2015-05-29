/*****************************************************************************
* Copyright (C) 2013 by Vasco Ferraz. All Rights Reserved.                   *
*                                                                            *
* This program is free software: you can redistribute it and/or modify       *
* it under the terms of the GNU General Public License as published by       *
* the Free Software Foundation, either version 3 of the License, or          *
* (at your option) any later version.                                        *
*                                                                            *
* This program is distributed in the hope that it will be useful,            *
* but WITHOUT ANY WARRANTY; without even the implied warranty of             *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
* GNU General Public License for more details.                               *
*                                                                            *
* You should have received a copy of the GNU General Public License          *
* along with this program. If not, see <http://www.gnu.org/licenses/>.       *
*                                                                            *
*  Author:        Vasco Ferraz                                               *
*  Contact:       http://vascoferraz.com/contact/                            *
*  Description:   http://vascoferraz.com/projects/24c-eeprom-check/          *
*****************************************************************************/

#include <Wire.h>

#define EEPROM_I2C_ADDRESS 0x50

//uncomment accordingly:
//int maxaddress=128-1;             //24C01    -> 1024 bit    -> 128 byte
//int maxaddress=256-1;             //24C02    -> 2048 bit    -> 256 byte
//int maxaddress=512-1;             //24C04    -> 4096 bit    -> 512 byte
//int maxaddress=1024-1;            //24C08    -> 8192 bit    -> 1024 byte
//int maxaddress=2048-1;            //24C16    -> 16384 bit   -> 2048 byte
//int maxaddress=4096-1;            //24C32    -> 32768 bit   -> 4096 byte
//int maxaddress=8192-1;            //24C64    -> 65536 bit   -> 8192 byte
//int maxaddress=16384-1;           //24C128   -> 131072 bit  -> 16384 byte
//int maxaddress=32768-1;           //24C256   -> 262144 bit  -> 32768 byte
//unsigned int maxaddress=65536-1;  //24C512   -> 524288 bit  -> 65536 byte

int address = 0;
unsigned int value = 0;
unsigned int check_value = 0;

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();
  randomSeed(analogRead(0));
}

void loop()
{  
  for (address=0 ; address<=maxaddress ; address++)
  {
   value = random(256); // generates a random number between 0 and 255
   writeEEPROM(EEPROM_I2C_ADDRESS, address, value);
   Serial.print(address); Serial.print(" - "); Serial.print(value); Serial.print(" - ");
  
   check_value = readEEPROM(EEPROM_I2C_ADDRESS, address); Serial.print(check_value);
   Serial.print(" - ");
  
   if (check_value != value) {Serial.println("NOK"); while(1);}
   else if (check_value == value) {Serial.println("OK");}
  }
}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  if (maxaddress <= 255) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress));
    Wire.write(data);
    Wire.endTransmission();
   }
   
  if(maxaddress >= 511) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    Wire.endTransmission();
   }
   
  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
  
  if(maxaddress <= 255) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress));
    Wire.endTransmission();
   }
  
  if(maxaddress >= 511) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
   }
  
   Wire.requestFrom(deviceaddress,1);
 
   if (Wire.available()) rdata = Wire.read();
 
   return rdata;
}
