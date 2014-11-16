//
//  prototype.h
//  2048_prototype
//
//  Created by SeconDatke on 14-9-28.
//  Copyright (c) 2014年 ISDC 2014. All rights reserved.
//

// known issues:
//
//		* not working perfectly on Retina display
//		* need a function to destroy p_font

#ifndef _048_prototype_prototype_h
#define _048_prototype_prototype_h

#ifdef __cplusplus

extern "C" {

#endif

	#define PROTOTYPE_dllexport __declspec(dllexport)
	
	// font
	//
	// if you want to display text with
	// p_graphic_draw_text in the window
	// you must load a font with p_text_load_font()
	// and set it in p_text_args
	// or just use p_set_window_default_font()
	struct p_font {
		void *font;
	};
	
	struct p_window_args {
		unsigned int width;
		unsigned int height;
		const char *title;
		p_font *default_font;
	};
	
	struct p_window {
		void *window;
	};
	
	// 0-255 or 0x00-0xFF, not float.
	struct p_color {
		unsigned char R, G, B;
		unsigned char alpha;
	};
	
	// the x & y is the coord of
	// topleft corner of rectangle
	struct p_rectangle_args {
		unsigned int width;
		unsigned int height;
		unsigned int x, y;
		p_color color;
	};
	
	enum p_event_type {
		EVENT_UNKNOWN,
		EVENT_CLOSE,
		EVENT_KEYUP,
	};
	
	//	field key_code is used in EVENT_KEYUP
	//	it will be set as the ASCII code of key
	struct p_event {
		p_event_type type;
		short key_code;
	};
	
	struct p_text_args {
		unsigned int x, y;
		unsigned short size;
		p_color color;
		p_font *font;
	};
	
	p_window * p_create_window(const p_window_args *args);
	
	void p_set_window_default_font(p_window *window, p_font *font);
	
	typedef void (*p_message_handler) (p_window *, const p_event *);
	
	// set the event handler for a window
	// use as the condition of event loop
	//		(returns 0 if window is closed)
	int p_handle_message(p_window *window, p_message_handler handler);
	
	//	p_create_window() -> loop(p_handle_message() -> p_graphic_clear() ->
	//		draw your stuff -> p_graphic_redraw()) -> p_destroy_window()
	void p_close_window(p_window *window);
	
	void p_destroy_window(p_window *window);
	
	void p_graphic_clear(p_window *window, const p_color *color);
	
	void p_graphic_redraw(p_window *window);
	
	void p_graphic_draw_rectangle(p_window *window, const p_rectangle_args *args);
	
	void p_graphic_draw_text(p_window *window, const char *text, const p_text_args *args);
	
	p_font *p_text_load_font(const char *filename);

#ifdef __cplusplus

}

#endif

#endif