#include "mbed.h"
#include "MAX7219.h"
#include <string>

#define dp23 P0_0
 
Max7219 displeji(dp2,dp1,dp6,dp23,dp24,dp25,dp26,dp27);

int brojDispleja = 5;

int displejZaKonstantniUnos = 0;
Serial pc(USBTX, USBRX);
AnalogIn potenciometar(dp9);

string unos;
string tekst;
float kasnjenjeZnakPoZnak=1.5;
float kasnjenjeScroll=0.3;
 
void postaviKasnjenje()
{
    float vrijednost = potenciometar;
    displeji.postaviKasnjenjeZnakPoZnak(1.5 + kasnjenjeZnakPoZnak * potenciometar);
    displeji.postaviKasnjenjeZnakPoZnak(0.2 + kasnjenjeScroll * potenciometar);
} 
Ticker ticker;
 
 
void konstantiUnosZnaka()
{
    pc.printf("\n\rUnesite znakove za prikaz (';' za prekid):\n\r");
    while(true) 
    {
        char znak = pc.getc();
        displeji.prikaziZnak(znak,displejZaKonstantniUnos++);
        if(displejZaKonstantniUnos == 5)
        {
            displejZaKonstantniUnos = 0;
            displeji.ocisti();
        }
        
        if(znak == ';')
            break;
    }
}
 
void unesiZnak()
{
    pc.printf("\n\rUnesite znak za prikaz:\n\r");
    char znak = pc.getc();
    for(int i = 0; i < brojDispleja; i++)
    {
        displeji.prikaziZnak(znak,i);
    }
    pc.printf("Uspjesno ste ispisali %c \n\r", znak);
    
}

void prikazVremena()
{
    pc.printf("\n\rTrenunto vrijeme iznosi:\n\r");
    displeji.prikazVremena();
}

void promijeniOsvjetljenje(int pojacaj)
{
    if(pojacaj == 0)
        displeji.smanjiOsvjetljenjeDispleja();
    else
        displeji.pojacajOsvjetljenjeDispleja();
}
void unesiString(char unos)
{
    
    pc.printf("\n\rUnesite string za ispis (prekid unosom ';'): \n\r");
    while(true) 
    {
        char znak=pc.getc();
        tekst.push_back(znak);
        if(znak == ';')
            break;
    }
    pc.printf("\n\rTrenutno se prikazuje string");
    while(pc.readable())
    {
        char c=pc.getc(); // Buffer koji kupi nepotrebne znakove
    }
    
    while(!pc.readable()){
        if(unos=='2')
        {
            displeji.prikaziString(tekst);
        }
        if(unos=='3')
        {
            displeji.prikaziStringScroll(tekst);
        }
       
    }
    
    tekst="";
    pc.printf("\n\r");
    
}
 
void meni()
{
    pc.printf("\n\r\n|----------------------MENI ZA KONTROLU MAX7219 DISPLEJA-----------------------|\n\r");
    pc.printf(      "|Brzina prikaza znakova je regulisana potenciometrom.                          |\n\r");
    pc.printf(      "|Da bi prikazali jedan znak na svim displejima, unesite 1                      |\n\r");
    pc.printf(      "|Da bi prikazali string znak po znak na svim displejima, unesite 2             |\n\r");
    pc.printf(      "|Da bi prikazali string u scrollable modu na svim displejima, unesite 3        |\n\r");
    pc.printf(      "|Da bi prikazali znakove direktno nakon unosa, unesite 4                       |\n\r");
    pc.printf(      "|Da bi prikazali trenutno vrijeme na displejima, unesite 5                     |\n\r");
    pc.printf(      "|Da bi smanjili osvjetljenje displeja, unesite 6                               |\n\r");
    pc.printf(      "|Da bi pojacali osvjetljenje displeja, unesite 7                               |\n\r");
    pc.printf(      "|DEFAULT KASNJENJE ZNAK PO ZNAK: 1.5 s                                         |\n\r");
    pc.printf(      "|DEFAULT KASNJENJE SCROLL: 0.3 s                                              |\n\r");
    pc.printf(      "|------------------------------------------------------------------------------|\n\r");
    goto begin;
    begin:
    pc.printf("Vas komanda: ");
    displejZaKonstantniUnos = 0;
    char c=pc.getc();
    if(c>='1'&&c<='7')
    {
        if(c=='1')
            unesiZnak();
        if(c=='2')
            unesiString(c);
        if(c=='3')
            unesiString(c);
        if(c=='4')
            konstantiUnosZnaka();
        if(c=='5')
            prikazVremena();
        if(c=='6')
            promijeniOsvjetljenje(0);
        if(c=='7')
            promijeniOsvjetljenje(1);
   }
   else
    {
        pc.printf("\n\rGreska, probajte ponovo.\n\r");
        goto begin;
    }
    
}

int main()
{
    unos="";
    tekst="";
    displeji.displejInicijalizacija();
    ticker.attach(postaviKasnjenje,0.25);
    while(1) 
    {
        meni();
    }
}