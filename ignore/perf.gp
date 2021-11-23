set term png
set output "perf.png"
set title "Desempenho Operacoes com Matrizes"
set xlabel "Dimensao da Matriz"
set ylabel "Tempo de Execucao (s)
set logscale y
set key left top
plot "ignore/perf.gpdat" u 1:2 w linesp t "Multiplicacao",\
"ignore/perf.gpdat" u 1:3 w linesp t "Soma",\
"ignore/perf.gpdat" u 1:4 w linesp t "Transposicao"