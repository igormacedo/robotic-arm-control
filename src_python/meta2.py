from time import sleep
from math import pi, atan2, sqrt, cos, sin, acos, asin

##  Adding path to armdriver at runtime
import sys
import os
import inspect
path = os.path.dirname(os.path.abspath(inspect.stack()[0][1])).replace("src_python","armdriver-module/build")
print path
sys.path.append(path)

from armdriver import *

HOME_POS = "#0P1500#1P1500#2P1500#3P1500#4P1500"
L1 = 4.76
L2 = 3.00
L3 = 14.7
L4 = 18.6
L5 = 5.6
serial_fd = None

#angulos = {0:0.0, 1:0.0, 2:0.0, 3:0.0}

def convertGrau2Pulse(deg, joint):
    pulse = 0
    if joint == 0:
        pulse = int(deg*(BAS_MAX-BAS_MIN)/180.0 + 1370);
    elif joint == 1:
        pulse = int((deg-90.0)*(SHL_MAX-SHL_MIN)/90.0 + 1450);
    elif joint == 2:
        pulse = int(1600 - (deg+90)*(ELB_MAX-ELB_MIN)/90.0);
    elif joint == 3:
        pulse = int(1480 + deg*(WRI_MAX-WRI_MIN)/180.0);
    else:
        pass
    return pulse

def inverse_kinematic(x,y,x,phi):
	angles = {0:0.0, 1:0.0, 2:0.0, 3:0.0}
    phi = phi * pi/180.0
	angles[0] = atan2(y,x)
	a = 0
    c = 0
	a = sqrt(x*x + y*y) - cos(phi)*L5;
	c = z - sin(phi)*L5 - L1 - L2;
    print("a: "+str(a)+", c: "+str(c)+", phi: "+str(phi))

	angles[2] = - acos((a*a + c*c - L4*L4 - L3*L3)/(2*L4*L3));
	angles[1] = pi - asin((a*a+c*c+L3*L3-L4*L4)/(2*L3*sqrt(a*a+c*c))) - atan2(a,c);
	angles[3] = phi - ang.theta1 - ang.theta2;

    angles = {key:item*180/pi for key,item in angles.items()} ## convert to degree

	print("Ângulo 0: %lf, Ângulo 1: %lf, Ângulo 2: %lf, Ângulo 3: %lf\n" % tuple(angles.valeus()));
	return angles

def move(x,y,z,phi):
	phi = -90;
	angle = inverse_kinematic(x,y,z,phi);
	int pulso0,pulso1,pulso2,pulso3;

    pulse = {key:convertGrau2Pulse(item,key) for key,item in angle.items()}
    pulse = {joint:trava(joint,item) for joint, item in pulse.items()}

	comando = "#0P%d#1P%d#2P%d#3P%dT3000" % tuple(pulse.values());
	print("\n %s \n", comando);
    enviar_comando(comando, serial_fd)

def hold():
    enviar_comando("#4P550T3000", serial_fd)

def leave():
    enviar_comando("#4P1000T3000", serial_fd)

def halt():
    enviar_comando("#0P0#1P0#2P0#3P040T3000", serial_fd)


def main():

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

        input("Pressione enter para continuar...")

        while True:
            inp = raw_input(" Type x, y, z, and phi with spaces: ")
            inp = inp.split(" ")
            inp = [float(i) for i in inp]

            move(inp[0], inp[1], inp[2], inp[3])



if __name__ == "__main__":
    main()
