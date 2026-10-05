#ifndef LIN_PROTOCOL_H
#define LIN_PROTOCOL_H
#include <stdbool.h>
#include <stdint.h>
#define LIN_MAX_DATA_LEN 8U
typedef enum { LIN_CHECKSUM_CLASSIC = 0, LIN_CHECKSUM_ENHANCED } LinChecksumType;
typedef enum { LIN_OK = 0, LIN_ERR_PARAM, LIN_ERR_PID, LIN_ERR_CHECKSUM } LinStatus;
typedef struct { uint8_t id; uint8_t pid; uint8_t length; uint8_t data[LIN_MAX_DATA_LEN]; uint8_t checksum; LinChecksumType checksum_type; } LinFrame;
uint8_t lin_make_pid(uint8_t id);
bool lin_validate_pid(uint8_t pid);
uint8_t lin_extract_id(uint8_t pid);
uint8_t lin_checksum(const LinFrame *frame);
LinStatus lin_validate_frame(const LinFrame *frame);
#endif
