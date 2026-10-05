# Pruebas del Analizador Sintactico

## Caso valido completo

```cpp
int main() {
    int numero = 10;
    float promedio = 8.5;

    if (numero >= 5) {
        numero = numero + 1;
    } else {
        numero = 0;
    }

    while (numero < 15) {
        numero = numero + 1;
    }

    return numero;
}
```

Resultado esperado: **Sintaxis valida**.

## Declaracion sin punto y coma

```cpp
int main() {
    int numero = 10
    return numero;
}
```

Resultado esperado: error en la declaracion porque falta `;`.

## Condicion sin parentesis de cierre

```cpp
int main() {
    int numero = 10;
    if (numero >= 5 {
        return numero;
    }
}
```

Resultado esperado: error porque falta `)` despues de la condicion.

## Bloque sin llave de cierre

```cpp
int main() {
    int numero = 10;
    while (numero < 15) {
        numero = numero + 1;
}
```

Resultado esperado: error porque falta una llave `}` para cerrar un bloque.

## Expresion incompleta

```cpp
int main() {
    int resultado = 10 + ;
    return resultado;
}
```

Resultado esperado: error porque falta un operando despues de `+`.
