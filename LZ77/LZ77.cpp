#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

std::vector<std::tuple<int, int, char>> Compress(const std::string& input, int bufferSize = 256, int matchLimit = 15) {
    std::vector<std::tuple<int, int, char>> compressedData;
    int length = input.length();
    int cursor = 0;

    while (cursor < length) {
        int bestMatchLength = 0;
        int backDistance = 0;
        int searchStart = std::max(0, cursor - bufferSize);
        int searchEnd = cursor;

        for (int j = searchStart; j < searchEnd; ++j) {
            int matchLength = 0;
            while (matchLength < matchLimit &&
                cursor + matchLength < length &&
                input[j + matchLength] == input[cursor + matchLength]) {
                ++matchLength;
            }
            if (matchLength > bestMatchLength) {
                bestMatchLength = matchLength;
                backDistance = cursor - j;
            }
        }

        if (bestMatchLength > 0) {
            compressedData.emplace_back(backDistance, bestMatchLength, '\0');
            cursor += bestMatchLength;
        }
        else {
            compressedData.emplace_back(0, 0, input[cursor]);
            ++cursor;
        }
    }

    return compressedData;
}

std::string Decompress(const std::vector<std::tuple<int, int, char>>& compressedData) {
    std::string output;

    for (const auto& element : compressedData) {
        int backDistance, matchLength;
        char character;
        std::tie(backDistance, matchLength, character) = element;

        if (matchLength > 0) {
            int startIdx = output.size() - backDistance;
            for (int i = 0; i < matchLength; ++i) {
                output.push_back(output[startIdx + i]);
            }
        }
        else {
            output.push_back(character);
        }
    }

    return output;
}

void DisplayCompressed(const std::vector<std::tuple<int, int, char>>& compressedData) {
    for (const auto& element : compressedData) {
        int backDistance, matchLength;
        char character;
        std::tie(backDistance, matchLength, character) = element;

        if (matchLength > 0) {
            std::cout << "(" << backDistance << ", " << matchLength << ") ";
        }
        else {
            std::cout << "'" << character << "' ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::string userInput;
    std::cout << "Enter text: ";
    std::cin >> userInput;

    auto compressedData = Compress(userInput);
    std::cout << "Compressed data: ";
    DisplayCompressed(compressedData);

    auto decompressedData = Decompress(compressedData);
    std::cout << "Decompressed data: " << decompressedData << std::endl;

    return 0;
}
