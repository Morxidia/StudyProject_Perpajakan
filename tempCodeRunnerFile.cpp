bool LoginAdmin(){
    string tempUsername,tempPassword;
    clearScreen();
    cout << "====== LOGIN ADMIN ======" << endl;
    cout << "Username\t: "; cin >> tempUsername;
    cout << "Password\t: "; tempPassword = maskedInput();;

    for(int i = 0; i < 2; i++){
        if(tempUsername == adminlist[i].username && tempPassword == adminlist[i].password) {
            cout << "SELAMAT DATANG " << adminlist[i].name;
            adminMode = true;
            return adminMode;
        }
    }
    adminMode = false;
}
