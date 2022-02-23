#include "Level.h"
#include "plog/Log.h"

#define OFFSET (3.5f)

Level::Level() {
	mRowCount = 0;
	mColumnCount = 0;
	mRowSpacing = 0;
	mColumnSpacing = 0;
	mPlayerScore = 0;
	mBreakableBricksNum = 0;
}

void Level::loadFromXML(const std::string& filename, const sf::RenderWindow& window) {

	// Paddle
	try {
		if (!mPaddleTexture.loadFromFile("Resource/Textures/Paddle.png"))
			throw "Cannot load resource at Resource/Textures/Paddle.png";
	}
	catch (std::string message) {
		PLOGD << message;
		exit(-1);
	}
	mPaddle.create(
		sf::Vector2f(window.getSize().x / 10.0f, window.getSize().y / 40.0f),
		sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y)
	);
	mPaddle.setTexture(mPaddleTexture);

	// Ball
	try {
		if (!mBallTexture.loadFromFile("Resource/Textures/Ball.png"))
			throw "Cannot load resource at Resource/Textures/Ball.png";
	}
	catch (std::string message) {
		PLOGD << message;
		exit(-1);
	}
	mBall.create(
		sf::Vector2f(mPaddle.getSize().y, mPaddle.getSize().y), // The ball is a "square" with side length equal to the thickness of the paddle
		sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f)
	);
	mBall.setTexture(mBallTexture);
	mBall.resetVelocity();

	// Bricks and background
	using namespace tinyxml2;
	XMLDocument source;
	try {
		source.LoadFile(filename.c_str());

		XMLElement* pLevelElement = source.RootElement();

		mRowCount = strtod(pLevelElement->Attribute("RowCount"), nullptr);
		mColumnCount = strtod(pLevelElement->Attribute("ColumnCount"), nullptr);
		mRowSpacing = strtod(pLevelElement->Attribute("RowSpacing"), nullptr);
		mColumnSpacing = strtod(pLevelElement->Attribute("ColumnSpacing"), nullptr);
		if (!mBackgoundTexture.loadFromFile("Resource/" + std::string(pLevelElement->Attribute("BackgroundTexture")))) {
			throw "Cannot read background texture!";
		}
		mBackground.setPosition(0.0f, 0.0f);
		mBackground.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		mBackground.setTexture(&mBackgoundTexture);

		// Brick data
		XMLElement* pBrickTypesElement = pLevelElement->FirstChildElement("BrickTypes");

		// TAKE GOOD CARE! Huge difference between "Type" and "Types"
		XMLElement* pBrickTypeElement = pBrickTypesElement->FirstChildElement("BrickType");

		while (pBrickTypeElement) {
			BrickID currentBrickID;
			unsigned int currentHitPoints;

			// Loading data that has to be copied per brick object
			if (pBrickTypeElement->Attribute("Id") == nullptr) {
				throw "Cannot read attribute Id";
			}
			currentBrickID = pBrickTypeElement->Attribute("Id")[0];

			if (pBrickTypeElement->Attribute("HitPoints") == nullptr) {
				throw "Cannot read attribute HitPoints";
			}
			// Special case for impenetrable bricks
			if (currentBrickID == 'I') {
				currentHitPoints = -1; // Unsigned conversion will underflow to 2^32-1
			}
			else {
				currentHitPoints = strtod(pBrickTypeElement->Attribute("HitPoints"), nullptr);
			}

			// Creates the unique brick in the mBrick map
			mBrick.insert(std::pair(
				currentBrickID, Brick(currentBrickID, currentHitPoints)
			));

			// Loading data that should be shared among bricks
			mHitSoundBuffer.insert(std::pair(currentBrickID, sf::SoundBuffer()));
			if (!mHitSoundBuffer[currentBrickID].loadFromFile("Resource/" + std::string(pBrickTypeElement->Attribute("HitSound"))))
			{
				PLOGD << "Cannot read Resource/" + std::string(pBrickTypeElement->Attribute("HitSound"));
				exit(-1);
			}
			mHitSound.insert(std::pair(currentBrickID, sf::Sound()));
			mHitSound[currentBrickID].setBuffer(mHitSoundBuffer[currentBrickID]);

			// All but impenetrable have a break sound as well
			if (currentBrickID != 'I') {
				mBreakSoundBuffer.insert(std::pair(currentBrickID, sf::SoundBuffer()));
				if (!mBreakSoundBuffer[currentBrickID].loadFromFile("Resource/" + std::string(pBrickTypeElement->Attribute("BreakSound"))))
				{
					PLOGD << "Cannot read Resource/" + std::string(pBrickTypeElement->Attribute("BreakSound"));
					exit(-1);
				}
				mBreakSound.insert(std::pair(currentBrickID, sf::Sound()));
				mBreakSound[currentBrickID].setBuffer(mBreakSoundBuffer[currentBrickID]);
				mBrickBreakScore[currentBrickID] = strtod(pBrickTypeElement->Attribute("BreakScore"), NULL);
			}

			mBrickTexture.insert(std::pair(currentBrickID, sf::Texture()));
			if (!mBrickTexture[currentBrickID].loadFromFile("Resource/" + std::string(pBrickTypeElement->Attribute("Texture"))))
			{
				PLOGD << "Cannot read Resource/" + std::string(pBrickTypeElement->Attribute("Texture"));
				exit(-1);
			}
			pBrickTypeElement = pBrickTypeElement->NextSiblingElement("BrickType");
		}

		pLevelElement = pLevelElement->FirstChildElement("Bricks");
		mBrickLayout = pLevelElement->GetText();

		mPlayerScore = 0; // Reset player score

		arrangeBricks(window);
	}
	catch (std::string message) {
		PLOGD << message;
		exit(-1);
	}
}

void Level::arrangeBricks(const sf::RenderWindow& window) {
	// Clears the brick list first, in case it isn't empty because of previous allocations
	mBrickList.clear();

	// Defining the size of a brick
	sf::Vector2f brickSize(
		(window.getSize().x - (mColumnCount + 1) * mColumnSpacing) / mColumnCount,
		// Same size in order to be square 
		(window.getSize().x - (mColumnCount + 1) * mRowSpacing) / mColumnCount
	);

	// Sets all brick sizes
	for (auto& brick : mBrick) {
		brick.second.setSize(brickSize);
	}

	// The spacing scale
	// This is done so that the spacing can be tweaked, 1 means no tweaking ergo default
	float columnSpacingScale = 1.0f, rowSpacingScale = 1.0f;
	mColumnSpacing *= columnSpacingScale;
	mRowSpacing *= rowSpacingScale;

	// Defining a position which will track the brick which is currently being placed
	sf::Vector2f currentBrickPosition(
		mColumnSpacing * OFFSET, // left offset correction
		mRowSpacing
	);

	// Required to track the rows
	unsigned int columnCounter = 1;

	// Parsing the positions
	for (size_t i = 0; i < mBrickLayout.size(); i++) {
		if (mBrick.find(mBrickLayout[i]) != mBrick.end()	// Checks if the key is valid
			or mBrickLayout[i] == '_') {					// Or if the parsed character is an underline
			// If the character is NOT an underline:
			if (mBrickLayout[i] != '_') {
				mBrick[mBrickLayout[i]].setPosition(currentBrickPosition);
				mBrickList.emplace_back(mBrick[mBrickLayout[i]]);
				mBreakableBricksNum++;
			}
			// This will run regardless if underline or not
			currentBrickPosition.x += brickSize.x + mColumnSpacing;
			if (columnCounter % mColumnCount == 0) {
				columnCounter = 0;
				currentBrickPosition.y += brickSize.y + mRowSpacing;
				currentBrickPosition.x = mColumnSpacing * OFFSET;
			}
			columnCounter++;
		}
	}

	// Setting textures by reference to save memory
	for (auto& brick : mBrickList) {
		brick.setTexture(mBrickTexture[brick.getBrickID()]);
	}
}

void Level::draw(sf::RenderWindow& window) {
	window.draw(mBackground);
	mPaddle.draw(window);
	mBall.draw(window);
	for (auto& brick : mBrickList) {
		brick.draw(window);
	}
}

void Level::update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt, bool& gameIsOver) {
	mPaddle.setPosition(mousePosition, window);

	// Ball Collision with borders
	if (mBall.getPosition().x < 0)
	{
		mBall.xInvertVelocity();
		mBall.rewindPosition();
	}
	if (mBall.getPosition().y < 0)
	{
		mBall.yInvertVelocity();
		mBall.rewindPosition();
	}
	if ((mBall.getPosition().x + mBall.getSize().x) > window.getSize().x)
	{
		mBall.xInvertVelocity();
		mBall.rewindPosition();
	}

	// Game over conditions:
	if ((mBall.getPosition().y + mBall.getSize().y) > window.getSize().y) {
		gameIsOver = true;
		return;
	}

	if (mBreakableBricksNum == 0) {
		gameIsOver = true;
		return;
	}

	CollisionSide collisionSide;
	if (mBall.collidedWith(mPaddle, collisionSide))
		// in this case "collisionSide" is unused since the ball can collide with the paddle only from one side
	{
		mBall.redirect(mPaddle.getCenter().x, mPaddle.getSize().x);
		mBall.rewindPosition();
	}

	// Brick iterator
	// Needs to be implemented this way instead of auto brick : mBrickList because objects need to be removed
	// Iterating over the whole list is not the ideal option, however, the list and objects are relatively small
	// A better way would be to create a quadtree, and check recursively, but that is unneccessary complexness
	for (auto itBrick = mBrickList.begin(); itBrick != mBrickList.end(); ++itBrick) {
		if (mBall.collidedWith(*itBrick, collisionSide)) { // collisionSide is an "out" parameter
			switch (collisionSide) {
			case CollisionSide::LEFT:
				mBall.xInvertVelocity();
				mBall.rewindPosition();
				break;
			case CollisionSide::RIGHT:
				mBall.xInvertVelocity();
				mBall.rewindPosition();
				break;
			case CollisionSide::TOP:
				mBall.yInvertVelocity();
				mBall.rewindPosition();
				break;
			case CollisionSide::BOTTOM:
				mBall.yInvertVelocity();
				mBall.rewindPosition();
				break;
			default:
				break;
			}
			itBrick->decreaseHitPoints();
			if (itBrick->isDead()) {
				mBreakSound[itBrick->getBrickID()].play();
				mPlayerScore += mBrickBreakScore[itBrick->getBrickID()];
				mBreakableBricksNum--;

				mBrickList.remove(*itBrick++);
			}
			else {
				mHitSound[itBrick->getBrickID()].play();
			}
		}
	}

	mBall.updatePosition(window, dt);
}
