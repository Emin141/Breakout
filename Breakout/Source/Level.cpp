#include "Level.h"

Level::Level() {
    mRowCount = 0;
    mColumnCount = 0;
    mRowSpacing = 0;
    mColumnSpacing = 0;
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
        mBrick[currentBrickType++].setAttributes(pBrickTypeElement);
        pBrickTypeElement = pBrickTypeElement->NextSiblingElement("BrickType");
    }

    pLevelElement = pLevelElement->FirstChildElement("Bricks");
    mBrickLayout = pLevelElement->GetText();
    std::cout << mBrickLayout << "\n";
}

void Level::Draw(sf::RenderWindow& window) {
	mPaddle.Draw(window);
	mBall.Draw(window);
	// Draw all bricks
}

void Level::Update(const sf::Vector2i& mousePosition, const sf::RenderWindow& window, const float dt) {
	mPaddle.SetPosition(mousePosition, window);

	// Ball Collision with borders
	if (mBall.GetPosition().x < 0) mBall.XInvertVelocity();
	if (mBall.GetPosition().y < 0) mBall.YInvertVelocity();
	if ((mBall.GetPosition().x + mBall.GetSize().x) > window.getSize().x) mBall.XInvertVelocity();
	
	// Loss condition:
	if ((mBall.GetPosition().y + mBall.GetSize().y) > window.getSize().y) mBall.YInvertVelocity();


	if (mBall.CollidedWith(mPaddle)) 
	{
		mBall.YInvertVelocity();

		// Kicks the ball out of the collision box
		mBall.SetPosition(
			{
				mBall.GetPosition().x, 
				mPaddle.GetPosition().y - mBall.GetSize().y - 1.0f
			}
		);
	}

	mBall.UpdatePosition(window, dt);
}
