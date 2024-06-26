#pragma once

#include "enemy.h"
#include "alpha.h"
#include "beta.h"
#include "gamma.h"
#include "monster.h"
#include "dragon.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

class Level {
private:
    int levelNo;
public:
    Texture EnemyTexAlpha;
    Texture EnemyTexBeta;
    Texture EnemyTexGamma;
    Texture EnemyTexMonster;
    Texture EnemyTexDragon;

    vector<Enemy*> enemies;
    Level(int levelNumber) : levelNo(levelNumber) {
        EnemyTexAlpha.loadFromFile("img/PNG/Enemies/enemyBlack3.png");
        EnemyTexBeta.loadFromFile("img/PNG/Enemies/enemyBlue3.png");
        EnemyTexGamma.loadFromFile("img/PNG/Enemies/enemyRed3.png");
        EnemyTexMonster.loadFromFile("img/monster1.png");
        EnemyTexDragon.loadFromFile("img/dragon.png");
    }


    void generateEnemies(char shape, int currentLevel) {
        float speed = 0.f;
        if (currentLevel == 1)
            speed = 10.f;
        else if (currentLevel == 2)
            speed = 50.f;
        else if (currentLevel == 3)
            speed = 90.f;

        switch (shape) {
        case 'r':
            rectangleEnemiesFilles(speed);
            break;
      
        case 't':
            triangleEnemiesFilled(speed);
            break;

        case 'c':
            crossEnemies(speed);
            break;

        case 'f':
            circleEnemies(speed);
            break;
            
        case 'm':
            monsterEnemy();
            break;

        case 'd':
            dragonEnemy();
            break;
        
        }

    }

    void drawEnemies(RenderWindow& window) {
        for (auto enemy : enemies) {
            window.draw(enemy->sprite);
        }
    }

    void rectangleEnemiesFilles(float speed) {

        int rows = 6;
        int cols = 4;
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                Enemy* e = nullptr;
                if (j == 1) {
                    e = new Alpha(EnemyTexAlpha, 100, "img/PNG/Effects/fire17.png", speed);
                }
                else if (j == 2) {
                    e = new Alpha(EnemyTexAlpha, 100, "img/PNG/Effects/fire17.png", speed);
                }
                else if (j == 3) {
                    e = new Alpha(EnemyTexAlpha, 100, "img/PNG/Effects/fire17.png", speed);
                }
                e->sprite.setPosition(i * 120, j * 110);
                enemies.push_back(e);
            }
        }
    }

    void triangleEnemiesFilled(float speed) {
        int rows = 4;
        int cols = 7;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j <= i; j++) {
                Enemy* e = nullptr;
                if (i % 3 == 0) {
                    e = new Beta(EnemyTexBeta, 100, "img/PNG/Effects/fire17.png", speed);
                }
                else if (i % 3 == 1) {
                    e = new Beta(EnemyTexBeta, 100, "img/PNG/Effects/fire17.png", speed);
                }
                else if (i % 3 == 2) {
                    e = new Beta(EnemyTexBeta, 100, "img/PNG/Effects/fire17.png", speed);
                }
                float offsetX = (cols - i) * 52; 
                float offsetY = 62 * i;
                e->sprite.setPosition((j * 120) + offsetX, (i + 1) * 50 + offsetY);
                enemies.push_back(e);
            }
        }
    }

    void crossEnemies(float speed) {
        int rows = 5;
        int cols = 5;
        int enemyWidth = 100; 

        for (int i = 0; i < rows; i++) {
            int startingX = (780 - cols * enemyWidth) / 2; 

            for (int j = 0; j < cols; j++) {
                Enemy* e = nullptr;
                if (i == j || i + j == rows - 1) { 
                    e = new Gamma(EnemyTexAlpha, 100, "img/PNG/Effects/fire17.png", speed);
                    e->sprite.setPosition(startingX + j * enemyWidth, (i + 1) * 110);
                    enemies.push_back(e);
                }
            }
        }
    }

    void circleEnemies(float speed) {
        int numEnemies = 10;
        float centerX = 700 / 2;
        float centerY = 700 / 2; 
        float radius = 200; 
        float angleIncrement = 360.0f / numEnemies; 

        for (int i = 0; i < numEnemies; i++) {
            float angle = i * angleIncrement;

            float x = centerX + radius * std::cos(angle * 3.14159 / 180); // Convert degrees to radians
            float y = centerY + radius * std::sin(angle * 3.14159 / 180);

            Enemy* e = new Alpha(EnemyTexAlpha, 100, "img/PNG/Effects/fire17.png", speed);
            e->sprite.setPosition(x, y);
            enemies.push_back(e);
        }
    }

    void monsterEnemy() {
        enemies.clear();
        Enemy* e = nullptr;
        e = new Monster(EnemyTexMonster, 600, "img/PNG/Effects/fire08.png", 2500.0f, 0.01f);
        e->sprite.setPosition(390, 100);
        enemies.push_back(e);
    }

    void dragonEnemy() {
        enemies.clear();
        Enemy* e = nullptr;
        e = new Dragon(EnemyTexDragon, 600, "img/PNG/Effects/fire08.png", 800.0f, 0.01f);
        e->sprite.setPosition(220, 100);
        enemies.push_back(e);
    }

    //No of Enemies to determine the wave ending
    int noEmeny() {
        return enemies.size();
    }
     
    ~Level() {
        for (auto enemy : enemies) {
            delete enemy;
        }
    }
};
