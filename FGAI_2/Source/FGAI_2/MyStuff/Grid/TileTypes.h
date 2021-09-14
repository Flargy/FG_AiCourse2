#pragma once

#include "TileTypes.generated.h"

UENUM()
enum ETileType
{
  Water     UMETA(DisplayName = "Water"),
  Wall      UMETA(DisplayName = "Wall"),
  Ground    UMETA(DisplayName = "Ground"),
};