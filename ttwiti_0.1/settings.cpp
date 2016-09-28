#include <libconfig.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
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
  prefs.open("accounts", ios::out | ios::in | ios::app);
  prefs.close();
}

void settings::addAccount(string  username, string token_key, string token_secret){
  ofstream prefs;
  prefs.open("accounts", ios::out | ios::in | ios::app);
  prefs << username << endl << token_key << endl << token_secret << endl;
  prefs.close();
}

bool settings::noAccounts(){
    ifstream prefs;
    prefs.open("accounts");
    int t = prefs.peek() == std::ifstream::traits_type::eof();
    prefs.close();
    return t;
}


vector<string> settings::getInfoVector(){
  vector<string> v;
  ifstream prefs;
  prefs.open("accounts");
  std::string line;
  while(std::getline(prefs, line)){
    std::getline(prefs, line); //key
    v.push_back(line);
    std::getline(prefs, line); //secret
    v.push_back(line);
  }
  return v; 
}



