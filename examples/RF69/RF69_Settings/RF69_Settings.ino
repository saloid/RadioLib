/*
   RadioLib RF69 Settings Example

   This example shows how to change all the properties of RF69 radio.
   RadioLib currently supports the following settings:
    - pins (SPI slave select, digital IO 0, digital IO 1)
    - carrier frequency
    - bit rate
    - receiver bandwidth
    - allowed frequency deviation
    - output power during transmission
    - sync word

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

// RF69 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// DIO1 pin:  3
RF69 rf1 = new Module(10, 2, 3);

// or using RadioShield
// https://github.com/jgromes/RadioShield
RF69 rf2 = RadioShield.ModuleB;

void setup() {
  Serial.begin(9600);

  // initialize RF69 with default settings
  Serial.print(F("[RF69] Initializing ... "));
  // carrier frequency:                   434.0 MHz
  // bit rate:                            48.0 kbps
  // Rx bandwidth:                        125.0 kHz
  // frequency deviation:                 50.0 kHz
  // output power:                        13 dBm
  // sync word:                           0x2D01
  int state = rf1.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // initialize RF69 with non-default settings
  Serial.print(F("[RF69] Initializing ... "));
  // carrier frequency:                   868.0 MHz
  // bit rate:                            300.0 kbps
  // Rx bandwidth:                        250.0 kHz
  // frequency deviation:                 60.0 kHz
  // output power:                        17 dBm
  // sync word:                           0x2D01
  state = rf2.begin(868.0, 300.0, 250.0, 60.0, 17);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // you can also change the settings at runtime
  // and check if the configuration was changed successfully

  // set carrier frequency to 433.5 MHz
  if (rf1.setFrequency(433.5) == ERR_INVALID_FREQUENCY) {
    Serial.println(F("[RF69] Selected frequency is invalid for this module!"));
    while (true);
  }

  // set bit rate to 100.0 kbps
  state = rf1.setBitRate(100.0);
  if (state == ERR_INVALID_BIT_RATE) {
    Serial.println(F("[RF69] Selected bit rate is invalid for this module!"));
    while (true);
  } else if (state == ERR_INVALID_BIT_RATE_BW_RATIO) {
    Serial.println(F("[RF69] Selected bit rate to bandwidth ratio is invalid!"));
    Serial.println(F("[RF69] Increase receiver bandwidth to set this bit rate."));
    while (true);
  }

  // set receiver bandwidth to 250.0 kHz
  state = rf1.setRxBandwidth(250.0);
  if (state == ERR_INVALID_RX_BANDWIDTH) {
    Serial.println(F("[RF69] Selected receiver bandwidth is invalid for this module!"));
    while (true);
  } else if (state == ERR_INVALID_BIT_RATE_BW_RATIO) {
    Serial.println(F("[RF69] Selected bit rate to bandwidth ratio is invalid!"));
    Serial.println(F("[RF69] Decrease bit rate to set this receiver bandwidth."));
    while (true);
  }

  // set allowed frequency deviation to 10.0 kHz
  if (rf1.setFrequencyDeviation(10.0) == ERR_INVALID_FREQUENCY_DEVIATION) {
    Serial.println(F("[RF69] Selected frequency deviation is invalid for this module!"));
    while (true);
  }

  // set output power to 2 dBm
  if (rf1.setOutputPower(2) == ERR_INVALID_OUTPUT_POWER) {
    Serial.println(F("[RF69] Selected output power is invalid for this module!"));
    while (true);
  }

  // up to 8 bytes can be set as sync word
  // NOTE: sync word must not contain any zero bytes
  // set sync word to 0x0123456789ABCDEF
  uint8_t syncWord[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
  if (rf1.setSyncWord(syncWord, 8) == ERR_INVALID_SYNC_WORD) {
    Serial.println(F("[RF69] Selected sync word is invalid for this module!"));
    while (true);
  }

  Serial.println(F("[RF69] All settings changed successfully!"));

  // RF69 can also measure temperature (roughly)
  // to get correct temperature measurements, the sensor must be calibrated
  // at ambient temperature
  rf1.setAmbientTemperature(25); // replace 25 with your ambient temperature
}

void loop() {
  // measure temperature
  Serial.print(F("[RF69] Measured temperature: "));
  Serial.print(rf1.getTemperature());
  Serial.println(F(" deg C"));

  // wait 100 ms before the next measurement
  delay(100);
}
