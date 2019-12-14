#include "spi.h"
#include "gpio.h"

#include "ssd1306_oled.h"
#include "lvgl.h"

#include "ssd1306_lvgl.h"

extern OLED_HandleTypeDef oled;

void ssd1306_disp_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t* color_p) {
  /*Return if the area is out the screen*/
  if (x2 < 0 || y2 < 0 || x1 > LV_HOR_RES - 1 || y1 > LV_VER_RES - 1) {
    lv_flush_ready();
    return;
  }

  /*Return if the screen is uninitialized*/
  if(!oled.Interface) {
    lv_flush_ready();
    return;
  }

  for(uint8_t i = y1; i <= y2; i++) {
    for(uint8_t j = x1; j <= x2; j++) {
      uint8_t x_lshift = 7 - (j % 8);
      uint16_t fb_offset = 16 * i + (j / 8);
      uint16_t lv_offset = (x2 - x1 + 1) * (i - y1) + (j - x1);
      if(color_p[lv_offset].full > 0) {
        oled.Framebuffer[fb_offset] |= (0x01 << x_lshift);
      }
      else {
        oled.Framebuffer[fb_offset] &= ~(0x01 << x_lshift);
      }
    }
  }

  OLED_UploadBuffer(&oled, x1, x2, y1, y2);
  lv_flush_ready();
}