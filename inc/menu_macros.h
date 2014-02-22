#define START_MENU(name, config) static menu_list_t name = { \
         .configure_settings = config, .menu = {
#define END_MENU(name, menu_size, active_item) }, .size = menu_size, \
         .action_item_num = active_item };

#define SIMPLE_ITEM(id_val) { .id = id_val, .type = MENU_ITEM_CLICKABLE }

#define ACTION_ITEM(id_val, func, list) { .id = id_val, .type = \
         MENU_ITEM_CLICKABLE, .action = func, .data = (void *) list }
#define TEXT_ITEM(id_val) { .id = id_val, .type = MENU_ITEM_TEXT }
#define EDITABLE_ITEM(id_val, func, title, ent) { .id = id_val, \
         .type = MENU_ITEM_EDITABLE, .action = func, .get_title = title, \
         .data = (void *) ent }
