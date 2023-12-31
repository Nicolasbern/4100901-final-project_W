/*
 * gui.h
 *
 *  Created on: Nov 20, 2023
 *      Author: saaci
 */

#ifndef INC_GUI_H_
#define INC_GUI_H_

#include <stdint.h>


void GUI_init(void);

void GUI_locked(void);
void GUI_unlocked(void);
void GUI_update_password_init(void);
void GUI_update_password(uint8_t *password);
void GUI_update_password_success(void);
void GUI_wait(void);
void GUI_pass_update(void);
void GUI_Fail(void);
void GUI_Retry (void);
void GUI_blocked (void);

#endif /* INC_GUI_H_ */
