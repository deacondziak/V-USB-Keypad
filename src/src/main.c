#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include "usbdrv.h"
#include <util/delay.h>
#include "reportbuf.h"


void init_keys() {
    DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3)) | ((1 << PC4) | (1 << PC5));
    PORTC |= ((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
}

uint8_t g_reportBuf[1 + NUM_KEYS_MAX] = {0}; // 8 bits ctrl + 6 bytes for keys
uint8_t g_idleRate = 4;

const PROGMEM char usbHidReportDescriptor[53] = {
    0x05, 0x01,     // Usage Page (Generic Desktop Page)
    0x09, 0x06,     // Usage (Keyboard)
    0xA1, 0x01,     // Collection (Application)
    0x05, 0x07,         // Usage Page (Keyboard)
    0x19, 0xE0,         // Usage Minimum (Left Ctrl)
    0x29, 0xE7,         // Usage Maximum (Right GUI)
    0x15, 0x00,         // Logical Min (0)
    0x25, 0x01,         // Logical Max (1)
    0x75, 0x01,         // Report Size (1)
    0x95, 0x08,         // Report Count (8)
    0x81, 0x02,         // Input(Data, Var, Abs)

    0x19, 0x00,         // Usage Minimum (0)
    0x29, 0x65,         // Usage Maximum (0x65)
    0x15, 0x00,         // Logical Min (0)
    0x25, 0x65,         // Logical Max (0x65)
    0x75, 0x08,         // Report Size (8)
    0x95, 0x06,         // Report Count (6)
    0x81, 0x00,         // Input(Data, Array, Abs)

    0x05, 0x08,         // Usage Page (LED)
    0x19, 0x01,         // Usage Minimum (Num Lock)
    0x29, 0x03,         // Usage Maximum (Scroll Lock)
    0x15, 0x00,         // Logical Min (0)
    0x25, 0x01,         // Logical Max (1)
    0x75, 0x01,         // Report Size (1)
    0x95, 0x03,         // Report Count (3)
    0x91, 0x02,         // Output(Data, Var, Abs)
    0xC0            // End Collection
};


#define KEY_DELETE 0x63

uint8_t buildReport(){
    uint8_t current_key = 0;

    if(!(PINC & (1 << PC0))){
        g_reportBuf[1] = KEY_DELETE;
        current_key++;
    }


int main(){
    init_keys();
    usbInit();

    sei();
    
    while(1){

        usbPoll();
        if(usbInterruptIsReady() && change == 1){
            usbSetInterrupt(g_reportBuf, sizeof(g_reportBuf));
        }

    }






}