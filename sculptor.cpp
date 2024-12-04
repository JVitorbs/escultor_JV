#include "sculptor.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector3D>
#include <iostream>
#include <fstream>

// Construtor da classe Sculptor
Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx;  // Define o número de voxels na direção X
    ny = _ny;  // Define o número de voxels na direção Y
    nz = _nz;  // Define o número de voxels na direção Z

    // Aloca a matriz tridimensional de voxels
    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
        }
    }

    // Inicializa os voxels com valores padrão (invisíveis e cor preta/transparente)
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                v[i][j][k].show = false;  // Define que o voxel está invisível inicialmente
                v[i][j][k].r = v[i][j][k].g = v[i][j][k].b = v[i][j][k].a = 0.0f; // Cor preta e transparente
            }
        }
    }

    // Inicializa a cor atual (branco opaco)
    r = g = b = 1.0f;
    a = 1.0f;
}

// Destrutor da classe Sculptor
Sculptor::~Sculptor() {
    // Libera a memória alocada para a matriz de voxels
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];  // Libera cada vetor de voxels
        }
        delete[] v[i];  // Libera a linha de voxels
    }
    delete[] v;  // Libera o array de matrizes
}

// Define a cor atual para a criação de voxels
void Sculptor::setColor(float _r, float _g, float _b, float _a) {
    r = _r;  // Define o componente vermelho
    g = _g;  // Define o componente verde
    b = _b;  // Define o componente azul
    a = _a;  // Define o componente alfa (transparência)
}

// Coloca um voxel na posição (x, y, z)
void Sculptor::putVoxel(int x, int y, int z) {
    // Verifica se os índices estão dentro dos limites da matriz
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = true;  // Torna o voxel visível
        v[x][y][z].r = r;  // Atribui a cor vermelha ao voxel
        v[x][y][z].g = g;  // Atribui a cor verde ao voxel
        v[x][y][z].b = b;  // Atribui a cor azul ao voxel
        v[x][y][z].a = a;  // Atribui a transparência ao voxel
    }
}

// Remove um voxel da posição (x, y, z)
void Sculptor::cutVoxel(int x, int y, int z) {
    // Verifica se os índices estão dentro dos limites da matriz
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = false;  // Torna o voxel invisível
    }
}

// Cria um bloco de voxels de forma cúbica com coordenadas (x0, y0, z0) a (x1, y1, z1)
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                putVoxel(i, j, k);  // Chama putVoxel para cada voxel dentro da caixa
            }
        }
    }
}

// Remove um bloco de voxels de forma cúbica com coordenadas (x0, y0, z0) a (x1, y1, z1)
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                cutVoxel(i, j, k);  // Chama cutVoxel para cada voxel dentro da caixa
            }
        }
    }
}

// Cria uma esfera de raio 'radius' com o centro em (xcenter, ycenter, zcenter)
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = xcenter - radius; i <= xcenter + radius; i++) {
        for (int j = ycenter - radius; j <= ycenter + radius; j++) {
            for (int k = zcenter - radius; k <= zcenter + radius; k++) {
                // Verifica se o ponto (i, j, k) está dentro da esfera
                if ((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter) <= radius * radius) {
                    putVoxel(i, j, k);  // Coloca um voxel dentro da esfera
                }
            }
        }
    }
}

// Remove uma esfera de raio 'radius' com o centro em (xcenter, ycenter, zcenter)
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = xcenter - radius; i <= xcenter + radius; i++) {
        for (int j = ycenter - radius; j <= ycenter + radius; j++) {
            for (int k = zcenter - radius; k <= zcenter + radius; k++) {
                // Verifica se o ponto (i, j, k) está dentro da esfera
                if ((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter) <= radius * radius) {
                    cutVoxel(i, j, k);  // Remove o voxel dentro da esfera
                }
            }
        }
    }
}

// Cria um elipsóide com centro em (xcenter, ycenter, zcenter) e raios (rx, ry, rz)
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = xcenter - rx; i <= xcenter + rx; i++) {
        for (int j = ycenter - ry; j <= ycenter + ry; j++) {
            for (int k = zcenter - rz; k <= zcenter + rz; k++) {
                // Verifica se o ponto (i, j, k) está dentro do elipsóide
                if (((i - xcenter)*(i - xcenter)) / (rx * rx) + ((j - ycenter)*(j - ycenter)) / (ry * ry) + ((k - zcenter)*(k - zcenter)) / (rz * rz) <= 1) {
                    putVoxel(i, j, k);  // Coloca um voxel dentro do elipsóide
                }
            }
        }
    }
}

// Remove um elipsóide com centro em (xcenter, ycenter, zcenter) e raios (rx, ry, rz)
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = xcenter - rx; i <= xcenter + rx; i++) {
        for (int j = ycenter - ry; j <= ycenter + ry; j++) {
            for (int k = zcenter - rz; k <= zcenter + rz; k++) {
                // Verifica se o ponto (i, j, k) está dentro do elipsóide
                if (((i - xcenter)*(i - xcenter)) / (rx * rx) + ((j - ycenter)*(j - ycenter)) / (ry * ry) + ((k - zcenter)*(k - zcenter)) / (rz * rz) <= 1) {
                    cutVoxel(i, j, k);  // Remove o voxel dentro do elipsóide
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    // Escreve o cabeçalho "COFF"
    file << "COFF\n";

    // Conta o número de voxels ativos (mostrados)
    int numVoxels = 0;
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                if (v[i][j][k].show) {
                    ++numVoxels;
                }
            }
        }
    }

    // Cada voxel tem 8 vértices e 6 faces
    int numVertices = numVoxels * 8;
    int numFaces = numVoxels * 6;

    // Escreve o número de vértices, faces e arestas (arestas = 0 no formato OFF/COFF)
    file << numVertices << " " << numFaces << " 0\n";

    // Escreve os vértices com cor (RGBA)
    int vertexIndex = 0; // Índice do vértice
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                if (v[i][j][k].show) {
                    // Cada voxel tem 8 vértices
                    file << i << " " << j << " " << k << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i + 1 << " " << j << " " << k << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i + 1 << " " << j + 1 << " " << k << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i << " " << j + 1 << " " << k << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i << " " << j << " " << k + 1 << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i + 1 << " " << j << " " << k + 1 << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i + 1 << " " << j + 1 << " " << k + 1 << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";

                    file << i << " " << j + 1 << " " << k + 1 << " "
                         << int(v[i][j][k].r * 255) << " "
                         << int(v[i][j][k].g * 255) << " "
                         << int(v[i][j][k].b * 255) << " "
                         << int(v[i][j][k].a * 255) << "\n";
                }
            }
        }
    }

    // Escreve as faces
    for (int i = 0; i < numVoxels; ++i) {
        int baseIndex = i * 8;
        file << "4 " << baseIndex << " " << baseIndex + 1 << " " << baseIndex + 2 << " " << baseIndex + 3 << "\n"; // Face frontal
        file << "4 " << baseIndex + 4 << " " << baseIndex + 5 << " " << baseIndex + 6 << " " << baseIndex + 7 << "\n"; // Face traseira
        file << "4 " << baseIndex << " " << baseIndex + 4 << " " << baseIndex + 7 << " " << baseIndex + 3 << "\n"; // Face esquerda
        file << "4 " << baseIndex + 1 << " " << baseIndex + 5 << " " << baseIndex + 6 << " " << baseIndex + 2 << "\n"; // Face direita
        file << "4 " << baseIndex + 3 << " " << baseIndex + 2 << " " << baseIndex + 6 << " " << baseIndex + 7 << "\n"; // Face superior
        file << "4 " << baseIndex << " " << baseIndex + 1 << " " << baseIndex + 5 << " " << baseIndex + 4 << "\n"; // Face inferior
    }

    file.close();
}
