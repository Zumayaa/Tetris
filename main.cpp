#include <iostream>
#include <allegro.h>
#include <time.h>
#include "Tetris_allegro.h"

using namespace std;

int main(){
    //Iniciar
    int musica;
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, anchura, altura, 0, 0);

    //Inicializar Audio
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0){
        allegro_message("Error: inicilizando sistema de sonido\n%s\n", allegro_error);
        return 1;
    }
    set_volume(50, 50);

    //BITMAPS
    BITMAP * buffer = create_bitmap(anchura, altura);
    BITMAP * muroH = load_bitmap("Imagenes/suelo.bmp", NULL);
    BITMAP * muroV = load_bitmap("Imagenes/pacolor4.bmp", NULL);
    BITMAP * marco = load_bitmap("Imagenes/marco.bmp", NULL);

    BITMAP * img_b = load_bitmap("Imagenes/ladrillos.bmp", NULL);
    BITMAP * elimn = load_bitmap("Imagenes/elimina_piezas.bmp", NULL);
    BITMAP * img_texto = load_bitmap("Imagenes/textos.bmp", NULL);
    BITMAP * img_texto2 = load_bitmap("Imagenes/textos.bmp", NULL);
    BITMAP * img_num = load_bitmap("Imagenes/numeros.bmp", NULL);
    BITMAP * goBmp = load_bitmap("Imagenes/GameOver.bmp", NULL);
    BITMAP * p = load_bitmap("Imagenes/portada.bmp", NULL);

    portada(p);
    delete p;


    //SAMPLES
    SAMPLE * col = load_wav("Sonidos/colocar_bloque.wav");
    SAMPLE * eli = load_wav("Sonidos/line_clear.wav");
    SAMPLE * rot = load_wav("Sonidos/figura_rota.wav");

    MIDI * musica_fondoa = load_midi("Sonidos/track a.mid");
    MIDI * musica_fondob = load_midi("Sonidos/track b.mid");
    MIDI * musica_fondoc = load_midi("Sonidos/track c.mid");
    MIDI * musica_fondod = load_midi("Sonidos/track d.mid");
    MIDI * velocidad_alta = load_midi("Sonidos/speed.mid");




    saltura:
    //Integers
    int val = 7;
    int vcaida = val;
        int puntos = 0, nivel = 0;

        srand(time(NULL));
    musica =  1 + rand() % 4;
    if (musica == 1){ play_midi(musica_fondoa, 1);
    }
    else if (musica == 2){ play_midi(musica_fondob, 1);
    }
    else if (musica == 3) {play_midi(musica_fondoc, 1);
    }
    else if (musica == 4) {play_midi(musica_fondod, 1);
    }


    int aux = 0, pb = 0;
    int aleatorio, fila, cfila, fin;

    int ese = 0, zeta = 0, ele = 0, cuadrado = 0, palo = 0, ele2 = 0, te = 0;




    //Booleanos
    bool colb = false;
    bool coli = false, cold = false;
    bool gameOver = false, reproducir;

    //Bloques
    Bloque b_prin = { 5, 2, Ladrillo};
    Bloque b_prin_sig = { 15, 5, Ladrillo };
    Bloque bl1[3] = { {  0, -1, Ladrillo } , {  1, -1, Ladrillo } , {  0, 1, Ladrillo} };
    Bloque bl2[3] = { {  0,  1, Ladrillo } , {  1,  0, Ladrillo } , { -1, 0, Ladrillo} };
    Bloque bl3[3] = { {  0, -1, Ladrillo } , { -1, -1, Ladrillo } , { -1, 0, Ladrillo} };
    Bloque bl4[3] = { {  0, -1, Ladrillo } , {  0,  1, Ladrillo } , {  0, 2, Ladrillo} };
    Bloque bl5[3] = { {  0, -1, Ladrillo } , {  0,  1, Ladrillo } , {  1, 1, Ladrillo} };
    Bloque bl6[3] = { {  0, -1, Ladrillo } , {  1, -1, Ladrillo } , { -1, 0, Ladrillo} };
    Bloque bl7[3] = { { -1, -1, Ladrillo } , {  0, -1, Ladrillo } , {  1, 0, Ladrillo} };


    //Generar piezas aleatorias0
    pieza pAc(b_prin, bl1, 0);
    srand(time(NULL));
    aleatorio = 1 + rand() % 7;
    if(aleatorio == 1) pAc.setBls(bl1), pAc.setColor(color1);
    else if(aleatorio == 2) pAc.setBls(bl2), pAc.setColor(color6);
    else if(aleatorio == 3) pAc.setBls(bl3), pAc.setColor(color5);
    else if(aleatorio == 4) pAc.setBls(bl4), pAc.setColor(color3);
    else if(aleatorio == 5) pAc.setBls(bl5), pAc.setColor(color4);
    else if(aleatorio == 6) pAc.setBls(bl6), pAc.setColor(color2);
    else if(aleatorio == 7) pAc.setBls(bl7), pAc.setColor(color7);


    pieza pSig(b_prin_sig, bl1, 0);
    aleatorio = 1 + rand() % 7;
    if(aleatorio == 1) pSig.setBls(bl1), pSig.setColor(color1);
    else if(aleatorio == 2) pSig.setBls(bl2), pSig.setColor(color6);
    else if(aleatorio == 3) pSig.setBls(bl3), pSig.setColor(color5);
    else if(aleatorio == 4) pSig.setBls(bl4), pSig.setColor(color3);
    else if(aleatorio == 5) pSig.setBls(bl5), pSig.setColor(color4);
    else if(aleatorio == 6) pSig.setBls(bl6), pSig.setColor(color2);
    else if(aleatorio == 7) pSig.setBls(bl7), pSig.setColor(color7);


    limpiar_mapa();
    while(!key[KEY_ESC] && gameOver == false){
        clear_to_color(buffer, 0x000000);
        mostrar_muros(buffer, marco);
        mostrar_datos(buffer, img_texto, img_num, puntos, nivel);
        mostrar_dat  (buffer, img_num, ese, zeta);
        mostrar_dat1 (buffer, img_num, ele, cuadrado);
        mostrar_dat2 (buffer, img_num, palo, ele2);
        mostrar_dat3 (buffer, img_num, te);
     //   mostrar_marco(buffer, marco);
        mostrar_mapa(buffer, img_b);

        if(pAc.colision_abajo()) colb = true;
        if(pAc.colision_derec()) cold = true;
        if(pAc.colision_izqui()) coli = true;

        //Bajar pieza
        if(pb++ >= vcaida && !colb){
            pb = 0;
            pAc.incrY(1);
        }

        //Colosison abajo
        if(colb){
            play_sample(col, 100, 150, 1000, 0);
            pAc.insertar_mapa();
            fila = pAc.getY() + 2;
            while(fila > 19)
                fila--;
            fin = fila - 4;
            cfila = fila;
            while(fila >= fin){
                if(pAc.fila_llena(fila)){
                    play_sample(eli, 100, 150, 1000, 0);
                    for(int i=1; i<11; i++)
                        blit(elimn, buffer, 0, 0, i* Tbloque, fila* Tbloque, 25, 25);
                    blit(buffer, screen, 0, 0, 0, 0, anchura, altura);
                    for(int i=1; i<11; i++){
                        blit(elimn, buffer, 25, 0, i* Tbloque, fila* Tbloque, 25, 25);
                        blit(buffer, screen, 0, 0, 0, 0, anchura, altura);
                        blit(elimn, buffer, 50, 0, i*Tbloque, fila * Tbloque, 25, 25);
                        rest(8);
                    }
                    puntos++;
                    if(puntos % 5 == 0){
                        nivel++;
                        val=val-0.7;

                   if (nivel >= 10){
                        play_midi(velocidad_alta, 1);
                        }

                    }

                }
                fila--;
            }
            fila = cfila;
            while(fila >= fin){
                if(pAc.fila_llena(fila))
                    eliminar_fila(fila);
                else
                    fila--;
            }
            if(pAc.getY() < 3){
                gameOver = true;
                break;
            }
            b_prin.x = 5, b_prin.y = 2;
            pAc = pSig;
            pAc.setBPrin(b_prin);
            aleatorio = 1 + rand() % 7;
            if(aleatorio == 1) pSig.setBls(bl1), pSig.setColor(color1), ele++;
            else if(aleatorio == 2) pSig.setBls(bl2), pSig.setColor(color6), te++;
            else if(aleatorio == 3) pSig.setBls(bl3), pSig.setColor(color5), cuadrado++;
            else if(aleatorio == 4) pSig.setBls(bl4), pSig.setColor(color3), palo++;
            else if(aleatorio == 5) pSig.setBls(bl5), pSig.setColor(color4), ele2++;
            else if(aleatorio == 6) pSig.setBls(bl6), pSig.setColor(color2), ese++;
            else if(aleatorio == 7) pSig.setBls(bl7), pSig.setColor(color7), zeta++;

            colb = false;
            rest(100);
        }



        //Detectando el teclado
        if(key[KEY_RIGHT] && !cold)
            pAc.incrX(1);
        if(key[KEY_LEFT] && !coli)
            pAc.incrX(-1);
        if(key[KEY_UP]){
            reproducir = true;
            pieza pAux = pAc;
            pAc.rotar();
            pAc.incrX(1);
            if(pAc.colision_izqui()){
                pAc = pAux;
                reproducir = false;
            }
            pAc.incrX(-2);
            if(pAc.colision_derec()){
                pAc = pAux;
                reproducir = false;
            }
            pAc.incrX(1);
            if(reproducir)
                play_sample(rot, 100, 150, 1000, 0);
        }
        if(key[KEY_DOWN])
            vcaida = 0.1;

        if(key[KEY_SPACE])
            vcaida = -0.00000000001;


        if(++aux >= val){
            vcaida = val;
            aux = 0;
        }

        pAc.mostrar_pieza(buffer, img_b);
        pSig.mostrar_pieza(buffer, img_b);
        blit(buffer, screen, 0, 0, 0, 0, anchura, altura);
        // Reiniciar variables
        cold = false, coli = false;
        rest(50);
    }

    if(gameOver){
        while(!key[KEY_ESC]){
            blit(goBmp, buffer, 0, 0, 29, 175, 243, 108);
            if(key[KEY_ENTER])
                goto saltura;
            blit(buffer, screen, 0, 0, 0, 0, anchura, altura);
            rest(5);
        }
    }

    return 0;
}
END_OF_MAIN();
