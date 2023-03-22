#include "simul.hpp"

typedef struct Vecinos {
	Vecinos(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
	int i;
	int j;
} Vecinos;

std::tuple<int,bool> Perco_size(int i,int j, Eigen::MatrixXi M)
{
  int L = M.rows()-2;
  int count = 0;
  bool Perco = false;
	
	std::queue<Vecinos> Ve;
  Ve.push(Vecinos(i, j));


	while (!Ve.empty()) {
		Vecinos x = Ve.front(); // Se extrae el vecino "más antiguo"
		Ve.pop(); // Se elimina dicho vecino de la estructura
		int i = x.i; // Se guardan sus coordenadas
		int j = x.j;

    // Se verifica cuales de los 4 vecinos tienen valor 1
    if (M(i,j-1))
    {
      M(i,j-1) = 0;
      count += 1;
      Ve.push(Vecinos(i, j-1));
    }
    if (M(i,j+1))
		{
      M(i,j+1) = 0;
      count += 1;
      Ve.push(Vecinos(i, j+1));
    }

    if (M(i-1,j))
		{
      M(i-1,j) = 0;
      count += 1;
      Ve.push(Vecinos(i - 1, j));
    }
    if (M(i+1,j))
		{
		  if (i+1 == L) Perco = true; // Si llega al final de la matriz no extendida entonces es percolante
      M(i+1,j) = 0;
      count += 1;
      Ve.push(Vecinos(i + 1, j));
    }
		
	}

	return std::make_tuple(count,Perco);
}



int Big_Perco_size(int L,Eigen::MatrixXi &M)
{ // Calcula el tamaño (sin normalizar) 
  // del cluster percolante más grande
  bool Perco = false;
  bool current_Perco;
  int max_size = 0;
  int current_size = 0;

  for (int j=1; j<=L;j++) // Se recorre la primera fila 
  {                       // de la matriz no extendida
    if (M(1,j))
    { // Cuando un elemento de la primera fila es 1 entonces se procede a verificar si su cluster es percolante
      std::tie(current_size,current_Perco) = Perco_size(1,j,M);

      if (current_Perco && current_size > max_size)
      { // Si es percolante y tiene el tamaño actual más grande entonces se actualizan las variables
        Perco = current_Perco;
        max_size = current_size;
      }
    }
    
  }

  if (!Perco) // Si no hubo ningun percolante de ariba a abajo
  {           // entonces se verifica de derecha a izquierda con un sistema análogo al anterior
    max_size = 0;
    current_size = 0;
    Eigen::MatrixXi Transpose = M.transpose();
    for (int j=1; j<=L;j++)
    {
      if (Transpose(1,j))
      {
        std::tie(current_size,current_Perco) = Perco_size(1,j,Transpose);
        if (current_Perco && current_size > max_size)
        {
          Perco = current_Perco;
          max_size = current_size;
        }
      }
        
    }
  }

  return max_size;
}

