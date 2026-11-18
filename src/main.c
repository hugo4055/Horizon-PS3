/*
 * Horizon PS3 - cliente de teste inicial
 * Plataforma: PS3 (PSL1GHT)
 *
 * Esta etapa apenas valida a inicializacao do homebrew e mostra uma
 * mensagem no PS3. Ainda nao implementa o motor Horizon/Minecraft.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/process.h>
#include <sysutil/sysutil.h>
#include <sysutil/msg.h>

static volatile int running = 1;

static void on_exit(void)
{
    running = 0;
}

static void on_dialog_close(int button, void *userdata)
{
    (void)button;
    (void)userdata;
    running = 0;
}

int main(void)
{
    cellSysutilRegisterCallback(0, (void (*)(uint64_t, void *))on_exit, NULL);

    cellMsgDialogOpen2(
        CELL_MSGDIALOG_TYPE_DIALOG_TYPE_OK,
        "Horizon PS3 Test Client\n\n"
        "Homebrew iniciado com sucesso!\n"
        "PS3 Slim / HEN 4.92\n\n"
        "Esta e apenas a tela inicial de teste.\n"
        "O motor Minecraft ainda sera portado.",
        on_dialog_close,
        NULL,
        NULL
    );

    while (running) {
        cellSysutilCheckCallback();
        usleep(100000);
    }

    cellSysutilUnregisterCallback(0);
    return 0;
}
