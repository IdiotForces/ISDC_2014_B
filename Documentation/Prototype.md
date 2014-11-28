#Project 2048 Documentation#
####Prototype 框架参考####

---

##运作流程 + 函数文档##

1. 使用 `p_create_window()` 创建一个窗口供绘图。

    函数参数解释：
    
    * `const p_window_args *args`. 传入一个 `p_window_arg` 类型的指针，指定创建的窗口属性。
        
        `p_window_arg` 结构体的具体属性如下：
        
        * `unsigned int width`, `unsigned int height`. 指定所创建窗口的宽度和高度，单位为像素。
        
        * `const char *title`. 指定所创建窗口的标题。
        
        * `p_font *default_font`.指定窗口中文本的默认字体（主要是指 `p_graphic_draw_text()` 函数绘制出来的文字）。如果不设置这个的话，每次绘制文本都需要在 `p_text_args` 里手动设定字体。同时如果不指定默认字体，该项应为 `NULL`。
        
    函数返回一个 `p_window` 类型的指针，该指针代表所创建的窗口，`p_window` 结构体的具体细节不在需要掌握的范围内。
    
2. 进入窗口事件循环，使用 `p_handle_message()` 处理事件。

    函数参数解释：
    
    * `p_window *window`. 指定对应的窗口。
    
    * `p_message_handler handler` 指定一个消息处理函数，每当有事件发生时将会调用这个函数，其目的在于通知程序事件的发生，从而可以在函数中做出相应的操作。
    
        * `p_message_handler` 是一个函数指针，其声明如下：
        
                typedef void (*p_message_handler) (p_window *, const p_event *);
                
            当事件发生时，将会调用该参数指向的函数，其两个参数的意义分别为：
            
            * 第一个参数为一个 `p_window` 类型的指针，即该事件发生的窗口。
            
            * 第二个参数为一个 `p_event` 结构体类型的指针，该结构体中包含了需要处理的事件的类型、其他内容，其具体定义为：
            
                1. `p_event_type type`. 代表该事件的类型。`p_event_type` 为一个枚举类型，它有如下几个可能值：
                    * `EVENT_UNKNOWN`. 即该事件类型未知，一般不会出现。
                    
                    * `EVENT_CLOSE`. 用户向窗口发送了关闭消息（比如点击了关闭按钮）。该事件一般必须被处理，调用 `p_close_window()` 函数把窗口关闭，否则窗口将无法关闭（点击关闭按钮无反应）。
                    
                    * `EVENT_KEYUP`. 用户按下并松开了一个键，而具体是哪个键的信息则被放在 `key_code` 字段中。
                    
                2. `short key_code`. 该字段仅在 `type == EVENT_KEYUP` 时有意义，存储的是按下的键的 ASCII 码。
                
    当窗口存在时，该函数返回 1。当窗口被关闭后（通常是调用了 `p_close_window()` 关闭），该函数返回 0。因此一般使用 `p_handle_message()` 作为事件循环的条件部分，当窗口关闭后，事件循环自动结束。
    
* （事件循环内）使用 `p_graphic_clear()` 擦除上一帧绘制的画面。

    函数参数解释：
    
    * `p_window *window`. 指定要清除的窗口。
    
    * `const p_color *color`. 指定一个 `p_color` 结构，定义窗口的背景色。
    
        `p_color` 结构内有四个 `unsigned char` 字段，分别为 `R`, `G`, `B`, `alpha`。代表三原色和透明度比例。采用 [0, 255) 的范围。其中，alpha 通道为 255 时为完全不透明。
        
* （事件循环内）进行绘图操作。

* （事件循环内）使用 `p_graphic_redraw()` 函数将绘图结果显示出来。

    函数参数解释：
    
    * `p_window *window`. 指定对应的窗口。
    
* 调用 `p_close_window()` 函数，关闭窗口并退出事件循环。一般是由 `EVENT_CLOSE` 事件所触发。

    函数参数解释：
    
    * `p_window *window`. 指定要关闭的窗口。
    
* 调用 `p_destroy_window()` 函数，释放窗口的内存资源。

    函数参数解释：
    
    * `p_window *window`. 指定要释放的窗口。
    
---

##绘图功能##

本部分主要聚焦于上一部分的第 4 点，即绘图部分，绘图部分又主要由两个函数来完成，即 `p_graphic_draw_rectangle()` 和 `p_graphic_draw_text()`，分别用于绘制矩形和绘制文本。

* `p_graphic_draw_rectangle()` 函数。在指定窗口内根据指定参数绘制一个矩形。

    函数参数解释：
    
    * `p_window *window`. 指定要执行绘图操作的窗口。
    
    * `const p_rectangle_args *args` 传入一个 `p_rectangle_args` 类型的指针，指定绘制的文本属性。
        
        `p_rectangle_args` 结构体的具体属性如下：

        * `unsigned int width`, `unsigned int height`. 指定所绘制矩形的宽度和高度，单位为像素。
        
        * `unsigned int x`, `unsigned int y`. 指定所绘制矩形__左上角__在窗口中的位置，单位为像素。
        
        * `p_color color`. 指定所绘制矩形的颜色。

* `p_graphic_draw_text()` 函数。在指定窗口内根据指定参数绘制一段文字。

    函数参数解释：
    
    * `p_window *window`. 指定要执行绘图操作的窗口。
    
    * `const char *text`. 指定要绘制的文本内容。
    
    * `const p_text_args *args` 传入一个 `p_text_args` 类型的指针，指定绘制的文本属性。
        
        `p_text_args` 结构体的具体属性如下：
        
        * `unsigned int x`, `unsigned int y`. 指定所绘制文本__中心点__在窗口中的位置，单位为像素。
        
        * `unsigned short size`. 指定所绘制文本的字号大小。
        
        * `p_color color`. 指定所绘制文本的颜色。
        
        * `p_font *font`. 指定绘制文本所用的字体。若为 `NULL` 则将使用当前窗口的默认字体。

---

##字体问题##

由于后台实现的限制，在绘制文字时，必须手动载入其字体。因此需要预先准备一个字体文件供载入，而在运行程序时也需要相应的字体，因此为了示例程序能够正常运行，包里面附带了两个字体，一个是 Ubuntu Mono 字体，用于 Demo，另一个是思源黑体，用于 2048 的示例。

载入字体使用 `p_text_load_font()` 函数。

* 参数为 `const char *filename`，即字体文件的文件名。在这里要注意路径问题。

* 返回一个 `p_font` 指针，可用于在 `p_text_args` 中指定文本的字体，或者为窗口指定全局默认字体。

使用字体有以下几种方式：

1. 在程序的开始先载入字体，之后将返回的 `p_font` 指针作为 `p_window_args` 的 `default_font` 字段传给 `p_create_window()` 函数，创建窗口。即预设定窗口的默认字体。这也是 Demo 程序的处理方式。

2. 先创建窗口，再载入字体，之后使用 `p_set_window_default_font()` 函数设置窗口的默认字体，`p_set_window_default_font()` 函数只有两个参数，分别为目标窗口的 `p_window` 指针和源字体的 `p_font` 指针。

3. 在绘制文本时，手动在 `p_text_args` 中为文本指定字体。

注意如果未设定窗口的默认字体，则应在一开始就把用于创建窗口的  `p_window_args` 结构中的 `default_font` 设置为 `NULL`。

---
[SCU ISDC](http://www.scuisdc.com) 2014