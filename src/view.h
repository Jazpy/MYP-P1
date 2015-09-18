#ifndef VIEW_H
#define VIEW_H

/**
 * @file view.h
 *
 * @brief view handler
 * 
 * handles almost all GtkWidgets
 */


#include <gtk/gtk.h>

/**
 * @brief view handler struct
 * 
 * contains associated GtkWidgets
 */
struct view
{
	GtkWidget *window, *drawing_area;
	GtkWidget *button_box, *eq_box;
	GtkWidget *submit_button, *clear_button;
	GtkWidget *left_button, *right_button;	
	GtkWidget *top_button, *bot_button;	

	GtkWidget *eq_text;
};

/**
 * @brief initializes view struct
 * 
 * param v view to initialize
 */
void view_init(struct view *v);

#endif /* VIEW_H */
