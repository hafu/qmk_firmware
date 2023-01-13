/* Copyright 2021 Hannes Fuchs (hafu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

RGB_MATRIX_EFFECT(STATIC_ALPHAS)
RGB_MATRIX_EFFECT(GAMING)
RGB_MATRIX_EFFECT(GAMING_FIXED_COLORS)
RGB_MATRIX_EFFECT(TEST)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// shared vars
const uint8_t LED_INDEX_WASD_SPACE[] = {
    9, 14, 15, 21, 33
};
// key index of numbers (1-4)
const uint8_t LED_INDEX_NUMBERS_1_TO_4[] = {
    7, 13, 19, 24 //, 29, 35, 40, 45, 51, 57
};
// key index of q and e
const uint8_t LED_INDEX_QE[] = {
    8, 20
};
// key index of tab, shift, ctrl
const uint8_t LED_INDEX_MODS[] = {
    2, 4, 5
};

#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])
// NOTE: this function is declared in the keymap.c and linked later
void rgb_matrix_set_color_led_list(const uint8_t* led_array, size_t size, RGB* rgb);


// static colors for alpahs, for testing led flag map
static bool STATIC_ALPHAS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i <= led_max; ++i) {
        RGB_MATRIX_TEST_LED_FLAGS();
        //if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_ALPHAS) ) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, RGB_MAGENTA);
	    // sidebars
        } else if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
            rgb_matrix_set_color(i, RGB_GREEN);
        } else {
            rgb_matrix_set_color(i, RGB_WHITE);
        }
    }
    return led_max < RGB_MATRIX_LED_COUNT;
}

// gaming, colors can be changed via speed, hue and sat
static bool GAMING(effect_params_t* params) {

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed;
    RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed;
    RGB rgb3 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed;
    RGB rgb4 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed;
    // lower the brightness of other keys
    hsv.v = rgb_matrix_config.hsv.v / 8;
    RGB rgb5 = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb5.r, rgb5.g, rgb5.b);
    }
    rgb_matrix_set_color_led_list(LED_INDEX_WASD_SPACE, ARRAYSIZE(LED_INDEX_WASD_SPACE), &rgb1);
    rgb_matrix_set_color_led_list(LED_INDEX_NUMBERS_1_TO_4, ARRAYSIZE(LED_INDEX_NUMBERS_1_TO_4), &rgb2);
    rgb_matrix_set_color_led_list(LED_INDEX_QE, ARRAYSIZE(LED_INDEX_QE), &rgb3);
    rgb_matrix_set_color_led_list(LED_INDEX_MODS, ARRAYSIZE(LED_INDEX_MODS), &rgb4);

    return led_max < RGB_MATRIX_LED_COUNT;
}

// test pattern for colors
static bool TEST(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        rgb_matrix_set_color_all(RGB_OFF);
    }

    rgb_matrix_set_color(0, RGB_WHITE);
    rgb_matrix_set_color(6, RGB_RED);
    rgb_matrix_set_color(12, RGB_CORAL);
    rgb_matrix_set_color(18, RGB_ORANGE);
    rgb_matrix_set_color(23, RGB_GOLDENROD);
    rgb_matrix_set_color(28, RGB_GOLD);
    rgb_matrix_set_color(34, RGB_YELLOW);
    rgb_matrix_set_color(39, RGB_CHARTREUSE);
    rgb_matrix_set_color(44, RGB_GREEN);
    rgb_matrix_set_color(50, RGB_SPRINGGREEN);
    rgb_matrix_set_color(56, RGB_TURQUOISE);
    rgb_matrix_set_color(61, RGB_TEAL);
    rgb_matrix_set_color(66, RGB_CYAN);
    rgb_matrix_set_color(1, RGB_AZURE);
    rgb_matrix_set_color(7, RGB_BLUE);
    rgb_matrix_set_color(13, RGB_PURPLE);
    rgb_matrix_set_color(19, RGB_MAGENTA);
    rgb_matrix_set_color(24, RGB_PINK);

    return led_max < RGB_MATRIX_LED_COUNT;
}

// gaming with fixed defined colors
static bool GAMING_FIXED_COLORS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // get current brightness
    uint8_t brightness = rgb_matrix_config.hsv.v;

    // turn all off on init
    if (params->init) {
        rgb_matrix_set_color_all(RGB_OFF);
    }

    // color definitions for different keys and adjust brightness to current level
    HSV hsv1 = { HSV_MAGENTA };
    hsv1.v = brightness;
    RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv1);
    HSV hsv2 = { HSV_GREEN };
    hsv2.v = brightness;
    RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv2);
    HSV hsv3 = { HSV_CYAN };
    hsv3.v = brightness;
    RGB rgb3 = rgb_matrix_hsv_to_rgb(hsv3);
    HSV hsv4 = { HSV_ORANGE };
    hsv4.v = brightness;
    RGB rgb4 = rgb_matrix_hsv_to_rgb(hsv4);
    HSV hsv5 = { HSV_RED };
    // lower brightess for other keys
    hsv5.v = brightness / 8;
    RGB rgb5 = rgb_matrix_hsv_to_rgb(hsv5);


    // set all keys to one color
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb5.r, rgb5.g, rgb5.b);
    }
    // set keys to different colors
    rgb_matrix_set_color_led_list(LED_INDEX_WASD_SPACE, ARRAYSIZE(LED_INDEX_WASD_SPACE), &rgb1);
    rgb_matrix_set_color_led_list(LED_INDEX_NUMBERS_1_TO_4, ARRAYSIZE(LED_INDEX_NUMBERS_1_TO_4), &rgb2);
    rgb_matrix_set_color_led_list(LED_INDEX_QE, ARRAYSIZE(LED_INDEX_QE), &rgb3);
    rgb_matrix_set_color_led_list(LED_INDEX_MODS, ARRAYSIZE(LED_INDEX_MODS), &rgb4);

    return led_max < RGB_MATRIX_LED_COUNT;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
