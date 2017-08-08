#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkBuilder *gtkBuilder;
	GtkWidget *window;
	GError     *error = NULL;
	gtk_init(&argc, &argv);
	    
	gtkBuilder = gtk_builder_new();
	if(!gtk_builder_add_from_file(gtkBuilder, "gui_config.glade", &error))
	{
		g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
	}
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "crc_main"));
	
	 /* Connect signals */
    gtk_builder_connect_signals( gtkBuilder, NULL );
	
	 /* Destroy builder, since we don't need it anymore */   
	g_object_unref(G_OBJECT(gtkBuilder));
	
	gtk_widget_show(window);
	gtk_main();
    
    return 0;
}