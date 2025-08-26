#include <lpc17xx.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define RS_CTRL 0x00000100 //P0.8 
#define EN_CTRL 0x00000200 //PO.9 
#define DT_CTRL 0x000000F0 //PO.4 TO P0.7 
#define BUZZER_PIN (1<<17) // P2.13 for buzzer 

unsigned long int init_command[] = {0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80}; 
unsigned long int temp1 = 0, temp2 = 0, i, j, var1, var2; 
unsigned char flag1 = 0, flag2 = 0; 
unsigned char msg[] = {"ALCOHOL%:"}; 
unsigned char msg2[] = {"Level: "}; 
unsigned char buzzer_state = 0; 

void delay(unsigned int r1) { 
    unsigned int r; 
    for(r = 0; r < r1; r++); 
} 

// Buzzer patterns for different alcohol levels 
void buzzer_pattern_high(void) { 
    int z; 
    for(z = 0; z < 20; z++) { // Rapid beeps for high alcohol 
        LPC_GPIO0->FIOSET = BUZZER_PIN; 
        delay(1000000); 
        LPC_GPIO0->FIOCLR = BUZZER_PIN; 
        delay(1000000); 
    } 
} 

/*void buzzer_pattern_medium(void) { 
    int x; 
    for(x = 0; x < 10; x++) { // Medium paced beeps 
        LPC_GPIO0->FIOSET = BUZZER_PIN; 
        delay(2000000); 
        LPC_GPIO0->FIOCLR = BUZZER_PIN; 
        delay(2000000); 
    } 
}*/ 

/*void buzzer_pattern_low(void) { 
    int y; 
    for(y = 0; y < 5; y++) { // Slow beeps for low alcohol 
        LPC_GPIO2->FIOSET = BUZZER_PIN; 
        delay(3000000); 
        LPC_GPIO2->FIOCLR = BUZZER_PIN; 
        delay(3000000); 
    } 
}*/ 

void lcd_init(void); 
void lcd_write(void); 
void port_write(void); 
void delay(unsigned int); 
void lcd_print_msg(void); 
void lcd_print_msg2(void); 

int main(void) { 
    unsigned int i; 
    unsigned int sensorReading; 
    char disp_level[10]; 
    char percentageStr[14]; 
    float alcohol_percentage; 

    SystemInit(); 
    SystemCoreClockUpdate(); 
    LPC_PINCON->PINSEL1 |= 1<<14; //function 1 on P0.23 for AD0 
    LPC_SC->PCONP |= (1<<12); //peripheral power supply for ADC 
    LPC_GPIO0->FIODIR = DT_CTRL | RS_CTRL | EN_CTRL; 
    LPC_GPIO0->FIODIR |= BUZZER_PIN; 

    lcd_init(); 
    lcd_print_msg(); 
    lcd_print_msg2(); 

    while(1) { 
        // ADC Reading 
        LPC_ADC->ADCR = (1<<0) | (1<<21) | (1<<24); 
        while(((sensorReading = LPC_ADC->ADGDR) & 0X80000000) == 0); 
        sensorReading = LPC_ADC->ADGDR; 
        sensorReading >>= 4; 
        sensorReading &= 0x00000FFF; 

        // Convert ADC reading to alcohol percentage (0-100%) 
        // Assuming sensor gives linear output and max ADC value (4095) = 100% 
        alcohol_percentage = (float)sensorReading * 100.0 / 4095.0; 
        sprintf(percentageStr, " %.1f%% ", alcohol_percentage); 

        // Alcohol Level Classification and Buzzer Control 
        if(alcohol_percentage >= 50.0) { 
            strcpy(disp_level, " HIGH "); 
            buzzer_pattern_high(); 
        } 
        else if(alcohol_percentage >= 20.0) { 
            strcpy(disp_level, " MEDIUM "); 
            //buzzer_pattern_medium(); 
        } 
        else { 
            strcpy(disp_level, " LOW "); 
            //buzzer_pattern_low(); 
        } 

        // LCD Display Update 
        temp1 = 0x89; 
        flag1 = 0; 
        lcd_write(); 
        delay(800); 
        i = 0; 
        flag1 = 1; 
        while(disp_level[i] != '\0') { 
            temp1 = disp_level[i]; 
            lcd_write(); 
            i += 1; 
        } 

        temp1 = 0xC5; 
        flag1 = 0; 
        lcd_write(); 
        delay(800); 
        i = 0; 
        flag1 = 1; 
        while(percentageStr[i] != '\0') { 
            temp1 = percentageStr[i]; 
            lcd_write(); 
            i += 1; 
        } 
        delay(1000000); // Delay between readings 
    } 
} 

void lcd_init(void) { 
    unsigned int x; 
    flag1 = 0; 
    for(x = 0; x < 9; x++) { 
        temp1 = init_command[x]; 
        lcd_write(); 
    } 
    flag1 = 1; 
} 

void lcd_write(void) { 
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0; 
    temp2 = temp1 & 0xf0; 
    port_write(); 
    if (flag2 == 0) { 
        temp2 = temp1 & 0x0f; 
        temp2 = temp2 << 4; 
        port_write(); 
    } 
} 

void port_write(void) { 
    LPC_GPIO0->FIOPIN = temp2; 
    if (flag1 == 0) 
        LPC_GPIO0->FIOCLR = RS_CTRL; 
    else 
        LPC_GPIO0->FIOSET = RS_CTRL; 
    LPC_GPIO0->FIOSET = EN_CTRL; 
    delay(25); 
    LPC_GPIO0->FIOCLR = EN_CTRL; 
    delay(3000000); 
} 

void lcd_print_msg(void) { 
    unsigned int a; 
    for(a = 0; msg[a] != '\0'; a++) { 
        temp1 = msg[a]; 
        lcd_write(); 
    } 
} 

void lcd_print_msg2(void) { 
    temp1 = 0xC0; 
    flag1 = 0; 
    lcd_write(); 
    delay(800); 
    i = 0; 
    flag1 = 1; 
    while(msg2[i] != '\0') { 
        temp1 = msg2[i]; 
        lcd_write(); 
        i++; 
    } 
} 
