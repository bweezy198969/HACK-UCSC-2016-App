#include <pebble.h>
#include "windows/stats.h"

static Window *s_main_window;
static TextLayer *s_output_layer;

static ActionBarLayer *mood_select_bar;
static GBitmap *s_ellipsis_bitmap;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
	window_set_background_color(s_main_window, GColorRed);
	
	mood_select_bar = action_bar_layer_create();
	
	s_ellipsis_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ellipsis);
	action_bar_layer_set_icon_animated(mood_select_bar, BUTTON_ID_SELECT, s_ellipsis_bitmap, true);
	
	text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_background_color(s_output_layer, GColorClear);
	text_layer_set_text(s_output_layer, "THIS IS THE STATS");
	text_layer_set_text_alignment(s_output_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentLeft));
	layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
}

static void window_unload(Window *window) {
  gbitmap_destroy(s_ellipsis_bitmap);
	
  window_destroy(window);
  s_main_window = NULL;
}

void stats_window_push() {
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}