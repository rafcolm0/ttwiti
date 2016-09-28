#include <string>
#include <fstream>
#include <iostream>
#include "twitter_man.h"
#include "libtwitcurl/twitcurl.h"

using namespace std;

twitter_man::twitter_man(){
  std::string CONSUMER_KEY("L1BkxDo0Uqd6x4B6NS2MTfen8");
  std::string CONSUMER_SECRET("Q6UEjXmsWR8wwlYXxHiAOnoeUrustLtLogE4JscFkKvSjGNlkU");
  twitterObj.getOAuth().setConsumerKey(CONSUMER_KEY);
  twitterObj.getOAuth().setConsumerSecret(CONSUMER_SECRET);
}

bool twitter_man::addAccount(string pin_text, settings* sets){
  std::string myOAuthAccessTokenKey("");
  std::string myOAuthAccessTokenSecret("");
  twitterObj.getOAuth().setOAuthPin(pin_text);
  twitterObj.oAuthAccessToken();
  twitterObj.getOAuth().getOAuthTokenKey(myOAuthAccessTokenKey);
  twitterObj.getOAuth().getOAuthTokenSecret(myOAuthAccessTokenSecret);
  if(twitterObj.accountVerifyCredGet()){
    sets->addAccount(twitterObj.getTwitterUsername(), myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str());
    return true;
  }
  return false;   
}

void twitter_man::requestPIN(){
  std::string AUTH_URL;
  twitterObj.oAuthRequestToken(AUTH_URL);
  system(("xdg-open " + AUTH_URL).c_str());
}

bool twitter_man::postTweet(string text, string key, string secret){
  twitterObj.getOAuth().setOAuthTokenKey(key);
  twitterObj.getOAuth().setOAuthTokenSecret(secret);
  if(twitterObj.statusUpdate(text)){
    return true;
  }
  return false;
}

