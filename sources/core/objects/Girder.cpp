#include "Girder.h"

#include "Materials.h"
#include "MetalWall.h"
#include "Item.h"

#include "../ObjectFactory.h"
#include "../Game.h"

#include "representation/Sound.h"

using namespace kv;

Girder::Girder()
{
    SetSprite("icons/structures.dmi");
    SetState("girder");

    SetPassable(Dir::ALL, passable::AIR);

    anchored_ = true;
    name = "Girder";
}

void Girder::AttackBy(IdPtr<Item> item)
{
    if (IdPtr<Metal> metal = item)
    {
        metal->Delete();

        GetTurf()->Delete();
        Create<Turf>(MetalWall::GetTypeStatic(), GetOwner());

        Delete();
    }
    else if (IdPtr<Wrench> wrench = item)
    {
        PlaySoundIfVisible("Ratchet.wav");
        Create<Item>(Metal::GetTypeStatic(), GetOwner());
        Delete();
    }
}
