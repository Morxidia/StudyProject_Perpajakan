#include <iostream>

using namespace std;

#include <conio.h> // untuk getch()

// string getPassword() {
//     string password;
//     char ch;

//     while (true) {
//         ch = _getch(); 

//         if (ch == 13) break; // Enter
//         else if (ch == 8 && !password.empty()) { // Backspace
//             password.pop_back();
//             cout << "\b \b"; 
//         } else if (isprint(ch)) {
//             password.push_back(ch);
//             cout << '*'; 
//     }

//     return password ;
//     }
// }


int main(){
    string input;
    char ch;
        cout << "tekan apapun = ";
        ch = _getch();
        cout << ch;
        cout << "\nkamu menekan = " << ch;
}