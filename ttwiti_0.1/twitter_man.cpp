#include <string>
#include <fstream>
#include <iostream>
#include "twitter_man.h"
#include "libtwitcurl/twitcurl.h"

using namespace std;

twitter_man::twitter_man(){
  std::string CONSUMER_KEY("bzBVA1VcS9Ca7D7l3wTyBzNCh");
  std::string CONSUMER_SECRET("6wgGa170G7wKJa7gTzespKGXPCcPJEiG61QT6311Bi0VlTPlwj");
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
  string replyMsg = "";
  if(twitterObj.statusUpdate(text)){
    twitterObj.getLastWebResponse( replyMsg );
    //cout << "\ntwitCurl::statusUpdate web response:\n" << replyMsg.c_str() << endl ;
    return true;
  }
  twitterObj.getLastCurlError( replyMsg );
  //cout << "\ntwitCurl::statusUpdate web response:\n" << replyMsg.c_str() << endl ;
  return false;
}

void twitter_man::visitProfile(){  //NOT WORKING!
  string link = "";
  string replyMsg = "";
  if(twitterObj.timelinePublicGet()){
      cout << "OK LINK: " << link << endl;
      twitterObj.getLastWebResponse( replyMsg );
      cout << "OK M: " << replyMsg << endl;
  } else {
    twitterObj.getLastCurlError( replyMsg );
    cout << "FAIL M: " << replyMsg << endl;
  }  
}

