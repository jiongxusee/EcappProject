//Pin Configurations

#define POTENTIOMETER_SELECT 0x01
#define SEVEN_SEG_ONE PORTCbits.RC0
#define SEVEN_SEG_TWO PORTCbits.RC1
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
#define PR2_VALUE 249 //Set PR2 = 249 for PWM period of 1ms
#define TEMP_MIN 25 //Min temperature in Celsius
#define TEMP_MAX 40 //Max temperature in Celsius
#define POWER_MIN 0 //Min power in percentage
#define POWER_MAX 100 //Max power in percentage

//End Constant

//Prototypes
void Handler_High(void); //Interrupt Handler
void ISR_High(void); //ISR
void Handler_Low(void); //Interrupt Handler
void ISR_Low(void); //ISR

static int Read_Potentiometer(unsigned char channel); //Input
static void Decrease_Temperature(unsigned int value); //Process
static void Increase_Temperature(unsigned int value); //Process
static int Convert_Temp_To_Power(unsigned int temp); //Process
static int map(int value, int inMin, int inMax, int outMin, int outMax); //Process
static void Run_Lightbulb(unsigned char power); //Output
static void Light_LED(unsigned char led); //Output Green, Yellow, Red
//static int Read_Potentiometer(int channel);

//End Prototypes
