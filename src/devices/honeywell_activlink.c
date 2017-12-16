/*
* *** Honeywell Activlink Doorbells ***
*/

#include "rtl_433.h"
#include "pulse_demod.h"
#include "util.h"

static int honeywell_callback(bitbuffer_t *bitbuffer) {
    uint8_t buffer[80];
    bitbuffer_extract_bytes(bitbuffer, 0, 0, buffer, 128);

    char raw_str[160];
    for (unsigned n=0; n<sizeof(buffer); n++) { sprintf(raw_str+n*2, "%02x", buffer[n]); }

    data_t *data = data_make(
          "payload", "", DATA_STRING, raw_str,
          NULL);

    data_acquired_handler(data);
    return 1;
}

static char *output_fields[] = {
    "payload",
    NULL
};

r_device honeywell_activlink = {
    .name           = "Honeywell Activlink Doorbell",
    .modulation     = FSK_PULSE_PCM,
    .short_limit    = 39,
    .long_limit     = 39,
    .reset_limit    = 39936,
    .json_callback  = &honeywell_callback,
    .disabled       = 0,
    .demod_arg      = 0,
    .fields         = output_fields,
};
