#include <iostream>
using namespace std;

long long ceilDiv(long long a, long long b) {
    return (a + b - 1) / b;
}

long long hitungLangkah(long long jumlah, long long kapasitas) {
    if (jumlah == 0)
        return 0;

    if (kapasitas == 0)
        return -1;

    long long load = ceilDiv(2 * jumlah, kapasitas);
    long long unload = 2 * ceilDiv(jumlah, kapasitas);

    return load + unload;
}

int main() {
    long long k, n, m;

    cout << "=== PROGRAM PEMINDAHAN BARANG ===\n\n";

    cout << "Masukkan k n m: \n";
    cin >> k >> n >> m;

    cout << "\nKapasitas robot : " << k << " kg\n";
    cout << "Barang 2 kg     : " << n << " unit\n";
    cout << "Barang 1 kg     : " << m << " unit\n";

    // Mengecek ulang
    if (n % 3 != 0 || m % 3 != 0) {
        cout << "\nBarang tidak dapat dibagi rata ke 3 kotak.\n";
        cout << "Hasil: -1\n";
        return 0;
    }

    long long barang2kg = n / 3;
    long long barang1kg = m / 3;

    long long kapasitas2kg = k / 2;
    long long kapasitas1kg = k;

    // Robot tidak mampu membawa barang 2 kg
    if (barang2kg > 0 && kapasitas2kg == 0) {
        cout << "\nRobot tidak mampu membawa barang 2 kg.\n";
        cout << "Hasil: -1\n";
        return 0;
    }

    long long langkah2kg =
        hitungLangkah(barang2kg, kapasitas2kg);

    long long langkah1kg =
        hitungLangkah(barang1kg, kapasitas1kg);

    if (langkah2kg == -1 || langkah1kg == -1) {
        cout << "\nPenyeimbangan tidak dapat dilakukan.\n";
        cout << "Hasil: -1\n";
        return 0;
    }

    cout << "\nSetiap kotak harus memiliki:\n";
    cout << "- " << barang2kg << " barang 2 kg\n";
    cout << "- " << barang1kg << " barang 1 kg\n";

    cout << "\nLangkah barang 2 kg : "
         << langkah2kg << endl;

    cout << "Langkah barang 1 kg : "
         << langkah1kg << endl;

    cout << "\nTotal langkah minimum: "
         << langkah2kg + langkah1kg << endl;

    return 0;
}