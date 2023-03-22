SHELL:=/bin/bash
CXX=g++
CXXFLAGS=-std=c++17 -g -pg -O1 
SANITFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined
VALGRINDFLAGS=--tool=memcheck --track-origins=yes --leak-check=full
CATCH= $$(pkg-config --cflags catch2)
FIGURES = prob.pdf size.pdf time.pdf profile1.pdf profile0.pdf percolation.pdf
DATA := datos32.txt datos64.txt datos128.txt datos256.txt datos512.txt
TIME := datosO1.txt datosO3.txt


all: simulation.out

test: sim_test.x


%.out: %.cpp
	source $$HOME/spack/share/spack/setup-env.sh; \
	spack load eigen; \
	$(CXX) $(CXXFLAGS) -Wall  $^ -o $@

%.x: %.o simul.o sim_ops_stats.o
	source $$HOME/spack/share/spack/setup-env.sh; \
	spack load catch2; \
	spack load eigen; \
	$(CXX) $(CXXFLAGS) $(CATCH) $^ -o $@

%.o: %.cpp
	source $$HOME/spack/share/spack/setup-env.sh; \
	spack load catch2; \
	spack load eigen; \
	$(CXX) $(CXXFLAGS) $(CATCH) -c $<

simul: main.x
	./$< 4  0.6 10



profile: main.x
	./$< 128 0.59271 10; \
	gprof ./$< gmon.out> profile.txt; \
	cat profile.txt

debug: main.x
	gdb ./&<

report: report.pdf ${FIGURES} 
	xdg-open $<

report.pdf: report.tex ${FIGURES} 
	pdflatex $<

percolation.pdf: script_percolation.gp
	gnuplot $<

prob.pdf: script_prob.gp ${DATA}
	gnuplot $<

size.pdf: script_size.gp ${DATA}
	gnuplot $<

time.pdf: script_time.gp ${TIME}
	gnuplot $<

profile1.pdf: script_profile-O1.gp profile_data-O1.txt
	gnuplot $<

profile0.pdf: script_profile-O0.gp profile_data-O0.txt
	gnuplot $<


#Crea el pdf delreporte. Por tanto, las figuras del reporte deben estar dentro del repositorio, no se deben crear desde cero. Así mismo el latex debe estar allí.

time: timechronos.out  #me da el tiempo de procesamiento con chronos, hace uso de clog por lo que se recomienda el uso de escritura sobre un .txt
clean: #Borra los archivos intermedios, temporales y ejecutables, dejando limpio el repositorio para que contenga solamente los archivos fundamentales
	rm -rf *.x *.out *.exe *.log *.aux *.pdf

# %.png:  # Crearlas imágenes con dos niveles diferentes de optimización del compilador.
# %.txt:  # Crear los datos para las imágenes
