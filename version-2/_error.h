// archivo: error.h

#ifndef _ERROR_H_INCLUDED
#define _ERROR_H_INCLUDED

#include <iostream>

#define _CNT_MSJ_ERROR 6
#define _MSJ_OK ""
#define _MSJ_NOK "\nNo se pudo realizar la tarea\n"
#define _MSJ_ERROR_DIGITOS "\nError, entrada no reconocida\n"
#define _MSJ_ERROR_PRECISION "\nError, precision no adecuada\n"
#define _MSJ_ERROR_OVERFLOW "\nError, operación sobrepasó la precisión\n"
#define _MSJ_ERROR_ENTRADA "\nError, no se pudo leer la entrada\n"


typedef enum status{
    OK,
    NOK,
    ERROR_DIGITOS,
    ERROR_PRECISION,
    ERROR_OVERFLOW,
    ERROR_ENTRADA

} status_t;

void error_msj(status_t codigo);

#endif