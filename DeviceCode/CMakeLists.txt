# I target a recent cmake, it shouldn't be a problem on a dev machine
cmake_minimum_required(VERSION 3.11)

##############################################################################################################################################################
###================================================================= ARDUINO SETUP ========================================================================###
##############################################################################################################################################################

#Project name
set(PROJECT_NAME FreeRTOS_Demo)

# Product filename
set(PRODUCT_NAME FreeRTOS_Demo)

# The MCU you're going to use.
set(MCU atmega2560)

## Chip frequency
set(F_CPU 16000000UL)

# BAUDRATE
set(BAUD 115200)

#Programmer type
set(PROG_TYPE arduino)

# Set the port that arduino is connected to.
set(PORT COM6)

# Use AVR GCC toolchain setup
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER $ENV{AVR8_BIN}/avr-g++)
set(CMAKE_C_COMPILER $ENV{AVR8_BIN}/avr-gcc)


##############################################################################################################################################################
###============================================================== LINKING LIBS / SRC ======================================================================###
##############################################################################################################################################################


# Pass defines to compiler
add_definitions(
        -DF_CPU=${F_CPU}
)

# Sets linker MMCU linker flag
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

if((NOT EXISTS "${PROJECT_SOURCE_DIR}/include"))
    message("Unable to find INCLUDE folder, attempting to create include folder")
    FILE(MAKE_DIRECTORY include)
endif()

if((NOT EXISTS "${PROJECT_SOURCE_DIR}/src"))
    message("Unable to find SRC folder, attempting to create src folder")
    FILE(MAKE_DIRECTORY src)
endif()


file(GLOB SRC_FILES "src/*.c") # Load all files in src folder
file(GLOB HEADER_FILES "include/*.h")
ADD_LIBRARY(GENERAL_LIB ${SRC_FILES} ${HEADER_FILES})


#Pass wall config here if you want to have a strict compiler
add_compile_options(
        -mmcu=${MCU} # MCU
        -std=gnu99 # C99 standard
        -Os # optimize
        -Wno-main
        -Wfatal-errors
        -Wl,--relax,--gc-sections
        -g
        -gdwarf-2
        -funsigned-char # a few optimizations
        -funsigned-bitfields
        -fpack-struct
        -fshort-enums
        -ffunction-sections
        -fdata-sections
        -fno-split-wide-types
        -fno-tree-scev-cprop
)

# Create one target
add_executable(${PRODUCT_NAME} main.c ${SRC_FILES})



##############################################################################################################################################################
###============================================================ COMPILE / UPLOAD SETUP ====================================================================###
##############################################################################################################################################################


# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Strip binary for upload
add_custom_target(strip ALL $ENV{AVR8_BIN}/avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL $ENV{AVR8_BIN}/avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)
# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
add_custom_target(eeprom $ENV{AVR8_BIN}/avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

# Upload the firmware with avrdude
add_custom_target(upload $ENV{AVRDUDE}/avrdude -c "$ENV{AVRDUDE}\\avrdude.conf" -p ${MCU} -cwiring -P ${PORT} -b ${BAUD} -D -U  flash:w:${PRODUCT_NAME}.hex DEPENDS hex)

##############################################################################################################################################################
###================================================================ FREERTOS SETUP ========================================================================###
##############################################################################################################################################################

set(FREE_RTOS_PATH "${PROJECT_SOURCE_DIR}/FreeRTOS")



if((NOT EXISTS "${FREE_RTOS_PATH}"))
    message("Unable to find RTOS folder, attempting to create a repo")
    FILE(MAKE_DIRECTORY FreeRTOS)
    execute_process(COMMAND git init WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    execute_process(COMMAND git submodule add https://github.com/ihavn/VIA_FreeRTOS_AVRMEGA WORKING_DIRECTORY ${FREE_RTOS_PATH})
    FILE(REMOVE ${FREE_RTOS_PATH}/VIA_FreeRTOS_AVRMEGA/.gitignore)
endif()

include_directories(${PROJECT_SOURCE_DIR}/FreeRTOS/VIA_FreeRTOS_AVRMEGA/src)


############################################ FREE RTOS LINKER SETUP ###########################################################

file(GLOB RTOS_SRC_FILES "${PROJECT_SOURCE_DIR}/FreeRTOS/VIA_FreeRTOS_AVRMEGA/src/*.c") # Load all files in src folder
file(GLOB RTOS_DRIVER_SRC_FILES "${PROJECT_SOURCE_DIR}/FreeRTOS/VIA_FreeRTOS_AVRMEGA/FreeRTOSTraceDriver/*.c") # Load all files in src folder

############################################ ACTUAL SOURCE LINKER SETUP #######################################################

############################################ LIBRARY LINKING ##################################################################

ADD_LIBRARY(RTOS_LIB ${RTOS_SRC_FILES} ${RTOS_DRIVER_SRC_FILES})

#UNCOMMENT IN YOU NEED TO LINK .A FILES
target_link_libraries(${PRODUCT_NAME} "${PROJECT_SOURCE_DIR}/SensorDrivers/libIotLibrary.a")
target_link_libraries(${PROJECT_NAME} RTOS_LIB)

include_directories($ENV{AVR8_HOME}/avr/include/avr)
include_directories($ENV{AVR8_HOME}/avr/include/util)
include_directories(SensorDrivers)
include_directories(include)

