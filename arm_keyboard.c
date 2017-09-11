/*************************************************************/
/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */
/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */
/*							     */
/*   DRIVER DO BRAÇO ROBÓTICO LYNX AL5D PARA A PORTA SERIAL  */
/*							     */
/*   DESENVOLVEDORES:					     */
/*	- ENG. M.SC. DESNES AUGUSTO NUNES DO ROSÁRIO	     */
/*	- ENG. DANILO CHAVES DE SOUSA ICHIHARA		     */
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "ufrn_al5d.h"

//Posicao inicial para todos os servos
#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500"

int main()
{
	ufrn_header();

	int serial_fd;
	char *comando;

	// INICIO DO PROGRAMA DEMO //

	printf("Robotic Arm Control Console \n\n");

	serial_fd = abrir_porta();

	if(serial_fd == -1)
	{
		printf("Erro while opening serial port /dev/ttyS0\nAbort program...");
		return -1;
	}
	else
	{
		printf("Serial port /dev/ttyS0 successfully opened!\n");


		if(configurar_porta(serial_fd) == -1)
		{
		    printf("Erro while initializing port\n");
		    close(serial_fd);
		    return -1;
		}

		comando = (char*) malloc(sizeof(char)*BUFSIZE);
		int joint = 0, position = 0;

		while(joint >= 0)
		{
			//////////////////////
			// Envio de COMANDO //
			//////////////////////

			// NECESSÁRIO: Limpar a regiao de memória da string //
			//             antes de mandar outro comando        //
			memset(comando, 0, BUFSIZE);

			printf("\nType your command in the format:\n #<canal>P<valor_posicao> \n");
			printf("Joint {0,1,2,3,4} {-1 to exit}: ");
			scanf("%d",&joint);
			printf("Position: ");
			scanf("%d",&position);
			sprintf(comando,"#%dP%d",joint,trava(joint,position));

			//Escrevendo com teste de escrita
			if(enviar_comando(comando,serial_fd) == -1)
			{
				printf("Problem sending command\nAbort program...");
				return -1;
			}

			printf("Pressione enter para continuar...");
			getchar();

	//		strcpy(comando,"#0P500");
	//		sprintf(comando,"#%dP%d",SHL_SERVO,1000);
	//		strcpy(comando,"#2P1500");
	//		strcpy(comando,"#3P2000");
	//		sprintf(comando,"#%dP%d",GRI_SERVO,1000);

		}

			// FIM DO PROGRAMA DEMO //
		  fechar_porta(serial_fd);
			printf("\nAcesso a porta serial /dev/ttyS0 finalizado\n");

  }

	printf("\nPROGRAMA DEMONSTRACAO FINALIZADO\n\n");

	return 0;
}
