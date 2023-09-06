/*
Open ACC

usa diretivas como o pragma

#pragma acc data copyin(a,b) copyout(c)
{
    #pragma acc parallel
    {
        #pragma acc loop gang vector
        for (i = 0; i < N; i++)
        {
            c[i] = a[i] + b[i];
        }
    }
}

para compilar: pgcc -fast -Minfo=accel -ta=tesla:managed main.c

pra tirar o manager precisa das clausilas copy, copyin, copyout

copy(array[starting_index:length])

*/