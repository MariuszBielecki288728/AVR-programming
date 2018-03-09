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
podłączonych pod Arduino. Do odczytu tekstu można użyć biblioteki Serial z Arduino
albo bezpośrednio przez rejestry UART. 
1.5 Zbuduj układ z kilkoma diodami obok siebie oraz trzema przyciskami. 
Pierwszy przycisk powinien zerować diody, pozostałe dwa powinny wywoływać wyświetlenie na diodach 
następnego/poprzedniego kodu Graya. Kody należy zapetlić – odpowiednio dużo naciśnięć powinno 
wracać do kodu zerowego. Zadbaj o rozwiązanie problemu drgających styków (debouncing) 
– jedno naciśnięcie przycisku powinno powodować zawsze jedną zmianę kodu. 
Maksymalne punkty za elegancką realizację – wszystkie diody na jednym porcie, 
wyliczanie kodów operacjami bitowymi.


2.1 Zbuduj układ realizujący oddychającą diodę LED RGB. Należy wykorzystać timery do 
modulowania jasności diody. Uwagi:
  2.1.1 Kolor diody dla każdego cyklu "oddechu" powinien być losowany. 
  Losowanie osobno wartości kanałów RGB nie jest dobrą metodą losowania kolorów 
  – prowadzi to do częstego losowania kolorów słabo nasyconych lub ciemnych. 
  Najlepiej losować tylko kolory maksymalnie nasycone i maksymalnie jasne, losując tylko 
  składową H z układu HSV.
  2.1.2 Zmiana jasności powinna sprawiać wrażenie sinusoidalnej. 
  Należy pamiętać o logarytmicznym postrzeganiu jasności przez wzrok: dioda, której jasność 
  faktycznie zmienia się sinusoidalnie, będzie zdawać się jasna przez większość 
  czasu oraz bardzo szybko gasnąć. Należy wspomóc się funkcją wykładniczą.
  2.1.3 Mikrokontrolery z serii Atmega nie posiadają jednostki zmiennoprzecinkowej, 
  operacje na typachdouble i float są emulowane z dużym kosztem wydajnościowym. 
  Warto wykonywać obliczenia stałoprzecinkowe, a np. funkcje trygonometryczne tablicować.
2.2 Używając diody IR i detektora IR zbuduj urządzenie wykrywające zbliżenie obiektu, 
np. dłoni, i sygnalizujący ten fakt za pomocą diody LED. Dostępny w wypożyczonych zestawach 
odbiornik IR (OSRB38C9BA) jest czuły na częstotliwość 37,9 kHz: z taką częstotliwością 
należy migać diodą IR. Miganie diody należy regularnie przerywać i wznawiać 
– czujnik nie jest przystosowany do fali ciągłej.
2.3 Zbuduj układ odtwarzający próbkowany dźwięk 
(np. jak z jednokanałowego WAV, próbkowanie 8 kHz, 8 bit), na przykład głos "Dzień dobry". 
Próbki należy wyprowadzać za pomocą wyjścia PWM sterowanego licznikiem, wartość wypełnienia 
fali prostokątnej ma odpowiadać wartości próbki. Dźwięk można wyprowadzić za pomocą 
brzęczyka bez generatora (tzn. takiego, który po podpięciu do zasilania nie brzęczy, 
tylko robi stuk), albo za pomocą głośniczka i prostego układu tranzystorowego wzmacniacza 
(np. jak tutaj na obrazku 1). Próbki mają być zapisane w pamięci programu.
2.4 Zbuduj układ odtwarzający wybraną melodię (minimum pół minuty) z nut. Melodia ma być 
zapisana w tablicy w pamięci programu, każda nuta ma być opisana jej wysokością 
(np. C D E F G A H jako liczby 0 do 6) oraz czasem trwania. (Pauzę też można traktować jako nutę). 
Dźwięk powinien być wyprowadzany przez wyjście sterowane licznikiem w modulacji PFM 
(stałe wypełnienie 50%, zmienna częstotliwość), można wykorzystać tryb CTC licznika. 
2.5 Używając licznika (np. 16-bitowego TC1) jako metody pomiaru czasu, 
zmierz czas (w cyklach) wykonywania różnych operacji matematycznych na różnych typach danych:
    Dodawanie, mnożenie, dzielenie i reszta z dzielenia dla typów uint8_t, uint16_t, uint32_t,
    Dodawanie, mnożenie, potęgowanie dla typów float i double.
    

3.1 Zbuduj układ dostosowujący (średnie) natężenie światła diody do natężenia 
światła panującego w otoczeniu (im ciemniej tym dioda powinna jaśniej świecić). 
Do pomiaru natężenia padającego światła należy wykorzystać fotorezystor (LDR) i ADC. 
Aby otrzymać maksymalną ilość punktów, należy zadbać o liniowość pomiaru od rezystancji 
fotorezystora
3.2 Mierz rezystancję termistora przez ADC wybraną przez siebie metodą (możliwości jak w zadaniu 1).
Wykonując pomiary w znanych temperaturach określ stałą B swojego termistora. 
Napisz program, który będzie regularnie (np. co 1 sekundę) mierzył rezystancję 
termistora i wypisywał przez UART wynik pomiaru temperatury (w stopniach Celsjusza).
3.3 Trzynóżkowy zintegrowany termometr MCP9700 (w zestawie) wytwarza napięcie liniowo 
proporcjonalne do temperatury: 10 miliwoltów na stopień Celsjusza, 500 miliwoltów przy 
temperaturze 0 stopni. Wykonuj pomiary używając wbudowanego napięcia referencyjnego (Aref) 1.1V 
dla zwiększonej dokładności. Wykonaj prosty termostat. W tym celu zbuduj układ 
z załączonego obrazka. Układ grzałki powinien składać się z kilku (2 do 4) rezystorów 
o wartości 50 do 200 om, rezystory powinny być połączone równolegle i przylegać do układu 
termometru. Działanie grzałki należy przetestować: włączona (5v na pinie sterującym) 
powinna być ciepła w dotyku. Napisz program, który utrzymuje ustaloną temperaturę 
termometru (np. 30 stopni). Niech działa on na zasadzie histerezy: 
grzałka powinna być włączona aż do osiągnięcia ustalonej temperatury, po czym należy ją 
wyłączyć i zaczekać, aż temperatura trochę spadnie (np. o pół stopnia), 
i dopiero wtedy ponownie włączyć grzałkę. Stan grzałki powinien być sygnalizowany przez 
diodę świecącą, bieżącą wartość temperatury należy wypisywac przez UART.
3.4 Zmierz za pomocą ADC napięcie zasilające. 
Aby to osiągnąć, ustaw napięcie referencyjne (Aref) na napięcie zasilające, zaś multiplekser 
ADC skonfiguruj, aby mierzyć wbudowane napięcie referencyjne 1.1V. 
Wyliczaj w programie wartość napięcia zasilającego (w woltach) i wypisuj przez UART 
(powinno wynosić około 5V). Złóż na płytce stykowej grzałkę z zadania 3. 
Włączaj i wyłączaj grzałkę co sekundę; włączenie grzałki powinno powodować 
zauważalny spadek zmierzonego napięcia zasilającego.


```
