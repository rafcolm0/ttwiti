#include <libconfig.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class settings{
public:
  settings(){
    /*** TODO getlogin_r(char *buf, size_t bufsize) -> get usermane***/
    if(chdir("/home/rc/.config/ttwiti/") != 0){
      system("mkdir /home/rc/.config/ttwiti/");
      chdir("/home/rc/.config/ttwiti/");
    }
    ofstream prefs;
    prefs.open("prefs");
    prefs.close();
  }

  void addAccount(string  username, string token_key, string token_secret){
    ofstream prefs;
    prefs.open("prefs", ios::out | ios::in | ios::app);
    prefs << "<" << username << "><" << token_key << "><" << token_secret << ">" << endl;
    prefs.close();
  }

  bool noAccounts(){
    ifstream prefs;
    prefs.open("prefs");
    int t = prefs.peek() == std::ifstream::traits_type::eof();
    prefs.close();
    return t;
  }
};
