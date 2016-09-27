#include <libconfig.h>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class settings{
public:
  settings();
  void addAccount(string  username, string token_key, string token_secret);
  bool noAccounts();
};
