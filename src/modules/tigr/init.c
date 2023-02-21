#include "binding.h"

symbol_definition_t symbols[] = {{"tigr.window", tigr_window},
                                 {"tigr.bitmap", tigr_bitmap},
                                 {"tigr.free", tigr_free},
                                 {"tigr.closed", tigr_closed},
                                 {"tigr.update", tigr_update},
                                 {"tigr.clear", tigr_clear},
                                 {"tigr.fill", tigr_fill},
                                 {"tigr.line", tigr_line},
                                 {"tigr.rect", tigr_rect},
                                 {"tigr.fillRect", tigr_fillrect},
                                 {"tigr.circle", tigr_circle},
                                 {"tigr.fillCircle", tigr_fillcircle},
                                 {"tigr.clip", tigr_clip},
                                 {"tigr.blit", tigr_blit},
                                 {"tigr.blitAlpha", tigr_blitalpha},
                                 {"tigr.color", tigr_color},
                                 {"tigr.print", tigr_print},
                                 {"tigr.mouse", tigr_mouse},
                                 {"tigr.keyDown", tigr_keydown},
                                 {"tigr.keyHeld", tigr_keyheld},
                                 NULL};

symbol_definition_t *
module_init (void)
{
    return symbols;
}
