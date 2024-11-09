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

float timeElapsed = 0.f;

void getFPS(const float& dt) {
    float fps = 1 / dt;
    timeElapsed += dt;
    // output FPS every one second
    if (timeElapsed > 1.f) {
        cout << "FPS is : " << fps << endl;
        timeElapsed = 0.f;
    }
}

int main() {
    Window canvas;
    canvas.create(768, 768, "GE");

    Player hero(672, 672, "Resources/down0.png");
    Timer timer;
    Camera camera(canvas);
    World world(canvas);
    NPCmanager npcs;
    ProjsManager p;

    bool running = true; 
    bool playerStartsAttack = false;

    while (running)
    {
        // Check for input (key presses or window events)
        canvas.checkInput();

        // Clear the window for the next frame rendering
        canvas.clear();

        float dt = timer.dt();
        // output FPS once per second
        getFPS(dt);

// ---------------------- Update -----------------------------------------------------
        // update player movement
        hero.update(dt, canvas, world, camera);

        // update camera system
        Vec2 playerPos = hero.getWorldPos();
        camera.update(playerPos);

        // generate NPC array and update NPC movement
        npcs.update(dt, playerPos, camera);
        // update NPC's projectiles
        npcs.setProjectiles(dt, hero, camera);

        // check collision between each NPC and player
        npcs.checkNPCPlayerCollision(hero);
        
        // ----------------Player Attack------------------------
        if (hero.getIfApplyAOE()) {  
            // AOE attack---------------

        }
        else{ 
            // linear attack------------
            //check if any NPC is in player's attack range
            playerStartsAttack = npcs.getIfNPCinPlayerAttackRange();
            //if so, attack the closest NPC using projectiles
            if (playerStartsAttack) {
                // get one NPC which is closest to player
                NPC* closestNPC = npcs.getClosestNPCtoPlayer();
                // player LINEAR ATTACK -- launch projectiles
                hero.updateProjectiles(dt, *closestNPC, camera);
            }
        }

// ---------------------- Draw -------------------------------------------------------
        // draw map---------------------------------
        Vec2 camPos = camera.getCameraPos();
        world.draw(canvas,camPos); 

        // draw player -----------------------------
        hero.draw(canvas);
        // draw player's flicker effect when player is hit by projectile or collide with NPC
        hero.drawFlicker(canvas, playerFlickerColor);
        // draw player's projectiles when linear attack triggered
        if (playerStartsAttack) hero.drawProjectiles(canvas, playerProjWidth, playerProjColor);

        // draw NPC--------------------------------
        npcs.draw(canvas);
        // draw NPC's projectile if it's speed is zero
        npcs.drawProjectiles(canvas);


        canvas.present();
    }

    return 0;
}
