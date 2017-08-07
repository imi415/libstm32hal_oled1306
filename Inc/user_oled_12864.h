#ifndef __USER_12864_H
#define __USER_12864_H

#define OLED_SLAVE_ADDR 0x78
#define OLED_I2C_INTERFACE hi2c1

void OLED_Init(void);
void OLED_Position_Set(uint8_t posX, uint8_t posY);
void OLED_Fill(uint8_t fillData);
void OLED_Clear(void);
void OLED_Power(uint8_t powerState);
void OLED_String_Display(uint8_t posX, uint8_t posY, char * buf);
void OLED_Write_Command(uint8_t cmd);
void OLED_Write_Data(uint8_t data);

#endif

