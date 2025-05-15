#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

struct NPWPTempt {
    string NPWP;//1 more bit for null terminator 
    string NIK;
    string Name;
    char gender;
    string noTelepon;
    bool statusKawin;
    int tanggungan;
    string PTKP;
    bool statusWajibPajak;
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

vector<NPWPTempt> pulldata(){ 
    vector<NPWPTempt> TempData;
    ifstream file("npwp.txt");
    string line;

    if (file.is_open()) {
        int indx = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string field;
            int fieldNo = 1;
            NPWPTempt Temp;

            //getting the string until ','
            while (getline(ss, field, ',')) {
                switch (fieldNo) {
                    case 1: Temp.NPWP = field; break;
                    case 2: Temp.NIK = field; break;
                    case 3: Temp.Name = field; break;
                    case 4: Temp.gender = field.at(0) ; break;
                    case 5: Temp.noTelepon = field; break;
                    case 6: Temp.statusKawin = (field == "1")? true: false; break;
                    case 7: Temp.tanggungan = stoi(field); break;
                    case 8: Temp.PTKP = field; break;
                    case 9: Temp.statusWajibPajak = (field == "1")? true: false; break;
                    case 10: Temp.alamat = field; break;
                }
                fieldNo++;
            }
            indx++;
            TempData.push_back(Temp);
        }
        file.close();
    } else {
        cout << "❌ Gagal membuka file.\n";
        return TempData;
    }
    
    return TempData;
}

bool CheckNIK(string NIK){
    vector<NPWPTempt> Data = pulldata();
    for(size_t i = 0; i < Data.size(); ++i){
        if(Data[i].NIK == NIK){
            return true;
        }
    }
    return false;
}


long int PTKPtoValue(string PTKP){
    if(PTKP == "TK-0") return 54000000;
    else if(PTKP == "TK-1") return 58500000;
    else if(PTKP == "TK-2") return 63000000;
    else if(PTKP == "TK-3") return 67500000;
    else if(PTKP == "K-0") return 58500000;
    else if(PTKP == "K-1") return 63000000;
    else if(PTKP == "K-2") return 67500000;
    else if(PTKP == "K-3") return 72000000;
    else{
        cout << "Error PTKP can't be classified" << endl;
        return 0;
    }
}

// Fungsi untuk menambah data
void daftarUser() {
    NPWPTempt User;
    char pilihanJenis;
    int kodeJenisWP;

    cout << "=== PENDAFTARAN NPWP ===" << endl;
    cout << "Pilih Jenis Wajib Pajak:" << endl;
    cout << "1. WP Pekerja Bebas/profesional (Dokter, Notaris, dll)" << endl;
    cout << "2. WP Orang Pribadi (Pengusaha)" << endl;
    cout << "3. WP Orang Pribadi (Karyawan)" << endl;
    cout << "Pilihan (1-3): ";
    cin >> pilihanJenis;
    cin.ignore();

    cout << "Masukkan NIK: ";
    getline(cin, User.NIK);
    if(CheckNIK(User.NIK)){
        cout << "NIK sudah terdaftar\nanda dapat melakukan pencarian data dengan NIK terkait" << endl;
        return;
    }

    cout << "Masukan Nama : ";
    getline(cin, User.Name);

    do{
        cout << "Masukkan Jenis Kelamin (L/P): ";
        cin >> User.gender;
        cin.ignore();
        if((User.gender != 'L' && User.gender != 'P') && (User.gender != 'l' && User.gender != 'p')){
            cout << "harap masukan input yang sesuai" << endl;
        }
    } while ((User.gender != 'L' && User.gender != 'P') && (User.gender != 'l' && User.gender != 'p'));
    User.gender = toupper(User.gender); //change char to uppercase

    
    do{
        cout << "Masukkan No Telepon (12)      : ";
        cin >> User.noTelepon;
        cin.ignore();
    }
    while(User.noTelepon.length() < 12 || User.noTelepon.length() > 13);

    char tempK;
    
    do{
        cout << "Kawin(K) / Lajang(L): ";
        cin >> tempK;
        cin.ignore();
    }
    while((tempK != 'k' && tempK != 'l')&&(tempK != 'K' && tempK != 'L'));
    User.statusKawin = (tempK == 'k' || tempK == 'K')? true : false;

    cout << "Jumlah Tanggungan (maks 3): ";
    cin >> User.tanggungan;
    cin.ignore();
    User.tanggungan = (User.tanggungan > 3)? 3 : User.tanggungan;

    if(User.statusKawin){
        User.PTKP = "K-" + to_string(User.tanggungan);
    }
    else{
        User.PTKP = "TK-" + to_string(User.tanggungan);
    }

    long int NilaiPTKP = PTKPtoValue(User.PTKP);
    long int currentsalary;
    cout << "Masukan Gaji anda saat ini : ";
    cin >> currentsalary;
    cin.ignore();
    User.statusWajibPajak = (currentsalary > NilaiPTKP)? true: false;
    
    cout << "Alamat                      : ";
    getline(cin, User.alamat);
    
    // Menentukan kode jenis WP berdasarkan pilihan
    switch (pilihanJenis) {
        case '1': kodeJenisWP = 1 + rand() % 3; break; // 01–03
        case '2': kodeJenisWP = 4 + rand() % 3; break; // 04–06
        case '3': kodeJenisWP = 7 + rand() % 3; break; // 07–09
        default : kodeJenisWP = 0; break;
    }
    
    // generate NPWP 
    User.NPWP = generateFormattedNPWP(kodeJenisWP);
    
    // Menampilkan data yang telah dimasukkan
    cout << "\n=== DATA YANG TELAH DITAMBAHKAN ===" << endl;
    cout << "NPWP: " << User.NPWP << endl;
    cout << "NIK: " << User.NIK << endl;
    cout << "Jenis Kelamin: " << User.gender << endl;
    cout << "No Telepon: " << User.noTelepon << endl;
    cout << "Status Kawin: " << boolalpha << User.statusKawin << endl;
    cout << "Jumlah Tanggungan: " << User.tanggungan << endl;
    cout << "Status PTKP: " << User.PTKP << endl;
    cout << "Status Wajib Pajak: " << boolalpha << User.statusWajibPajak << endl;
    cout << "Alamat: " << User.alamat << endl;

    // Simpan data ke file
    ofstream file("npwp.txt", ios::app);
    if (file.is_open()) {
        file << User.NPWP << ',' << User.NIK << ',' << User.Name << ',' << User.gender << ',' << User.noTelepon << ','
             << User.statusKawin << ',' << User.tanggungan << ',' << User.PTKP << ','
             << User.statusWajibPajak << ',' << User.alamat << endl;
        file.close();
        cout << "\n✅ Data berhasil disimpan ke npwp.txt\n";
    } else {
        cout << "\n❌ Gagal menyimpan data ke file.\n";
    }
}


//menarik data dari txt ke dalam variable

string booltostring(bool cond){
    return (cond)? "aktif" : "tidak aktif";
}

void caridata(){
    vector<NPWPTempt> Data = pulldata();
    size_t index = 0;
    NPWPTempt SearchData;
    char option;
    bool found = false;
    cout << Data[0].Name << endl;
    cout << "Cari data berdasar" << endl;
    cout << "1.Nama" << endl;
    cout << "2.NPWP" << endl;
    cout << "3.NIK" << endl;
    cin >> option;
    cin.ignore();
    
    switch (option)
    {
        case '1':
        cout << "Masukan Nama anda : " << endl;
        getline(cin, SearchData.Name);
        for(size_t i = 0; i < Data.size(); ++i){
            if(Data[i].Name == SearchData.Name){
                found = true;
                index = i;
                break;
            }
        }
        break;
    case '2':
        cout << "Masukan NPWP anda : " << endl;
        getline(cin, SearchData.NPWP);
        for(size_t i = 0; i < Data.size(); ++i){
            if(Data[i].NPWP == SearchData.NPWP){
                found = true;
                index = i;
                break;
            }
        }
        break;
    case '3':
        cout << "Masukan NIK anda : " << endl;
        getline(cin, SearchData.NIK);
        for(size_t i = 0; i < Data.size(); ++i){
            if(Data[i].NIK == SearchData.NIK){
                found = true;
                index = i;
                break;
            }
        }
        break;
    default:
        break;
    }
    
    if(found){
        cout << setfill('=') << setw(60) << "" << setfill(' ') << endl;
        cout << " NPWP             : " << Data[index].NPWP << endl;
        cout << " NIK              : " << Data[index].NIK << endl;
        cout << " Name             : " << Data[index].Name << endl;
        cout << " gender           : " << Data[index].gender << endl;
        cout << " noTelepon        : " << Data[index].noTelepon << endl;
        cout << " statusKawin      : " << booltostring(Data[index].statusKawin) << endl;
        cout << " tanggungan       : " << Data[index].tanggungan << endl;
        cout << " PTKP             : " << Data[index].PTKP << endl;
        cout << " statusWajibPajak : " << booltostring(Data[index].statusWajibPajak) << endl;
        cout << " alamat           : " << Data[index].alamat << endl;
        cout << setfill('=') << setw(60) << "" << setfill(' ') << endl;
    }else{
        cout << "Data tidak ditemukan" << endl;
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
            cout << "\nData ke-" << no+1 << ":\n";
            cout << "----------------------------------------\n";
            stringstream ss(line);
            string field;
            int fieldNo = 1;

            while (getline(ss, field, ',')) {
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
            no++;
        }
        file.close();
    } else {
        cout << "❌ Gagal membuka file.\n";
    }
}

void MenuNPWP(){
    char pilihan = ' ';
    while(pilihan != '3'){
        system("cls");
        cout << "Pilih Menu:\n";
        cout << "1. Tambah Data NPWP\n";
        cout << "2. Lihat Data NPWP\n";
        cout << "3. kembali ke menu utama\n";
        cout << "Pilihan (1-2): ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan) {
            case '1':
                daftarUser();
                break;
            case '2':
                caridata();
                break;
            case '3':
                return;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                cout << "press any button to continue";
                getchar();
            break;
        }
    }
}

int main() {
    system("cls");
    srand(time(0)); // supaya rand() beda tiap jalan
    char pilihan;
    cout << "Pilih Menu:\n";
    cout << "1. Daftar atau Cek NPWP\n";
    cout << "2. Bayar Pajak\n";
    cout << "3. Admin\n";
    cout << "Pilihan (1-2): ";
    cin >> pilihan;

    switch (pilihan) {
        case '1':
            MenuNPWP();
            break;
        case '2':
            break;
        case '3':
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
    }
}  
