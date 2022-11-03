#include<SFML/Graphics.hpp>
#include<ctime>
#include<vector>
using namespace sf;
using namespace std;

#define WIDTH 800        //가로
#define HEIGHT 1000       //세로
#define BAR_COUNT 10    //밟는 bar 개수
static const float GRAVITY = 0.2f;    //중력

//플래이어 클래스
class Player
{
private:
    int x;
    int y;
    int imgWidth;
    int imgHeight;
    float dy;
    Sprite* imgJump;
    Sprite* imgReady;
    Texture t1;
    Texture t2;
    bool jumpFlag;
private:
    const Sprite& GetImg()
    {
        if (jumpFlag)
        {
            return *imgJump;
        }
        else
        {
            return *imgReady;
        }
    }

public:
    Player() : dy(0), jumpFlag(true)
    {
        x = static_cast<int>(WIDTH / 2);
        y = static_cast<int>(HEIGHT / 2);

        t1.loadFromFile("images/mole1.png");
        t2.loadFromFile("images/mole2.png");

        imgJump = new Sprite(t1);
        imgReady = new Sprite(t2);

        imgWidth = static_cast<int>(imgReady->getTexture()->getSize().x);
        imgHeight = static_cast<int>(imgReady->getTexture()->getSize().y);
    }
    ~Player()
    {
        delete(imgJump);
        delete(imgReady);
    }

    void SetPosition()
    {
        imgReady->setPosition(x, y);
        imgJump->setPosition(x, y);
    }
    void Move()
    {
        if (Keyboard::isKeyPressed(Keyboard::Right)) //오른쪽이동
        {
            x += 4;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) //왼쪽이동
        {
            x -= 4;
        }
        if (x <= 0)    //왼쪽 벽 뚫지 못하게
        {
            x = 0;
        }
        if (x >= WIDTH - imgWidth)    //오른쪽 벽 뚫지 못하게
        {
            x = WIDTH - imgWidth;
        }

        jumpFlag = true;
        dy += GRAVITY;
        y += static_cast<int>(dy);

        if (y > HEIGHT - imgHeight)
        {
            jumpFlag = false;
            dy = -10;
        }

    }
    void Draw(RenderWindow& app)
    {
        app.draw(GetImg());
    }

    float GetDy() const
    {
        return dy;
    }
    int GetY() const
    {
        return y;
    }
    int GetX() const
    {
        return x;
    }
    int GetWidth() const
    {
        return imgWidth;
    }
    int GetHeight() const
    {
        return imgHeight;
    }
    void SetY(int _y)
    {
        y = _y;
    }
    void Jump()
    {
        jumpFlag = false;
        dy = -10;
    }
};

// 점프 bar 클래스
class Bar
{
private:
    int x;
    int y;
    int imgWidth;
public:
   

};

int main(void)
{
    RenderWindow app(VideoMode(WIDTH, HEIGHT), "JumpUp Mole!");
    app.setFramerateLimit(60);

    Player* mole = new Player();
    Bar* bar = new Bar();

    while (app.isOpen())
    {
        Event e;
        if (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                app.close();
            }
        }
        mole->Move();
        mole->SetPosition();

        //draw
        app.clear(Color::White);
        mole->Draw(app);
        app.display();
    }

    delete(bar);
    delete(mole);
    return 0;
}