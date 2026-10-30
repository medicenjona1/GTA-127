#include <sdk_version.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>

// Definición del módulo SPRX
SYS_MODULE_INFO(GTAClient_PS3, 0, 1, 1);
SYS_MODULE_START(prx_start);
SYS_MODULE_STOP(prx_stop);

sys_ppu_thread_t g_thread_id = SYS_PPU_THREAD_ID_INVALID;

// Bucle principal del cliente
void main_thread(uint64_t arg) {
    // Esperar a que el juego cargue en memoria
    sys_timer_sleep(10);

    // Aquí van tus ganchos (hooks) y lógica de red para PS3
    while (true) {
        sys_timer_usleep(100000);
    }

    sys_ppu_thread_exit(0);
}

extern "C" int prx_start(size_t args, const void *argp) {
    // Crear el hilo del plugin
    sys_ppu_thread_create(&g_thread_id, main_thread, 0, 1000, 0x2000, SYS_PPU_THREAD_CREATE_JOINABLE, "GTAClientThread");
    return SYS_PRX_RES_STARTED;
}

extern "C" int prx_stop(size_t args, const void *argp) {
    if (g_thread_id != SYS_PPU_THREAD_ID_INVALID) {
        uint64_t exit_code;
        sys_ppu_thread_join(g_thread_id, &exit_code);
    }
    return SYS_PRX_RES_STOPPED;
}
