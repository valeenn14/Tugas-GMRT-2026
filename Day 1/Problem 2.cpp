#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long C, R;
    int K;

    cout << "=====================================\n";
    cout << "       SIMULASI BATERAI ROBOT\n";
    cout << "=====================================\n\n";

    // Input
    cout << "Masukkan jumlah misi (n): ";
    cin >> n;

    cout << "Masukkan kapasitas maksimum baterai (C): ";
    cin >> C;

    cout << "Masukkan energi setiap charging (R): ";
    cin >> R;

    cout << "Masukkan maksimum jumlah charging (K): ";
    cin >> K;

    vector<long long> x(n);

    cout << "\nMasukkan kebutuhan energi setiap misi:\n";

    for (int i = 0; i < n; i++) {
        cout << "Energi misi ke-" << i + 1 << ": ";
        cin >> x[i];
    }

    cout << "\n=====================================\n";
    cout << "         MULAI SIMULASI\n";
    cout << "=====================================\n";

    long long energi = C;
    int charging = 0;
    int selesai = 0;

    cout << "\nEnergi awal robot: " << energi << endl;

    // Proses setiap misi
    for (int i = 0; i < n; i++) {

        cout << "\n-------------------------------------\n";
        cout << "MISI KE-" << i + 1 << endl;
        cout << "-------------------------------------\n";

        cout << "Energi saat ini       : " << energi << endl;
        cout << "Energi yang dibutuhkan: " << x[i] << endl;

        // Jika energi tidak cukup, charging
        while (energi < x[i] && charging < K) {

            cout << "\nEnergi tidak cukup.\n";
            cout << "Robot melakukan charging...\n";

            energi += R;
            charging++;

            // Energi tidak boleh melebihi kapasitas C
            if (energi > C) {
                energi = C;
            }

            cout << "Charging ke-" << charging << endl;
            cout << "Energi setelah charging: "
                 << energi << endl;
        }

        // Jika energi masih tidak cukup
        if (energi < x[i]) {

            cout << "\nMisi tidak dapat dijalankan!\n";
            cout << "Energi tidak mencukupi dan batas "
                    "charging sudah tercapai.\n";

            break;
        }

        // Jalankan misi
        cout << "\nEnergi mencukupi.\n";
        cout << "Robot menjalankan misi...\n";

        energi -= x[i];
        selesai++;

        cout << "Misi berhasil!\n";
        cout << "Energi tersisa: " << energi << endl;
    }

    // Hasil akhir
    cout << "\n=====================================\n";
    cout << "           HASIL SIMULASI\n";
    cout << "=====================================\n";

    cout << "Jumlah misi berhasil : " << selesai << endl;
    
    return 0;
}