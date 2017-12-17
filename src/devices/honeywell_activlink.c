/*
* *** Honeywell Activlink Doorbells ***
*/

#include "rtl_433.h"
#include "pulse_demod.h"
#include "util.h"

static int honeywell_callback(bitbuffer_t *bitbuffer) {
    fprintf(stderr, "bitbuffer:: Number of rows: %d \n", bitbuffer->num_rows);
    for (uint16_t row = 0; row < bitbuffer->num_rows; ++row) {
        fprintf(stderr, "[%02d] {%d} ", row, bitbuffer->bits_per_row[row]);
        for (uint16_t col = 0; col < (bitbuffer->bits_per_row[row]+7)/8; ++col) {
            fprintf(stderr, "%02x ", bitbuffer->bb[row][col]);
        }
        fprintf(stderr, "\n");
    }

    return 0;
}

static char *output_fields[] = {
    "payload",
    NULL
};

r_device honeywell_activlink = {
    .name           = "Honeywell Activlink Doorbell",
    .modulation     = OOK_PULSE_PWM_TERNARY,
    .short_limit    = 64,
    .long_limit     = 128,
    .reset_limit    = 1200,
    .json_callback  = &honeywell_callback,
    .disabled       = 0,
    .demod_arg      = 2,
    .fields         = output_fields,
};

