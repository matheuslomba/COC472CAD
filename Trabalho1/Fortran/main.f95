! compilador: gfortran main.f95
! ./a.out

!-------------------------------------------------------------------

program main

    implicit none
    integer :: maximo, ordem, i, j, b
    real :: ordemN
    real(8) :: tij_i, tij_f, tji_i, tji_f

    real*8, dimension(:,:), allocatable :: matrizA
    real*8, dimension(:), allocatable :: vetorX
    real*8, dimension(:), allocatable :: vetorB

    open(unit=1, file = "f95resultados.csv", status = "unknown", action = "write")
    write(1, "(a)") "ordemN, IJ, JI"

    do maximo = 0, 30 !maximo = +- 31.000

        print*, "--------------------------------------------------------------------"

        call random_number(ordemN)
        ordem = int(ordemN*1000) + maximo*1000

        print*, "Tamanho dos arrays: ", ordem
        print*, "--------------------------------"

        if (allocated(matrizA)) then
            deallocate(matrizA)
        endif
        if (allocated(vetorX)) then
            deallocate(vetorX)
        endif
        if (allocated(vetorB)) then
            deallocate(vetorB)
        endif
        allocate(matrizA(ordem, ordem))
        allocate(vetorX(ordem))
        allocate(vetorB(ordem))

        call random_seed
        call random_number(matrizA)
        call random_number(vetorX)

        ! Multiplicaij
        print*, "Primeira ordem de execução:"
        call cpu_time(tij_i)
        do i = 1, ordem
            b = 0
            do j = 1, ordem

                b = b + matrizA(i, j)*10 * vetorX(j)*10

            end do
            vetorB(i) = b

        end do
        call cpu_time(tij_f)
        print*, "Tempo de execução: ", tij_f-tij_i, " segundos."
    
        ! Multiplicaji
        print*, "Segunda ordem de execução:"
        call cpu_time(tji_i)
        do i = ordem, 1
            b = 0
            do j = ordem, 1

                b = b + matrizA(i, j)*10 * vetorX(j)*10

            end do
            vetorB(i) = b

        end do
        call cpu_time(tji_f)
        print*, "Tempo de execução: ", tji_f-tji_i, " segundos."

        write(1,*) ordem, ",", (tij_f-tij_i), ",", (tji_f-tji_i)

    end do

end program main


