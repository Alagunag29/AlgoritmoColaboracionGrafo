#include <allegro.h>


typedef struct nodo{
    int adyacencia;
    char color;        
}nodo;

int tope = 0;
nodo vector[7];
int matriz[7][7];


bool disponible = true, terminar = false;
int amarillo, verde, rojo, blanco, veces = 0;
int uno, dos, tres, cuatro, cinco, seis, siete;
int col, n = 0, x =150, y= 230;
int m=0, s=0, ml=0;


BITMAP *buffer;
BITMAP *fondo;
BITMAP *raton;
BITMAP *imgA;
BITMAP *imgR;
BITMAP *imgV;
BITMAP *boton1;
BITMAP *boton2;      
 
 
// app
void init(void);
void load();
int controlBotones(void);
void controlOpciones();
void pintarPunto(int);
void pintarColo(int);
void pintadaInicial(void);


///logica
void inicializarMatriz(void);
void llenarMatrizArcos(void);
void cambioBotones(void);
int correrVecMat(int);
bool verificacion(void);
void dibujoCronometro(void);
void cronometro(void);

int main(void)
{
    init();
    inicializarMatriz();
    llenarMatrizArcos();
    int seleccion = 0;
    while(!key[KEY_ESC] && !terminar && m < 1){
         draw_sprite(screen, buffer, 0, 0);
         clear(buffer);
         
         draw_sprite(buffer, fondo, 0, 0);
         draw_sprite(buffer, imgA, 600, 420);
         draw_sprite(buffer, imgR, 710, 420);
         draw_sprite(buffer, imgV, 810, 420);
         draw_sprite(buffer, boton1, 800, 10);

         //seleccion = controlBotones();
         controlOpciones();        
         cambioBotones();
         dibujoCronometro();
         draw_sprite(buffer, raton, mouse_x, mouse_y); 
           
          
    }
    if (m > 1)
       allegro_message("Se acabo el tiempo. Perdio!!!");
       
    return 0;

}
END_OF_MAIN();

// inicializar allegro y los componente de la app
void init()
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 520, 0, 0);
    if (res != 0){
        allegro_message(allegro_error);
        exit(-1);      
    }
    install_timer();
    install_keyboard();
    install_mouse();
    srand(time(0));
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_volume(255, 255);
    load();
}

void load(void)
{
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    fondo = load_bitmap("imagenes/fondo.bmp", NULL);
    raton = load_bitmap("imagenes/raton.bmp", NULL);
    imgA  = load_bitmap("imagenes/amarillo.bmp", NULL);
    imgR  = load_bitmap("imagenes/rojo.bmp", NULL);
    imgV  = load_bitmap("imagenes/verde.bmp", NULL);
    boton1 = load_bitmap("imagenes/boton1.bmp", NULL);
    boton2 = load_bitmap("imagenes/boton2.bmp", NULL);
    amarillo = makecol (255, 247,0);
    rojo = makecol (255, 0, 0);
    verde = makecol(100, 255, 50);
    blanco = makecol(255, 255, 255);
    uno = dos = tres = cuatro = cinco = seis = siete = blanco;    
   // srand(time(NULL));
}

void cambioBotones(void){
     bool estado;
     if (mouse_x > 830 && mouse_x  < 967 && mouse_y > 38 && mouse_y < 78 )
     {
          draw_sprite(buffer, boton2, 800, 10);
          if (mouse_b & 1 ){
               terminar = true;
               estado = verificacion();
               if ( !estado)
               {
                   allegro_message("malo");    
               }
               else
               {
                   allegro_message("bueno");
               }
          }
     }
}


int controlBotones(void)
{
    if (!disponible)
        return -1;
    if (mouse_b&1 && veces < 7){
        rest(300);
        if(getpixel(buffer, mouse_x, mouse_y) == amarillo)
        {  
            veces++;
            vector[veces-1].adyacencia = veces;
            vector[veces-1].color = 'A';
            return amarillo;
        }else if (getpixel(buffer, mouse_x, mouse_y) == rojo)
        {     
              veces++;
              vector[veces-1].adyacencia = veces;
              vector[veces-1].color = 'R';
              return rojo;
        }else if (getpixel(buffer, mouse_x, mouse_y) == verde)
        {
              veces++;
              vector[veces-1].adyacencia = veces;
              vector[veces-1].color = 'V';
              return verde;
        }
    } 
    return 0;
}

void controlOpciones()
{ 
     int col = controlBotones();
     if(col > 0 && veces <= 7)
     {
            if (veces == 1){
                uno = col;
            }else if (veces == 2){
                dos = col;
            }else if (veces == 3){
                tres = col;
            }else if (veces == 4){
                cuatro = col;
            }else if (veces == 5){
                cinco = col;
            }else if (veces == 6){
                seis = col;
            }else if (veces == 7){
                siete = col;
            }
            //circlefill(buffer, x, y, 30, col);
     }
     pintadaInicial();
}  


void pintadaInicial(void)
{
     circlefill(buffer, 150, 230, 32, siete);
     circlefill(buffer, 310, 140, 32, seis);
     circlefill(buffer, 460, 50, 32, cinco);
     circlefill(buffer, 610, 140, 32, cuatro);
     circlefill(buffer, 610, 290, 32, tres);
     circlefill(buffer, 460, 380, 32, dos); 
     circlefill(buffer, 310, 290, 32, uno);
 
}




// metodos de la lofica de la app
void inicializarMatriz()
{
     for (int i = 0; i < 7; i++)
     {
         for (int j = 0; j < 7; j++ )
         {
             matriz[i][j] = 0;
         }    
     }
} 

void llenarMatrizArcos(void){
     matriz[0][1] = 1; matriz[0][2] = 1; matriz[0][5] = 1; matriz[0][6] = 1;
     matriz[1][0] = 1; matriz[1][2] = 1; matriz[1][4] = 1;
     matriz[2][0] = 1; matriz[2][1] = 1; matriz[2][3] = 1;
     matriz[3][2] = 1; matriz[3][4] = 1; matriz[3][5] = 1;
     matriz[4][1] = 1; matriz[4][3] = 1; matriz[4][5] = 1;
     matriz[5][0] = 1; matriz[5][3] = 1; matriz[5][4] = 1; matriz[5][6] = 1;
     matriz[6][0] = 1; matriz[6][5] = 1;                                                                                           
}

int correrVecMat(int i)
{
    int sw = 0, j;
    for (j = 0; j < i && sw == 0; j++)
    {
        if (matriz[i][j] == 1)
        {
             if (vector[i].color == vector[j].color)
             {
                sw = 1; 
                //allegro_message(" %c ", vector[i].color);
             }
        }
    }
    
    return sw;
}

bool verificacion(void)
{
     //correr en vector y pasar a la matriz   
     int sw = 0;
     for(int i = 0; i < 7 && sw == 0; i++)
     {    
          sw = correrVecMat(i);        
     }
     if( sw == 0)
         return true;
     else 
         return false;
// true es que esta ok ; false grafo mal construido
}


//dibujoCronometro;
void dibujoCronometro(void){
     textprintf_ex(buffer, font, 10, 510, makecol(255, 100, 200), -1, "%d: %d: %d", m, s, ml );  
     rest(100);
     ml++;
     cronometro();          
}

// cronometro
void cronometro(void)
{
     if(ml > 10){
           s++;
           ml=0;
           if(s > 60)
           {
                m++;
                s=0;
                if(m>60){
                    m = 0;         
                }
           }
     }
}


