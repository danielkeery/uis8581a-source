#ifndef __MARLIN3_BASE_GLB_H__
#define __MARLIN3_BASE_GLB_H__

#include <linux/kernel.h>
#include <linux/bitops.h>

#define CP_START_ADDR		0x40500000

#define CP_SDIO_PRIORITY_ADDR 0x40130150

/* set sdio higher priority to visit iram */
#define M6_TO_S0_HIGH_PRIORITY 0X80000000

/* time out in waiting wifi to come up */
#define POWERUP_WAIT_MS	60000

/* define the timeout value when waiting for bt wifi power up */
#define BTWIFI_POWERUP_WAIT_MS 60000

#define AHB_EB0					0x40130004
#define APB_EB					0x40130008

#define BT_EN					BIT(4)
#define WIFI_EN					BIT(5)

#define CLK_CTRL3				0x4083c04c
#define CGM_BT_32M_EN				BIT(18)
#define CGM_BT_64M_EN				BIT(19)

#define BT_32M_CLK_EN				0x4083c050
#define BT_64M_CLK_EN				0x4083c054

#define WCN_PLL_CONFIG			0x4083c040

#define WCN_PLL_CONFIG_32M		BIT(0)
#define WCN_PLL_CONFIG_64M		BIT(1)

#define AHB_EB2					0x4013000c
#define BT_RST					BIT(0)
#define WIFI_RST				BIT(1)

#define WCN_POWERUP_WAIT_MS		60000

#endif