#include "Level.h"

enum BrickType { // NOT a class enum
	SOFT = 0,
	MEDIUM = 1,
	HARD = 2,
	IMPENETRABLE = 3,
	SIZE = 4
};

Level::Level() {
    mRowCount = 0;
    mColumnCount = 0;
    mRowSpacing = 0;
    mColumnSpacing = 0;
	mPlayerScore = 0;
}

void Level::ArrangeBricks(const sf::RenderWindow& window) {
	// Defining the size of a brick
	sf::Vector2f brickSize(
		(window.getSize().x - (mColumnCount + 1) * mColumnSpacing) / mColumnCount,
		// Same size in order to be square 
		(window.getSize().x - (mColumnCount + 1) * mRowSpacing) / mColumnCount
	);

	// Sets all brick sizes
	for (auto& brick : mBrick) {
		brick.SetSize(brickSize);
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
			mBrick[SOFT].SetPosition(currentBrickPosition);
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
			mBrick[MEDIUM].SetPosition(currentBrickPosition);
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
			mBrick[HARD].SetPosition(currentBrickPosition);
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
			mBrick[IMPENETRABLE].SetPosition(currentBrickPosition);
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
}

void Level::LoadFromXML(const std::string& filename, const sf::RenderWindow& window) {

    // Paddle
	mPaddleTexture.loadFromFile("Resource/Textures/Paddle.png");
	mPaddle.Create(
		mPaddleTexture,
		sf::Vector2f(200.0f, 25.0f),
		sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y)
	);

    // Ball
	mBallTexture.loadFromFile("Resource/Textures/Ball.png");
	mBall.Create(
		mBallTexture,
		sf::Vector2f(32, 32),
		sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f)
	);
	mBall.ResetVelocity();

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
        mBrick[currentBrickType++].SetAttributes(pBrickTypeElement);
        pBrickTypeElement = pBrickTypeElement->NextSiblingElement("BrickType");
    }

    pLevelElement = pLevelElement->FirstChildElement("Bricks");
    mBrickLayout = pLevelElement->GetText();

	// Important call
	ArrangeBricks(window);
}

void Level::Draw(sf::RenderWindow& window) {
	mPaddle.Draw(window);
	mBall.Draw(window);
	for (auto& brick : mBrickList) {
		brick.Draw(window);
	}
}

void Level::Update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt, bool& gameIsOver) {
	mPaddle.SetPosition(mousePosition, window);

	// Ball Collision with borders
	if (mBall.GetPosition().x < 0)
	{
		mBall.XInvertVelocity();
		mBall.RewindPosition();
	}
	if (mBall.GetPosition().y < 0)
	{
		mBall.YInvertVelocity();
		mBall.RewindPosition();
	}
	if ((mBall.GetPosition().x + mBall.GetSize().x) > window.getSize().x)
	{
		mBall.XInvertVelocity();
		mBall.RewindPosition();
	}
	
	// Loss condition:
	if ((mBall.GetPosition().y + mBall.GetSize().y) > window.getSize().y) {
		gameIsOver = true;
		return;
	}

	CollisionSide collisionSide;
	if (mBall.CollidedWith(mPaddle, collisionSide))
	{
		mBall.Redirect(mPaddle.GetCenter().x, mPaddle.GetSize().x);
		mBall.RewindPosition();
	}

	// Brick iterator
	// Needs to be implemented this way instead of auto brick : mBrickList because objects need to be removed
	for (auto itBrick = mBrickList.begin(); itBrick != mBrickList.end(); ++itBrick) {
		if (mBall.CollidedWith(*itBrick, collisionSide)) { // collisionSide is an "out" parameter
			switch (collisionSide) {
			case CollisionSide::LEFT:
				mBall.XInvertVelocity();
				mBall.RewindPosition();
				break;
			case CollisionSide::RIGHT:
				mBall.XInvertVelocity();
				mBall.RewindPosition();
				break;
			case CollisionSide::TOP:
				mBall.YInvertVelocity();
				mBall.RewindPosition();
				break;
			case CollisionSide::BOTTOM:
				mBall.YInvertVelocity();
				mBall.RewindPosition();
				break;
			default:
				break;
			}
			itBrick->DecreaseHitPoints();
			if (itBrick->IsDead()) {
				itBrick->PlayBreakSound();
				mPlayerScore += itBrick->GetBreakScore(); // Destroys it too fast
				mBrickList.remove(*itBrick++);
			}
			else {
				itBrick->PlayHitSound();
			}
		}
	}

	mBall.UpdatePosition(window, dt);
}
