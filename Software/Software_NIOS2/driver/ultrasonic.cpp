#include "i2c_opencores.h"
#include "system.h"

#include "ultrasonic.hpp"

UltraSonicDevice::UltraSonicDevice(const UltraSonicAddress deviceAddress) : __deviceAddress(deviceAddress)
{

}


uint8_t UltraSonicDevice::writeRegister(const UltraSonicRegistersWrite reg, const alt_u8 val)
{
	I2C_start(I2C_OPENCORES_0_BASE, reg, 0);
	I2C_write(I2C_OPENCORES_0_BASE, val, 1);
}
