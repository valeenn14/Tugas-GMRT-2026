#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, K;
    long long C, R;

    cout << "=== PROGRAM SIMULASI BATERAI ROBOT ===\n\n";


    cout << "Jumlah misi: ";
    cin >> n;

    cout << "Kapasitas baterai: ";
    cin >> C;

    cout << "Energi setiap charging: ";
    cin >> R;

    cout << "Maksimum charging: ";
    cin >> K;

    vector<long long> x(n);

    cout << "\nKebutuhan energi setiap misi:\n";
    for (int i = 0; i < n; i++) {
        cout << "Misi " << i + 1 << ": ";
        cin >> x[i];
    }

    long long energi = C;
    int charging = 0;
    int selesai = 0;

    cout << "\n--- Simulasi ---\n";

    for (int i = 0; i < n; i++) {
        while (energi < x[i] && charging < K) {
            energi += R;
            charging++;

            if (energi > C)
                energi = C;
        }

        if (energi < x[i]) {
            cout << "Misi " << i + 1 << " gagal.\n";
            break;
        }

        energi -= x[i];
        selesai++;

        cout << "Misi " << i + 1 << " berhasil, "
             << "energi tersisa: " << energi << endl;
    }

    cout << "\n--- Hasil ---\n";
    cout << "Misi berhasil : " << selesai << endl;
    cout << "Total charging: " << charging << endl;
    cout << "Energi akhir  : " << energi << endl;

    return 0;
}