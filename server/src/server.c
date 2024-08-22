#include "server.h"

int main(void) 
{
	logger = log_create("server.log", "SERVER_LOG", 1, LOG_LEVEL_DEBUG);

	int socket_servidor = iniciar_servidor();
	log_info(logger, "SERVER listo para recibir al cliente");
	int socket_cliente = esperar_cliente(socket_servidor);

	t_list* lista;
	while (1) 
	{
		int cod_op = recibir_operacion(socket_cliente);
		switch (cod_op) 
		{
		case MENSAJE:
			recibir_mensaje(socket_cliente);
			break;
		case PAQUETE:
			lista = recibir_paquete(socket_cliente);
			log_info(logger, "Me llegaron los siguientes valores: \n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "CLIENTE se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}

void iterator(char* value) 
{
	log_info(logger,"%s", value);
}