# JK-BMS Monitor using RS485-TTL

Arduino code used to read voltages of cells, cell count, remain capacity, charging current and pack voltage. This code used to monitor 8 cells of LiFEPo4, 24 Battery pack using JK-B1A8S20P

(Note: JK-BMS RS485 adapter GND and RS-485_TTL module GND need to connect to avoid data packet drop issues)


# Schematics 3.3V
<img src="BMS-RS485-TTL-and-Wemos-with-3v3.JPG"/>

# RS485 - TTL Module
<img src="rs485_ttl_module.jpg"/>
`https://tronic.lk/product/xy-017-uart-ttl-to-rs485-3-3v-5v-module-for-arduino`

# WeMos Module
<img src="WeMosD1Mini_pinout.png"/>
`https://tronic.lk/product/nodemcu-d1-mini-lua-wifi-wemos-4m-esp8266-module`

# JK-BMS RS485 adapter
<img src="JK RS485 adapter.jpg"/>

## References

* https://github.com/dj-nitehawk/jk-bms-test
* https://github.com/dj-nitehawk/Hybrid-Inverter-Monitor
