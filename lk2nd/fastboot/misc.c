// SPDX-License-Identifier: BSD-3-Clause
/* Copyright (c) 2019-2022, Stephan Gerhold <stephan@gerhold.net> */

#include <debug.h>
#include <fastboot.h>
#include <platform.h>

#if WITH_DEBUG_LOG_BUF
static void cmd_oem_log(const char *arg, void *data, unsigned sz)
{
	fastboot_stage(data, log_copy(data));
}
FASTBOOT_REGISTER("oem log", cmd_oem_log);
#endif

static void cmd_oem_reboot_edl(const char *arg, void *data, unsigned sz)
{
	fastboot_okay("");
	reboot_device(EMERGENCY_DLOAD);
}
FASTBOOT_REGISTER("oem reboot-edl", cmd_oem_reboot_edl);

static void cmd_oem_charger(const char *arg, void *data, unsigned sz)
{
	extern unsigned boot_into_charger;
	extern void cmd_continue(const char *arg, void *data, unsigned sz);

	dprintf(INFO, "booting into charger mode\n");
	boot_into_charger = 1;
	fastboot_okay("");
	cmd_continue(NULL, NULL, 0);
}

static void lk2nd_charger_fastboot_register(void)
{
	fastboot_register("oem charger", cmd_oem_charger);
	fastboot_register("reboot-charger", cmd_oem_charger);
}
FASTBOOT_INIT(lk2nd_charger_fastboot_register);
