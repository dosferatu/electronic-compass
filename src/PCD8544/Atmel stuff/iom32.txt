00001 /*
00002    iom32.h - internal register definitions for ATmega32
00003 
00004    Contributors:
00005      Created by Marek Michalkiewicz <marekm@linux.org.pl>
00006 
00007    THIS SOFTWARE IS NOT COPYRIGHTED
00008 
00009    This source code is offered for use in the public domain.  You may
00010    use, modify or distribute it freely.
00011 
00012    This code is distributed in the hope that it will be useful, but
00013    WITHOUT ANY WARRANTY.  ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
00014    DISCLAIMED.  This includes but is not limited to warranties of
00015    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
00016 
00017    Based on information from the file m32def.inc which is part of
00018    AVR Studio 3.2.  Warning: subject to change, there may be errors,
00019    verify with the official datasheet when it is released.
00020  */
00021 
00022 #ifndef __IOM32
00023 #define __IOM32 1
00024 
00025 #define AVR_MEGA 1
00026 #define AVR_ENHANCED 1
00027 
00028 /* I/O space addresses */
00029 
00030 /* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
00031 #define TWBR    0x00
00032 #define TWSR    0x01
00033 #define TWAR    0x02
00034 #define TWDR    0x03
00035 
00036 /* ADC */
00037 #define ADCL    0x04
00038 #define ADCH    0x05
00039 #define ADCSR   0x06
00040 #define ADMUX   0x07
00041 
00042 /* analog comparator */
00043 #define ACSR    0x08
00044 
00045 /* UART */
00046 #define UBRR    0x09
00047 #define UBRRL   UBRR
00048 #define UCSRB   0x0A
00049 #define UCSRA   0x0B
00050 #define UDR     0x0C
00051 
00052 /* SPI */
00053 #define SPCR    0x0D
00054 #define SPSR    0x0E
00055 #define SPDR    0x0F
00056 
00057 /* Port D */
00058 #define PIND    0x10
00059 #define DDRD    0x11
00060 #define PORTD   0x12
00061 
00062 /* Port C */
00063 #define PINC    0x13
00064 #define DDRC    0x14
00065 #define PORTC   0x15
00066 
00067 /* Port B */
00068 #define PINB    0x16
00069 #define DDRB    0x17
00070 #define PORTB   0x18
00071 
00072 /* Port A */
00073 #define PINA    0x19
00074 #define DDRA    0x1A
00075 #define PORTA   0x1B
00076 
00077 /* EEPROM */
00078 #define EECR    0x1C
00079 #define EEDR    0x1D
00080 #define EEARL   0x1E
00081 #define EEARH   0x1F
00082 
00083 #define UBRRH   0x20
00084 #define UCSRC   UBRRH
00085 
00086 #define WDTCR   0x21
00087 
00088 #define ASSR    0x22
00089 
00090 /* Timer 2 */
00091 #define OCR2    0x23
00092 #define TCNT2   0x24
00093 #define TCCR2   0x25
00094 
00095 /* Timer 1 */
00096 #define ICR1L   0x26
00097 #define ICR1H   0x27
00098 #define OCR1BL  0x28
00099 #define OCR1BH  0x29
00100 #define OCR1AL  0x2A
00101 #define OCR1AH  0x2B
00102 #define TCNT1L  0x2C
00103 #define TCNT1H  0x2D
00104 #define TCCR1B  0x2E
00105 #define TCCR1A  0x2F
00106 
00107 #define SFIOR   0x30
00108 
00109 #define OSCCAL  0x31
00110 
00111 /* Timer 0 */
00112 #define TCNT0   0x32
00113 #define TCCR0   0x33
00114 
00115 #define MCUSR   0x34
00116 #define MCUCSR  MCUSR
00117 #define MCUCR   0x35
00118 
00119 #define TWCR    0x36
00120 
00121 #define SPMCR   0x37
00122 
00123 #define TIFR    0x38
00124 #define TIMSK   0x39
00125 
00126 #define GIFR    0x3A
00127 #define GIMSK   0x3B
00128 #define GICR    GIMSK
00129 
00130 #define OCR0    0x3C
00131 
00132 #define SPL     0x3D
00133 #define SPH     0x3E
00134 #define SREG    0x3F
00135 
00136 
00137 /* Interrupt vectors (byte addresses) */
00138 
00139 #define RESET_vect              (0x00)
00140 #define INT0_vect               (0x04)
00141 #define INT1_vect               (0x08)
00142 #define INT2_vect               (0x0C)
00143 #define TIMER2_COMP_vect        (0x10)
00144 #define TIMER2_OVF_vect         (0x14)
00145 #define TIMER1_CAPT_vect        (0x18)
00146 #define TIMER1_COMPA_vect       (0x1C)
00147 #define TIMER1_COMPB_vect       (0x20)
00148 #define TIMER1_OVF_vect         (0x24)
00149 #define TIMER0_COMP_vect        (0x28)
00150 #define TIMER0_OVF_vect         (0x2C)
00151 #define SPI_STC_vect            (0x30)
00152 #define UART_RX_vect            (0x34)
00153 #define UART_UDRE_vect          (0x38)
00154 #define UART_TX_vect            (0x3C)
00155 #define ADC_vect                (0x40)
00156 #define EE_RDY_vect             (0x44)
00157 #define ANA_COMP_vect           (0x48)
00158 #define TWI_INT_vect            (0x4C)
00159 
00160 #define INT_VECT_SIZE (0x50)
00161 
00162 /* Bit numbers */
00163 
00164 /* GIMSK */
00165 #define INT1    7
00166 #define INT0    6
00167 #define INT2    5
00168 #define IVSEL   1
00169 #define IVCE    0
00170 
00171 /* GIFR */
00172 #define INTF1   7
00173 #define INTF0   6
00174 #define INTF2   5
00175 
00176 /* TIMSK */
00177 #define OCIE2   7
00178 #define TOIE2   6
00179 #define TICIE1  5
00180 #define OCIE1A  4
00181 #define OCIE1B  3
00182 #define TOIE1   2
00183 #define OCIE0   1
00184 #define TOIE0   0
00185 
00186 /* TIFR */
00187 #define OCF2    7
00188 #define TOV2    6
00189 #define ICF1    5
00190 #define OCF1A   4
00191 #define OCF1B   3
00192 #define TOV1    2
00193 #define OCF0    1
00194 #define TOV0    0
00195 
00196 /* SPMCR */
00197 #define SPMIE   7
00198 #define ASB     6
00199 /* bit 5 reserved */
00200 #define ASRE    4
00201 #define BLBSET  3
00202 #define PGWRT   2
00203 #define PGERS   1
00204 #define SPMEN   0
00205 
00206 /* TWCR */
00207 #define TWINT   7
00208 #define TWEA    6
00209 #define TWSTA   5
00210 #define TWSTO   4
00211 #define TWWC    3
00212 #define TWEN    2
00213 #define TWI_TST 1
00214 #define TWIE    0
00215 
00216 /* TWAR */
00217 #define TWGCE   0
00218 
00219 /* MCUCR */
00220 /* bit 7 reserved (SM2?) */
00221 #define SE      7
00222 #define SM2     6
00223 #define SM1     5
00224 #define SM0     4
00225 #define ISC11   3
00226 #define ISC10   2
00227 #define ISC01   1
00228 #define ISC00   0
00229 
00230 /* MCUCSR */
00231 #define JTD     7
00232 #define ISC2    6
00233 #define EIH     5
00234 #define JTRF    4
00235 #define WDRF    3
00236 #define BORF    2
00237 #define EXTRF   1
00238 #define PORF    0
00239 
00240 /* SFIOR */
00241 #define RPDD    7
00242 #define RPDC    6
00243 #define RPDB    5
00244 #define RPDA    4
00245 #define ACME    3
00246 #define PUD     2
00247 #define PSR2    1
00248 #define PSR10   0
00249 
00250 /* TCCR0 */
00251 #define FOC0    7
00252 #define PWM0    6
00253 #define COM01   5
00254 #define COM00   4
00255 #define CTC0    3
00256 #define CS02    2
00257 #define CS01    1
00258 #define CS00    0
00259 
00260 /* TCCR2 */
00261 #define FOC2    7
00262 #define PWM2    6
00263 #define COM21   5
00264 #define COM20   4
00265 #define CTC2    3
00266 #define CS22    2
00267 #define CS21    1
00268 #define CS20    0
00269 
00270 /* ASSR */
00271 /* bits 7-4 reserved */
00272 #define AS2     3
00273 #define TCN2UB  2
00274 #define OCR2UB  1
00275 #define TCR2UB  0
00276 
00277 /* TCCR1A */
00278 #define COM1A1  7
00279 #define COM1A0  6
00280 #define COM1B1  5
00281 #define COM1B0  4
00282 #define FOC1A   3
00283 #define FOC1B   2
00284 #define PWM11   1
00285 #define PWM10   0
00286 
00287 /* TCCR1B */
00288 #define ICNC1   7
00289 #define ICES1   6
00290 /* bit 5 reserved */
00291 #define CTC11   4
00292 #define CTC10   3
00293 #define CS12    2
00294 #define CS11    1
00295 #define CS10    0
00296 
00297 /* WDTCR */
00298 /* bits 7-5 reserved */
00299 #define WDTOE   4
00300 #define WDE     3
00301 #define WDP2    2
00302 #define WDP1    1
00303 #define WDP0    0
00304 
00305 /* EECR */
00306 /* bits 7-4 reserved */
00307 #define EERIE   3
00308 #define EEMWE   2
00309 #define EEWE    1
00310 #define EERE    0
00311 
00312 /* PA7-PA0 = ADC7-ADC0 */
00313 /* PORTA */
00314 #define PA7     7
00315 #define PA6     6
00316 #define PA5     5
00317 #define PA4     4
00318 #define PA3     3
00319 #define PA2     2
00320 #define PA1     1
00321 #define PA0     0
00322 
00323 /* DDRA */
00324 #define DDA7    7
00325 #define DDA6    6
00326 #define DDA5    5
00327 #define DDA4    4
00328 #define DDA3    3
00329 #define DDA2    2
00330 #define DDA1    1
00331 #define DDA0    0
00332 
00333 /* PINA */
00334 #define PINA7   7
00335 #define PINA6   6
00336 #define PINA5   5
00337 #define PINA4   4
00338 #define PINA3   3
00339 #define PINA2   2
00340 #define PINA1   1
00341 #define PINA0   0
00342 
00343 /*
00344    PB7 = SCK
00345    PB6 = MISO
00346    PB5 = MOSI
00347    PB4 = SS#
00348    PB3 = AIN1
00349    PB2 = AIN0
00350    PB1 = T1
00351    PB0 = T0
00352  */
00353 
00354 /* PORTB */
00355 #define PB7     7
00356 #define PB6     6
00357 #define PB5     5
00358 #define PB4     4
00359 #define PB3     3
00360 #define PB2     2
00361 #define PB1     1
00362 #define PB0     0
00363 
00364 /* DDRB */
00365 #define DDB7    7
00366 #define DDB6    6
00367 #define DDB5    5
00368 #define DDB4    4
00369 #define DDB3    3
00370 #define DDB2    2
00371 #define DDB1    1
00372 #define DDB0    0
00373 
00374 /* PINB */
00375 #define PINB7   7
00376 #define PINB6   6
00377 #define PINB5   5
00378 #define PINB4   4
00379 #define PINB3   3
00380 #define PINB2   2
00381 #define PINB1   1
00382 #define PINB0   0
00383 
00384 /*
00385    PC7 = TOSC2
00386    PC6 = TOSC1
00387    PC1 = SDA
00388    PC0 = SCL
00389  */
00390 /* PORTC */
00391 #define PC7      7
00392 #define PC6      6
00393 #define PC5      5
00394 #define PC4      4
00395 #define PC3      3
00396 #define PC2      2
00397 #define PC1      1
00398 #define PC0      0
00399 
00400 /* DDRC */
00401 #define DDC7    7
00402 #define DDC6    6
00403 #define DDC5    5
00404 #define DDC4    4
00405 #define DDC3    3
00406 #define DDC2    2
00407 #define DDC1    1
00408 #define DDC0    0
00409 
00410 /* PINC */
00411 #define PINC7   7
00412 #define PINC6   6
00413 #define PINC5   5
00414 #define PINC4   4
00415 #define PINC3   3
00416 #define PINC2   2
00417 #define PINC1   1
00418 #define PINC0   0
00419 
00420 /*
00421    PD7 = OC2
00422    PD6 = ICP
00423    PD5 = OC1A
00424    PD4 = OC1B
00425    PD3 = INT1
00426    PD2 = INT0
00427    PD1 = TXD
00428    PD0 = RXD
00429  */
00430 
00431 /* PORTD */
00432 #define PD7      7
00433 #define PD6      6
00434 #define PD5      5
00435 #define PD4      4
00436 #define PD3      3
00437 #define PD2      2
00438 #define PD1      1
00439 #define PD0      0
00440 
00441 /* DDRD */
00442 #define DDD7    7
00443 #define DDD6    6
00444 #define DDD5    5
00445 #define DDD4    4
00446 #define DDD3    3
00447 #define DDD2    2
00448 #define DDD1    1
00449 #define DDD0    0
00450 
00451 /* PIND */
00452 #define PIND7   7
00453 #define PIND6   6
00454 #define PIND5   5
00455 #define PIND4   4
00456 #define PIND3   3
00457 #define PIND2   2
00458 #define PIND1   1
00459 #define PIND0   0
00460 
00461 /*
00462    PE2 = ALE
00463    PE1 = OC1B
00464    PE0 = ICP / INT2
00465  */
00466 
00467 /* SPSR */
00468 #define SPIF    7
00469 #define WCOL    6
00470 #define SPI2X   0
00471 
00472 /* SPCR */
00473 #define SPIE    7
00474 #define SPE     6
00475 #define DORD    5
00476 #define MSTR    4
00477 #define CPOL    3
00478 #define CPHA    2
00479 #define SPR1    1
00480 #define SPR0    0
00481 
00482 /* UCSRA */
00483 #define RXC     7
00484 #define TXC     6
00485 #define UDRE    5
00486 #define FE      4
00487 #define OVR     3
00488 #define DOR     OVR
00489 #define PE      2
00490 #define U2X     1
00491 #define MPCM    0
00492 
00493 /* UCSRB */
00494 #define RXCIE   7
00495 #define TXCIE   6
00496 #define UDRIE   5
00497 #define RXEN    4
00498 #define TXEN    3
00499 #define UCSZ2   2
00500 #define CHR9    2
00501 #define RXB8    1
00502 #define TXB8    0
00503 
00504 /* UCSRC */
00505 #define URSEL   7
00506 #define UMSEL   6
00507 #define UPM1    5
00508 #define UPM0    4
00509 #define USBS    3
00510 #define UCSZ1   2
00511 #define UCSZ0   1
00512 #define UCPOL   0
00513 
00514 /* ACSR */
00515 #define ACD     7
00516 #define AINBG   6
00517 #define ACO     5
00518 #define ACI     4
00519 #define ACIE    3
00520 #define ACIC    2
00521 #define ACIS1   1
00522 #define ACIS0   0
00523 
00524 /* ADCSR */
00525 #define ADEN    7
00526 #define ADSC    6
00527 #define ADFR    5
00528 #define ADIF    4
00529 #define ADIE    3
00530 #define ADPS2   2
00531 #define ADPS1   1
00532 #define ADPS0   0
00533 
00534 /* ADMUX */
00535 #define REFS1   7
00536 #define REFS0   6
00537 #define ADLAR   5
00538 #define MUX4    4
00539 #define MUX3    3
00540 #define MUX2    2
00541 #define MUX1    1
00542 #define MUX0    0
00543 
00544 /* Pointer registers (same for all AVR devices so far) */
00545 #define XL r26
00546 #define XH r27
00547 #define YL r28
00548 #define YH r29
00549 #define ZL r30
00550 #define ZH r31
00551 
00552 /* Last memory addresses */
00553 #define RAMEND          0x85F
00554 #define XRAMEND         0x85F
00555 #define E2END           0x3FF
00556 #define FLASHEND        0x7FFF
00557 
00558 #endif  /* __IOM32 */