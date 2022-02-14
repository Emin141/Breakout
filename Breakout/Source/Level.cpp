#include "Level.h"

Level::Level() {
    mRowCount = 0;
    mColumnCount = 0;
    mRowSpacing = 0;
    mColumnSpacing = 0;
	mPlayerScore = 0;

	mBrickBreakScore.fill(0);
}

void Level::arrangeBricks(const sf::RenderWindow& window) {
	// Clears the brick list first
	mBrickList.clear();

	// Defining the size of a brick
	sf::Vector2f brickSize(
		(window.getSize().x - (mColumnCount + 1) * mColumnSpacing) / mColumnCount,
		// Same size in order to be square 
		(window.getSize().x - (mColumnCount + 1) * mRowSpacing) / mColumnCount
	);

	// Sets all brick sizes
	for (auto& brick : mBrick) {
		brick.setSize(brickSize);
	}

	// Defining a position which will track the brick which is currently being placed
	sf::Vector2f currentBrickPosition(
		mColumnSpacing,
		mRowSpacing
	);

	// Parsing the positions
	unsigned int columnCounter = 1;
	for (size_t i = 0; i < mBrickLayout.size() ; i++) {
		switch (mBrickLayout[i]) {
		case 'S':
			mBrick[SOFT].setPosition(currentBrickPosition);
			mBrickList.emplace_back(mBrick[SOFT]);
			currentBrickPosition.x += brickSize.x + mColumnSpacing;
			if (columnCounter % mColumnCount == 0) {
				columnCounter = 0;
				currentBrickPosition.y += brickSize.y + mRowSpacing;
				currentBrickPosition.x = mColumnSpacing;
			}
			columnCounter++;
			break;
		case 'M':
			mBrick[MEDIUM].setPosition(currentBrickPosition);
			mBrickList.emplace_back(mBrick[MEDIUM]);
			currentBrickPosition.x += brickSize.x + mColumnSpacing;
			if (columnCounter % mColumnCount == 0) {
				columnCounter = 0;
				currentBrickPosition.y += brickSize.y + mRowSpacing;
				currentBrickPosition.x = mColumnSpacing;
			}
			columnCounter++;
			break;
		case 'H':
			mBrick[HARD].setPosition(currentBrickPosition);
			mBrickList.emplace_back(mBrick[HARD]);
			currentBrickPosition.x += brickSize.x + mColumnSpacing;
			if (columnCounter % mColumnCount == 0) {
				columnCounter = 0;
				currentBrickPosition.y += brickSize.y + mRowSpacing;
				currentBrickPosition.x = mColumnSpacing;
			}
			columnCounter++;
			break;
		case 'I':
			mBrick[IMPENETRABLE].setPosition(currentBrickPosition);
			mBrickList.emplace_back(mBrick[IMPENETRABLE]);
			currentBrickPosition.x += brickSize.x + mColumnSpacing;
			if (columnCounter % mColumnCount == 0) {
				columnCounter = 0;
				currentBrickPosition.y += brickSize.y + mRowSpacing;
				currentBrickPosition.x = mColumnSpacing;
			}
			columnCounter++;
			break;
		case '_':
			currentBrickPosition.x += brickSize.x + mColumnSpacing;
			if (columnCounter % mColumnCount == 0) {
				columnCounter = 0;
				currentBrickPosition.y += brickSize.y + mRowSpacing;
				currentBrickPosition.x = mColumnSpacing;
			}
			columnCounter++;
			break;
		default:
			break;
		}
	}

	// Setting textures
	for (auto& brick : mBrickList) {
		switch (brick.getBrickType()) {
		case SOFT:
			brick.setTexture(mBrickTexture[SOFT]);
			break;
		case MEDIUM:
			brick.setTexture(mBrickTexture[MEDIUM]);
			break;
		case HARD:
			brick.setTexture(mBrickTexture[HARD]);
			break;
		case IMPENETRABLE:
			brick.setTexture(mBrickTexture[IMPENETRABLE]);
			break;
		}
	}
}

void Level::loadFromXML(const std::string& filename, const sf::RenderWindow& window) {

    // Paddle
	mPaddleTexture.loadFromFile("Resource/Textures/Paddle.png");
	mPaddle.create(
		sf::Vector2f(200.0f, 25.0f),
		sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y)
	);
	mPaddle.setTexture(mPaddleTexture);

    // Ball
	mBallTexture.loadFromFile("Resource/Textures/Ball.png");
	mBall.create(
		sf::Vector2f(32, 32),
		sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f)
	);
	mBall.setTexture(mBallTexture);
	mBall.resetVelocity();

    // Bricks
    using namespace tinyxml2;
    XMLDocument source;
    source.LoadFile(filename.c_str());

    XMLElement* pLevelElement = source.RootElement();
    if (pLevelElement == NULL) {
        std::cout << "Cannot read Level element at " << filename << std::endl;
        std::cin.get();
        exit(-1);
    }

    mRowCount = strtod(pLevelElement->Attribute("RowCount"), NULL);
    mColumnCount = strtod(pLevelElement->Attribute("ColumnCount"), NULL);
    mRowSpacing = strtod(pLevelElement->Attribute("RowSpacing"), NULL);
    mColumnSpacing = strtod(pLevelElement->Attribute("ColumnSpacing"), NULL);

    XMLElement* pBrickTypesElement = pLevelElement->FirstChildElement("BrickTypes");
    if (pBrickTypesElement == NULL) {
        std::cout << "Cannot read BrickTypes element at " << filename << std::endl;
        std::cin.get();
        exit(-1);
    }

    // TAKE GOOD CARE! Huge difference between "Type" and "Types"

    // Brick data
    XMLElement* pBrickTypeElement = pBrickTypesElement->FirstChildElement("BrickType");
    unsigned int currentBrickType = 0;
    while (currentBrickType < 4) {
        // Loading data that can be copied without much memory loss
		mBrick[currentBrickType].setAttributes(pBrickTypeElement);
		
		// Loading data that should be shared among bricks
		mHitSoundBuffer[currentBrickType].loadFromFile("Resource/" + std::string(pBrickTypeElement->Attribute("HitSound")));
		mHitSound[currentBrickType].setBuffer(mHitSoundBuffer[currentBrickType]);

		if (currentBrickType < 3) {
			mBreakSoundBuffer[currentBrickType].loadFromFile("Resource/" + std::string(pBrickTypeElement->Attribute("BreakSound")));
			mBreakSound[currentBrickType].setBuffer(mBreakSoundBuffer[currentBrickType]);

			mBrickBreakScore[currentBrickType] = strtod(pBrickTypeElement->Attribute("BreakScore"), NULL);
		}

		mBrickTexture[currentBrickType].loadFromFile("Resource/" + std::string(pBrickTypeElement->Attribute("Texture")));
		

		currentBrickType++;
        pBrickTypeElement = pBrickTypeElement->NextSiblingElement("BrickType");
    }

    pLevelElement = pLevelElement->FirstChildElement("Bricks");
    mBrickLayout = pLevelElement->GetText();

	mPlayerScore = 0; // Reset player score

	arrangeBricks(window);
}

void Level::draw(sf::RenderWindow& window) {
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
	
	// Loss condition:
	if ((mBall.getPosition().y + mBall.getSize().y) > window.getSize().y) {
		gameIsOver = true;
		return;
	}

	CollisionSide collisionSide;
	if (mBall.collidedWith(mPaddle, collisionSide))
	{
		mBall.redirect(mPaddle.getCenter().x, mPaddle.getSize().x);
		mBall.rewindPosition();
	}

	// Brick iterator
	// Needs to be implemented this way instead of auto brick : mBrickList because objects need to be removed
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
				mBreakSound[itBrick->getBrickType()].play();

				mPlayerScore += mBrickBreakScore[itBrick->getBrickType()];
				mBrickList.remove(*itBrick++);
			}
			else {
				mHitSound[itBrick->getBrickType()].play();
			}
		}
	}

	mBall.updatePosition(window, dt);
}
