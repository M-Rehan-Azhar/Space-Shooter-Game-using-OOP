#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include "player.h"
#include "level.h"
#include "addons.h"
#include "powerup.h"
#include "fire.h"
#include "lives.h"
#include "danger.h"
#include <fstream>
#include <algorithm>

const char title[] = "OOP-Project, Spring-2024";

using namespace std;
using namespace sf;

class Game {
private:
    bool isPaused = false;
    Clock powerUpClock;
    Clock playerFireModeClock;
    Clock anouncerClock;
    bool isAnnouncer;
    bool isGameEnded = false;
public:
    Sprite background;
    Texture bg_texture;
    Text livesText;
    Text scoreText;
    Text AnnouncementText;
    Text playAgain;
    RectangleShape healthBar;
    Player* p;
    Level* level;
    int currentWave = 0;
    int currentLevel = 1;
    int noLives = 3;
    Font font;

    vector<Addons*> activeAddons;

    struct PlayerData {
        string name;
        int score;
    };

    Game() {
        p = new Player("img/player_ship.png", "img/PNG/Effects/fire05.png");
        bg_texture.loadFromFile("img/bg.jpg");
        background.setTexture(bg_texture);
        background.setScale(1, 1);
        //Load Font
        
        
        if (!font.loadFromFile("font/luckiestguy.ttf")) {
            cerr << "Error in font"; 
        }

        //Lives Text
        
        livesText.setFont(font);
        livesText.setString("Lives: " + noLives);
        livesText.setCharacterSize(23);
        livesText.setFillColor(Color::White);
        livesText.setPosition(50.0f, 10.0f); 

        //Score Text

        scoreText.setFont(font);
        scoreText.setString("Score: 0");
        scoreText.setCharacterSize(23); 
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(650.0f, 10.0f);

        // health bar

        healthBar.setSize(Vector2f(200, 12));
        healthBar.setPosition(50.0f, 750.0f);
        healthBar.setFillColor(Color::Green); 

        // Initialize Announcement Text
        AnnouncementText.setFont(font);
        AnnouncementText.setString("");
        AnnouncementText.setCharacterSize(24);
        AnnouncementText.setFillColor(Color::White);
        AnnouncementText.setPosition(350.f, 350.f);

        // Init Enemies

        level = new Level(currentLevel);
    }

    void start_game(RenderWindow& window, string playerName) {
        srand(time(0));
        Clock clock;

        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();

                if (e.type == Event::MouseButtonPressed) {
                    if (e.mouseButton.button == Mouse::Left) {
                        Vector2i mousePosition = Mouse::getPosition(window);


                        if (playAgain.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            restart_game(window);
                        }


                    }
                }

                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::P) {
                        isPaused = !isPaused;
                    }
                    else if (e.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }
            }

            if (!isPaused) {
                if (Keyboard::isKeyPressed(Keyboard::A)) p->move("l");
                if (Keyboard::isKeyPressed(Keyboard::D)) p->move("r");
                if (Keyboard::isKeyPressed(Keyboard::W)) p->move("u");
                if (Keyboard::isKeyPressed(Keyboard::S)) p->move("d");
                if (Keyboard::isKeyPressed(Keyboard::R)) restart_game(window);
                if (!isAnnouncer) {
                    p->fire(deltaTime);
                    p->pName = playerName;

                    for (auto& enemy : level->enemies) {
                        if (enemy->type == 4 || enemy->type == 1 || enemy->type == 2 || enemy->type == 3) {
                            enemy->move(deltaTime);
                        }
                            
                        enemy->fire(deltaTime, p);
                        enemy->displayHealth();
                    }

                    // Level StoryLine
                    if (level->noEmeny() == 0) {
                        if (currentWave == 1 && currentLevel == 1) {
                            newPhaseStart("Level 1 Starting..", 'r');
                        }
                        else if (currentWave == 2 && currentLevel == 1) {
                            newPhaseStart("Wave Starting..", 't');
                        }
                        else if (currentWave == 3 && currentLevel == 1) {
                            newPhaseStart("Wave Starting..", 'f');
                        }
                        else if (currentWave == 4 && currentLevel == 1) {
                            currentLevel++;
                            currentWave = 0;
                            newPhaseStart("Monster is Here", 'm');
                        }
                        else if (currentWave == 1 && currentLevel == 2) {
                            newPhaseStart("Level 2 Starting..", 'r');
                        }
                        else if (currentWave == 2 && currentLevel == 2) {
                            newPhaseStart("Wave Starting..", 'c');
                        }
                        else if (currentWave == 2 && currentLevel == 2) {
                            newPhaseStart("Wave Starting..", 't');
                        }
                        else if (currentWave == 3 && currentLevel == 2) {
                            newPhaseStart("Wave Starting..", 'r');
                        }
                        else if (currentWave == 4  && currentLevel == 2) {
                            level->generateEnemies('d', currentLevel);
                            currentLevel++;
                            currentWave = 0;
                            p->sprite.setPosition(400, 700);
                        }
                        else if (currentWave == 1 && currentLevel == 3) {
                            newPhaseStart("Level 3 Starting..", 'f');
                        }
                        else if (currentWave == 2 && currentLevel == 3) {
                            newPhaseStart("Wave Starting..", 'r');
                        }
                        else if (currentWave == 2 && currentLevel == 3) {;
                            newPhaseStart("Wave Starting..", 't');
                        }
                        else if (currentWave == 3 && currentLevel == 3) {
                            newPhaseStart("Monster is Here", 'm');
                        }
                        else if (currentWave == 4 && currentLevel == 3) {
                            level->generateEnemies('d', currentLevel);
                            currentLevel++;
                            currentWave = 0;

                        }

                        cout << "Current Wave: " << currentWave << endl;
                        currentWave++;
                    }

                    updateAddons(deltaTime);

                    window.clear(Color::Black);
                    window.draw(background);

                    window.draw(p->sprite);
                    for (auto& bullet : p->bullets) {
                        window.draw(bullet.sprite);
                    }

                    for (auto& enemy : level->enemies) {
                        window.draw(enemy->sprite);
                        window.draw(enemy->healthBar);
                        for (auto& bomb : enemy->bombs) {
                            window.draw(bomb.sprite);
                        }
                    }

                    displayPlayerHealthBar();
                    //TODO: Fix HealthBar
                    //window.draw(healthBar);

                    livesText.setString("Lives: " + to_string(int(p->pLives)));
                    scoreText.setString("Score: " + to_string(int(p->pScore)));

                    deductLife(&(p->pHealth));
                    level->drawEnemies(window);

                    for (auto& addon : activeAddons) {
                        window.draw(addon->sprite);
                    }

                    stopPowerUpMode();
                    stopPlayerFireMode();

                    playerEnemyCollision();
                    bulletCollision();
                    bombCollision();

                    window.draw(livesText);
                    window.draw(scoreText);
                }
                else {
                    window.clear(Color::Black);
                    window.draw(background);
                    Announcer(window);
                    window.draw(AnnouncementText);
                }

                window.display();

                if (p->pLives == 0) {
                    PlayerData pl;
                    pl.name = p->pName;
                    pl.score = p->pScore;
                    end_game(pl);
                }
            }
            else {
                window.clear(Color::Black);
                window.draw(background);
                window.draw(p->sprite);

                for (auto& bullet : p->bullets) {
                    window.draw(bullet.sprite);
                }

                for (auto& enemy : level->enemies) {
                    window.draw(enemy->sprite);
                    for (auto& bomb : enemy->bombs) {
                        window.draw(bomb.sprite);
                    }
                }

                for (auto& addon : activeAddons) {
                    window.draw(addon->sprite);
                }

                window.draw(livesText);

                Text pauseText;
                pauseText.setFont(font);
                pauseText.setString("Game Paused");
                pauseText.setCharacterSize(60);
                pauseText.setFillColor(Color::White);
                pauseText.setPosition(180, 350);

                window.draw(pauseText);
                window.display();
            }
        }
    }
    void newPhaseStart(string text, char shape) {
        AnnouncementText.setString(text);
        isAnnouncer = true;
        anouncerClock.restart();
        level->generateEnemies(shape, currentLevel);
        p->sprite.setPosition(400.f, 700.f);
    }
    void Announcer(RenderWindow& window) {
        if (isAnnouncer) {
            AnnouncementText.setFont(font);
            AnnouncementText.setCharacterSize(60);
            AnnouncementText.setFillColor(Color::White);
            AnnouncementText.setPosition(170.f, 350.f);
            if (isGameEnded) {

                Text finalScore;
                finalScore.setString("Final Score: " + to_string(int(p->pScore)));;
                finalScore.setFont(font);
                finalScore.setCharacterSize(27);
                finalScore.setFillColor(Color::White);
                finalScore.setPosition(270, 290);
                window.draw(finalScore);

                playAgain.setString("Play Again");
                playAgain.setFont(font);
                playAgain.setCharacterSize(48);
                playAgain.setFillColor(Color::Green);
                playAgain.setPosition(250, 450);
                window.draw(playAgain);


            }
            if (anouncerClock.getElapsedTime().asSeconds() >= 2.0f) {
                isAnnouncer = false;
            }
        }
    }

    void AddonsGenerator(int x, int y) {
        //Dont spawn more than 1 addon at a time
        if (!activeAddons.empty()) {
            return;
        }
        x += 19;
        y += 15;
        int N = 4;
        int r = rand() % N + 1;

        Texture addonTex;
        Addons* add = nullptr;

        //cout << r << " ";

        if (r == 1) {
            if (addonTex.loadFromFile("img/PNG/Power-ups/powerupRed_bolt.png")) {
                add = new PowerUp(addonTex, x, y, 200.0f);
            }
        }
        else if (r == 2) {
            if (addonTex.loadFromFile("img/PNG/Power-ups/powerupRed_bolt.png")) {
                add = new Fire(addonTex, x, y, 200.0f);
            }
        }
        else if (r == 3) {
            if (addonTex.loadFromFile("img/PNG/Power-ups/powerupRed_bolt.png")) {
                add = new Lives(addonTex, x, y, 200.0f);
            }
        }
        else if (r == 4) {
            if (addonTex.loadFromFile("img/PNG/Power-ups/powerupRed_bolt.png")) {
                add = new Danger(addonTex, x, y, 200.0f);
            }
        }

        if (add != nullptr) {
            activeAddons.push_back(add);
        }
        
    }


    void updateAddons(float deltaTime) {
        for (auto it = activeAddons.begin(); it != activeAddons.end();) {
            (*it)->update(deltaTime);
            if ((*it)->sprite.getPosition().y > 780) {
                // Remove the addon if it moves out of the screen
                if ((*it)->type == 4) {
                    p->pScore += 5;
                }
                delete* it;
                it = activeAddons.erase(it);
            }
            else if (p->sprite.getGlobalBounds().intersects((*it)->sprite.getGlobalBounds())) {
                // Handle collision with player
                (*it)->activate(p);
                delete* it;
                it = activeAddons.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    //Stoing power up mode if it is activated
    void stopPowerUpMode() {
        
        if (p->isFireMode && playerFireModeClock.getElapsedTime().asSeconds() >= 5.0f) {
            p->isFireMode = false;
        }
        else if (!(p->isFireMode)) {
            playerFireModeClock.restart();
        }
    }

    //Stoing Fire mode if it is activated
    void stopPlayerFireMode() {

        if (p->isPowerUpMode && powerUpClock.getElapsedTime().asSeconds() >= 5.0f) {
            p->isPowerUpMode = false;
        }
        else if (!(p->isPowerUpMode)) {
            powerUpClock.restart();
        }
    }

    void deductLife(float* health) {
        if (*health <= 0 && !(p->isPowerUpMode)) {
            p->pLives--;
            *health = 100.0f;
        }
    }
    void playerEnemyCollision() {
        for (auto enemyIt = level->enemies.begin(); enemyIt != level->enemies.end();) {
            if ((*enemyIt)->isHitWithPlayer(p->sprite.getGlobalBounds())) {
                cout << "Player Hitted with Enemy" << endl;
                p->pLives = 0;
                enemyIt = level->enemies.erase(enemyIt);
            }
            else {
                // Increment the iterator only if no enemy is removed
                ++enemyIt;
            }
        }
    }

    void bombCollision() {
        for (auto& enemy : level->enemies) {
            for (auto bombIt = enemy->bombs.begin(); bombIt != enemy->bombs.end();) {
                if (p->isHit(bombIt->sprite.getGlobalBounds())) {
                    if (enemy->type == 1) {
                        p->pHealth -= 20.0f;
                    }
                    else if (enemy->type == 2) {
                        p->pHealth -= 20.0f;
                    }
                    else if (enemy->type == 3) {
                        p->pHealth -= 20.0f;
                    }
                    else if (enemy->type == 4) {
                        p->pHealth -= 0.5f;
                    }
                    else if (enemy->type == 5) {
                        p->pHealth -= 0.8f;
                    }
                    bombIt = enemy->bombs.erase(bombIt);
                }
                else {
                    ++bombIt;
                }
            }
        }
    }

    void bulletCollision() {
        for (auto bulletIt = p->bullets.begin(); bulletIt != p->bullets.end();) {
            bool bulletRemoved = false;
            for (auto enemyIt = level->enemies.begin(); enemyIt != level->enemies.end();) {
                if ((*enemyIt)->isHit(bulletIt->sprite.getGlobalBounds())) {
                    (*enemyIt)->decreaseHealth(bulletIt->damage);
                    if ((*enemyIt)->isDead()) {
                        // 10% chance to spawn an addon
                        if (rand() % 100 < 10) {
                            AddonsGenerator((*enemyIt)->sprite.getPosition().x, (*enemyIt)->sprite.getPosition().y);
                        }
                        if ((*enemyIt)->type == 1) {
                            p->pScore += 10 * currentLevel;
                        }else if ((*enemyIt)->type == 2) {
                            p->pScore += 20 * currentLevel;
                        }else if ((*enemyIt)->type == 3) {
                            p->pScore += 30 * currentLevel;
                        }else if ((*enemyIt)->type == 4) {
                            p->pScore += 40;
                        }
                        enemyIt = level->enemies.erase(enemyIt);
                    }
                    else {
                        ++enemyIt;
                    }
                    bulletIt = p->bullets.erase(bulletIt);
                    bulletRemoved = true;
                    break;
                }
                else {
                    ++enemyIt;
                }
            }
            if (!bulletRemoved) {
                ++bulletIt;
            }
        }
    }
    void restart_game(RenderWindow& window) {
        Game g;
        g.start_game(window, p->pName);
        isGameEnded = false;
    }
    void end_game(PlayerData currentPlayer) {
        isGameEnded = true;
        AnnouncementText.setString("!!!Game Over!!!");
        isAnnouncer = true;


        // Open the file to store player scores
        fstream file("player_scores.txt", ios::in | ios::out | ios::app);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }
        vector<PlayerData> playerScores;
        PlayerData player;
        bool playerExists = false;
        while (file >> player.name >> player.score) {
            if (player.name == currentPlayer.name) {
                player.score = max(player.score, currentPlayer.score);
                playerExists = true;
            }
            playerScores.push_back(player);
        }

        if (!playerExists) {
            playerScores.push_back(currentPlayer);
        }
        sort(playerScores.begin(), playerScores.end(), [](const PlayerData& a, const PlayerData& b) {
            return a.score > b.score;
            });
        file.close();
        file.open("player_scores.txt", ios::out | ios::trunc);

        for (const auto& p : playerScores) {
            file << p.name << " " << p.score << endl;
        }
    }

    //Player Health Bar
    void displayPlayerHealthBar() {
        float totalHealth = p->pHealth + (p->pLives - 1) * 100.0f; 
        float healthPercentage = totalHealth / (100.0f * p->pLives);

        healthBar.setSize(Vector2f(200 * healthPercentage, 20)); // Adjust the width of the health bar

    }
    ~Game() {
        delete p;
        delete level;
        for (auto addon : activeAddons) {
            delete addon;
        }
    }
};
