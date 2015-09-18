#ifndef VIEW_H
#define VIEW_H

#include <gtk/gtk.h>

struct view
{
	GtkWidget *window;
	GtkWidget *button_box;
	GtkWidget *submit_button;
	GtkWidget *left_button, *right_button;	
	GtkWidget *top_button, *bot_button;	
};

void view_init(struct view *v);

#endif /* VIEW_H */
