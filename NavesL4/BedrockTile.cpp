#include "BedrockTile.h"
BedrockTile::BedrockTile(float x, float y, Game* game):Tile("res/Items/BedrockBlock.png", x, y, game) {
	identifier = ItemEnum::Bedrock;
	toolNeededForBreaking = ItemEnum::Default;
}