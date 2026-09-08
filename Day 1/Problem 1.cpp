#include <iostream>
using namespace std;

long long ceilDiv(long long a, long long b) {
    return (a + b - 1) / b;
}

long long hitungLangkah(long long q, long long kapasitas) {
    if (q == 0)
        return 0;

    if (kapasitas == 0)
        return -1;

    long long load = ceilDiv(2 * q, kapasitas);
    long long unload = 2 * ceilDiv(q, kapasitas);

    return load + unload;
}

int main() {
    long long k, n, m;

    cin >> k >> n >> m;

    // Jumlah barang dan berat yang sama
    if (n % 3 != 0 || m % 3 != 0) {
        cout << -1 << endl;
        return 0;
    }

    // Jumlah barang yang harus ada di setiap kotak
    long long barang2kg = n / 3;
    long long barang1kg = m / 3;

    // Kapasitas robot untuk masing-masing jenis barang
    long long kapasitas2kg = k / 2;
    long long kapasitas1kg = k;

    // Jika ada barang 2 kg tetapi robot tidak mampu membawanya
    if (barang2kg > 0 && kapasitas2kg == 0) {
        cout << -1 << endl;
        return 0;
    }

    // Langkah untuk barang 2 kg
    long long langkah2kg =
        hitungLangkah(barang2kg, kapasitas2kg);

    // Langkah untuk barang 1 kg
    long long langkah1kg =
        hitungLangkah(barang1kg, kapasitas1kg);

    if (langkah2kg == -1 || langkah1kg == -1) {
        cout << -1 << endl;
        return 0;
    }

    cout << langkah2kg + langkah1kg << endl;

    return 0;
}