#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Types.h"

class AudioSystem
{
public:
    bool load(const std::string &path);

    void play();

    void stop();

    Seconds getSongTime() const;

private:
    sf::Music music;
};