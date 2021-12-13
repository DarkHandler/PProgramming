#include <global.hh>
#include <timing.hpp> 

/////////////////////////////////////////////////////////////////////////////////
//   Usage:
//           ./program_name -nt T -nx S
//           T:   number of iterations to run for (default = 100)
//           S:   problem size (default = 15000)
//
//   Description:
//           Computes a[0:nx-1] = a[0:nx-1]*b[0:nx-1] + c[0:nx-1] T times, for array length nx
//           Reports time
//
/////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv) {
    //Time variables
    timing total_timer,iter_timer, t_elem; 
    total_timer.start();
    
    uint64_t niter=1000;
    uint64_t nx=15000;

    std::string mystr;
    double *a, *b, *c; 

    ///////////////////////////////////////
    //  Read command-line parameters -nt
    for (size_t i=0; i < argc; i++) {
        mystr=argv[i];
        if (mystr == "-nt"){
            niter=atoi(argv[i+1]);
        }
		if (mystr == "-nx"){ 
			nx=atoi(argv[i+1]);
		}
    }
    //std::cout << "Looping " << niter << " times."   << std::endl;
//	std::cout << "Problem size nx is: " << nx << std::endl;

    //////////////////////////////////////////
    // Initialize
    a = new double[nx];
	b = new double[nx]; 
	c = new double[nx];
    for (size_t i = 0; i < nx; i++) {
      a[i] = 1.0; 
	  b[i] = 2.0;  
	  c[i] = 5.0;
    }


    /////////////////////////////
    //  Compute Loop
	//  Determinar el tiempo de ejecución de este ciclo
    iter_timer.start(); //INICIAR CONTEO TIEMPO
    for (size_t j = 0; j < niter; j++) {
      for (size_t i = 0; i < nx; i++) {
			a[i] = a[i]*b[i]+c[i];
      }
    }
    iter_timer.stop(); //DETENER CONTEO DE TIEMPO
    
    delete [] a;
    delete [] b;
    delete [] c;
    
    total_timer.stop();
    
    std::cout << total_timer.elapsed() << std::endl;		// Descomentar solo para hacer el experimento
    std::cout << iter_timer.elapsed()/niter << std::endl;	// Descomentar solo para hacer el experimento
    std::cout << iter_timer.elapsed()/niter/nx << std::endl;	// Descomentar solo para hacer el experimento

    //Completar esta sección
    //std::cout << "Elapsed time (ms): " << total_timer.elapsed() << std::endl;// Comentar para hacer el experimento
    //std::cout << "Elapsed time per iteration (ms/iter): " << iter_timer.elapsed()/niter << std::endl;	// Comentar para hacer el experimento
    //std::cout << "Elapsed time per iteration per point (ms/iter/operation): " << iter_timer.elapsed()/niter/nx << std::endl; //Comentar para hacer el experimento			
}

