
// PIC16F886 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include "i2c_lib.h"
#include "pic_clock.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



void main(void){
    
    //マスタ受信**********************************
    unsigned char add, M_adress, write, read, data[1];
    
    write = 0x00;
    read = 0x01;
    
    I2CMasterInit();  //I2C初期化
    
    add = (M_adress << 1) | read;  //アドレスにr/wを足す
    GetDataI2C(add,data,1);
    
    
    
    //スレーブ送信*********************************
    unsigned char data[1];
    data[1] = 0x43;
    
    I2CSlaveInit();  //I2C初期化
    
    SlaveMode(*data,1);
    
    
    
    
    
}