#include <iostream>
#include <cmath>
#include <string>

char** FillSquareMatrix(const std::string& text, int& n) {
    int len = text.size();
    n = std::ceil(std::sqrt(len));
    char** matrix = new char* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new char[n];
        for (int j = 0; j < n; ++j)
            matrix[i][j] = ' ';
    }

    int k = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (k < len)
                matrix[i][j] = text[k++];
    return matrix;
}

char** FillSquareMatrixDecryption(const std::string& text, int& n) {
    int len = text.size();
    n = std::ceil(std::sqrt(len));
    char** matrix = new char* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new char[n];
        for (int j = 0; j < n; ++j)
            matrix[i][j] = ' ';
    }

    int k = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (k < len)
                matrix[j][i] = text[k++];
    return matrix;
}

char** TransposeMatrix(char** matrix, int n) {
    char** transposed = new char* [n];
    for (int i = 0; i < n; ++i) {
        transposed[i] = new char[n];
        for (int j = 0; j < n; ++j)
            transposed[i][j] = matrix[j][i];
    }
    return transposed;
}

void FreeMatrix(char** matrix, int n) {
    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

std::string CaesarEncrypt(const std::string& text, int shift) {
    std::string result = "";
    for (char c : text) {
        result += char(c + shift);
    }
    return result;
}

std::string CaesarDecrypt(const std::string& cipher, int shift) {
    std::string result = "";
    for (char c : cipher) {
        result += char(c - shift);
    }
    return result;
}

class DoubleCipher {
public:
    DoubleCipher(int cesarShift) : cesarShift(cesarShift) {}

    std::string Encrypt(const std::string& text) {
        std::string cesarEncrypted = CaesarEncrypt(text, cesarShift);

        int n;
        char** matrix = FillSquareMatrix(cesarEncrypted, n);
        char** transposed = TransposeMatrix(matrix, n);
        std::string encryptedText;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                encryptedText += transposed[i][j];

        FreeMatrix(matrix, n);
        FreeMatrix(transposed, n);

        return encryptedText;
    }

    std::string Decrypt(const std::string& cipher) {
        int n;
        char** matrix = FillSquareMatrixDecryption(cipher, n);
        std::string decryptedText;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] != ' ')
                    decryptedText += matrix[i][j];

        FreeMatrix(matrix, n);

        return CaesarDecrypt(decryptedText, cesarShift);
    }

private:
    int cesarShift;
};

int main() {
    std::string text;
    int cesarShift;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::cout << "Enter Caesar shift: ";
    std::cin >> cesarShift;

    DoubleCipher doubleCipher(cesarShift);

    std::string encryptedText = doubleCipher.Encrypt(text);
    std::cout << "Encrypted Text: " << encryptedText << std::endl;

    std::string decryptedText = doubleCipher.Decrypt(encryptedText);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}
