#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <stdlib.h>

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

static void activate_action(GtkAction *action){
  const gchar *name = gtk_action_get_name (action);
  GtkWidget *dialog;
  switch (*name){
  case '0':
    GtkWidget *window;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
    const gboolean *edit;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Tweet away, ma' boy:");
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
    // /* Set the default buffer text. */ 
    //gtk_text_buffer_set_text (buffer, "Hello Text View!", -1);
    gtk_text_view_set_editable(text_view, TRUE);
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
    exit (EXIT_FAILURE);
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
  gtk_action_group_add_actions(action_group, entries, n_entries,
			       NULL);

  uim = gtk_ui_manager_new();
  gtk_ui_manager_insert_action_group(uim, action_group, 0);

  if (!gtk_ui_manager_add_ui_from_string(uim, ui_info, -1, &error)) {
    g_message("Failed to build menus: %s\n", error->message);
    g_error_free(error);
    error = NULL;
  }

  /* Indicator */
  indicator = app_indicator_new("example-simple-client",
				"go-jump",
				APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

  indicator_menu = gtk_ui_manager_get_widget(uim, "/ui/IndicatorPopup");

  app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
  app_indicator_set_attention_icon(indicator, "indicator-messages-new");

  app_indicator_set_menu(indicator, GTK_MENU(indicator_menu));

  gtk_main();

  return 0;
}
