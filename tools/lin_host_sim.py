#!/usr/bin/env python3
def make_pid(frame_id:int)->int:
    frame_id&=0x3F
    p0=((frame_id>>0)^(frame_id>>1)^(frame_id>>2)^(frame_id>>4))&1
    p1=1^(((frame_id>>1)^(frame_id>>3)^(frame_id>>4)^(frame_id>>5))&1)
    return frame_id|(p0<<6)|(p1<<7)
def checksum(pid:int,data:list[int],enhanced:bool=True)->int:
    total=pid if enhanced else 0
    for value in data:
        total+=value
        if total>0xFF:total-=0xFF
    return (~total)&0xFF
if __name__=="__main__":
    data=[0x34,0x12,60,0];pid=make_pid(0x11)
    print(f"BREAK SYNC=55 PID={pid:02X} DATA={' '.join(f'{x:02X}' for x in data)} CHK={checksum(pid,data):02X}")
