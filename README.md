# STM32 LIN Bus Diagnostic Node with Slave Scheduler

Automotive LIN slave-node reference implementation for STM32, written in Embedded C with a layered protocol/application architecture.

## Overview

The node receives LIN headers from a master, validates protected identifiers, handles scheduled frames, publishes sensor/status data, controls an actuator, and exposes a small application-level diagnostic interface.

## Features

- LIN protected-identifier parity
- Classic and enhanced checksum
- Frame validation
- Automotive-style command/status/feedback frame map
- Diagnostic request handling
- Sensor and actuator abstractions
- Communication error counters
- Host-side protocol tests
- Python LIN frame generator

## Frame Map

| ID | Direction | Purpose |
|---|---|---|
| 0x10 | Master -> Slave | Node command |
| 0x11 | Slave -> Master | Sensor/status |
| 0x12 | Slave -> Master | Actuator feedback |
| 0x3C | Master -> Slave | Diagnostic request |
| 0x3D | Slave -> Master | Diagnostic response |

## Architecture

```text
Application
    |
Protocol / LIN core
    |
Drivers / BSP
    |
STM32 HAL + MCU
```

The protocol core is kept free of STM32 HAL types so it can be unit-tested on a desktop compiler.

## Example LIN Frame

```text
BREAK | SYNC 0x55 | PID | DATA[1..8] | CHECKSUM
```

## Repository Layout

```text
Protocol/
Application/
tests/
tools/
docs/
Makefile.host
```

## Hardware

Recommended: STM32G0/F0 board, LIN transceiver, analog sensor or potentiometer, PWM load, and logic analyzer. Do not connect MCU UART directly to the LIN wire; use a LIN transceiver.

## Host Test

```bash
make -f Makefile.host test
python3 tools/lin_host_sim.py
```

Expected test output:

```text
LIN protocol tests: PASS
```

## Portfolio Value

Demonstrates Embedded C, automotive LIN networking, low-level frame validation, diagnostics, fault handling, testable protocol design, and hardware/software separation.

## Status

Portfolio-ready reference implementation. Generate the exact STM32CubeMX/HAL initialization for the chosen STM32 board and LIN transceiver during hardware integration.

## License

MIT
