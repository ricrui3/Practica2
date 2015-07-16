#ifndef __AFN_HPP__
#define __AFN_HPP__
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<stack>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <fstream>



using namespace std;
//Estructura
struct trans {
	int vertex_inicio;
	int vertex_final;
	char trans_simbolo;
};


class AFN {

public:
	vector<int> vertex;
	vector<trans> trancisiones;
	int final_estado;

	AFN() {

	}

	int get_vertex_count() {
		return vertex.size();
	}

	void set_vertex(int no_vertex) {
		for(int i = 0; i < no_vertex; i++) {
			vertex.push_back(i);
		}
	}

	void set_transicion(int vertex_inicio, int vertex_final, char trans_simbolo) {
		trans new_trans;
		new_trans.vertex_inicio = vertex_inicio;
		new_trans.vertex_final = vertex_final;
		new_trans.trans_simbolo = trans_simbolo;
		trancisiones.push_back(new_trans);
	}

	void set_final_estado(int fs) {
		final_estado = fs;
	}

	int get_final_estado() {
		return final_estado;
	}

	void display() {
		trans new_trans;
		cout<<"\n";
		for(int i = 0; i < trancisiones.size(); i++) {
			new_trans = trancisiones.at(i);
			cout<<"q"<<new_trans.vertex_inicio<<" --> q"<<new_trans.vertex_final<<"  : Simbolo - "<<new_trans.trans_simbolo<<endl;
		}
		cout<<"\nEl estado inicial es q0"<<endl;
		cout<<"\nEl estado final es q"<<get_final_estado()<<endl;
	}

	void displayEspecial() {
		trans new_trans;
		cout<<"\n";

		// open a file in write mode.
		ofstream outfile("Grafo.dot");

		// write inputted data into the file.
		outfile << "digraph AFD{" << endl;
		outfile << "\tnode [shape = circle];" << endl;

		outfile << "\tq0" << "[shape = doublecircle];" << endl;
		outfile << "\tqi [shape = point ];" << endl;

		outfile << "\n\t" << "qi -> q0"<< endl;
		for(int i = 0; i < trancisiones.size(); i++) {
			new_trans = trancisiones.at(i);
			cout << "q" << new_trans.vertex_inicio << " -> q" << new_trans.vertex_final << "  : Simbolo - "
				<< new_trans.trans_simbolo<<endl;
			outfile << "\t" << "q" << new_trans.vertex_inicio << " -> q" << new_trans.vertex_final
				<< "[label =" << new_trans.trans_simbolo <<"];" << endl;
		}

		outfile << "}";
		// close the opened file.
		outfile.close();

		system("dot Grafo.dot -Tpng > Grafo.png");
		system("shotwell Grafo.png& ");

		cout<<"\nEl estado inicial es q0"<<endl;
		cout<<"\nEl estado final es q"<<get_final_estado()<<endl;
	}
	


};
// Concatencaion
//  concatenacion
AFN concat(AFN a, AFN b, int opc) {
	AFN resultado;
	resultado.set_vertex(a.get_vertex_count() + b.get_vertex_count());
	int i;
	trans new_trans;

	for(i = 0; i < a.trancisiones.size(); i++) {
		new_trans = a.trancisiones.at(i);
		resultado.set_transicion(new_trans.vertex_inicio, new_trans.vertex_final, new_trans.trans_simbolo);
	}

	if(opc != 1)
		resultado.set_transicion(a.get_final_estado(), a.get_vertex_count(), 'e');   //Estado Epsilon

	for(i = 0; i < b.trancisiones.size(); i++) {
		new_trans = b.trancisiones.at(i);
		if(opc == 1)
			resultado.set_transicion(new_trans.vertex_inicio + a.get_vertex_count()-1, new_trans.vertex_final + a.get_vertex_count(), new_trans.trans_simbolo);
		else
			resultado.set_transicion(new_trans.vertex_inicio + a.get_vertex_count(), new_trans.vertex_final + a.get_vertex_count(), new_trans.trans_simbolo);
	}

	resultado.set_final_estado(a.get_vertex_count() + b.get_vertex_count() - 1);

	return resultado;
}

//operacion cerradura kleene *
AFN kleene(AFN a) {
	AFN resultado;
	int i;
	trans new_trans;
	
	resultado.set_vertex(a.get_vertex_count() + 2);

	resultado.set_transicion(0, 1, 'e');   //Estado Epsilon

	for(i = 0; i < a.trancisiones.size(); i++) {
		new_trans = a.trancisiones.at(i);
		resultado.set_transicion(new_trans.vertex_inicio + 1, new_trans.vertex_final + 1, new_trans.trans_simbolo);
	}

	resultado.set_transicion(a.get_vertex_count(), a.get_vertex_count() + 1, 'e'); //Estado Epsilon
	resultado.set_transicion(a.get_vertex_count(), 1, 'e');  //Estado Epsilon
	resultado.set_transicion(0, a.get_vertex_count() + 1, 'e'); //Esatdo Epsilon

	resultado.set_final_estado(a.get_vertex_count() + 1);

	return resultado;
}
//operacion +
AFN Positiva(AFN a) {
	AFN resultado;
	int i;
	trans new_trans;
	
	resultado.set_vertex(a.get_vertex_count() + 2);

	resultado.set_transicion(0, 1, 'e');   //Estado Epsilon

	for(i = 0; i < a.trancisiones.size(); i++) {
		new_trans = a.trancisiones.at(i);
		resultado.set_transicion(new_trans.vertex_inicio + 1, new_trans.vertex_final + 1, new_trans.trans_simbolo);
	}

	resultado.set_transicion(a.get_vertex_count(), a.get_vertex_count() + 1, 'e'); //Estado Epsilon
	resultado.set_transicion(a.get_vertex_count(), 1, 'e');  //Estado Epsilon
//	resultado.set_transicion(0, a.get_vertex_count() + 1, 'e'); //Esatdo Epsilon

	resultado.set_final_estado(a.get_vertex_count() + 1);

	return resultado;
}

// operacion OR
AFN or_seleccion(vector<AFN> seleccions, int no_of_seleccions) {
	AFN resultado;
	int vertex_count = 2;
	int i, j;
	AFN med;
	trans new_trans;

	for(i = 0; i < no_of_seleccions; i++) {
		vertex_count += seleccions.at(i).get_vertex_count();
	}

	resultado.set_vertex(vertex_count);
	
	int adder_track = 1;

	for(i = 0; i < no_of_seleccions; i++) {
		resultado.set_transicion(0, adder_track, 'e');  // Estado Epsilon
		med = seleccions.at(i);
		for(j = 0; j < med.trancisiones.size(); j++) {
			new_trans = med.trancisiones.at(j);
			resultado.set_transicion(new_trans.vertex_inicio + adder_track, new_trans.vertex_final + adder_track, new_trans.trans_simbolo);
		}
		adder_track += med.get_vertex_count();

		resultado.set_transicion(adder_track - 1, vertex_count - 1, 'e'); // Esatdo Epsilon
	}

	resultado.set_final_estado(vertex_count - 1);

	return resultado;
}

//Pila de simbolos
AFN leer_AFN(string re) {
	stack<char> operador;
	stack<AFN> operands;
	char op_inic;
	int op_fin;
	char pila;
	AFN *nueva_pila;
	
	for(string::iterator it = re.begin(); it != re.end(); ++it) {
		pila = *it;
		if(pila != '(' && pila != ')' && pila != '*' && pila != '+' && pila != '|' && pila != '.') {
			nueva_pila = new AFN();
			nueva_pila->set_vertex(2);
			nueva_pila->set_transicion(0, 1, pila);
			nueva_pila->set_final_estado(1);
			operands.push(*nueva_pila);
			delete nueva_pila;
		} else {
			if(pila == '*') {
				AFN star_sym = operands.top();
				operands.pop();
				operands.push(kleene(star_sym));
			} else if(pila == '+') {
				AFN star_sym = operands.top();
				operands.pop();
				operands.push(Positiva(star_sym));                 
			} else if(pila == '.') {
				operador.push(pila);
			} else if(pila == '|') {
				operador.push(pila);
			} else if(pila == '(') {
				operador.push(pila);
			} else {
				op_fin = 0;
				char c;
				op_inic = operador.top();
				if(op_inic == '(') continue;
				do {
					operador.pop();
					op_fin++;
				} while(operador.top() != '(');
				operador.pop();
				AFN op1;
				AFN op2;
				vector<AFN> seleccions;
				if(op_inic == '.') {
					for(int i = 0; i < op_fin; i++) {
						op2 = operands.top();
						operands.pop();
						op1 = operands.top();
						operands.pop();
						operands.push(concat(op1, op2, 1));
					}
				} else if(op_inic == '|'){
					seleccions.assign(op_fin + 1, AFN());
					int h = op_fin;
					for(int i = 0; i < op_fin + 1; i++) {
						seleccions.at(h) = operands.top();
						h--;
						operands.pop();
					}
					operands.push(or_seleccion(seleccions, op_fin+1));
				} else {
					
				}
			}
		}
	}

	return operands.top();
}


#endif
