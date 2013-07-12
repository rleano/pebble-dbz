#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xBA, 0x22, 0x5B, 0xE1, 0x99, 0xCB, 0x40, 0x54, 0xB4, 0x01, 0x96, 0x70, 0x48, 0x57, 0xA2, 0x5A }
PBL_APP_INFO(MY_UUID,
             "PebbleZ", "ralphkui",
             1, 2, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

// Main window
Window window;
static const int height = 168;
static const int width = 144;

// Time attributes
TextLayer text_time_layer;
GFont time_font;
static char time_text[] = "00:00";
static int current_image = 0;

Layer background_layer;
Layer front_layer;
BmpContainer back;
BmpContainer goku;
BmpContainer gohan;
BmpContainer piccolo;
BmpContainer vegeta;

GRect front_rec;

void back_update_callback(Layer *me, GContext* ctx) {
	(void)me;
	(void)ctx;
	
	GRect destination = layer_get_frame(&back.layer.layer);
	
	destination.origin.x = 0;
	destination.origin.y = 50;
	
	graphics_draw_bitmap_in_rect(ctx, &back.bmp, destination);
}

void front_update_callback(Layer *me, GContext* ctx) {
	(void)me;
	(void)ctx;
	
	BmpContainer *bmp = &goku;
	
	if (current_image == 0) {
		bmp = &goku;
	}
	else if (current_image == 1) {
		bmp = &gohan;
	}
	else if (current_image == 2) {
		bmp = &vegeta;
	}
	else {
		bmp = &piccolo;
	}
	
	GRect destination = layer_get_frame(&bmp->layer.layer);
	
	destination.origin.x = 0;
	destination.origin.y = 0;
	
	graphics_draw_bitmap_in_rect(ctx, &bmp->bmp, destination);
}

// Initializes all
void handle_init(AppContextRef ctx) {
    (void)ctx;
	
	// Inits resources
	resource_init_current_app(&APP_RESOURCES);

    window_init(&window, "PebbleZ");
    window_stack_push(&window, true /* Animated */);
	window_set_background_color(&window, GColorBlack);
	
	layer_init(&background_layer, window.layer.frame);
	background_layer.update_proc = &back_update_callback;
	layer_add_child(&window.layer, &background_layer);
	
	//ValidColors
	// GColorBlack, GColorWhite, GColorClear
	
	// Initializes Time Layer
	time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_BIG_NOODLE_TITLING_55));
	text_layer_init(&text_time_layer, GRect(width/2 - 55, height/2 - 30, 110, 60));
	text_layer_set_text_color(&text_time_layer, GColorWhite);
	text_layer_set_background_color(&text_time_layer, GColorClear);
	text_layer_set_text_alignment(&text_time_layer, GTextAlignmentCenter);
	text_layer_set_font(&text_time_layer, time_font);
	
	// Set time
	PblTm currentTime;
	get_time(&currentTime);
	if(clock_is_24h_style()){
		string_format_time(time_text, sizeof(time_text), "%H:%M", &currentTime);
	} else {
		string_format_time(time_text, sizeof(time_text), "%I:%M", &currentTime);
	}
	// removes initial 0 in AM/PM mode
	//if (!clock_is_24h_style() && (time_text[0] == '0')) {
	//	memmove(time_text, &time_text[1], sizeof(time_text) - 1);
	//}
	
	text_layer_set_text(&text_time_layer, time_text);
	
	// Sets texttime layer on top of window layer
	layer_add_child(&background_layer, &text_time_layer.layer);
	
	// Creates and sets the front
	front_rec = GRect(0, 0, 144, 50);
	layer_init(&front_layer, front_rec);
	front_layer.update_proc = &front_update_callback;
	layer_add_child(&background_layer, &front_layer);
	
	bmp_init_container(RESOURCE_ID_IMAGE_BACK,  &back);
	bmp_init_container(RESOURCE_ID_IMAGE_GOKU, &goku);
	bmp_init_container(RESOURCE_ID_IMAGE_PICCOLO, &piccolo);
	bmp_init_container(RESOURCE_ID_IMAGE_GOHAN, &gohan);
	bmp_init_container(RESOURCE_ID_IMAGE_VEGETA, &vegeta);
	
	text_layer_set_text(&text_time_layer, time_text);
}

// Liberates resources
void handle_deinit(AppContextRef ctx) {
	(void)ctx;

	// Liberates images
	bmp_deinit_container(&back);
	bmp_deinit_container(&goku);
	bmp_deinit_container(&gohan);
	bmp_deinit_container(&piccolo);
	bmp_deinit_container(&vegeta);
	
	fonts_unload_custom_font(time_font);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
	(void)t;
	(void)ctx;
	
	// Updates time
	// section based on Simplicity by Pebble Team begins
	PblTm currentTime;
	get_time(&currentTime);
	if(clock_is_24h_style()){
		string_format_time(time_text, sizeof(time_text), "%H:%M", &currentTime);
	} else {
		string_format_time(time_text, sizeof(time_text), "%I:%M", &currentTime);
	}
	
	current_image = (current_image + 1) % 4;
	
	// removes initial 0 in AM/PM mode
	//if (!clock_is_24h_style() && (time_text[0] == '0')) {
	//	memmove(time_text, &time_text[1], sizeof(time_text) - 1);
	//}
	// section ends
	
	text_layer_set_text(&text_time_layer, time_text);
}


void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		// Initializer method
		.init_handler = &handle_init,
		// Exit method
		.deinit_handler = &handle_deinit,
		// Minute method, called every MINUTE_UNIT, and called handle_menu_tick
		.tick_info = {
			.tick_handler = &handle_minute_tick,
			.tick_units = MINUTE_UNIT
		}
	};
	app_event_loop(params, &handlers);
}
