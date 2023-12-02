// En Linux compilar con:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -lSDL2_image -ldl

// Bibliotecas estándar de C++
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SDLApp.hpp"
#include "TexturedRectangle.hpp"
#include "AnimatedSprite.hpp"
#include "GameEntity.hpp"
#include "ResourceManager.hpp"
#include "Vector2D.hpp"
#include "Sound.hpp"
#include "DynamicText.hpp"

// Posibilidad de crear nuestra aplicación como global
SDLApp* app;

// Crear dos objetos para renderizar
// Eventualmente, querremos algún tipo de fábrica
// para gestionar la creación de objetos en nuestra aplicación...
GameEntity* leftpaddle;
GameEntity* rightpaddle;
GameEntity* ball;

Sound* CollisionSound;
Sound* ScoreSound;

struct GameState{
    float movementSpeed;
    float ballSpeed;
    int ballXDirection;
    int ballYDirection;
    int leftScore;
    int rightScore;
};

// Almacena el estado global del juego actual
GameState* gameState;

// Maneja el movimiento de la paleta izquierda
void HandleLeftPaddle(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int leftpaddlex  =  leftpaddle->GetTexturedRectangle().GetPositionX();
    int leftpaddley  =  leftpaddle->GetTexturedRectangle().GetPositionY();
    if(state[SDL_SCANCODE_W]){
        leftpaddley -= gameState->movementSpeed;
        leftpaddle->SetPosition(leftpaddlex,leftpaddley);
    }
    else if(state[SDL_SCANCODE_S]){
        leftpaddley += gameState->movementSpeed;
        leftpaddle->SetPosition(leftpaddlex,leftpaddley);
    }
}

// Maneja el movimiento de la paleta derecha
void HandleRightPaddle(){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int rightpaddlex = rightpaddle->GetTexturedRectangle().GetPositionX();
    int rightpaddley = rightpaddle->GetTexturedRectangle().GetPositionY();

    if (state[SDL_SCANCODE_UP]) {
        rightpaddley -= gameState->movementSpeed;
        rightpaddle->SetPosition(rightpaddlex,rightpaddley);
    }
    else if (state[SDL_SCANCODE_DOWN]) {
        rightpaddley += gameState->movementSpeed;
        rightpaddle->SetPosition(rightpaddlex,rightpaddley);
    }

}

// Función de devolución de llamada para manejar eventos
void HandleEvents(){
    SDL_Event event;

    // (1) Manejar la entrada
    // Iniciar nuestro bucle de eventos
    while(SDL_PollEvent(&event)){
        // Manejar cada evento específico
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){
            app->StopAppLoop();
        }
    }
    // Manejar el movimiento de las paletas
    HandleLeftPaddle();
    HandleRightPaddle();
}

// Posiciona la pelota en el centro de la cancha
void SetBallPositionCenter(){
    int ballXposition=app->GetWindowWidth()/2-(ball->GetTexturedRectangle().GetWidth()/2);
    int ballYposition=app->GetWindowHeight()/2-(ball->GetTexturedRectangle().GetHeight()/2);

    // Establecer la posición de la pelota
    ball->SetPosition(ballXposition,ballYposition);
}

// Maneja la colisión con las paletas
void HandlePaddleCollision(){
    // Obtener la posición de la pelota y luego
    // la actualizaremos en función de la dirección en la que se mueve la pelota
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();

    // Detección de colisión con una paleta
    if(ballXposition >= 20 &&
       gameState->ballXDirection == -1 &&
       leftpaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    { 
        gameState->ballXDirection = 1;
        CollisionSound->PlaySound();
        // Detectar dónde ocurrió la colisión
        int paddleMidPoint = leftpaddle->GetTexturedRectangle().GetPositionY()+100;
        if(paddleMidPoint <= ballYposition){
            gameState->ballYDirection = -1; 
        }else if(paddleMidPoint > ballYposition){
            gameState->ballYDirection =  1; 
        }
    }
    else if(ballXposition <=610 && 
            gameState->ballXDirection == 1 &&
            rightpaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    { 
        gameState->ballXDirection = -1;
        CollisionSound->PlaySound();
        // Detectar dónde ocurrió la colisión
        int paddleMidPoint = rightpaddle->GetTexturedRectangle().GetPositionY()+100;
        if(paddleMidPoint <= ballYposition){
            gameState->ballYDirection = -1; 
        }else if(paddleMidPoint > ballYposition){
            gameState->ballYDirection = 1; 
        }
    }

    // Establecer la posición de la pelota
    ball->SetPosition(ballXposition,ballYposition);
}

// Maneja los límites a lo largo del eje x e y del tablero de juego
void HandleBoundariesAndScoring(){
    // Obtener la posición de la pelota y luego
    // la actualizaremos en función de la dirección en la que se mueve la pelota
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();

    // Establecer los límites de la pelota (para que no salga del campo de juego)
    if(ballYposition > app->GetWindowHeight()){
        gameState->ballYDirection = -1;
    }else if(ballYposition < 0){
        gameState->ballYDirection = 1;
    }
    // Establecer la posición de la pelota
    ball->SetPosition(ballXposition,ballYposition);

    // Manejar el caso de puntuación
    // La pelota se centrará nuevamente en la pantalla si
    // se produce una puntuación
    if(ballXposition > app->GetWindowWidth() + 80){
        ScoreSound->PlaySound();
        gameState->ballXDirection = -1;
        gameState->leftScore+=1;
        // Recentrar la pelota al inicio
        SetBallPositionCenter();
    }else if(ballXposition < -100){
        ScoreSound->PlaySound();
        gameState->ballXDirection = 1;
        gameState->rightScore+=1;
        // Recentrar la pelota al inicio
        SetBallPositionCenter();
    }

}


// Maneja el movimiento de la pelota y su dirección
void HandleBallMoving(){
    // Obtener la posición de la pelota y luego
    // la actualizaremos en función de la dirección en la que se mueve la pelota
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();
    // Mover la pelota de izquierda a derecha
    if(gameState->ballXDirection == 1 ){
        ballXposition+= gameState->movementSpeed;
    }else{
        ballXposition-= gameState->movementSpeed;
    }
    // Mover la pelota de arriba a abajo
    if(gameState->ballYDirection == 1 ){
        ballYposition+= gameState->movementSpeed;
    }else{
        ballYposition-= gameState->movementSpeed;
    }

    // Establecer la posición de la pelota
    ball->SetPosition(ballXposition,ballYposition);
}

// Función de actualización
void HandleUpdate(){
    // Obtener la posición de la pelota y luego
    // la actualizaremos en función de la dirección en la que se mueve la pelota
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();
    // Manejar el movimiento de la pelota
    HandleBallMoving();
    // Manejar los límites y la puntuación
    HandleBoundariesAndScoring();
    // Manejar la colisión con las paletas
    HandlePaddleCollision();
    
    // Un poco de trampa, pero queremos detener
    // nuestros sonidos después de cierta duración.
    static int currentTime   = SDL_GetTicks();
    static int lastTime      = SDL_GetTicks();
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1000) {
        ScoreSound->StopSound();
        CollisionSound->StopSound();
        lastTime = currentTime;
    }
}

// Maneja el renderizado de las entidades del juego
void HandleRendering(){    
    // Renderizar nuestros objetos
    leftpaddle->Render();
    rightpaddle->Render();
    ball->Render();
    // Renderizar el texto después de dibujar los objetos
    DynamicText leftScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf",32);
    DynamicText rightScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf",32);

    std::string lScore = "izquierda: " + std::to_string(gameState->leftScore);
    std::string rScore= "derecha: " + std::to_string(gameState->rightScore);

    leftScore.DrawText(app->GetRenderer(),lScore,0,0,100,50);
    rightScore.DrawText(app->GetRenderer(),rScore,500,0,100,50);
}

// Punto de entrada del programa
int main(int argc, char* argv[]){
    // Configurar la aplicación SDL
    const char* title = "Ping Pong";
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO ,title, 20,20,640,480);
    app->SetMaxFrameRate(16);

    // Crear objetos en nuestra escena
    leftpaddle = new GameEntity(app->GetRenderer());
    leftpaddle->AddTexturedRectangleComponent("./assets/images/leftpaddle.bmp");
    leftpaddle->GetTexturedRectangle().SetDimensions(20,200);
    leftpaddle->AddBoxCollider2D();
    leftpaddle->GetBoxCollider2D(0).SetDimensions(leftpaddle->GetTexturedRectangle().GetWidth(), leftpaddle->GetTexturedRectangle().GetHeight());
    leftpaddle->SetPosition(10,200);

    rightpaddle = new GameEntity(app->GetRenderer());
    rightpaddle->AddTexturedRectangleComponent("./assets/images/rightpaddle.bmp");
    rightpaddle->GetTexturedRectangle().SetDimensions(20,200);
    rightpaddle->AddBoxCollider2D();
    rightpaddle->GetBoxCollider2D(0).SetDimensions(rightpaddle->GetTexturedRectangle().GetWidth(), rightpaddle->GetTexturedRectangle().GetHeight());
    rightpaddle->SetPosition(610,200);

    ball = new GameEntity(app->GetRenderer());
    ball->AddTexturedRectangleComponent("./assets/images/ball.bmp");
    ball->AddBoxCollider2D();
    ball->GetTexturedRectangle().SetDimensions(20,20);
    ball->GetBoxCollider2D(0).SetDimensions(ball->GetTexturedRectangle().GetWidth(), ball->GetTexturedRectangle().GetHeight());
    ball->SetPosition(app->GetWindowWidth()/2,app->GetWindowHeight()/2);

    // Configurar nuestros sonidos
    CollisionSound = new Sound("./assets/sounds/Collide.wav");
    // TODO: Por ahora, configuramos el dispositivo 'por sonido'
    //       'puede' tener sentido si tenemos varios dispositivos, o
    //       dispositivos de 'captura', probablemente querremos refactorizar
    //       esto en algún momento.
    CollisionSound->SetupDevice();
    
    // Configurar el sonido de puntuación
    ScoreSound= new Sound("./assets/sounds/Score.wav");
    ScoreSound->SetupDevice();

    // Configurar el estado del juego
    gameState = new GameState;
    gameState->movementSpeed    = 5.0f;
    gameState->ballSpeed        = 2.0f;
    gameState->ballXDirection   = 1;
    gameState->ballYDirection   = 1;
    gameState->leftScore        = 0;
    gameState->rightScore       = 0;

    // Establecer las funciones de devolución de llamada
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);
    // Ejecutar nuestra aplicación hasta que se termine
    app->RunLoop();

    // Limpiar nuestra aplicación
    delete app;
    delete leftpaddle;
    delete rightpaddle;
    delete ball;
    delete CollisionSound;
    delete ScoreSound;

    return 0;
}
