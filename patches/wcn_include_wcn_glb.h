#ifndef __WCN_GLB_H__
#define __WCN_GLB_H__

#include <misc/marlin_platform.h>
#include "bufring.h"
#include "wcn_parn_parser.h"
#include "wcn_txrx.h"
#include "wcn_log.h"

#ifdef CONFIG_SC2342_INTEG
#include "sc2342_integrate_glb.h"
#endif

#ifdef CONFIG_SC2355
#include "sc2355_glb.h"
#include "wcn_dump.h"
#endif

#ifdef CONFIG_UMW2652
#include "umw2652_glb.h"
#include "wcn_dump.h"
#endif

#ifdef CONFIG_UMW2653
#include "umw2653_glb.h"
#include "wcn_dump.h"
#endif

/* log buf size */
#define M3E_MDBG_RX_RING_SIZE		(64*1024)
#define M3L_MDBG_RX_RING_SIZE		(96 * 1024)
#define M3_MDBG_RX_RING_SIZE		(96 * 1024)
#define MDBG_RX_RING_SIZE	(128 * 1024)

#endif