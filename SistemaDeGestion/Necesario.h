#pragma once

std::string cargarCadena();
bool Valido(const std::string& nombre);
void mostrarError(const std::string& mensaje, int linea);
int cargarEntero(int x, int y, int lineaError);
bool ValidoDescripcion(const std::string& texto);
bool emailValido(const std::string& email);

