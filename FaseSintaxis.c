#include "EstructuraToken.h"
#include "FaseSintaxis.h"

char tipo_Token[6][20] = {"PalRes", "Id", "Num", "SimEsp", "Cadena", "Error"};

void SintaxisEscribir(struct nodo *reco, int edo)
{
  if(reco != NULL) {
    //printf("\nEstado #%2d:\nLexema:%s\nTipo Token:%s\n", edo, reco->token.lexema, tipo_Token[reco->token.tipo]);
    switch (edo) {
    case 1:/*Escribir*/
      if (strcmp(reco->token.lexema, "escribir") == 0)
        SintaxisEscribir(reco->siguiente, 2);
      break;
    case 2:/*(*/
      if (strcmp(reco->token.lexema, "(") == 0)
        SintaxisEscribir(reco->siguiente, 3);
      else {
        printf("Sintaxis incorrecta, se esperaba un \"(\"  \n");
        SintaxisEscribir(reco->siguiente, 1);
      }
      break;
    case 3:/*Id*/
      if (strcmp(tipo_Token[reco->token.tipo], "Id") == 0)
        SintaxisEscribir(reco->siguiente, 6);
      else if (strcmp(reco->token.lexema, "\"") == 0)
        SintaxisEscribir(reco->siguiente, 4);
      else
        printf("Sintaxis incorrecta, se esperaba un Id o abertura de comillas \" \n");
      break;
    case 4:/*Cadena*/
      if (strcmp(tipo_Token[reco->token.tipo], "Cadena")== 0)
        SintaxisEscribir(reco->siguiente, 5);
      else if(strcmp(reco->token.lexema, "\"") == 0)
        SintaxisEscribir(reco->siguiente, 6);
      else
        printf("Sintaxis incorrecta, se esperaba una cadena \n");
      break;
    case 5:/*Comilla*/
      if (strcmp(reco->token.lexema, "\"") == 0)
        SintaxisEscribir(reco->siguiente, 6);
      else
        printf("Sintaxis incorrecta, se esperaba un cierre de comillas \n");
      break;
    case 6:/*Signo +*/
      if (strcmp(reco->token.lexema, "+") == 0)
        SintaxisEscribir(reco->siguiente, 3);
      else
        SintaxisEscribir(reco, 7);
      break;
    case 7:/*)*/
      if (strcmp(reco->token.lexema, ")") == 0)
        SintaxisEscribir(reco->siguiente, 8);
      else
        printf("Sintaxis incorrecta, se esperaba ) \n");
      break;
    case 8:/*;*/
      if (strcmp(reco->token.lexema, ";") == 0 )
        printf("Sintaxis Escribir Correcta...!\n");
      else
        printf("Sintaxis incorrecta, se esperaba fin de instruccion ;");
      break;
    default:
      break;
    }
    SintaxisEscribir(reco->siguiente, 1);
  }
}

void SintaxisLeer(struct nodo *reco, int edo)
{
  if (reco != NULL) {
    switch (edo) {
    case 1:
      if (strcmp(reco->token.lexema, "leer") == 0)
        SintaxisLeer(reco->siguiente, 2);
      break;
    case 2:
      if (strcmp(reco->token.lexema, "(") == 0)
        SintaxisLeer(reco->siguiente, 3);
      else
        printf("Sintaxis incorrecta, se esperaba una abertura de parentesis \n");
      break;
    case 3:
      if (strcmp(tipo_Token[reco->token.tipo], "Id") == 0)
        SintaxisLeer(reco->siguiente, 4);
      else
        printf("El Id es invalido");
      break;
    case 4:
      if (strcmp(reco->token.lexema, ")") == 0)
        SintaxisLeer(reco->siguiente, 5);
      else
        printf("Se esperaba \")\"");
      break;
    case 5:
      if(strcmp(reco->token.lexema, ";") == 0)
        printf("Sintaxis Leer Correcta...!\n");
      else
        printf("se esperaba fin de linea");
      break;
    default:
      break;
    }
    SintaxisLeer(reco->siguiente, 1);
  }
}

void SintaxisFor(struct nodo *reco, int edo)
{
  if(reco != NULL) {
    //printf("\nEstado #%2d:\nLexema:%s\nTipo Token:%s\n", edo, reco->token.lexema, tipo_Token[reco->token.tipo]);
    switch(edo) {
    case 1:
      if( (strcmp(reco->token.lexema, "para") == 0) &&
          (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
        SintaxisFor(reco->siguiente, 2);
      break;
    case 2:
      if(strcmp(tipo_Token[reco->token.tipo], "Id") == 0)
        SintaxisFor(reco->siguiente, 3);
      else
        printf("Identificador no valido");
      break;
    case 3:
      if( (strcmp(reco->token.lexema, ":=") == 0)  &&
          (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
        SintaxisFor(reco->siguiente, 4);
      else
        printf("No se inicio la variable");
      break;
      case 4:
      if(strcmp(tipo_Token[reco->token.tipo],"Num") == 0)
        SintaxisFor(reco->siguiente, 5);
      else
        printf("No se indico hasta cuando cierra el ciclo");
      break;
    case 5:
      if( (strcmp(reco->token.lexema, "hasta") == 0) &&
          (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
        SintaxisFor(reco->siguiente,6);
      else
        printf("Error en la sentencia PARA hasta %s", reco->token.lexema);
      break;
    case 6:
      if(strcmp(tipo_Token[reco->token.tipo],"Num") == 0)
        SintaxisFor(reco->siguiente, 7);
      else
        printf("No se indico hasta cuando cierra el ciclo");
      break;
    case 7:
      if( (strcmp(reco->token.lexema,"hacer") == 0) &&
          (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
        SintaxisFor(reco->siguiente, 8);
      else
        printf("Error en la sentencia PARA hacer");
      break;
    case 8:
      if( (strcmp(reco->token.lexema,"iniciopara") == 0) &&
          (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
        SintaxisFor(reco->siguiente, 9);
      else
        printf("No se inicio el ciclo PARA inicio para");
      break;
    case 9:
      if( (strcmp(reco->token.lexema,"finpara") == 0) &&
          (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
        printf("Sintaxis Para Correcta...!");
      else
      //Bloque de Intrucciones
        SintaxisFor(reco->siguiente, edo);
      break;
    }
    SintaxisFor(reco->siguiente, 1);
  }
}

void SintaxisIf(struct nodo *reco, int edo)
{
  if(reco != NULL) {
    //printf("\nEstado #%2d:\nLexema:%s\nTipo Token:%s\n", edo, reco->token.lexema, tipo_Token[reco->token.tipo]);
    switch(edo) {
      case 1:/*si*/
        if( (strcmp(reco->token.lexema, "si") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisIf(reco->siguiente, 2);
        break;
      case 2:/* ( -> Parentesis Abierto*/
        if( (strcmp(reco->token.lexema,"(") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisIf(reco->siguiente, 3);
        else
          printf("Aqui no van instrucciones...");
        break;
      case 3:/* ) -> Parentesis Cerrado*/
        if( (strcmp(reco->token.lexema,")") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisIf(reco->siguiente, 4);
        else
        //Aqui entra exp, no la valida ya que corresponde a otra sintaxis distinta
          SintaxisIf(reco->siguiente, edo);
        break;
      case 4:/*Entonces*/
        if( (strcmp(reco->token.lexema, "entonces") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisIf(reco->siguiente,5);
        else
          printf("Aqui no van instrucciones...");
        break;
      case 5:/*iniciosi*/
        if( (strcmp(reco->token.lexema, "iniciosi") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisIf(reco->siguiente,6);
        else
          printf("Aqui no van instrucciones...");
        break;
      case 6:/*finsi*/
        if( (strcmp(reco->token.lexema, "finsi") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisIf(reco->siguiente,7);
        else
        //Intrucciones del boque true
          SintaxisIf(reco->siguiente, edo);
        break;
      case 7:/*sino*/
        if( (strcmp(reco->token.lexema, "sino") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisIf(reco->siguiente,8);
        else
          printf("Sintaxis IF Correcta..!\n");
        break;
      case 8:/*iniciosino*/
        if( (strcmp(reco->token.lexema, "iniciosino") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisIf(reco->siguiente,9);
        else
          printf("Aqui no van instrucciones...");
        break;
      case 9:/*finsino*/
        if( (strcmp(reco->token.lexema, "finsino") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          printf("Sintaxis IF-ELSE Correcta..!\n");
        else
        //Intrucciones del boque flase
          SintaxisIf(reco->siguiente, edo);
        break;
      default:
        SintaxisIf(reco->siguiente, edo);
        break;
    }
  SintaxisIf(reco->siguiente, 1);
  }
}

void SintaxisProgram(struct nodo *reco, int edo)
{
  if(reco != NULL) {
    //printf("\nEstado #%2d:\nLexema:%s\nTipo Token:%s\n", edo, reco->token.lexema, tipo_Token[reco->token.tipo]);
    switch(edo) {
      case 1:/*var*/
        if( (strcmp(reco->token.lexema, "var") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisProgram(reco->siguiente, 2);
        break;
      case 2:/*const*/
        if( (strcmp(reco->token.lexema,"const") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisProgram(reco->siguiente, 3);
        else
          SintaxisProgram(reco->siguiente, edo);
        break;
      case 3:/*incio*/
        if( (strcmp(reco->token.lexema,"inicio") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisProgram(reco->siguiente, 4);
        else
        //Aqui entra exp, no la valida ya que corresponde a otra sintaxis distinta
          SintaxisProgram(reco->siguiente, edo);
        break;
      case 4:/*fin*/
        if( (strcmp(reco->token.lexema, "fin") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          printf("Sintaxis Program Correcta..!\n");
        else
          SintaxisProgram(reco->siguiente, edo);
        break;
      default:
        SintaxisProgram(reco->siguiente, edo);
        break;
    }
  SintaxisProgram(reco->siguiente, 1);
  }
}

void SintaxisVar(struct nodo *reco, int edo)
{
  if(reco != NULL) {
    //printf("\nEstado #%2d:\nLexema:%s\nTipo Token:%s\n", edo, reco->token.lexema, tipo_Token[reco->token.tipo]);
    switch(edo) {
      case 1:/*var*/
        if( (strcmp(reco->token.lexema, "var") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisVar(reco->siguiente, 2);
        break;
      case 2:/*tipoVar*/
        if(((strcmp(reco->token.lexema,"cadena") == 0) ||
            (strcmp(reco->token.lexema,"entero") == 0) ||
            (strcmp(reco->token.lexema,"real") == 0) ||
            (strcmp(reco->token.lexema,"booleano") == 0) ) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisVar(reco->siguiente, 3);
        break;
      case 3:/* : */
        if( (strcmp(reco->token.lexema,":") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisVar(reco->siguiente, 4);
        break;
      case 4:/* id */
        if(strcmp(tipo_Token[reco->token.tipo], "Id") == 0)
          SintaxisVar(reco->siguiente, 5);
        break;
      case 5:/* asignacion */
        if( (strcmp(reco->token.lexema,";") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) ) {
          printf("Sintaxis Declaracion Variable Correcta...!\n");
          SintaxisVar(reco->siguiente, 2);
        } else if( (strcmp(reco->token.lexema,":=") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisVar(reco->siguiente, 6);
        break;  
      case 6:/*Numero || Comilla*/
        if (strcmp(tipo_Token[reco->token.tipo], "Num") == 0)
          SintaxisVar(reco->siguiente, 9);
        else if( (strcmp(reco->token.lexema,"\"") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisVar(reco->siguiente, 7);
        else
          printf("Sintaxis incorrecta, se esperaba un Id o abertura de comillas \" \n");
        break;
      case 7:/*Cadena*/
        if (strcmp(tipo_Token[reco->token.tipo], "Cadena")== 0)
          SintaxisVar(reco->siguiente, 8);
        else if(strcmp(reco->token.lexema, "\"") == 0)
          SintaxisVar(reco->siguiente, 6);
        else
          printf("Sintaxis incorrecta, se esperaba una cadena \n");
        break;
      case 8:/*Comilla*/
        if( (strcmp(reco->token.lexema,"\"") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisVar(reco->siguiente, 9);
        else
          printf("Sintaxis incorrecta, se esperaba un cierre de comillas \n");
        break;
      case 9:/*Punto Coma*/
        if( (strcmp(reco->token.lexema,";") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) ) {
          printf("Sintaxis Declaracion Variable Correcta...!\n");
          SintaxisVar(reco->siguiente, 2);
        } else
          printf("Sintaxis incorrecta, se esperaba un cierre de comillas \n");
        break;
      default:
        SintaxisVar(reco->siguiente, edo);
        break;
    }
  SintaxisVar(reco->siguiente, 1);
  }
}

void SintaxisConst(struct nodo *reco, int edo)
{
  if(reco != NULL) {
    //printf("\nEstado #%2d:\nLexema:%s\nTipo Token:%s\n", edo, reco->token.lexema, tipo_Token[reco->token.tipo]);
    switch(edo) {
      case 1:/*canst*/
        if( (strcmp(reco->token.lexema, "const") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisConst(reco->siguiente, 2);
        break;
      case 2:/*tipoConst*/
        if(((strcmp(reco->token.lexema,"cadena") == 0) ||
            (strcmp(reco->token.lexema,"entero") == 0) ||
            (strcmp(reco->token.lexema,"real") == 0) ||
            (strcmp(reco->token.lexema,"booleano") == 0) ) &&
            (strcmp(tipo_Token[reco->token.tipo], "PalRes") == 0) )
          SintaxisConst(reco->siguiente, 3);
        break;
      case 3:/* : */
        if( (strcmp(reco->token.lexema,":") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisConst(reco->siguiente, 4);
        break;
      case 4:/* id */
        if(strcmp(tipo_Token[reco->token.tipo], "Id") == 0)
          SintaxisConst(reco->siguiente, 5);
        break;
      case 5:/* asignacion */
        if( (strcmp(reco->token.lexema,":=") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisConst(reco->siguiente, 6);
        break;  
      case 6:/*Numero || Comilla*/
        if (strcmp(tipo_Token[reco->token.tipo], "Num") == 0)
          SintaxisConst(reco->siguiente, 9);
        else if( (strcmp(reco->token.lexema,"\"") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisConst(reco->siguiente, 7);
        else
          printf("Sintaxis incorrecta, se esperaba un Id o abertura de comillas \" \n");
        break;
      case 7:/*Cadena*/
        if (strcmp(tipo_Token[reco->token.tipo], "Cadena")== 0)
          SintaxisConst(reco->siguiente, 8);
        else if(strcmp(reco->token.lexema, "\"") == 0)
          SintaxisConst(reco->siguiente, 6);
        else
          printf("Sintaxis incorrecta, se esperaba una cadena \n");
        break;
      case 8:/*Comilla*/
        if( (strcmp(reco->token.lexema,"\"") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) )
          SintaxisConst(reco->siguiente, 9);
        else
          printf("Sintaxis incorrecta, se esperaba un cierre de comillas \n");
        break;
      case 9:/*Punto Coma*/
        if( (strcmp(reco->token.lexema,";") == 0) &&
            (strcmp(tipo_Token[reco->token.tipo], "SimEsp") == 0) ) {
          printf("Sintaxis Declaracion Constante Correcta...!\n");
          SintaxisConst(reco->siguiente, 2);
        } else
          printf("Sintaxis incorrecta, se esperaba un cierre de comillas \n");
        break;
      default:
        SintaxisConst(reco->siguiente, edo);
        break;
    }
  SintaxisConst(reco->siguiente, 1);
  }
}