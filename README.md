# Analizador Sintactico Grafico

Aplicacion de escritorio desarrollada en C++ 17 con Qt Widgets. Realiza analisis lexico y sintactico de un subconjunto didactico de C/C++ y presenta los resultados sin utilizar una consola.

## Funcionalidad

- Editor grafico para escribir o cargar codigo de prueba.
- Tabla de tokens con lexema, tipo y linea.
- Validacion de la estructura del programa mediante descenso recursivo.
- Mensajes de error con numero de linea y token cercano.
- Arbol sintactico simplificado para explicar la estructura reconocida.

## Lenguaje aceptado

El analizador reconoce:

- Tipos: `int`, `float`, `double`, `char`, `bool`, `string` y `void`.
- Declaraciones: `int edad = 20;`
- Asignaciones: `edad = edad + 1;`
- Funciones y parametros: `int sumar(int a, int b) { ... }`
- Condicionales `if` y `else` con bloques.
- Ciclos `while` con bloques.
- Sentencias `return`.
- Llamadas a funciones: `mostrar(valor);`
- Expresiones con `+`, `-`, `*`, `/`, `%`, comparaciones e igualdad.
- Literales enteros, reales, cadenas y booleanos.
- Comentarios de una linea y de bloque.

## Gramatica simplificada

```text
programa       -> sentencia* EOF
sentencia      -> declaracion | funcion | asignacion | llamada
                | if | while | return | bloque
declaracion    -> tipo IDENTIFICADOR ("=" expresion)? ";"
funcion        -> tipo IDENTIFICADOR "(" parametros? ")" bloque
parametros     -> tipo IDENTIFICADOR ("," tipo IDENTIFICADOR)*
asignacion     -> IDENTIFICADOR "=" expresion ";"
llamada        -> IDENTIFICADOR "(" argumentos? ")" ";"
if             -> "if" "(" expresion ")" bloque ("else" (if | bloque))?
while          -> "while" "(" expresion ")" bloque
return         -> "return" expresion? ";"
bloque         -> "{" sentencia* "}"
expresion      -> igualdad
igualdad       -> comparacion (("==" | "!=") comparacion)*
comparacion    -> termino (("<" | "<=" | ">" | ">=") termino)*
termino        -> factor (("+" | "-") factor)*
factor         -> unario (("*" | "/" | "%") unario)*
unario         -> ("!" | "-") unario | primario
primario       -> IDENTIFICADOR | literal | "(" expresion ")"
```

## Estructura del proyecto

- `lexer.cpp`: analizador lexico utilizado por la aplicacion.
- `lexer.l`: especificacion de referencia para FLEX.
- `lexerbridge.cpp` y `lexerbridge.h`: puente entre el lexer y la interfaz.
- `parser.cpp` y `parser.h`: analizador sintactico descendente recursivo.
- `token.h`: representacion de los tokens.
- `mainwindow.cpp`, `mainwindow.h` y `mainwindow.ui`: interfaz grafica.
- `PRUEBAS.md`: casos correctos e incorrectos para demostrar el proyecto.
- `CMakeLists.txt`: configuracion de compilacion.

## Compilacion

1. Instale Qt 6 con MinGW de 64 bits y CMake.
2. Abra `CMakeLists.txt` en Qt Creator.
3. Seleccione el kit Desktop Qt 6.11.2 MinGW 64 bit.
4. Configure el proyecto en modo Release.
5. Compile y ejecute `AnalizadorSintactico`.

## Uso

1. Escriba codigo en el editor o pulse **Cargar**.
2. Pulse **Analizar**.
3. Revise la tabla de tokens.
4. Consulte el estado sintactico y el arbol simplificado.
5. Corrija los errores indicados y vuelva a analizar.

## Presentacion sugerida

1. Definir el analisis sintactico y su relacion con el analisis lexico.
2. Explicar la gramatica aceptada.
3. Mostrar el descenso recursivo y la precedencia de operadores.
4. Ejecutar un caso valido y enseñar el arbol sintactico.
5. Ejecutar un caso con errores y explicar la recuperacion.
6. Cerrar con las limitaciones y posibles mejoras.

## Limitaciones

Es un lenguaje didactico, no un compilador completo de C++. No realiza analisis semantico, comprobacion de tipos, generacion de codigo ni ejecucion del programa.
