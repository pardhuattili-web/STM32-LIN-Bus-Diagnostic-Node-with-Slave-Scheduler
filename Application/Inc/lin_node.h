#ifndef LIN_NODE_H
#define LIN_NODE_H
#include <stdint.h>
#include "lin_protocol.h"
typedef struct{uint16_t sensor_raw;uint8_t actuator_percent;uint32_t rx_frames;uint32_t tx_frames;uint32_t checksum_errors;uint32_t pid_errors;uint32_t timeouts;uint8_t sleeping;}LinNodeStatus;
void LinNode_Init(void);
void LinNode_ProcessFrame(const LinFrame *frame);
void LinNode_SetSensor(uint16_t raw);
void LinNode_SetSleeping(uint8_t sleeping);
void LinNode_GetStatus(LinNodeStatus *status);
void LinNode_ClearErrors(void);
uint8_t LinNode_BuildStatusFrame(LinFrame *frame);
uint8_t LinNode_BuildFeedbackFrame(LinFrame *frame);
#endif
