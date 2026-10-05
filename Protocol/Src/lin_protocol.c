#include "lin_protocol.h"

static uint8_t p0(uint8_t id){return (uint8_t)(((id>>0)^(id>>1)^(id>>2)^(id>>4))&1U);}
static uint8_t p1(uint8_t id){return (uint8_t)(((id>>1)^(id>>3)^(id>>4)^(id>>5))&1U);}
uint8_t lin_make_pid(uint8_t id){id&=0x3FU;return (uint8_t)(id|(p0(id)<<6)|((uint8_t)!p1(id)<<7));}
bool lin_validate_pid(uint8_t pid){return lin_make_pid((uint8_t)(pid&0x3FU))==pid;}
uint8_t lin_extract_id(uint8_t pid){return (uint8_t)(pid&0x3FU);}
static uint8_t add_mod255(uint8_t sum,uint8_t value){uint16_t n=(uint16_t)sum+value;if(n>255U)n-=255U;return (uint8_t)n;}
uint8_t lin_checksum(const LinFrame *f){if(f==0||f->length>LIN_MAX_DATA_LEN)return 0xFFU;uint8_t s=0U;if(f->checksum_type==LIN_CHECKSUM_ENHANCED)s=add_mod255(s,f->pid);for(uint8_t i=0U;i<f->length;++i)s=add_mod255(s,f->data[i]);return (uint8_t)~s;}
LinStatus lin_validate_frame(const LinFrame *f){if(f==0||f->length>LIN_MAX_DATA_LEN)return LIN_ERR_PARAM;if(!lin_validate_pid(f->pid))return LIN_ERR_PID;if(lin_checksum(f)!=f->checksum)return LIN_ERR_CHECKSUM;return LIN_OK;}
