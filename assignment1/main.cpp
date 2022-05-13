#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string turn_add_string(string str, int time) {
    string s = str;
    int add_time = time - s.length();
    int i = 0;

    while (i != add_time) {
        s = "0" + s;
        i++;
    }

    return s;
}

string add(string num1, string num2, int base) {
    string str1 = num1;
    string str2 = num2;
    string result = "";
    int tmpR = 0;
    int tmpA = 0;
    int tmpB = 0;
    int tmpC = 0;
    int time = max(str1.length(), str2.length()) + 1;
    str1 = turn_add_string(str1, time);
    str2 = turn_add_string(str2, time);

    for (int i = time - 1; i >= 0; i--) {
        tmpA = str1[i] - '0';
        tmpB = str2[i] - '0';
        tmpR = tmpC + tmpA + tmpB;

        if (tmpR >= base) {
            tmpC = 1;
            tmpR -= base;
        }
        else {
            tmpC = 0;
        }

        if (i == 0 && tmpR == 0)
        {
            break;
        }

        result = std::to_string(tmpR) + result;
    }

    return result;
}

string inc(string str1, string str2, int base) {
    int length = max(str1.length(), str2.length());
    int carry = 0;
    //two digits' sum
    int sum = 0;
    string res;

    //add zero(s)
    while (str1.length() < length)
        str1.insert(0, "0");

    while (str2.length() < length)
        str2.insert(0, "0");

    for (int i = length - 1; i >= 0; i--) {
        sum = (str1[i] - '0') + (str2[i] - '0') + carry;
        carry = sum / base;
        res.insert(0, to_string(sum % base));
    }

    //carry > 0
    if (carry) {
        res.insert(0, to_string(carry));
    }

    //handle unecessary zero(s)
    return res.erase(0, min(res.find_first_not_of('0'), res.length() - 1));
}

string subtract(string str1, string str2, int base) {
    int length = max(str1.length(), str2.length());
    //the difference between str1[i] and str2[i]
    int dif = 0;
    string res;

    while (str1.length() < length)
        str1.insert(0, "0");

    while (str2.length() < length)
        str2.insert(0, "0");

    for (int i = length - 1; i >= 0; i--) {
        dif = (str1[i] - '0') - (str2[i] - '0');
        if (dif >= 0)
            res.insert(0, to_string(dif));
        else {
            //catch previous data
            int pre = i - 1;
            while (pre >= 0) {
                str1[pre] = ((str1[pre] - '0') - 1) % base + '0';
                if (str1[pre] != '0' + base - 1)
                    break;
                else
                    pre--;
            }

            res.insert(0, to_string(dif + base));
        }

    }

    return res.erase(0, min(res.find_first_not_of('0'), res.length() - 1));
}

string mul(string str1, string str2, int base) {
    int length = max(str1.length(), str2.length());

    while (str1.length() < length) {
        str1.insert(0, "0");
    }

    while (str2.length() < length) {
        str2.insert(0, "0");
    }

    if (length == 1) {
        int tmp = (str1[0] - '0') * (str2[0] - '0');

        if (tmp < base)
        {
            return to_string(tmp);
        }

        int carry = tmp / base;
        int remained = tmp % base;

        return to_string(carry) + to_string(remained);
    }

    string str1_1 = str1.substr(0, length / 2);
    string str1_2 = str1.substr(length / 2, length - length / 2);
    string str2_1 = str2.substr(0, length / 2);
    string str2_2 = str2.substr(length / 2, length - length / 2);

    string p0 = mul(str1_1, str2_1, base);
    string p1 = mul(str1_2, str2_2, base);
    string p2 = mul(inc(str1_1, str1_2, base), inc(str2_1, str2_2, base), base);
    string p3 = subtract(p2, inc(p0, p1, base), base);

    for (int i = 0; i < 2 * (length - length / 2); i++) {
        p0.append("0");
    }

    for (int i = 0; i < length - length / 2; i++) {
        p3.append("0");
    }

    string res = inc(inc(p0, p1, base), p3, base);

    return res.erase(0, min(res.find_first_not_of('0'), res.length() - 1));
}

int main() {
    std::stringstream str2digit;
    string str1 = "";
    string str2 = "";
    int base = 0;
    cin >> str1;
    cin >> str2;
    cin >> base;
    string sum = "";
    sum = add(str1, str2, base);
    string pro = "";
    pro = mul(str1, str2, base);

    cout << sum << " " << pro << endl;

    return 0;
}
