// Copyright 2024 hafu (@hafu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

// Hardware configuration / serial pins
#define SERIAL_PIO_USE_PIO1
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

// Enter mass storage UF2 boot-loader via double-tap of reset button
// https://docs.qmk.fm/platformdev_rp2040#double-tap
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25

// detect main half of split via VBUS
#define USB_VBUS_PIN GP24
