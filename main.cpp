#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

SDL_Texture* createButtonTexture(SDL_Renderer* renderer, const SDL_Color& color, int width, int height) {
    // Créer une surface transparente
    SDL_Surface* buttonSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_SetSurfaceBlendMode(buttonSurface, SDL_BLENDMODE_BLEND);

    // Remplir la surface avec la couleur du contour
    SDL_FillRect(buttonSurface, nullptr, SDL_MapRGBA(buttonSurface->format, 0, 0, 0, 0));
    SDL_FillRect(buttonSurface, nullptr, SDL_MapRGBA(buttonSurface->format, color.r, color.g, color.b, color.a));

    // Convertir la surface en texture
    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);

    // Détruire la surface maintenant que la texture est créée
    SDL_FreeSurface(buttonSurface);

    return buttonTexture;
}

SDL_Rect createButton(int x, int y, int width, int height, SDL_Texture* buttonTexture, SDL_Renderer* renderer) {
    // Définir les coordonnées et les dimensions du bouton
    SDL_Rect buttonRect = {x, y, width, height};

    // Dessiner le bouton sur le rendu
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);

    return buttonRect;
}

int main(int argc, char** argv) {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        return 1;
    }

    // Création d'une fenêtre
    SDL_Window *fenetre = SDL_CreateWindow(
        "Ma fenêtre SDL",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (fenetre == nullptr) {
        std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Création d'un renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    // Créer la texture du bouton une fois en dehors de la boucle
    SDL_Texture* buttonTexture = createButtonTexture(renderer, {255, 0, 0, 255}, 50, 50);

    // Boucle principale
    SDL_Event evenement;
    int terminer = 0;

    while (!terminer) {
        while (SDL_PollEvent(&evenement)) {
            if  (evenement.type == SDL_QUIT) {
                terminer = 1;
            }
        }

        // Effacer le rendu
        SDL_RenderClear(renderer);

        // Dessiner le bouton
        SDL_Rect buttonRect = createButton(100, 100, 50, 50, buttonTexture, renderer);  // Rouge

        // Logique de jeu ou de traitement ici

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
