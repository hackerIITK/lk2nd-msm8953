// SPDX-License-Identifier: BSD-3-Clause
/* Copyright (c) 2022, Stephan Gerhold <stephan@gerhold.net> */

#include <debug.h>
#include <lk2nd/init.h>
#include <lk2nd/version.h>

void lk2nd_init(void)
{
	extern void (*__lk2nd_init_start)(void);
	extern void (*__lk2nd_init_end)(void);
	void (**func)(void);

	dprintf(CRITICAL, "[lk2nd] %s (Built: %s)\n", LK2ND_VERSION, LK2ND_BUILD_TIME_IST);
	for (func = &__lk2nd_init_start; func < &__lk2nd_init_end; ++func)
		(*func)();
}
