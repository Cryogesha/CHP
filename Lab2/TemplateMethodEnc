#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Crypto
{
    public:
    virtual char* encrypt(const string &plaintext) = 0;
    virtual char* decrypt(const std::string &ciphertext) = 0;
    
    virtual ~Crypto() = 0;
};
Crypto::~Crypto() {}

class TemplateMethodDecrypter : public Crypto
{
    private:
    int len = 256;
    char* arr1;
    char* arr2; 
    
    int findIndex(char symbol)
    {
        int i = 0;
        while(arr2[i] != symbol)
        {
            i++;
        }
        
        return i;
    }
    
    public:
    TemplateMethodDecrypter()
    {
        arr1 = new char[len];
        arr2 = new char[len];
        
        for(int i = 0; i < len; i++)
        {
            arr1[i] = (char)i;
            arr2[i] = (char)(len - i);
        }
    }
    
    virtual char* encrypt(const string &plaintext) override {
        char* newtext = new char[plaintext.length()];
        
        for(int i = 0; i < plaintext.length(); i++)
        {
            *(newtext + i) = arr2[(int)plaintext[i]];
        }
    
        return newtext;
    }
    
    virtual char* decrypt(const std::string &ciphertext) override {
        char* newtext = new char[ciphertext.length()];
        
        for(int i = 0; i < ciphertext.length(); i++)
        {
            *(newtext + i) = arr1[findIndex(ciphertext[i])];
        }
    
        return newtext;
    }
    
    ~TemplateMethodDecrypter() override
    {
        delete[] arr1;
        delete[] arr2;
    }
};

int main() {
    Crypto& crypto = *new TemplateMethodDecrypter();
    
    std::string plaintext;
    std::cout << "Enter the plaintext: ";
    std::cin >> plaintext;
    
    std::string ciphertext = crypto.encrypt(plaintext);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    std::string decryptedText = crypto.decrypt(ciphertext);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    return 0;
}
