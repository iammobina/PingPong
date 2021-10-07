#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong!");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    
    sf::Event event;

    bool play = true;
    bool up = false;
    bool down = false; 

    int yvelredpad = 0;
    int xvelball = -4;
    int yvelball = -4;
    int yvelblackpad = 0;
    int redpadscore = 0;
    int blackpadscore = 0;


    sf::Font font;
    if (font.loadFromFile("Data/HARNGTON.TTF") == 0)
    {
        return 1;
    } 
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    //score.setColor(sf::Color::Black);
    score.setPosition(380 , 10);
    score.setString("0 : 0");



    sf::Texture red_pad;
    sf::Texture balck_pad;
    sf::Texture tex_background;
    sf::Texture tex_ball;

    if (red_pad.loadFromFile("Data/21.png") == false) {
        return -1;
    }
    if (tex_ball.loadFromFile("Data/ball.png") == false) {
        return -1;
    }
    if (balck_pad.loadFromFile("Data/w.png") == false) {
        return -1;
    }
    if (tex_background.loadFromFile("Data/bluebackground.png") == false) {
        return -1;
    }
    sf::SoundBuffer buff_hit;
    sf::Sound hit;
    hit.setBuffer(buff_hit);
    if (buff_hit.loadFromFile("Data/Hit_Hurt.wav") == false)
    {
        return -1;
    }
    

    sf::RectangleShape backgrounds;
    backgrounds.setSize(sf::Vector2f(800, 600));
    backgrounds.setPosition(0, 0);
    backgrounds.setTexture(&tex_background);

    sf::RectangleShape redpad;
    redpad.setSize(sf::Vector2f(50, 100));
    redpad.setPosition(50, 200);
    redpad.setTexture(&red_pad);

    sf::RectangleShape blackpad;
    redpad.setSize(sf::Vector2f(50, 100));
    redpad.setPosition(700, 200);
    redpad.setTexture(&balck_pad);

    sf::RectangleShape balls;
    redpad.setSize(sf::Vector2f(65, 65));
    redpad.setPosition(400, 250);
    redpad.setTexture(&tex_ball);

    while (play == true)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                play = false;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                up = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                down = true;
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
                up = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
                down = false;
            }
        }

        if (up == true)
        {
            yvelredpad = -5;
        }
        if (down == true)
        {
            yvelredpad = 5;
        }
        if (up == true && down == true)
        {
            yvelredpad = 0;
        }
        if (up == false && down == false)
        {
            yvelredpad = 0;
        }

        redpad.move(0,yvelredpad);

        if (redpad.getPosition().y < 0) {
            redpad.setPosition(50, 0);
        }
        if (redpad.getPosition().y > 500) {
            redpad.setPosition(50, 500);
        }

        if (balls.getPosition().y < blackpad.getPosition().y)
        {
            yvelblackpad = -2;
        }
        if (balls.getPosition().y > blackpad.getPosition().y)
        {
            yvelblackpad = 2;
        }
        blackpad.move(0, yvelblackpad);

        balls.move(xvelball, yvelball);

        if (balls.getPosition().y < 0) {
            yvelball = -yvelball;
        }
        if (balls.getPosition().y > 550) {
            yvelball = -yvelball;
        }

        if (balls.getPosition().x < -50) {
            blackpadscore++;
            balls.setPosition(300, 200);
        }

        if (balls.getPosition().x > 800) {
            redpadscore++;
            balls.setPosition(300, 200);
        }

        if (balls.getGlobalBounds().intersects(redpad.getGlobalBounds()) == true) {
            xvelball = -xvelball;
            //hit.play();
        }

        if (balls.getGlobalBounds().intersects(blackpad.getGlobalBounds()) == true) {
            xvelball = -xvelball;
            //hit.play();
        }


    window.clear();
    window.draw(backgrounds);
    window.draw(redpad);
    window.draw(blackpad);
    window.draw(balls);

    std::stringstream text;
    text << redpadscore << " : " << blackpadscore;
    score.setString(text.str());

    window.draw(score);

    window.display();
}
window.close();
    return 0;
}