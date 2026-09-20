# ESPHome component for DS-CO2-20 CO2 Sensor.

```yaml
# Example ESPHome configuration:

external_components:
  - source: github://mikerussellnz/esphome-dsco220
    refresh: 30s

sensor:
  - platform: dsco220
    name: DS-CO2-20 CO2
    uart_id: uart_co2

uart:
  - id: uart_co2
    tx_pin: GPIO10
    rx_pin: GPIO11
    baud_rate: 9600
```