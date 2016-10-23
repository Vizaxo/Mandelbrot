#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing(cairo_t *cr);

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event\n");

	return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data)
{
	    gtk_main_quit ();
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	do_drawing(cr);
	return FALSE;
}

static void do_drawing(cairo_t *cr)
{
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);
	/*cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40.0);*/

	cairo_move_to(cr, 10.0, 50.5);
	cairo_line_to(cr, 100.0, 50.5);
	cairo_stroke(cr);

	unsigned char *img = get_data(cr);

	printf("%s", img);
	
	//cairo_show_text(cr, "Hi");
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *darea;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);

	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL); 
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
