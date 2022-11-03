#include<SFML/Graphics.hpp>
#include<ctime>
#include<vector>
using namespace sf;
using namespace std;

#define WIDTH 800        //����
#define HEIGHT 1000       //����
#define BAR_COUNT 10    //��� bar ����
static const float GRAVITY = 0.2f;    //�߷�

//�÷��̾� Ŭ����
class Player
{
private:
    //�δ��� ��ġ
    int x;
    int y;
    //�δ��� ũ��
    int imgWidth;
    int imgHeight;

    float dy;
    //�δ��� ���� �̹���
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
        if (Keyboard::isKeyPressed(Keyboard::Right)) //�������̵�
        {
            x += 4;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) //�����̵�
        {
            x -= 4;
        }
        if (x <= -50)    //���� �� ���� ���ϰ�
        {
            x = -50;
        }
        if (x >= WIDTH - 150)    //������ �� ���� ���ϰ�
        {
            x = WIDTH - 150;
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

// ���� bar Ŭ����
class Bar
{
private:
    struct Pos {
        int x;
        int y;
    };
    vector<Pos> vBar;
    int imgWidth;
    Sprite* imgBar;
    Texture t;
public:
    Bar()
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        t.loadFromFile("images/ch4_bar1.png");
        imgBar = new Sprite(t);

        imgWidth = imgBar->getTexture()->getSize().x;

        for (int i = 0; i < BAR_COUNT; ++i)
        {
            Pos p;
            p.x = rand() % WIDTH - imgWidth / 2;
            p.y = rand() % HEIGHT;
            vBar.push_back(p);
        }

        vBar[0].y = HEIGHT - 200;
    }
    ~Bar()
    {
        delete(imgBar);
    }
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