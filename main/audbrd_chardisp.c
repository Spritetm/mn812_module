#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "audbrd_bus.h"
#include "font-5x7.h"

extern const uint8_t audsch_bit_start[] asm("_binary_audsch_bit_start");
extern const uint8_t audsch_bit_end[] asm("_binary_audsch_bit_end");

void audbrd_chardisp_init() {
	const uint8_t *p=audsch_bit_start;
	//skip to sync
	while (!(p[0]==0xff && p[1]==0x20)) p++;

	//reset fpga into download mode
	audbrd_bus_write(AUDBRD_REG_FPGA_RESET, 0x0);

	//Send bitstream as bits
	while (p!=audsch_bit_end) {
		for (int bit=0x80; bit!=0; bit=bit>>1) {
			int b=((*p)&bit)?0x01:0x00;
			audbrd_bus_write(AUDBRD_REG_FPGA_CLK0, b);
			audbrd_bus_write(AUDBRD_REG_FPGA_CLK1, b);
		}
		p++;
	}
	//Add some dummy bits
	for (int i=0; i<32; i++) {
		audbrd_bus_write(AUDBRD_REG_FPGA_CLK0, 0);
		audbrd_bus_write(AUDBRD_REG_FPGA_CLK1, 0);
	}
}


void audbrd_chardisp_set_bitmap(int pos, unsigned char *v) {
	audbrd_bus_write(AUDBRD_REG_CHAR_CHARSEL, pos);
	
	for (int i=0; i<5; i++) {
		audbrd_bus_write(AUDBRD_REG_CHAR_COLDATA(i), v[i]);
	}
}

void audbrd_chardisp_set_char(int pos, unsigned char c) {
	audbrd_chardisp_set_bitmap(pos, &font_data[(c)*5]);
}

