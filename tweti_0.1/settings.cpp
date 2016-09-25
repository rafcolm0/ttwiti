#include <libconfig.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
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

  int numberOfAccounts(){
    return 0;
  }
private:
  ofstream prefs;
};
