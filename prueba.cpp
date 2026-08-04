#include <iostream>
#include <SFML/Config.hpp>

using namespace std;

int prueba() {
	cout << "=== ESTADO DE TU ENTORNO ===" << endl << endl;
	
	// 1. Version de C++
	cout << "Codigo de macro __cplusplus: " << __cplusplus << endl;
	cout << "Estandar de C++ en uso: ";
	if (__cplusplus >= 202002L) cout << "C++20" << endl;
	else if (__cplusplus >= 201703L) cout << "C++17" << endl;
	else if (__cplusplus >= 201402L) cout << "C++14" << endl;
	else if (__cplusplus >= 201103L) cout << "C++11" << endl;
	else cout << "C++98 / C++03" << endl;
	
	// 2. Version de SFML
	cout << endl << "Version de SFML instalada: " 
		<< SFML_VERSION_MAJOR << "." 
		<< SFML_VERSION_MINOR << "." 
		<< SFML_VERSION_PATCH << endl;
	
	return 0;
}
