/************************************************
 * pic_clock.h
 * Yu Yoshida
 * ==============================================
 * delay用のクロック定義ヘッダファイル
 * ==============================================
 * ・ver1.00 初版 2015/01/15 Yu Yoshida
 * 20MHzで定義
 * ==============================================
 * PIC16F88
 * XC8 (v1.33/Win)
 * ==============================================
 * Created by fabsat Project (Tokai University)
 ************************************************/

#ifndef __PIC_CLOCK_H__
#define	__PIC_CLOCK_H__
#include <xc.h>

/* Define Clock Frequency for Delay */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000
#endif

#endif	/* PIC_CLOCK_H */