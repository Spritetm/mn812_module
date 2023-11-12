#pragma once
#include <stdint.h>

//Known register addresses

#define AUDBRD_REG_ROTARY_CNT(n) (0x80+n)
#define AUDBRD_REG_ROTARY_LED(n) (0x80+n)
#define AUDBRD_REG_BTN_LED(n) (0xA0+n)
#define AUDBRD_REG_FPGA_CLK0 0xF0
#define AUDBRD_REG_FPGA_CLK1 0xF1
#define AUDBRD_REG_FPGA_RESET 0xF2
#define AUDBRD_REG_DIM_ROTARYLED1 0xFA
#define AUDBRD_REG_DIM_ROTARYLED2 0xFB
#define AUDBRD_REG_DIM_BTNLED_RED 0xFC
#define AUDBRD_REG_DIM_BTNLED_GREEN 0xFD
#define AUDBRD_REG_BTN_CTL 0xFE

//Note: these are dependent on the FPGA bitstream included in this project
#define AUDBRD_REG_CHAR_COLDATA(i) (0x00+i)
#define AUDBRD_REG_CHAR_CHARSEL (0x08)

//Write a value to a certain register address.
void audbrd_bus_write(uint8_t address, uint16_t data);

//Read a value from a certain register address
uint16_t audbrd_bus_read(uint8_t address);

//Startup function
void audbrd_bus_setup();
