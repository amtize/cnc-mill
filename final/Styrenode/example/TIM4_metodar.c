
 /* Programkode for Prosjektoppgaver i ELE 340 Datamaskinkonstruksjon
 * Kristian Thorsen 2016 - 2017
 * Legges inn i fila TIM_metodar.c
 *
 */

/*
 * Setter opp TIM4 til � lage et 4 kHz 50% duty klokkesignal til SCF filteret. Dette signalet skal
 * ut p� pinne PD12. Bruker kanal 1, CH1, i TIM4 for � lage dette.
 * I denne funksjonen skriver vi direkte til registerne i TIM4.
 * Vi bruker driverfunksjonene/bibliotekene for � sette opp GPIO PD12.
 */
void TIM4_oppstart_reg(void) {

    //Slepp f�rst til klokka paa TIM4.
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


    // Setter hvilken modus TIM4 skal v�re i ved � bruke capture compare mode register 1 (CCMR1)
    // Bit 6:4 skal v�re 110 (for PWM mode 1, up-count).
    // Bit 3 settes til 1 (for at Capture compare verdi 1 bare oppdateres ved start av ny periode)
    TIM4->CCMR1 = 0x68;             // = 0b01101000

    // Setter hvilken capture compare kanal som skal v�re aktiv.
    // Vi vil sammenligne telleren med capture compare verdi nr. 1 og at kanal 1 skal v�re output
    TIM4->CCER = 0x01;

    // Setter prescaler for klokke, grunnklokken p� 72 MHz deles p� dette tallet. Timerens
    // klokkefrekvens blir da resultatet av denne delingen. f_TIM4 = f / (PSC + 1)
    TIM4->PSC = 0x47;               // = 71, alts� 72. Det gir f_TIM4 = 1 MHz og T_TIM4 = 1 us.

    // Setter auto-reload, aka. hvor langt skal vi telle
    TIM4->ARR = 0xFA;               // = 250            (alts� til 250 us, f = 4 kHz)

    // Setter capture compare verdi nr. 1 for TIM4. Dette er hvor langt timeren skal telle mens
    // utgangen er h�y. (Setter Duty Cycle)
    TIM4->CCR1 = 0x7D;              // = 125            (alts� til 125, halvparten D = 50%)

    // Vi kunne p� de tre registerne over like gjerne satt inn tallet p� 10-talls form.


    // S� oppsett av GPIO-pinnen PD12 som blir brukt av TIM4-modulen
    // Her bruker vi driverfunksjonene (enkelt � bare kopiere og tilpasse koden ovenfra)
    // ------------------------------------------

    // Deklarasjon av initialiseringsstrukturen.
    GPIO_InitTypeDef GPIO_InitStructure_TIM4;

    // Slepp til klokka paa GPIO-portD.
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE); // | RCC_AHBPeriph_AFIO

    // Konfigurer PD12.
    GPIO_InitStructure_TIM4.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure_TIM4.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_TIM4.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_TIM4.GPIO_PuPd  = GPIO_PuPd_NOPULL;

    // Initialiser, dvs. last ned konfigurasjonen i modulen
    GPIO_Init(GPIOD, &GPIO_InitStructure_TIM4);

    // Knytt TIM4-pinnane til AF */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_2); //.

    // Aktiverer s� timeren ved � skrive til Enable bit i CR1 registeret
    TIM4->CR1 |= 0x01;

}

void TIM4_aktiver_reg(void){
        TIM4->CR1 |= 0x01;          // Aktiverer ved � skrive 1 til Enable bit i CR1 registeret.
}

void TIM4_deaktiver_reg(void){
        TIM4->CR1 &= 0xFE;          // Detaktiverer ved � slette Enable bittet i CR1 registeret
}
