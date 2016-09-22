#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <stdlib.h>
#include <cstdlib>

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


void update_statusbar(GtkTextBuffer *buffer, GtkStatusbar  *statusbar) {
  gchar *msg;
  gint row, col;
  GtkTextIter iter; 
  gtk_statusbar_pop(statusbar, 0); 
  gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));
  row = gtk_text_iter_get_line(&iter);
  col = gtk_text_iter_get_line_offset(&iter);
  msg = g_strdup_printf("Col: %d Ln: %d", col+1, row+1);
  gtk_statusbar_push(statusbar, 0, msg);
  g_free(msg);
}

void mark_set_callback(GtkTextBuffer *buffer, const GtkTextIter *new_location, GtkTextMark *mark, gpointer data) {
  update_statusbar(buffer, GTK_STATUSBAR(data));
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
    GtkWidget *view;
    GtkWidget *statusbar;
    GtkToolItem *term;
    GtkTextBuffer *buffer;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Tweet away, my boy/girl:");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 300);
    vbox = gtk_vbox_new(FALSE, 0);  //vbox def
    gtk_container_add(GTK_CONTAINER(window), vbox);
    toolbar = gtk_toolbar_new();  //toolbar def
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    term = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), term, -1);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);
    text_view = gtk_text_view_new(); //text_view def
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_widget_grab_focus(text_view);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(term), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(buffer, "changed", G_CALLBACK(update_statusbar), statusbar);
    g_signal_connect_object(buffer, "mark_set", G_CALLBACK(mark_set_callback), statusbar, G_CONNECT_SWAPPED);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
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
    exit(0);
  }
}

int main(int argc, char **argv){
  GtkWidget*      indicator_menu;
  GtkActionGroup* action_group;
  GtkUIManager*   uim;
  AppIndicator* indicator;
  GError* error = NULL;

  gtk_init(&argc, &argv);

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
