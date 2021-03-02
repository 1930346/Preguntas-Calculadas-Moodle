#include <iostream>
#include <string>
#include <ctime>
#include <math.h>
#include <string.h>
#include "ExpressionParser.h"
#include <fstream>

using namespace std;
#define LONGITUD 10
#define PREGUNTAS 30
#define NUMEROS 40

void vaciarMatriz(string(*)[LONGITUD]);
void calculadaManual(string, string(*)[LONGITUD], int*, string(*), int*);
void calcularResultados(string, double(*)[NUMEROS], double(*)[NUMEROS], int*, string (*)[LONGITUD], int*, int*, int*, int*);
void sustituirEnPregunta(string, double(*)[NUMEROS], int , string (*), string (*)[LONGITUD], int*, int*);
void presentarExamen(string (*), double (*)[NUMEROS], int (*), int*, double*);

int main() {              
	srand(time(NULL));
	int opcion = 0, puntuacion = 0, cantidadPreguntas = 0, comodinesRegistrados = 0, limiteMinimo = 0, limiteMaximo = 0, aleatoriosPregunta;
	int auxiliarRelleno = 0, filasAyuda = 0, vectorOpcionesPregunta[NUMEROS];

	string comodines[PREGUNTAS][LONGITUD];
	string vectorPreguntas[PREGUNTAS];
	string pregunta, formula, respuesta = "", decision = "";

	double valoresComodines[PREGUNTAS][NUMEROS] = { 0 }, auxiliarValores[PREGUNTAS][NUMEROS] = { 0.0 }, auxiliarDelAuxilair[PREGUNTAS][NUMEROS] = { 0.0 };
	double resultados[PREGUNTAS][NUMEROS] = { 0.0 };
	double tolerancia = 0.0;
	
	ifstream archivo;


	do {
		std::cout << "1.- Crear una pregunta calculada.";
		std::cout << "\n2.- Crear una pregunta calculada simple.";
		std::cout << "\n3.- Crear una pregunta calculada de opcion multiple.\n";
		std::cout << "Elija una opcion: ";
		cin >> opcion;
		vectorOpcionesPregunta[cantidadPreguntas] = opcion;
		switch (opcion) {
		case 1:
			std::cout << "Quiere importar una pregunta de un archivo? (Si/No): " << endl;
			cin >> decision;
			if (decision == "Si"){   //LECTURA
				archivo.open("pregunta.txt", ios::in);  //abriendo el archivo en modo lectura   (primer parametro ruta donde se creara, 

				if (archivo.fail()) {
					std::cout << "No se pudo abrir el archivo";
					exit(1);
				}

				while (!archivo.eof()) {      //mientras no sea el final del archivo   eof es una función que recorre todo el archivo
					std::getline(archivo, pregunta);      //pasamos todo lo del archivo a esa variable String
					std::cout << pregunta << endl;
				}
				archivo.close();
			} else {
				std::cout << "Ingrese el texto de la pregunta. Ingresar comodines con { } \n";
				std::getline(cin, pregunta);
				std::getline(cin, pregunta);
			}

			if (cantidadPreguntas == 0) {
				vaciarMatriz(comodines);
			}
			calculadaManual(pregunta, comodines, &cantidadPreguntas, vectorPreguntas, &comodinesRegistrados);
			//	std::cout<<pregunta;
			for (int i = 0; i < PREGUNTAS; i++) {
				for (int j = 0; j < LONGITUD; j++) {
					if (comodines[i][j] != "") {
						std::cout <<"i: "<< i << " j: " << j << " -- " << comodines[i][j];
						std::cout << "\n";
					}
					else {
						break;
					}
				}
			}
			comodinesRegistrados = comodinesRegistrados;
			if (comodinesRegistrados != 0) {

				std::cout << "Ingrese el numero de conjuntos de respuestas que utilizaras: ";
				cin >> aleatoriosPregunta;

				for (int i = 0; i < PREGUNTAS; i++) {
					for (int j = 0; j < NUMEROS; j++) {
						if (comodines[i][j] != "") {
							std::cout << "Comodin: " << comodines[i][j] << endl;
							std::cout << "Ingrese el limite minimo: ";
							cin >> limiteMinimo;
							std::cout << "Ingrese el limite maximo: ";
							cin >> limiteMaximo;
							for (int k = 0; k < aleatoriosPregunta; k++) {
								valoresComodines[auxiliarRelleno][k] = (double)limiteMinimo + (rand() % (limiteMaximo - limiteMinimo));
								auxiliarValores[auxiliarRelleno][k] = valoresComodines[auxiliarRelleno][k];
								std::cout << "COMODINES ANTES DE ENTRAR A FUNCION: " << valoresComodines[auxiliarRelleno][k] << endl;
							}
							auxiliarRelleno++;
						}
						else {
							break;
						}
					}
				}

				sustituirEnPregunta(pregunta, auxiliarValores, auxiliarRelleno, vectorPreguntas, comodines, &cantidadPreguntas, &aleatoriosPregunta);
				//INVOCANDO LAS FUNCIONES PARA LOS CALCULOS POSIBLES ERRORES DE AQUÍ HACIA ABAJO
				std::cout << "Ingrese la formula (Ingresar los comodines con { }): ";
				std::getline(cin, pregunta);
				std::getline(cin, pregunta);
				calcularResultados(pregunta, valoresComodines, resultados, &cantidadPreguntas, comodines, &comodinesRegistrados, &aleatoriosPregunta, &filasAyuda, &auxiliarRelleno);
				vaciarMatriz(comodines);
				std::cout << "\n\n";


			}
			auxiliarRelleno = 0;
			cantidadPreguntas++;

			break;
		case 2:
			std::cout << "Quiere importar una pregunta de un archivo? (Si/No): " << endl;
			cin >> decision;
			if (decision == "Si") {   //LECTURA
				archivo.open("pregunta.txt", ios::in);  //abriendo el archivo en modo lectura   (primer parametro ruta donde se creara, 

				if (archivo.fail()) {
					std::cout << "No se pudo abrir el archivo";
					exit(1);
				}

				while (!archivo.eof()) {      //mientras no sea el final del archivo   eof es una función que recorre todo el archivo
					std::getline(archivo, pregunta);      //pasamos todo lo del archivo a esa variable String
					std::cout << pregunta << endl;
				}
				archivo.close();
			}
			else {
				std::cout << "Ingrese el texto de la pregunta. Ingresar comodines con { } \n";
				std::getline(cin, pregunta);
				std::getline(cin, pregunta);
			}
			if (cantidadPreguntas == 0) {
				vaciarMatriz(comodines);
			}
			calculadaManual(pregunta, comodines, &cantidadPreguntas, vectorPreguntas, &comodinesRegistrados);
			//	std::cout<<pregunta;
			for (int i = 0; i < PREGUNTAS; i++) {
				for (int j = 0; j < LONGITUD; j++) {
					if (comodines[i][j] != "") {
						std::cout << "i: " << i << " j: " << j << " -- " << comodines[i][j];
						std::cout << "\n";
					}
					else {
						break;
					}
				}
			}
			comodinesRegistrados = comodinesRegistrados;
			if (comodinesRegistrados != 0) {

				std::cout << "Ingrese el numero de conjuntos de respuestas que utilizaras: ";
				cin >> aleatoriosPregunta;

				for (int i = 0; i < PREGUNTAS; i++) {
					for (int j = 0; j < NUMEROS; j++) {
						if (comodines[i][j] != "") {
							std::cout << "Comodin: " << comodines[i][j] << endl;
							std::cout << "Ingrese el limite minimo: ";
							cin >> limiteMinimo;
							std::cout << "Ingrese el limite maximo: ";
							cin >> limiteMaximo;
							for (int k = 0; k < aleatoriosPregunta; k++) {
								valoresComodines[auxiliarRelleno][k] = (double)limiteMinimo + (rand() % (limiteMaximo - limiteMinimo));
								auxiliarValores[auxiliarRelleno][k] = valoresComodines[auxiliarRelleno][k];
								std::cout << "COMODINES ANTES DE ENTRAR A FUNCION: " << valoresComodines[auxiliarRelleno][k] << endl;
							}
							auxiliarRelleno++;
						}
						else {
							break;
						}
					}
				}

				sustituirEnPregunta(pregunta, auxiliarValores, auxiliarRelleno, vectorPreguntas, comodines, &cantidadPreguntas, &aleatoriosPregunta);
				//INVOCANDO LAS FUNCIONES PARA LOS CALCULOS POSIBLES ERRORES DE AQUÍ HACIA ABAJO
				std::cout << "Ingrese la formula (Ingresar los comodines con { }): ";
				std::getline(cin, pregunta);
				std::getline(cin, pregunta);
				calcularResultados(pregunta, valoresComodines, resultados, &cantidadPreguntas, comodines, &comodinesRegistrados, &aleatoriosPregunta, &filasAyuda, &auxiliarRelleno);
				vaciarMatriz(comodines);
				std::cout << "\n\n";


			}
			auxiliarRelleno = 0;
			cantidadPreguntas++;
			break;
		case 3:
			
			std::cout << "Quiere importar una pregunta de un archivo? (Si/No): " << endl;
			cin >> decision;
			if (decision == "Si") {   //LECTURA
				archivo.open("pregunta.txt", ios::in);  //abriendo el archivo en modo lectura   (primer parametro ruta donde se creara, 

				if (archivo.fail()) {
					std::cout << "No se pudo abrir el archivo";
					exit(1);
				}

				while (!archivo.eof()) {      //mientras no sea el final del archivo   eof es una función que recorre todo el archivo
					std::getline(archivo, pregunta);      //pasamos todo lo del archivo a esa variable String
					std::cout << pregunta << endl;
				}
				archivo.close();
			}
			else {
				std::cout << "Ingrese el texto de la pregunta. Ingresar comodines con { } \n";
				std::getline(cin, pregunta);
				std::getline(cin, pregunta);
			}

			if (cantidadPreguntas == 0) {
				vaciarMatriz(comodines);
			}

			calculadaManual(pregunta, comodines, &cantidadPreguntas, vectorPreguntas, &comodinesRegistrados);
			//	std::cout<<pregunta;
			for (int i = 0; i < PREGUNTAS; i++) {
				for (int j = 0; j < LONGITUD; j++) {
					if (comodines[i][j] != "") {
						std::cout << "i: " << i << " j: " << j << " -- " << comodines[i][j];
						std::cout << "\n";
					}
					else {
						break;
					}
				}
			}
			comodinesRegistrados = comodinesRegistrados;
			if (comodinesRegistrados != 0) {

				std::cout << "Ingrese el numero de conjuntos de respuestas que utilizaras: ";
				cin >> aleatoriosPregunta;

				for (int i = 0; i < PREGUNTAS; i++) {
					for (int j = 0; j < NUMEROS; j++) {
						if (comodines[i][j] != "") {
							std::cout << "Comodin: " << comodines[i][j] << endl;
							std::cout << "Ingrese el limite minimo: ";
							cin >> limiteMinimo;
							std::cout << "Ingrese el limite maximo: ";
							cin >> limiteMaximo;
							for (int k = 0; k < aleatoriosPregunta; k++) {
								valoresComodines[auxiliarRelleno][k] = (double)limiteMinimo + (rand() % (limiteMaximo - limiteMinimo));
								auxiliarValores[auxiliarRelleno][k] = valoresComodines[auxiliarRelleno][k];
								std::cout << "COMODINES ANTES DE ENTRAR A FUNCION: " << valoresComodines[auxiliarRelleno][k] << endl;
							}
							auxiliarRelleno++;
						}
						else {
							break;
						}
					}
				}

				sustituirEnPregunta(pregunta, auxiliarValores, auxiliarRelleno, vectorPreguntas, comodines, &cantidadPreguntas, &aleatoriosPregunta);
				//INVOCANDO LAS FUNCIONES PARA LOS CALCULOS POSIBLES ERRORES DE AQUÍ HACIA ABAJO
				std::cout << "Ingrese la formula (Ingresar los comodines con { }): ";
				std::getline(cin, pregunta);
				std::getline(cin, pregunta);
				calcularResultados(pregunta, valoresComodines, resultados, &cantidadPreguntas, comodines, &comodinesRegistrados, &aleatoriosPregunta, &filasAyuda, &auxiliarRelleno);
				vaciarMatriz(comodines);
				std::cout << "\n\n";


			}
			auxiliarRelleno = 0;
			cantidadPreguntas++;

			break;
		default:
			printf("Opcion no existente.");
			break;
		}
		std::cout << "\nDesea agregar otra pregunta (Si/No)? ";
		std::getline(cin, respuesta);
	} while (respuesta == "Si");
	
	std::cout << endl;
	for (int i = 0; i < cantidadPreguntas + 1; i++) {
		std::cout << vectorPreguntas[i] << endl;
	}
	std::cout << "\n\nResultados: " << endl; 
	for (int i = 0; i < cantidadPreguntas + 1; i++) {
		for (int  j = 0; j < NUMEROS; j++){
			if (resultados[i][j] > 0.0) {
				std::cout << resultados[i][j] << "\t";
			}
		}
		std::cout << "\n";
	}
	
	std::cout << "Ingrese la tolerancia de las respuestas: ";
	cin >> tolerancia;

	presentarExamen(vectorPreguntas, resultados, vectorOpcionesPregunta, &cantidadPreguntas, &tolerancia);


	return 0;
}


void presentarExamen(string (*vectorPreguntas), double (*resultados)[NUMEROS], int (*vectorOpcionesPregunta),int *cantidadPreguntas, double *tolerancia) {
	system("cls");
	srand(time(NULL));
	int recorrerPreguntas = 0;
	double respuesta = 0.0;
	int respuestaOpcion = 0;

	std::cout << "PREPARANDO EXAMEN..." << endl;
	std::cout << "INICIO DE EXAM. " << endl;

	while (recorrerPreguntas < *cantidadPreguntas){
		if (vectorOpcionesPregunta[recorrerPreguntas] == 3){
			std::cout << "Pregunta numero: " << recorrerPreguntas << endl;
			std::cout << vectorPreguntas[recorrerPreguntas] << "\nElige la respuesta correcta: " << endl;

			std::cout << "1: " << resultados[recorrerPreguntas][0] << endl;
			std::cout << "2: " << resultados[recorrerPreguntas][0] + 1 + rand() % 100 << endl;
			std::cout << "3: " << resultados[recorrerPreguntas][0] + 1 + rand() % 10 << endl;
			std::cout << "4: " << resultados[recorrerPreguntas][0] + 1 + rand() % 20 << endl;
			cin >> respuestaOpcion;
			if (respuestaOpcion == 1) {
				std::cout << "Respuesta correcta :D " << endl;
				break;
			} else {
				std::cout << "Respuesta incorrecta :c " << endl;
				break;
			}
		} else if (vectorOpcionesPregunta[recorrerPreguntas] == 1 || vectorOpcionesPregunta[recorrerPreguntas] == 2){
			std::cout << "Pregunta numero: " << recorrerPreguntas << endl;
			std::cout << vectorPreguntas[recorrerPreguntas] << "\nIngresa la respuesta: ";
			cin >> respuesta;
			for (int i = 0; i < NUMEROS; i++){
				if (((resultados[recorrerPreguntas][i] == (double)(respuesta)) || (resultados[recorrerPreguntas][i] == (double)(respuesta+*tolerancia))) || (resultados[recorrerPreguntas][i] == (double)(respuesta - *tolerancia))){
					std::cout << "Respuesta correcta :D " << endl;
					break;
				} else {
					std::cout << "Respuesta incorrecta :c " << endl;
					break;
				}
			}
		}
		recorrerPreguntas++;
	}
	

}



void vaciarMatriz(string(*comodines)[LONGITUD]) {
	for (int i = 0; i < PREGUNTAS; i++) {
		for (int j = 0; j < LONGITUD; j++) {
			comodines[i][j] = "";
		}
	}
}



void calculadaManual(string pregunta, string(*comodines)[LONGITUD], int* cantidadPreguntas, string *vectorPreguntas, int* comodinesRegistrados) {
	int posicion = 0, i = 0;
	string comodinx[LONGITUD] = { "" };

	while (pregunta.length() > 1 && pregunta.find_first_of("{") != -1) {
		posicion = pregunta.find_first_of("{");
		pregunta = pregunta.substr(posicion + 1);
		comodinx[i] = pregunta.substr(0, pregunta.find_first_of("}"));
		i++;
	}

	for (int j = 0; j <= i; j++) {
		comodines[0][j] = comodinx[j];
		*comodinesRegistrados = *comodinesRegistrados + 1;
	}
	*comodinesRegistrados = *comodinesRegistrados - 1;

}


void calcularResultados(string formula, double (*valoresComodines)[NUMEROS], double (*resultados)[NUMEROS], int* cantidadPreguntas, string (*comodines)[LONGITUD], int* comodinesRegistrados, int* aleatoriosPregunta, int* filasAyuda, int* auxiliarRelleno) {
	int posicionLlave = 0, posicionLlaveCierre = 0, k = 0, columnas = 0, i = 0;
	string formulaAuxiliar = formula;
	std::string var;

	int numeroDeComodines = count(formula.begin(), formula.end(), '{');
	//std::cout << "auxiliarRelleno antes de entrar a los for: " << *auxiliarRelleno << endl;
	for (int i = 0; i < *aleatoriosPregunta; i++) {
	//	std::cout << "auxiliarRelleno despues de entrar a los for i: " << i << endl;
		for (int j = 0; j < numeroDeComodines; j++) {
		//	std::cout << "j cntando el numero de comodines j:  " << j << endl;
			var = formula.substr(formula.find('{') + 1, formula.find('}') - formula.find('{') - 1);
		//	std::cout << var << endl;
			for (int k = 0; k < *auxiliarRelleno+1; k++) {
			//	std::cout << " K: " << k << endl;
			//	std::cout << var << " > " << comodines[0][k] << std::endl;
				if (var == comodines[0][k]) {
					formula = formula.replace(formula.find('{'), formula.find('}') - formula.find('{') + 1, std::to_string(valoresComodines[k][columnas]));
					std::cout << "PREGUNTA CON NUMEROS: " << formula << endl;
					//std::cout << "Columnas: " << columnas << endl;
					system("PAUSE");
				}
			}
		}
		
		//--------------------------------- EMPIEZA LA FORMULA -------
		ExpressionParser calculoResultado(formula);
		if (!calculoResultado.MatchingParetheses()) {
			std::cout << "Error: mismatched parentheses or empty input"
				<< std::endl;
		}
		std::vector<std::string>RPN;
		if (calculoResultado.InfixToRPN(RPN)) {
			//Print<std::string, std::vector<std::string>::const_iterator>("RPN tokens : ", RPN.begin(), RPN.end(), " ");

			std::string str_result;
			if (calculoResultado.Evaluate(RPN, str_result)) {
				std::cout << "Resultado = " << str_result << std::endl;
				//std::cout << std::endl;
				resultados[*cantidadPreguntas][columnas] = std::stod(str_result);
			}
		}
		else {
			std::cout << "Error: mismatched parentheses" << std::endl;
		}
		formula = formulaAuxiliar;
		columnas++;
	}
	
	for (int i = 0; i < PREGUNTAS; i++) {
		for (int j = 0; j < NUMEROS; j++) {
			valoresComodines[i][j] = 0.0;
		}
	}
	*comodinesRegistrados = 0;
	*aleatoriosPregunta = 0;
	*auxiliarRelleno = 0;
	
}




void sustituirEnPregunta(string pregunta, double(*auxiliarValores)[NUMEROS], int auxiliarRelleno, string(*vectorPreguntas), string(*comodines)[LONGITUD], int *cantidadPreguntas, int *aleatoriosPregunta) {
	int posicionLlave = 0, posicionLlaveCierre = 0, k = 0;
	string preguntaAuxiliar;

	for (int i = 0; i < auxiliarRelleno; i++){
		for (int j = 0; j < *aleatoriosPregunta; j++){
			std::cout << "i: " << i << " j: " << j << " -- " << auxiliarValores[i][j] << endl;
		}
	}
	std::string var;
	int numeroDeComodines = count(pregunta.begin(), pregunta.end(),'{');
	for (int i = 0; i < auxiliarRelleno; i++) {
		for(int j = 0; j < numeroDeComodines; j++){
			var = pregunta.substr(pregunta.find('{')+1, pregunta.find('}') - pregunta.find('{')-1);
			//	std::cout << var << endl;
			for (int k = 0; k < auxiliarRelleno; k++) {
			//	std::cout << var << "  " << comodines[0][k] << std::endl;
				if (var == comodines[0][k]) {
					pregunta = pregunta.replace(pregunta.find('{'), pregunta.find('}') - pregunta.find('{') + 1, std::to_string(auxiliarValores[k][0]));
				//	std::cout << "PREGUNTA CON NUMEROS: " << pregunta << endl;
				}
			}
		}
	}

	for (int i = *cantidadPreguntas; i < *cantidadPreguntas+1; i++){
		vectorPreguntas[i] = pregunta;
	//	std::cout << "Vector preguntas: " << vectorPreguntas[i] << endl;
	}

}

