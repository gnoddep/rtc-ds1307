Based on the kernel module in linux 4.9

This is a very dirty hack to be able to set the external interrupt pin (SQW)
of the DS1307 RTC chip. **It is only tested on a Raspberry Pi rev 2**

It creates a character device at /dev/ds1307/sqw which can be opened and the
following ioctl calls are supported:

* `DS1307_ENABLE_SQW`  - Enable the SQW interrupt at the given frequency
  (1, 4096, 8092, 32768 are supported, other values will throw an error), pass
  the actual value, not the bitmap that the controller expects
* `DS1307_DISABLE_SQW` - Disable the SQW and reset the frequency to 1Hz
* `DS1307_SQW_STATUS`  - Read the value of the control registry, if bit 4 is 1
  then the interrupt is enabled, if it's 0, the interrupt is disabled.
  
  Bit 0 and 1 represent the frequency:
  - 00b (0x00): 1Hz
  - 01b (0x01): 4096Hz
  - 10b (0x02): 8092Hz
  - 11b (0x03): 32768Hz
