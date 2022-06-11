#include "MapInformation.h"
#include "../utils/Enums.h"

void MapInformation::reset() {

    this->width = 15;
    this->height = 15;
    this->timer = 255;
    this->level = 0;
    this->definedMapLevel = 0;
    this->randomLevel = false;
    this->randomLevelIndex = 0;
}

uint8_t MapInformation::getLevel() {
    return this->level;
}

uint8_t MapInformation::getDefinedMapLevel() {
    return this->definedMapLevel;
}

uint16_t MapInformation::getWidth() {
    return this->width;
}

uint16_t MapInformation::getHeight() {
    return this->height;
}

uint16_t MapInformation::getTimer() {
    return this->timer;
}

bool MapInformation::getRandomLevel() {
    return this->randomLevel;
}

uint8_t MapInformation::getRandomLevelIndex() {
    return this->randomLevelIndex;
}

bool MapInformation::getHasRune() {
    return this->hasRune;
}

bool MapInformation::isBossLevel() {
    return this->bossLevel;
}

bool MapInformation::isShopLevel() {
    return this->shopLevel;
}

bool MapInformation::isAltarLevel() {
    return this->altarLevel;
}

void MapInformation::setLevel(uint8_t level) {
    this->level = level;
}

void MapInformation::setDefinedMapLevel(uint8_t definedMapLevel) {
    this->definedMapLevel = definedMapLevel;
}

void MapInformation::setWidth(uint16_t width) {
    this->width = width;
}

void MapInformation::setHeight(uint16_t height) {
    this->height = height;
}

void MapInformation::setTimer(uint16_t timer) {
    this->timer = timer;
}

void MapInformation::setShopLevel(bool value) {
    this->shopLevel = value;
}

void MapInformation::setBossLevel(bool value) {
    this->bossLevel = value;
}

void MapInformation::setAltarLevel(bool value) {
    this->altarLevel = value;
}

void MapInformation::setRandomLevel(bool randomLevel) {
    this->randomLevel = randomLevel;
}

void MapInformation::setRandomLevelIndex(uint8_t randomLevelIndex) {
    this->randomLevelIndex = randomLevelIndex;
}

void MapInformation::incRandomLevelIndex() {
    this->randomLevelIndex++;
}

void MapInformation::setHasRune(bool hasRune) {
    this->hasRune = hasRune;
}

void MapInformation::decTimer() {
    //SJH 
    if (this->timer > 0) this->timer--;
}

MapTiles MapInformation::getBlock(int16_t x, int16_t y) {


    if ((x < 0) || (x >= this->width) || (y< 0) || (y >= this->height)) {
        return MapTiles::Fill;
    } 
    else {
        MapTiles Block = static_cast<MapTiles>(mapData[(x + (y * this->width))]);
        return Block;
    }

}

MapTiles MapInformation::getBlock(int16_t idx) {

    MapTiles Block = static_cast<MapTiles>(mapData[idx]);
    return Block;

}

void MapInformation::setBlock(uint16_t x, uint16_t y, MapTiles block) {

    if ((x >= this->width) || (y >= this->height)) {
        return;
    }
    mapData[x + (y * (this->width))] = static_cast<uint8_t>(block);

}

void MapInformation::setBlock(uint16_t index, MapTiles block) {

    if (index > (this->height * this->width)) {
        return;
    }
    mapData[index] = static_cast<uint8_t>(block);

}

void MapInformation::swap(uint8_t & a, uint8_t & b) {

    uint8_t t = a;
    a = b;
    b = t;

}

bool MapInformation::between(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {

    if (x > x1)     swap(x, x1);
    if (y > y1)     swap(y, y1);
        
    return ((x <= x2) && (x2 <= x1) && (y <= y2) && (y2 <= y1));

}

int8_t MapInformation::getTileX(uint16_t x) {
    
    return (x / TILE_WIDTH);

}

uint8_t MapInformation::getTileY(uint16_t y) {
    
    return (y / TILE_HEIGHT);

}

uint8_t MapInformation::getTileXOffset(uint16_t x) {
    
    return (x % TILE_WIDTH);

}

uint8_t MapInformation::getTileYOffset(uint16_t y) {
    
    return (y % TILE_HEIGHT);

}

uint16_t MapInformation::getDistance(int x,int y,int x1,int y1) {
    
    uint16_t ret = (abs(this->getTileX(x) - this->getTileX(x1)) + abs(this->getTileY(y) - this->getTileY(y1))); 
    return ret;
    
}

uint8_t MapInformation::getOffset(uint8_t x, uint8_t y) {

    if ((x >= this->width) || (y >= this->height)) {
        return 0;
    }
    return (x + (y * (this->width)));

}

void MapInformation::clearMap() {

    for (uint32_t x = 0; x < MAP_SIZE; x ++) {

        mapData[x] = MapTiles::Fill;

    }

}


WalkType MapInformation::isWalkable(uint16_t x, uint16_t y, Direction direction, uint8_t width, uint8_t height) {

    bool up, down, left, right;

    return isWalkable(x, y, direction, width, height, up, down, left, right);

}

WalkType MapInformation::isWalkable(uint16_t x, uint16_t y, Direction direction, uint8_t width, uint8_t height, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight) {

    MapTiles tile1 = MapTiles::Empty;
    MapTiles tile2 = MapTiles::Empty;
    int16_t xMod = x % 16;
    int16_t yMod = y % 16;

    uint8_t widthHalf = width / 2;
    uint8_t heightHalf = height / 2;
    
    WalkType walk = WalkType::Normal; 

    switch (direction) {

        // case Direction::Up:
        //     tile1 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y - heightHalf));
        //     if (((x - widthHalf) % 16) + width > 16) tile2 = this->getBlock(this->getTileX(x + widthHalf), this->getTileY(y - heightHalf));
        //     nudgeRight = isEmptyTile(tile2) && isWallTile(tile1) && (16 - ((x - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
        //     nudgeLeft = isEmptyTile(tile1) && isWallTile(tile2) && ((x - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
        //     break;

        // case Direction::Right:
        //     tile1 = this->getBlock(this->getTileX(x + widthHalf - 1), this->getTileY(y - heightHalf));
        //     if (((y - heightHalf) % 16) + height > 16) tile2 = this->getBlock(this->getTileX(x + widthHalf - 1), this->getTileY(y + heightHalf)); 
        //     nudgeDown = isEmptyTile(tile2) && isWallTile(tile1) && (16 - ((y - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
        //     nudgeUp = isEmptyTile(tile1) && isWallTile(tile2) && ((y - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
        //     break;

        // case Direction::Down:
        //     tile1 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y + heightHalf - 1));
        //     if (((x - widthHalf) % 16) + width > 16) tile2 = this->getBlock(this->getTileX(x + widthHalf), this->getTileY(y + heightHalf - 1));
        //     nudgeRight = isEmptyTile(tile2) && isWallTile(tile1) && (16 - ((x - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
        //     nudgeLeft = isEmptyTile(tile1) && isWallTile(tile2) && ((x - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
        //     break;

        // case Direction::Left:
        //     tile1 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y - heightHalf));
        //     if (((y - heightHalf) % 16) + height > 16) tile2 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y + heightHalf));
        //     nudgeDown = isEmptyTile(tile2) && isWallTile(tile1) && (16 - ((y - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
        //     nudgeUp = isEmptyTile(tile1) && isWallTile(tile2) && ((y - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
        //     break;
            
        case Direction::Up:
            tile1 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y - heightHalf));
            if (((x - widthHalf) % 16) + width > 16) tile2 = this->getBlock(this->getTileX(x + widthHalf), this->getTileY(y - heightHalf));
            nudgeRight = isEmptyTile(tile2) && (16 - ((x - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
            nudgeLeft = isEmptyTile(tile1) && ((x - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
            break;

        case Direction::Right:
            tile1 = this->getBlock(this->getTileX(x + widthHalf - 1), this->getTileY(y - heightHalf));
            if (((y - heightHalf) % 16) + height > 16) tile2 = this->getBlock(this->getTileX(x + widthHalf - 1), this->getTileY(y + heightHalf)); 
            nudgeDown = isEmptyTile(tile2) && (16 - ((y - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
            nudgeUp = isEmptyTile(tile1) && ((y - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
            break;

        case Direction::Down:
            tile1 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y + heightHalf - 1));
            if (((x - widthHalf) % 16) + width > 16) tile2 = this->getBlock(this->getTileX(x + widthHalf), this->getTileY(y + heightHalf - 1));
            nudgeRight = isEmptyTile(tile2) && (16 - ((x - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
            nudgeLeft = isEmptyTile(tile1) && ((x - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
            break;

        case Direction::Left:
            tile1 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y - heightHalf));
            if (((y - heightHalf) % 16) + height > 16) tile2 = this->getBlock(this->getTileX(x - widthHalf), this->getTileY(y + heightHalf));
            nudgeDown = isEmptyTile(tile2) && (16 - ((y - widthHalf) % TILE_SIZE)) <= 7;  // 5 Tighter
            nudgeUp = isEmptyTile(tile1) && ((y - widthHalf) % TILE_SIZE) <= 11; // 9 Tighter
            break;            
    }

    switch (tile1) {

        case MapTiles::OpenDoor:
        case MapTiles::UpStairs:
        case MapTiles::DownStairs:
        case MapTiles::Empty:
        case MapTiles::CornerFill:
        case MapTiles::OpenChest:
        case MapTiles::Rubble:
        case MapTiles::PressPlate_Up:
        case MapTiles::PressPlate_Down:
        case MapTiles::DoorLHSOpen:
        case MapTiles::DoorRHSOpen:
        case MapTiles::DoorTOPOpen:
        case MapTiles::DoorBOTOpen:
        case MapTiles::SpearDoorLHSOpen:
        case MapTiles::SpearDoorRHSOpen:
        case MapTiles::SpearDoorTOPOpen:
        case MapTiles::SpearDoorBOTOpen:
        case MapTiles::WormHole_F0:
        case MapTiles::ThreeSkulls:
        case MapTiles::Shadow:
            walk = WalkType::Normal;
            break;

        case MapTiles::Shop03 ... MapTiles::Shop05:

            switch (direction) {

                case Direction::Up:
                    yMod = (y - widthHalf) % 16;
                    walk = ((yMod == 0) || (yMod > 8) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Left:
                    xMod = (x - widthHalf) % 16;
                    yMod = (y - widthHalf) % 16;
                    walk = ((xMod > 10 && yMod <= 8) || (yMod > 8) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Right:
                    xMod = (x + widthHalf) % 16;
                    yMod = (y - widthHalf) % 16;
                    walk = ((xMod <= 6 && yMod <= 8) || (yMod > 8) ? WalkType::Normal : WalkType::Stop);
                    break;

            }

            break;
            
        case MapTiles::Barrel:

            switch (direction) {

                case Direction::Left:
                    xMod = (x - widthHalf) % 16;
                    yMod = (y - widthHalf) % 16;
                    walk = ((xMod > 11) || (yMod >= 13) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Right:
                    xMod = (x + widthHalf) % 16;
                    yMod = (y - widthHalf) % 16;
                    walk = ((xMod < 5 && yMod <= 9) || (xMod < 7 && yMod > 9 && yMod < 13) || (yMod >= 13) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Up:
                    xMod = (x - widthHalf) % 16;
                    yMod = (y - widthHalf) % 16;
                    walk = ((xMod < 13 && yMod >= 13 ) || (xMod >= 13) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Down:
                    xMod = (x - widthHalf) % 16;
                    yMod = (y + widthHalf) % 16;
                    walk = ((xMod >= 12) || (yMod <= 1) ? WalkType::Normal : WalkType::Stop);
                    break;
                
            }

            break;        

        case MapTiles::StraightTOP:
        case MapTiles::StraightBOT:
        case MapTiles::StraightTorchTOP_F0:
        case MapTiles::StraightTorchTOP_F1:
        case MapTiles::StraightTorchBOT_F0:
        case MapTiles::StraightTorchBOT_F1:

            switch (direction) {

                case Direction::Left:
                case Direction::Right:
                    walk = WalkType::Normal;
                    break;

                default:
                    walk = WalkType::Stop;
                    break;
                
            }

            break;

        case MapTiles::StraightLHS:
        case MapTiles::StraightTorchLHS_F0:
        case MapTiles::StraightTorchLHS_F1:
        case MapTiles::StraightRHS:
        case MapTiles::StraightTorchRHS_F0:
        case MapTiles::StraightTorchRHS_F1:

            switch (direction) {

                case Direction::Up:
                case Direction::Down:
                    walk = WalkType::Normal;
                    break;

                default:
                    walk = WalkType::Stop;
                    break;
                
            }

            break;

        case MapTiles::DoorTOP:
        case MapTiles::SpearDoorTOP:

            switch (direction) {
                
                case Direction::Down:
                    yMod = (y - widthHalf) % 16;
                    walk = (yMod >= 8 ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Up:
                    yMod = (y - widthHalf) % 16;
                    walk = ((yMod == 0) || (yMod > 6) ? WalkType::Normal : WalkType::Stop);
                    break;

                default:
                    walk = WalkType::Normal;
                    break;
                
            }

            break;

        case MapTiles::DoorBOT:
        case MapTiles::SpearDoorBOT:

            switch (direction) {

                case Direction::Up:
                    walk = WalkType::Stop;
                    break;

                case Direction::Down:
                    yMod = (y - widthHalf) % 16;
                    walk = ((yMod == 0) || (yMod > 6) ? WalkType::Normal : WalkType::Stop);
                    break;

                default:
                    walk = WalkType::Normal;
                    break;
                
            }

            break;

        case MapTiles::DoorLHS:
        case MapTiles::SpearDoorLHS:

            switch (direction) {

                case Direction::Left:
                    xMod = (x - widthHalf) % 16;
                    walk = ((xMod > 6) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Right:
                    xMod = (x - widthHalf) % 16;
                    walk = ((xMod >= 8) ? WalkType::Normal : WalkType::Stop);
                    break;

                default:
                    walk = WalkType::Normal;
                    break;
                
            }

            break;

        case MapTiles::DoorRHS:
        case MapTiles::SpearDoorRHS:

            switch (direction) {

                case Direction::Left:
                    xMod = (x - widthHalf) % 16;
                    walk = ((xMod <= 8) ? WalkType::Normal : WalkType::Stop);
                    break;

                case Direction::Right:
                    xMod = (x + widthHalf) % 16;
                    walk = ((xMod < 12) ? WalkType::Normal : WalkType::Stop);
                    break;

                default:
                    walk = WalkType::Normal;
                    break;
                
            }

            break;

        case MapTiles::CornerLL:

            switch (direction) {

                case Direction::Down:
                case Direction::Left:
                    walk = WalkType::Normal;
                    break;

                default:
                    walk = WalkType::Stop;
                    break;
                
            }

            break;

        case MapTiles::CornerLR:

            switch (direction) {

                case Direction::Down:
                case Direction::Right:
                    walk = WalkType::Normal;
                    break;

                default:
                    walk = WalkType::Stop;
                    break;
                
            }

            break;

        case MapTiles::CornerTL:

            switch (direction) {

                case Direction::Up:
                case Direction::Left:
                    walk = WalkType::Normal;
                    break;

                default:
                    walk = WalkType::Stop;
                    break;
                
            }

            break;

        case MapTiles::CornerTR:

            switch (direction) {

                case Direction::Up:
                case Direction::Right:
                    walk = WalkType::Normal;
                    break;

                default:
                    walk = WalkType::Stop;
                    break;
                
            }

            break;

        case MapTiles::TriangleTL:

            xMod = (x - widthHalf) % 16;
            yMod = (y - heightHalf) % 16;

            switch (direction) {

                case Direction::Left:
//                    if (xMod + yMod >= 16) {
                    if (xMod + yMod >= 14) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                case Direction::Up:
//                    if (xMod + yMod >= 16) {
                    if (xMod + yMod >= 14) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                default:
                    walk = WalkType::Normal;

            }
            break;

        case MapTiles::TriangleTR:

            switch (direction) {

                case Direction::Right:
                    xMod = (x + widthHalf) % 16;
                    yMod = (y + heightHalf) % 16;
                    walk = ((xMod <= yMod + 5 && yMod <= 10) || (xMod < yMod - 9 && yMod > 10) ? walk : WalkType::Stop);
                    break;

                case Direction::Up:
                    xMod = (x + widthHalf) % 16;
                    yMod = (y - heightHalf) % 16;

                    if (xMod!= 0 && xMod <= yMod + 2) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                default:
                    walk = WalkType::Normal;
                    break;

            }
            break;

        case MapTiles::TriangleLL:
            xMod = (x - widthHalf) % 16;
            yMod = (y + heightHalf) % 16;

            switch (direction) {

                case Direction::Left:
                    if (yMod != 0 && xMod >= yMod) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                case Direction::Down:
                    if (xMod >= yMod) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                default:
                    walk = WalkType::Normal;
                    break;

            }
            break;

        case MapTiles::TriangleLR:
            xMod = (x + widthHalf) % 16;
            yMod = (y + heightHalf) % 16;

            switch (direction) {

                case Direction::Right:
                    if (yMod != 0 && xMod + yMod <= 16) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                case Direction::Down:
                    if (xMod != 0 && xMod + yMod <= 16) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Stop;
                    }
                    break;

                default:
                    walk = WalkType::Normal;
                    break;

            }
            break;

        case MapTiles::SpiderWebTL:
            xMod = (x - widthHalf) % 16;
            yMod = (y - heightHalf) % 16;

            switch (direction) {

                case Direction::Left:
                case Direction::Right:
                    if (xMod + yMod >= 18) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                case Direction::Up:
                case Direction::Down:
                    if (xMod + yMod >= 18) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                default:
                    walk = WalkType::Normal;

            }
            break;

        case MapTiles::SpiderWebTR:

            switch (direction) {

                case Direction::Left:
                case Direction::Right:
                    xMod = (x + widthHalf) % 16;
                    yMod = (y - heightHalf) % 16;

                    if (xMod - 4 < yMod) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                case Direction::Up:
                case Direction::Down:
                    xMod = (x + widthHalf) % 16;
                    yMod = (y - heightHalf) % 16;

                    if (xMod!= 0 && xMod < yMod) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                default:
                    walk = WalkType::Normal;
                    break;

            }
            break;

        case MapTiles::SpiderWebLL:
            xMod = (x - widthHalf) % 16;
            yMod = (y + heightHalf) % 16;

            switch (direction) {

                case Direction::Left:
                case Direction::Right:
                    if (yMod != 0 && xMod >= yMod) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                case Direction::Up:
                case Direction::Down:
                    if (xMod >= yMod) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                default:
                    walk = WalkType::Normal;
                    break;

            }
            break;

        case MapTiles::SpiderWebLR:
            xMod = (x + widthHalf) % 16;
            yMod = (y + heightHalf) % 16;

            switch (direction) {

                case Direction::Left:
                case Direction::Right:
                    if (yMod != 0 && xMod + yMod <= 16) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                case Direction::Up:
                case Direction::Down:
                    if (xMod != 0 && xMod + yMod <= 16) {
                        walk = WalkType::Normal;
                    }
                    else {
                        walk = WalkType::Slow;
                    }
                    break;

                default:
                    walk = WalkType::Normal;
                    break;

            }
            break;

        default:
            walk = WalkType::Stop;
            break;
        
    }

    if (walk != WalkType::Stop) {

        switch (tile2) {

            case MapTiles::OpenDoor:
            case MapTiles::UpStairs:
            case MapTiles::DownStairs:
            case MapTiles::Empty:
            case MapTiles::CornerFill:
            case MapTiles::OpenChest:
            case MapTiles::Rubble:
            case MapTiles::PressPlate_Up:
            case MapTiles::PressPlate_Down:
            case MapTiles::DoorLHSOpen:
            case MapTiles::DoorRHSOpen:
            case MapTiles::DoorTOPOpen:
            case MapTiles::DoorBOTOpen:
            case MapTiles::SpearDoorLHSOpen:
            case MapTiles::SpearDoorRHSOpen:
            case MapTiles::SpearDoorTOPOpen:
            case MapTiles::SpearDoorBOTOpen:
            case MapTiles::WormHole_F0:
            case MapTiles::ThreeSkulls:
            case MapTiles::Shadow:
                break;

            case MapTiles::StraightTOP:
            case MapTiles::StraightBOT:
            case MapTiles::StraightTorchTOP_F0:
            case MapTiles::StraightTorchTOP_F1:
            case MapTiles::StraightTorchBOT_F0:
            case MapTiles::StraightTorchBOT_F1:

                switch (direction) {

                    case Direction::Left:
                    case Direction::Right:
                        break;

                    default:
                        walk = WalkType::Stop;
                        break;
                    
                }

                break;

            case MapTiles::Shop03 ... MapTiles::Shop05:

                switch (direction) {

                    case Direction::Up:
                        yMod = (y - widthHalf) % 16;
                        walk = ((yMod == 0) || (yMod > 8) ? walk : WalkType::Stop);
                        break;

                    case Direction::Left:
                        xMod = (x - widthHalf) % 16;
                        yMod = (y + widthHalf) % 16;
                        walk = ((xMod > 10 && yMod <= 8) || (yMod > 8) ? walk : WalkType::Stop);
                        break;

                    case Direction::Right:
                        xMod = (x + widthHalf) % 16;
                        yMod = (y + widthHalf) % 16;
                        walk = ((xMod <= 6 && yMod <= 8) || (yMod > 8) ? walk : WalkType::Stop);
                        break;

                }

                break;

            case MapTiles::Barrel:

                switch (direction) {

                    case Direction::Left:
                        xMod = (x - widthHalf) % 16;
                        yMod = (y - widthHalf) % 16;
                        walk = ((xMod > 11) || (yMod <= 7) ? WalkType::Normal : WalkType::Stop);
                        break;

                    case Direction::Right:
                        xMod = (x + widthHalf) % 16;
                        yMod = (y - widthHalf) % 16;
                        walk = ((xMod < 5 && yMod > 7) || (yMod <= 7) ? walk : WalkType::Stop);
                        break;

                    case Direction::Up:
                        xMod = (x + widthHalf) % 16;
                        yMod = (y - widthHalf) % 16;
                        walk = ((xMod <= 4) || (xMod <= 5 && yMod > 9) || (xMod >5 && yMod > 11) ? walk : WalkType::Stop);
                        break;

                    case Direction::Down:
                        xMod = (x + widthHalf) % 16;
                        yMod = (y + widthHalf) % 16;
                        walk = ((xMod <= 3) || (yMod <= 1) ? walk : WalkType::Stop);
                        break;
                    
                }

                break;

            case MapTiles::StraightLHS:
            case MapTiles::StraightTorchLHS_F0:
            case MapTiles::StraightTorchLHS_F1:
            case MapTiles::StraightRHS:
            case MapTiles::StraightTorchRHS_F0:
            case MapTiles::StraightTorchRHS_F1:

                switch (direction) {

                    case Direction::Up:
                    case Direction::Down:
                        break;

                    default:
                        walk = WalkType::Stop;
                        break;
                    
                }

                break;
                
            case MapTiles::DoorTOP:
            case MapTiles::SpearDoorTOP:

                switch (direction) {
                
                    case Direction::Down:
                        yMod = (y - widthHalf) % 16;
                        walk = (yMod >= 8 ? WalkType::Normal : WalkType::Stop);
                        break;
                        
                    case Direction::Up:
                        yMod = (y - widthHalf) % 16;
                        walk = ((yMod == 0) || (yMod > 6) ? walk : WalkType::Stop);
                        break;

                    default:
                        break;
                    
                }

                break;

            case MapTiles::DoorBOT:
            case MapTiles::SpearDoorBOT:

                switch (direction) {

                    case Direction::Up:
                        walk = WalkType::Stop;
                        break;

                    case Direction::Down:
                        yMod = (y - widthHalf) % 16;
                        walk = ((yMod == 0) || (yMod > 6) ? walk : WalkType::Stop);
                        break;

                    default:
                        break;
                    
                }

                break;

            case MapTiles::DoorLHS:
            case MapTiles::SpearDoorLHS:

                switch (direction) {

                    case Direction::Left:
                        xMod = (x - widthHalf) % 16;
                        walk = ((xMod > 2) ? walk : WalkType::Stop);
                        break;

                    case Direction::Right:
                        xMod = (x - widthHalf) % 16;
                        walk = ((xMod >= 8) ? WalkType::Normal : WalkType::Stop);
                        break;
                        
                    default:
                        break;
                    
                }

                break;

            case MapTiles::DoorRHS:
            case MapTiles::SpearDoorRHS:

                switch (direction) {

                    case Direction::Left:
                        xMod = (x - widthHalf) % 16;
                        walk = ((xMod <= 8) ? WalkType::Normal : WalkType::Stop);
                        break;

                    case Direction::Right:
                        xMod = (x + widthHalf) % 16;
                        walk = ((xMod < 12) ? walk : WalkType::Stop);
                        break;

                    default:
                        break;
                    
                }

                break;
                    
            case MapTiles::CornerLL:

                switch (direction) {

                    case Direction::Down:
                    case Direction::Left:
                        break;

                    default:
                        walk = WalkType::Stop;
                        break;
                    
                }

                break;

            case MapTiles::CornerLR:

                switch (direction) {

                    case Direction::Down:
                    case Direction::Right:
                        break;

                    default:
                        walk = WalkType::Stop;
                        break;
                    
                }

                break;

            case MapTiles::CornerTL:

                switch (direction) {

                    case Direction::Up:
                    case Direction::Left:
                        break;

                    default:
                        walk = WalkType::Stop;
                        break;
                    
                }

                break;

            case MapTiles::CornerTR:

                switch (direction) {

                    case Direction::Up:
                    case Direction::Right:
                        break;

                    default:
                        walk = WalkType::Stop;
                        break;
                    
                }

                break;

            case MapTiles::TriangleTL:
                break;

            case MapTiles::TriangleTR:
                xMod = (x + widthHalf) % 16;
                yMod = (y - heightHalf) % 16;

                switch (direction) {

                    case Direction::Up:
                        walk = ((xMod < 3 && yMod < 14) || (xMod >= 3 && yMod > xMod - 3) ? walk : WalkType::Stop);
                        break;

                    default:
                        break;

                }
                break;

            case MapTiles::TriangleLL:
                xMod = (x - widthHalf) % 16;
                yMod = (y + heightHalf) % 16;

                switch (direction) {

                    case Direction::Left:
                        if (xMod < yMod) {
                            walk = WalkType::Stop;
                        }
                        break;

                    default:
                        break;

                }
                break;

            case MapTiles::TriangleLR:
                xMod = (x + widthHalf) % 16;
                yMod = (y + heightHalf) % 16;

                switch (direction) {

                    case Direction::Right:
                        if (xMod + yMod > 16) {
                            walk = WalkType::Stop;
                        }
                        break;

                    case Direction::Down:
                        if (xMod + yMod > 16) {
                            walk = WalkType::Stop;
                        }
                        break;

                    default:
                        break;

                }
                break;


            case MapTiles::SpiderWebTL:
                xMod = (x - widthHalf) % 16;
                yMod = (y - heightHalf) % 16;

                switch (direction) {

                    case Direction::Left:
                    case Direction::Right:
                        if (xMod + yMod >= 18) {
                            walk = WalkType::Normal;
                        }
                        else {
                            walk = WalkType::Slow;
                        }
                        break;

                    default:
                        walk = WalkType::Normal;

                }
                break;

            case MapTiles::SpiderWebTR:

                switch (direction) {

                    case Direction::Left:
                    case Direction::Right:
                        xMod = (x + widthHalf) % 16;
                        yMod = (y - heightHalf) % 16;

                        if (xMod - 4 < yMod) {
                            walk = WalkType::Normal;
                        }
                        else {
                            walk = WalkType::Slow;
                        }
                        break;

                    default:
                        walk = WalkType::Normal;
                        break;

                }
                break;

            case MapTiles::SpiderWebLL:
                xMod = (x - widthHalf) % 16;
                yMod = (y + heightHalf) % 16;

                switch (direction) {

                    case Direction::Left:
                    case Direction::Right:
                        if (yMod != 0 && xMod >= yMod) {
                            walk = WalkType::Normal;
                        }
                        else {
                            walk = WalkType::Slow;
                        }
                        break;

                    case Direction::Up:
                    case Direction::Down:
                        if (xMod >= yMod) {
                            walk = WalkType::Normal;
                        }
                        else {
                            walk = WalkType::Slow;
                        }
                        break;

                    default:
                        walk = WalkType::Normal;
                        break;

                }
                break;

            case MapTiles::SpiderWebLR:
                xMod = (x + widthHalf) % 16;
                yMod = (y + heightHalf) % 16;

                switch (direction) {

                    case Direction::Left:
                    case Direction::Right:
                        if (yMod != 0 && xMod + yMod <= 16) {
                            walk = WalkType::Normal;
                        }
                        else {
                            walk = WalkType::Slow;
                        }
                        break;

                    case Direction::Up:
                    case Direction::Down:
                        if (xMod != 0 && xMod + yMod <= 16) {
                            walk = WalkType::Normal;
                        }
                        else {
                            walk = WalkType::Slow;
                        }
                        break;

                    default:
                        walk = WalkType::Normal;
                        break;

                }
                break;

            default:
                walk = WalkType::Stop;
                break;
            
        }

    }

    if (walk != WalkType::Stop) {

        nudgeUp = false;
        nudgeDown = false;
        nudgeLeft = false;
        nudgeRight = false;

    }

    return walk;
    
}

bool MapInformation::isEmptyTile(MapTiles tile) {

    switch (tile) {

        case MapTiles::OpenDoor:
        case MapTiles::UpStairs:
        case MapTiles::DownStairs:
        case MapTiles::Empty:
        case MapTiles::CornerFill:
        case MapTiles::OpenChest:
        case MapTiles::Rubble:
        case MapTiles::PressPlate_Up:
        case MapTiles::PressPlate_Down:
        case MapTiles::DoorLHSOpen:
        case MapTiles::DoorRHSOpen:
        case MapTiles::DoorTOPOpen:
        case MapTiles::DoorBOTOpen:
        case MapTiles::SpearDoorLHSOpen:
        case MapTiles::SpearDoorRHSOpen:
        case MapTiles::SpearDoorTOPOpen:
        case MapTiles::SpearDoorBOTOpen:
        case MapTiles::WormHole_F0:
            return true;

        default:
            return false;

    }

}


bool MapInformation::isWallTile(MapTiles tile) {

    switch (tile) {

        case MapTiles::StraightTOP:
        case MapTiles::StraightBOT:
        case MapTiles::StraightLHS:
        case MapTiles::StraightRHS:
        case MapTiles::StraightTorchTOP_F0:
        case MapTiles::StraightTorchTOP_F1:
        case MapTiles::StraightTorchBOT_F0:
        case MapTiles::StraightTorchBOT_F1:
        case MapTiles::StraightTorchLHS_F0:
        case MapTiles::StraightTorchLHS_F1:
        case MapTiles::StraightTorchRHS_F0:
        case MapTiles::StraightTorchRHS_F1:
        case MapTiles::CornerLL:
        case MapTiles::CornerLR:
        case MapTiles::CornerTL:
        case MapTiles::CornerTR:
        case MapTiles::StraightLR:
        case MapTiles::StraightTB:
        case MapTiles::FullBlockWall:
        case MapTiles::FullSquare:
        case MapTiles::EndTRL:
        case MapTiles::EndRBL:
        case MapTiles::EndTBL:
        case MapTiles::EndTRB:
            return true;

        default:
            return false;

    }

}