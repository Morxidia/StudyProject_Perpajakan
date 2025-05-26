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
#include <limits>

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

struct TaxForm
{
    string NPWP;
    string NIK;
    string Name;
    char gender;
    string paymentYear;
    string salary;
    string additionalIncome;
    string allowance;
    string honorium;
    string totalIncome;
    string positionExpanse;
    string pension;
    string netIncome;   
    string PTKP;
    string taxIncome;
    string percTax;
    string taxTotal;
};

void clearScreen() {
#ifdef _WIN32 // for Windows
    system("cls");
#elif defined(__linux__) // for Linux
    cout << "\n";
    system("clear");
#endif
}

string addThousandSeparators(string num){
    int pos = num.find('.');
    int len = (pos == string::npos)? num.length() : pos;
    for(int i = len - 3; i > 0; i -=3){
        num.insert(i, ".");
    }
    return num;
}

string cleanNumberInput(const string& input){
    string cleaned;
    for(char c : input){
        if(isdigit(c)){
            cleaned += c;
        }
    }
    return cleaned;
}

string numSeparatorInput(string inputPhrase){
    string input;
    char ch;

    cout << inputPhrase;
     
    while((ch = _getch()) != '\r'){
        if (ch == '\b'){
            if(!input.empty()){
                input.pop_back();
                cout << "\b \b";
            }

        }
        else if (isdigit(ch)){
            input += ch;
            cout << ch;
        }

        string cleaned = cleanNumberInput(input);
        string formated = addThousandSeparators(cleaned);

        cout << "\r" << string(50, ' ') << "\r";
        cout << inputPhrase << formated;
    }
    cout << endl;
    return input;
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

        // isprint itu buat karakter yang ditampilin jadi spasi gak bakal ke input
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

string commaToDot(string text){
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

vector<NPWPTempt> pullNPWP(){ 
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

vector<TaxForm> pullTaxHistory(){
    vector<TaxForm> TempData;
    ifstream file("./Data/TaxPaymentHistory.txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string field;
            int fieldNo = 1;
            TaxForm Temp;

            //getting the string until ','
            while (getline(ss, field, ',')) {
                switch (fieldNo) {
                    case 1: Temp.NPWP = field; break;
                    case 2: Temp.NIK = field; break;
                    case 3: Temp.Name = field; break;
                    case 4: Temp.gender = field.at(0); break;
                    case 5: Temp.paymentYear = field; break;
                    case 6: Temp.salary = field; break;
                    case 7: Temp.additionalIncome = field; break;
                    case 8: Temp.allowance = field; break;
                    case 9: Temp.honorium = field; break;
                    case 10: Temp.totalIncome = field; break;
                    case 11: Temp.positionExpanse = field; break;
                    case 12: Temp.pension = field; break;
                    case 13: Temp.netIncome = field; break;
                    case 14: Temp.PTKP = field; break;
                    case 15: Temp.taxIncome = field; break;
                    case 16: Temp.percTax = field; break;
                    case 17: Temp.taxTotal = field; break;
                }
                fieldNo++;
            }
            TempData.push_back(Temp);
        }
        file.close();
    } else {
        cout << "Gagal membuka file.\n";
        return TempData;
    }
    
    return TempData;
}

int CheckNIK(string NIK){
    vector<NPWPTempt> Data = pullNPWP();
    for(size_t i = 0; i < Data.size(); ++i){
        if(Data[i].NIK == NIK){
            return i;
        }
    }
    return -1;
}

int checkNPWP(string NPWP){
    vector<NPWPTempt> Data = pullNPWP();
    for(size_t i = 0; i < Data.size(); ++i){
        if(Data[i].NPWP == NPWP){
            return i;
        }
    }
    return -1;
}

int checkName(string name){
    vector<NPWPTempt> Data = pullNPWP();
    toLowercase(&name);
    for(size_t i = 0; i < Data.size(); ++i){
        toLowercase(&Data[i].Name);
        if(Data[i].Name == name){
            return i;
        }
    }
    return -1;
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

bool isNumber(string &text){
    for(char c : text){
        if(!isdigit(c)){
            return false;
        }
    }
    return !text.empty();
}

// Fungsi untuk menambah data
void daftarUser() {
    NPWPTempt User;
    char pilihanJenis;
    int kodeJenisWP;
    int consoleWidth = 50;

    clearScreen();
    cout << "=================== PENDAFTARAN NPWP ===================" << endl;
    cout << "Pilih Jenis Wajib Pajak:" << endl;
    cout << "1. WP Pekerja Bebas/profesional (Dokter, Notaris, dll)" << endl;
    cout << "2. WP Orang Pribadi (Pengusaha)" << endl;
    cout << "3. WP Orang Pribadi (Karyawan)" << endl;
    cout << "Pilihan (1-3): ";
    cin >> pilihanJenis;
    cin.ignore();

    int nikminlen = 16;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    do
    {
        cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
        cout << "Masukkan NIK\t\t\t: ";
        getline(cin, User.NIK);
        if((CheckNIK(User.NIK) != -1)){
            clearScreen();
            cout << "NIK '" << User.NIK << "' sudah terdaftar\nanda dapat melakukan pencarian data dengan NIK terkait\npress enter to continue...";
            getchar();
            return;
        }
    } while ((User.NIK.length() < nikminlen) || !(isNumber(User.NIK)));

    while(User.Name.length() == 0 ){
        cout << "Masukan Nama\t\t\t: ";
        getline(cin, User.Name);
    }

    do{
        cout << "Masukkan Jenis Kelamin (L/P)\t: ";
        cin >> User.gender;
        cin.ignore();
        if((User.gender != 'L' && User.gender != 'P') && (User.gender != 'l' && User.gender != 'p')){
            cout << "harap masukan input yang sesuai" << endl;
        }
    } while ((User.gender != 'L' && User.gender != 'P') && (User.gender != 'l' && User.gender != 'p'));
    User.gender = toupper(User.gender); //change char to uppercase

    int telplen = 12;
    do
    {
        cout << "Masukkan No Telepon (12 digit)\t: ";
        cin >> User.noTelepon;
        cin.ignore();
    } while (User.noTelepon.length() < telplen);
    

    char statuskawin;    
    do{
        cout << "Kawin(K) / Lajang(L)\t\t: ";
        cin >> statuskawin;
        cin.ignore();
    }
    while((statuskawin != 'k' && statuskawin != 'l')&&(statuskawin != 'K' && statuskawin != 'L'));
    User.statusKawin = (statuskawin == 'k' || statuskawin == 'K')? true : false;

    int makstanggungan;
    cout << "Jumlah Tanggungan (maks 3)\t: ";
    cin >> User.tanggungan;
    cin.ignore();
    User.tanggungan = (User.tanggungan > makstanggungan)? makstanggungan : User.tanggungan;

    if(User.statusKawin){
        User.PTKP = "K" + to_string(User.tanggungan);
    }
    else{
        User.PTKP = "TK" + to_string(User.tanggungan);
    }

    long int NilaiPTKP = PTKPtoValue(User.PTKP);
    string currentsalary;
    currentsalary = numSeparatorInput("Masukan gaji anda saat ini\t: ");
    User.statusWajibPajak = (stoll(currentsalary) > NilaiPTKP)? true: false;
    
    cout << "Alamat\t\t\t: ";
    getline(cin, User.alamat);
    User.alamat = commaToDot(User.alamat);

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
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    cout << "NPWP\t\t\t: " << User.NPWP << endl;
    cout << "NIK\t\t\t: " << User.NIK << endl;
    cout << "NIK\t\t\t: " << User.Name << endl;
    cout << "Jenis Kelamin\t\t: " << User.gender << endl;
    cout << "No Telepon\t\t: " << User.noTelepon << endl;
    cout << "Status Kawin\t\t: " << boolalpha << User.statusKawin << endl;
    cout << "Jumlah Tanggungan\t: " << User.tanggungan << endl;
    cout << "Status PTKP\t\t: " << User.PTKP << endl;
    cout << "Status Wajib Pajak\t\t: " << boolalpha << User.statusWajibPajak << endl;
    cout << "Alamat\t\t\t: " << User.alamat << endl;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;

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
    vector<NPWPTempt> Data = pullNPWP();
    NPWPTempt SearchData;
    int index;
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
        index = checkName(SearchData.Name);
        break;
    case '2':
        cout << "Masukan NPWP anda : ";
        getline(cin, SearchData.NPWP);
        index = checkNPWP(SearchData.NPWP);
        break;
    case '3':
        cout << "Masukan NIK anda : ";
        getline(cin, SearchData.NIK);
        index = CheckNIK(SearchData.NIK);
        break;
    default:
        break;
    }
    
    if(index != -1){
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
    return;
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

int taxPaymentHistory(string NIK, string yearPayment){
    vector<TaxForm> taxHistory = pullTaxHistory();
    for(size_t i = 0; i < taxHistory.size(); ++i){
        if((taxHistory[i].NIK == NIK) && taxHistory[i].paymentYear == yearPayment)
            return i;
    }
    return -1;
}

NPWPTempt pullNPWPfromNPWP(string NPWP){
    vector<NPWPTempt> Data = pullNPWP();
    for(size_t i = 0; i < Data.size(); ++i){
        if(Data[i].NPWP == NPWP){
            return Data[i];
        }
    }
}

float taxtoperc(unsigned long long int income){
    if(income < 60000000)
        return 0.05;
    else if(income < 250000000)
        return 0.15;
    else if(income < 500000000)
        return 0.25;
    else if(income < 5000000000)
        return 0.30;
    else
        return 0.35;
}

void taxHistorybyNPWP(string NPWP){
    vector<TaxForm> taxHistory = pullTaxHistory();
    int consoleWidth = 50;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    for(size_t i = 0; i < taxHistory.size(); ++i){
        if(taxHistory[i].NPWP == NPWP){
            cout << "Nama\t\t\t: " << taxHistory[i].Name << endl;
            cout << "Tahun pembayaran\t: " << taxHistory[i].paymentYear << endl;
            cout << "Total yang dibayarkan\t: " << addThousandSeparators(taxHistory[i].taxTotal) << endl;
            cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
        }
    }
    return ;
}

void taxHistorybyNIK(string NIK){
    vector<TaxForm> taxHistory = pullTaxHistory();
    int consoleWidth = 50;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    for(size_t i = 0; i < taxHistory.size(); ++i){
        if(taxHistory[i].NIK == NIK){
            cout << "Nama\t\t\t: " << taxHistory[i].Name << endl;
            cout << "Tahun pembayaran\t: " << taxHistory[i].paymentYear << endl;
            cout << "Total yang dibayarkan\t: " << addThousandSeparators(taxHistory[i].taxTotal) << endl;
            cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
        }
    }
    return ;
}

void taxSearchMenu(){
    char userOption;
    string NPWP;
    string NIK;
    int consoleWidth = 50;
    string header = "Pencarian Histori Pembayaran Pajak";
    int headPadding = (consoleWidth - header.length())/2;
    clearScreen();
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    cout << setw(headPadding + header.length()) << right << header  << endl;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    cout << "Masukan opsi untuk melakukan pencarian\nhistori pembayaran pajak" << endl;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    cout << "1.Cari menggunakan NPWP" << endl;
    cout << "2.Cari menggunakan NIK" << endl;
    cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
    cout << "masukan Opsi anda : ";
    cin >> userOption;
    cin.ignore();

    switch (userOption)
    {
    case '1':
        clearScreen();
        cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
        cout << "Masukan NPWP anda\t: ";
        getline(cin, NPWP);
        taxHistorybyNPWP(NPWP);
        cout << "press any key to continue....";
        getchar();
        break;
        case '2':
        clearScreen();
        cout << setfill('-') << setw(consoleWidth) << "" << setfill(' ') << endl;
        cout << "Masukan NIK anda\t: ";
        getline(cin, NIK);
        taxHistorybyNIK(NIK);
        cout << "press any key to continue....";
        getchar();
        break;
    default:
        break;
    }
}

void taxPaymentRegistration(){   
    TaxForm userTaxForm;
    NPWPTempt UserNPWP;
    string tempNP;

    float addTaxPerc;
    char userOption;
    clearScreen();

    string header = "PENGISIAN FORM PEMBAYARAN PAJAK";
    int outputWidth = 70;
    int headPadding = (outputWidth - header.length())/2;

    cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;
    cout << setw(headPadding + header.length()) << right << header << endl;
    cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;
    cout << "Masukan NPWP anda\t\t: "; getline(cin, tempNP);

    if((checkNPWP(tempNP)) == -1){
        do
        {
            cout << "NPWP tidak ditemukan" << endl;
            cout << "apakah anda ingin lanjut dengan NIK" << endl;
            cout << "pendaftaran dengan NIK dikenakan tambahan pajak 20%' dari hasil pembayaran pajak" << endl;
            cout << "apakah ingin lanjut dengan NIK? (y/n): ";
            cin >> userOption;
            cin.ignore();
        } while ((userOption != 'Y' && userOption != 'N') && (userOption != 'y' && userOption != 'n'));

        if(userOption == 'n'){
            return;
        }

        clearScreen();
        cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;
        cout << setw(headPadding + header.length()) << right << header << endl;
        cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;
        int nikminlen = 16;
        while(UserNPWP.NIK.length() < nikminlen){
            cout << "Masukkan NIK: ";
            getline(cin, UserNPWP.NIK);
            int indexNIK = CheckNIK(UserNPWP.NIK);
            if(indexNIK != -1){
                vector<NPWPTempt> DataNPWP = pullNPWP();
                cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
                cout << "NIK sudah terdaftar" << endl;
                UserNPWP = DataNPWP[indexNIK];
                cout << "NPWP anda :" << UserNPWP.NPWP << endl;
                cout << "Nama anda :" << UserNPWP.Name << endl;
                cout << "silahkan melakukan pengisian formulir berdasar NPWP tersebut" << endl;
                cout << "press any key to continue..."; getchar();
                return;
            }
        }
        userTaxForm.NIK = UserNPWP.NIK;
        
        cout << "Masukkan Nama: ";
        getline(cin, userTaxForm.Name);


        userTaxForm.NPWP = "00.000.000.0-000.000";
        
        char statuskawin;    
        do{
            cout << "Kawin(K) / Lajang(L): ";
            cin >> statuskawin;
            cin.ignore();
        }
        while((statuskawin != 'k' && statuskawin != 'l')&&(statuskawin != 'K' && statuskawin != 'L'));

        UserNPWP.statusKawin = (statuskawin == 'k' || statuskawin == 'K')? true : false;

        cout << "Jumlah Tanggungan (maks 3): ";
        cin >> UserNPWP.tanggungan;
        cin.ignore();

        int makstanggungan;
        UserNPWP.tanggungan = (UserNPWP.tanggungan > makstanggungan)? makstanggungan : UserNPWP.tanggungan;
        
        if(UserNPWP.statusKawin){
            UserNPWP.PTKP = "K" + to_string(UserNPWP.tanggungan);
        }
        else{
            UserNPWP.PTKP = "TK" + to_string(UserNPWP.tanggungan);
        }
        addTaxPerc = 1.2;
    }
    else{
        clearScreen();
        //Pengecekan data ketika user telah memiliki NPWP

        cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;
        cout << setw(headPadding + header.length()) << right << header << endl;
        cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;

        //pull data from file
        UserNPWP = pullNPWPfromNPWP(tempNP);
        
        userTaxForm.NPWP = UserNPWP.NPWP;
        cout << "NPWP\t\t\t\t: " << userTaxForm.NPWP << endl;
        userTaxForm.NIK = UserNPWP.NIK;
        cout << "NIK\t\t\t\t: " << userTaxForm.NIK << endl;
        
        userTaxForm.gender = UserNPWP.gender;
        cout << "gender\t\t\t\t: " << userTaxForm.gender << endl;
        
        userTaxForm.Name = UserNPWP.Name;
        cout << "Nama\t\t\t\t: " << userTaxForm.Name << endl;
        

        addTaxPerc = 1.0;
    }


    cout << "Masukan Tahun pembayaran\t: 20";
    getline(cin, userTaxForm.paymentYear);
    userTaxForm.paymentYear = "20" + userTaxForm.paymentYear;

    int checkHistoryIndex = taxPaymentHistory(userTaxForm.NIK, userTaxForm.paymentYear);
    if(checkHistoryIndex != -1){
        clearScreen();
        vector<TaxForm> taxHistory = pullTaxHistory();
        TaxForm userData = taxHistory[checkHistoryIndex];
        cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
        cout << "anda sudah melakukan pembayaraan pada tahun tersebut" << endl;
        cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
        cout << "berikut adalah histori dari pembayaran anda" << endl;
        cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
        cout << "NIK\t\t\t: " << userData.NIK << endl;
        cout << "Name\t\t\t: " << userData.Name << endl;
        cout << "Net Income\t\t: " << addThousandSeparators(userData.netIncome) << endl;
        cout << "Taxable Income\t\t: " << addThousandSeparators(userData.taxIncome) << endl;
        cout << "Tax total\t\t: " << addThousandSeparators(userData.taxTotal) << endl;
        cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
        cout << "press any key to continue...";
        getchar();
        return;
    }

    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
    int timesIncome;
    do{
        cout << "Rentang waktu pemasukan dan pengeluaran yang ingin di input" << endl;
        cout << "1. tahunan" << endl;
        cout << "2. bulanan" << endl;
        cout << "\nMasukan rentang waktu penghasilan\ndan pengeluaran yang ingin anda masukan" << endl;
        cout << "\nMasukan Opsi (1/2)\t\t: ";
        cin >> userOption;
        cin.ignore();
        switch (userOption)
        {
            case '1':
            timesIncome = 1;
            break;
            case '2':
            timesIncome = 12;
            break;
            default:
            break;
        }
    }while((userOption != '2') && (userOption != '1'));
    string incomeTime = (userOption == '1')? "tahun" : "bulan";
    
    unsigned long int ptkpValue = PTKPtoValue(UserNPWP.PTKP);//menarik nilai PTKP
    
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
    cout << "Silahkan masukan pemasukan anda dalam se-" << incomeTime << endl;
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;

    userTaxForm.salary = numSeparatorInput("Masukan Gaji anda\t\t: ");
    unsigned long long int tempSalary = stoll(userTaxForm.salary);
    tempSalary = tempSalary * timesIncome;
    userTaxForm.salary = to_string(tempSalary);
    
    userTaxForm.additionalIncome = numSeparatorInput("Masukan penghasilan lain anda\t: "); 
    unsigned long long int tempAdditionalIncome = stoll(userTaxForm.additionalIncome);
    tempAdditionalIncome = tempAdditionalIncome * timesIncome;
    userTaxForm.additionalIncome = to_string(tempAdditionalIncome);
    
    userTaxForm.allowance = numSeparatorInput("Masukan tunjangan lain anda\t: "); 
    unsigned long long int tempAllowance = stoll(userTaxForm.allowance);
    tempAllowance = tempAllowance * timesIncome;
    userTaxForm.allowance = to_string(tempAllowance);
    
    userTaxForm.honorium = numSeparatorInput("Masukan honorium anda\t\t: "); 
    unsigned long long int tempHonorium = stoll(userTaxForm.honorium);
    tempHonorium = tempHonorium * timesIncome;
    userTaxForm.honorium = to_string(tempHonorium);
    
    unsigned long long int totalIncome = tempSalary + tempAdditionalIncome + tempAllowance + tempHonorium;
    userTaxForm.totalIncome = to_string(totalIncome);
    
    if(totalIncome < ptkpValue){
        clearScreen();
        cout << "Penghasilan anda lebih kecil daripada nilai PTKP, anda tidak diwajibkan membayar pajak" << endl;
        cout << "silahkan menekan tombol apa saja untuk keluar..."; getchar();
        return;
    }

    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
    cout << "Silahkan masukan Pengeluaran anda dalam se-" << incomeTime << endl;
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;

    userTaxForm.positionExpanse = numSeparatorInput("Masukan biaya jabatan anda\t: ");
    unsigned long long int tempPositionExpanse = stoll(userTaxForm.positionExpanse);
    tempPositionExpanse = tempPositionExpanse * timesIncome;
    userTaxForm.positionExpanse = to_string(tempPositionExpanse);
    
    userTaxForm.pension = numSeparatorInput("Masukan iuran pensiun anda\t: "); 
    unsigned long long int tempPension = stoll(userTaxForm.pension);
    tempPension = tempPension * timesIncome;
    userTaxForm.pension = to_string(tempPension);
    
    cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;
    cout << "Pehitungan pajak berdasarkan pemasukan dan pengeluaran anda" << endl;
    cout << setfill('=') << setw(outputWidth) << "" << setfill(' ') << endl;

    //gross income and net income calculation
    unsigned long long int totalExpanse = tempPositionExpanse + tempPension;
    unsigned long long int netIncome = totalIncome - totalExpanse;

    userTaxForm.netIncome = to_string(netIncome);

    cout << "Net income anda\t\t\t: " << addThousandSeparators(userTaxForm.netIncome) << endl;

    //nilai PTKP sudah di tarik
    cout << "PTKP anda\t\t\t: " << UserNPWP.PTKP << endl;
    cout << "Nilai PTKP anda\t\t\t: " << addThousandSeparators(to_string(ptkpValue)) << endl;
    userTaxForm.PTKP = UserNPWP.PTKP;

    unsigned long long int taxableIncome = netIncome - ptkpValue;

    userTaxForm.taxIncome = to_string(taxableIncome);
    cout << "Pengahsilan wajib pajak anda\t: " << addThousandSeparators( userTaxForm.taxIncome) << endl;

    float taxperc = taxtoperc(taxableIncome);
    taxperc = taxperc * addTaxPerc;
    userTaxForm.percTax = to_string(taxperc);

    int percentage = 100;
    cout << "Persentase pajak anda\t\t: " << taxperc*percentage << "%" << endl;
    
    unsigned long long int taxOut = taxableIncome * taxperc;
    userTaxForm.taxTotal = to_string(taxOut);
    cout << "Total Pajak yang harus dibayar\t: " << addThousandSeparators(userTaxForm.taxTotal) << endl;
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;

    ofstream file("./Data/TaxPaymentHistory.txt", ios::app);
    if(file.is_open()){
        file << userTaxForm.NPWP << ',' << userTaxForm.NIK << ',' << userTaxForm.Name << ',' << userTaxForm.gender << ','
             << userTaxForm.paymentYear << ',' << userTaxForm.salary << ',' << userTaxForm.additionalIncome << ','
             << userTaxForm.allowance << ',' << userTaxForm.honorium << ',' << userTaxForm.totalIncome << ','
             << userTaxForm.positionExpanse << ',' << userTaxForm.pension << ',' << userTaxForm.netIncome << ','
             << userTaxForm.PTKP << ',' << userTaxForm.taxIncome << ',' << userTaxForm.percTax << ',' << userTaxForm.taxTotal << endl;
        file.close();
        cout << "\nData berhasil disimpan" << endl;
    }else {
        cout << "\nGagal menyimpan data.\n";
    }
    cout << "press any key to continue....";
    getchar();
}

void taxMenu(){
    char pilihan = ' ';
    while(pilihan != '3'){
        clearScreen();
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilih Menu:\n";
        cout << "1. Registrasi pembayaran pajak tahunan\n";
        cout << "2. Lihat Histori Pembayaran pajak\n";
        cout << "3. kembali ke menu utama\n";
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilihan (1-3): ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan) {
            case '1':
                taxPaymentRegistration();
                break;
            case '2':
                taxSearchMenu();
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
    
    cout << "Username\t\t\t: "; cin >> inputuser;
    cin.ignore();
    cout << "Name\t\t\t\t: "; 
    getline(cin, inputname);

    
    
    toLowercase(&inputname);
    
    for (size_t i = 0; i < adminlist.size(); i++) {
        string name = adminlist[i].name;    
        toLowercase(&name);                
        if (inputuser == adminlist[i].username && inputname == name) {
            found = true;
            index = i;
            break;
        }
    }
        

    if(found){
        cout << "\nVerifikasi berhasil !!\n";
        getchar();
        
        cout << "Masukan Password baru\t\t: "; newPass = maskedInput();
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
        toLowercase(&inputuser);
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

void swap(NPWPTempt &a, NPWPTempt &b) {
    NPWPTempt temp = a;
    a = b;
    b = temp;
}

int partition(vector<NPWPTempt> &data, int low, int high, const string &key) {
    string pivot;
    if (key == "nik") pivot = data[high].NIK;
    else if (key == "npwp") pivot = data[high].NPWP;
    else pivot = data[high].Name;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        string current;
        if (key == "nik") current = data[j].NIK;
        else if (key == "npwp") current = data[j].NPWP;
        else current = data[j].Name;

        if (current <= pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

void quickSortNPWP(vector<NPWPTempt> &data, int low, int high, const string &key) {
    if (low < high) {
        int pi = partition(data, low, high, key);
        quickSortNPWP(data, low, pi - 1, key);
        quickSortNPWP(data, pi + 1, high, key);
    }
}




void lihatsemuadata(vector<NPWPTempt> &data) {
    int perPage = 10;
    clearScreen();
    for (int i = 0; i < data.size(); ++i) {
        cout << "No. " << i + 1 << "\n";
        cout << "Nama           : " << data[i].Name << "\n";
        cout << "NPWP           : " << data[i].NPWP << "\n";
        cout << "NIK            : " << data[i].NIK << "\n";
        cout << "Gender         : " << (data[i].gender == 'L' ? "Laki-laki" : "Perempuan") << "\n";
        cout << "Telepon        : " << data[i].noTelepon << "\n";
        cout << "PTKP           : " << data[i].PTKP << "\n";
        cout << "Status Kawin   : " << (data[i].statusKawin ? "aktif" : "tidak aktif") << "\n";
        cout << "Wajib Pajak    : " << (data[i].statusWajibPajak ? "aktif" : "tidak aktif") << "\n";
        cout << "Alamat         : " << data[i].alamat << "\n";
        cout << string(30, '-') << "\n";

        if ((i + 1) % perPage == 0 && i + 1 != data.size()) {
            char lanjut;
            cout << "Tampilkan data berikutnya? (y/n): ";
            cin >> lanjut;
            cin.ignore();
            if (lanjut != 'y' && lanjut != 'Y') {
                cout << "Pengambilan data dihentikan.\n";
                break;
            }
        }
        else if(i == data.size()){
            system("pause");
        }
    }
}

void urutkanDanTampilkan() {
    vector<NPWPTempt> data = pullNPWP();

    cout << "Urutkan berdasarkan:\n";
    cout << "1. Nama\n2. NPWP\n3. NIK\nPilihan: ";
    int pilihan;
    cin >> pilihan;

    string key = (pilihan == 1) ? "nama" : (pilihan == 2) ? "npwp" : "nik";

    quickSortNPWP(data, 0, data.size() - 1, key);

    lihatsemuadata(data);  // tampilkan data yang sudah diurutkan
}


void adminMenu() {
    char choice;
    do {
        clearScreen();
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Akun admin Menu" << endl;
        cout << "2. Lihat semua Data" << endl;
        cout << "3. Cari Data" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: "; cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1':
                AkunAdmin();
                break;
            case '2':
                urutkanDanTampilkan();
                break;
            case '3':
                caridata();
                break;
            case '0':
                adminMode = false;
                return;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (true);
}



int main() {
    srand(time(0)); // supaya rand() beda tiap jalan
    char pilihan;
    adminlist = loadDadmin();
    //#admin mode

    while(pilihan != '3'){
        clearScreen();
        cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;
        cout << "Pilih Menu:\n";
        cout << "1. Daftar atau Cek NPWP\n";
        cout << "2. Menu pajak\n";
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
                taxMenu();
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