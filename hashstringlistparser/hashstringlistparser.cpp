#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdint.h>
#include <vector>

std::string to_lower_case(std::string s)
{
    for (uint64_t i = 0; i < s.length(); i++)
    {
        s[i] = std::tolower(s[i]);
    }

    return s;
}

int main(int argc, char* argv[])
{
    std::ifstream hash_to_string_list_file = std::ifstream(argv[1], std::ifstream::binary);

    if (!hash_to_string_list_file.good())
    {
        std::cout << "Error: " + std::string(argv[1]) + " could not be read." << std::endl;
    }

    hash_to_string_list_file.seekg(0, hash_to_string_list_file.end);

    uint64_t file_size = hash_to_string_list_file.tellg();

    hash_to_string_list_file.seekg(0, hash_to_string_list_file.beg);

    std::ofstream duplicates_file = std::ofstream("duplicates.txt", std::ofstream::binary);

    if (!duplicates_file.good())
    {
        std::cout << "Error: duplicates.txt could not be read." << std::endl;
    }

    std::map<uint64_t, uint64_t> hash_map;
    std::vector<std::string> hash_map_strings;
    std::vector<std::string> hash_strings;
    std::vector<std::string> hash_resource_type_strings;

    std::string line = "";

    while (std::getline(hash_to_string_list_file, line))
    {
        if (line.length() > 4)
        {
            std::string hash_string = line.substr(0, 16);
            std::string hash_resource_type = line.substr(17, 4);
            std::string ioi_string = line.substr(22, line.length() - 22);

            size_t pos = ioi_string.find_last_of('\r');

            if (pos != std::string::npos)
            {
                ioi_string.erase(pos, 1);
            }

            bool legal_line = false;

            std::string legal_chars = "0123456789ABCDEF";

            bool is_a_hash = false;

            if (hash_string.length() == 16)
            {
                is_a_hash = true;

                for (int i = 0; i < 16; i++)
                {
                    bool is_legal = false;

                    for (int j = 0; j < 16; j++)
                    {
                        if (hash_string[i] == legal_chars[j])
                        {
                            is_legal = true;
                        }
                    }

                    if (!is_legal)
                    {
                        is_a_hash = false;
                    }
                }
            }

            if (is_a_hash)
            {
                legal_line = true;
            }

            if (legal_line)
            {
                ioi_string = to_lower_case(ioi_string);

                uint64_t hash = std::strtoull(hash_string.c_str(), nullptr, 16);

                std::map<uint64_t, uint64_t>::iterator it = hash_map.find(hash);

                if (it != hash_map.end())
                {
                    std::string duplicate = hash_string + "." + hash_resource_type + "," + ioi_string + " has duplicate: " + hash_string + "." + hash_resource_type + "," + hash_map_strings.at(it->second) + "\n";

                    //if (ioi_string != hash_map_strings.at(it->second))
                    duplicates_file.write(duplicate.c_str(), duplicate.length());
                }
                else
                {
                    hash_strings.push_back(hash_string);

                    hash_map_strings.push_back(ioi_string);

                    hash_resource_type_strings.push_back(hash_resource_type);

                    hash_map[hash] = hash_map_strings.size() - 1;
                }
            }
            else
            {
                std::cout << "Not a legal line: " << line << std::endl;
            }
        }
    }

    std::ofstream master_hash_to_string_list_file = std::ofstream("master_hash_to_string_list.txt", std::ofstream::binary);

    if (!master_hash_to_string_list_file.good())
    {
        std::cout << "Error: master_hash_to_string_list.txt could not be read." << std::endl;
    }

    for (int i = 0; i < hash_strings.size(); i++)
    {
        std::string output = hash_strings.at(i) + "." + hash_resource_type_strings.at(i) + "," + hash_map_strings.at(i) + "\n";

        master_hash_to_string_list_file.write(output.c_str(), output.length());
    }

    return 0;
}
