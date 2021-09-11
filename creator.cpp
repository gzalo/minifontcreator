#include <sdl/sdl.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int fuente[8][8];
SDL_Surface *pantalla;

int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cerr << "Error al iniciar SDL" << endl;
		return -1;
	}
	pantalla = SDL_SetVideoMode( 8*32, 8*32, 32, SDL_SWSURFACE );
	
	if(pantalla == NULL){
		cerr << "Error al crear la superficie de video" << endl;
	}
	
	SDL_WM_SetCaption("Editor de fuentes",NULL);
	
	bool cerrado=false;	
	int botonApretado = 0;
			
	while(!cerrado){
		SDL_Event event;
		while(SDL_PollEvent(&event)){ 
			if(event.type == SDL_QUIT)
				cerrado = true;
			if(event.type == SDL_MOUSEBUTTONDOWN){
				if(event.button.button == SDL_BUTTON_LEFT)
					botonApretado = 1;
				else if(event.button.button == SDL_BUTTON_RIGHT)
					botonApretado = 2;	
			}
			
			if(event.type == SDL_MOUSEBUTTONUP)
				botonApretado = 0;
			
			if(botonApretado !=0){ 
				int posX = event.motion.x; 
				int posY = event.motion.y; 
				if(posX<32*8 && posY<32*8){
					int celdaX = posX/32;
					int celdaY = posY/32;
					
					if(botonApretado == 1){
						fuente[celdaY][celdaX] = 1;
					}else{
						fuente[celdaY][celdaX] = 0;
					}
				}
			}
		}
		
		for(int y=0;y<8;y++){
			for(int x=0;x<8;x++){
			
				SDL_Rect rect;
				rect.x = x*32;
				rect.y = y*32;
				rect.h = 32;
				rect.w = 32;
				
				if(fuente[y][x]==0){
					SDL_FillRect(pantalla,&rect,0x00FFFFFF);
				}else{
					SDL_FillRect(pantalla,&rect,0x00000000);
				}
			}
		}
		
		SDL_Flip(pantalla);
		SDL_Delay(1);
	}
	ofstream of("salida.txt");
	
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			of << fuente[y][x] << ",";
		}
	}
	
	of.close();
	SDL_Delay(100);
	system("notepad salida.txt");
	
	SDL_Quit();
	
	return 0;
}
