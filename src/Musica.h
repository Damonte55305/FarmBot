#ifndef MUSICA_H
#define MUSICA_H

class Musica {
public:
    Musica(int *melody, int* durations, int size);
    void reproducir();

private:
    int* melody;
    int* durations;
    int size;
};

#endif //MUSICA_H