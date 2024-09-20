#include <mega128.h>
#include <stdio.h>
#include <delay.h>

void main(void)
{
    char data;
    unsigned char i;

    PORTB = 0x00;
    DDRB = 0xFF;
    PORTE = 0x00;
    DDRE = 0x00;

    TCCR1A = 0xA1;
    TCCR1B = 0x05;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    OCR1CH = 0x00;
    OCR1CL = 0x00;

    TCCR3A = 0x40;
    TCCR3B = 0x09;
    TCNT3H = 0x00;
    TCNT3L = 0x00;
    ICR3H = 0x00;
    ICR3L = 0x00;
    OCR3AH = 0x00;
    OCR3AL = 0x00;
    OCR3BH = 0x00;
    OCR3BL = 0x00;
    OCR3CH = 0x00;
    OCR3CL = 0x00;

    UCSR0A = (0 << RXC0) | (0 << TXC0) | (0 << UDRE0) | (0 << FE0) | (0 << DOR0) | (0 << UPE0) | (0 << U2X0) | (0 << MPCM0);
    UCSR0B = (0 << RXCIE0) | (0 << TXCIE0) | (0 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0) | (0 << UCSZ02) | (0 << RXB80) | (0 << TXB80);
    UCSR0C = (0 << UMSEL0) | (0 << UPM01) | (0 << UPM00) | (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00) | (0 << UCPOL0);
    UBRR0H = 0x00;
    UBRR0L = 0x67;

    while (1)
    {
        data = getchar();
        putchar(data);

        switch (data)
        {
        case 'G':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0xFF;
            OCR1BL = 0xFF;
            break;

        case 'L':
            PORTB.0 = 0x00;
            PORTB.1 = 0x01;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0xFF;
            OCR1BL = 0xFF;
            break;

        case 'R':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x00;
            PORTB.3 = 0x01;

            OCR1AL = 0xFF;
            OCR1BL = 0xFF;
            break;

        case 'B':
            PORTB.0 = 0x00;
            PORTB.1 = 0x01;
            PORTB.2 = 0x00;
            PORTB.3 = 0x01;

            OCR1AL = 0xFF;
            OCR1BL = 0xFF;
            break;

        case 'S':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0x00;
            OCR1BL = 0x00;
            break;

        case '1':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0x19;
            OCR1BL = 0xFF;
            break;

        case '3':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0xFF;
            OCR1BL = 0x19;
            break;

        case '7':
            PORTB.0 = 0x00;
            PORTB.1 = 0x01;
            PORTB.2 = 0x00;
            PORTB.3 = 0x01;

            OCR1AL = 0x19;
            OCR1BL = 0xFF;
            break;

        case '9':
            PORTB.0 = 0x00;
            PORTB.1 = 0x01;
            PORTB.2 = 0x00;
            PORTB.3 = 0x01;

            OCR1AL = 0xFF;
            OCR1BL = 0x19;
            break;

        case 'Q':
            PORTB.0 = 0x00;
            PORTB.1 = 0x01;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0x19;
            OCR1BL = 0xFF;
            break;

        case 'P':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x00;
            PORTB.3 = 0x01;

            OCR1AL = 0xFF;
            OCR1BL = 0x19;
            break;

        case 'X':
            PORTB.0 = 0x01;
            PORTB.1 = 0x00;
            PORTB.2 = 0x01;
            PORTB.3 = 0x00;

            OCR1AL = 0x00;
            OCR1BL = 0x00;

            for (i = 0; i < 2; i++) {
                DDRE = 0xFF;
                OCR3AH = 5101 >> 8;
                OCR3AL = 5101 & 0x00FF;
                delay_ms(250);
                DDRE = 0x00;

                if (i == 0)
                    delay_ms(50);
            }
            break;
        }
    }
}
