/*************************************************************/
/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */
/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */
/*							     																				 */
/*    MODULO PYTHON DO DRIVER DO BRAÇO ROBÓTICO LYNX AL5D    */
/*							                                             */
/*   DESENVOLVEDOR:					                                 */
/*	- ENG. IGOR MACEDO SILVA                    	           */
/*	                                        	               */
/*************************************************************/

/*  ADAPTADO DE: */
/*************************************************************/
/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */
/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */
/*							                                             */
/*   DRIVER DO BRAÇO ROBÓTICO LYNX AL5D PARA A PORTA SERIAL  */
/*							                                             */
/*   DESENVOLVEDORES:				                           	     */
/*	- ENG. M.SC. DESNES AUGUSTO NUNES DO ROSÁRIO	           */
/*	- ENG. DANILO CHAVES DE SOUSA ICHIHARA		               */
/*************************************************************/

#include "ufrn_al5d.h"
#include <Python.h>

//Initialize serial port
//int configurar_porta(int fd)
static PyObject* py_configurar_porta(PyObject* self, PyObject* args)
{
	int fd;
	PyArg_ParseTuple(args, "i", &fd);

	int portstatus = 0;

	struct termios options;
	// Get the current options for the port...
	tcgetattr(fd, &options);
	// Set the baud rates to 115200...
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	// Enable the receiver and set local mode...
	options.c_cflag |= (CLOCAL | CREAD);

	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	//options.c_cflag |= SerialDataBitsInterp(8);           /* CS8 - Selects 8 data bits */
	options.c_cflag &= ~CRTSCTS;                            // disable hardware flow control
	options.c_iflag &= ~(IXON | IXOFF | IXANY);           // disable XON XOFF (for transmit and receive)
	//options.c_cflag |= CRTSCTS;                     /* enable hardware flow control */

	options.c_cc[VMIN] = 0;     //min carachters to be read
	options.c_cc[VTIME] = 0;    //Time to wait for data (tenths of seconds)

	//Set the new options for the port...
	tcflush(fd, TCIFLUSH);

	if (tcsetattr(fd, TCSANOW, &options)==-1)
	{
		perror("On tcsetattr:");
		portstatus = -1;
	}
	else
		portstatus = 1;

	//return portstatus;
	return Py_BuildValue("i", portstatus);
}


//int abrir_porta(void)
static PyObject* py_abrir_porta(PyObject* self, PyObject* args)
{
	int fd; // file description for the serial port

	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

	if(fd == -1) // if open is unsucessful
	{
		//perror("open_port: Unable to open /dev/ttyS0 - ");
		perror("open_port: Unable to open /dev/ttyS0. \n");
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
		//fcntl(fd, F_SETFL, FNDELAY);
		//printf("port is open.\n");
	}

	//return(fd);
	return Py_BuildValue("i", fd);
} //open_port

//int enviar_comando(char* data, int fd)
static PyObject* py_enviar_comando(PyObject* self, PyObject* args)
{
	char *data;
	int fd;
	PyArg_ParseTuple(args, "si", &data,&fd);

	int n;

	//printf("%s[%d]\n", data, strlen(data));

	data[strlen(data)] = 0x0d;
	data[strlen(data)+1] = 0x00;

	n = write(fd, data, strlen(data));

	if (n < 0)
	{
		fputs("write() falhou!\n", stderr);
		//return -1;
		return Py_BuildValue("i", -1);
	}
	else
	{
		//data[strlen(data)] = '\0';
		//printf("%s[%d]\n", data, strlen(data));
		//printf("Successfully wrote %d bytes\n",n);
		//return n;
		return Py_BuildValue("i", n);
	}
}

//void fechar_porta(int fd)
static PyObject* py_fechar_porta(PyObject* self, PyObject* args)
{
	int fd;
	PyArg_ParseTuple(args, "i", &fd);
	close(fd);
	Py_RETURN_NONE;
}

//unsigned int trava(unsigned int canal, unsigned int pos)
static PyObject* py_trava(PyObject* self, PyObject* args)
{
	unsigned int canal, pos;
	PyArg_ParseTuple(args, "II", &canal, &pos);

	switch(canal)
	{
		case BAS_SERVO:
			if(pos<BAS_MIN)
				//return BAS_MIN;
				return Py_BuildValue("I", BAS_MIN);
			else if (pos > BAS_MAX)
				//return BAS_MAX;
				return Py_BuildValue("I", BAS_MAX);
			else
				//return pos;
				return Py_BuildValue("I", pos);
		break;
		case SHL_SERVO:
			if(pos<SHL_MIN)
				//return SHL_MIN;
				return Py_BuildValue("I", SHL_MIN);
			else if (pos > SHL_MAX)
				//return SHL_MAX;
				return Py_BuildValue("I", SHL_MAX);
			else
				//return pos;
				return Py_BuildValue("I", pos);
		break;
		case ELB_SERVO:
			if(pos<ELB_MIN)
				//return ELB_MIN;
				return Py_BuildValue("I", ELB_MIN);
			else if (pos > ELB_MAX)
				//return ELB_MAX;
				return Py_BuildValue("I", ELB_MAX);
			else
				//return pos;
				return Py_BuildValue("I", pos);
		break;
		case WRI_SERVO:
			if(pos<WRI_MIN)
				//return WRI_MIN;
				return Py_BuildValue("I", WRI_MIN);
			else if (pos > WRI_MAX)
				//return WRI_MAX;
				return Py_BuildValue("I", WRI_MAX);
			else
				//return pos;
				return Py_BuildValue("I", pos);
		break;
		case GRI_SERVO:
			if(pos<GRI_MIN)
				//return GRI_MIN;
				return Py_BuildValue("I", GRI_MIN);
			else if (pos > GRI_MAX)
				//return GRI_MAX;
				return Py_BuildValue("I", GRI_MAX);
			else
				//return pos;
				return Py_BuildValue("I", pos);
		break;
		default:
			if(pos<500)
				//return 500;
				return Py_BuildValue("I", 500);
			else if (pos > 2500)
				//return 2500;
				return Py_BuildValue("I", 2500);
			else
				//return pos;
				return Py_BuildValue("I", pos);
		break;
	}
}

//void ufrn_header(void)
static PyObject* py_ufrn_header(PyObject* self, PyObject* args)
{
	printf("/*************************************************************/\n");
	printf("/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */\n");
	printf("/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */\n");
	printf("/*							     																				 */\n");
	printf("/*    MODULO PYTHON DO DRIVER DO BRAÇO ROBÓTICO LYNX AL5D    */\n");
	printf("/*							                                             */\n");
	printf("/*   DESENVOLVEDOR:					                                 */\n");
	printf("/*	- ENG. IGOR MACEDO SILVA                    	           */\n");
	printf("/*	                                        	               */\n");
	printf("/*************************************************************/\n");
	printf("/* ADAPTADO DE: */\n");
	printf("/*************************************************************/\n");
	printf("/*       UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE         */\n");
	printf("/*   DEPARTAMENTO DE ENGENHARIA DE COMPUTAÇÃO E AUTOMAÇÃO    */\n");
	printf("/*							                                             */\n");
	printf("/*        DRIVER DO BRAÇO ROBÓTICO LYNX AL5D - v2.0 	       */\n");
	printf("/*							                                             */\n");
	printf("/*   DESENVOLVEDORES:					                               */\n");
	printf("/*	- ENG. M.SC. DESNES AUGUSTO NUNES DO ROSÁRIO	           */\n");
	printf("/*	- ENG. DANILO CHAVES DE SOUSA ICHIHARA		               */\n");
	printf("/*************************************************************/\n\n");
	Py_RETURN_NONE;
}

// Bind Python function names to our C functions
static PyMethodDef armdriver_methods[] = {
        {"configurar_porta", py_configurar_porta, METH_VARARGS},
        {"abrir_porta", py_abrir_porta, METH_VARARGS},
        {"enviar_comando", py_enviar_comando, METH_VARARGS},
        {"trava", py_trava, METH_VARARGS},
        {"fechar_porta", py_fechar_porta, METH_VARARGS},
        {"ufrn_header", py_ufrn_header, METH_VARARGS},
        {NULL, NULL}
};

//Python calls this to let us initialize our module
PyMODINIT_FUNC
initarmdriver(void)
{
        PyObject *module = Py_InitModule("armdriver", armdriver_methods);
				if (PyModule_AddIntConstant (module, "BUFSIZE", BUFSIZE)) { goto except; };

				// Servo da base HS-485HB //
				if (PyModule_AddIntConstant (module, "BAS_SERVO", BAS_SERVO)) { goto except; };
				if (PyModule_AddIntConstant (module, "BAS_MIN", BAS_MIN)) { goto except; };
				if (PyModule_AddIntConstant (module, "BAS_MAX", BAS_MAX)) { goto except; };

				// Servo do ombro HS-805BB //
				if (PyModule_AddIntConstant (module, "SHL_SERVO", SHL_SERVO)) { goto except; };
				if (PyModule_AddIntConstant (module, "SHL_MIN", SHL_MIN)) { goto except; };
				if (PyModule_AddIntConstant (module, "SHL_MAX", SHL_MAX)) { goto except; };

				// Servo do cotovelo HS-755HB//
				if (PyModule_AddIntConstant (module, "ELB_SERVO", ELB_SERVO)) { goto except; };
				if (PyModule_AddIntConstant (module, "ELB_MIN", ELB_MIN)) { goto except; };
				if (PyModule_AddIntConstant (module, "ELB_MAX", ELB_MAX)) { goto except; };

				// Servo do punho HS-645MG //
				if (PyModule_AddIntConstant (module, "WRI_SERVO", WRI_SERVO)) { goto except; };
				if (PyModule_AddIntConstant (module, "WRI_MIN", WRI_MIN)) { goto except; };
				if (PyModule_AddIntConstant (module, "WRI_MAX", WRI_MAX)) { goto except; };

				// Servo da garra HS-322HD //
				if (PyModule_AddIntConstant (module, "GRI_SERVO", GRI_SERVO)) { goto except; };
				if (PyModule_AddIntConstant (module, "GRI_MIN", GRI_MIN)) { goto except; };
				if (PyModule_AddIntConstant (module, "GRI_MAX", GRI_MAX)) { goto except; };

				goto finally;
				except:
					Py_XDECREF(module);
					module = NULL;
				finally:
					return;
}
