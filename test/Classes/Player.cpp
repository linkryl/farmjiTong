#include "Player.h"
#include <functional>

void PlayerPart::go(const Direction direction)
{
	// ��׼�ٶ�
	double base_speed = 60;
	// һ��6֡
	const int upper_limit = 6;
	// ÿһ֡�����ļ��
	const float frameGap = 0.2;
	int originDistance = speed * base_speed, distance = originDistance;
	for (int i = 1; i <= originDistance; ++i) {
		Vec2 pos = modifyVec2(Vec2(getPosition()), direction, i);
		if (!can_move(getPlayer()->getTiledMap(), pos, direction)) {
			distance = i - 1;
			break;
		}
	}
	// ����
	Vec2 moveVec2 = generateVec2(direction, distance);
	auto moveAction = MoveBy::create(upper_limit * frameGap * distance / originDistance, moveVec2);
	// ����ӳ�䵽string
	std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
	// ����
	// ����֡����map
	//static std::map<std::string, Vector<SpriteFrame*>> spriteFramesMap;
	Vector<SpriteFrame*> spriteFrames;
	auto direct = numToString[direction];
	auto path = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + ".plist";
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
	for (int i = 0; i < upper_limit; i++)
	{
		std::string direct = numToString[direction];
		std::string index = std::to_string(i);
		auto imageName = part_name + "_" + direct + "_" + index + ".png";
		auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
		//auto frame = SpriteFrame::create(path, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
		/*if (spriteFramesMap.find(direct) != spriteFramesMap.end() && spriteFramesMap[direct].empty())
			spriteFramesMap[direct].pushBack(frame);*/
		spriteFrames.pushBack(frame);
	}
	////////*Something goes wrong here*/
	Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
	Animate* animate = Animate::create(ani);
	/////////////

	// ��������Spawn
	auto moveSpawn = Spawn::createWithTwoActions(moveAction, animate);

	const size_t hash_value = partNameHash[part_name] + direction + hashValue[GO];
	moveSpawn->setTag(hash_value);
	// ���if������֤�˶���������ж�������;�����
	const auto sign = this->_actionManager->getActionByTag(hash_value, this);
	if (this->_actionManager->getActionByTag(hash_value, this) == nullptr)
	{
		// UP�ǵ�һ��ö���࣬LEFT�����һ��
		for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
			// �����������Ķ���
			if (i != direction)
				this->stopActionByTag(i - direction + hash_value);
		if (can_move(getPlayer()->getTiledMap(), getPosition(), direction)) {
			this->runAction(moveSpawn);
		}
		
	}

}
void PlayerPart::stand(const Direction direction)
{
	// ����ӳ�䵽string
	std::map<int, std::string> numToString = { {UP,"walk_up"}, {RIGHT, "walk_right"}, {LEFT, "walk_left"}, {DOWN, "walk_down"} };
	auto direct = numToString[direction];
	auto imagePath = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + "_5.png";
	this->stopAllActions();
	this->setTexture(imagePath);
}

void PlayerPart::light_hit(const Direction direction)
{
	// һ��6֡
	const int upper_limit = 6;
	// ÿһ֡�����ļ��
	const float frameGap = 0.05;
	// ����ӳ�䵽string
	std::map<int, std::string> numToString = { {UP,"light_hit_up"}, {RIGHT, "light_hit_right"}, {LEFT, "light_hit_left"}, {DOWN, "light_hit_down"} };
	// ����
	Vector<SpriteFrame*> spriteFrames;
	auto direct = numToString[direction];
	auto path = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + ".plist";
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
	for (int i = 0; i < upper_limit; i++)
	{
		std::string direct = numToString[direction];
		std::string index = std::to_string(i);
		auto imageName = part_name + "_" + direct + "_" + index + ".png";
		auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
		spriteFrames.pushBack(frame);
	}
	Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
	Animate* animate = Animate::create(ani);

	const size_t hash_value = hashValue[LIGHT_HIT];
	// const size_t hash_value = hasher(part_name) + direction + hashValue[LIGHT_HIT];
	animate->setTag(partNameHash[part_name] + direction + hash_value);
	// ���if������֤�˶���������ж�������;�����
	const auto sign = this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this);
	if (this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this) == nullptr)
	{
		// UP�ǵ�һ��ö���࣬LEFT�����һ��
		for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
			// �����������Ķ���
			for (const auto& item : hashValue)
			{
				int val = item.second;
				if (val != hash_value || i != direction)
				{
					int partHash = partNameHash[part_name];
					int temp = i + partNameHash[part_name] + val;
					//this->stopActionByTag(i - direction + hash_value);
					this->stopActionByTag(i + partNameHash[part_name] + val);
				}
			}
		this->runAction(animate);
	}
}
void PlayerPart::heavy_hit(const Direction direction)
{
	// һ��6֡
	const int upper_limit = 6;
	// ÿһ֡�����ļ��
	const float frameGap = 0.10;
	// ����ӳ�䵽string
	std::map<int, std::string> numToString = { {UP,"heavy_hit_up"}, {RIGHT, "heavy_hit_right"}, {LEFT, "heavy_hit_left"}, {DOWN, "heavy_hit_down"} };
	// ����
	Vector<SpriteFrame*> spriteFrames;
	auto direct = numToString[direction];
	auto path = "/motion/" + direct + "/" + part_name + "/" + part_name + "_" + direct + ".plist";
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path);
	for (int i = 0; i < upper_limit; i++)
	{
		std::string direct = numToString[direction];
		std::string index = std::to_string(i);
		auto imageName = part_name + "_" + direct + "_" + index + ".png";
		auto frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
		spriteFrames.pushBack(frame);
	}
	Animation* ani = Animation::createWithSpriteFrames(spriteFrames, frameGap);
	Animate* animate = Animate::create(ani);

	const size_t hash_value = hashValue[HEAVY_HIT];
	// const size_t hash_value = hasher(part_name) + direction + hashValue[LIGHT_HIT];
	animate->setTag(partNameHash[part_name] + direction + hash_value);
	// ���if������֤�˶���������ж�������;�����
	const auto sign = this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this);
	if (this->_actionManager->getActionByTag(partNameHash[part_name] + direction + hash_value, this) == nullptr)
	{
		// UP�ǵ�һ��ö���࣬LEFT�����һ��
		for (Direction i = UP; i <= LEFT; i = (Direction)(i + 1))
			// �����������Ķ���
			for (const auto& item : hashValue)
			{
				int val = item.second;
				if (val != hash_value || i != direction)
				{
					int partHash = partNameHash[part_name];
					int temp = i + partNameHash[part_name] + val;
					//this->stopActionByTag(i - direction + hash_value);
					this->stopActionByTag(i + partNameHash[part_name] + val);
				}
			}
		this->runAction(animate);
	}
}

PlayerPart* PlayerPart::create(const std::string& path, const std::string& part_name)
{
	PlayerPart* playerPart = new PlayerPart(part_name);
	if (playerPart && playerPart->initWithFile(path))
	{
		playerPart->autorelease();
		return playerPart;
	}
	CC_SAFE_DELETE(playerPart);
	return nullptr;
}