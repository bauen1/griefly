#include "ImageLoader.h"
#include "ASpritesClass.h"

void LoadImages()
{
    GetSpriter()->LoadImage("icons/Doorglass.dmi");
    GetSpriter()->LoadImage("icons/floors.dmi");
    GetSpriter()->LoadImage("icons/structures.dmi");
    GetSpriter()->LoadImage("icons/items.dmi");
    GetSpriter()->LoadImage("icons/walls.dmi");
    GetSpriter()->LoadImage("icons/shards.dmi");
    GetSpriter()->LoadImage("icons/space.png");
    GetSpriter()->LoadImage("icons/human.png");
    GetSpriter()->LoadImage("icons/device.dmi");
}