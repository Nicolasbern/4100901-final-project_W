# 4100901-final-project 

## ELECTRONIC SAFE BOX WITH DOUBLE VERIFICATION

This project is undertaken with the objective of creating an electronic safe that incorporates an added layer of security through a dual verification system. The primary aim is to establish a robust mechanism for accessing the safe by implementing a password-based authentication process, which serves as the key for either unlocking or securing the "lock". The fundamental functionality involves entering a password, and as previously mentioned, this action determines whether access is granted or denied.

Furthermore, the design incorporates a feature enabling users to modify their passwords according to their preferences, achieved through the implementation of specific commands. This not only enhances user convenience but also adds an extra layer of personalization and control over the security aspect of the electronic safe. The password change functionality ensures adaptability to varying security needs and preferences, contributing to a comprehensive and user-friendly electronic safe solution.

## INTRODUCTION
The electronic safe project, developed around the STM32L476RG microcontroller along with various peripherals, introduces a practical solution to address security concerns. The system incorporates a unique feature where users can input a 4-digit key to either unlock or temporarily lock the safe. This functionality adds an additional layer of security by controlling access for a predetermined duration.

In tandem with the key-based mechanism, the project incorporates a dual verification system involving a new password. This innovative security measure enhances the overall safety of the electronic safe, requiring users to pass through two distinct authentication steps for access.

Furthermore, recognizing the importance of user customization, the project includes a password change functionality. Users have the flexibility to modify the password according to their preferences, contributing to a personalized and adaptable security solution. The combination of key-based access, dual verification, and password customization collectively creates a robust and user-friendly electronic safe, effectively addressing security concerns in a comprehensive manner.

![image](https://github.com/Nicolasbern/4100901-final-project_W/assets/115322460/7969ca05-0fd3-44ec-bf94-31532230c72b)

The project's core functionality revolves around a safe with dual verification for enhanced security. If the initial password is entered incorrectly, the system allows three additional attempts. After four consecutive incorrect entries, the system enforces a 30-second block to prevent unauthorized access. This stringent security measure ensures that only authorized users can gain entry.

Similarly, the second verification, facilitated through YAT (Yet Another Terminal), follows a similar protocol. If the YAT-based password is incorrectly entered, the system allows three more attempts before initiating a 30-second lockout, mirroring the behavior of the initial password verification.

Upon successful validation of both passwords, an LED indicator is activated, symbolizing the safe's opening. This visual cue provides users with immediate feedback about the successful authentication and access to the safe.

Additionally, the project incorporates a key update functionality to address security concerns. To update the password, users must enter the current key. If the current password is incorrectly entered three times, the system initiates a lockdown as a security precaution. If the current password is correctly entered, the system prompts a double verification process through YAT. Should the YAT-based verification also fail three times, the system enforces another lockdown, emphasizing the project's commitment to security measures and preventing unauthorized access.

In summary, the project not only provides robust double verification for safe access but also includes security features such as temporary lockouts and multi-step verification processes to ensure the utmost protection of the electronic safe.

## Hardware prerequisites
* The example is a digital lock system featuring an STM32L4 for controling the system, an ESP8266 for interfacing with the internet, a keypad for getting the sequences, and an OLED display for GUI.
* The following is the pinout of the STM32:
![pinout](Doc/pinout.png)

## Firmware prerequisites
* The ESP8266 runs the esp-link [v2.2.3](https://github.com/jeelabs/esp-link/releases/tag/v2.2.3) firmware. Please follow the [serial flashing guide](https://github.com/jeelabs/esp-link/blob/master/FLASHING.md#initial-serial-flashing).
* The STM32 runs the firmware compiled from this repository using STM32CubeIDE.

## Building and Flashing
* Open the project in STM32CubeIDE.
* Compile using the current project settings.
* Use an ST-LINK to flash the firmware into the STM32.

## Functionality
* ***TODO:*** Add more explanation here.
* The keypad...
* The Debug console...
* The internet interface...
* The system sends metrics to the internet every 24h by using an alarm of the embedded RTC.

## Contact info
* Sam C - saacifuentesmu@unal.edu.co
