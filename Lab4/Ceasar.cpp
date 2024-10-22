#include <iostream>
#include <string>
using namespace std;

class Crypto
{
    public:
    virtual string encrypt(const string& plaintext) = 0;
    virtual string decrypt(const std::string& ciphertext) = 0;
    
    virtual ~Crypto() = 0;
};
Crypto::~Crypto() {}

class Ceasar : public Crypto
{
    private:
    
    int shift;
    
    public:
    
    Ceasar(int shift)
    {
        this->shift = shift;
    }
    
    string encrypt(const string& text) override {
        string result = "";
    
        for (char c : text) {
            result += char(c + shift);
        }
        
        return result;
    }
    
    string decrypt(const string& text) override {
        string result = "";
    
        for (char c : text) {
            result += char(c - shift);
        }
        
        return result;
    }
    
    ~Ceasar() override {}
};

int main() {
    string text;
    int shift;
    
    cout << "Enter Text: ";
    cin >> text;
    
    cout << "Enter shift value: ";
    cin >> shift;
    
    Crypto& c = *new Ceasar(shift);

    string encryptedText = c.encrypt(text);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = c.decrypt(encryptedText);
    cout << "Decrypted text: " << decryptedText << endl;
    
    delete &c;
    
    return 0;
}