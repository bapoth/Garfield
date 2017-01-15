#ifndef ULTRASONIC_HPP_
#define ULTRASONIC_HPP_

#include "alt_types.h"

/*
 * defines all possible IIC addresses for the SRF08 ultra sonic range finder
 * */
enum class UltraSonicAddress : alt_u8  {
	DEVICE_00 = 0xE0,
	DEVICE_01 = 0xE2,
	DEVICE_02 = 0xE4,
	DEVICE_03 = 0xE6,
	DEVICE_04 = 0xE8,
	DEVICE_05 = 0xEA,
	DEVICE_06 = 0xEC,
	DEVICE_07 = 0xEE,
	DEVICE_08 = 0xF0,
	DEVICE_09 = 0xF2,
	DEVICE_10 = 0xF4,
	DEVICE_11 = 0xF6,
	DEVICE_12 = 0xF8,
	DEVICE_13 = 0xFA,
	DEVICE_14 = 0xFC,
	DEVICE_15 = 0xFE,
};

/*
 * defines all possible write registers
 * */
enum class UltraSonicRegistersWrite : alt_u8 {
	COMMAND 	= 0x00, // can init a ranging
	MAX_GAIN 	= 0x01, // maximum gain value (range + max_gain must be tested for best results)
	RANGE		= 0x02, // time need for one measurement
};


/*
 * defines all possible read registers
 * */
enum class UltraSonicRegisterRead : alt_u8 {
	SW_REVISION		= 0x00,
	LIGHT_SENSOR	= 0x01,
	ECHO_HIGH_0x01	= 0x02,
	ECHO_LOW_0x01	= 0x03,
	ECHO_HIGH_0x02	= 0x04,
	ECHO_LOW_0x02	= 0x05,
	ECHO_HIGH_0x03	= 0x06,
	ECHO_LOW_0x03	= 0x07,
	ECHO_HIGH_0x04	= 0x08,
	ECHO_LOW_0x04	= 0x09,
	ECHO_HIGH_0x05	= 0x0A,
	ECHO_LOW_0x05	= 0x0B,
	ECHO_HIGH_0x06	= 0x0C,
	ECHO_LOW_0x06	= 0x0D,
	ECHO_HIGH_0x07	= 0x0E,
	ECHO_LOW_0x07	= 0x0F,
	ECHO_HIGH_0x08	= 0x10,
	ECHO_LOW_0x08	= 0x11,
	ECHO_HIGH_0x09	= 0x12,
	ECHO_LOW_0x09	= 0x13,
	ECHO_HIGH_0x0A	= 0x14,
	ECHO_LOW_0x0A	= 0x15,
	ECHO_HIGH_0x0B	= 0x16,
	ECHO_LOW_0x0B	= 0x17,
	ECHO_HIGH_0x0C	= 0x18,
	ECHO_LOW_0x0C	= 0x19,
	ECHO_HIGH_0x0D	= 0x1A,
	ECHO_LOW_0x0D	= 0x1B,
	ECHO_HIGH_0x0E	= 0x1C,
	ECHO_LOW_0x0E	= 0x1D,
	ECHO_HIGH_0x0F	= 0x1E,
	ECHO_LOW_0x0F	= 0x1F,
	ECHO_HIGH_0x10	= 0x20,
	ECHO_LOW_0x10	= 0x21,
	ECHO_HIGH_0x11	= 0x22,
	ECHO_LOW_0x11	= 0x23,
};

/*
 * defines all possible commands for the ultrasonic sensor
 * */
enum class UltraSonicCommands : alt_u8 {
	START_MEAS_INCHES			= 0x50,
	START_MEAS_CM				= 0x51,
	START_MEAS_TIME_MICROSEC 	= 0x52,
	START_MEAS_INCHES_ANN		= 0x53,
	START_MEAS_CM_ANN			= 0x54,
	START_MEAS_TIME_MICROSEC_ANN= 0x55,
	CHANGE_ADDRESS_COMMAND_1	= 0xA0,
	CHANGE_ADDRESS_COMMAND_2	= 0xA5,
	CHANGE_ADDRESS_COMMAND_3	= 0xAA,
};

/*
 * represents a ultrasonic hardware device
 * */
class UltraSonicDevice {
private:
	/* no default cstr is allowed */
	UltraSonicDevice() = delete;

	/* used for broadcasting a command to all devices on the iic bus */
	static const alt_u8 __broadcastAddress = 0;
	UltraSonicAddress __deviceAddress;
public:
	UltraSonicDevice(const UltraSonicAddress deviceAddress);
	alt_u8 writeRegister(const UltraSonicRegistersWrite reg, const alt_u8 val);
	alt_u8 readRegister(const UltraSonicRegisterRead reg, alt_u8& readPtr);

	alt_u8 readMeasurement(alt_u8* const ultrasonic_measurement);

	alt_u8 changeAddress(const UltraSonicAddress currentAddress, const UltraSonicAddress newAddress);
};

#endif /* ULTRASONIC_HPP_ */
