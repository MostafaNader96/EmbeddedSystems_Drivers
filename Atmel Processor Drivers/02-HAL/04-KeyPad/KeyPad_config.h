#define KEYPAD_R0_PORT	'B'
#define KEYPAD_R0_PIN	0

#define KEYPAD_R1_PORT	'B'
#define KEYPAD_R1_PIN	1

#define KEYPAD_R2_PORT	'B'
#define KEYPAD_R2_PIN	2

#define KEYPAD_R3_PORT	'B'
#define KEYPAD_R3_PIN	3

#define KEYPAD_C0_PORT	'B'
#define KEYPAD_C0_PIN	4

#define KEYPAD_C1_PORT	'B'
#define KEYPAD_C1_PIN	5

#define KEYPAD_C2_PORT	'B'
#define KEYPAD_C2_PIN	6

#define KEYPAD_C3_PORT	'B'
#define KEYPAD_C3_PIN	7

/*Choose the number of keypad's columns and rows*/
#define KEYPAD_ROWS_NUMBER			4
#define KEYPAD_COLUMNS_NUMBER		4

/*Choose Ports & Pins of Keypad*/
#define KEYPAD_ROWS_PORT 		{KEYPAD_R0_PORT,KEYPAD_R1_PORT,KEYPAD_R2_PORT,KEYPAD_R3_PORT}
#define KEYPAD_ROWS_PIN  		{KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN}
#define KEYPAD_COLUMNS_PORT		{KEYPAD_C0_PORT,KEYPAD_C1_PORT,KEYPAD_C2_PORT,KEYPAD_C3_PORT}
#define KEYPAD_COLUMNS_PIN  	{KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN}

/*Choose the Keypad Representation*/
#define KEYPAD_KEYS				{{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}}

/*The default value if no key is pressed*/
#define KEYPAD_DEFAULT       0xff
