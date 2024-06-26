#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include <fstream>
using namespace sf;
class Menu {
public:
    Font font;
    Texture bg_texture;
    Sprite background;

    struct PlayerData {
        string name;
        int score;
    };
    void display_menu() {
        RenderWindow window(VideoMode(780, 780), "Main Menu");

        //Game Object
        Game g;

        // Load a font
        if (!font.loadFromFile("font/luckiestguy.ttf")) {
            cerr << "Error loading font" << endl;
            return;
        }

        // Create "Play" button
        Text playText;
        playText.setString("Play");
        playText.setFont(font);
        playText.setCharacterSize(48);
        playText.setFillColor(Color::White);
        playText.setPosition(400, 250);


        Text instructionsText;
        instructionsText.setString("Instructions");
        instructionsText.setFont(font);
        instructionsText.setCharacterSize(48);
        instructionsText.setFillColor(Color::White);
        instructionsText.setPosition(400, 350);
        

        Text highscoreText;
        highscoreText.setString("HighScore");
        highscoreText.setFont(font);
        highscoreText.setCharacterSize(48);
        highscoreText.setFillColor(Color::White);
        highscoreText.setPosition(400, 450);

        bg_texture.loadFromFile("img/bg_menu.jpg");
        background.setTexture(bg_texture);
        background.setScale(0.4, 0.4);


        while (window.isOpen()) {

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();


                if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        Vector2i mousePosition = Mouse::getPosition(window);


                        if (playText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            string name;
                            cout << "Name:";
                            cin >> name;
                            g.start_game(window, name);
                        }


                        if (instructionsText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            displayInstructionScreen(window);
                        }

                        if (highscoreText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            displayHighScoreScreen(window);
                        }

                    }
                }
            }
            window.clear(Color::Black);
            window.draw(background);
            window.draw(playText);
            window.draw(instructionsText);
            window.draw(highscoreText);
            window.display();
        }
    }
    void displayInstructionScreen(RenderWindow& window) {
        RenderWindow instructionWindow(VideoMode(780, 780), "Instructions");

        while (instructionWindow.isOpen()) {
            Event e;
            while (instructionWindow.pollEvent(e)) {
                if (e.type == Event::Closed)
                    instructionWindow.close();
            }

            instructionWindow.clear(Color::Black);
            instructionWindow.draw(background);

            Text text;
            text.setString("Instructions");
            text.setFont(font);
            text.setCharacterSize(55);
            text.setPosition(100, 50);
            text.setFillColor(Color::White);
            instructionWindow.draw(text);

            Text l1;
            l1.setString("* Use W,A,S,D to control the Ship");
            l1.setFont(font);
            l1.setCharacterSize(25);
            l1.setPosition(100, 200);
            l1.setFillColor(Color::White);
            instructionWindow.draw(l1);

            Text l2;
            l2.setString("* Different Enemies gets you different Score");
            l2.setFont(font);
            l2.setCharacterSize(25);
            l2.setPosition(100, 250);
            l2.setFillColor(Color::White);
            instructionWindow.draw(l2);

            Text l3;
            l3.setString("* Different Enemies gets you different Score");
            l3.setFont(font);
            l3.setCharacterSize(25);
            l3.setPosition(100, 300);
            l3.setFillColor(Color::White);
            instructionWindow.draw(l3);

            Text l4;
            l4.setString("* Always try to get the addons dropping from sky");
            l4.setFont(font);
            l4.setCharacterSize(25);
            l4.setPosition(100, 350);
            l4.setFillColor(Color::White);
            instructionWindow.draw(l4);

            Text l5;
            l5.setString("* Lookout for your number of lifes");
            l5.setFont(font);
            l5.setCharacterSize(25);
            l5.setPosition(100, 400);
            l5.setFillColor(Color::White);
            instructionWindow.draw(l5);

            Text l6;
            l6.setString("* Make highscore and reach the leaderboard");
            l6.setFont(font);
            l6.setCharacterSize(25);
            l6.setPosition(100, 450);
            l6.setFillColor(Color::White);
            instructionWindow.draw(l6);

            Text l7;
            l7.setString("* Increasing levels comes with difficult enemies");
            l7.setFont(font);
            l7.setCharacterSize(25);
            l7.setPosition(100, 500);
            l7.setFillColor(Color::White);
            instructionWindow.draw(l7);

            Text l8;
            l8.setString("* Beware of Monsters and Dragons");
            l8.setFont(font);
            l8.setCharacterSize(25);
            l8.setPosition(100, 550);
            l8.setFillColor(Color::White);
            instructionWindow.draw(l8);
            instructionWindow.display();

        }

    }
    void displayHighScoreScreen(RenderWindow& window) {

        RenderWindow highScoreWindow(VideoMode(780, 780), "High Scores");


        ifstream file("player_scores.txt");
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }

        // Read player scores from the file
        vector<PlayerData> playerScores;
        PlayerData player;
        while (file >> player.name >> player.score) {
            playerScores.push_back(player);
        }

        file.close();

        string badges[3] = { "Gold", "Silver", "Bronze" };


        while (highScoreWindow.isOpen()) {
            Event e;
            while (highScoreWindow.pollEvent(e)) {
                if (e.type == Event::Closed)
                    highScoreWindow.close();
            }


            highScoreWindow.clear(Color::Black);
            highScoreWindow.draw(background);

            Text title;
            title.setString("HighScores");
            title.setFont(font);
            title.setCharacterSize(55);
            title.setPosition(100,50);
            title.setFillColor(Color::White);
            highScoreWindow.draw(title);

            for (int i = 0; i < 3 && i < playerScores.size(); ++i) {
                Text text;
                text.setString(playerScores[i].name + ": " + to_string(playerScores[i].score) + " - Badge: " + badges[i]);
                text.setFont(font); 
                text.setCharacterSize(26);
                text.setPosition(100, 50 * (i + 1) + 200);
                text.setFillColor(Color::White);
                highScoreWindow.draw(text);
            }

            // Display the window
            highScoreWindow.display();
        }
    }

};


