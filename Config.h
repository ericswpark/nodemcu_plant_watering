#ifndef CONFIG_H
#define CONFIG_H

// Set a different ADS1115 address if you set the ADDR pin differently
#define ADS1X15_ADDR 0x48
// How many channels are there?
// NOTE: parts of the sketch still assume 4 channels. This needs a rewrite in the future.
#define CHANNEL_COUNT 4
// Map the relay output pins here
#define RELAY_ONE D3
#define RELAY_TWO D4
#define RELAY_THREE D5
#define RELAY_FOUR D6
// Set if the relay is flipped (HIGH results in off)
#define RELAY_REVERSE true


#endif