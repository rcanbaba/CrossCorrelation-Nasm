//
//  main.c
//  CrossCorrelation
//
//  Created by Can Babaoğlu on 6.10.2019.
//  Copyright © 2019 Can Babaoğlu. All rights reserved.
//

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cross_correlation_asm_full(int* arr_1, int size_1, int* arr_2, int size_2, int* output, int output_size);


int main()
{
    int numberOfArrays;
    char buffer[100] = {0};
    
    int** arrays;
    int* arraySizes;
    int lineCount = 0;
    int i, j;
    
    const char arrayFileName[] = "arrays.txt";
    FILE* arrayFile = fopen(arrayFileName, "r");
    if (arrayFile == NULL)
    {
        fprintf(stderr, "Unable to open file %s!\n", arrayFileName);
        return 1;
    }
    
    
    //  read number of arrays
    fgets(buffer, 100, arrayFile);
    sscanf(buffer, "%d", &numberOfArrays);
    printf("%s contains %d arrays\n", arrayFileName, numberOfArrays);
    
    
    //  allocate memory for arrays
    arrays = malloc(numberOfArrays * sizeof(int*));
    if (arrays == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for arrays!\n");
        return 3;
    }
    //  and array sizes
    arraySizes = malloc(numberOfArrays * sizeof(int));
    if (arraySizes == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for arrays!\n");
        return 4;
    }
    
    
    //  read array file line by line
    for (lineCount = 0; lineCount < numberOfArrays; ++lineCount)
    {
        char* tok;
        int numberCount = 0;
        char tokenBuffer[100] = {0};
        int j;
        
        
        //  read line into buffer
        fgets(buffer, 100, arrayFile);
        
        //  count amount of numbers in the line string
        strcpy(tokenBuffer, buffer);
        tok = strtok(tokenBuffer, " \t\n");
        while (tok != NULL)
        {
            ++numberCount;
            tok = strtok(NULL, " \t\n");
        }
        //printf("Found %d numbers in line %d\n", numberCount, lineCount);
        arraySizes[lineCount] = numberCount;
        
        
        //  allocate memory for arrays[lineCount]
        arrays[lineCount] = malloc(numberCount * sizeof(int));
        if (arrays[lineCount] == NULL)
        {
            fprintf(stderr, "Unable to allocate memory for array %d\n", lineCount);
            return 2;
        }
        
        //  read numbers
        strcpy(tokenBuffer, buffer);
        tok = strtok(tokenBuffer, " \t\n");
        j = 0;
        while (tok != NULL)
        {
            sscanf(tok, "%d", &(arrays[lineCount][j]));
            tok = strtok(NULL, " \t\n");
            ++j;
        }
        
    }
    fclose(arrayFile);
    
    
    
    //  print all readed arrays
    printf("\n\n");
    printf("--- Arrays ---\n");
    for (i = 0; i < numberOfArrays; ++i)
    {
        int j = 0;
        for (j = 0; j < arraySizes[i]; ++j)
        {
            printf("%d ", arrays[i][j]);
        }
        printf("\n");
    }
    
    
    
    
    
    //  open an output file
    FILE* outputFile = fopen("cross_correlation_output_c.txt", "w");
    if (outputFile == NULL)
    {
        fprintf(stderr, "Unable to open output file for correlations!\n");
        return 4;
    }
    
    //  calculate result of all cross correlations
    //and write to output file
    for (i = 0; i < numberOfArrays-1; ++i)
    {
        for (j = i+1; j < numberOfArrays; ++j)
        {
            int output_size = arraySizes[i] + arraySizes[j] - 1;
            int* output = malloc(output_size * sizeof(int));
            int nonzeroCount = cross_correlation_asm_full(arrays[i], arraySizes[i], arrays[j], arraySizes[j], output, output_size);
            
         // printf("%d ->i, %d ->j, \n", i, j);
//            printf("%d ->i, %d ->j, arrays\n", arrays[i], arrays[j]);
//            printf("%d ->i, %d ->j, arraysize\n", arraySizes[i], arraySizes[j]);
//            printf("%d, %d outtt\n\n_____",output, output_size);
            
            //  write output to file
            int k = 0;
            for (k = 0; k < output_size; ++k)
            {
                fprintf(outputFile, "%d ", output[k]);
            }
            fprintf(outputFile, "\n");
            
            
            //  write number of nonzero elements
            fprintf(outputFile, "%d\n", nonzeroCount);
            
            
            //  deallocate output
            free(output);
        }
    }
    fclose(outputFile);
    
    
    //  deallocate
    for (i = 0; i < numberOfArrays; ++i)
    {
        free(arrays[i]);
    }
    free(arrays);
    free(arraySizes);
            
    
    return 0;
}

int cross_correlation_asm_full(int* arr_1, int size_1, int* arr_2, int size_2, int* output, int output_size){
    
    
    
//    printf("arr_10: %d ", arr_1[0]);
//    printf("arr_11: %d ", arr_1[1]);
//    printf("arr_12: %d ", arr_1[2]);
//    printf("arr_20: %d ", arr_2[0]);
//    printf("arr_21: %d ", arr_2[1]);
//    printf("arr_22: %d ", arr_2[2]);
    
    int a=0;
    int b=0;
    int n=0;
    
    for (n = 0; n < size_1 + size_2 - 1; n++)
    {
      int kmin, kmax, k;

      output[n] = 0;

      kmin = (n >= size_2 - 1) ? n - (size_2 - 1) : 0;
      kmax = (n < size_1 - 1) ? n : size_1 - 1;

        printf("NN: %d", n);
        printf(" kmin: %d", kmin);
        printf(" kmax: %d", kmax);
        b = kmin;
      for (k = kmax; k >= kmin; k--)
      {
          
        printf("\n/// KK: %d :: BB: %d :: ",k ,b);
        output[n] += arr_1[k] * arr_2[size_2 - b - 1 ];
        printf("arr_1: %d * ", arr_1[k]);
        printf("arr_2: %d ", arr_2[size_2 - b - 1]);
          b++;
         // b -- ;                  
      }
        
     printf(" le Out: %d \n", output[n]);
        
    }
    
    printf(" OUT:");
    
    for (a=0; a<output_size; a++){
        printf("-");
        printf("%d", output[a]);
        
    }
    
    printf("\n\n");
    
    
    //printf("%d ----- %d----- %d----- %d , CROSS\n", output[0], output[1],output[2],output[3]);
    
    return 0;
    
}




