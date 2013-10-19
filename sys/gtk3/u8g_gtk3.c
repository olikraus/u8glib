/*
  http://developer.gnome.org/gtk3/3.0/gtk-getting-started.html

  http://developer.gnome.org/gtk3/stable/
  
  http://developer.gnome.org/gtk3/stable/GtkImage.html
  
  http://developer.gnome.org/gdk-pixbuf/unstable//gdk-pixbuf-The-GdkPixbuf-Structure.html#GdkPixbuf
  https://developer.gnome.org/gdk-pixbuf/stable/
  
  https://developer.gnome.org/gdk-pixbuf/stable/gdk-pixbuf-Image-Data-in-Memory.html#gdk-pixbuf-new-from-data

  Idea: Use "gdk_pixbuf_new_from_data" to create a GdkPixbuf. Then create the widget with "gtk_image_new_from_pixbuf"
  
*/

#include <gtk/gtk.h>

int
main (int   argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *v_box;
  GtkWidget *image;
  
  GtkWidget *button_box;
  GtkWidget *b1;
  GtkWidget *b2;
  GtkWidget *b3;
  GtkWidget *b4;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW (window), "U8glib");

  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  
  
  v_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);  
  gtk_container_add(GTK_CONTAINER(window), v_box);

  image = gtk_button_new_with_label ("test");
  gtk_box_pack_start(GTK_BOX(v_box), image, FALSE, FALSE, 0);

  button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);  
  g_object_set(G_OBJECT(button_box), "spacing" , 2, NULL);
  gtk_box_pack_start(GTK_BOX(v_box), button_box, FALSE, FALSE, 0);
    
  b1 = gtk_button_new_with_label ("b1");
  gtk_box_pack_start(GTK_BOX(button_box), b1, FALSE, FALSE, 0);
  b2 = gtk_button_new_with_label ("b2");
  gtk_box_pack_start(GTK_BOX(button_box), b2, FALSE, FALSE, 0);
  b3 = gtk_button_new_with_label ("b3");
  gtk_box_pack_start(GTK_BOX(button_box), b3, FALSE, FALSE, 0);
  b4 = gtk_button_new_with_label ("b4");
  gtk_box_pack_start(GTK_BOX(button_box), b4, FALSE, FALSE, 0);

  gtk_widget_show_all(window);

  gtk_main ();

  return 0;
}

