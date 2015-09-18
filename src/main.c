#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"
#include "view.h"
#include "grammar_checker.h"
#include "linked_list.h"
#include "binary_tree.h"
#include "shunting_yard.h"

static struct tree_node *main_tree = 0;
static GtkWidget *main_draw = 0;
static GtkWidget *main_window = 0;
static GdkPixmap *pixmap = 0;
static float leftx, rightx, topy, boty;
static int to_clear;

void clear()
{
	gdk_draw_rectangle(pixmap, main_draw -> style -> white_gc,
		TRUE, 0, 0, main_draw -> allocation.width,
		main_draw -> allocation.height);

	gtk_widget_queue_draw(main_draw);
}

struct tree_result get_tree_value(float xval)
{
	return evaluate_tree(main_tree, xval);
}

void update_draw()
{
	int did_draw = 0;
	if(to_clear)
	{
		clear();
		to_clear = 0;
	}

	int width = main_draw -> allocation.width;
	int height = main_draw -> allocation.height;

	float range = rightx - leftx;
	float step = range / width;
	float yscale = height / (topy - boty);
	float xppu = width / range;
	
	gdk_draw_line(pixmap, main_draw -> style -> black_gc,
		0, yscale * (topy),
		width, yscale * (topy));

	gdk_draw_line(pixmap, main_draw -> style -> black_gc,
		xppu * (range - rightx), 0,
		xppu * (range - rightx), height);

	struct tree_result result;

	int prev_x, prev_y; 

	for(int i = 0; i != width; ++i)
	{
		result = get_tree_value(leftx + i * step);

		if(strcmp(result.str, "s") != 0)
			continue;

		int y = height / 2 - (result.val * yscale);

		if(did_draw && abs(y - prev_y) < height)
		{
			gdk_draw_line(pixmap, main_draw -> style -> black_gc,
				prev_x, prev_y, i, y);

			prev_x = i;
			prev_y = y;
		} else {
			gdk_draw_point(pixmap, main_draw -> style -> black_gc,
				i, y);

			prev_x = i;
			prev_y = y;
		}

		did_draw = 1;
	}

	if(!did_draw)
	{
		GtkWidget *dialog;
  		dialog = gtk_message_dialog_new(NULL,
            		GTK_DIALOG_DESTROY_WITH_PARENT,
            		GTK_MESSAGE_ERROR,
            		GTK_BUTTONS_OK,
            		"%s", result.str);
  		gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);

		return ;
	}

	gtk_widget_queue_draw(main_draw);
}

void sub_button_clicked(GtkWidget *widget, GtkWidget *text_box)
{
	char *string = gtk_entry_get_text(GTK_ENTRY(text_box));
	
	//remove whitespace
	char* i = string;
  	char* j = string;
  	while(*j != '\0')
  	{
    		*i = *j++;

    		if(!isspace(*i))
      			i++;
  	}

  	*i = 0;
	
	if(strcmp(string, "") == 0)
	{
		GtkWidget *dialog;
  		dialog = gtk_message_dialog_new(NULL,
            		GTK_DIALOG_DESTROY_WITH_PARENT,
            		GTK_MESSAGE_ERROR,
            		GTK_BUTTONS_OK,
            		"empty string");
  		gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);

		return;
	}

	//TOKENIZAN
	int index = 0, prev_token_id = 0;
	struct node *token_head;
	struct node *conductor;
	token_head = malloc(sizeof(struct node));
	token_head -> next = 0;
	conductor = token_head;

	while(string[index] != '\0')
	{
		conductor -> t = get_next_token(string, &index,
			&prev_token_id);
	
		if(string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	//ANALYZAN
	char *result = analyze_linked_list(token_head);
	
	if(strcmp(result, "s") != 0)
	{
		GtkWidget *dialog;
  		dialog = gtk_message_dialog_new(NULL,
            		GTK_DIALOG_DESTROY_WITH_PARENT,
            		GTK_MESSAGE_ERROR,
            		GTK_BUTTONS_OK,
            		"%s", result);
  		gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);

  		free_list(token_head);

		return;
	}

    	struct node *parsed;
	parsed = parse_linked_list(token_head);

	//TREE GENERATAN
	struct tree_node *tree = make_tree(parsed);
	
	if(tree == 0)
	{
		GtkWidget *dialog;
  		dialog = gtk_message_dialog_new(NULL,
            		GTK_DIALOG_DESTROY_WITH_PARENT,
            		GTK_MESSAGE_ERROR,
            		GTK_BUTTONS_OK,
            		"error generating tree");
  		gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  		gtk_dialog_run(GTK_DIALOG(dialog));
  		gtk_widget_destroy(dialog);

		free_list(token_head);
		free_list(parsed);
		free_tree(tree);

		return;
	}

	main_tree = tree;

	//MEMORY FREEAN
	free_list(token_head);
	free_list(parsed);

	update_draw();
}

static gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event)
{
	if(pixmap)
		g_object_unref(pixmap);

	pixmap = gdk_pixmap_new(widget -> window,
		widget -> allocation.width,
		widget -> allocation.height, -1);

	gdk_draw_rectangle(pixmap, widget -> style -> white_gc,
		TRUE, 0, 0, widget -> allocation.width,
		widget -> allocation.height);

	return TRUE;
}

static gboolean expose_event(GtkWidget *widget, GdkEventExpose *event)
{
	gdk_draw_drawable(widget -> window,
		widget -> style -> fg_gc[gtk_widget_get_state(widget)],
		pixmap, event -> area.x, event -> area.y,
		event -> area.x, event -> area.y,
		event -> area.width, event -> area.height);

	return FALSE;
}

void clear_button_clicked(GtkWidget *widget, gpointer data)
{
	clear();
}

void left_button_clicked(GtkSpinButton *widget, gpointer data)
{
	to_clear = 1;
	leftx = gtk_spin_button_get_value(widget);
}

void right_button_clicked(GtkSpinButton *widget, gpointer data)
{
	to_clear = 1;
	rightx = gtk_spin_button_get_value(widget);
}

void top_button_clicked(GtkSpinButton *widget, gpointer data)
{
	to_clear = 1;
	topy = gtk_spin_button_get_value(widget);
}

void bot_button_clicked(GtkSpinButton *widget, gpointer data)
{
	to_clear = 1;
	boty = gtk_spin_button_get_value(widget);
}

int main(int argc, char *argv[])
{
	leftx = boty = -10.0f;
	rightx = topy = 10.0f;
	//DISPLAYAN
	gtk_init(&argc, &argv);

	to_clear = 0;
	struct view v;
	view_init(&v);
	main_draw = v.drawing_area;
	main_window = v.window;
	gtk_widget_realize(main_draw);

	g_signal_connect(v.window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(v.submit_button, "clicked", 
      		G_CALLBACK(sub_button_clicked),
		GTK_ENTRY(v.eq_text));
	g_signal_connect(v.clear_button, "clicked", 
      		G_CALLBACK(clear_button_clicked), NULL);
	g_signal_connect(main_draw, "configure-event",
		G_CALLBACK(configure_event), NULL); 
	g_signal_connect(main_draw, "expose-event",
		G_CALLBACK(expose_event), NULL); 
	g_signal_connect(v.left_button, "value-changed", 
      		G_CALLBACK(left_button_clicked), NULL); 
	g_signal_connect(v.right_button, "value-changed", 
      		G_CALLBACK(right_button_clicked), NULL); 
	g_signal_connect(v.top_button, "value-changed", 
      		G_CALLBACK(top_button_clicked), NULL); 
	g_signal_connect(v.bot_button, "value-changed", 
      		G_CALLBACK(bot_button_clicked), NULL); 

	gtk_widget_show_all(main_window);

	gtk_main();

	free_tree(main_tree);
	
	return 0;
}
