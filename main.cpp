#include <iostream>
#include <fstream>
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "Tile.h"
#include "Tileset.h"
#include "NPCmanager.h"
#include "ProjsManager.h"

using namespace std;
using namespace GamesEngineeringBase;

const int maxSize = 50;

int main() {
    // Create a canvas window
    Window canvas;
    canvas.create(768, 768, "GE");

    //SoundManager soundManager;
    //soundManager.loadMusic("Resources/battle 16bit.wav");
    //soundManager.playMusic();

    Player hero(672, 672, "Resources/down0.png");
    Timer timer;
    Camera camera(canvas);
    World world(canvas);
    NPCmanager npcs;
    ProjsManager p;

    bool running = true; // Variable to control the main loop's running state.
    bool playerStartsAttack = false;

    while (running)
    {
        // Check for input (key presses or window events)
        canvas.checkInput();

        // Clear the window for the next frame rendering
        canvas.clear();

        float dt = timer.dt();
        hero.update(dt, canvas, world, camera);

        Vec2 playerPos = hero.getWorldPos();
        camera.update(playerPos);

        npcs.checkNPCPlayerCollision(hero);
        npcs.update(dt, playerPos,camera);

        NPC* closestNPC = npcs.getClosestNPCtoPlayer(hero);
        npcs.setProjectiles(dt, hero, camera);

        playerStartsAttack = npcs.getIsAnyAggroActive();
        if(playerStartsAttack) hero.updateProjectiles(dt, *closestNPC, camera);
        
        Vec2 camPos = camera.getCameraPos();

        world.draw(canvas,camPos);    
        hero.draw(canvas);
        hero.drawFlicker(canvas, playerFlickerColor);
        npcs.draw(canvas);

        npcs.drawProjectiles(canvas);
        if (playerStartsAttack) hero.drawProjectiles(canvas, playerProjWidth, playerProjColor);

        canvas.present();
    }

    return 0;
}
