#pragma once

//Startup function. Uploads the FPGA image.
void audbrd_chardisp_init();

//Set one character to a given (5-byte) bitmap.
void audbrd_chardisp_set_bitmap(int pos, const unsigned char *v);
