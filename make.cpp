//GENERADOR GÉNERICO DE MAKEFILES POR FRANCISCO JAVIER PIZARRO
//solo apto para programas cuyas librerías propias son independientes de las otras
#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>    
#include <cstdio>       
#pragma execution_character_set( "utf-8" )
int main () {
    SetConsoleOutputCP( 65001 );
    string ficheroMake;
    cout << "Introduzca el nombre del fichero Makefile que desea crear" << endl;
    cin >> ficheroMake;
    ofstream f(ficheroMake);
    if(f.is_open()) {
        //Partes genéricas del makefile
        cout << "Fichero creado correctamente" << endl;
        f <<    "#------------------------------------------------------------------------------" << endl << 
                "# File:   Makefile" << endl <<
                "# Autor:  Francisco Javier Pizarro" << endl <<
                "# Coms:   Fichero Makefile generado génericamente" << endl << 
                "#         make all compila y generará los ejecutables" << endl << 
                "#         make programaA compila y genera programaA" << endl << 
                "#         ..." << endl << 
                "#------------------------------------------------------------------------------" << endl;
        cout << "Cabecera generada correctamente " << endl;
        f << endl <<
                "#---------------------------------------------------------" << endl << 
                "# Definición de macros" << endl << 
                "CC = g++" << endl << 
                "CPPFLAGS = -I. -std=c++11      #opciones de compilación" << endl << 
                "LDFLAGS =                      #opciones de linkado" << endl << 
                "RM = rm -f                     #comando para borrar ficheros" << endl << endl << 
                "all: ";
        cout << "Macros génericas generadas de manera correcta" << endl;
        //Partes particulares(n ejecutables y nombres)
        cout << "Introduzca el número total de ejecutables(.exe) deseados" << endl;
        unsigned int nExe;
        cin >> nExe;
        string exe[nExe];
        cout << "Introduzca los nombres de los ejecutables deseados(sin la terminación .exe), introduzca uno por linea" << endl;
        cin.ignore();
        for(int i = 0; i < nExe; i++) {
            getline(cin, exe[i]);
            f << exe[i] << " ";
        }
        f << endl << "#-----------------------------------------------------------" << endl;
        //Partes compilación
        unsigned int nLib;
        for(int i = 0; i < nExe; i++) {
            //Compilación genérica
            f <<   "# Compilacion" << endl << 
                    exe[i] << ".o: " << exe[i] << ".cpp" << endl << 
	               "	${CC} -c " << exe[i] << ".cpp ${CPPFLAGS}" << endl << 
                   "#linkado" << endl;
            //Compilación particular
            cout << "Introduzca el número de módulos librería, creados por usted(que invoca con #include (comillas)) que usa el programa " << exe[i]<< endl;
            cin >> nLib;
            string lib[nLib];
            cout << "Introduzca los nombres de las librerías uno a uno por línea, sin la terminación que tienen" << endl;
            cin.ignore();
            for(int j = 0; j < nLib; j++) {
                getline(cin, lib[j]);
            }
            f << exe[i] << ": " << exe[i] << ".o ";
            for(int j = 0; j < nLib; j++) {
                f << lib[j] << ".o ";
            }               
            f << endl <<"	${CC} " << exe[i] << ".o ";
            for(int j = 0; j < nLib; j++) {
                f << lib[j] << ".o ";
            }
            f << "-o " << exe[i] << " ${LDFLAGS}" << endl << endl;
            for(int j = 0; j < nLib; j++) {
                f << lib[j] << ".o: " << lib[j] << ".cpp " << lib[j] << ".hpp " << endl << 
               "	${CC} -c " << lib[j] << ".cpp ${CPPFLAGS}" << endl;
            }
            f << "#-----------------------------------------------------------" << endl;
            cout << "Fichero completado correctamente " << endl;
        }
        f.close();
    }
    else {
        cout << "ERROR creando el fichero" << endl;
        return 1;
    }
    return 0;
}