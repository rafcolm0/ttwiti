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
    prefs.open ("prefs", std::fstream::in | std::fstream::out | std::fstream::app);    
  }

  ~settings(){
    prefs.close();
  }

  void addAccount(string  username, string token_key, string token_secret){
    prefs << "<" << username << "><" << token_key << "><" << token_secret << ">" << endl;
  }

  bool noAccounts(){
    return prefs.peek() == std::ifstream::traits_type::eof();
  }

  void close(){
    prefs.close();
  }
  
private:
  fstream prefs;
  
};
