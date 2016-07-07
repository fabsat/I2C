//I/Oピンの設定
#define SDA RA0
#define SCL RA1
#define TRISSDA TRISA0

//関数プロトタイプ
void I2CMasterInit(void);
void I2CSlaveInit(void);
void I2CStart(void);
void I2CStop(void);
unsigned char I2COut(unsigned char data);
unsigned charI2CRcv(unsigned char ACK);
void Send(unsigned char adress,unsigned char data);
void AdressSend(unsigned char adress);
void GetDataI2C(unsigned char *Buffer, unsigned char CNT);
void SlaveMode(unsigned char *Buffer, unsigned char CNT);