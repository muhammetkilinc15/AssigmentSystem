#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


char * encoding(char *arr)
{

    char current = arr[0];
    int count=1;
    int j=0;
    char * result = (char *)calloc(100,sizeof(char));
    for (int  i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i+1]==current)
        {
            count++;
        }
        else
        {
            result[j++]=count+'0';
            result[j++]=current;
            current= arr[i+1];
            count=1;
        }
    }
    
    return result;
}

// int countNumWord(char *arr)
// {
//     // ahmet 0
//     int count = 0;
//     for (int i = 0; arr[i] != '0'; i++)
//     {
//         if (arr[i] != ' ')
//         {
//             while (arr[i] != ' ' && arr[i] != '0')
//             {
//                 i++;
//             }
//             i--;
//             count++;
//         }
//     }
//     return count;
// }
int **getDissimilarityMatrix(int *arr, int size);
int main(int argc, char const *argv[])
{



    char *ptr;
    char name[]="AAAAABBBCCDDDDDD";
    ptr = encoding(name);
    printf("%s",ptr);


    // float x, y;
    // x = atof(argv[1]);
    // y = atof(argv[2]);
    // printf("%f", (x * y));

    // int arr[] = {4, 7, 5, -2};
    // int **result;
    // result = getDissimilarityMatrix(arr, 4);

    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j <= i; j++)
    //     {
    //         printf("%d ", result[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}
// int **getDissimilarityMatrix(int *arr, int size)
// {
//     int **result = (int **)calloc(size, sizeof(int *));
//     for (int i = 0; i < size; i++)
//     {
//         result[i] = (int *)calloc(i + 1, sizeof(int));
//         for (int j = 0; j <= i; j++)
//         {
//             result[i][j] = (arr[i] - arr[j]) * (arr[i] - arr[j]);
//         }
//     }
//     return result;
// }

#include<string.h>
void Main ()
{
    char buf[100];
    int fd1= open("file1.txt",O_RDWR , O_CREAT,S_IRUSR , S_IWUSR);
    int fd2= open("file2.txt",O_RDWR , O_CREAT,S_IRUSR , S_IWUSR);

    strcpy(buf,"12345678901234567890");
    write(fd2,buf,20);
    write(fd1,buf,15);

    lseek(fd1,5,SEEK_SET);
    read(fd1,buf,10);
    lseek(fd2,-5,SEEK_END);
    lseek(fd1,-5,SEEK_CUR);
    write(fd1,buf,strlen(buf));

}