# Test Plan

Host tests validate all 64 protected identifiers, reject corrupted PID parity, accept a valid enhanced checksum, reject changed data, and reject malformed lengths.

Hardware validation uses a logic analyzer to capture BREAK/SYNC/PID/DATA/CHECKSUM, verifies IDs 0x10/0x11/0x12, and injects PID/checksum faults. Malformed frames must never alter actuator state.
