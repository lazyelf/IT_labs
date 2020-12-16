#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

typedef struct symbol_struct
{
    std::string symbol;
    std::string code = "";
    double p;
} SYMBOL;

class Node
{
private:
    SYMBOL *s;

public:
    Node *left = 0;
    Node *right = 0;

    SYMBOL *get_s()
    {
        return s;
    }
    std::string get_symbol()
    {
        return s->symbol;
    }
    std::string get_code()
    {
        return s->code;
    }
    double get_p()
    {
        return s->p;
    }

    Node(Node *l, Node *r)
    {
        s = new SYMBOL;
        this->s->symbol = r->s->symbol + l->s->symbol;
        this->s->p = l->s->p + r->s->p;
        this->left = l;
        this->right = r;
    }
    Node(SYMBOL *s)
    {
        this->s = s;
        left = right = 0;
    }
    ~Node() { delete s; }

    bool compare(Node *b)
    {
        return this->s->p > b->s->p;
    }

    void traversal_code(std::string code)
    {
        this->s->code = code;
        if (left)
        {
            left->traversal_code(code + "0");
            right->traversal_code(code + "1");
        }
    }

    void print(int wide)
    {
        //if (this != NULL)
        //  return;
        using namespace std;
        cout.width(wide + 3);
        cout << s->symbol + "\t\t";
        cout.width(8);
        cout << s->p << "\t\t" << s->code << "\n";
    }
};

class Analiser
{
private:
    int amount;
    std::vector<SYMBOL *> arr;
    std::string str;

public:
    Analiser() : amount(0) {}
    Analiser(std::string path)
    {
        amount = 0;
        std::ifstream in(path);

        if (in.is_open())
        {
            while (1)
            {
                std::string s;
                in >> s;
                if (s == "0")
                {
                    break;
                }
                SYMBOL *add = new SYMBOL;
                add->symbol = s;
                in >> add->p;
                arr.push_back(add);
                ++amount;
            }

            in.close();
        }
        else
            std::cout << "Unable to open file";
    }
    ~Analiser()
    {
        arr.clear();
    }

    void print()
    {
        std::cout << "Table\n";
        for (int i = 0; i < amount; ++i)
        {
            std::cout << arr[i]->symbol.c_str() << "  " << arr[i]->p << '\t' << arr[i]->code << '\n';
        }
    }

    std::vector<Node *> create_node_array()
    {
        std::vector<Node *> n_arr;
        for (int i = 0; i < amount; ++i)
        {
            Node *add = new Node(arr[i]);
            n_arr.push_back(add);
        }
        return n_arr;
    }

    double calculate_l_av()
    {
        double l_av = 0;
        for (auto var : arr)
        {
            l_av += var->p * var->code.length();
        }
        return l_av;
    }
    double calculate_l_min()
    {
        double l_min = 0;
        for (auto var : arr)
        {
            l_min += var->p * log2(var->p);
        }
        return -l_min;
    }

    int get_amount()
    {
        return arr.size();
    }

    void create_string()
    {
        for (auto var : arr)
        {
            str += var->code;
        }
    }

    void print_triple_block(std::string code)
    {
        using namespace std;
        string result = triple_block(code);

        cout << "\nCombination to code: " << code << '\n';
        cout << "r₁ = k₁ xor k₂ = " << code[0] << " xor " << code[1] << " = " << result[0] << '\n';
        cout << "r₂ = k₁ xor k₃ = " << code[0] << " xor " << code[2] << " = " << result[1] << '\n';
        cout << "r₃ = k₂ xor k₃ = " << code[1] << " xor " << code[2] << " = " << result[3] << '\n';
        cout << "\nResult is:\n_________________________\n"
             << "|r₁ |r₂ |k₁ |r₃ |k₂ |k₃ |\n|";
        for (int i = 0; i < 6; ++i)
        {
            cout << result[i] << "  |";
        }
        cout << "\n-------------------------\n";

        char error = code[0] ^ code[1] ^ code[2];
        cout << "Eror = "
             << "k₁ xor k₂ xor k₃ = " << code[0] << " xor " << code[1] << " xor " << code[2] << " = " << error << '\n';

        int entered;
        cout << "Decoding:\n\t1 - decode without errors\n\t2 - invert 1 bit\n\t3 - invert 2 bits\n\t";
        cin >> entered;
        switch (entered)
        {
        case 2:
            cout << "Enter bit position: ";
            cin >> entered;
            if (entered > 6 || entered < 1)
                break;
            if (result[entered - 1] == '0')
            {
                result[entered - 1] = '1';
            }
            else
            {
                result[entered - 1] = '0';
            }
            break;
        case 3:
            for (int i = 0; i < 2; ++i)
            {
                cout << "Enter bit position: ";
                cin >> entered;
                if (entered > 6 || entered < 1)
                    break;
                if (result[entered - 1] == '0')
                {
                    result[entered - 1] = '1';
                }
                else
                {
                    result[entered - 1] = '0';
                }
            }
            break;
        default:
            break;
        }
        string s = decode_triple_block(result, error);
        cout << "Results of decoding is: " << s << '\n';
    }

    void print_quadruple_block(std::string code)
    {
        using namespace std;
        string result = quadruple_block(code);

        cout << "\nCombination to code: " << code << '\n';
        cout << "r₁ = k₁ xor k₂ xor k₄ = " << code[0] << " xor " << code[1] << " xor " << code[3] << " = " << result[0] << '\n';
        cout << "r₂ = k₁ xor k₃ xor k₄ = " << code[0] << " xor " << code[2] << " xor " << code[3] << " = " << result[1] << '\n';
        cout << "r₃ = k₂ xor k₃ xor k₄ = " << code[1] << " xor " << code[2] << " xor " << code[3] << " = " << result[3] << '\n';
        cout << "\nResult is:\n"
             << "_____________________________\n"
             << "|r₁ |r₂ |k₁ |r₃ |k₂ |k₃ |k₄ |\n|";
        for (int i = 0; i < 7; ++i)
        {
            cout << result[i] << "  |";
        }
        cout << "\n-----------------------------\n";

        char error = (code[0] ^ code[1] ^ code[2] ^ code[3]) + '0';
        cout << "Eror = "
             << "k₁ xor k₂ xor k₃ xor k₄ = " << code[0] << " xor " << code[1] << " xor " << code[2] << " xor " << code[3] << " = " << error << '\n';

        int entered;
        cout << "Decoding:\n\t1 - decode without errors\n\t2 - invert 1 bit\n\t3 - invert 2 bits\n\t";
        cin >> entered;
        switch (entered)
        {
        case 2:
            cout << "Enter bit position: ";
            cin >> entered;
            if (entered > 7 || entered < 1)
                break;
            if (result[entered - 1] == '0')
            {
                result[entered - 1] = '1';
            }
            else
            {
                result[entered - 1] = '0';
            }
            break;
        case 3:
            for (int i = 0; i < 2; ++i)
            {
                cout << "Enter bit position: ";
                cin >> entered;
                if (entered > 7 || entered < 1)
                    break;
                if (result[entered - 1] == '0')
                {
                    result[entered - 1] = '1';
                }
                else
                {
                    result[entered - 1] = '0';
                }
            }
            break;
        }
        string s = decode_quadruple_block(result, error);
        cout << "Results of decoding is: " << s << '\n';
    }

    std::string triple_block(std::string code)
    {
        std::string result = "000000";
        result[0] = (code[0] ^ code[1]) + '0';
        result[1] = (code[0] ^ code[2]) + '0';
        result[2] = code[0];
        result[3] = (code[1] ^ code[2]) + '0';
        result[4] = code[1];
        result[5] = code[2];
        return result;
    }

    std::string quadruple_block(std::string code)
    {
        std::string result = "0000000";
        result[0] = (code[0] ^ code[1] ^ code[3]);
        result[1] = (code[0] ^ code[2] ^ code[3]);
        result[2] = code[0];
        result[3] = (code[1] ^ code[2] ^ code[3]);
        result[4] = code[1];
        result[5] = code[2];
        result[6] = code[3];
        return result;
    }

    void hemming_code()
    {
        std::cout << '\n'
                  << str << "\n";
        for (const char *p = str.c_str(); *p != '\0'; ++p)
        {
            std::cout << "\nd = 3 or d = 4? (3/4/other - exit): ";
            int mode;
            std::cin >> mode;
            if (mode == 3)
            {
                std::string code = "";
                for (int i = 0; i < 3 && *p != '\0'; ++i, ++p)
                {
                    code += *p;
                }
                if (code.length() == 3)
                {
                    print_triple_block(code);
                }
            }
            else
            {
                if (mode == 4)
                {
                    std::string code = "";
                    for (int i = 0; i < 4 && *p != '\0'; ++i, ++p)
                    {
                        code += *p;
                    }
                    if (code.length() == 4)
                    {
                        print_quadruple_block(code);
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    std::string decode_quadruple_block(std::string result, char error)
    {
        std::string syndrome = "000";
        std::string code = "";
        syndrome[2] = (result[0] ^ result[2] ^ result[4] ^ result[6]) + '0';
        syndrome[1] = (result[1] ^ result[2] ^ result[5] ^ result[6]) + '0';
        syndrome[0] = (result[3] ^ result[4] ^ result[5] ^ result[6]) + '0';

        std::cout << "C₁ = r₁ xor k₁ xor k₂ xor k₄ = " << result[0] << " xor " << result[2] << " xor " << result[4] << " xor " << result[6] << " = " << syndrome[2] << '\n';
        std::cout << "C₂ = r₂ xor k₁ xor k₃ xor k₄ = " << result[1] << " xor " << result[2] << " xor " << result[5] << " xor " << result[6] << " = " << syndrome[1] << '\n';
        std::cout << "C₃ = r₃ xor k₂ xor k₃ xor k₄ = " << result[3] << " xor " << result[4] << " xor " << result[5] << " xor " << result[6] << " = " << syndrome[0] << '\n';

        char *p;
        int check = strtol(syndrome.c_str(), &p, 2);
        if (!check)
        {
            code += result[2];
            code += result[4];
            code += result[5];
            code += result[6];
            return code;
        }
        else
        {
            if (check == 1 || check == 2 || check == 4 || check > 7)
            {
                code = "Syndrome point on not informational symbol. Decoding is impossible. Resending is needed.\n";
                return code;
            }
            if (result[check - 1] == '0')
            {
                result[check - 1] = '1';
            }
            else
            {
                result[check - 1] = '0';
            }

            code += result[2];
            code += result[4];
            code += result[5];
            code += result[6];

            std::cout << "k₁ xor k₂ xor k₃ xor k₄ xor error = " << code[0] << " xor " << code[1] << " xor "  << code[2] << " xor "  << error << " = ";
            if ((code[0] ^ code[1] ^ code[2] ^ code[3] ^ error) - '0')
            {
                std::cout << "1\n";
                code = "Double error. Decoding is impossible. Resending is needed.\n";
                return code;
            }
            std::cout << "0\n";
        }

        return code;
    }

    std::string decode_triple_block(std::string result, char error)
    {
        std::string syndrome = "000";
        std::string code = "";
        syndrome[2] = result[0] ^ result[2] ^ result[4];
        syndrome[1] = result[1] ^ result[2] ^ result[5];
        syndrome[0] = result[3] ^ result[4] ^ result[5];

        std::cout << "C₁ = r₁ xor k₁ xor k₂ = " << result[0] << " xor " << result[2] << " xor " << result[4] << " = " << syndrome[2] << '\n';
        std::cout << "C₂ = r₂ xor k₁ xor k₃ = " << result[1] << " xor " << result[2] << " xor " << result[5] << " = " << syndrome[1] << '\n';
        std::cout << "C₃ = r₃ xor k₂ xor k₃ = " << result[3] << " xor " << result[4] << " xor " << result[5] << " = " << syndrome[0] << '\n';

        char *p;
        int check = strtol(syndrome.c_str(), &p, 2);
        if (!check)
        {
            code += result[2];
            code += result[4];
            code += result[5];
            return code;
        }
        else
        {
            if (check == 1 || check == 2 || check == 4 || check > 6)
            {
                code = "Syndrome point on not informational symbol. Decoding is impossible. Resending is needed.\n";
                return code;
            }
            if (result[check - 1] == '0')
            {
                result[check - 1] = '1';
            }
            else
            {
                result[check - 1] = '0';
            }

            code += result[2];
            code += result[4];
            code += result[5];

            std::cout << "k₁ xor k₂ xor k₃ xor error = " << code[0] << " xor " << code[1] << " xor "  << code[2] << " xor "  << error << " = ";
            if (code[0] ^ code[1] ^ code[2] ^ error)
            {
                std::cout << "1\n";
                code = "Double error. Decoding is impossible. Resending is needed.\n";
                return code;
            }
            std::cout << "0\n";
        }
        return code;
    }
};

bool comparator(Node *a, Node *b)
{
    return a->compare(b);
}

void sort_arr(std::vector<Node *> &arr)
{
    std::sort(arr.begin(), arr.end(), comparator);
}

void print_arr(std::vector<Node *> &arr, int iteration)
{
    std::cout << "\nTable iteration " << iteration << "\n";
    int wide = arr[0]->get_symbol().length();
    for (int i = 1; i < arr.size(); ++i)
    {
        int n_wide = arr[i]->get_symbol().length();
        if (n_wide > wide)
        {
            wide = n_wide;
        }
    }
    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i]->print(wide);
    }
    std::cout << "\n";
}

void delete_tree(Node *root)
{
    if (!root)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

void print_code(Node *root, int wide)
{
    if (!root)
        return;
    //root->print(wide);
    root->right->print(wide);
    root->left->print(wide);
}

Node *create_graph(std::vector<Node *> arr, int iteration, bool print)
{
    if (arr.size() == 1)
    {
        arr[0]->traversal_code("");
        return arr[0];
    }
    sort_arr(arr);
    Node *l = arr.back();
    arr.pop_back();
    Node *r = arr.back();
    arr.pop_back();
    Node *n = new Node(l, r);
    arr.push_back(n);

    if (arr[0]->get_p() != 1 && print)
        print_arr(arr, iteration);

    return create_graph(arr, iteration + 1, print);
}

std::vector<Node *> delete_node(std::vector<Node *> arr, Node *dell)
{
    std::vector<Node *> ret;
    int i = 0;
    for (; i < arr.size(); ++i)
    {
        if (arr[i] == dell)
            break;
        ret.push_back(arr[i]);
    }
    for (++i; i < arr.size(); ++i)
    {
        ret.push_back(arr[i]);
    }
    return ret;
}

void make_code_table(Node *root, int size, bool print)
{
    std::vector<Node *> arr;
    arr.push_back(root);
    for (int i = size - 1; i > 0; --i)
    {
        Node *dell;
        for (int j = arr.size(); j != 0; --j)
        {
            if (arr[j - 1]->left)
            {
                dell = arr[j - 1];
            }
        }
        arr = delete_node(arr, dell);
        arr.push_back(dell->right);
        arr.push_back(dell->left);

        sort_arr(arr);
        if (i != 1 && print)
            print_arr(arr, i - 1);
    }
}

int main(int argc, char *argv[])
{
    std::string name;
    if (argc < 2)
    {
        using namespace std;
        cout << "Please, enter file name: ";
        std::getline(std::cin, name, '\n');
    }
    else
    {
        name = argv[1];
    }
    Analiser *a = new Analiser(name);
    a->print();

    std::cout << "\nPrint code table? (y/n): ";
    std::string s;
    std::cin >> s;
    Node *top;
    if (s == "y")
    {
        top = create_graph(a->create_node_array(), 1, true);
        top->traversal_code("");
        make_code_table(top, a->get_amount(), true);
    }
    else
    {
        top = create_graph(a->create_node_array(), 1, false);
        top->traversal_code("");
        make_code_table(top, a->get_amount(), false);
    }

    a->print();
    std::cout << "\nLmin = " << a->calculate_l_min();
    std::cout << "\nLav  = " << a->calculate_l_av() << '\n';

    delete_tree(top);

    a->create_string();
    a->hemming_code();

    delete a;
    return 0;
}
