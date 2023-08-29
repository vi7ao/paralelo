/* tipos de dados no MPI

lista dos tipos aqui: https://hpc-tutorials.llnl.gov/mpi/derived_data_type/#:~:text=Derived%20data%20types%20allow%20you,Vector

count = 5
MPI_Type_contiguous(count, MPI_INT, &t_vetor_int)

MPI_Type_vector(count, blocklenght, stride, oldtype, &newtype)
MPI_Type_hvector(count, blocklenght, stride, oldtype, newtype, ierr)

MPI_Type_extent(MPI_FLOAT, &extent)
exemplo:
MPI_Type_extent(MPI_FLOAT, &size_float)
MPI_Tupe_extent(MPI_INT, &size_int)
count = 2
oldtypes[0] = MPI_FLOAT
oldtypes[1] = MPI_INT
offset[0] = 0
offset[1] = 4 * size_float + size_int
block[0] = 3
block[1] = 1

MPI_Type_struct(count, blockcounts, offsets, oldtypes, &particletype)


prox aula: vetor de estruturas vs. estrutura de vetores
*/