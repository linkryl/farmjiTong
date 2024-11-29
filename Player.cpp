#include "Player.h"
void Player::go(const Direction direction)
{
	// int-动作映射map
	// 基准速度
	double base_speed = 75;
	static std::map<int, Vec2> intToMove = { {UP, Vec2(0, speed * base_speed)}, {RIGHT, Vec2(speed * base_speed, 0)},
	{ DOWN, Vec2(0, -speed * base_speed * 4 / 3) }, {LEFT, Vec2(-speed * base_speed, 0)} };
	// DOWN动画要多两帧
	const int upper_limit = direction == DOWN ? 8 : 6;
	// 每一帧动画的间隔
	const float frameGap = 0.2;
	// 动作
	auto move = MoveBy::create(upper_limit * frameGap, intToMove[direction]);
	// 数字映射到string
	std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
	// 动画
	// 动画帧序列map
	//static std::map<std::string, Vector<SpriteFrame*>> spriteFramesMap;
	Vector<SpriteFrame*> spriteFrames;
	auto direct = numToString[direction];
	auto path = "/motion/" + direct + "/" + direct + ".plist";
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
	for (int i = 0; i < upper_limit; i++)
	{
		std::string direct = numToString[direction];
		std::string index = std::to_string(i);
		auto imageName = direct + "-" + index + ".png";
		auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
		//auto frame = SpriteFrame::create(path, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
		/*if (spriteFramesMap.find(direct) != spriteFramesMap.end() && spriteFramesMap[direct].empty())
			spriteFramesMap[direct].pushBack(frame);*/
		spriteFrames.pushBack(frame);
	}
	Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
	Animate* animate = Animate::create(ani);
	// 动作并行Spawn
	auto moveSpawn = Spawn::createWithTwoActions(move, animate);
	moveSpawn->setTag(direction);
	// 这个if条件保证了动作连贯进行而不是中途被打断
	if (this->_actionManager->getActionByTag(direction, this) == nullptr)
	{
		// UP是第一个枚举类，LEFT是最后一个
		for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
			// 打断其他方向的动作
			if (i != direction)
				this->stopActionByTag(i);
		this->runAction(moveSpawn);
	}
	
}
Player* Player::create(const std::string& path)
{
	Player* player = new (std::nothrow) Player();
	if (player && player->initWithFile(path))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}