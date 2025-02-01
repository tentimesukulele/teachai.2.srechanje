#include <gtk/gtk.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1 MB limit for file loading

// Function prototypes
void *load_file_async(void *filename);
void create_text_editor(GtkWidget *window);
void on_compile_button_clicked(GtkWidget *widget, gpointer data);
void run_compiler(const char *filename);
void capture_and_display_output(const char *output);
void highlight_syntax_errors(const char *error_output);
void on_toggle_ide_buttons(GtkWidget *widget, gpointer data);
void add_line_numbers(GtkWidget *text_view);
void run_debugger(const char *filename);

// Global variables for widgets
static GtkWidget *text_view; // Text editor widget
static GtkWidget *output_text_view; // Output area for compiler/runtime errors
static GtkWidget *button_box; // Box to contain buttons (compile, open, etc.)
static const char *current_file = "example.c"; // Current file to work on

// Basic structure for file loading
void *load_file_async(void *filename) {
    FILE *file = fopen((char *)filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    char *content = malloc(MAX_FILE_SIZE);
    size_t size = fread(content, 1, MAX_FILE_SIZE - 1, file);
    content[size] = '\0';

    fclose(file);

    // Now set the text to TextView widget in the main thread
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, content, -1);

    free(content);
    return NULL;
}

// Create the text editor widget
void create_text_editor(GtkWidget *window) {
    // Create the TextView widget
    text_view = gtk_text_view_new();
    gtk_widget_set_size_request(text_view, 800, 600); // Size of the editor
    gtk_container_add(GTK_CONTAINER(window), text_view);

    // Add line numbers (for simple display of line numbers)
    add_line_numbers(text_view);
}

// Callback for opening a file
void on_open_file(GtkWidget *widget, gpointer data) {
    const char *filename = (const char *)data;

    // Create a thread to load the file asynchronously
    pthread_t load_thread;
    pthread_create(&load_thread, NULL, load_file_async, (void *)filename);
    pthread_detach(load_thread);
}

// Function to run the compiler (for C, C++, or Python)
void run_compiler(const char *filename) {
    // Clear the output text view before new output
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text_view));
    gtk_text_buffer_set_text(buffer, "", -1);  // Clear existing output

    // Create a pipe to capture stdout and stderr
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process: Run compiler or interpreter
        close(pipe_fd[0]); // Close the read end of the pipe

        // Redirect stdout and stderr to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        dup2(pipe_fd[1], STDERR_FILENO);

        const char *ext = strrchr(filename, '.');
        if (!ext) {
            return;
        }

        if (strcmp(ext, ".c") == 0 || strcmp(ext, ".cpp") == 0) {
            // Compile C/C++ code
            const char *compiler = (strcmp(ext, ".c") == 0) ? "gcc" : "g++";
            char cmd[512];
            snprintf(cmd, sizeof(cmd), "%s -o output %s", compiler, filename);
            system(cmd);

            // Execute the compiled program if compilation succeeds
            snprintf(cmd, sizeof(cmd), "./output");
            system(cmd);
        } else if (strcmp(ext, ".py") == 0) {
            // Run Python code
            char cmd[512];
            snprintf(cmd, sizeof(cmd), "python3 %s", filename);
            system(cmd);
        }

        close(pipe_fd[1]); // Close the write end of the pipe
        exit(0); // Exit child process after execution
    } else if (pid < 0) {
        perror("Fork failed");
    } else {
        // Parent process: Capture the output from the pipe
        close(pipe_fd[1]); // Close the write end of the pipe

        char output[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], output, sizeof(output) - 1)) > 0) {
            output[bytes_read] = '\0';
            capture_and_display_output(output);
        }

        close(pipe_fd[0]); // Close the read end of the pipe
        wait(NULL); // Wait for the child process to finish
    }
}

// Function to capture and display compiler/output errors
void capture_and_display_output(const char *output) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text_view));
    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(buffer, &end_iter);
    gtk_text_buffer_insert(buffer, &end_iter, output, -1);

    // Highlight errors in the output
    highlight_syntax_errors(output);
}

// Function to highlight syntax errors in the editor
void highlight_syntax_errors(const char *error_output) {
    // Simple error highlighting based on line numbers
    const char *line_start = error_output;
    while ((line_start = strstr(line_start, ":")) != NULL) {
        const char *line_end = strstr(line_start, ":");
        if (line_end) {
            // Parse line number (e.g., "filename.c: 12: error:")
            char line_number_str[16] = {0};
            strncpy(line_number_str, line_start + 1, line_end - line_start - 1);
            int line_number = atoi(line_number_str);

            // Here, you'd typically highlight the line with the error in the editor
            // But since GTK TextView doesn't have native syntax highlighting support,
            // you would need additional implementation to mark specific lines.
            line_start = line_end;
        }
    }
}

// Compile button callback
void on_compile_button_clicked(GtkWidget *widget, gpointer data) {
    const char *filename = (const char *)data;
    run_compiler(filename);
}

// Function to show IDE buttons when clicked
void on_toggle_ide_buttons(GtkWidget *widget, gpointer data) {
    gboolean visible = gtk_widget_get_visible(button_box);
    gtk_widget_set_visible(button_box, !visible); // Toggle visibility
}

// Add line numbers to the editor
void add_line_numbers(GtkWidget *text_view) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    gint line_number = 1;
    while (gtk_text_iter_forward_line(&iter)) {
        // Insert line numbers in the margin
        char line_number_str[10];
        snprintf(line_number_str, sizeof(line_number_str), "%d", line_number++);
    }
}

// Run debugger (basic example using GDB)
void run_debugger(const char *filename) {
    // Launch GDB for debugging
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: Run GDB
        execlp("gdb", "gdb", "--args", "./output", NULL);
        perror("Failed to start GDB");
        exit(1);
    } else if (pid < 0) {
        perror("Fork failed");
    } else {
        wait(NULL); // Wait for debugger to finish
    }
}

// Simple main window setup
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Custom C IDE");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create vertical box to arrange widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create toggle button for showing IDE buttons
    GtkWidget *toggle_button = gtk_button_new_with_label("Show IDE Tools");
    g_signal_connect(toggle_button, "clicked", G_CALLBACK(on_toggle_ide_buttons), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), toggle_button, FALSE, FALSE, 5);

    // Create box to hold IDE buttons
    button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Create the text editor widget
    create_text_editor(vbox);

    // Create compile button
    GtkWidget *compile_button = gtk_button_new_with_label("Compile");
    g_signal_connect(compile_button, "clicked", G_CALLBACK(on_compile_button_clicked), current_file);
    gtk_box_pack_start(GTK_BOX(button_box), compile_button, FALSE, FALSE, 5);

    // Create output text view (for compiler/runtime errors)
    output_text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_text_view), FALSE); // Make it non-editable
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(output_text_view), GTK_WRAP_WORD);
    GtkWidget *scroll_win = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_win), output_text_view);
    gtk_box_pack_start(GTK_BOX(button_box), scroll_win, TRUE, TRUE, 5);

    // Pack the button box below the editor
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 5);

    // Initially hide the IDE buttons
    gtk_widget_set_visible(button_box, FALSE);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
