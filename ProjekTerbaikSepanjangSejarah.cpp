#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm> 
#include <conio.h>
#include <cctype>
#include <vector>
#include <iomanip>

using namespace std;

struct NPWPTempt {
    string NPWP;
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

void clearScreen() {
#ifdef _WIN32 // for Windows
    system("cls");
#elif defined(__linux__) // for Linux
    cout << "\n";
    system("clear");
#endif
}

//visible buat nentuin brp banyak karakter yang ingin diperlihatkan
//ShowLastW nentuin apakah karakter terakhir boleh terlihat
string maskedInput(bool ShowLastW = false, int visible = 0, char maskChar = '*') {
    string input; 
    char ch; // ini char yang di pake cuman buat nyimpen

    while (true) {
        ch = _getch();

        // Enter = ASCII 13(teken enter loop berakhir)
        if (ch == 13) {
            cout << endl;
            break;
        }

        // Backspace = ASCII 8/ disini spasi bakal ke tutup juga(kecuali dia blm masukin apa apa)
        if (ch == 8 && !input.empty()) {
            input.pop_back();
            cout << "\b \b";
        }

        // isprint itu buar karakter yang ditampilin jadi spasi gak bakal ke input
        else if (isprint(ch)) {
            input.push_back(ch); // ch itu karakter, jadi push_back bakal masukin karakter ke input

            if (ShowLastW) {
                // untuk nentuin berapa banyak karak yg gak boleh terlihat
                if ((int)input.size() <= (int)input.size() - visible)
                    cout << maskChar;
                else {
                    // Tampilkan karakter terakhir
                    cout << ch;
                }
            } else {
                // jadi disini bakal ketutupan semua sama *
                cout << maskChar;
            }
        }
    }

    return input;
}


struct Admintempt{
    char name[50];
    char username[50];
    char password[50];
};
bool adminMode = false;
string u, n;


void toLowercase(string *text){
    string newtext = *text;
    transform(newtext.begin(), newtext.end(), newtext.begin(), ::tolower);
    *text = newtext;
}

string commatodot(string text){
    string newtext = text;
    for(int i = 0; i < text.length(); i ++){
        if(text[i] == ',')
            newtext[i] = '.';   
    }
    return newtext;
}

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
    ifstream file("./Data/NPWP.txt");
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
        cout << "Gagal membuka file.\n";
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
    if(PTKP == "TK0") return 54000000;
    else if(PTKP == "TK1") return 58500000;
    else if(PTKP == "TK2") return 63000000;
    else if(PTKP == "TK3") return 67500000;
    else if(PTKP == "K0") return 58500000;
    else if(PTKP == "K1") return 63000000;
    else if(PTKP == "K2") return 67500000;
    else if(PTKP == "K3") return 72000000;
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

    while(User.NIK.length() < 16){
        cout << "Masukkan NIK: ";
        getline(cin, User.NIK);
        if(CheckNIK(User.NIK)){
            cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
            cout << "NIK sudah terdaftar\nanda dapat melakukan pencarian data dengan NIK terkait\npress enter to continue...";
            getchar();
            return;
        }
    }

    while(User.Name.length() == 0 ){
        cout << "Masukan Nama : ";
        getline(cin, User.Name);
    }

    do{
        cout << "Masukkan Jenis Kelamin (L/P): ";
        cin >> User.gender;
        cin.ignore();
        if((User.gender != 'L' && User.gender != 'P') && (User.gender != 'l' && User.gender != 'p')){
            cout << "harap masukan input yang sesuai" << endl;
        }
    } while ((User.gender != 'L' && User.gender != 'P') && (User.gender != 'l' && User.gender != 'p'));
    User.gender = toupper(User.gender); //change char to uppercase

    do
    {
        cout << "Masukkan No Telepon (12 digit)      : ";
        cin >> User.noTelepon;
        cin.ignore();
    } while (User.noTelepon.length() < 12);
    

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
        User.PTKP = "K" + to_string(User.tanggungan);
    }
    else{
        User.PTKP = "TK" + to_string(User.tanggungan);
    }

    long int NilaiPTKP = PTKPtoValue(User.PTKP);
    long int currentsalary;
    cout << "Masukan Gaji anda saat ini : ";
    cin >> currentsalary;
    cin.ignore();
    User.statusWajibPajak = (currentsalary > NilaiPTKP)? true: false;
    
    cout << "Alamat                      : ";
    getline(cin, User.alamat);
    User.alamat = commatodot(User.alamat);

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
    clearScreen();
    cout << "NPWP: " << User.NPWP << endl;
    cout << "NIK: " << User.NIK << endl;
    cout << "NIK: " << User.Name << endl;
    cout << "Jenis Kelamin: " << User.gender << endl;
    cout << "No Telepon: " << User.noTelepon << endl;
    cout << "Status Kawin: " << boolalpha << User.statusKawin << endl;
    cout << "Jumlah Tanggungan: " << User.tanggungan << endl;
    cout << "Status PTKP: " << User.PTKP << endl;
    cout << "Status Wajib Pajak: " << boolalpha << User.statusWajibPajak << endl;
    cout << "Alamat: " << User.alamat << endl;
    cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;

    // Simpan data ke file
    ofstream file("./Data/NPWP.txt", ios::app);
    if (file.is_open()) {
        file << User.NPWP << ',' << User.NIK << ',' << User.Name << ',' << User.gender << ',' << User.noTelepon << ','
             << User.statusKawin << ',' << User.tanggungan << ',' << User.PTKP << ','
             << User.statusWajibPajak << ',' << User.alamat << endl;
        file.close();
        cout << "\nData berhasil disimpan\n";
    } else {
        cout << "\nGagal menyimpan data.\n";
    }
    cout << "press any key to continue....";
    getchar();
}

string booltostring(bool cond){
    return (cond)? "aktif" : "tidak aktif";
}

string gendertostring(char text){
    return (text == 'L')? "Laki-laki" : "Perempuan";
}

void caridata(){
    vector<NPWPTempt> Data = pulldata();
    size_t index = 0;
    NPWPTempt SearchData;
    char option;
    bool found = false;
    clearScreen();
    cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
    cout << "Cari data berdasar" << endl;
    cout << "1.Nama" << endl;
    cout << "2.NPWP" << endl;
    cout << "3.NIK" << endl;
    cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
    cout << "Masukan Opsi : ";
    cin >> option;
    cin.ignore();
    cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
    switch (option)
    {
        case '1':
        cout << "\nMasukan Nama anda : ";
        getline(cin, SearchData.Name);
        toLowercase(&SearchData.Name);
        for(size_t i = 0; i < Data.size(); ++i){
            toLowercase(&Data[i].Name);
            if(Data[i].Name == SearchData.Name){
                found = true;
                index = i;
                break;
            }
        }
        break;
    case '2':
        cout << "Masukan NPWP anda : ";
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
        cout << "Masukan NIK anda : ";
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
        clearScreen();
        cout << setfill('=') << setw(60) << "" << setfill(' ') << endl;
        cout << " NPWP               : " << Data[index].NPWP << endl;
        cout << " NIK                : " << Data[index].NIK << endl;
        cout << " Name               : " << Data[index].Name << endl;
        cout << " gender             : " << gendertostring(Data[index].gender) << endl;
        cout << " noTelepon          : " << Data[index].noTelepon << endl;
        cout << " statusKawin        : " << booltostring(Data[index].statusKawin) << endl;
        cout << " tanggungan         : " << Data[index].tanggungan << endl;
        cout << " PTKP               : " << Data[index].PTKP << endl;
        cout << " status Wajib Pajak : " << booltostring(Data[index].statusWajibPajak) << endl;
        cout << " alamat             : " << Data[index].alamat << endl;
        cout << setfill('=') << setw(60) << "" << setfill(' ') << endl;
    }else{
        cout << "Data tidak ditemukan" << endl;
    }
    cout << "press any key to continue..";
    getchar();
}

// Fungsi untuk melihat data yang sudah ada
void lihatData() {
    clearScreen();
    ifstream file("./Data/NPWP.txt");
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
                    case 1: cout << "NPWP               : " << field << endl; break;
                    case 2: cout << "NIK                : " << field << endl; break;
                    case 3: cout << "Nama               : " << field << endl; break;
                    case 4: cout << "Jenis Kelamin      : " << field << endl; break;
                    case 5: cout << "No Telepon         : " << field << endl; break;
                    case 6: cout << "Status Kawin       : " << field << endl; break;
                    case 7: cout << "Jumlah Tanggungan  : " << field << endl; break;
                    case 8: cout << "Status PTKP        : " << field << endl; break;
                    case 9: cout << "Status Wajib Pajak : " << field << endl; break;
                    case 10: cout <<"Alamat             : " << field << endl; break;
                }
                fieldNo++;
            }
            cout << "----------------------------------------\n";
            no++;
        }
        file.close();
    } else {
        cout << " Gagal membuka file.\n";
    }
}

void MenuNPWP(){
    char pilihan = ' ';
    while(pilihan != '3'){
        clearScreen();
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilih Menu:\n";
        cout << "1. Tambah Data NPWP\n";
        cout << "2. Lihat Data NPWP\n";
        cout << "3. kembali ke menu utama\n";
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilihan (1-3): ";
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

/*
A
D
M
I
N
*/

vector<Admintempt> adminlist;


void saveAdminList() {
    ofstream file("./Data/Admin.dat", ios::binary);
    if (!file.is_open()) {
        cout << "Gagal membuka file Admin.dat untuk menyimpan.\n";
        return;
    }

for (size_t i = 0; i < adminlist.size(); ++i) {
    const Admintempt &admin = adminlist[i];
    file.write(reinterpret_cast<const char*>(&admin), sizeof(Admintempt));
}

    file.close();
}


vector<Admintempt> loadDadmin() {
    vector<Admintempt> temp;
   ifstream file("./Data/Admin.dat", ios::binary);
    if (!file.is_open()) return temp;

    Admintempt admin;

    // Selama bisa membaca 1 struct penuh dari file
    while (file.read(reinterpret_cast<char*>(&admin), sizeof(Admintempt))) {
        temp.push_back(admin);
    }

    file.close();
    return temp;
}

void addAdmin() {
    clearScreen();
    Admintempt admin;
    string temp;

    cout << "Tambah Admin Baru\n";


    while (true) {
        cout << "Nama\t\t: ";
        cin.getline(admin.name, 50);

        bool name = false;
        for (size_t i = 0; i < adminlist.size(); i++) {
            if (adminlist[i].name == admin.name) {
                name = true;
                break;
            }
        }

        if (name) {
            cout << "Nama sudah digunakan, silakan masukkan nama lain.\n";
        } else {
            break;
        }
    }


    while (true) {
        cout << "Username(4 char)\t: ";
        getline(cin, temp);
        toLowercase(&temp);   // jadikan lowercase
        strncpy(admin.username, temp.c_str(), sizeof(admin.username) - 1);
        admin.username[sizeof(admin.username) - 1] = '\0';

        if (strlen(admin.username) < 4) {
            cout << "Username terlalu pendek, coba lagi.\n";
            continue;
        }

        bool username = false;
        for (size_t i = 0; i < adminlist.size(); i++) {
            if (adminlist[i].username == admin.username) {
                username = true;
                break;
            }
        }

        if (username) {
            cout << "Username sudah digunakan, silakan masukkan username lain.\n";
        } else {
            break;
        }
    }


while (true) {
    cout << "Password\t\t: ";
    string pass = maskedInput();

    if (pass.length() < 8) {
        cout << "Password terlalu pendek, coba lagi.\n";
    } else {
        strncpy(admin.password, pass.c_str(), sizeof(admin.password) - 1);
        admin.password[sizeof(admin.password) - 1] = '\0'; 
        break;
    }
}
    // Tambah admin baru ke list
    adminlist.push_back(admin);
    saveAdminList();

    cout << "Admin berhasil ditambahkan.\n";
    getchar();
}

void deleteAdmin() {
    clearScreen();
    string username;
    cout << "Masukkan username admin yang ingin dihapus: ";
    getline(cin, username);
    
    bool found = false;
    int index = -1;
    
    // Cari index admin yang username-nya sama dengan input user
    for (int i = 0; i < adminlist.size(); ++i) {
        if (adminlist[i].username == username) {
            found = true;
            index = i;
            break;  // langsung keluar loop setelah ketemu
        }
    }



    if (found) {
        string deletedName = adminlist[index].name;
        string deletedUsername = adminlist[index].username;

        adminlist.erase(adminlist.begin() + index);

        cout << "Admin\t\t: \nNama\t\t: " << deletedName
            << "\nUsername\t: " << deletedUsername << " berhasil dihapus.\n";

        // Simpan perubahan ke file
        saveAdminList();
        getchar();
    } else {
        cout << "Admin dengan username '" << username << "' tidak ditemukan.\n";
        getchar();
    }
}

void forgetPassword(){
    string inputuser, inputname, newPass;
    int index = -1;
    bool found = false;
    clearScreen();
    
    cout << "Username\t: "; cin >> inputuser;
    cout << "Name\t: "; cin >> inputname;
    
    for (size_t i = 0; i < adminlist.size(); i++){
        if (inputuser == adminlist[i].username && inputname == adminlist[i].name){
            found = true;
            index = i;
            break;
        }
    }
    
    if(found){
        cout << "Verifikasi berhasil !!";
        getchar();
        
        cout << "Masukan Password baru\t: "; newPass = maskedInput();
        string temppass = newPass;
        while (true){
            cout << "konfirmasi Password baru\t: "; newPass = maskedInput();
                
            if(newPass != temppass){
                cout << "Password baru tidak sesuai !!";
                getchar();
            } else {
                break;
            }
        

        }
        strncpy(adminlist[index].password, newPass.c_str(), sizeof(adminlist[index].password) - 1);
        adminlist[index].password[sizeof(adminlist[index].password) - 1] = '\0';
    
        saveAdminList();
        cout << "Password berhasil diganti !! ";
    }else {
        cout << "Data tidak cocok. Reset gagal.\n";
        getchar();
    }

    cout << "Tekan enter untuk lanjut...";
    getchar();

}

void UpdateAdmin() {
    clearScreen();
string username, password;
cout << "Pastikan ini anda " << n << endl;
cout << "Username\t: ";
cin >> username;

bool found = false;
int index = -1;

for (int i = 0; i < adminlist.size(); i++) {
    if (adminlist[i].username == username && u == username) {
        cout << "Password\t: ";
        password = maskedInput();

        if (adminlist[i].password == password) {
            found = true;
            index = i;
        } else {
            cout << "Password salah!\n";
            return;
        }
        break; 
    } 

    else if (adminlist[i].username == username && u != username) {
        cout << "Anda hanya boleh mengubah akun anda sendiri\n";
        return;
    }
}

if (!found) {
    cout << "Admin tidak ditemukan atau password salah.\n";
    return;
}

    string newName, newUser, newPass;

    cout << "Nama Baru\t: ";
    getline(cin, newName);
    for (int i = 0; i < adminlist.size(); ++i) {
    if (i != index && adminlist[i].username == newUser) {
        cout << "Username baru sudah digunakan admin lain.\n";
        return;
    }
}
    cout << "Username Baru\t: ";
    getline(cin, newUser);
    cout << "Password Baru\t: ";
    newPass = maskedInput();

    strncpy(adminlist[index].name, newName.c_str(), sizeof(adminlist[index].name) - 1);
    strncpy(adminlist[index].username, newUser.c_str(), sizeof(adminlist[index].username) - 1);
    strncpy(adminlist[index].password, newPass.c_str(), sizeof(adminlist[index].password) - 1);

    adminlist[index].name[sizeof(adminlist[index].name) - 1] = '\0';
    adminlist[index].username[sizeof(adminlist[index].username) - 1] = '\0';
    adminlist[index].password[sizeof(adminlist[index].password) - 1] = '\0';

    saveAdminList();
    cout << "Admin berhasil diperbarui!\n";
    getchar();
}

bool LoginAdmin() {
    clearScreen();
    int tries = 3;
    string inputuser, inputpass;

    while (tries > 0) {
        clearScreen();
        int index;
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "====== LOGIN ADMIN ======" << endl;
        cout << "Ketik '#' pada kolom Username jika lupa password.\n";
        cout << "Username\t: ";
        getline(cin, inputuser);
        if(inputuser == "#"){
            forgetPassword();
            return false;
        }
        cout << "Password\t: ";
        inputpass = maskedInput();

        bool found = false;
        for (size_t i = 0; i < adminlist.size(); i++) {
            if (inputuser == adminlist[i].username && inputpass == adminlist[i].password) {
                found = true;
                index = i;
                break;
            }
        }

        if (found) {
            cout << "\nLogin berhasil. Selamat datang Admin " << adminlist[index].name << "!" << endl;
            u = inputuser;
            n = adminlist[index].name;
            adminMode = true;
            getchar();
            return true;
        } else {
            tries--;
            cout << "\nLogin gagal. Sisa percobaan: " << tries << endl;
            if (tries > 0) {
                cout << "Tekan Enter untuk mencoba lagi...";
                cin.ignore();
                getchar();
            }
        }
    }

    cout << "\nLogin gagal berkali-kali. JANGAN NGAKU ADMIN !!.\n";
    getchar();
    return false;
}

void AkunAdmin() {
    char pilihan;
    do {
        clearScreen();
        cout << setfill('=') << setw(40) << "" << setfill(' ') << endl;
        cout << "         MENU AKUN ADMIN\n";
        cout << setfill('=') << setw(40) << "" << setfill(' ') << endl;
        cout << "1. Tambah Admin\n";
        cout << "2. Ubah Data Admin\n";
        cout << "3. Hapus Admin\n";
        cout << "4. Kembali ke Menu Utama\n";
        cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
        cout << "Pilih opsi (1-4): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case '1':
                addAdmin();
                break;
            case '2':
                UpdateAdmin();
                break;
            case '3':
                deleteAdmin();
                break;
            case '4':
                return;
            default:
                cout << "Opsi tidak valid. Tekan Enter untuk lanjut...";
                getchar();
                break;
        }
    } while (pilihan != '4');
}


void adminMenu() {
    char choice;
    do {
        clearScreen();
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Akun admin Menu" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: "; cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1':
                AkunAdmin();
                break;
            case '2':

            case '0':
                adminMode = false;
                cout << "Logout berhasil.\n";
                return;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (true);
}



int main() {
    adminlist = loadDadmin();
    srand(time(0)); // supaya rand() beda tiap jalan
    char pilihan;
    
    while(pilihan != '3'){
        clearScreen();
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilih Menu:\n";
        cout << "1. Daftar atau Cek NPWP\n";
        cout << "2. Bayar Pajak\n";
        cout << "3. Keluar Program\n";
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilihan (1-3) : ";
        cin >> pilihan;
        cin.ignore();
        
        switch (pilihan) {
            case '#':
                if(LoginAdmin())
                    adminMenu();
                break;

            case '1':
                MenuNPWP();
                break;
            case '2':
                break;
            case '3':
                cout << "press key to confirm....";
                getchar();
                return 0;
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                cout << "press any button to continue"; getchar();
                break;
        }
    }
    return 0;
}