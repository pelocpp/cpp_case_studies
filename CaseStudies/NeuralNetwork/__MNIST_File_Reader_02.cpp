// See also
// https://github.com/wichtounet/mnist

#include <iostream>
#include <fstream>
#include <vector>

// Zusammenfassung
// train-images-idx3-ubyte:  60.000 Bilder für das Training.
// train-labels-idx1-ubyte:  Die 60.000 korrekten Ziffern dazu.
// t10k-images-idx3-ubyte:   10.000 Bilder für den Test.
// t10k-labels-idx1-ubyte:   Die 10.000 korrekten Ziffern dazu.


// Hilfsfunktion zum Umkehren der Byte-Reihenfolge (Big-Endian zu Little-Endian)
static uint32_t swapEndian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    return (val << 16) | (val >> 16);
}


// Siehht hübscher aus 
//static uint32_t swapEndian(uint32_t val) {
//    return ((val << 24) & 0xff000000) |
//        ((val << 8) & 0x00ff0000) |
//        ((val >> 8) & 0x0000ff00) |
//        ((val >> 24) & 0x000000ff);
//}

static constexpr auto MaxIterations = 6;

static void readMnistImages(std::string path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geoeffnet werden: " << path << std::endl;
        return;
    }

    uint32_t magic = 0, numImages = 0, rows = 0, cols = 0;

    // Header einlesen (4x 4-Byte Integer)
    file.read((char*)&magic, 4);
    file.read((char*)&numImages, 4);
    file.read((char*)&rows, 4);
    file.read((char*)&cols, 4);

    // Endianness korrigieren
    magic = swapEndian(magic);
    numImages = swapEndian(numImages);
    rows = swapEndian(rows);
    cols = swapEndian(cols);

    // Validierung: idx1 Magic Number ist immer 2049 (0x00000801)
    if (magic != 2051) {
        throw std::runtime_error("Ungueltige Magic Number fuer Labels!");
    }

    std::cout << "Magic: " << magic << ", Bilder: " << numImages
        << ", Format: " << rows << "x" << cols << std::endl;


    // Die ersten drei Bilder einlesen (28 * 28 Bytes)
    for (int n = 0; n < MaxIterations; n++) {
        std::vector<uint8_t> pixels(rows * cols);
        file.read((char*)pixels.data(), pixels.size());

        // Visualisierung in der Konsole
        for (int i = 0; i < (int)rows; i++) {
            for (int j = 0; j < (int)cols; j++) {
                // Wenn Pixelwert > 128, zeichne ein Zeichen, sonst Leerstelle
                std::cout << (pixels[i * cols + j] > 128 ? "##" : "  ");
            }
            std::cout << std::endl;
        }
    }

    file.close();
}

static std::vector<uint8_t> readMnistLabels(std::string path) {

    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Datei konnte nicht geoeffnet werden!");
    }

    uint32_t magicNumber = 0;
    uint32_t numberOfItems = 0;

    // 1. Header lesen (2x 4 Bytes)
    file.read(reinterpret_cast<char*>(&magicNumber), 4);
    file.read(reinterpret_cast<char*>(&numberOfItems), 4);

    // Byte-Reihenfolge korrigieren
    magicNumber = swapEndian(magicNumber);
    numberOfItems = swapEndian(numberOfItems);

    // Validierung: idx1 Magic Number ist immer 2049 (0x00000801)
    if (magicNumber != 2049) {
        throw std::runtime_error("Ungueltige Magic Number fuer Labels!");
    }

    // 2. Labels einlesen (jeweils 1 Byte pro Label)
    std::vector<uint8_t> labels(numberOfItems);
    file.read(reinterpret_cast<char*>(labels.data()), numberOfItems);

    file.close();

    // Die ersten drei Labels ausgeben
    for (int n = 0; n < MaxIterations; n++) {
        std::cout << "Label " << n << ": " << (char)(labels[n] + '0') << std::endl;
    }

    return labels;
}


static void read_MNIST_Files_02() {
    // Beispielaufruf für die Trainings-Bilder

    std::string filenameTrain = "../Resources/train-images-idx3-ubyte";
    //std::string filenameTrain = "../Resources/t10k-images-idx3-ubyte";
    readMnistImages(filenameTrain);

    std::string filenameLabels = "../Resources/train-labels-idx1-ubyte";
    // std::string filenameLabels = "../Resources/t10k-labels-idx1-ubyte";
    readMnistLabels(filenameLabels);
}
