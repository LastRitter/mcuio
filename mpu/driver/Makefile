# This comes from the zio Makefile

TARGET		= mcuio
obj-m		= $(TARGET).o

KERNEL_DIR =/lib/modules/$(shell uname -r)/build
MODULE_DIR =$(shell pwd)
DEST_DIR   =/opt/

all: $(TARGET).ko

$(TARGET).ko : 
	    make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules

clean:
	    rm -rfv $(TARGET) *.o *~core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers

install:
	    cp $(TARGET).ko $(DEST_DIR) -f


CONFIG_MCUIO				= n
CONFIG_MCUIO_LDISC_HC			= n

CONFIG_MCUIO_JS_SHIELD			= n
CONFIG_MCUIO_LUCKY_SHIELD		= n
CONFIG_MCUIO_DIGITALIO_SHIELD		= n
CONFIG_MCUIO_DOGOLED_SHIELD		= n

CONFIG_MCUIO_SHIELDS_MANUAL_PROBE	= n

CONFIG_MCUIO_IRQ_TEST			= n


$(TARGET)-y	= core.o bus.o sysfs.o

$(TARGET)-$(CONFIG_MCUIO)			+= mcuio.o mcuio-hc-drv.o mcuio-hc-dev.o mcuio-soft-hc.o mcuio-soft-local-irq-ctrl-msg-dev.o
$(TARGET)-$(CONFIG_MCUIO_LDISC_HC)		+= mcuio-hc-ldisc.o

$(TARGET)-$(CONFIG_MCUIO_JS_SHIELD)		+= mcuio-js-shield.o
$(TARGET)-$(CONFIG_MCUIO_LUCKY_SHIELD)		+= mcuio-lucky-shield.o
$(TARGET)-$(CONFIG_MCUIO_DIGITALIO_SHIELD)	+= mcuio-dio-shield.o
$(TARGET)-$(CONFIG_MCUIO_DOGOLED_SHIELD)	+= mcuio-dogoled-shield.o

$(TARGET)-$(CONFIG_MCUIO_SHIELDS_MANUAL_PROBE)	+= mcuio-shields-manprobe.o

$(TARGET)-$(CONFIG_MCUIO_IRQ_TEST)		+= mcuio-irq-test.o



