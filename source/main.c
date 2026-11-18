/*
 * Horizon PS3 - proof-of-life client
 * Target: PlayStation 3 / PSL1GHT / HEN 4.92
 *
 * This is a standalone homebrew test screen, NOT the Horizon game engine.
 * It intentionally does not download or install Minecraft files.
 */
#include <stdio.h>
#include <string.h>
#include <io/pad.h>
#include <sysutil/sysutil.h>
#include <tiny3d.h>
#include <libfont.h>

static volatile int running = 1;
static int selected = 0;
static int last_buttons = 0;
static const char *items[] = {
    "Iniciar teste grafico (ainda nao implementado)",
    "Estado do controle",
    "Sobre este prototipo",
    "Sair"
};

static void callback(uint64_t status, uint64_t param, void *userdata)
{
    (void)param; (void)userdata;
    if (status == SYSUTIL_EXIT_GAME) running = 0;
}

static void draw_text(float x, float y, float size, uint32_t color, const char *s)
{
    fontDraw(x, y, size, color, s, 0);
}

int main(int argc, char **argv)
{
    (void)argc; (void)argv;
    sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, callback, NULL);
    ioPadInit(7);

    /* Tiny3D provides the PS3 RSX-backed 2D drawing path. */
    tiny3d_Init(1024 * 1024);
    fontInit();

    while (running) {
        padInfo pad_info;
        padData pad_data;
        memset(&pad_info, 0, sizeof(pad_info));
        memset(&pad_data, 0, sizeof(pad_data));
        ioPadGetInfo(&pad_info);
        if (pad_info.status[0]) ioPadGetData(0, &pad_data);

        int buttons = pad_data.BTN_CROSS | pad_data.BTN_CIRCLE |
                      pad_data.BTN_UP | pad_data.BTN_DOWN;
        if ((pad_data.BTN_UP) && !(last_buttons & pad_data.BTN_UP))
            selected = (selected + 3) % 4;
        if ((pad_data.BTN_DOWN) && !(last_buttons & pad_data.BTN_DOWN))
            selected = (selected + 1) % 4;
        if ((pad_data.BTN_CROSS) && !(last_buttons & pad_data.BTN_CROSS)) {
            if (selected == 3) running = 0;
        }
        last_buttons = buttons;

        tiny3d_Clear(0x000000ff, TINY3D_CLEAR_ALL);
        tiny3d_Enter();
        tiny3d_Project2D();
        fontDrawStart();
        draw_text(42, 38, 1.35f, 0xffffffff, "HORIZON - PS3 TEST CLIENT");
        draw_text(42, 78, 0.85f, 0xffc060ff, "PROTOTIPO HOMEbrew | PS3 SLIM | HEN 4.92");
        draw_text(42, 125, 0.85f, 0xffffffff, "Menu de verificacao - DualShock 3");
        for (int i = 0; i < 4; ++i) {
            char line[160];
            snprintf(line, sizeof(line), "%s %s", i == selected ? ">" : " ", items[i]);
            draw_text(58, 175 + (float)i * 34.0f, 0.78f,
                      i == selected ? 0x70e0ffff : 0xd0d0d0ff, line);
        }
        draw_text(42, 335, 0.68f, 0xa0a0a0ff, "D-Pad: navegar   X: selecionar   O: voltar");
        draw_text(42, 372, 0.62f, 0xffb060ff, "Aviso: motor Horizon ainda nao foi portado para o PS3.");
        fontDrawFinish();
        tiny3d_Flip();
        sysUtilCheckCallback();
    }

    fontEnd();
    ioPadEnd();
    return 0;
}
