/*
    #pragma omp target device(0) map (to from:3)
    #pragma omp teams num_teams(sizeBlocks) num_threads(bsize)
    #pragma omp distribute
    for (i = 0; i < N; i+= sizeBlocks){
        #pragma omp parallel for
        for (b = i; b < i + sizeBlocks; b++){
            B[b] += sin(B[b]);
        }
    }
    nota: no OpenACC é assim: #pragma acc kernels antes do primeiro loop


    #pragma omp target teams distribute parallel for map(to: a,b) map(from: c)
    for (i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    openMP                  openACC
    target                  parallel/kernels
    teams                   parallel/kernels
    distribute              loop gang
    sind                    loop vector

    #pragma omp target enter data map(to: a[0:Ndim*Ndim], b[0:Ndim]) map(tofrom: xold[0:Ndim], xnew[0:Ndim])
    while((conv > TOL) && (iter < MAX_ITER)){
        iter++;
        #pragma omp target
        #pragma omp teams distribute parallel for
        for (int i = 0; i < Ndim; i++){
            xnew[i] = 0.0;
            for (int j = 0; j < Ndim; j++){
                if (i != j){
                    xnew[i] += A[i*Ndim + j] * xold[i];
                }
                xnew[i] = (b[i] - xnew[i]) / A[i*Ndim + i];
            }
        }
        conv = 0.0;
        #pragma omp target
        #pragma omp teams distribute parallel for reduction(+:conv)
        for (int i = 0; i < Ndim; i++){
            tmp = xnew[i] - xold[i];
            conv += tmp * tmp;
        }
        conv = sqrt(conv);
        tmp_vector = xold;
        xold = xnew;
        xnew = tmp_vector;
    }
    #pragma omp target exit data map(from: xnew[0:Ndim])
*/