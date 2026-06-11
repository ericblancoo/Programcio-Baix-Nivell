/*
Developer: Eric Blanco (23−maig−2024)
Revised: Izan Hernandez (23-juny-2024)
*/

#include <avr/interrupt.h>
#include <util/atomic.h>
#include "serial_device.h"
#include <util/delay.h>

#include <stdbool.h>

#define BAUD_RATE 9600
#define F_CPU 16000000UL
#define UBRR_VALUE ((F_CPU / (BAUD_RATE * 16UL)) - 1)

static queue_t queue_RX, queue_TX;

ISR(USART_RX_vect) {
    queue_enqueue(&queue_RX, UDR0); 
}


ISR(USART_UDRE_vect) {
    if (!queue_is_empty(&queue_TX)) {
        uint8_t data_to_send = queue_front(&queue_TX);
        queue_dequeue(&queue_TX);
        UDR0 = data_to_send;
    } else {
        UCSR0B &= ~_BV(UDRIE0);
    }
}

void serial_open(void) {
    
    //  velocitat de transmissió 9600
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE);
    // UDRIEn: USART Data Register Empty Interrupt Enable
    UCSR0A = (1 << UDRIE0);
    // Habilita  transmissió i la recepció
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Configura velocitat i format 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits de dades sense paritat

    // Rx complete interrupt | Data register empty interrupt
    UCSR0B |= (1 << UDRIE0) | (1<< RXCIE0); // ("|=") per no sobreescriure els bits d'abans
    queue_empty(&queue_RX);
    queue_empty(&queue_TX);
    sei();
}



void serial_close(void){
    while (!queue_is_empty(&queue_TX));
    UCSR0B = 0;
}


uint8_t serial_get(void){
    while (serial_can_get()==false); 
    uint8_t get= queue_front(&queue_RX);
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    queue_dequeue(&queue_RX);
    }
    return get;

}


void serial_put(uint8_t c){
    while (serial_can_put()==false);
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    queue_enqueue(&queue_TX, c);

    UCSR0B |= _BV(UDRIE0);
    }
    return;
}

bool serial_can_get(void){
    return !queue_is_empty(&queue_RX);
}

bool serial_can_put(void){
    return !queue_is_full(&queue_TX);
}

//queue is empty = true
// queue is full = true
