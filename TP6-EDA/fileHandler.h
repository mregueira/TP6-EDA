#ifndef FILE_HANDLER_H_ //FILE_HANDLER_H_ !
#define FILE_HANDLER_H_
#include <fstream>
#include <vector>

using namespace std;
class fileHandler
{
public:
	fileHandler(char * fileName, char mode);// 'r' indica el modo lectura.

	int countLines(void);   //cuenta las lineas del archivo. cada línea termina con '\n'.

	int identifyWordLine(string & word); //recibe una palabra y devuelve el numero de linea en 
										 //que se encuentra. Por línea no debe haber mas de 49
										 //caracteres.
										 //la primer linea es la línea cero. Si no encuentra la palabra devuelve -1.
	bool extractLines(string * wordsArray, int numberOfWords);
	//llena el arreglo con las líneas del archivo.
	//devuelve true o false según el éxito de la operación.
	//cada línea no supera los 'numberOfCaracteres' caractéres.
	bool extractLines(vector <string> & vector_); //llena el vector de strings con todas las líneas del archivo.
												  //devuelve true or false según el éxito de la operación
	~fileHandler();
private:

	std::ifstream file;

};
#endif // FILE_HANDLER_H_ !

