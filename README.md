# AVR-programming
set of my solutions to tasks given at "Embedded systems" university course.
Programs are written in C, I tested them on arduino uno, but in great majority of programs there are no traces of arduino API,
so basically I was programming atmega328P microcontroller.

## What have I learned?
- basics of electric circuits
- how to use microcontroller datasheet
- I/O in AVR
- PWM and PFM modulation (Fast PWM, CTC, etc.)
- communication via UART
- 8-bit and 16-bit counters
- ADC
- interrupts
- basics of energy management in AVR
- communication via SPI, shift registers
- Play melody and make RGB led breathe ;)

## Tasks
(only those solved by me, in Polish)

```
1.1 Zrealizuj efekt przewijającej się diodki na kilku diodach zamontowanych obok siebie 
na płytce stykowej, jak w serialu Nieustraszony (Knight Rider) albo oczy Cylonów. 
Maksymalne punkty za elegancką realizację – wszystkie diody na jednym porcie mikrokontrolera, 
przesuwanie zapalonych diod przez operacje bitowe.
1.2 Zbuduj urządzenie które zapamiętuje naciśnięcia i zwolnienia przycisku przez użytkownika, 
i odtwarza je zapalając i gasząc diodę z 1 sekundowym opóźnieniem. Podpowiedź: zastosuj bufor cykliczny. 
1.3 Zbuduj wyświetlacz widmowy (ang. persistence of vision, PoV) 
– zamontuj kilka diod LED jedna obok drugiej na płytce stykowej, i steruj nimi tak, 
aby poruszając płytką w powietrzu pokazał się jakiś napis. 
Maksymalne punkty za elegancką realizację – wszystkie diody na jednym porcie mikrokontrolera, 
wyświetlenie kolumny jednym zapisem do portu, dane do wyświetlenia zapisane w tablicy.
1.4 Zbuduj i zaprogramuj układ tłumaczący tekst na kod Morse’a. 
Tekst ma być wprowadzany na komputerze, a wynik ma zostać wyemitowany przy użyciu diody i brzęczyka 
podłączonych pod Arduino. Do odczytu tekstu można użyć biblioteki Serial z Arduinoalbo bezpośrednio przez rejestry UART. 
```
