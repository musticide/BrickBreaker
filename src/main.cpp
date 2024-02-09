#include <SFML/Graphics.hpp>

int
main (int argc, char *argv[])
{
  sf::RenderWindow window (sf::VideoMode (1280, 720), "SFML works!",
                           sf::Style::None | sf::Style::Close);
  sf::CircleShape shape (100.f);
  shape.setFillColor (sf::Color::Green);

  while (window.isOpen ())
    {
      sf::Event event;
      while (window.pollEvent (event))
        {
          if (event.type == sf::Event::Closed)
            window.close ();
        }

      window.clear ();
      if (window.hasFocus ())
        {
          shape.setFillColor (sf::Color::Yellow);
        }
      else
        {
          shape.setFillColor (sf::Color::Green);
        }
      window.draw (shape);
      window.display ();
    }

  return 0;
}
