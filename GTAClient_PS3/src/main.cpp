#include <psl1ght/types.h>
#include <sys/prx.h>
#include <sys/thread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// Información del módulo SPRX
SYS_MODULE_INFO(GTAClient_PS3, 0, 1, 1);
SYS_MODULE_START(prx_start);
SYS_MODULE_STOP(prx_stop);

// Servidor objetivo
#define SERVER_IP   "192.168.0.230"
#define SERVER_PORT 5000

sys_ppu_thread_t g_thread_id = 0;

// Puntero para la función hook
typedef int (*sys_net_connect_t)(int socket, const struct sockaddr *addr, socklen_t addrlen);
sys_net_connect_t sys_net_connect_original = nullptr;

// Intercepción de conexiones
int sys_net_connect_hook(int socket, const struct sockaddr *addr, socklen_t addrlen) {
    if (addr != nullptr && addr->sa_family == AF_INET) {
        struct sockaddr_in *addr_in = (struct sockaddr_in *)addr;
        uint16_t port = ntohs(addr_in->sin_port);

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

// Hilo principal
void main_thread(void* arg) {
    sleep(10);

    while (1) {
        usleep(100000);
    }

    sysThreadExit(0);
}

extern "C" int prx_start(size_t args, const void *argp) {
    sysThreadCreate(&g_thread_id, main_thread, NULL, 1000, 0x2000, THREAD_JOINABLE, "GTAClientThread");
    return SYS_PRX_RES_STARTED;
}

extern "C" int prx_stop(size_t args, const void *argp) {
    if (g_thread_id != 0) {
        u64 exit_code = 0;
        sysThreadJoin(g_thread_id, &exit_code);
    }
    return SYS_PRX_RES_STOPPED;
}
