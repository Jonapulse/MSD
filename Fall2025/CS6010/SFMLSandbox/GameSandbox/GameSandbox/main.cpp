//
//  main.cpp
//  GameSandbox
//
//  Created by Jonathan Pulsipher on 9/15/25.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, const char * argv[]) {
    
    sf::RenderWindow window (sf::VideoMode({800, 600}), "My first SFML game!!");
    
        const sf::Font font("test.ttf");
        sf::Text text(font, "Hello SFML", 50);
        sf::Texture characterImage = sf::Texture("character.png");
    
        sf::Sprite sprite(characterImage);
        int x = 0;
    
        sf::Clock clock;
        while(window.isOpen()){
          while(std::optional event = window.pollEvent()){
              if(event->is<sf::Event::Closed>())
                  window.close();
          }
    
  //  NOTE: At this point, this should display a window though it won't show anything else.
    
//          window.clear();
//          sf::Time timeElapsed = clock.restart();
//          sprite.move(sf::Vector2f(time.Elapsed.asMilliseconds(), 0)); // +x go right, +y go down.
//          window.draw(text);
//          window.draw(sprite);
//          window.display();
    }
    
    return 0;
}
