//
//  main.cpp
//  Prototype_Demo
//
//  Created by SeconDatke on 14-11-15.
//  Copyright (c) 2014年 ISDC 2014. All rights reserved.
//

#include <string.h>

#include <Prototype/Prototype.h>

p_color background_color = { 0, 0, 0, 0 };
p_color text_color = { 255, 255, 255, 255 };
p_color panel_color = { 128, 128, 128, 255 };
p_color textbox_color = { 96, 96, 96, 255 };

#define FORM_WIDTH 800
#define FORM_HEGIHT 600
p_window_args window_args = { FORM_WIDTH, FORM_HEGIHT, "Prototype Demo - SCU ISDC 2014", NULL };

#define BORDER 64
p_rectangle_args panel_args = { FORM_WIDTH-BORDER, FORM_HEGIHT-BORDER, BORDER/2, BORDER/2, panel_color };

#define TEXTBOX_WIDTH 360
#define TEXTBOX_HEIGHT 64
p_rectangle_args panel_textbox_args = { TEXTBOX_WIDTH, TEXTBOX_HEIGHT, (FORM_WIDTH-TEXTBOX_WIDTH)/2, (FORM_HEGIHT-TEXTBOX_HEIGHT)/2, textbox_color };

#define TEXT_SIZE_MSG 32
#define TEXT_SIZE_INPUT 28
p_text_args text_args_message = { FORM_WIDTH/2-48, FORM_HEGIHT/2-64, TEXT_SIZE_MSG, text_color, NULL };
p_text_args text_args_input = { FORM_WIDTH/2, FORM_HEGIHT/2, TEXT_SIZE_INPUT, text_color, NULL };

#define INPUT_BUF_LEN 256
char input_buf[INPUT_BUF_LEN] = { '\0' };

void event_handler(p_window *window, const p_event *event) {
	char *p = input_buf;
	
	switch (event->type) {
		case EVENT_CLOSE:
			p_close_window(window);
			break;
			
		case EVENT_KEYUP:
			if (*p) while (*++p);
			*p++ = event->key_code;
			*p = '\0';
			break;
			
		default:
			break;
	}
}

int main(int argc, const char * argv[]) {
	
	p_font *font_default = p_text_load_font("Ubuntu-Mono.ttf");
	window_args.default_font = font_default;
	
	p_window *window = p_create_window(&window_args);
	
	while (p_handle_message(window, event_handler)) {
		p_graphic_clear(window, &background_color);
		
		p_graphic_draw_rectangle(window, &panel_args);
		p_graphic_draw_rectangle(window, &panel_textbox_args);
		
		p_graphic_draw_text(window, "Enter some text: ", &text_args_message);
		p_graphic_draw_text(window, input_buf, &text_args_input);
		
		p_graphic_redraw(window);
	}
	
	p_destroy_window(window);
	
    return 0;
}
