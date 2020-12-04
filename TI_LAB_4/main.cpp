#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Process
{
private:
    vector<string> vocabulary;
    vector<int> code;
    string line;

public:
    Process(string path)
    {
        ifstream in(path);
        if (in.is_open())
        {
            string temp;
            do
            {
                in >> temp;
                vocabulary.push_back(temp);
            } while (!in.eof());

            in.close();
        }
        else
            cout << "Unable to open file";
    }

    bool search_str(string str)
    {
        for (int i = vocabulary.size() - 1; i >= 0; --i)
        {
            if (str == vocabulary[i])
                return true;
        }
        return false;
    }

    void coding(string path)
    {
        cout << "Enter string: ";
        string t;
        getline(cin, t);
        getline(cin, line);

        cout << "Coding table\n";
        int i = 0;
        while (line[i] != 0)
        {
            string buf_vocabulary;
            buf_vocabulary += line[i];
            buf_vocabulary += line[i + 1];
            string buf_code;
            string letter;

            do
            {
                buf_code = buf_vocabulary;
                i += 2;
                letter = "";
                letter += line[i];
                letter += line[i + 1];
                buf_vocabulary += letter;
            } while (search_str(buf_vocabulary));

            if (line[i] != '\0')
                vocabulary.push_back(buf_vocabulary);

            int order;
            for (int j = 0; j < vocabulary.size(); ++j)
            {
                if (buf_code == vocabulary[j])
                {
                    order = j + 1;
                    break;
                }
            }
            code.push_back(order);

            if (letter[0] != '\0')
            {
                cout << buf_code << '\t' << letter << '\t' << code.back() << '\t' << buf_vocabulary << " = " << vocabulary.size() << '\n';
            }
            else
            {
                cout << buf_code << "\t \t" << code.back() << '\t' << '\n';
            }
        }
        cout << "Result code is: ";

        ofstream out(path);
        if (out.is_open())
        {
            for (int i = 0; i < code.size(); ++i)
            {
                out << code[i] << ' ';
            }

            out.close();
        }
        else
            cout << "Unable to open file";
        print_code();
    }

    void print_code()
    {
        for (int i = 0; i < code.size(); ++i)
        {
            cout << ' ' << code[i];
        }
        cout << '\n';
    }

    void decoding(string path)
    {
        ifstream in(path);
        if (in.is_open())
        {
            int temp;
            do
            {
                in >> temp;
                code.push_back(temp);
            } while (!in.eof());

            in.close();
        }
        else
            cout << "Unable to open file";

        cout << "Decoding table\n";
        for (int i = 0; i < code.size() - 1; ++i)
        {
            line += vocabulary[code[i] - 1];

            string buf_vocabulary;
            if (i != code.size() - 2)
            {
                buf_vocabulary += vocabulary[code[i] - 1] + vocabulary[code[i + 1] - 1][0] + vocabulary[code[i + 1] - 1][1];
                vocabulary.push_back(buf_vocabulary);
                cout << code[i] << '\t' << code[i + 1] << '\t' << vocabulary[code[i] - 1] << '\t' << buf_vocabulary << '\n';
            }
            else
            {
                cout << code[i] << '\t' << "-" << '\t' << vocabulary[code[i] - 1] << '\t' << "-" << '\n';
            }
        }
        cout << "Result string is: " << line << '\n';
    }
};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Ukrainian");
    string file_name(argv[1]);
    Process *proc = new Process(file_name);
    cout << "Enter what you want to do:\n"
         << "1 - coding process\n"
         << "2 - decoding process\n";
    int choose;
    cin >> choose;
    if (choose == 1)
    {
        proc->coding(argv[2]);
    }
    else
    {
        proc->decoding(argv[2]);
    }

    delete proc;
    return 0;
}