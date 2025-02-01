#include <gtk/gtk.h>
#include <fstream>
#include <iostream>
#include <sstream>

static GtkWidget *text_view;

// Callback function for the "Open" menu item
static void on_open_activate(GtkMenuItem *menuitem, gpointer user_data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(user_data),
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Open", GTK_RESPONSE_ACCEPT, nullptr);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        std::ifstream file(filename);

        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string file_contents = buffer.str();

            // Set the content of the text view with the file's content
            GtkTextBuffer *buffer_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            gtk_text_buffer_set_text(buffer_text, file_contents.c_str(), -1);
        }
        g_free(filename);
        gtk_widget_destroy(dialog);
    }
}

// Callback function for the "Save" menu item
static void on_save_activate(GtkMenuItem *menuitem, gpointer user_data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(user_data),
                                                    GTK_FILE_CHOOSER_ACTION_SAVE,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Save", GTK_RESPONSE_ACCEPT, nullptr);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        std::ofstream file(filename);

        if (file.is_open()) {
            GtkTextBuffer *buffer_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
            GtkTextIter start, end;
            gtk_text_buffer_get_bounds(buffer_text, &start, &end);
            gchar *text = gtk_text_buffer_get_text(buffer_text, &start, &end, FALSE);
            file << text;
            g_free(text);
        }
        g_free(filename);
        gtk_widget_destroy(dialog);
    }
}

// Set up the menu bar
static GtkWidget* create_menu(GtkWidget *window) {
    GtkWidget *menu_bar = gtk_menu_bar_new();
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("File");

    GtkWidget *open_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open_item, "activate", G_CALLBACK(on_open_activate), window);

    GtkWidget *save_item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(save_item, "activate", G_CALLBACK(on_save_activate), window);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);
    return menu_bar;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple IDE with GTK4");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Set up the text view (editor)
    text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    GtkWidget *scroll_window = gtk_scrolled_window_new();
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Create the menu bar
    GtkWidget *menu_bar = create_menu(window);

    // Set up the layout with a box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), scroll_window, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Connect the window's destroy signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start GTK main loop
    gtk_main();

    return 0;
}
