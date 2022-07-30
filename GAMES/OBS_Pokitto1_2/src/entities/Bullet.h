#pragma once

enum class BulletType : uint8_t {
    PlayerBullet,
	BossBullet,
};

class Bullet : public Point {

    private:

        uint8_t hitCount = 0;
        uint8_t muzzleIndex = 0;

        Direction direction = Direction::Down;
        HitObject hitObject = HitObject::None;
    
    public:

        uint8_t getHitCount()                   { return this->hitCount; }
        uint8_t getMuzzleIndex()                { return this->muzzleIndex; }

        Direction getDirection()                { return this->direction; }
        HitObject getHitObject()                { return this->hitObject; }

        void setHitCount(uint8_t val)           { this->hitCount = val; }
        void setMuzzleIndex(uint8_t val)        { this->muzzleIndex = val; }

        void setDirection(Direction val)        { this->direction = val; }
        void setHitObject(HitObject val)        { this->hitObject = val; }

        void reset() {

            this->setX(-1);
            this->hitCount = 0;
            this->hitObject = HitObject::None;
            this->setActive(false);

        }

        void incHitCount() {

            this->hitCount++;

        }

        void decMuzzleIndex() {

            this->muzzleIndex--;

        }

        Rect getRect(BulletType bulletType) {

            Rect rect = { this->getX() + 1, this->getY() + 1, 1, 1 };

            switch (bulletType) {

                case BulletType::PlayerBullet:

                    rect.width = 7;
                    rect.height = 5;
                    return rect;

                case BulletType::BossBullet:

                    rect.width = 4;
                    rect.height = 4;
                    return rect;

            }

            return rect; // should never get here!

        }

};
