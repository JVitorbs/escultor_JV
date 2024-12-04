#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <QtCore>

// Definição de uma estrutura Voxel, que contém informações sobre a cor, transparência e visibilidade de um voxel.
struct Voxel {
    float r, g, b;  // Componentes de cor: vermelho (r), verde (g) e azul (b)
    float a;        // Transparência do voxel (alfa)
    bool show;      // Flag que indica se o voxel está visível (ativado) ou não
};

// A classe Sculptor permite manipular uma matriz de voxels e desenhar formas tridimensionais (caixas, esferas, elipsóides).
class Sculptor {
private:
    Voxel ***v;  // Matriz 3D dinâmica de voxels, onde cada voxel contém informações de cor, transparência e visibilidade
    int nx, ny, nz;  // Dimensões da matriz de voxels (número de voxels nas direções X, Y e Z)
    float r, g, b, a;  // Cor e transparência atuais a serem aplicadas aos voxels

public:
    // Declaração de uma função que escreve a representação 3D dos voxels em um arquivo no formato OFF.
    void writeOFF(const char* filename);

    // Construtor da classe Sculptor que inicializa a matriz de voxels com as dimensões fornecidas.
    Sculptor(int _nx, int _ny, int _nz);

    // Destruidor da classe Sculptor que limpa a memória alocada para a matriz de voxels.
    ~Sculptor();

    // Método que define a cor e transparência para os voxels subsequentes.
    void setColor(float r, float g, float b, float a);

    // Método que coloca um voxel na posição (x, y, z) com a cor e transparência atuais.
    void putVoxel(int x, int y, int z);

    // Método que remove um voxel da posição (x, y, z).
    void cutVoxel(int x, int y, int z);

    // Método que cria uma caixa (volume cúbico) definida pelas coordenadas (x0, y0, z0) a (x1, y1, z1).
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

    // Método que remove uma caixa (volume cúbico) definida pelas coordenadas (x0, y0, z0) a (x1, y1, z1).
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

    // Método que cria uma esfera com o centro em (xcenter, ycenter, zcenter) e o raio 'radius'.
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);

    // Método que remove uma esfera com o centro em (xcenter, ycenter, zcenter) e o raio 'radius'.
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

    // Método que cria um elipsóide com centro em (xcenter, ycenter, zcenter) e raios (rx, ry, rz).
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    // Método que remove um elipsóide com centro em (xcenter, ycenter, zcenter) e raios (rx, ry, rz).
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    // Função que exporta a representação 3D dos voxels para um arquivo no formato OFF.
    // O formato OFF é usado para descrever objetos 3D em termos de vértices e faces.
    void writeOFF(const QString& filename);
};

#endif // SCULPTOR_H
