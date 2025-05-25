#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

bool wczytajDane(const string& nazwaPliku, vector<float>& x, vector<float>& y) {
    ifstream file(nazwaPliku);
    if (!file.is_open()) {
        cerr << "Blad otwarcia pliku" << endl;
        return false;
    }

    string linia;

    // Wczytaj linię x
    if (!getline(file, linia)) {
        cerr << "Blad wczytywania linii x" << endl;
        return false;
    }
    istringstream issX(linia);
    string token;
    issX >> token; // "x:"
    while (issX >> token) {
        x.push_back(stof(token));
    }

    // Wczytaj linię y
    if (!getline(file, linia)) {
        cerr << "Blad wczytywania linii y" << endl;
        return false;
    }
    istringstream issY(linia);
    issY >> token; // "y:"
    while (issY >> token) {
        y.push_back(stof(token));
    }

    if (x.size() != y.size()) {
        cerr << "Niezgodne rozmiary x i y" << endl;
        return false;
    }

    return true;
}

float lagrangeInterpolation(float xp, const vector<float>& x, const vector<float>& y) {
    int n = x.size();
    float result = 0;
    for (int i = 0; i < n; i++) {
        float tmp = y[i];
        for (int j = 0; j < n; j++) 
        {
            if (i != j)
                tmp *= (xp - x[j]) / (x[i] - x[j]);
        }
        result += tmp;
    }
    return result;
}

float obliczSredniBladKwadratowy(const vector<float>& x, const vector<float>& y,
                                  const vector<float>& x_wezly, const vector<float>& y_wezly) {
    float sumaBledow = 0;
    int liczbaPunktow = 0;

    for (size_t i = 0; i < x.size(); i++) {
        // Jeśli x[i] nie jest wezłem, obliczamy błąd
        if (i % 5 != 0) {
            float yInterpolowane = lagrangeInterpolation(x[i], x_wezly, y_wezly);
            sumaBledow += pow(y[i] - yInterpolowane, 2);
            liczbaPunktow++;
        }
    }

    return (liczbaPunktow > 0) ? sumaBledow / liczbaPunktow : 0;
}

int main() {
    vector<float> x, y, x_wezly, y_wezly;
    string nazwaPliku = "dane.txt";

    if (!wczytajDane(nazwaPliku, x, y)) {
        return 1;
    }

    for (size_t i = 0; i < x.size(); i += 5) {
        x_wezly.push_back(x[i]);
        y_wezly.push_back(y[i]);
    }

    float xp;
    cout << "Podaj punkt interpolacji: ";
    cin >> xp;

    float wynik = lagrangeInterpolation(xp, x_wezly, y_wezly);
    cout << "Wartosc wielomianu interpolacyjnego w punkcie " << xp << " wynosi: " << wynik << endl;

    ofstream outFile("interpolacja.csv");
    if (!outFile) {
        cerr << "Blad zapisu do pliku" << endl;
        return 1;
    }

    outFile << "x,y" << endl;
    for (const float iks : x) {
        outFile << iks << "," << lagrangeInterpolation(iks, x_wezly, y_wezly) << endl;
    }
    outFile.close();
    cout << "Dane interpolacji zapisane do pliku interpolacja.csv" << endl;

    float sredniBladKwadratowy = obliczSredniBladKwadratowy(x, y, x_wezly, y_wezly);
    cout << "Sredni blad kwadratowy: " << sredniBladKwadratowy << endl;

    return 0;
}