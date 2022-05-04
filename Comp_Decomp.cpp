#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string decompression(std::string str)
{
    std::string text = "";
    int num;
    int size = str.length();
    for(int i = 0; i <= size; ++i)
    {
        if((str[i] <= 126 && str[i] >= 58) || (str[i] <= 46 && str[i] >= 33))
        {
        	int j = i + 1;

            while(!(str[j] == '\0' || str[j] == ' ' || str[j] == '\n' || (str[j] <= 126 && str[j] >= 58) || (str[j] <= 46 && str[j] >= 33))){j++;}

            --j;
            std::string ptr = str.substr(i + 1, j - i);
            num = stoi(ptr);
        	i += j - i;

            for (int k = 0;k < num; ++k)
            {
                if(((str[j - 2] <= 126 && str[j - 2] >= 58)) || (str[j - 2] <= 46 && str[j - 2] >= 33))
                {
                    text += str[j - 2];
				}
                else
                {
                    ++j;
                    text += str[j - 2];
                }
				
            }
			
        }
		else if(str[i] == ' ') 
		{                        
			int j = i + 1;
			while(!(str[j] == '\0' || str[j] == ' ' || str[j] == '\n' || (str[j] <= 126 && str[j] >= 58) || (str[j] <= 46 && str[j] >= 33))){j++;}

        	--j;
			std::string ptr = str.substr(i + 1, j - i);
			num = std::stoi(ptr);
			i += j - i;

			for (int k = 0;k < num; ++k)
			{
				
				if(str[j - 2] == ' ')
            	{
                	text += ' ';
            	}
            	else
            	{
            		++j;
                	text += ' ';
            	}
				
			}
		
		}		
		else if(str[i + 1] == '\0') 
		{                        
        	text += '\n';                
		}
				
	}
	str = "";

    return text;
}
            

    
std::string compressor(std::string text)
{   
	std::string zip = "";
	static int count = 1;

	for(int i = 0; i < text.length(); ++i)
	{
		
		if(text[i] == text[i + 1])
		{   
			count++;
		}
		else if(text[i + 1] == '\0')
		{
			zip += text[i];
			zip += std::to_string(count);
			zip += '\n';
		}
		else
        {
            zip+= text[i];
			zip += std::to_string(count);
			count = 1;
        }

       
    }

        return zip;
}

int main()
{
	std::string text;
	int choice;
	std::cout << "Press 1 if you want to compress a file " << std::endl;
	std::cout << "Press 2 if you want to decompress a file " << std::endl;
	std::cin >> choice;
	
	if(choice == 1)
	{	
		std::cout << "You have chosen to comppress a file:" << std::endl;
		std::cout << "Please enter the name of the file you want to compress" << std::endl;
		std::string path_in;
		std::cin >> path_in;
		std::cout << "And now, please enter the file you want to write the decompressed text in" << std::endl;
		std::string path_out;
		std::cin >> path_out;
		std::ifstream fin(path_in);
		std::ofstream fout(path_out);
		if(fin.is_open())
		{

			while(std::getline(fin, text))

			{
				if(compressor(text).length() > text.length())

				{
					std::cout << "Please try again, the compressed text is going to be longer than the initial one." << std::endl;
					break;
				}
				else
				{
					if (fout.is_open())
				{
					fout << compressor(text);
				}
				}
				std::cout << std::endl;
			}
		}
		fout.close();
		fin.close();
	}
    else
	{
		std::cout << "You have chosen to decompress a file:" << std::endl;
		std::cout << "Please enter the name of the file you want to decompress" << std::endl;
		std::string path_in;
		std::cin >> path_in;
		std::cout << "And now, please enter the file you want to write the decompressed text in" << std::endl;
		std::string path_out;
		std::cin >> path_out;
		std::ofstream fout(path_out);
		std::ifstream fin(path_in);
		if(fin.is_open())
		{
			
			while(std::getline(fin, text))	

			{
				if (fout.is_open())
				{
					fout << decompression(text);
				}
			}
			std::cout << std::endl;
        }
		
		fout.close();
		fin.close();
	}	
	}
