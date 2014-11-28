#Project 2048 Documentation#
####Demo 程序####

---

##源程序注释##

_main.cpp_

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
    
    // 事件处理函数
    void event_handler(p_window *window, const p_event *event) {
    	char *p = input_buf;
    	
    	// 根据事件类型决定如何处理事件
    	switch (event->type) {
    	    // 该函数需要处理关闭事件，否则窗口无法关闭
    		case EVENT_CLOSE:
    		    // 调用 p_close_window() 函数关闭窗口
    			p_close_window(window);
    			break;
    			
    		// 键盘事件
    		case EVENT_KEYUP:
    		       // 将当前按下的字符追加到 input_buf 的末尾
    			if (*p) while (*++p);
    			*p++ = event->key_code;    // 使用 event->key_code 获取当前按键的 ASCII 码
    			*p = '\0';
    			break;
    			
    		default:
    			break;
    	}
    }
    
    int main(int argc, const char * argv[]) {
    	
    	p_font *font_default = p_text_load_font("Ubuntu-Mono.ttf"); // 载入 Ubuntu Mono 字体
    	window_args.default_font = font_default; // 将载入的字体设置为窗口的默认字体
    	
    	p_window *window = p_create_window(&window_args); // 创建窗口
    	
    	while (p_handle_message(window, event_handler)) {
    		p_graphic_clear(window, &background_color); // 清屏，为下面绘制图形做准备
    		
    		p_graphic_draw_rectangle(window, &panel_args);
    		p_graphic_draw_rectangle(window, &panel_textbox_args);
    		
    		p_graphic_draw_text(window, "Enter some text: ", &text_args_message);
    		// 将 input_buf 中的内容 (用户键入的内容) 绘制到窗口中心
    		p_graphic_draw_text(window, input_buf, &text_args_input);
    		
    		p_graphic_redraw(window);    // 将缓冲区中的内容显示到屏幕上
    	}
    	// 当窗口退出时，p_handle_message() 返回 0，事件循环结束
    	    	
    	p_destroy_window(window);      // 程序退出前释放窗口所占内存
    	
        return 0;
    }

---
[SCU ISDC](http://www.scuisdc.com) 2014