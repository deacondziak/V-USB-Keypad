#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include "usbdrv.h"
#include <util/delay.h>
#include "reportbuf.h"



void timer2_init(void) {

    cli();


    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;

    OCR2A = 249 // (16,000,000 / (64 * 1000)) - 1

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22);
    TIMSK2 |= (1 << OCIE2A);

    sei();
}
    ISR(TIMER2_COMPA_vect){
        
    }

int main(){
    wdt_enable(WDT0_2S);

    init_keys();
    usbInit();

    usbDeviceDisconnect();
    uchar i = 0;
    while(--i){
        wdt_reset();
        _delay_ms(1);
    }

    usbDeviceConnect();
    sei();
    
    while(1){
        wdt_reset();

        usbPoll();
        if(usbInterruptIsReady() && change == 1){
            usbSetInterrupt(g_reportBuf, sizeof(g_reportBuf));
        }

    }






}