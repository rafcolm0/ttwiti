#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>

static void activate_action (GtkAction *action);

static GtkActionEntry entries[] = {
    {"Post a tweet",  "post-tweet",     "_Tweet",  "<control>N",
        "Post a tweet",    G_CALLBACK(activate_action)},
    {"Go to profile", "visit-pofile",    "_Profile", "<control>O",
        "Open a file",          G_CALLBACK(activate_action)},
    {"Go to timeline", "visit-timeline",    "_Timeline", "<control>S",
        "Save file",            G_CALLBACK(activate_action)},
    {"Exit", "application-exit", "_Exit", "<control>Q",
        "Exit the application", G_CALLBACK(gtk_main_quit)},
};
static guint n_entries = G_N_ELEMENTS(entries);

static const gchar *ui_info =
"<ui>"
"  <popup name='IndicatorPopup'>"
"    <menuitem action='Post a tweet' />"
"    <menuitem action='Go to profile' />"
"    <menuitem action='Go to timeline' />"
"    <menuitem action='Exit' />"
"  </popup>"
"</ui>";

static void activate_action(GtkAction *action)
{
    const gchar *name = gtk_action_get_name (action);
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_CLOSE,
                                    "You activated action: \"%s\"",
                                    name);

    g_signal_connect(dialog, "response", 
                     G_CALLBACK(gtk_widget_destroy), NULL);

    gtk_widget_show(dialog);
}

int main(int argc, char **argv)
{
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
