
///// NHIEM VU 3

void nhiemvu3()
{
disable_interrupts(int_timer5);
enable_interrupts(int_timer1);

beep(3,100);
chonct=0;
qei_set_count(0);
En2=0;
Ti1=0;
Ti2=0;

enable_interrupts(int_timer5);
clear_interrupt(int_timer5);
set_timer5(59286);
}
