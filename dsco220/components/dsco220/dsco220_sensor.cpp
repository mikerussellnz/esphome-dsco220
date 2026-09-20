#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "dsco220_sensor.h"

namespace esphome {
namespace dsco220 {

static const char *TAG = "dsco220.sensor";

static constexpr uint8_t CO2_READ_COMMAND[] = {0x42, 0x4D, 0xE3, 0x00, 0x00, 0x01, 0x72};
static constexpr uint8_t CO2_READ_COMMAND_LENGTH = sizeof(CO2_READ_COMMAND);
static constexpr uint8_t CO2_READ_RESPONSE_LENGTH = 12;
static constexpr uint32_t CO2_READ_TIMEOUT_MS = 1000;
static constexpr uint16_t DSCO220_BAUD_RATE = 9600;

void DSCO220Sensor::setup() {
  ESP_LOGCONFIG(TAG, "DS-CO2-20 initialized");
}

void DSCO220Sensor::update() {
  while (this->available()) {
    uint8_t discarded_byte;
    this->read_byte(&discarded_byte);
  }

  this->flush();
  for (uint8_t index = 0; index < CO2_READ_COMMAND_LENGTH; index++) {
    this->write_byte(CO2_READ_COMMAND[index]);
  }
  this->flush();

  uint8_t response[CO2_READ_RESPONSE_LENGTH];
  uint8_t bytes_read = 0;
  const uint32_t start = millis();

  while ((millis() - start) < CO2_READ_TIMEOUT_MS) {
    if (this->available() >= CO2_READ_RESPONSE_LENGTH) {
      while (this->available() && bytes_read < CO2_READ_RESPONSE_LENGTH) {
        if (!this->read_byte(&response[bytes_read])) {
          break;
        }
        bytes_read++;
      }
      break;
    }
    delay(10);
  }

  const int co2 = bytes_read == CO2_READ_RESPONSE_LENGTH
                      ? (response[4] << 8) | response[5]
                      : -1;

  if (co2 < 0) {
    ESP_LOGW(TAG, "Failed to read CO2 measurement");
    this->status_set_warning();
    return;
  }

  ESP_LOGD(TAG, "CO2: %d ppm", co2);
  this->publish_state(co2);
  this->status_clear_warning();
}

void DSCO220Sensor::dump_config() {
  ESP_LOGCONFIG(TAG, "DS-CO2-20 CO2 sensor");
  ESP_LOGCONFIG(TAG, "  Baud rate: %u", DSCO220_BAUD_RATE);
}

}  // namespace dsco220
}  // namespace esphome
