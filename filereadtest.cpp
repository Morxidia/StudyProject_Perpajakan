#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct NPWPTempt {
    char NPWP[21];//1 more bit for null terminator 
    char NIK[17];
    string Name;
    char gender;
    char noTelepon[13];
    bool statusKawin;
    int tanggungan;
    string PTKP;
    bool statusWajibPajak;
    string alamat;
};

main(){
    system("cls");
    ifstream file("npwp.txt");
    string line;

    cout << (true)? "aktif" : "tidak aktif" << endl;
}