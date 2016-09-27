#include <libconfig.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "settings.h"

using namespace std;


settings::settings(){
  string home = getenv("HOME");
  if(chdir((home + "/.config/ttwiti").c_str()) != 0){
    cout << "HOME:  " << (home + "/.config/ttwiti").c_str() << endl << endl << endl;
    system(("mkdir " + home + "/.config/ttwiti").c_str());
    chdir((home + "/.config/ttwiti").c_str());
  }
  ofstream prefs;
  prefs.open("prefs", ios::out | ios::in | ios::app);
  prefs.close();
}

void settings::addAccount(string  username, string token_key, string token_secret){
  ofstream prefs;
  prefs.open("prefs", ios::out | ios::in | ios::app);
  prefs << "<" << username << "><" << token_key << "><" << token_secret << ">" << endl;
  prefs.close();
}

bool settings::noAccounts(){
    ifstream prefs;
    prefs.open("prefs");
    int t = prefs.peek() == std::ifstream::traits_type::eof();
    prefs.close();
    return t;
  }

