#include "sculptor.h"

int main() {
    // Inicializa o Sculptor com uma área maior para mais detalhes
    Sculptor sc(80, 80, 40);

    // Definir a cor marrom para a base
    sc.setColor(0.65f, 0.16f, 0.16f, 1.0f);  // Marrom

    // Criar a base da árvore (quadrado)
    sc.putBox(15, 25, 15, 25, 0, 3);

    // Definir a cor verde para a árvore
    sc.setColor(0.0f, 1.0f, 0.0f, 1.0f);  // Verde para a árvore

    // Criar a primeira camada da árvore (maior)
    sc.putBox(12, 28, 12, 28, 4, 6);  // Camada maior
    sc.putBox(13, 27, 13, 27, 7, 9);  // Camada intermediária

    // Criar a segunda camada da árvore (um pouco menor)
    sc.putBox(14, 26, 14, 26, 10, 12);
    sc.putBox(15, 25, 15, 25, 13, 15);

    // Criar a terceira camada da árvore (ainda menor)
    sc.putBox(16, 24, 16, 24, 16, 18);
    sc.putBox(17, 23, 17, 23, 19, 21);

    // Criar a quarta camada da árvore (menor ainda)
    sc.putBox(18, 22, 18, 22, 22, 24);
    sc.putBox(19, 21, 19, 21, 25, 27);

    // Criar a quinta camada da árvore (bem fina)
    sc.putBox(20, 20, 20, 20, 28, 30);

    // Criar a estrela no topo da árvore e bolas amarelas
    sc.setColor(1.0f, 1.0f, 0.0f, 1.0f);  // Cor amarela para a estrela
    sc.putSphere(20, 20, 31, 2);  // Colocando a estrela no topo
    sc.putSphere(26, 20, 15, 1);  // Bola2 de Natal na primeira camada
    sc.putSphere(18, 25, 18, 1);  // Bola na segunda camada
    sc.putSphere(23, 19, 23, 1);  // Bola2 na segunda camada
    sc.putSphere(29, 29, 6, 1);  // Bola
    sc.putSphere(18, 28, 7, 1);  // Bola


    sc.setColor(0.0f, 0.0f, 1.0f, 1.0f);  // Cor azul para a estrela
    sc.putSphere(24, 18, 18, 1);  // Bola2 na segunda camada
    sc.putSphere(28, 21, 8, 1);  // Bola
    sc.putSphere(20, 27, 11, 1);  // Bola

    // Adicionar algumas bolinhas de Natal (esferas vermelhas)
    sc.setColor(1.0f, 0.0f, 0.0f, 1.0f);  // Cor vermelha para as bolinhas
    sc.putSphere(22, 26, 15, 1);  // Bola de Natal na primeira camada
    sc.putSphere(24, 24, 20, 1);  // Bola na terceira camada
    sc.putSphere(17, 17, 23, 1);  // Bola na quarta camada
    sc.putSphere(28, 17, 10, 1);  // Bola
    sc.putSphere(27, 27, 12, 1);  // Bola


    sc.setColor(0.3f, 0.0f, 0.7f, 1.0f);  // Cor para bola presente
    sc.putSphere(29, 18, 2, 2);  // Bola presente chão

    sc.setColor(1.0f, 0.0f, 1.0f, 1.0f);  // Cor para o presente rosa
    sc.putBox(27, 30, 22, 27, 0, 2);  // presente 1 rosa

    sc.setColor(0.50f, 0.1f, 0.1f, 1.0f);  // Marrom
    sc.putEllipsoid(26, 30, 1, 2, 1, 1); //elipsoide no chão

    sc.setColor(0.0f, 0.6f, 1.0f, 1.0f);  // Cor para o presente cubo
    sc.putBox(20, 22, 28, 30, 0, 2);  // presente 2

    sc.setColor(1.0f, 0.9f, 0.8f, 1.0f);  // Cor clara com tons quentes para a lareira
    sc.putBox(0, 5, 30, 34, 0, 40);  // parede esquerda lareira
    sc.putBox(5, 5, 35, 45, 10, 40);  // meio lareira
    sc.putBox(0, 0, 35, 45, 0, 40);  // meio lareira
    sc.putBox(0, 5, 46, 50, 0, 40);  // direita lareira

    sc.setColor(0.65f, 0.16f, 0.16f, 1.0f);  // Marrom
    sc.putBox(1, 1, 37, 43, 0, 0);  // lenha
    sc.putBox(5, 5, 37, 43, 0, 0);  // lenha

    sc.putBox(1, 6, 38, 38, 1, 1);  // lenha
    sc.putBox(1, 6, 42, 42, 1, 1);  // lenha


    sc.setColor(1.0f, 1.0f, 0.0f, 1.0f); // chama amaraela
    sc.putBox( 3, 3, 39, 41, 0, 1);
    sc.putBox( 3, 3, 38, 42, 2, 2);
    sc.putBox( 3, 3, 39, 41, 3, 3);
    sc.putBox( 3, 3, 40, 40, 4, 4);

    sc.setColor(1.0f, 0.0f, 0.0f, 1.0f); // chama vermelha
    sc.putVoxel(3, 40, 5);
    sc.putVoxel(3, 41, 4);
    sc.putVoxel(3, 39, 4);
    sc.putVoxel(3, 42, 3);
    sc.putVoxel(3, 38, 3);
    sc.putVoxel(3, 43, 2);
    sc.putVoxel(3, 37, 2);

    // Exportar o modelo para um arquivo OFF
    sc.writeOFF("arvore_natal_fina_cor.off");

    return 0;
}
