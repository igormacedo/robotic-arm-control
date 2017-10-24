from time import sleep

##  Adding path to armdriver at runtime
import sys
import os
import inspect
path = os.path.dirname(os.path.abspath(inspect.stack()[0][1])).replace("src_python","armdriver-module/build")
print path
sys.path.append(path)

from armdriver import *
HOME_POS = "#0P1500#1P1500#2P1500#3P1500#4P1500"

print "Programa de demonstracao iniciado"

serial_fd = abrir_porta()
if serial_fd == -1:
    print "Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa..."
    quit()
else:
    print "Porta serial /dev/ttyS0 aberta com sucesso"
    if configurar_porta(serial_fd) == -1:
        print "Erro inicializando a porta"
        fechar_porta(serial_fd)
        quit()

	#//////////////////////
	#// PRIMEIRO COMANDO //
	#//////////////////////
    comando = HOME_POS
    print "\nPRIMEIRO COMANDO - POSICAL INICIAL\n"
    if enviar_comando(comando, serial_fd) != -1 :
        print "Enviando de comando com teste de envio: ",
        print HOME_POS
    else:
        print "Problema no envio do comando\nAbortando o programa..."
        quit()

    raw_input("Pressione enter para continuar...")

    #/////////////////////
    #// SEGUNDO COMANDO //
    #/////////////////////
    print "\nSEGUNDO COMANDO - MOVER O PUNHO\n"
    print "Espere 5 segundos...\n"
    sleep(5)

    comando = "#" + str(WRI_SERVO) + "P" + str(trava(WRI_SERVO,429496729))
    print "Envio de comando sem teste de envio, utilizando a funcao trava: " + comando
    enviar_comando(comando, serial_fd)

    raw_input("Pressione enter para continuar...")

	#//////////////////////
	#// TERCEIRO COMANDO //
	#//////////////////////
    print "\nTERCEIRO COMANDO - MOVER A GARRA\n"
    print "Espere 5 segundos...\n"
    sleep(5)

    comando = "#" + str(GRI_SERVO) + "P" + str(trava(GRI_SERVO,2000))
    enviar_comando(comando, serial_fd)

    # FIM DO PROGRAMA DEMO
    fechar_porta(serial_fd)
    print "\nAcesso a porta serial /dev/ttyS0 finalizado\n"

print "\nPROGRAMA DEMONSTRACAO FINALIZADO\n\n"
