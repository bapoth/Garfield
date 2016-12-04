#creating a new driver
create_driver PWM_Generator_driver

#Associate with the hardware version
set_sw_property hw_class_name PWM_Generator

set_sw_property min_compatible_hw_version 1.0

#driver version
set_sw_property version 1.0

#do not automatic intializing the driver
set_sw_property auto_initialize false

#for copying into the BSP
set_sw_property bsp_subdirectory drivers


#
# Source files
#

# c files
add_sw_property c_source HAL/src/PWM_Generator.c

# include files
add_sw_property include_source HAL/inc/PWM_Generator.h
add_sw_property include_source inc/PWM_Generator_regs.h

# This driver supports HAL & UCOSII BSP (OS) types
add_sw_property supported_bsp_type HAL
add_sw_property supported_bsp_type UCOSII
