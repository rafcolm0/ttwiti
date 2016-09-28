#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class settings{
public:
  settings();
  void addAccount(string  username, string token_key, string token_secret);
  bool noAccounts();
  vector<string> getInfoVector();
};
#endif
