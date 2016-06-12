# Password-Based-Lock-System-Arduino
Building a Lock(Password Based) using Arduino UNO and SIM-900A GSM module:

Digital code lock is a type of digital locks where a combination of digits/characters or both are used for unlocking the lock. The door unlocks upon entering the correct password. A hex key pad is used as the input device. GSM Module SIM 900A is used to send message when request for password is made and make a call to owner on entering wrong password. A DC Motor is used to demonstrate the locking and unlocking of the door.

COMPONENTS USED 
Arduino Board
Hex-key Pad
GSM Module SIM 900A
DC Motor 
LEDs

Usage of Device:

Installation – You will be asked to input 5 digits as password at the initial boot/reset of the device. The first 5 digits you input at installation will be saved as your SET PASSWORD. The device will go LOCKED after setting PASSWORD.
Key A – for unlocking the device. Input correct password and press A for Unlocking.
Key B – for locking any time. Just press B and you will see the LOCKED message.
Key C – for changing the password. Input the correct password and Press C. You will see message asking to ENTER NEW PASSWORD. Enter 5 digits as password. The first 5 digits you enter will be SAVED as NEW PASSWORD.
Exceptions – You can not use keys ‘A’, ‘B’ and ‘C’ inside the password combination. These 3 keys are control keys of the device with specific functions. The program checks for these key presses (at the password setting time – you may see the SetPassword() function and look the condition to check for invalid key press) and identifies them as Invalid Keys. You will have to input 5 new digits as password after an Invalid Key press.
ALERT ING THE USER:
If the user enters wrong password for 3 consecutive times, a security alert call would be done  and even a message will be sent to the owner.
If in case the user forgets the password, on pressing the key 'D', password will be sent as sms to registered user mobile number.
