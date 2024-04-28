// Copyright 2024 hafu (@hafu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// may change later to default MASTER_LEFT
#define MASTER_RIGHT
// increase speed of i2c communication (default 400000)
#define F_SCL 800000L
//#define F_SCL 727000L
//#define F_SCL 667000L
