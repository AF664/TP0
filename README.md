# TP0
BigNum

Para usar makefile

Compilación (equivalente a g++ main.cpp cmdline.cpp big_num.cpp -o main -ansi -pedantic -Wall):
make all

Remover arhivos compilación:
make clean

Cambios:
Main tiene la forma similar a la version2

Bignum de la version1 pero con varias modificaciones
Ejemplo: conversión usar stoi para conversión

Compila pero todavía le falta para funcionar bien



// actualizaciones de 24 de mayo - Alexis

Le agregue metodos para setear y mirar el signo del objeto BigNum
Cree un bool para ver si el numero es valido, en caso de que no es valido es false, sirve para realizar las cuentas
Se modifico calculadora.resolver para que trabaje en funcion de los signos de los numeros
Ej si num1 y num2 son negativos y la operacion es -
la operacion resultante seria
-num2 +(num1) pero le cambio los signos a los numeros 
num2 = -num2, num1=-num1
finalmente => num2-num1
con los numeros positivos

Tambien modifique el constructor de cuenta para que sea mas abarcativo y tome
\t " " al inicio de los numeros

Ahi un problema cuando le ingresas numeros con el signo en la entrada, Ej
+7654+87654 --> num1 tira error por corrupcion o doble free
7654+-7654 --> num2 tira error por corrupcion o doble free

el problema salta al terminar el constructor de calculadora, linea 57. En ese momento llama a los destructores de las clases BigNum en las lineas 53 y 54 (todo en calculadora.cpp). Ahi me aparece el error. 
Pero para mi es un problema que lo arrastra desde el constructor de BigNum, en el for (linea 70 de BigNum.cpp).

Mañana lo veo en detalle.

Faltaria:
    Algoritmo de resta
    verificar problemas de memoria
    El informe.
    
 //Actualización 25 de mayo
 Agregué operadores =, ==, menor, mayor a BigNum y adapté contenido de suma, multiplicación y resta a los operadores correspondientes.
