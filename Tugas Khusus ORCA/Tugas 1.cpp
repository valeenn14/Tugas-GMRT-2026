#include <iostream>
#include <string>
using namespace std;

class KomponenROV {
protected:
    string nama;
    string status;

public:
    KomponenROV(string n, string s);
    virtual void info();
    virtual ~KomponenROV() {}
};

class Thruster : public KomponenROV {
private:
    int power;

public:
    Thruster(string n, string s, int p);
    void info() override;
};

class Sensor : public KomponenROV {
private:
    int nilai;

public:
    Sensor(string n, string s, int v);
    void info() override;
};

int main() {
    int jumlah;

    cout << "Masukkan jumlah komponen: ";
    cin >> jumlah;

    KomponenROV** komponen = new KomponenROV*[jumlah];

    for (int i = 0; i < jumlah; i++) {
        string jenis, nama, status;
        int nilai;

        cout << "\nKomponen ke-" << i + 1 << endl;

        cout << "Jenis (Thruster/Sensor): ";
        cin >> jenis;

        cout << "Nama: ";
        cin >> nama;

        cout << "Status: ";
        cin >> status;

        if (jenis == "Thruster") {
            cout << "Power: ";
            cin >> nilai;
            komponen[i] = new Thruster(nama, status, nilai);
        }
        else if (jenis == "Sensor") {
            cout << "Nilai sensor: ";
            cin >> nilai;
            komponen[i] = new Sensor(nama, status, nilai);
        }
        else {
            cout << "Jenis komponen tidak valid!" << endl;
            delete[] komponen;
            return 1;
        }
    }

    cout << "\nDATA KOMPONEN ROV" << endl;

    cout << "Jumlah Komponen : " << jumlah << endl;
    cout << endl;

    for (int i = 0; i < jumlah; i++) {
        cout << "Komponen ke-" << i + 1 << endl;
        komponen[i]->info();
        cout << endl;
    }

    for (int i = 0; i < jumlah; i++)
        delete komponen[i];

    delete[] komponen;

    return 0;
}

KomponenROV::KomponenROV(string n, string s) {
    nama = n;
    status = s;
}

void KomponenROV::info() {
    cout << "Nama   : " << nama << endl;
    cout << "Status : " << status << endl;
}

Thruster::Thruster(string n, string s, int p)
    : KomponenROV(n, s) {
    power = p;
}

void Thruster::info() {
    cout << "Jenis : Thruster" << endl;
    cout << "Nama : " << nama << endl;
    cout << "Status : " << status << endl;
    cout << "Power : " << power << endl;
}

Sensor::Sensor(string n, string s, int v)
    : KomponenROV(n, s) {
    nilai = v;
}

void Sensor::info() {
    cout << "Jenis : Sensor" << endl;
    cout << "Nama : " << nama << endl;
    cout << "Status : " << status << endl;
    cout << "Nilai Sensor : " << nilai << endl;
}