# Ordenamiento y búsqueda de bitácora (Equipo 6)

Programa en C++ que:
1. Lee los eventos de red de `equipo6.csv`.
2. Los ordena por fecha y hora (`std::sort`).
3. Guarda el resultado ordenado en `ordenado.csv`.
4. Pide una fecha (día mes año) y muestra todos los eventos desde esa fecha.

## Cómo correrlo

```bash
g++ -std=c++17 -o main main.cpp
./main
```

Ejemplo de entrada: `21 8 2024`

## Correrlo en línea
Abre este repositorio en GitHub Codespaces (botón **Code → Codespaces → Create codespace**) y en la terminal ejecuta los comandos de arriba.
