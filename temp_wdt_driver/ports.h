#ifndef _OMAP_WATCHDOG_H
#define _OMAP_WATCHDOG_H

#define WATCHDOG_REV		(0x00)
#define WATCHDOG_SYS_CONFIG	(0x10)
#define WATCHDOG_STATUS		(0x14)
#define WATCHDOG_CNTRL		(0x24)
#define WATCHDOG_CRR		(0x28)
#define WATCHDOG_LDR		(0x2c)
#define WATCHDOG_TGR		(0x30)
#define WATCHDOG_WPS		(0x34)
#define WATCHDOG_SPR		(0x48)

/* Using the prescaler, the OMAP watchdog could go for many
 * months before firing.  These limits work without scaling,
 * with the 60 second default assumed by most tools and docs.
 */
#define TIMER_MARGIN_DEFAULT	60	/* 60 secs */


#endif				/* _OMAP_WATCHDOG_H */
