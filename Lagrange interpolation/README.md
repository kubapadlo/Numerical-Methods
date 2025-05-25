# Interpolacja Lagrange’a

Interpolacja Lagrange’a służy do przybliżania funkcji na podstawie skończonego zestawu punktów. Pozwala na aproksymację wartości funkcji w miejscach, gdzie nie mamy bezpośrednich danych.

## Dane wejściowe funkcji

- `x_p` – punkt, w którym chcemy obliczyć wartość funkcji.
- `wezly_x` – współrzędne x znanych węzłów interpolacyjnych.
- `wezly_y` – współrzędne y (wartości funkcji) dla znanych węzłów.

Im więcej węzłów, tym interpolacja jest zazwyczaj dokładniejsza, choć może pojawić się efekt Rungego dla dużej liczby węzłów nierównomiernie rozłożonych.

## Idea algorytmu

Szukamy wielomianu P(x), który przechodzi dokładnie przez wszystkie dane punkty węzłowe:

### Własności funkcji bazowych
Wzór:
![image](https://github.com/user-attachments/assets/375c0642-db56-4912-ae69-e693bb477422)

- Dla swojego węzła głównego daje 1
- Dla pozostałych węzłów daje 0

Dzięki temu każdy składnik sumy odpowiada tylko wartości w jednym węźle, a cała suma daje funkcję interpolacyjną.

### Wyjaśnienie wzoru na funkcje bazową
Licznik - gwarantuje nam, że funkcja bazowa danego węzła, dla wszystkich pozostałych węzłów przyjmuje 0.

Mianownik - gwarantuje nam, że funkcja bazowa dla węzła głównego daje 1.

## Schemat postępowania
![image](https://github.com/user-attachments/assets/ed81fe75-03a6-45da-b118-59461d1a42ae)

1. Dla każdego węzła tworzymy jego funkcję bazową i mnożymy ją przez wartość funkcji w węźle
2. Aby uzyskać wartość funkcji w dowolnym punkcie sumujemy wyniki dla wszystkich węzłów

![przyklad_pomocniczy](https://github.com/user-attachments/assets/09e1fdd7-e555-4349-a3c2-ff597afaf2e1)



# Działanie programu
Program jako węzły przyjmuje co 5 wartość z pliku, a następnie próbuje wyliczyć wartość dla punktów pomiedzy.
Stosując średni błąd kwadratowy obliczamy jak dokładna jest nasza funkcja. Dla tych samych argumentów porównujemy wynik funkcji interpolującej z już wszystkimi danymi z pliku (pomijając węzły bo dla nich błąd=0)
