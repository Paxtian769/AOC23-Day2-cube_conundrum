#include <iostream>
#include <fstream>
#include <string>


int parse_number(std::string game_line, int &pos) {
    int val = 0;
    while (pos < game_line.length() && ('0' <= game_line[pos] && game_line[pos] <= '9'))
    {
        val = val * 10 + game_line[pos] - '0';
        pos++;
    }

    return val;
}

std::string parse_color(std::string game_line, int &pos) {
    std::string color = "";
    while (pos < game_line.length() && (game_line[pos] != ' ' && game_line[pos] != ';' && game_line[pos] != ','))
    {
        color += game_line[pos];
        pos++;
    }
    return color;
}


bool is_valid_game(std::string game_line, int &pos, int red_num, int green_num, int blue_num, int &power) {
    bool valid = false;

    int red_max = 0;
    int green_max = 0;
    int blue_max = 0;

    while (pos < game_line.length()) {
        int val;
        std::string color;
        val = parse_number(game_line, pos);
        pos++;
        color = parse_color(game_line, pos);
        pos+=2;
        if (color == "red") {
            if (val > red_max) {
                red_max = val;
            }
        }
        if (color == "green") {
            if (val > green_max) {
                green_max = val;
            }
        }
        if (color == "blue") {
            if (val > blue_max) {
                blue_max = val;
            }
        }
    }

    valid = (red_max <= red_num && green_max <= green_num && blue_max <= blue_num);

    power += (red_max * green_max * blue_max);

    return valid;
}


int game_id_parser(std::string game_line, int &pos) {
    int id = 0;

    for (pos = 5; pos < game_line.length() && (0 <= game_line[pos] && game_line[pos] <= '9'); pos++) {
        id = id * 10 + (game_line[pos] - '0');
    }

    return id;
}

int main(int argc, char **argv) {
    std::ifstream input_file;
    input_file.open("input.txt");

    std::string game_line;

    int game_id_total = 0;

    int red_num = 12;
    int green_num = 13;
    int blue_num = 14;

    int power = 0;


    while (std::getline(input_file, game_line)) {
        int pos = 0;
        int game_id = game_id_parser(game_line, pos);

        pos += 2;

        if (is_valid_game(game_line, pos, red_num, green_num, blue_num, power)) {
            game_id_total += game_id;
        }

    }

    std::cout << "Final ID count = " << game_id_total << '\n';
    std::cout << "Power = " << power << '\n';

    return 0;
}
