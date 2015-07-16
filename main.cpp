#include <string.h>
#include <fstream>
#include "AFN.hpp"

using namespace std;

void token(char* str) {
    char * pch;

    pch = strtok (str,"ESCRIBIR_TODA_LA_EXPRECION_REGULAR_ENTRE_PARENTESIS:EXPRECION_REGULAR:");

    while (pch != NULL)
    {

        pch = strtok (NULL, "ESCRIBIR_TODA_LA_EXPRECION_REGULAR_ENTRE_PARENTESIS:EXPRECION_REGULAR:");

    }

}

int main() {
    cout<<"\n\nAlgoritmo de construccion de Thompson mediante una expresion regular como entrada "
    <<"y devuelve su correspondiente Automata Finito no determinista\n";
    cout<<"\nLos elementos basicos para la construccion de la AFN son : \n";


    AFN a, b;

    cout<<"\nPara el segmento de expresion regular : (a)";
    a.set_vertex(2);
    a.set_transicion(0, 1, 'a');
    a.set_final_estado(1);
    a.display();


    cout<<"\nPara el segmento de expresion regular : (b)";
    b.set_vertex(2);
    b.set_transicion(0, 1, 'b');
    b.set_final_estado(1);
    b.display();


    cout<<"\nPara el segmento de expresion regular [ Concatenacion ] : (a.b)";
    AFN ab = concat(a, b);
    ab.display();


    cout<<"\nPara el segmento de expresion regular [ Cerradura de Kleene  ] : (a*)";
    AFN a_star = kleene(a);
    a_star.display();


    cout<<"\nPara el segmento de expresion regular [ Cerradura de Kleene  ] : (a+)";
    AFN b_star = Positiva(a);
    b_star.display();

    cout<<"\nPara el segmento de expresion regular [Or] : (a|b)";
    int nume_seleciones;
    nume_seleciones = 2;
    vector<AFN> selecion(nume_seleciones, AFN());
    selecion.at(0) = a;
    selecion.at(1) = b;
    AFN a_or_b = or_seleccion(selecion, nume_seleciones);
    a_or_b.display();

    ifstream infile("ExpresionRegular.txt");
    char buffer[1000000];
    infile >> buffer;
    cout << "La cadena es:";
    cout << buffer << endl;
    infile.close();
    token(buffer);

    AFN prueba_AFN = leer_AFN(buffer);  //-----------------------------leer expresion regular

    cout<<"Por ejemplo : \n Para la expresion regular "<<buffer<<" -- \n"<<endl;





    prueba_AFN.display();



    return 0;
}


// ESCRIBIR_TODA_LA_EXPRECION_REGULAR_ENTRE_PARENTESIS:EXPRECION_REGULAR:((a|(c.d+)))   // expresion regular como las recibe
