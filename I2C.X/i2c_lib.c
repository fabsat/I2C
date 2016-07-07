#include <xc.h>
#include "pic_clock.h"
#include "i2c_lib.h"

//初期設定
void I2CMasterInit(void){
    TRISA = 0b00000001;
    PORTA = 0b00000011;
}

void I2CSlaveInit(void){
    TRISA = 0b00000011;
    PORTA = 0b00000011;
}

//スタート条件出力
void I2CStart(void){
    /*SCL,SDAは常時highとする*/
    SDA = 0;  //先にSDA Low
    TRISSDA = 0;  //SDA出力
}

//ストップ条件出力
void I2CStop(void){
    SCL = 0;       //SCL Low
    __delay_us(1);
    SDA = 0;       //SDA Low
    TRISSDA = 0;   //出力モードに戻す SDA = Low
    SCL = 1;       //先にSCLをHigh
    __delay_us(1);
    SDA = 1;       //後からSDAをHigh
    __delay_us(10); //感覚用遅延
}

//I2Cで1バイト出力
//スレーブからのACKを戻り値とする
unsigned char I2COut(unsigned char data){
    int i;
    unsigned char BitPos, ACK;
    
    //data out
    TRISSDA = 0;       //SDA出力モード
    BitPos = 0x80;     //ビット位置初期値
    for(i=0; i<8; i++){  //8ビット繰り返し
        SCL = 0;         //SCL Low
        if((data & BitPos) != 0){  //ビット出力
            SDA = 1;     //SDA High
        }
        else{
            SDA = 0;     //SDA Low
        }
        BitPos = BitPos >> 1;  //ビット位置移動
        SCL = 1;          //SCL Highに戻す
    }
    //ACKチェック
    SCL = 0;     //クロック 1Low
    TRISSDA = 1;  //入力モードにしてACK入力
    __delay_us(2);
    SCL = 1;      //クロックHighに戻す
    __delay_us(2);
    ACK = SDA;    //ACKチェック
    return(ACK);  //ACKを戻り値とする
}

//I2Cで1バイト入力
//パラメータでACK/NAKを返送
unsigned char I2CRcv(unsigned char Ack){
    int i;
    unsigned char BitPos, data;
    
    data = 0;
    BitPos = 0x80;   //ビット位置リセット
    for(i=0; i<8; i++){   //8ビット繰り返し
        SCL = 0;  //SCL Low
        TRISSDA = 1;  //入力モード
        __delay_us(3);  //幅確保
        SCL = 1;   //SCL High
        if(SDA){   //ビット入力
            data |=BitPos;
        }
        BitPos = BitPos >>1;  //ビットシフト
    }
    //ACK/NAK出力
    SCL = 0;    //SCL Low
    SDA = Ack;  //ACK ot NAk 出力
    TRISSDA = 0;  //SDA出力モード
    __delay_us(2);  //パルス幅確保
    SCL = 1;  //SCL High
    return(data);  //受信データを戻す
}

//マスタ送信
void Send(unsigned char adress,unsigned char data){
    I2CStart();  //スタート条件
    I2COut(adress);  //アドレス
    while(I2COut(adress)==1){  //ACK失敗ならば再送
        I2COut(adress);
    }
    I2COut(data);  //データ出力
    I2CStop();     //ストップ条件
}

void AdressSend(unsigned char adress){
    I2CStart();  //スタート条件
    I2COut(adress);
    while(I2COut(adress)==1){  //ACK失敗ならば再送
        I2COut(adress);
    }
    I2CStop();     //ストップ条件
}

//マスタ受信
void GetDataI2C(unsigned char adress,unsigned char *Buffer, unsigned char CNT)
{
    unsigned char i;
    
    I2CStart();  //スタート条件出力
    I2COut(adress);  //アドレス送信 Readモード
    for(i=0; i<CNT; i++){  //複数バイト連続受信
        Buffer[i] = I2CRcv(0);  //ACK受信データ取得
    }
    Buffer[i] = I2CRcv(1);  //NAK受信データ取得
    I2CStop();  //ストップ条件出力
}

//スレーブ
void SlaveMode(unsigned char *Buffer, unsigned char CNT){
    unsigned char adress, rw, buf, i, data, count;
    adress = 0b00011100;
    count = 0;
    
    while(count < 1000){
        if(SDA == 1){

        }
        else if(SDA == 0){
            buf = I2CRcv(0);
            if((adress<<1) == buf){
                adress = buf;
                rw = adress & 0x01;  //write=0, read=1
                if(rw == 0){
                    for(i=0; i<CNT; i++){
                        Buffer[i] = I2CRcv(0);
                    }
                    Buffer[i] = I2CRcv(1);
                }
                else if(rw == 1){
                    for(i=0; i<CNT; i++){
                        data = Buffer[i];
                        if(I2COut(data) == 1){
                            break;
                        }
                    }
                }
            }
        }
        count++;
    }    
}
