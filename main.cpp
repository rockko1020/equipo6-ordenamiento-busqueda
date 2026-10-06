#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using std::cout;
using std::cin;
using std::string;
using std::vector;

struct event
{
    string date;
    string time;
    string ip_origin;
    string ip_destiny;
    string domain_origin;
    string port_origin;
    string port_destiny;
    string domain_destiny;
    
};

 
vector<event> read(const string& document)
{
    vector<event> eventos;        
    std::ifstream archivo(document); 
    string line;

    while (std::getline(archivo, line))   
    {
        std::stringstream ss(line);       
        event e;                          
        string pedazo;
        int contador = 0;

        while (std::getline(ss, pedazo, ',')) 
        {
            if (contador == 0) e.date = pedazo;
            else if (contador == 1) e.time = pedazo;
            else if (contador == 2) e.ip_origin = pedazo;
            else if (contador == 3) e.port_origin = pedazo;
            else if (contador == 4) e.domain_origin = pedazo;
            else if (contador == 5) e.ip_destiny = pedazo;
            else if (contador == 6) e.port_destiny = pedazo;
            else if (contador == 7) e.domain_destiny = pedazo;
            contador++;
        }

        eventos.push_back(e);   
    }

    return eventos;   
}


time_t toTimeT(const event& e) {
    std::tm t = {};
    t.tm_mday = std::stoi(e.date.substr(0,2));
    t.tm_mon  = std::stoi(e.date.substr(3,2)) - 1;
    t.tm_year = std::stoi(e.date.substr(6,4)) - 1900;
    t.tm_hour = std::stoi(e.time.substr(0,2));
    t.tm_min  = std::stoi(e.time.substr(3,2));
    t.tm_sec  = std::stoi(e.time.substr(6,2));
    return std::mktime(&t);
}


bool operator<(const event& a, const event& b) {
    time_t ta = toTimeT(a);
    time_t tb = toTimeT(b);
    return ta < tb;
}

void write(const string& document, const vector<event>& eventos) {
    std::ofstream archivo_salida(document);

    for (const event& e : eventos) {
        archivo_salida << e.date << "," << e.time << "," 
                       << e.ip_origin << "," << e.port_origin << "," 
                       << e.domain_origin << "," << e.ip_destiny << ","
                       << e.port_destiny << ","
                       << e.domain_destiny << "\n";
    }
}

void search(const vector<event>& evento)
{
    std::tm t = {};
    int dia,mes,anio;
    cout << "Dia, mes y aniooo (separados por espacio): ";
    cin >> dia >> mes >> anio;

    t.tm_mday = dia;
    t.tm_mon  = mes - 1;
    t.tm_year = anio - 1900;
    auto a = std::mktime(&t);


    auto it = std::find_if(evento.begin(),evento.end(),[a](const event& e)
    {
        return toTimeT(e) >= a;   
    });
        
    for (auto iterador = it; iterador != evento.end(); iterador++)
    {
        
        cout << iterador->date << "," << iterador->time << "," 
        << iterador->ip_origin << "," << iterador->port_origin << "," 
        << iterador->domain_origin << "," << iterador->ip_destiny << ","
        << iterador->port_destiny << ","
        << iterador->domain_destiny << "\n";
        
    }
}

int main() {

    vector <event> eventos = read("equipo6.csv");
    std::sort(eventos.begin(), eventos.end());
    write("ordenado.csv", eventos);
    search(eventos);






    return 0;
}
