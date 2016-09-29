#ifndef _TWITTER_MAN_H
#define _TWITTER_MAN_H
#include <string>
#include "libtwitcurl/twitcurl.h"
#include "settings.h"

using namespace std;

class twitter_man{
 public:
  twitter_man();
  bool addAccount(string pin_text, settings* sets);
  void requestPIN();
  bool postTweet(string text, string key, string secret);
  void visitProfile();


 private:
  twitCurl twitterObj;
};
#endif
