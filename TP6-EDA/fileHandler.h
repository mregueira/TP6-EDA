#ifndef FILE_HANDLER_H_ //FILE_HANDLER_H_ !
#define FILE_HANDLER_H_
#include <fstream>
#include <vector>

using namespace std;
class fileHandler
{
public:
	fileHandler(char * fileName, char mode);// 'r' indica el modo lectura.

	int countLines(void);   //cuenta las lineas del archivo. cada l�nea termina con '\n'.

	int identifyWordLine(string & word); //recibe una palabra y devuelve el numero de linea en 
										 //que se encuentra. Por l�nea no debe haber mas de 49
										 //caracteres.
										 //la primer linea es la l�nea cero. Si no encuentra la palabra devuelve -1.
	bool extractLines(string * wordsArray, int numberOfWords);
	//llena el arreglo con las l�neas del archivo.
	//devuelve true o false seg�n el �xito de la operaci�n.
	//cada l�nea no supera los 'numberOfCaracteres' caract�res.
	bool extractLines(vector <string> & vector_); //llena el vector de strings con todas las l�neas del archivo.
												  //devuelve true or false seg�n el �xito de la operaci�n
	~fileHandler();
private:

	std::ifstream file;

};
#endif // FILE_HANDLER_H_ !

