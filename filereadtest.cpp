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
    NPWPTempt User;
    string line;
    ifstream myfile ("npwp.txt");

    if (myfile.is_open())
    {
    myfile  >> User.NPWP >> User.NIK >> User.Name
                    >> User.gender >> User.noTelepon >> User.statusKawin
                    >> User.tanggungan >> User.PTKP >> User.statusWajibPajak 
                    >> User.alamat;
                    myfile.close();
            }
            
    else cout << "Unable to open file"; 
            
    cout << User.NPWP << endl;
    return 0;
}