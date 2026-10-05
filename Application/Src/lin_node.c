#include "lin_node.h"
static LinNodeStatus g_node;
void LinNode_Init(void){g_node=(LinNodeStatus){0};}
void LinNode_SetSensor(uint16_t raw){g_node.sensor_raw=raw;}
void LinNode_SetSleeping(uint8_t sleeping){g_node.sleeping=sleeping?1U:0U;}
static uint8_t clamp_percent(uint8_t v){return v>100U?100U:v;}
void LinNode_ProcessFrame(const LinFrame *f){if(f==0)return;LinStatus s=lin_validate_frame(f);if(s!=LIN_OK){if(s==LIN_ERR_PID)++g_node.pid_errors;else if(s==LIN_ERR_CHECKSUM)++g_node.checksum_errors;return;}++g_node.rx_frames;switch(lin_extract_id(f->pid)){case 0x10U:if(f->length>=1U)g_node.actuator_percent=clamp_percent(f->data[0]);break;case 0x3CU:if(f->length>=1U&&f->data[0]==0x04U)LinNode_ClearErrors();break;default:break;}}
void LinNode_GetStatus(LinNodeStatus *s){if(s!=0)*s=g_node;}
void LinNode_ClearErrors(void){g_node.checksum_errors=0U;g_node.pid_errors=0U;g_node.timeouts=0U;}
uint8_t LinNode_BuildStatusFrame(LinFrame *f){if(f==0)return 0U;f->id=0x11U;f->pid=lin_make_pid(f->id);f->length=4U;f->checksum_type=LIN_CHECKSUM_ENHANCED;f->data[0]=(uint8_t)g_node.sensor_raw;f->data[1]=(uint8_t)(g_node.sensor_raw>>8);f->data[2]=g_node.actuator_percent;f->data[3]=g_node.sleeping;f->checksum=lin_checksum(f);++g_node.tx_frames;return 1U;}
uint8_t LinNode_BuildFeedbackFrame(LinFrame *f){if(f==0)return 0U;f->id=0x12U;f->pid=lin_make_pid(f->id);f->length=2U;f->checksum_type=LIN_CHECKSUM_ENHANCED;f->data[0]=g_node.actuator_percent;f->data[1]=(uint8_t)g_node.rx_frames;f->checksum=lin_checksum(f);++g_node.tx_frames;return 1U;}
