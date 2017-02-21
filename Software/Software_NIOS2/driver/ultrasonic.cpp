/*!
 * @file
 * */
#include "i2c_opencores.h"
#include "system.h"

#include "ultrasonic.hpp"

UltraSonicDevice::UltraSonicDevice(const UltraSonicAddress deviceAddress) : __deviceAddress(deviceAddress)
{

}


alt_u8 UltraSonicDevice::writeCMDRegister(const UltraSonicCommands val)
{
	alt_u8 result = 1;

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(UltraSonicRegistersWrite::COMMAND), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(val), 1);

	return result;
}

alt_u8 UltraSonicDevice::writeGAINRegister(const alt_u8 val)
{
	alt_u8 result = 1;

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(UltraSonicRegistersWrite::MAX_GAIN), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(val), 1);

	return result;
}

alt_u8 UltraSonicDevice::writeRANGERegister(const alt_u8 val)
{
	alt_u8 result = 1;

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(UltraSonicRegistersWrite::RANGE), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(val), 1);

	return result;
}

alt_u8 UltraSonicDevice::readRegister(const UltraSonicRegisterRead reg, alt_u8& readPtr)
{
	alt_u8 result = 1;

	// start IIC communication
	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 1);
	// write which register must be read
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(reg), 0);
	// read the actual register
	readPtr = I2C_read(I2C_OPENCORES_0_BASE, 1);

	return result ;
}

alt_u8 UltraSonicDevice::readMeasurement(alt_u8* ultrasonic_measurement, const alt_u8 length)
{
	alt_u8 result = 1;
	return result;
}

alt_u8 UltraSonicDevice::changeAddress(const UltraSonicAddress newAddress)
{
	alt_u8 result = 1;

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(UltraSonicCommands::CHANGE_ADDRESS_COMMAND_1),1);

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(UltraSonicCommands::CHANGE_ADDRESS_COMMAND_2),1);

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(UltraSonicCommands::CHANGE_ADDRESS_COMMAND_3),1);

	result = I2C_start(I2C_OPENCORES_0_BASE, static_cast<alt_u32>(__deviceAddress), 0);
	I2C_write(I2C_OPENCORES_0_BASE, static_cast<alt_u8>(newAddress),1);

	if( result == 0)
		__deviceAddress = newAddress;

	return result;
}

