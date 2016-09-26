#include <libconfig.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "libtwitcurl/twitcurl.h"

using namespace std;

class settings{
  
public:
  settings(){
    if(chdir("/home/rc/.config/ttwiti/") != 0){
      system("mkdir /home/rc/.config/ttwiti/");
      chdir("/home/rc/.config/ttwiti/");
    }
    prefs.open ("prefs", ios::out | ios::app | ios::in);    
  }

  ~settings(){
    prefs.close();
  }

  void addAccount(const char* pin){
    
  }

  int numberOfAccounts(){
    return 0;
  }

  void close(){
    prefs.close();
  }
  
private:
  ofstream prefs;
};
