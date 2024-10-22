#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class Crypto
{
    public:
    virtual string encrypt(const string& plaintext) = 0;
    virtual string decrypt(const std::string& ciphertext) = 0;
    
    virtual ~Crypto() = 0;
};
Crypto::~Crypto() {}

class TransposeCoder : public Crypto
{
    private:
    char** fillSquareMatrix(const string& text, int& n) {
        int len = text.size();
        n = ceil(sqrt(len));
    
        char** matrix = new char*[n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new char[n];
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = ' ';
            }
        }
    
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (k < len) {
                    matrix[i][j] = text[k++];
                }
            }
        }
        return matrix;
    }
    
    char** fillSquareMatrixDecryption(const string& text, int& n) {
        int len = text.size();
        n = ceil(sqrt(len));
    
        char** matrix = new char*[n];
        for (int i = 0; i < n; ++i) {
            matrix[i] = new char[n];
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = ' ';
            }
        }
        
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (k < len) {
                    matrix[j][i] = text[k++];
                }
            }
        }
        return matrix;
    }
    
    char** transposeMatrix(char** matrix, int n) {
        char** transposed = new char*[n];
        for (int i = 0; i < n; ++i) {
            transposed[i] = new char[n];
            for (int j = 0; j < n; ++j) {
                transposed[i][j] = matrix[j][i];
            }
        }
        return transposed;
    }
    
    void freeMatrix(char** matrix, int n) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    
    public:
    
    TransposeCoder(){}
    
    string encrypt(const string& text) override {
        int n;
        char** matrix = fillSquareMatrix(text, n);
    
        char** transposed = transposeMatrix(matrix, n);
        
        string encryptedText;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                    encryptedText += transposed[i][j];
            }
        }
        
        freeMatrix(matrix, n);
        freeMatrix(transposed, n);
    
        return encryptedText;
    }    
    
    string decrypt(const string& ciphertext) override{
        int n;
        char** matrix = fillSquareMatrixDecryption(ciphertext, n);

        string decryptedText;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] != ' ') {
                    decryptedText += matrix[i][j];
                }
            }
        }

        freeMatrix(matrix, n);
    
        return decryptedText;
    }
    
    ~TransposeCoder() override {}
};

int main() {
    string text;
    cout << "Enter the text to encrypt: ";
    cin >> text;

    Crypto& c = *new TransposeCoder();

    string encryptedText = c.encrypt(text);
    cout << "Encrypted text: " << encryptedText << endl;
    
    string decryptedText = c.decrypt(encryptedText);
    cout << "Decrypted text: " << decryptedText << endl;
    
    delete &c;

    return 0;
}
