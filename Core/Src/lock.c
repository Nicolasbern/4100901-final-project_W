// Inclusion of necessary header files
#include "lock.h"
#include "ring_buffer.h"
#include "keypad.h"
#include "main.h"
#include "gui.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stm32l4xx_hal.h"

#define MAX_PASSWORD 4 // Define the maximum length of the password

uint8_t password[MAX_PASSWORD] = "2002"; // Initial hardcoded password
uint8_t password2[MAX_PASSWORD]; // Placeholder for a second password, not used

uint8_t keypad_buffer[MAX_PASSWORD]; // Buffer for storing keypad inputs
ring_buffer_t keypad_rb; // Ring buffer for efficient data handling

uint8_t keypad_buffer2[MAX_PASSWORD]; // Secondary buffer for additional keypad input
ring_buffer_t keypad_rb2; // Second ring buffer instance

uint8_t count = 0; // Counter for tracking attempts or states

extern volatile uint16_t keypad_event; // External variable, probably for interrupt-based event handling

// Functions for controlling an LED
void LED_SetHigh(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Turns on the LED at pin PA5
}

// Función para apagar el LED.
void LED_SetLow(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // Turns off the LED at pin PA5
}

// Function to retrieve a key press from the keypad
static uint8_t lock_get_passkey(void)
{
	while (ring_buffer_size(&keypad_rb) == 0) {
		/* wait for key press */
		uint8_t key_pressed = keypad_run(&keypad_event);
		if (key_pressed != KEY_PRESSED_NONE) {
			ring_buffer_put(&keypad_rb, key_pressed);
		}
	}
    // Retrieve the key press
	uint8_t key_pressed;
	ring_buffer_get(&keypad_rb, &key_pressed);
	if (key_pressed == '*' || key_pressed == '#') {
		return 0xFF; // Special handling for '*' and '#'
	}
	return key_pressed;
}
// Similar function for the second keypad buffer
static uint8_t lock_get_2passkey(void)
{	 // Similar logic as lock_get_passkey
	while (ring_buffer_size(&keypad_rb2) == 0) {
		/* wait for key press */
		uint8_t key_pressed = keypad_run(&keypad_event);
		if (key_pressed != KEY_PRESSED_NONE) {
			ring_buffer_put(&keypad_rb2, key_pressed);
		}
	}
	uint8_t key_pressed;
	ring_buffer_get(&keypad_rb2, &key_pressed);
	if (key_pressed == '*' || key_pressed == '#') {
		return 0xFF;
	}
	return key_pressed;
}

// Function to get and update a new password
static uint8_t lock_get_password(void)
{
	uint8_t idx = 0;
	uint8_t passkey = 0;
	uint8_t new_password[MAX_PASSWORD];
	memset(new_password, 0, MAX_PASSWORD); // Clear the new_password buffer
	uint8_t password_shadow[MAX_PASSWORD + 1]  = {
			'-', '-', '-', '-','\0'
	};
    // Loop to read new password input
    while (passkey != 0xFF) {
        GUI_update_password(password_shadow); // Update GUI display
        passkey = lock_get_passkey(); // Get a key press
        password_shadow[idx] = '*'; // Update shadow password display
        new_password[idx++] = passkey; // Store the key press in new password
        GUI_update_password(new_password); // Update GUI with new password
        HAL_Delay(200); // Short delay for debounce/user experience
    }

    // Validate and update the password if necessary
    if (idx > 1) {
        memcpy(password, new_password, MAX_PASSWORD); // Update the stored password
        GUI_update_password_success(); // Show success message on GUI
    } else {
        GUI_locked(); // Lock the GUI if the password is not valid
        return 0; // Return failure
    }
    return 1; // Return success


}

// Function to validate the entered password against the stored one
static uint8_t lock_validate_password(void)
{
	uint8_t sequence2[MAX_PASSWORD];
	uint8_t sequence[MAX_PASSWORD];
	uint8_t seq_len = ring_buffer_size(&keypad_rb);
	for (uint8_t idx = 0; idx < seq_len; idx++) {
		ring_buffer_get(&keypad_rb, &sequence[idx]);
	}
	if (memcmp(sequence, password, 4) == 0) {
		 // Genera un número aleatorio de 4 dígitos
		  srand(HAL_GetTick()); // Inicializa la semilla con el tiempo actual (puedes ajustar esto según tus necesidades)
		  uint32_t randomNumber = rand() % 10000; // Genera números en el rango de 0 a 9999

		  // Convierte el número a una cadena de caracteres
		  char buffer[5]; // 4 dígitos + el carácter nulo '\0'
		  snprintf(buffer, sizeof(buffer), "%04lu", randomNumber);
		  printf("segunda validacion %s\r\n",buffer);

		  lock_get_2passkey();

		  uint8_t seq_len2 = ring_buffer_size(&keypad_rb2);
		  for (uint8_t idx = 0; idx < seq_len2; idx++) {
		  	ring_buffer_get(&keypad_rb2, &sequence2[idx]);
		  }
			if (memcmp(sequence2,buffer, 4) == 0) {
				return 1;
			}else {
				return 0;
			}
	}
	return 0;
}

// Function to update the password
static void lock_update_password(void)
{
	if (lock_validate_password() != 0) {
		GUI_update_password_init();
		lock_get_password();
	} else {
		GUI_locked();
        // Apaga el LED en PA5 para indicar que está bloqueado o falló la autenticación.
        LED_SetLow();
	}
}

// Function to attempt to unlock the lock
static void lock_open_lock(void)
{
	if (lock_validate_password() != 0) {
		GUI_unlocked();
		// Enciende el LED en PA5 para indicar que está desbloqueado.

	} else {
		GUI_locked();
		if (count < 3) {
		     // If the password is incorrect, show "Failed" and wait for 3 seconds
		     GUI_Fail();
		     HAL_Delay(3 * 1000);
		     count++;
		} else {
			if (count == 3) {// If the password is incorrect 3 times, show "Blocked" and wait for 10 seconds
				GUI_Retry();
				HAL_Delay(30 * 1000);
				count++;
			}else{
				if(count == 6){
					GUI_blocked();
					HAL_Delay(120 * 1000);
					count++;
				}
			}
		}
	}
}



void lock_init(void)
{
	ring_buffer_init(&keypad_rb, keypad_buffer, 12);
	ring_buffer_init(&keypad_rb2, keypad_buffer2, 12);
	GUI_init();
}


void lock_sequence_handler(uint8_t key)
{
	if (key == '*') {
		lock_update_password();
	} else if (key == '#') {
		lock_open_lock();
	} else {
		ring_buffer_put(&keypad_rb, key);
	}

}
