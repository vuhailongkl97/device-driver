#ifndef _MY_IOCTL_H
#define _MY_IOCTL_H

#define MAGIC_NUM  'E'
#define SET_BAUBRATE_NO 0x01 
#define GET_INFO_DEV_NO 0x02

#define SET_BAUBRATE  _IOW(MAGIC_NUM, SET_BAUBRATE_NO,unsigned long)
#define GET_INFO_DEV  _IOR(MAGIC_NUM, GET_INFO_DEV_NO, int *)

#endif
