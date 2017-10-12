#include "stdafx.h"
#include "client.h"
#include "server.h"
#include <iostream>
#include "fileHandler.h"

#define DEF_PORT 12345
#define DEF_PORT_STR "12345"

#define POS_CHAR 0
#define POS_CONT 1
#define FIRST_MACHINE 2 

#define PALABRA_CLAVE_BEGGINER "iniciar" // Segundo argumento esperado por línea de comandos

#define NUMBER_OF_VALID_CHARS 6
char validCharsTable[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };

enum {FAIL, BEGGINER, NO_BEGGINER} returnsParser;

int parserCmd(vector <string> & ipsVector, int cantMaquinas, int & maquinaPropia, int argc, char ** argv);
void YOU_GO_generatorFromInput(char * buf_YOU_GO, int bufSize);
int getNextIpFromBuf(char * buf, int bufSize);

using namespace std;

int main(int argc, char *argv[])
{
	fileHandler ipsHandler("ips.txt", 'r'); // Abro el archivo de las ips en modo escritura
	vector <string> ipsVector;
	ipsHandler.extractLines(ipsVector);
	int maquinaPropia = 0, cantMaquinas = (int) ipsVector.size();
	bool maquinaFounded = false, master = false, inputOk = false;

	//char * buf_YOU_GO = new char[cantMaquinas + 2]; //creo el buffer para el paquete YOU_GO (sumo '2' para el contador y el caracter de animación).

	switch (parserCmd(ipsVector, cantMaquinas, maquinaPropia, argc, argv))
	{
	case BEGGINER:
		master = true;
		inputOk = true;
		break;
	case NO_BEGGINER:
		master = false;
		inputOk = true;
		break;
	case FAIL:
		inputOk = false;

	}
	if (inputOk)
	{
		cout << " ----------------------------------- " << endl;
		cout << " | TP6 - INTRODUCCION A NETWORKING | " << endl;
		cout << " ----------------------------------- " << '\n' << endl;
		if (master)
		{
			client c;
			cout << ">> Ingrese una secuencia, comenzando por un caracter valido," << endl;
			cout << "   seguido de numeros de maquinas validos (entre 1 y " << cantMaquinas << "), SIN repetirse" << endl;
			cout << "   Caracteres validos: A - B - C - D - E - F" << endl;

			YOU_GO_generatorFromInput(c.get_buf(), (cantMaquinas + 2));  
			// Se genera un paquete YOU_GO a partir del input del usuario.
			// el programa se bloquea aquí hasta que el usuario
			// ingrese correctamente los parámetros.

			c.set_bufClen(cantMaquinas + 2);

			if (maquinaPropia == (c.get_buf())[FIRST_MACHINE])
			{
				cout << "ANIMATION DE FEDE" << endl;
				c.inc_counter();
				Sleep(500);
			}

			int nextIp = getNextIpFromBuf(c.get_buf(), cantMaquinas + 2);
			c.conect_to_host((ipsVector[nextIp-1]).c_str(), DEF_PORT_STR); //////
			c.send_msg(c.get_buf());

			cout << "--> Mensaje enviado correctamente al servidor" << endl;
		}
		
		do
		{
			server s(DEF_PORT);
			s.set_bufSlen(cantMaquinas + 2);
			s.conect_to_port();
			cout << "--> Conexion al puerto exitosa" << endl;
			s.read_from_port();
			if (!s.read_error())
			{
				
				cout << "ANIMACION DE FEDE" << endl;
				s.inc_counter();
				Sleep(500);

				if (s.check_if_last())
				{
					cout << ">> Ingrese una secuencia, comenzando por un caracter valido," << endl;
					cout << "   seguido de numeros de maquinas validos (entre 1 y " << cantMaquinas << "), SIN repetirse." << endl;
					cout << "   Caracteres validos: A - B - C - D - E - F" << endl;
					YOU_GO_generatorFromInput(s.get_buf(), (cantMaquinas + 2)); //aquí se bloquea el programa, hasta que el usuario
					if (maquinaPropia == (s.get_buf())[FIRST_MACHINE])          //ingrese correctamente el input.
					{
						// lo que haya hecho fede
						cout << "ANIMATION DE FEDE" << endl;/////
						s.inc_counter();
						Sleep(500);
					}														   
				}

				int nextIp = getNextIpFromBuf(s.get_buf(), cantMaquinas + 2);
				client c;
				c.set_bufClen(cantMaquinas + 2);
				c.conect_to_host(ipsVector[nextIp-1].c_str(), DEF_PORT_STR);
				c.send_msg(s.get_buf());
				cout << "--> Mensaje enviado correctamente al servidor" << endl;
			}
		} while (true);
	}
	else
	{
		cout << "--> Input error - Abortando programa" << endl;
	}

    return 0;
}

int parserCmd(vector <string> & ipsVector, int cantMaquinas, int & maquinaPropia, int argc, char ** argv)
{
	int ret = 0;
	bool maquinaFounded = false;
	if (argc > 1) // Línea de comandos con otro parámetro además del nombre
	{
		for (int i = 0; (i < cantMaquinas) && (!maquinaFounded); i++)
		{
			if (!strcmp(argv[1], ipsVector[i].c_str())) // Si la ip pasada por parámetro es una ip del archivo
			{
				maquinaFounded = true;
				maquinaPropia = i + 1; // Identifico el numero de máquina. Es i '+1'  porque las máquinas comienzan en '1', pero i en '0'.
			}
		}
		if (maquinaFounded) // Si se encontro la maquina me fijo el siguiente argumento.
		{
			if (argc > 2)
			{
				if (!strcmp(PALABRA_CLAVE_BEGGINER, argv[2])) // Si el segundo parámetro es correcto, la maquina es begginer
				{
					if (argc > 3) // Aunque sea begginer, verifico que no se hayan pasado parámetros demás.
					{
						ret = FAIL;
					}
					else // La máquina es begginer y no se pasó ningún parámetro demás. Está todo OK.
					{
						ret = BEGGINER;
					}
				}
			}
			else // Sin errores, pero la maquina no es begginer.
			{
				ret = NO_BEGGINER;
			}
		}
		else // Error, primer parámetro no corresponde a una ip válida
		{
			ret = FAIL;
		}
	}
	else  // Error, no hay parámetros
	{
		ret = FAIL;
	}

	return ret;
}

void YOU_GO_generatorFromInput(char * buf_YOU_GO, int bufSize)
{
	
	buf_YOU_GO[POS_CONT] = 0; // Ya se sabe que bufSize es mayor a POS_CONT, y que el contador debe arrancar en cero.
	char c = '\0';
	bool validCharFounded = false;
	
	do
	{
		cout << ">> Ingrese un caracter valido: ";
		cin >> c;
		for (int i = 0; i < NUMBER_OF_VALID_CHARS && !validCharFounded; i++)
		{
			if (c == validCharsTable[i])
			{
				validCharFounded = true;
				buf_YOU_GO[POS_CHAR] = c;
			}
		}
	} while (!validCharFounded);

	bool maquinaRepetida = false;
	unsigned int cantIps = bufSize - 2;                       // Las ips son el tamaño del buffer, menos el caracter de animación y el contador.
	unsigned int maquinaInput = 0;							  // Variable para guardar input
	unsigned int machinesReceivedCounter = 0;				  // Variable que cuenta las variables VÁLIDAS que recibo
	unsigned int * maquinasArray = new unsigned int[cantIps]; // Creo un arreglo auxiliar para acordarme que número de máquina recibí (para evitar repetir maquinas)

	for (unsigned int i = 0; i < cantIps; i++) // Lo inicializo en cero, sabiendo que cero no es un número de maquina.
	{
		maquinasArray[i] = 0;
	}

	do
	{
		maquinaRepetida = false; // Clear flag
		cout << ">> Ingrese una maquina valida: ";
		cin >> maquinaInput;
		if (maquinaInput <= cantIps) // Si pasa esta condición, la maquina ingresada o es válida o es repetida.
		{
			for (unsigned int i = 0; (i < cantIps) && (!maquinaRepetida); i++)
			{
				if (maquinaInput == maquinasArray[i])
				{
					maquinaRepetida = true;
				}
			}
			if (!maquinaRepetida)
			{
				maquinasArray[machinesReceivedCounter] = maquinaInput; // Recuerdo la maquina que se ingresó.
				buf_YOU_GO[machinesReceivedCounter + FIRST_MACHINE] = maquinaInput;
				machinesReceivedCounter++; // Incremento la maquina recibida, ya que en este punto estoy seguro de que lo que se recibió es válido.
			}
		}

	} while (machinesReceivedCounter < cantIps);
	buf_YOU_GO[machinesReceivedCounter + FIRST_MACHINE] = '\0';
	delete[] maquinasArray;
}

int getNextIpFromBuf(char * buf, int bufSize)
{
	int counter = buf[POS_CONT];
	int nextIpNumber = buf[2 + counter]; // Sumo dos para tener en cuenta el contador y el caracter de animación.
	return nextIpNumber;
}
