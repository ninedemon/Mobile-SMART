#include <SFML/Graphics.hpp>
using namespace sf;
#include "background.h"
#include "blanks.h"
#include "suggestion output.h"
#include "menu options.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>



int main()
{
	//create main window
	RenderWindow window(VideoMode(700, 900), "MobileSmart",Style::Default);
	//menu switching tool
	unsigned char menu_switch = 0;
	//turn on the menu with option 0
	menu_switch |= option_0;
	//universal string for various needs
	std::string universal="";
	//database for quanity of products
	std::vector <int> quanity_of_products;
	quanity_of_products.resize(1);
	//universal int for various needs
	int ani = 0;

	while (true)
	{
		quanity_of_products[ani] = 0;
		ani++;	
		if (ani == static_cast<int>(quanity_of_products.size()))
			break;
	}
	
	//database for name of products
	std::vector <std::string> name_of_products;
	name_of_products.resize(1);
	//database for product description
	std::vector <std::string> product_description;
	product_description.resize(1);
	//opening the server
	std::ifstream server_input;
	server_input.open("server.txt");
	assert(server_input.is_open() && "server is not open");
	ani = 0;
	//output data
	while (!server_input.eof())
	{
		std::getline(server_input, universal);
		if (universal == "NPopen")
		{
			while (true)
			{
				universal = "";
				std::getline(server_input, universal);
				if (universal == "NP close")
				{
					universal = "";
					break;
				}
				name_of_products[ani] = universal;
				ani++;
				if (ani == name_of_products.size())
					name_of_products.resize(ani + 1);
			}
		}
		ani = 0;

		std::getline(server_input, universal);
		if (universal == "QPopen")
		{
			int mini = 0;
			std::stringstream lex;
			while (true)
			{
				universal = "";
				std::getline(server_input, universal);
				if (universal == "QPclose")
				{
					universal = "";
					break;
				}
				lex << universal;
				lex >> mini;
				lex.str("");
				lex.clear();
				quanity_of_products[ani] = mini;
				ani++;
				if (ani == quanity_of_products.size())
					quanity_of_products.resize(ani + 1);
			}
		}
		ani = 0;
		std::getline(server_input, universal);
		if (universal == "PDopen")
		{
			while (true)
			{
				universal = "";
				std::getline(server_input, universal);
				if (universal == "PDclose")
				{
					universal = "";
					break;
				}
				product_description[ani] = universal;
				ani++;
				if (ani == product_description.size())
					product_description.resize(ani + 1);
			}
		}
	}
	server_input.close();
	
	//The main application cycle. Executed while the window is open
	while (window.isOpen())
	{
		Vector2i mousepozition = Mouse::getPosition(window);
		//menu with option0
		if (menu_switch & option_0)
		{
			Event event;
			while (window.pollEvent(event))
			{
				// The user clicked on the "cross" and wants to close the window?
				if (event.type == Event::Closed)
					// then we close it
					window.close();
			}
			window.clear(Color(255, 130, 4));
			background first("image\\FON.png", 2.0, 2.0, 0.0f, 900.0f);
			window.draw(first.access_sprite());
			//create button
			blanks one(250.0f, 65.0f, 225.0f, 180.0f, 89, 78, 233, 10.0f, 24, 16, 122);
			window.draw(one.access_squa());
			blanks two(250.0f, 65.0f, 225.0f, 280.0f, 89, 78, 233, 10.0f, 24, 16, 122);
			window.draw(two.access_squa());
			blanks three(250.0f, 120.0f, 225.0f, 380.0f, 89, 78, 233, 10.0f, 24, 16, 122);
			window.draw(three.access_squa());
			blanks four(250.0f, 65.0f, 225.0f, 550.0f, 89, 78, 233, 10.0f, 24, 16, 122);
			window.draw(four.access_squa());
			//create text on the button
			suggestion_output one_text("fonts\\FORTE.ttf", "Start", 44, 300.0f, 182.0f);
			window.draw(one_text.access_text());
			suggestion_output two_text("fonts\\FORTE.ttf", "Viewing", 44, 280.0f, 282.0f);
			window.draw(two_text.access_text());
			suggestion_output three_text("fonts\\FORTE.ttf", "Temporarily\n  log out", 44, 250.0f, 382.0f);
			window.draw(three_text.access_text());
			suggestion_output four_text("fonts\\FORTE.ttf", "Complete", 44, 250.0f, 550.0f);
			window.draw(four_text.access_text());
			//output to the screen
			window.display();

			//the algorithm for recognizing mouse clicks on a specific button
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (one.access_squa().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
				{
					menu_switch &= ~(option_0);
					menu_switch |= option1;
				}
				if (two.access_squa().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
				{
					menu_switch &= ~(option_0);
					menu_switch |= option4;
				}
				if (three.access_squa().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
				{
					window.close();
				}
				//if the user clicked on "finish", then we send the data to the server
				if (four.access_squa().getGlobalBounds().contains(static_cast<float>(mousepozition.x), static_cast<float>(mousepozition.y)))
				{
					std::ofstream server_save;
					server_save.open("server.txt");
					assert(server_save.is_open() && "Server is not open");
					ani = 0;
					server_save << "NPopen\n";
					while (true)
					{
						server_save << name_of_products[ani];
						server_save << '\n';
						ani++;
						if (ani == name_of_products.size())
						{
							server_save << "NP close\n";
							break;
						}
					}
					ani = 0;
					server_save << "QPopen\n";
					while (true)
					{
						server_save << quanity_of_products[ani];
						server_save << '\n';
						ani++;
						if (ani == quanity_of_products.size())
						{
							server_save << "QPclose\n";
							break;
						}
						
					}
					ani = 0;
					server_save << "PDopen\n";
					while (true)
					{
						server_save << product_description[ani];
						server_save << '\n';
						ani++;
						if (ani == product_description.size())
						{
							server_save << "PDclose\n";
							break;
						}
					}
					server_save.close();
				}
			}
		}
		//menu with option1
		if (menu_switch & option1)
		{
			Event event;
			while (window.pollEvent(event))
			{
				
				if (event.type == Event::Closed)
					window.close();
				//the algorithm for performing an action on specifically pressed keys
				if (event.type == Event::TextEntered)
				{
					if (event.text.unicode > 96 && event.text.unicode < 123 && universal.size()<13)
					{
						universal += static_cast<char>(event.text.unicode);
					}
					if (event.text.unicode == 8 && universal.size()>0)
						universal.pop_back();
					if (event.text.unicode == 13)
					{
						ani = 0;
						while (true)
						{
							if (name_of_products[ani] == "")
							{
								name_of_products[ani]= universal;
								universal = "";
								menu_switch &= ~(option1);
								menu_switch |= option2;
								break;
							}
							else
							{
								ani++;
								if (ani == name_of_products.size())
									name_of_products.resize(ani + 1);
							}
						}
					}
					if (event.text.unicode == 27)
					{
						menu_switch &= ~(option1);
						menu_switch |= option_0;
					}
				}
			}
			window.clear(Color::Black);
			background first("image\\FON.png", 2.0, 2.0, 0.0f, 900.0f);
			window.draw(first.access_sprite());
			suggestion_output one_text("fonts\\FORTE.ttf", "Name of products", 38, 100.0f, 182.0f);
			window.draw(one_text.access_text());
			blanks one(300.0f, 50.0f, 100.0f, 260.0f, 132, 132, 232, 10.0f, 77, 77, 221);
			window.draw(one.access_squa());
			suggestion_output two_text("fonts\\FORTE.ttf", universal, 38, 100.0f, 262.0f);
			window.draw(two_text.access_text());
			window.display();
		}
		//menu with option2
		if (menu_switch & option2)
		{
			window.clear(Color::Black);
			Event event;
			while (window.pollEvent(event))
			{
				
				if (event.type == Event::Closed)
					
					window.close();
				if (event.type == Event::TextEntered)
				{
					if (event.text.unicode > 47 && event.text.unicode < 58 && universal.size() < 3)
					{
						universal += static_cast<char>(event.text.unicode);
					}
					if (event.text.unicode == 8 && universal.size() > 0)
						universal.pop_back();
					if (event.text.unicode == 13)
					{
						ani = 0;
						while (true)
						{
							if (quanity_of_products[ani] == 0)
							{
								std::stringstream ofrend;
								ofrend << universal;
								universal = "";
								ofrend >> quanity_of_products[ani];
								menu_switch &= ~(option2);
								menu_switch |= option3;
								break;
							}
							else
							{
								ani++;
								if (ani == quanity_of_products.size())
								{
									quanity_of_products.resize(ani + 1);
									quanity_of_products[ani] = 0;
								}

							}
						}
					}
					if (event.text.unicode == 27)
					{
						menu_switch &= ~(option2);
						menu_switch |= option_0;
					}
				}
			}
			//display everything printed on the screen
			background first("image\\FON.png", 2.0, 2.0, 0.0f, 900.0f);
			window.draw(first.access_sprite());
			suggestion_output one_text("fonts\\FORTE.ttf", "Quanity of product", 38, 100.0f, 182.0f);
			window.draw(one_text.access_text());
			blanks one(300.0f, 50.0f, 100.0f, 260.0f, 132, 132, 232, 10.0f, 77, 77, 221);
			window.draw(one.access_squa());
			suggestion_output two_text("fonts\\FORTE.ttf", universal, 38, 100.0f, 262.0f);
			window.draw(two_text.access_text());
			window.display();
		}
		if (menu_switch & option3)
		{
			Event event;
			while (window.pollEvent(event))
			{
				
				if (event.type == Event::Closed)
				
					window.close();
				if (event.type == Event::TextEntered)
				{
					if (event.text.unicode > 96 && event.text.unicode < 123 && universal.size() < 13)
					{
						universal += static_cast<char>(event.text.unicode);
					}
					if (event.text.unicode == 8 && universal.size() > 0)
						universal.pop_back();
					if (event.text.unicode == 13)
					{
						ani = 0;
						while (true)
						{
							if (product_description[ani] == "")
							{
								product_description[ani]= universal;
								universal = "";
								menu_switch &= ~(option3);
								menu_switch |= option1;
								break;
							}
							else
							{
								ani++;
								if (ani == product_description.size())
									product_description.resize(ani + 1);
							}
						}
					}
					if (event.text.unicode == 27)
					{
						menu_switch &= ~(option3);
						menu_switch |= option_0;
					}
				}
			}
			//display everything printed on the screen
			window.clear(Color::Black);
			background first("image\\FON.png", 2.0, 2.0, 0.0f, 900.0f);
			window.draw(first.access_sprite());
			suggestion_output one_text("fonts\\FORTE.ttf", "Product description", 38, 100.0f, 182.0f);
			window.draw(one_text.access_text());
			blanks one(300.0f, 50.0f, 100.0f, 260.0f, 132, 132, 232, 10.0f, 77, 77, 221);
			window.draw(one.access_squa());
			suggestion_output two_text("fonts\\FORTE.ttf", universal, 38, 100.0f, 262.0f);
			window.draw(two_text.access_text());
			window.display();
		}
		
		if (menu_switch & option4)
		{
			Event event;
			while (window.pollEvent(event))
			{
				
				if (event.type == Event::Closed)
		
					window.close();
				if (event.type == Event::TextEntered)
				{
					if (event.text.unicode == 27)
					{
						menu_switch &= ~(option4);
						menu_switch |= option_0;
					}
				}
			}
			//create main table
			//create background for table
			window.clear(Color::White);
			blanks one(700.0f, 60.0f, 0.0f, 0.0f, 138, 138, 138, 0.0f);
			window.draw(one.access_squa());
			//create line table
			blanks line1(2.0f, 900.0f, 250.0f, 0.0f, 0, 0, 0, 0.0f);
			window.draw(line1.access_squa());
			blanks line2(2.0f, 900.0f, 500.0f, 0.0f, 0, 0, 0, 0.0f);
			window.draw(line2.access_squa());
			//create main text in table
			suggestion_output one_text("fonts\\arial.ttf", "Name of product", 24, 20.0f, 15.0f);
			window.draw(one_text.access_text());
			suggestion_output two_text("fonts\\arial.ttf", "Product description", 24, 275.0f, 15.0f);
			window.draw(two_text.access_text());
			suggestion_output three_text("fonts\\arial.ttf", "Quanity", 24, 550.0f, 15.0f);
			window.draw(three_text.access_text());
			ani = 0;
			float c = 0.0f;
			while (true)
			{
				//output of information about products in the table
				if (name_of_products[ani] == "")
					break;
				suggestion_output output1 = suggestion_output("fonts\\arial.ttf", name_of_products[ani], 26, 70.0f, (70.0f+c));
				window.draw(output1.access_text());
				suggestion_output output2 = suggestion_output("fonts\\arial.ttf", product_description[ani], 26, 350.0f, (70.0f + c));
				window.draw(output2.access_text());
				std::stringstream an;
				an<< quanity_of_products[ani];
				universal = "";
				an >> universal;
				an.str("");
				an.clear();
				suggestion_output output3=suggestion_output("fonts\\arial.ttf", universal, 26, 600.0f, (70.0f + c));
				window.draw(output3.access_text());
				blanks line4(900.0f, 2.0f, 0.0f, (115.0f+c), 0, 0, 0, 0.0f);
				window.draw(line4.access_squa());
				ani++;
				c += 50.0f;
				if (ani == static_cast<int>(name_of_products.size()))
					name_of_products.resize(ani + 1);
			}
			window.display();
		}
		
		
	}

	return 0;
}


