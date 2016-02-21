/*
 * Copyright 2013 Dog Hunter SA
 *
 * Author Davide Ciminaghi
 * GNU GPLv2
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/completion.h>
#include <linux/spinlock.h>
#include <linux/bitops.h>
#include <linux/i2c.h>
#include "mcuio.h"
#include "mcuio_ids.h"
#include "mcuio-internal.h"

unsigned long int busnum;
spinlock_t busnum_lock;

int mcuio_get_bus(void)
{
	int out;
	spin_lock(&busnum_lock);
	if (busnum == 0xffffffff) {
		out = -ENOMEM;
		goto end;
	}
	out = find_last_bit(&busnum, sizeof(busnum));
	if (out == sizeof(busnum))
		out = 0;
	set_bit(out, &busnum);
end:
	spin_unlock(&busnum_lock);
	return out;
}
EXPORT_SYMBOL(mcuio_get_bus);

void mcuio_put_bus(unsigned n)
{
	clear_bit(n, &busnum);
}
EXPORT_SYMBOL(mcuio_put_bus);

static int match_i2c_mcuio(struct device *dev, void *dummy)
{
	struct mcuio_device *mdev = to_mcuio_dev(dev);
	return mdev->id.class == MCUIO_CLASS_I2C_CONTROLLER;
}

static int match_i2c_adap(struct device *dev, void *dummy)
{
	return dev->type == &i2c_adapter_type;
}

struct i2c_adapter *mcuio_get_i2c_adapter(struct mcuio_device *mdev)
{
	/* Look for mcuio i2c controller device */
	struct device *hcdev = mdev->dev.parent;
	struct device *mcuio_i2c_dev = device_find_child(hcdev,
							 NULL,
							 match_i2c_mcuio);
	struct device *adap_dev;

	if (!mcuio_i2c_dev) {
		dev_err(&mdev->dev,
			"Cannot find mcuio i2c adapter mcuio dev\n");
		return NULL;
	}
	/* Found, now we need the corresponding adapter ... */
	adap_dev = device_find_child(mcuio_i2c_dev, NULL, match_i2c_adap);
	if (!adap_dev) {
		dev_err(&mdev->dev, "Cannot find mcuio i2c adapter\n");
		return NULL;
	}
	return to_i2c_adapter(adap_dev);
}
EXPORT_SYMBOL(mcuio_get_i2c_adapter);

static int __init mcuio_init(void)
{
    int ret = 0;

    spin_lock_init(&busnum_lock);
    
    ret = device_register(&mcuio_bus);
    if(ret != 0)
    {
        printk(KERN_ERR "register mcuio device failed !\n");
        goto mcuio_device_init_failed;
    }

    ret = bus_register(&mcuio_bus_type);
    if(ret != 0)
    {
        printk(KERN_ERR "register mcuio bus failed !\n");
        goto mcuio_bus_init_failed;
    }
    
#ifdef MCUIO_HC
    ret = mcuio_hc_init();
    if(ret != 0)
    {
        printk(KERN_ERR "init mcuio hc failed !\n");
        goto mcuio_hc_init_failed;
    }
#endif /* MCUIO_HC */

#ifdef MCUIO_LDISC
    ret = mcuio_ldisc_init();
    if(ret != 0)
    {
        printk(KERN_ERR "init mcuio ldisc failed !\n");
        goto mcuio_ldisc_init_failed;
    }
#endif /* MCUIO_LDISC */

#ifdef MCUIO_ADC
    ret = mcuio_adc_init();
    if(ret != 0)
    {
        printk(KERN_ERR "init mcuio adc failed !\n");
        goto mcuio_adc_init_failed;
    }
#endif /* MCUIO_ADC */
    
#ifdef MCUIO_GPIO
    ret = mcuio_gpio_init();
    if(ret !=0)
    {
        printk(KERN_ERR "init mcuio gpio failed !\n");
        goto mcuio_gpio_init_failed;
    }
#endif /* MCUIO_GPIO */

    return ret;

#ifdef MCUIO_GPIO
mcuio_gpio_init_failed : 
#endif /* MCUIO_GPIO */

#ifdef MCUIO_ADC
    mcuio_adc_exit();
mcuio_adc_init_failed : 
#endif /* MCUIO_ADC */

#ifdef MCUIO_LDISC
    mcuio_ldisc_exit();
mcuio_ldisc_init_failed : 
#endif /* MCUIO_LDISC */

#ifdef MCUIO_HC
    mcuio_hc_exit();
mcuio_hc_init_failed : 
#endif /* MCUIO_HC */

    bus_unregister(&mcuio_bus_type);

mcuio_bus_init_failed : 
    device_unregister(&mcuio_bus);

mcuio_device_init_failed : 
    return ret;
}

static void __exit mcuio_exit(void)
{
#ifdef MCUIO_GPIO
    mcuio_gpio_exit();
#endif /* MCUIO_GPIO */

#ifdef MCUIO_ADC
    mcuio_adc_exit();
#endif /* MCUIO_ADC */

#ifdef MCUIO_LDISC
    mcuio_ldisc_exit();
#endif /* MCUIO_LDISC */

#ifdef MCUIO_HC
    mcuio_hc_exit();
#endif /* MCUIO_HC */

    bus_unregister(&mcuio_bus_type);

    device_unregister(&mcuio_bus);
 
#ifdef MCUIO_HC
    mcuio_hc_exit();
#endif /* MCUIO_HC */

}

module_init(mcuio_init);
module_exit(mcuio_exit);

MODULE_AUTHOR("Davide Ciminaghi");
MODULE_DESCRIPTION("MCUIO subsys core module");
MODULE_LICENSE("GPL v2");
