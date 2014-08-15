#pragma once

#include "OnMapInt.h"

inline std::istream& operator>>(std::stringstream& file, VDir& vdir)
{
    file >> vdir.x;
    file >> vdir.y;
    file >> vdir.z;
    return file;
}

inline std::ostream& operator<<(std::stringstream& file, const VDir& vdir)
{
    file << vdir.x << " ";
    file << vdir.y << " ";
    file << vdir.z << " ";
    return file;
}

inline unsigned int hash(const VDir& vdir)
{
    return   vdir.x
           + vdir.y
           + vdir.z;
}

class IMovable : public IOnMapObject
{
public:
    DECLARE_GET_TYPE_ITEM(IMovable);
    DECLARE_SAVED(IMovable, IOnMapObject);
    IMovable();
    void processMove();//for move
    virtual bool checkMove(Dir direct);
    bool checkMoveTime();
    bool checkPassable();
    bool mainMove();

    virtual void ProcessForce();
    virtual void ApplyForce(VDir force) override;

    virtual bool IsTransp(int x, int y) override;

    virtual void delThis() override { IOnMapObject::delThis(); }

    virtual void processImage(DrawType type);
    virtual void Bump(id_ptr_on<IMovable> item) override;
public:
    VDir KV_SAVEBLE(force_);
    bool KV_SAVEBLE(anchored);
    int KV_SAVEBLE(lastMove);
    int KV_SAVEBLE(tickSpeed);
    int KV_SAVEBLE(pixSpeed);
    Dir KV_SAVEBLE(dMove);
};
ADD_TO_TYPELIST(IMovable);