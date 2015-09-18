#include "view.h"

void view_init(struct view *v)
{
	v -> window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(v -> window, 800, 600);

	gtk_window_set_title(GTK_WINDOW(v -> window), "GRAPHINATOR");
	gtk_window_set_default_size(GTK_WINDOW(v -> window), 600, 600);
	gtk_window_set_position(GTK_WINDOW(v -> window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(v -> window), 15);

	GtkAdjustment *adjustment_xneg, *adjustment_xpos;
	GtkAdjustment *adjustment_ypos, *adjustment_yneg;
	adjustment_xneg = gtk_adjustment_new(-10, -32000, 32000,
		0.001, 0.1, 0.0);
	adjustment_xpos = gtk_adjustment_new(10, -32000, 32000,
		0.001, 0.1, 0.0);
	adjustment_ypos = gtk_adjustment_new(10, -32000, 32000,
		0.001, 0.1, 0.0);
	adjustment_yneg = gtk_adjustment_new(-10, -32000, 32000,
		0.001, 0.1, 0.0);

	v -> submit_button = gtk_button_new_with_label("Update");
	gtk_widget_set_tooltip_text(v -> submit_button, "Equation to graph");
	v -> left_button = gtk_spin_button_new(adjustment_xneg, 0.001, 3);
	gtk_widget_set_tooltip_text(v -> left_button, "Lowest x value");
	v -> right_button = gtk_spin_button_new(adjustment_xpos, 0.001, 3);
	gtk_widget_set_tooltip_text(v -> right_button, "Highest x value");
	v -> top_button = gtk_spin_button_new(adjustment_ypos, 0.001, 3);
	gtk_widget_set_tooltip_text(v -> top_button, "Highest y value");
	v -> bot_button = gtk_spin_button_new(adjustment_yneg, 0.001, 3);
	gtk_widget_set_tooltip_text(v -> bot_button, "Lowest y value");

	v -> eq_box = gtk_hbox_new(0, 15);
	v -> eq_text = gtk_entry_new();


	gtk_box_pack_start(GTK_BOX(v -> eq_box), v -> submit_button,
		0, 0, 0);
	gtk_box_pack_start(GTK_BOX(v -> eq_box), v -> eq_text,
		0, 0, 0);

	v -> button_box = gtk_vbox_new(1, 15);
	gtk_box_pack_start(GTK_BOX(v -> button_box), v -> eq_box,
		0, 0, 0);
	gtk_box_pack_start(GTK_BOX(v -> button_box), v -> left_button,
		0, 0, 0);
	gtk_box_pack_start(GTK_BOX(v -> button_box), v -> right_button,
		0, 0, 0);
	gtk_box_pack_start(GTK_BOX(v -> button_box), v -> bot_button,
		0, 0, 0);
	gtk_box_pack_start(GTK_BOX(v -> button_box), v -> top_button,
		0, 0, 0);

	v -> drawing_area = gtk_drawing_area_new();

	GtkWidget *main_box = gtk_hbox_new(0, 15);
	gtk_box_pack_start(GTK_BOX(main_box), v -> button_box,
		0, 0, 0);
	gtk_box_pack_start(GTK_BOX(main_box), v -> drawing_area,
		1, 1, 0);

	gtk_container_add(GTK_CONTAINER(v -> window), main_box);
}
