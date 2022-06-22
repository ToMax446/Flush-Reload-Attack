#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <sys/time.h>

#define TIMEOUT 135


unsigned long getTime(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  unsigned long time_in_micros =   1000000 * tv.tv_sec + tv.tv_usec ;
  return time_in_micros;
}


#define CHAR_LIMIT 1000 //CHAR_LIMIT is set to 1000 to copy paper, but can be changed.

GtkTextBuffer *buffer = NULL;
int input_pos = 0;
int insertions_count = 0;
FILE* fd = NULL;

//generates a random character
char random_user_input(){
    srand ( time(NULL) );
    int lower = ' ';
    int upper = '~';
    int character = (rand() % (upper - lower + 1)) + lower;
    char new_input = character;
    return new_input;
}

//adds a randomly generated input to buffer (and therefore to the text view) at random timings.
static gboolean tick(gpointer pVoid) {
    if (input_pos == CHAR_LIMIT)
        return FALSE;  // stop timer.
    char input[] = "";
    char rand_input = random_user_input();
    strncat(input,  &rand_input, 1);
    if (buffer != NULL)
        gtk_text_buffer_insert_at_cursor (buffer, input, sizeof (input));
    input_pos++;
    srand(time(NULL));
    int interval = ((rand() & 60) + 1) * 10;
    g_timeout_add(interval, tick, NULL);
    return FALSE;
}



//saves timestamp when buffer is changed
static gboolean buffer_change_callback(void *x1, void *x2, gpointer data){
    fd = fopen("input.json", "a");
    fprintf(fd, "%ld, ", getTime());
    fclose(fd);
    insertions_count++;
}

static void activate (GtkApplication *app, gpointer user_data) {
    /* Declare variables */
    GtkWidget *window;
    GtkWidget *text_view;
    GtkWidget *scrolled_window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "TextView Target");
    gtk_window_set_default_size(GTK_WINDOW (window), 220, 200);
    /* The text buffer represents the text being edited */
    buffer = gtk_text_buffer_new (NULL);



    /* Text view is a widget in which can display the text buffer.
     * The line wrapping is set to break lines in between words.
     */
    text_view = gtk_text_view_new_with_buffer (buffer);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (text_view), GTK_WRAP_WORD);


  /* Create the scrolled window. Usually NULL is passed for both parameters so
     * that it creates the horizontal/vertical adjustments automatically. Setting
     * the scrollbar policy to automatic allows the scrollbars to only show up
     * when needed.
     */
 scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    /* The function directly below is used to add children to the scrolled window
     * with scrolling capabilities (e.g text_view), otherwise,
     * gtk_scrolled_window_add_with_viewport() would have been used
     */
 gtk_container_add (GTK_CONTAINER (scrolled_window),
                       text_view);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);

    gtk_container_add (GTK_CONTAINER (window), scrolled_window);

    g_signal_connect (buffer, "changed",
                      G_CALLBACK (buffer_change_callback), NULL);
    g_timeout_add(0, tick, NULL);


    gtk_widget_show_all (window);
}
static gboolean end(gpointer pVoid){
    exit(0);
}

int main (int argc, char *argv[]) {
    GtkApplication *app;
    int status;
    FILE* fd = fopen("input.json", "w");
    fprintf(fd, "{\"input time\": [");
    fclose(fd);
    app = gtk_application_new ("org.gtk.ff_target", G_APPLICATION_FLAGS_NONE);
    g_timeout_add_seconds(TIMEOUT, end, NULL);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}

