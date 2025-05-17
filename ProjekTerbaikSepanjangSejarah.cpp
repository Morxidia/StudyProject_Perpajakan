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

struct TaxForm
{
    string NPWP;
    string NIK;
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
    string name;
    string username;
    string password;
}; Admintempt admin[2] = {
    {"RAIHAN","raihan", "admin123"}
};

bool adminMode = false;


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

// vector<TaxForm> pullTaxHistory(){
//     vector<TaxForm> TempData;
//     ifstream file("./Data/TaxPaymentHistory.txt.txt");
//     string line;

//     if (file.is_open()) {
//         int indx = 0;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string field;
//             int fieldNo = 1;
//             NPWPTempt Temp;

//             //getting the string until ','
//             while (getline(ss, field, ',')) {
//                 switch (fieldNo) {
//                     case 1: Temp.NPWP = field; break;
//                 }
//                 fieldNo++;
//             }
//             indx++;
//             TempData.push_back(Temp);
//         }
//         file.close();
//     } else {
//         cout << "Gagal membuka file.\n";
//         return TempData;
//     }
    
//     return TempData;
// }

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

    int nikminlen = 16;
    while(User.NIK.length() < nikminlen){
        cout << "Masukkan NIK: ";
        getline(cin, User.NIK);
        if((CheckNIK(User.NIK) != -1)){
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

    int telplen = 12;
    do
    {
        cout << "Masukkan No Telepon (12 digit)      : ";
        cin >> User.noTelepon;
        cin.ignore();
    } while (User.noTelepon.length() < telplen);
    

    char statuskawin;    
    do{
        cout << "Kawin(K) / Lajang(L): ";
        cin >> statuskawin;
        cin.ignore();
    }
    while((statuskawin != 'k' && statuskawin != 'l')&&(statuskawin != 'K' && statuskawin != 'L'));
    User.statusKawin = (statuskawin == 'k' || statuskawin == 'K')? true : false;

    int makstanggungan;
    cout << "Jumlah Tanggungan (maks 3): ";
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
    long int currentsalary;
    cout << "Masukan Gaji anda saat ini : ";
    cin >> currentsalary;
    cin.ignore();
    User.statusWajibPajak = (currentsalary > NilaiPTKP)? true: false;
    
    cout << "Alamat                      : ";
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



bool taxPaymentHistory(){

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
            userTaxForm.NPWP = "00.000.000.0-000.000";
        }

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

        addTaxPerc = 1.0;
    }


    cout << "Masukan Tahun pembayaran\t: ";
    getline(cin, userTaxForm.paymentYear);

    //check data if payment has already exist

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
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;

    unsigned long int ptkpValue = PTKPtoValue(UserNPWP.PTKP);//menarik nilai PTKP
    
    cout << "\nSilahkan masukan pemasukan dan pengeluaran anda dalam se-" << incomeTime << endl << endl;
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;
    userTaxForm.salary = numSeparatorInput("Masukan Gaji anda\t\t: ");
    unsigned long long int tempSalary = stoll(userTaxForm.salary);
    tempSalary = tempSalary * timesIncome;
    if(tempSalary < ptkpValue){
        clearScreen();
        cout << "gaji anda lebih kecil daripada nilai PTKP, anda tidak diwajibkan membayar pajak" << endl;
        cout << "silahkan menekan tombol apa saja untuk keluar..."; getchar();
        return;
    }
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
    
    userTaxForm.positionExpanse = numSeparatorInput("Masukan tunjangan jabatan anda\t: ");
    unsigned long long int tempPositionExpanse = stoll(userTaxForm.positionExpanse);
    tempPositionExpanse = tempPositionExpanse * timesIncome;
    userTaxForm.positionExpanse = to_string(tempPositionExpanse);
    
    userTaxForm.pension = numSeparatorInput("Masukan iuran pensiun anda\t: "); 
    unsigned long long int tempPension = stoll(userTaxForm.pension);
    tempPension = tempPension * timesIncome;
    userTaxForm.pension = to_string(tempPension);

    //gross income and net income calculation
    unsigned long long int totalExpanse = tempPositionExpanse + tempPension;
    unsigned long long int netIncome = totalIncome - totalExpanse;

    userTaxForm.netIncome = to_string(netIncome);

    cout << "Net income anda\t\t\t: " << userTaxForm.netIncome << endl;

    //nilai PTKP sudah di tarik
    cout << "PTKP anda\t\t\t: " << UserNPWP.PTKP << endl;
    cout << "Nilai PTKP anda\t\t\t: " << ptkpValue << endl;
    userTaxForm.PTKP = UserNPWP.PTKP;

    unsigned long long int taxableIncome = netIncome - ptkpValue;

    userTaxForm.taxIncome = to_string(taxableIncome);
    cout << "Pengahsilan wajib pajak anda\t: " << userTaxForm.taxIncome << endl;

    float taxperc = taxtoperc(taxableIncome);
    taxperc = taxperc * addTaxPerc;
    userTaxForm.percTax = to_string(taxperc);

    int percentage = 100;
    cout << "Persentase pajak anda\t\t: " << taxperc*percentage << "%" << endl;
    
    unsigned long long int taxOut = taxableIncome * taxperc;
    userTaxForm.taxTotal = to_string(taxOut);
    cout << "Total Pajak yang harus dibayar\t: " << userTaxForm.taxTotal << endl;
    cout << setfill('-') << setw(outputWidth) << "" << setfill(' ') << endl;

    ofstream file("./Data/TaxPaymentHistory.txt", ios::app);
    if(file.is_open()){
        file << userTaxForm.NPWP << ',' << userTaxForm.NIK << ',' << userTaxForm.gender << ','
             << userTaxForm.paymentYear << ',' << userTaxForm.salary << ',' << userTaxForm.additionalIncome << ','
             << userTaxForm.allowance << ',' << userTaxForm.honorium << ',' << userTaxForm.totalIncome << ','
             << userTaxForm.positionExpanse << ',' << userTaxForm.pension << ',' << userTaxForm.netIncome << ','
             << userTaxForm.PTKP << ',' << userTaxForm.taxIncome << ',' << userTaxForm.percTax << ',' << userTaxForm.totalIncome;
        file.close();
        cout << "\nData berhasil disimpan" << endl;
    }else {
        cout << "\nGagal menyimpan data.\n";
    }
    cout << "press any key to continue....";
    getchar();
}

bool LoginAdmin(){
    string tempUsername,tempPassword;
    clearScreen();
    cout << "====== LOGIN ADMIN ======" << endl;
    cout << "Username\t: "; cin >> tempUsername;
    cout << "Password\t: "; tempPassword = maskedInput();;

    for(int i = 0; i < 2; i++){
        if(tempUsername == admin[i].username && tempPassword == admin[i].password) {
            cout << "SELAMAT DATANG " << admin[i].name;
            adminMode = true;
            return adminMode;
        }
    }
    adminMode = false;
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

int main() {
    srand(time(0)); // supaya rand() beda tiap jalan
    char pilihan;
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
                LoginAdmin();
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
