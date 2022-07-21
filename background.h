#ifndef BACK
#define BACK

class background
{
private:
	Image image;
	Texture texture;
	Sprite sprite;
	std::string m_adress;
	float m_scale_x;
	float m_scale_y;
	float m_x;
	float m_y;
public:
	background(std::string adress = "image\\page.png", float scale_x = 1.0f, float scale_y = 1.0f, float x = 0.0f, float y = 0.0f)
		:m_adress(adress), m_scale_x(scale_x), m_scale_y(m_scale_y), m_x(x), m_y(y)
	{
		image.loadFromFile(m_adress);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale(Vector2f(m_scale_x, m_scale_y));
		sprite.setPosition(Vector2f(m_x, m_y));
	}

	Sprite access_sprite()
	{
		return sprite;
	}
};
#endif
