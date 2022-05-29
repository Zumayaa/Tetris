#include "Tetris_allegro.h"
#include <allegro.h>

#define anchura 800
#define altura  820
#define Tbloque 25

#define color1   0
#define color2   1
#define color3   2
#define color4   3
#define color5   4
#define color6   5
#define color7   6

#define Ladrillo 0


int mapa[13][22];

void mostrar_bloque(BITMAP * buffer, BITMAP * img_b, int XC, int YC, int color, int tipo){
    blit(img_b, buffer, tipo * Tbloque, color * Tbloque, XC * Tbloque, YC * Tbloque, Tbloque, Tbloque);
}

pieza::pieza(Bloque _b_prin, Bloque _bls[3], int _color_p){
    b_prin = _b_prin;
    for(int i=0; i<3; i++)
        bls[i] = _bls[i];
    color_p = _color_p;
}

void pieza::mostrar_pieza(BITMAP * buffer, BITMAP * img_b){
    int XCls, YCls;
    b_prin.tipo = Ladrillo;
    mostrar_bloque(buffer, img_b, b_prin.x, b_prin.y, color_p, b_prin.tipo);
    for(int i=0; i<3; i++){
        XCls = b_prin.x + bls[i].x;
        YCls = b_prin.y + bls[i].y;
        if((XCls >= b_prin.x) && (YCls >= b_prin.y))
            bls[i].tipo = Ladrillo;
        else
            bls[i].tipo = Ladrillo;
        mostrar_bloque(buffer, img_b, XCls, YCls, color_p, bls[i].tipo);
    }
}

bool pieza::colision_abajo(){
    if(mapa[b_prin.y+1][b_prin.x] != 9)
        return true;
    int XCls, YCls;
    for(int i=0; i<3; i++){
        XCls = b_prin.x + bls[i].x;
        YCls = b_prin.y + bls[i].y;
        if(mapa[YCls+1][XCls] != 9)
            return true;
    }
    return false;
}

bool pieza::colision_derec(){
    if(mapa[b_prin.y][b_prin.x+1] != 9)
        return true;
    int XCls, YCls;
    for(int i=0; i<3; i++){
        XCls = b_prin.x + bls[i].x;
        YCls = b_prin.y + bls[i].y;
        if(mapa[YCls][XCls+1] != 9)
            return true;
    }
    return false;
}

bool pieza::colision_izqui(){
    if(mapa[b_prin.y][b_prin.x-1] != 9)
        return true;
    int XCls, YCls;
    for(int i=0; i<3; i++){
        XCls = b_prin.x + bls[i].x;
        YCls = b_prin.y + bls[i].y;
        if(mapa[YCls][XCls-1] != 9)
            return true;
    }
    return false;
}

void pieza::insertar_mapa(){
    int XCls, YCls;
    mapa[b_prin.y][b_prin.x] = (b_prin.tipo*10) + color_p;
    for(int i=0; i<3; i++){
        XCls = b_prin.x + bls[i].x;
        YCls = b_prin.y + bls[i].y;
        mapa[YCls][XCls] = (bls[i].tipo*10) + color_p;
    }
}

void pieza::rotar(){
    int aux;
    for(int i=0; i<3; i++){
        aux = bls[i].x;
        bls[i].x = bls[i].y;
        bls[i].y = aux;
        bls[i].x *= -1;
        rest(5);
    }
}

bool pieza::fila_llena(int fila){
    for(int i=1; i<11; i++)
        if(mapa[fila][i] == 9)
            return false;
    return true;
}

void mostrar_muros(BITMAP * buffer, BITMAP * marco){
//    blit(muroV, buffer, 0, 0, 0, 0, 25, 500);
 //   blit(muroH, buffer, 0, 0, 0, 500, 300, 25);
  //  blit(muroV, buffer, 0, 0, 275, 0, 25, 500);
     blit(marco, buffer, 0, 0, 0, 0, 850, 900);


}
/*
void mostrar_marco(BITMAP * buffer, BITMAP * marco){
   blit(marco, buffer, 0, 0, 0, 0, 850, 900);
}
*/
void limpiar_mapa(){
    for(int i=0; i<21; i++){
        for(int j=0; j<12; j++){
            if(j == 0 || j == 11 || i == 20)
                mapa[i][j] = 8;
            else
                mapa[i][j] = 9;
        }
    }
}

void mostrar_mapa(BITMAP * buffer, BITMAP * img_b){
    int t, c;
    for(int i=0; i<20; i++){
        for(int j=1; j<11; j++){
            if(mapa[i][j] != 9){
                t = mapa[i][j] / 10;
                c = mapa[i][j] % 10;
                mostrar_bloque(buffer, img_b, j, i, c, t);
            }
        }
    }
}

void mostrar_numero(BITMAP * buffer, BITMAP * img_num, int numero, int xnum, int ynum){
    int uDigito, pos = 0;
    if(numero != 0){
        while(numero != 0){
            uDigito = numero % 10;
            blit(img_num, buffer, uDigito*30, 0, xnum-pos, ynum, 30, 60);
            numero /= 10;
            pos += 38;
        }
    }
    else
        blit(img_num, buffer, 0, 0, xnum, ynum, 30, 60);
}

void mostrar_datos(BITMAP * buffer, BITMAP * img_texto, BITMAP* img_num, int puntos, int nivel){

    blit(img_texto, buffer, 0, 0, 350, 55, 90, 34);
    blit(img_texto, buffer, 0, 34, 625, 60, 119, 34);
    mostrar_numero(buffer, img_num, puntos, 620, 140);
    blit(img_texto, buffer, 0, 68, 610, 560, 122, 34);
    mostrar_numero(buffer, img_num, nivel, 630, 600);
}

void eliminar_fila(int fila){
    for(int i=fila; i>0; i--)
        for(int j=1; j<11; j++)
            mapa[i][j] = mapa[i-1][j];
}

void portada(BITMAP * p){
   int flash = 0;
   while(!key[KEY_ENTER]){
      if(flash<80)
        blit(p, screen, 0,0,0,0, anchura, altura);
      else
        blit(p, screen, 805,0,0,0, anchura, altura);
      rest(5);
      if(++flash == 150)
        flash = 0;
   }
 clear_to_color(screen, 0x000000);
}

