```yaml
# Example configuration:

external_components:
  - source: github://mikerussellnz/esphome-dsco220
    refresh: 30s

sensor:
  - platform: dsco220
    name: DS-CO2-20 CO2

uart:
  tx_pin: D0
  rx_pin: D1
  baud_rate: 9600
```