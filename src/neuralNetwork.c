#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_INPUTS 3
#define NUM_SAMPLES 4

void runNeuralNetwork() {
    int targetOutputs[NUM_SAMPLES] = {0, 1, 1, 1};
    int epoch = 0;
    double learningRate = 0.1;
    double weights[NUM_INPUTS];
    int inputSequences[NUM_SAMPLES][NUM_INPUTS] = {
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    double errors[NUM_SAMPLES] = {0};
    int threshold = 0;
    int output[NUM_SAMPLES] = {0};

    printf("   X1 \t   X2 \t   X3 \t   Target \t\n");
    printf("===============================================\n");
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < NUM_INPUTS; j++) {
            printf("   %d\t", inputSequences[i][j]);
        }
        printf("   %d\n", targetOutputs[i]);
    }
    printf("\n");

    srand((unsigned)time(0));
    for (int i = 0; i < NUM_INPUTS; i++) {
        weights[i] = -1 + (double)rand() / (RAND_MAX / (2));
        printf("Weight w%d = %f\n", i, weights[i]);
    }

    do {
        for (int i = 0; i < NUM_SAMPLES; i++) {
            double weightedSum = 0;
            for (int j = 0; j < NUM_INPUTS; j++) {
                weightedSum += inputSequences[i][j] * weights[j];
            }
            output[i] = (weightedSum >= threshold) ? 1 : 0;
            errors[i] = targetOutputs[i] - output[i];

            if (output[i] != targetOutputs[i]) {
                for (int j = 0; j < NUM_INPUTS; j++) {
                    weights[j] += learningRate * inputSequences[i][j] * errors[i];
                }
            }
        }
        epoch++;
    } while (epoch != 100);

    printf("===============================================\n");
    printf("New weights:\n");
    for (int i = 0; i < NUM_INPUTS; i++) {
        printf("w%d = %f\n", i, weights[i]);
    }

    printf("===============================================\n");
    for (int i = 0; i < NUM_SAMPLES; i++) {
        printf("Output = %d\n", output[i]);
    }
}

int main() {
    runNeuralNetwork();
    return 0;
}