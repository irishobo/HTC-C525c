/* arch/arm/mach-msm/include/mach/BOARD_HTC.h
 * Copyright (C) 2007-2009 HTC Corporation.
 * Author: Thomas Tsai <thomas_tsai@htc.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __ASM_ARCH_MSM_BOARD_HTC_H
#define __ASM_ARCH_MSM_BOARD_HTC_H

#include <linux/types.h>
#include <linux/list.h>
#include <asm/setup.h>

struct msm_pmem_setting{
	resource_size_t pmem_start;
	resource_size_t pmem_size;
	resource_size_t pmem_adsp_start;
	resource_size_t pmem_adsp_size;
	resource_size_t pmem_gpu0_start;
	resource_size_t pmem_gpu0_size;
	resource_size_t pmem_gpu1_start;
	resource_size_t pmem_gpu1_size;
	resource_size_t pmem_camera_start;
	resource_size_t pmem_camera_size;
	resource_size_t ram_console_start;
	resource_size_t ram_console_size;
};

enum {
	MSM_SERIAL_UART1	= 0,
	MSM_SERIAL_UART2,
	MSM_SERIAL_UART3,
#ifdef CONFIG_SERIAL_MSM_HS
	MSM_SERIAL_UART1DM,
	MSM_SERIAL_UART2DM,
#endif
	MSM_SERIAL_NUM,
};

enum {
	KERNEL_FLAG_WATCHDOG_ENABLE = BIT(0),
	KERNEL_FLAG_SERIAL_HSL_ENABLE = BIT(1),
	KERNEL_FLAG_KEEP_CHARG_ON = BIT(2),
	KERNEL_FLAG_APPSBARK = BIT(3),
	KERNEL_FLAG_KMEMLEAK = BIT(4),
	KERNEL_FLAG_RESERVED_5 = BIT(5),
	KERNEL_FLAG_RESERVED_6 = BIT(6),
	KERNEL_FLAG_RESERVED_7 = BIT(7),
	KERNEL_FLAG_PVS_SLOW_CPU = BIT(8),
	KERNEL_FLAG_PVS_NOM_CPU = BIT(9),
	KERNEL_FLAG_PVS_FAST_CPU = BIT(10),
#if defined (CONFIG_ARCH_MSM8960) || defined(CONFIG_ARCH_MSM8930)
	KERNEL_FLAG_ENABLE_SSR_MODEM = BIT(11),
#else
	KERNEL_FLAG_RESERVED_11 = BIT(11),
#endif
	KERNEL_FLAG_RESERVED_12 = BIT(12),
	KERNEL_FLAG_DISABLE_WAKELOCK = BIT(13),
	KERNEL_FLAG_PA_RECHARG_TEST = BIT(14),
	KERNEL_FLAG_TEST_PWR_SUPPLY = BIT(15),
	KERNEL_FLAG_RESERVED_16 = BIT(16),
	KERNEL_FLAG_RIL_DBG_RMNET = BIT(17),
	KERNEL_FLAG_RESERVED_18 = BIT(18),
	KERNEL_FLAG_RESERVED_19 = BIT(19),
	KERNEL_FLAG_RESERVED_20 = BIT(20),
	KERNEL_FLAG_RESERVED_21 = BIT(21),
	KERNEL_FLAG_RIL_DBG_MEMCPY = BIT(22),
	KERNEL_FLAG_RESERVED_23 = BIT(23),
	KERNEL_FLAG_RESERVED_24 = BIT(24),
	KERNEL_FLAG_PM_MONITOR = BIT(25),
	KERNEL_FLAG_RESERVED_26 = BIT(26),
	KERNEL_FLAG_RESERVED_27 = BIT(27),
	KERNEL_FLAG_RESERVED_28 = BIT(28),
	KERNEL_FLAG_ENABLE_BMS_CHARGER_LOG = BIT(29),
	KERNEL_FLAG_RPM_DISABLE_WATCHDOG = BIT(30),
	KERNEL_FLAG_GPIO_DUMP = BIT(31),
};

/* common init routines for use by arch/arm/mach-msm/board-*.c */

void __init msm_add_usb_devices(void (*phy_reset) (void));
void __init msm_add_mem_devices(struct msm_pmem_setting *setting);
void __init msm_init_pmic_vibrator(void);

struct mmc_platform_data;
int __init msm_add_sdcc_devices(unsigned int controller, struct mmc_platform_data *plat);
int __init msm_add_serial_devices(unsigned uart);

#if defined(CONFIG_USB_FUNCTION_MSM_HSUSB)
/* START: add USB connected notify function */
struct t_usb_status_notifier{
	struct list_head notifier_link;
	const char *name;
	void (*func)(int online);
};
	int usb_register_notifier(struct t_usb_status_notifier *);
	static LIST_HEAD(g_lh_usb_notifier_list);
/* END: add USB connected notify function */
#endif

int __init board_mfg_mode(void);
int __init parse_tag_smi(const struct tag *tags);
int __init parse_tag_hwid(const struct tag * tags);
int __init parse_tag_skuid(const struct tag * tags);
int parse_tag_engineerid(const struct tag * tags);
int __init parse_tag_smlog(const struct tag *tags);

char *board_serialno(void);
unsigned long get_kernel_flag(void);
unsigned int get_radio_flag(void);
unsigned int get_tamper_sf(void);

#endif
