#include "gui.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"


extern const uint8_t locked[];


void GUI_init(void)
{
	ssd1306_Init();
	GUI_locked();
}

void GUI_locked(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(20, 5);
	ssd1306_WriteString("Locked", Font_16x26, White);
	ssd1306_DrawBitmap(50, 35, locked, 30, 30, White);
	ssd1306_UpdateScreen();
}

void GUI_unlocked(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString("Unlocked", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_update_password_init(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString("New PW:", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_update_password(uint8_t *password)
{
	ssd1306_SetCursor(10, 35);
	ssd1306_WriteString((char *)password, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void GUI_update_password_success(void)
{
	ssd1306_SetCursor(5, 35);
	ssd1306_WriteString("Success!", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_wait(void){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("Waiting", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_pass_update(void){
	 ssd1306_Fill(Black);
	 ssd1306_SetCursor(10, 10);
	 ssd1306_WriteString("password", Font_16x26, White);
	 ssd1306_SetCursor(30, 10);
	 ssd1306_WriteString("update", Font_16x26, White);
	 ssd1306_UpdateScreen();
}


void GUI_second_validate(void){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("second", Font_16x26, White);
	 ssd1306_SetCursor(30, 10);
	 ssd1306_WriteString("validate", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_Fail(void){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("Fail", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_Retry (void){
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("Retry", Font_16x26, White);
	ssd1306_UpdateScreen();

}

void GUI_blocked (void){
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("Blocked", Font_16x26, White);
	ssd1306_UpdateScreen();

}
