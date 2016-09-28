#ifndef _STRINGS_H_
#define _STRINGS_H_
#include <cstring>
using namespace std;
// **** DECLARATIONS:
extern const std::string ACCOUNT_ADDER_INSTRUCS;
extern const std::string ACCOUNT_ADDER_TITLE;
extern const std::string ACCOUNT_ADDER_SIGN_IN;
extern const std::string ACCOUNT_ADDER_REQ_PIN;
extern const std::string ACCOUNT_ADDER_PIN_LABEL;
extern const std::string ACCOUNT_ADDER_ACCT_NAME;
extern const std::string ENTRY_POST_TWEET;
extern const std::string ENTRY_VISIT_PROFILE;
extern const std::string ENTRY_VISIT_TIMELINE;
extern const std::string ENTRY_ADD_ACCOUNT;
extern const std::string ENTRY_EXIT;
extern const std::string TWEET_TITLE;
extern const std::string NOTIF_TWEET_SUCCESS;

// **** DEFINITIONS:
extern const std::string ACCOUNT_ADDER_INSTRUCS = "To add an account, log into your twitter account through the link opened in your browser,  and Copy and Paste the PIN generated by Twitter below.";
extern const std::string ACCOUNT_ADDER_TITLE = "Add a twitter account";
extern const std::string ACCOUNT_ADDER_SIGN_IN = "Sign in";
extern const std::string ACCOUNT_ADDER_REQ_PIN = "Request new pin";
extern const std::string ACCOUNT_ADDER_PIN_LABEL = "PIN#: ";
extern const std::string ACCOUNT_ADDER_ACCT_NAME = "Account name: ";
extern const std::string ENTRY_POST_TWEET = "Post a tweet";
extern const std::string ENTRY_VISIT_PROFILE = "Go to Profile";
extern const std::string ENTRY_VISIT_TIMELINE = "Go to Timeline";
extern const std::string ENTRY_MANAGE_ACCOUNTS = "Manage accounts";
extern const std::string ENTRY_QUIT = "Quit";
extern const std::string TWEET_TITLE = "Tweet away, my boy/girl";
extern const std::string NOTIF_TWEET_SUCCESS = "Tweet succesful!";
#endif
