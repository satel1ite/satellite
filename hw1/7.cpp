#include <iostream>
#include <cstring>

bool PAL(char* str, int st, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (str[st + i] != str[st + len - 1 - i])
            return false;
    }
    return true;
}

int main() {
    //std::setlocale(LC_ALL, "");
    char s[101];
    std::cin.getline(s, 101);

    int max_len = 0;
    int st_ind = 0;

    int len = strlen(s);


    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            int sub_len = j - i + 1;

            if (PAL(s, i, sub_len)) {
                if (sub_len > max_len) {
                    max_len = sub_len;
                    st_ind = i;
                }
            }
        }
    }

    for (int i = 0; i < max_len; i++)
        std::cout << s[st_ind + i];

    return 0;
}
