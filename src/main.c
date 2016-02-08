#include <pebble.h>

static Window *s_main_window;
static Layer *s_main_window_layer;
static Layer *s_canvas_layer;
GPoint s_main_window_center;

char *digit = "111101111101111";

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {

  // set the fill colour
  graphics_context_set_fill_color(ctx, GColorWhite);

  // loop through the rows
  for (int i=0; i<5; i++){
    // loop through the columns
    for (int j=0; j<3; j++){
      
       // if the digit character is a 1 then draw a square
       if (digit[(i*3)+j] == '1'){
         graphics_fill_rect(ctx, GRect((j*15),(i*15), 14, 14), 0, GCornerNone);
       }   
      
    }
  }  
  
}




static void main_window_load(Window *window) {
  
  s_main_window_layer = window_get_root_layer(s_main_window);
  GRect window_bounds = layer_get_bounds(s_main_window_layer);
  s_main_window_center = grect_center_point(&window_bounds);
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(s_main_window_layer, s_canvas_layer);
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);    
}


static void main_window_unload(Window *window) {
  tick_timer_service_unsubscribe();
  layer_destroy(s_canvas_layer);
}


static void init(void) {
  s_main_window = window_create();
  
  window_set_background_color(s_main_window, GColorBlack);
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  window_stack_push(s_main_window, true);
  
}


static void deinit(void) {
  window_destroy(s_main_window);
  
}


int main(void) {
  
  init();
  app_event_loop();
  deinit();
  
}