# Architecture

The project is separated into application, protocol, and driver/BSP layers.

Application owns node state, diagnostics, sensor value, actuator demand, and sleep state. The protocol layer owns PID parity, checksums, frame validation, and frame encoding. Drivers/BSP should connect STM32 UART/LPUART, timer, ADC, PWM, GPIO, and LIN-transceiver signals.

The protocol layer avoids STM32 HAL types, allowing host-side unit testing before hardware integration.
