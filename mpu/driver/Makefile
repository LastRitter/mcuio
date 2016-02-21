# This comes from the zio Makefile

TARGET		= mcuio
obj-m		= $(TARGET).o

KERNEL_DIR	= /lib/modules/$(shell uname -r)/build
MODULE_DIR	= $(shell pwd)
DEST_DIR	= /opt/

EXTRA_CFLAGS	:= -g

.PHONY : all clean install

all : $(TARGET).ko

clean : 
	    rm -rfv $(TARGET) *.o *~core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers

install : 
	    cp $(TARGET).ko $(DEST_DIR) -f


CONFIG_MCUIO_HC				= y
EXTRA_CFLAGS	+= -DMCUIO_HC

CONFIG_MCUIO_LDISC			= y
EXTRA_CFLAGS	+= -DMCUIO_LDISC

CONFIG_MCUIO_ADC			= n
#EXTRA_CFLAGS	+= -DMCUIO_ADC

CONFIG_MCUIO_GPIO			= y
EXTRA_CFLAGS	+= -DMCUIO_GPIO

CONFIG_MCUIO_HID			= y
EXTRA_CFLAGS	+= -DMCUIO_HID

CONFIG_MCUIO_I2C			= y
EXTRA_CFLAGS	+= -DMCUIO_I2C

CONFIG_MCUIO_PWM			= n
#EXTRA_CFLAGS	+= -DMCUIO_PWM


CONFIG_MCUIO_REGMAP			= y

CONFIG_MCUIO_JS_SHIELD			= n
CONFIG_MCUIO_LUCKY_SHIELD		= n
CONFIG_MCUIO_DIGITALIO_SHIELD		= n
CONFIG_MCUIO_DOGOLED_SHIELD		= n

CONFIG_MCUIO_SHIELDS_MANUAL_PROBE	= n

CONFIG_MCUIO_IRQ_TEST			= n


$(TARGET)-y					= core.o bus.o sysfs.o

$(TARGET)-$(CONFIG_MCUIO_HC)			+= mcuio-hc-drv.o mcuio-hc-dev.o mcuio-soft-hc.o mcuio-soft-local-irq-ctrl-msg-dev.o
$(TARGET)-$(CONFIG_MCUIO_LDISC)			+= mcuio-hc-ldisc.o

$(TARGET)-$(CONFIG_MCUIO_ADC)			+= adc-mcuio.o
$(TARGET)-$(CONFIG_MCUIO_GPIO)			+= gpio-mcuio.o
$(TARGET)-$(CONFIG_MCUIO_HID)			+= hid-mcuio.o
$(TARGET)-$(CONFIG_MCUIO_I2C)			+= i2c-mcuio.o
$(TARGET)-$(CONFIG_MCUIO_PWM)			+= pwm-mcuio.o
$(TARGET)-$(CONFIG_MCUIO_REGMAP)		+= regmap-mcuio.o

$(TARGET)-$(CONFIG_MCUIO_JS_SHIELD)		+= mcuio-js-shield.o
$(TARGET)-$(CONFIG_MCUIO_LUCKY_SHIELD)		+= mcuio-lucky-shield.o
$(TARGET)-$(CONFIG_MCUIO_DIGITALIO_SHIELD)	+= mcuio-dio-shield.o
$(TARGET)-$(CONFIG_MCUIO_DOGOLED_SHIELD)	+= mcuio-dogoled-shield.o

$(TARGET)-$(CONFIG_MCUIO_SHIELDS_MANUAL_PROBE)	+= mcuio-shields-manprobe.o

$(TARGET)-$(CONFIG_MCUIO_IRQ_TEST)		+= mcuio-irq-test.o


$(TARGET).ko : $(wildcard ./*.c) $(wildcard ./*.h)
	    make -C $(KERNEL_DIR) M=$(MODULE_DIR) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules



