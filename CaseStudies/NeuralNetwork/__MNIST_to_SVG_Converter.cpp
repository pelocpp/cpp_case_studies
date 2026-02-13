#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// MNIST headers are Big-Endian; this helper swaps bytes for x86/x64 systems
static uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

static void mnist_to_svg_converter()
{
    std::string filename = "digit.idx";
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }

    uint32_t magic, num_images, rows, cols;
    file.read((char*)&magic, 4);
    file.read((char*)&num_images, 4);
    file.read((char*)&rows, 4);
    file.read((char*)&cols, 4);

    // Convert from Big-Endian
    num_images = swap_endian(num_images);
    rows = swap_endian(rows);
    cols = swap_endian(cols);

    std::cout << "Converting first image (" << rows << "x" << cols << ")..." << std::endl;

    // Read the first image's pixels (28x28 = 784 bytes)
    std::vector<unsigned char> pixels(rows * cols);
    file.read((char*)pixels.data(), rows * cols);

    // Open SVG output
    std::ofstream svg("digit.svg");
    svg << "<svg xmlns='http://www.w3.org/2000/svg' width='" << cols * 10 << "' height='" << rows * 10 << "'>\n";

    // Background
    svg << "  <rect width='100%' height='100%' fill='aliceblue' />\n";

    for (int r = 0; r < (int)rows; ++r) {
        for (int c = 0; c < (int)cols; ++c) {
            int val = pixels[r * cols + c];
            if (val > 0) { // Only draw non-white pixels
                // Map 0-255 grayscale to CSS rgb()
                // MNIST: 0=background, 255=foreground
                int color = 255 - val;
                svg << "  <rect x='" << c * 10 << "' y='" << r * 10
                    << "' width='10' height='10' fill='rgb("
                    << color << "," << color << "," << color << ")' />\n";
            }
        }
    }

    svg << "</svg>";
    svg.close();
    std::cout << "Done! Saved to digit.svg" << std::endl;
}

// ======================

static bool createSingleMNISTFile(const std::string& filename)
{
    std::ifstream ifile(filename, std::ios::binary);

    if (!ifile) {
        std::cerr << "Failed to open the IDX3-UBYTE file." << std::endl;
        return {};
    }

    // Read the IDX3-UBYTE file header
    char magicNumber[4];
    char numImagesBytes[4];
    char numRowsBytes[4];
    char numColsBytes[4];

    ifile.read(magicNumber, 4);
    ifile.read(numImagesBytes, 4);
    ifile.read(numRowsBytes, 4);
    ifile.read(numColsBytes, 4);

    // Initialize a vector to store the images
    std::vector<unsigned char> image(28 * 28);
    ifile.read((char*)(image.data()), 28 * 28);
    ifile.close();

    // Open target output
    std::ofstream ofile("digit.idx");

    // numImagesBytes = 1;
    numImagesBytes[0] = 0;
    numImagesBytes[1] = 0;
    numImagesBytes[2] = 0;
    numImagesBytes[3] = 1;

    ofile.write(magicNumber, 4);
    ofile.write(numImagesBytes, 4);
    ofile.write(numRowsBytes, 4);
    ofile.write(numColsBytes, 4);

    ofile.write((char*)image.data(), 28 * 28);
    ofile.close();
    std::cout << "Done! Saved to digit.idx" << std::endl;

    return true;
}

static bool createSingleMNISTFile()
{
    std::string filename = "../Resources/train-images-idx3-ubyte";

    return createSingleMNISTFile(filename);
}

