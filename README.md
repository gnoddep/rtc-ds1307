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

To install, make sure you have a decent build environment, the following
instructions are for the Raspberry Pi

```bash
# Make sure you have the latest kernel and sources:
$ rpi-update            # sudo apt-get install rpi-update
$ rpi-source            # https://github.com/notro/rpi-source

$ make
$ sudo make install
$ sudo depmod           # Because somehow make install did not do this correctly

# Disable loading of the original rtc_ds1307 module
$ sudo echo "blacklist rtc_ds1307" >/etc/modprobe.d/rtc.conf

# Make sure the rtc and this module are loaded at boottime
sudo echo "dtoverlay=i2c-rtc,ds1307" >>/boot/config

# If you have already loaded the original rtc_ds1307 module
sudo rmmod rtc_ds1307

# Load the module
modprobe rtc_ds1307_nerdman
```

If you want to allow access to the `/dev/rtc*` and `/dev/ds1307/sqw` devices by
non-root users, use the following udev rules and add the user to the `rtc` group

```bash
cat >/etc/udev/rules.d/99-rtc.rules <<EOF
SUBSYSTEM=="rtc", GROUP="rtc", MODE="0660"
SUBSYSTEM=="ds1307", GROUP="rtc", MODE="0660"
EOF
```

