/** author and twitter keys owner: rafcolm_
 ** twitter owner ID	1903897902
 ** consumer key:	L1BkxDo0Uqd6x4B6NS2MTfen8
 ** 
 ** description: Mini twitter client for quicker tweeting and notification access. Features no GUI. Only tweeting.
 ** 
 ** github: https://github.com/rafcolm0/ttwiti
 ** email: rafael.colon5@gmail.com
 ** linkedin: https://www.linkedin.com/in/rafaeljcolon
 ** External libraries used:
 **   -twitcurl (twitter API): https://github.com/swatkat/twitcurl 
 **/
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <libnotify/notify.h>
#include "settings.cpp"
#include "libtwitcurl/twitcurl.h"

using namespace std;

GtkWidget* indicator_menu;
GtkActionGroup* action_group;
GtkUIManager*   uim;
AppIndicator* indicator;
GError* error = NULL;
settings preferences;
twitCurl twitterObj;
std::string AUTH_URL;
std::string USER_PIN;
std::string CONSUMER_KEY("L1BkxDo0Uqd6x4B6NS2MTfen8");
std::string CONSUMER_SECRET("Q6UEjXmsWR8wwlYXxHiAOnoeUrustLtLogE4JscFkKvSjGNlkU");

static void activate_action (GtkAction *action);

static GtkActionEntry entries[] = {
  {"0",  "post-tweet",     "_Tweet",  "<alt>T",
   "Post a tweet",    G_CALLBACK(activate_action)},
  {"1", "visit-pofile",    "_Profile", "<altl>P",
   "Go to Profile",          G_CALLBACK(activate_action)},
  {"2", "visit-timeline",    "_Timeline", "<alt>T",
   "Go to Timeline",            G_CALLBACK(activate_action)},
  {"3", "settings",    "_Settings", "<alt>S",
   "Save file",            G_CALLBACK(activate_action)},
  {"4", "application-exit", "_Exit", "<alt>Q",
   "Exit the application", G_CALLBACK(gtk_main_quit)},
};
static guint n_entries = G_N_ELEMENTS(entries);

static const gchar *ui_info =
  "<ui>"
  "  <popup name='IndicatorPopup'>"
  "    <menuitem action='0' />" //Post a tweet
  "    <menuitem action='1' />" //Go to profile
  "    <menuitem action='2' />" //Go to timeline
  "    <menuitem action='3' />" //settings
  "    <menuitem action='4' />" //exit
  "  </popup>"
  "</ui>";

void terminate_prog(){
  exit(0);
}

void update_statusbar(GtkTextBuffer *buffer, GtkStatusbar  *statusbar) {
  gchar *msg;
  gtk_statusbar_pop(statusbar, 0); 
  msg = g_strdup_printf("Size: %ld", sizeof(buffer)/sizeof(char));
  gtk_statusbar_push(statusbar, 0, msg);
  g_free(msg);
}

void mark_set_callback(GtkTextBuffer *buffer, const GtkTextIter *new_location, GtkTextMark *mark, gpointer data) {
  update_statusbar(buffer, GTK_STATUSBAR(data));
}

void postTweet(GtkTextBuffer* buffer){
  GtkTextIter start_iter, end_iter;
  char *text;
  gtk_text_buffer_get_start_iter(buffer, &start_iter);
  gtk_text_buffer_get_end_iter(buffer, &end_iter);
  text = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE);
  notify_init("ttwiti");
  NotifyNotification* n = notify_notification_new ("Tweet posted succesfully!", text, 0);
  notify_notification_set_timeout(n, 10000); // 10 seconds
  if (!notify_notification_show(n, 0)) {
    std::cerr << "show has failed" << std::endl;
  }
}

static void activate_action(GtkAction *action){
  const gchar *name = gtk_action_get_name (action);
  GtkWidget *dialog;
  switch (*name){
  case '0':
    GtkWidget *window;
    GtkWidget *text_view;
    GtkWidget *vbox;
    GtkWidget *toolbar;
    GtkWidget *statusbar;
    GtkToolItem *tweet;
    GtkTextBuffer *buffer;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Tweet away, my boy/girl:");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 300);
    vbox = gtk_vbox_new(FALSE, 0);  //vbox def
    gtk_container_add(GTK_CONTAINER(window), vbox);
    /**
     ** TODO FIX statusbar
     **/
    toolbar = gtk_toolbar_new();  //toolbar def
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    tweet = gtk_tool_button_new_from_stock(GTK_STOCK_OK);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tweet, -1);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    text_view = gtk_text_view_new(); //text_view def
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_widget_grab_focus(text_view);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
    g_signal_connect_swapped(G_OBJECT(tweet), "clicked", G_CALLBACK(postTweet), buffer);
    g_signal_connect(buffer, "changed", G_CALLBACK(update_statusbar), statusbar);
    g_signal_connect_object(buffer, "mark_set", G_CALLBACK(mark_set_callback), statusbar, G_CONNECT_AFTER);
    // g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all (window);
    break;
  case '1':
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "You activated action: \"%s\"", name);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_widget_show(dialog);
    break;
  case '2':
    break;
  case '3':
    break;
  case '4':
    terminate_prog(); 
  }
}

void addAccount(GtkEntry* pin){
  const char* pin_text = gtk_entry_get_text(pin);
  if(pin_text != NULL){
    std::string myOAuthAccessTokenKey("");
    std::string myOAuthAccessTokenSecret("");
    twitterObj.getOAuth().setOAuthPin(pin_text);
    twitterObj.oAuthAccessToken();
    twitterObj.getOAuth().getOAuthTokenKey(myOAuthAccessTokenKey);
    twitterObj.getOAuth().getOAuthTokenSecret(myOAuthAccessTokenSecret);
    preferences.addAccount("user", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str());
    
  }
}

void requestPin(){
  twitterObj.oAuthRequestToken(AUTH_URL);
  system(("xdg-open " + AUTH_URL).c_str());
}

static void accountAdder(){
  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *pin_label;
  GtkWidget *pin;
  GtkWidget *toolbar;
  GtkToolItem *auth0;
  GtkWidget *hbox;
  GtkWidget *vbox;
  GtkWidget *halign;
  GtkWidget *balign;
  GtkWidget *signinBtn;
  GtkWidget *newpinBtn;
  GtkWidget *statusbar;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Add a twitter account");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, -1);
  toolbar = gtk_toolbar_new();  //toolbar def
  table = gtk_table_new(3, 2, FALSE);
  vbox = gtk_vbox_new(FALSE, 0);
  hbox = gtk_hbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  halign = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(halign), hbox);
  gtk_box_pack_start(GTK_BOX(vbox), halign, TRUE, TRUE, 5); 
  pin_label = gtk_label_new("PIN#: ");
  gtk_table_attach(GTK_TABLE(table), pin_label, 0, 1, 0, 1, (GTK_FILL), (GTK_FILL), 5, 5);
  pin = gtk_entry_new();
  auth0 = gtk_tool_button_new_from_stock(GTK_STOCK_OK);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), auth0, -1);
  signinBtn = gtk_button_new_with_label("Sign in");
  gtk_widget_set_size_request(signinBtn, 70, 30 );
  newpinBtn = gtk_button_new_with_label("Request new pin");
  gtk_widget_set_size_request(newpinBtn, -1, 30 );
  gtk_box_pack_start(GTK_BOX(hbox), signinBtn, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox), newpinBtn, FALSE, FALSE, 0);
  balign = gtk_alignment_new(0, 1, 1, 0);
  statusbar = gtk_statusbar_new();
  gtk_container_add(GTK_CONTAINER(balign), statusbar);
  gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), balign, FALSE, FALSE, 0);
  gtk_table_attach(GTK_TABLE(table), pin, 1, 2, 0, 1, (GTK_FILL), (GTK_FILL), 5, 5);
  g_signal_connect_swapped(G_OBJECT(signinBtn), "clicked", G_CALLBACK(addAccount), GTK_ENTRY(pin));
  g_signal_connect(G_OBJECT(newpinBtn), "clicked", G_CALLBACK(requestPin), NULL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(terminate_prog), NULL);
  gtk_widget_show_all(window);
}

int main(int argc, char **argv){
  gtk_init(&argc, &argv);
  twitterObj.getOAuth().setConsumerKey(CONSUMER_KEY);
  twitterObj.getOAuth().setConsumerSecret(CONSUMER_SECRET);
  if (preferences.noAccounts()){
    accountAdder();
  } else {
    
  }
  /* Menus */
  action_group = gtk_action_group_new("AppActions");
  gtk_action_group_add_actions(action_group, entries, n_entries, NULL);
  uim = gtk_ui_manager_new();
  gtk_ui_manager_insert_action_group(uim, action_group, 0);

  if (!gtk_ui_manager_add_ui_from_string(uim, ui_info, -1, &error)) {
    g_message("Failed to build menus: %s\n", error->message);
    g_error_free(error);
    error = NULL;
  }

  /* Indicator */
  indicator = app_indicator_new("example-simple-client", "go-jump", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

  indicator_menu = gtk_ui_manager_get_widget(uim, "/ui/IndicatorPopup");

  app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
  app_indicator_set_attention_icon(indicator, "indicator-messages-new");

  app_indicator_set_menu(indicator, GTK_MENU(indicator_menu));

  gtk_main();

  return 0;
}
