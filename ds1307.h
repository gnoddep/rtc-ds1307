#ifndef NERDMAN_DS1307_H
#define NERDMAN_DS1307 H

#include <linux/ioctl.h>

#define DS1307_MAJOR_NUM 100
#define DS1307_DEV_NAME "ds1307"

#define DS1307_ENABLE_SQW _IOW(DS1307_MAJOR_NUM, 0, unsigned int)
#define DS1307_DISABLE_SQW _IO(DS1307_MAJOR_NUM, 1)
#define DS1307_SQW_STATUS _IOR(DS1307_MAJOR_NUM, 2, unsigned int)

#endif
