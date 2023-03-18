#include "binding.h"

symbol_definition_t symbols[] = {{"gfx.window", gfx_window},
                                 {"gfx.bitmap", gfx_bitmap},
                                 {"gfx.close", gfx_close},
                                 {"gfx.closed", gfx_closed},
                                 {"gfx.update", gfx_update},
                                 {"gfx.clear", gfx_clear},
                                 {"gfx.line", gfx_line},
                                 {"gfx.rect", gfx_rect},
                                 {"gfx.circle", gfx_circle},
                                 {"gfx.blit", gfx_blitalpha},
                                 {"gfx.color", gfx_color},
                                 {"gfx.print", gfx_print},
                                 {"gfx.mouse", gfx_mouse},
                                 {"gfx.keyDown", gfx_keydown},
                                 {"gfx.keyHeld", gfx_keyheld},
                                 {"gfx.sleep", gfx_sleep},
                                 NULL};

symbol_definition_t *
module_init (void)
{
    return symbols;
}
