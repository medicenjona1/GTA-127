#include <sdk_version.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Definición del módulo SPRX
SYS_MODULE_INFO(GTAClient_PS3, 0, 1, 1);
SYS_MODULE_START(prx_start);
SYS_MODULE_STOP(prx_stop);

// Configuración de tu servidor privado
#define SERVER_IP   "192.168.0.230"
#define SERVER_PORT 5000

sys_ppu_thread_t g_thread_id = SYS_PPU_THREAD_ID_INVALID;

// Puntero para la función hook
typedef int (*sys_net_connect_t)(int socket, const struct sockaddr *addr, socklen_t addrlen);
sys_net_connect_t sys_net_connect_original = nullptr;

// Intercepción de conexiones
int sys_net_connect_hook(int socket, const struct sockaddr *addr, socklen_t addrlen) {
    if (addr != nullptr && addr->sa_family == AF_INET) {
        struct sockaddr_in *addr_in = (struct sockaddr_in *)addr;
        uint16_t port = ntohs(addr_in->sin_port);

        // Redirigir peticiones a tu servidor
        if (port == 80 || port == 443 || port == 3074) {
            addr_in->sin_addr.s_addr = inet_addr(SERVER_IP);
            addr_in->sin_port = htons(SERVER_PORT);
        }
    }

    if (sys_net_connect_original != nullptr) {
        return sys_net_connect_original(socket, addr, addrlen);
    }
    return -1;
}

// Hilo principal del cliente
void main_thread(uint64_t arg) {
    // Espera inicial a que el juego cargue en RAM
    sleep(10);

    while (true) {
        usleep(100000);
    }

    sys_ppu_thread_exit(0);
}

extern "C" int prx_start(size_t args, const void *argp) {
    sys_ppu_thread_create(&g_thread_id, main_thread, 0, 1000, 0x2000, SYS_PPU_THREAD_CREATE_JOINABLE, "GTAClientThread");
    return SYS_PRX_RES_STARTED;
}

extern "C" int prx_stop(size_t args, const void *argp) {
    if (g_thread_id != SYS_PPU_THREAD_ID_INVALID) {
        uint64_t exit_code = 0;
        sys_ppu_thread_join(g_thread_id, &exit_code);
    }
    return SYS_PRX_RES_STOPPED;
}
