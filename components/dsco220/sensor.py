import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import DEVICE_CLASS_CARBON_DIOXIDE, ICON_MOLECULE_CO2, UNIT_PARTS_PER_MILLION

DEPENDENCIES = ["uart"]

dsco220_ns = cg.esphome_ns.namespace("dsco220")
DSCO220Sensor = dsco220_ns.class_(
    "DSCO220Sensor", cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        DSCO220Sensor,
        unit_of_measurement=UNIT_PARTS_PER_MILLION,
        device_class=DEVICE_CLASS_CARBON_DIOXIDE,
        icon=ICON_MOLECULE_CO2,
        accuracy_decimals=0,
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
