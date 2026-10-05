#include <assert.h>
#include <stdio.h>
#include "lin_protocol.h"
static void test_pid(void){for(uint8_t id=0U;id<64U;++id){uint8_t pid=lin_make_pid(id);assert(lin_validate_pid(pid));assert(lin_extract_id(pid)==id);}}
static void test_checksum(void){LinFrame f={.id=0x11U,.pid=lin_make_pid(0x11U),.length=3U,.data={0x10U,0x20U,0x30U},.checksum_type=LIN_CHECKSUM_ENHANCED};f.checksum=lin_checksum(&f);assert(lin_validate_frame(&f)==LIN_OK);f.data[1]^=1U;assert(lin_validate_frame(&f)==LIN_ERR_CHECKSUM);}
static void test_bad_pid(void){LinFrame f={.id=0x11U,.pid=(uint8_t)(lin_make_pid(0x11U)^0x40U),.length=1U,.data={0x55U},.checksum_type=LIN_CHECKSUM_ENHANCED};f.checksum=lin_checksum(&f);assert(lin_validate_frame(&f)==LIN_ERR_PID);}
int main(void){test_pid();test_checksum();test_bad_pid();puts("LIN protocol tests: PASS");return 0;}
