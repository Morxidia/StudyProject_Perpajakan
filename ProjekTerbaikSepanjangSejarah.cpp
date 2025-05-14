#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct NPWPTempt {
    string npwp;
    string nik;
    string gender;
    string noTelepon;
    string statusKawin;
    int tanggungan;
    string statusPTKP;
    string statusWajibPajak;
    string alamat;
};

// Fungsi generate NPWP dengan format: AA.BBB.CCC.D-EEE.FFF
string generateFormattedNPWP(int jenisWP, int kodeKPP = 123, int status = 0 ) {
    stringstream npwp;

    // AA: jenis wajib pajak
    if (jenisWP < 10) npwp << "0";
    npwp << jenisWP << ".";

    // BBB.CCC: nomor unik (6 digit)
    for (int i = 0; i < 3; i++) npwp << rand() % 10;
    npwp << ".";
    for (int i = 0; i < 3; i++) npwp << rand() % 10;
    npwp << ".";

    // D: 1 digit random
    npwp << rand() % 10 << "-";

    // EEE: kode KPP
    if (kodeKPP < 10) npwp << "00";
    else if (kodeKPP < 100) npwp << "0";
    npwp << kodeKPP << ".";

    // FFF: status wajib pajak
    if (status < 10) npwp << "00";
    else if (status < 100) npwp << "0";
    npwp << status;

    return npwp.str();
}

void CheckNIK(string NIK){
    
}

// Fungsi untuk menambah data
void daftarUser() {
    NPWPTempt User;
    char pilihanJenis;
    int kodeJenisWP;

    cout << "=== PENDAFTARAN NPWP ===\n";
    cout << "Pilih Jenis Wajib Pajak:\n";
    cout << "1. WP Pekerja Bebas/profesional (Dokter, Notaris, dll)\n";
    cout << "2. WP Orang Pribadi (Pengusaha)\n";
    cout << "3. WP Orang Pribadi (Karyawan)\n";
    cout << "Pilihan (1-3): ";
    cin >> pilihanJenis;
    cin.ignore();

    cout << "Masukkan NIK                 : ";
    getline(cin, User.nik);
    CheckNIK(User.nik);
    cout << "Masukkan Jenis Kelamin (L/P): ";
    getline(cin, User.gender);
    cout << "Masukkan No Telepon         : ";
    getline(cin, User.noTelepon);
    cout << "Status Kawin (Kawin/Lajang) : ";
    getline(cin, User.statusKawin);
    cout << "Jumlah Tanggungan           : ";
    cin >> User.tanggungan;
    cin.ignore();
    cout << "Status PTKP (TK/K)          : ";
    getline(cin, User.statusPTKP);
    cout << "Status Wajib Pajak (Efektif/Non Efektif): ";
    getline(cin, User.statusWajibPajak);
    cout << "Alamat                      : ";
    getline(cin, User.alamat);

    // Menentukan kode jenis WP berdasarkan pilihan
    switch (pilihanJenis) {
        case '1': kodeJenisWP = 1 + rand() % 3; break; // 01–03
        case '2': kodeJenisWP = 4 + rand() % 3; break; // 04–06
        case '3': kodeJenisWP = 7 + rand() % 3; break; // 07–09
        default : kodeJenisWP = 0; break;
    }

    // generate NPWP nya
    User.npwp = generateFormattedNPWP(kodeJenisWP);

    // Menampilkan data yang telah dimasukkan
    cout << "\n=== DATA YANG TELAH DITAMBAHKAN ===\n";
    cout << "NPWP: " << User.npwp << endl;
    cout << "NIK: " << User.nik << endl;
    cout << "Jenis Kelamin: " << User.gender << endl;
    cout << "No Telepon: " << User.noTelepon << endl;
    cout << "Status Kawin: " << User.statusKawin << endl;
    cout << "Jumlah Tanggungan: " << User.tanggungan << endl;
    cout << "Status PTKP: " << User.statusPTKP << endl;
    cout << "Status Wajib Pajak: " << User.statusWajibPajak << endl;
    cout << "Alamat: " << User.alamat << endl;

    // Simpan data ke file
    ofstream file("npwp.txt", ios::app);
    if (file.is_open()) {
        file << User.npwp << "|" << User.nik << "|" << User.gender << "|" << User.noTelepon << "|"
             << User.statusKawin << "|" << User.tanggungan << "|" << User.statusPTKP << "|"
             << User.statusWajibPajak << "|" << User.alamat << endl;
        file.close();
        cout << "\n✅ Data berhasil disimpan ke npwp.txt\n";
    } else {
        cout << "\n❌ Gagal menyimpan data ke file.\n";
    }
}

// Fungsi untuk melihat data yang sudah ada
void lihatData() {
    system("cls");
    ifstream file("npwp.txt");
    string line;

    cout << "\n==== DAFTAR DATA NPWP ====\n";
    if (file.is_open()) {
        int no = 1;
        while (getline(file, line)) {
            cout << "\nData ke-" << no++ << ":\n";
            cout << "----------------------------------------\n";
            stringstream ss(line);
            string field;
            int fieldNo = 1;

            while (getline(ss, field, '|')) {
                switch (fieldNo) {
                    case 1: cout << "NPWP: " << field << endl; break;
                    case 2: cout << "NIK: " << field << endl; break;
                    case 3: cout << "Jenis Kelamin: " << field << endl; break;
                    case 4: cout << "No Telepon: " << field << endl; break;
                    case 5: cout << "Status Kawin: " << field << endl; break;
                    case 6: cout << "Jumlah Tanggungan: " << field << endl; break;
                    case 7: cout << "Status PTKP: " << field << endl; break;
                    case 8: cout << "Status Wajib Pajak: " << field << endl; break;
                    case 9: cout << "Alamat: " << field << endl; break;
                }
                fieldNo++;
            }
            cout << "----------------------------------------\n";
        }
        file.close();
    } else {
        cout << "❌ Gagal membuka file.\n";
    }
}

int main() {
    system("cls");
    srand(time(0)); // supaya rand() beda tiap jalan

    int pilihan;
    cout << "Pilih Menu:\n";
    cout << "1. Tambah Data NPWP\n";
    cout << "2. Lihat Data NPWP\n";
    cout << "Pilihan (1-2): ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            daftarUser();
            break;
        case 2:
            lihatData();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
    }

    return 0;
}
