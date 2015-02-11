//Pin Configurations

#define POTENTIOMETER_SELECT 0x01
#define SEVEN_SEG_ONE PORTCbits.RC0
#define SEVEN_SEG_TWO PORTEbits.RE2
#define SEVEN_SEG_DATA PORTD
#define LCD_E PORTAbits.RA4
#define LCD_RS PORTAbits.RA5
#define LCD_DATA PORTB
#define RED_LED PORTCbits.RC3
#define YELLOW_LED PORTCbits.RC4
#define GREEN_LED PORTCbits.RC5

/* Potentiometer - AN0 (RA0)
** Up Button - INT0 (RB0)
** Down Button - INT1 (RB1)
** Light Bulb - CCP1 (RC2)
** Buzzer - CCP2 (RC1)
*/

//End Pin Configurations

//Constants
#define TMR0_RESET 156 //TMR0L Value
#define PR2_VALUE 249 //Set PR2 = 249 for PWM period of 1ms
#define TEMP_MIN 25 //Min temperature in Celsius
#define TEMP_MAX 50 //Max temperature in Celsius
#define POWER_MIN 1 //Min power in 8 bits
#define POWER_MAX 249 //Max power in 8 bits
#define TEMP_STEP 1 //Temperature decrease or increase steps.
#define TEMP_INIT 30 //Initial Temperature
#define DEBOUNCE_TIME_MS 10 //Time for debounce check
#define BUZZER_RING_TIME_MS 10 //Buzzer ringing time
#define RED_LED_BLINK_RATE_MS 20 //Time for red LED blink rate
//End Constant

//Prototypes
void Handler_High(void); //Interrupt Handler
void ISR_High(void); //ISR
void Handler_Low(void); //Interrupt Handler
void ISR_Low(void); //ISR

static int Read_Potentiometer(unsigned char channel); //Input
static int Decrease_Temperature(unsigned int value); //Process
static int Increase_Temperature(unsigned int value); //Process
static void Run_Lightbulb(unsigned char power); //Output
static void Run_Buzzer(unsigned char status); //Output
static void Light_LED(unsigned char led); //Output Green, Yellow, Red
static void Light_SevenSeg(unsigned char); //Output
static void Init_LCD(void); //output
static void W_ctr_4bit(char x);
static void W_data_4bit(char x);
//End Prototypes
