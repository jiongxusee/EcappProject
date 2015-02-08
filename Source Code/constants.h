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
#define SW1 PORTCbits.RC6
#define BUZZER PORTDbits.RC7

//End Pin Configurations

//Constants
#define TMR0_RESET 156 //TMR0L Value
#define PR2_VALUE 249 //Set PR2 = 249 for PWM period of 1ms
#define TEMP_MIN 20 //Min temperature in Celsius
#define TEMP_MAX 50 //Max temperature in Celsius
#define POWER_MIN 0 //Min power in percentage
#define POWER_MAX 250 //Max power in percentage
#define TEMP_STEP 1 //Temperature decrease or increase steps.
#define TEMP_INIT 30 //Initial Temperature
#define ROOM_TEMP 25 //Room Temperature
#define DEBOUNCE_TIME_MS 10 //Time for debounce check
#define BUZZER_RING_TIME_MS 10 //Buzzer ringing time

//End Constant

//Prototypes
void Handler_High(void); //Interrupt Handler
void ISR_High(void); //ISR
void Handler_Low(void); //Interrupt Handler
void ISR_Low(void); //ISR

static int Read_Potentiometer(unsigned char channel); //Input
static int Decrease_Temperature(unsigned int value); //Process
static int Increase_Temperature(unsigned int value); //Process
static int map(int value, int inMin, int inMax, int outMin, int outMax); //Process
static void Run_Lightbulb(unsigned char power); //Output
static void Run_Buzzer(unsigned char status); //Output
static void Light_LED(unsigned char led); //Output Green, Yellow, Red
static void Light_SevenSeg(unsigned char); //Output
static void Init_LCD(void); //output
static void LCD_Ctr_4bit(char);
static void LCD_Data_4bit(char);

//End Prototypes
