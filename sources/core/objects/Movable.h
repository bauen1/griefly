#pragma once

#include "MaterialObject.h"

inline FastDeserializer& operator>>(FastDeserializer& file, VDir& vdir)
{
    file >> vdir.x;
    file >> vdir.y;
    file >> vdir.z;
    return file;
}

inline FastSerializer& operator<<(FastSerializer& file, const VDir& vdir)
{
    file << vdir.x;
    file << vdir.y;
    file << vdir.z;
    return file;
}

inline unsigned int hash(const VDir& vdir)
{
    return   vdir.x
           + vdir.y
           + vdir.z;
}

namespace kv
{

class Movable : public MaterialObject
{
public:
    DECLARE_SAVEABLE(Movable, MaterialObject);
    REGISTER_CLASS_AS(Movable);
    Movable();
    virtual bool TryMove(Dir direct);
    bool CheckMoveTime();
    virtual bool CheckPassable();
    bool MainMove();

    virtual bool Rotate(Dir dir);
    Dir GetDir() const { return direction_; }

    virtual void ProcessForce();
    virtual void ApplyForce(VDir force) override;

    virtual void Delete() override { MaterialObject::Delete(); }

    virtual void Represent() override;
    virtual void Bump(IdPtr<Movable> item) override;
    virtual void BumpByGas(Dir dir, bool inside = false) override;
public:
    VDir KV_SAVEABLE(force_);
    bool KV_SAVEABLE(anchored_);
    int KV_SAVEABLE(last_move_);
    int KV_SAVEABLE(tick_speed_);

    KV_ON_LOAD_CALL(LoadInForceManager);
    void LoadInForceManager();
private:
    Dir KV_SAVEABLE(direction_);
};
END_DECLARE(Movable);

}
class ForceManager
{
public:
    static ForceManager& Get();

    void Add(IdPtr<kv::Movable> m);
    void Process();
    void Clear();
    unsigned int Hash();
private:
    std::vector<IdPtr<kv::Movable>> under_force_;

    std::vector<IdPtr<kv::Movable>> to_add_;
};
